#include "Pbr.h"


NAMESPACE_TOPSIDE_BEGIN


struct SceneConstantBuffer
{
    alignas(16) mat4 ViewProjection[2];
    alignas(16) vec4 Eyeposition[2];
    alignas(16) vec3 LightDirection{};
    alignas(16) vec3 LightDiffuseColor{};
    alignas(16) int NumSpecularMipLevels{ 1 };
};

}

namespace Pbr {

struct Resources::Impl
{
    void Initialize(ID3D11Device* device)
    {
        // Set up pixel shader.
        Internal::ThrowIfFailed(device->CreatePixelShader(g_psPbrMain, sizeof(g_psPbrMain), nullptr, &Resources.PixelShader));

        // Check for device support for the optional feature that allows setting the render target array index from the vertex shader stage.
        D3D11_FEATURE_DATA_D3D11_OPTIONS3 options{};
        device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS3, &options, sizeof(options));
        if (options.VPAndRTArrayIndexFromAnyShaderFeedingRasterizer)
        {
            // Set up vertex shader with VPRT support.
            Internal::ThrowIfFailed(device->CreateInputLayout(Pbr::Vertex::vtx_desc, ARRAYSIZE(Pbr::Vertex::vtx_desc), g_vsPbrVprtMain, sizeof(g_vsPbrVprtMain), &Resources.InputLayout));
            Internal::ThrowIfFailed(device->CreateVertexShader(g_vsPbrVprtMain, sizeof(g_vsPbrVprtMain), nullptr, &Resources.VertexShader));
        }
        else
        {
            // Set up vertex shader with geometry shader due to no VPRT support.
            Internal::ThrowIfFailed(device->CreateInputLayout(Pbr::Vertex::vtx_desc, ARRAYSIZE(Pbr::Vertex::vtx_desc), g_vsPbrNoVprtMain, sizeof(g_vsPbrNoVprtMain), &Resources.InputLayout));
            Internal::ThrowIfFailed(device->CreateVertexShader(g_vsPbrNoVprtMain, sizeof(g_vsPbrNoVprtMain), nullptr, &Resources.VertexShader));
            Internal::ThrowIfFailed(device->CreateGeometryShader(g_gsPbrNoVprtMain, sizeof(g_gsPbrNoVprtMain), nullptr, &Resources.GeometryShader));
        }

        // Set up the constant buffers.
        static_assert((sizeof(SceneConstantBuffer) % 16) == 0, "Constant Buffer must be divisible by 16 bytes");
        const CD3D11_BUFFER_DESC pbrConstantBufferDesc(sizeof(SceneConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
        Internal::ThrowIfFailed(device->CreateBuffer(&pbrConstantBufferDesc, nullptr, &Resources.ConstantBuffer));

        // Samplers for environment map and BRDF.
        Resources.EnvironmentMapSampler = Texture::CreateSampler(device);
        Resources.BrdfSampler = Texture::CreateSampler(device);
    }

    struct DeviceResources
    {
        ComPtr<ID3D11SamplerState> BrdfSampler;
        ComPtr<ID3D11SamplerState> EnvironmentMapSampler;
        ComPtr<ID3D11InputLayout> InputLayout;
        ComPtr<ID3D11VertexShader> VertexShader;
        ComPtr<ID3D11GeometryShader> GeometryShader;
        ComPtr<ID3D11PixelShader> PixelShader;
        ComPtr<ID3D11Buffer> ConstantBuffer;
        ComPtr<ID3D11ShaderResourceView> BrdfLut;
        ComPtr<ID3D11ShaderResourceView> SpecularEnvironmentMap;
        ComPtr<ID3D11ShaderResourceView> DiffuseEnvironmentMap;
        mutable std::map<uint32, ComPtr<ID3D11ShaderResourceView>> SolidColorTextureCache;
    };

    DeviceResources Resources;
    TrackChanges<SceneConstantBuffer> SceneBuffer;
    uint32 SceneChangeCountBookmark{ 0 };
};

/* static */
Resources::Resources(ID3D11Device* device)
    : m_impl(std::make_shared<Impl>())
{
    m_impl->Initialize(device);
}

void Resources::SetBrdfLut(ID3D11ShaderResourceView* brdfLut)
{
    m_impl->Resources.BrdfLut = brdfLut;
}

void Resources::CreateDeviceDependentResources(ID3D11Device* device)
{
    m_impl->Initialize(device);
}

void Resources::ReleaseDeviceDependentResources()
{
    m_impl->Resources = {};
}

ComPtr<ID3D11Device> Resources::GetDevice() const
{
    ComPtr<ID3D11Device> device;
    m_impl->Resources.ConstantBuffer->GetDevice(&device);
    return device;
}

void Resources::SetLight(const vec4& direction, const vec4& diffuseColor)
{
    m_impl->SceneBuffer.Set([&](SceneConstantBuffer& sceneBuffer) {
        XMStoreFloat3(&sceneBuffer.LightDirection, direction);
        XMStoreFloat3(&sceneBuffer.LightDiffuseColor, diffuseColor);
    });
}

void Resources::SetViewProjection(const mat4& viewLeft, const mat4& viewRight, const mat4& projectionLeft, const mat4& projectionRight)
{
    m_impl->SceneBuffer.Set([&](SceneConstantBuffer& sceneBuffer) {
        StoreMatrix(&sceneBuffer.ViewProjection[0], XMMatrixTranspose(MultiplyMatrix(viewLeft, projectionLeft)));
        StoreMatrix(&sceneBuffer.ViewProjection[1], XMMatrixTranspose(MultiplyMatrix(viewRight, projectionRight)));
        XMStoreFloat4(&sceneBuffer.Eyeposition[0], XMMatrixInverse(nullptr, viewLeft).r[3]);
        XMStoreFloat4(&sceneBuffer.Eyeposition[1], XMMatrixInverse(nullptr, viewRight).r[3]);
    });
}

void Resources::SetEnvironmentMap(ID3D11DeviceContext3* context, ID3D11ShaderResourceView* specularEnvironmentMap, ID3D11ShaderResourceView* diffuseEnvironmentMap)
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc;
    diffuseEnvironmentMap->GetDesc(&desc);
    if (desc.ViewDimension != D3D_SRV_DIMENSION_TEXTURECUBE)
    {
        throw std::exception("Diffuse Resource View Type is not D3D_SRV_DIMENSION_TEXTURECUBE");
    }

    specularEnvironmentMap->GetDesc(&desc);
    if (desc.ViewDimension != D3D_SRV_DIMENSION_TEXTURECUBE)
    {
        throw std::exception("Specular Resource View Type is not D3D_SRV_DIMENSION_TEXTURECUBE");
    }
    
    m_impl->SceneBuffer.Set([&](SceneConstantBuffer& sceneBuffer) {
        sceneBuffer.NumSpecularMipLevels = desc.TextureCube.MipLevels;
    });
    m_impl->Resources.SpecularEnvironmentMap = specularEnvironmentMap;
    m_impl->Resources.DiffuseEnvironmentMap = diffuseEnvironmentMap;
}

ComPtr<ID3D11ShaderResourceView> Resources::CreateSolidColorTexture(Cvec4 color) const
{
    const FixedArray<byte, 4> rgba = Texture::CreateRGBA(color);

    // Check cache to see if this flat texture already exists.
    const uint32 colorKey = *reinterpret_cast<const uint32*>(rgba.data());
    auto textureIt = m_impl->Resources.SolidColorTextureCache.find(colorKey);
    if (textureIt != m_impl->Resources.SolidColorTextureCache.end())
    {
        return textureIt->second;
    }

    ComPtr<ID3D11ShaderResourceView> texture = Pbr::Texture::CreateTexture(GetDevice().Get(), rgba.data(), 1, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM);
    m_impl->Resources.SolidColorTextureCache.insert(std::make_pair(colorKey, texture));
    return texture;
}

void Resources::Bind(ID3D11DeviceContext3* context) const
{
    // If the constant buffer parameters changed, update the D3D constant buffer.
    if (m_impl->SceneBuffer.UpdateChangeCountBookmark(&m_impl->SceneChangeCountBookmark))
    {
        context->UpdateSubresource(m_impl->Resources.ConstantBuffer.Get(), 0, nullptr, &m_impl->SceneBuffer, 0, 0);
    }

    context->VSSetShader(m_impl->Resources.VertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_impl->Resources.PixelShader.Get(), nullptr, 0);
    context->GSSetShader(m_impl->Resources.GeometryShader.Get(), nullptr, 0);

    ID3D11Buffer* buffers[] = { m_impl->Resources.ConstantBuffer.Get() };
    context->VSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Scene, _countof(buffers), buffers);
    context->PSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Scene, _countof(buffers), buffers);
    context->IASetInputLayout(m_impl->Resources.InputLayout.Get());

    static_assert(ShaderSlots::DiffuseTexture == ShaderSlots::SpecularTexture + 1, "Diffuse must follow Specular slot");
    static_assert(ShaderSlots::SpecularTexture == ShaderSlots::Brdf + 1, "Specular must follow BRDF slot");
    ID3D11ShaderResourceView* shaderResources[] = { m_impl->Resources.BrdfLut.Get(), m_impl->Resources.SpecularEnvironmentMap.Get(), m_impl->Resources.DiffuseEnvironmentMap.Get() };
    context->PSSetShaderResources(Pbr::ShaderSlots::Brdf, _countof(shaderResources), shaderResources);
    ID3D11SamplerState* samplers[] = { m_impl->Resources.BrdfSampler.Get(), m_impl->Resources.EnvironmentMapSampler.Get() };
    context->PSSetSamplers(ShaderSlots::Brdf, _countof(samplers), samplers);
}

}


NAMESPACE_TOPSIDE_END
