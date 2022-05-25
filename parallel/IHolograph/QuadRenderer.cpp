#include "WinLib.h"


NAMESPACE_PARALLEL_BEGIN


struct QuadModelConstantBuffer
{
    mat4 model;
};

struct QuadRenderingParametersConstantBuffer
{
    mat4 viewProj[2];
};


// Assert that the constant buffer remains 16-byte aligned (best practice).
static_assert((sizeof(QuadModelConstantBuffer) % (sizeof(float) * 4)) == 0, "Model constant buffer size must be 16-byte aligned (16 bytes is the length of four floats).");


struct VertexPositionTex
{
    vec3 pos;
    vec2 tex;
};

// Loads vertex and pixel shaders from files and instantiates the quad geometry.
QuadRenderer::QuadRenderer(Shared<GfxDevResources> deviceResources) :
    dev_res(std::move(deviceResources))
{
    CreateDeviceDependentResources();
}

void QuadRenderer::Bind()
{
    const auto context = dev_res->GetD3DDeviceContext();

    const uint32 strides[] = { sizeof(VertexPositionTex) };
    const uint32 offsets[] = { 0 };

    context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), strides, offsets);
    context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(m_inputLayout.Get());

    context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    context->VSSetConstantBuffers(0, 1, m_modelConstantBuffer.GetAddressOf());
    context->VSSetConstantBuffers(1, 1, m_renderingConstantBuffer.GetAddressOf());

    if (!dev_res->GetDeviceSupportsVprt())
    {
        // On devices that do not support the D3D11_FEATURE_D3D11_OPTIONS3::
        // VPAndRTArrayIndexFromAnyShaderFeedingRasterizer optional feature,
        // a pass-through geometry shader sets the render target ID.
        context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
    }

    context->PSSetShader(m_pixelShaderRGB.Get(), nullptr, 0);
    context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
}

void QuadRenderer::Render(mat4 const& matrix, ID3D11ShaderResourceView* texture)
{
    const auto context = dev_res->GetD3DDeviceContext();

    QuadModelConstantBuffer cb;
    cb.model = transpose(matrix);

    context->UpdateSubresource(m_modelConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);

    context->PSSetShaderResources(0, 1, &texture);

    context->DrawIndexedInstanced(m_indexCount, 2, 0, 0, 0);
}

void QuadRenderer::Unbind()
{}

void QuadRenderer::SetViewProjection(
    const float4x4& worldToViewLeft,
    const float4x4& viewToProjLeft,
    const float4x4& worldToViewRight,
    const float4x4& viewToProjRight)
{
    float4x4 viewProjection[2];

    viewProjection[0] = transpose(worldToViewLeft * viewToProjLeft);
    viewProjection[1] = transpose(worldToViewRight * viewToProjRight);

    dev_res->GetD3DDeviceContext()->UpdateSubresource(m_renderingConstantBuffer.Get(), 0, nullptr, &viewProjection, 0, 0);
}

void QuadRenderer::CreateDeviceDependentResources()
{
    const bool usingVprt = dev_res->GetDeviceSupportsVprt();
    const void* vertexShader = (usingVprt) ? g_QuadVPRTVertexShader : g_QuadVertexShader;
    const size_t vertexShaderSize = (usingVprt) ? _countof(g_QuadVPRTVertexShader) : _countof(g_QuadVertexShader);

    DirectX::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateVertexShader(
            vertexShader,
            vertexShaderSize,
            nullptr,
            &m_vertexShader
        )
    );

    constexpr std::array<D3D11_INPUT_ELEMENT_DESC, 2> vertexDesc = {{
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    }};

    DirectX::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateInputLayout(
            vertexDesc.data(),
            static_cast<UINT>(vertexDesc.size()),
            vertexShader,
            vertexShaderSize,
            &m_inputLayout
        )
    );

    DirectX::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreatePixelShader(
            g_QuadPixelShaderRGB,
            _countof(g_QuadPixelShaderRGB),
            nullptr,
            &m_pixelShaderRGB
        )
    );

    if (!usingVprt)
    {
        DirectX::ThrowIfFailed(
            dev_res->GetD3DDevice()->CreateGeometryShader(
                g_QuadGeometryShader,
                _countof(g_QuadGeometryShader),
                nullptr,
                &m_geometryShader
            )
        );
    }

    static const std::array<VertexPositionTex, 4> quadVertices = {{
        { float3(-0.5f, +0.5f, +0.0f), float2(+0.0f, +0.0f) },
        { float3(+0.5f, +0.5f, +0.0f), float2(+1.0f, +0.0f) },
        { float3(+0.5f, -0.5f, +0.0f), float2(+1.0f, +1.0f) },
        { float3(-0.5f, -0.5f, +0.0f), float2(+0.0f, +1.0f) },
    }};

    const D3D11_SUBRESOURCE_DATA vertexBufferData = { quadVertices.data() };

    const CD3D11_BUFFER_DESC vertexBufferDesc{
        static_cast<UINT>(sizeof(VertexPositionTex) * quadVertices.size()),
        D3D11_BIND_VERTEX_BUFFER
    };

    DirectX::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateBuffer(
            &vertexBufferDesc,
            &vertexBufferData,
            &m_vertexBuffer
        )
    );

    constexpr std::array<uint16, 12> quadIndices = {{
        // -z
        0,2,3,
        0,1,2,

        // +z
        2,0,3,
        1,0,2,
    }};

    m_indexCount = static_cast<uint32_t>(quadIndices.size());

    const D3D11_SUBRESOURCE_DATA indexBufferData = { quadIndices.data() };

    const CD3D11_BUFFER_DESC indexBufferDesc{
        static_cast<UINT>(sizeof(uint16) * quadIndices.size()),
        D3D11_BIND_INDEX_BUFFER
    };
    DirectX::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateBuffer(
            &indexBufferDesc,
            &indexBufferData,
            &m_indexBuffer
        )
    );

    const D3D11_SAMPLER_DESC desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());

    DirectX::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateSamplerState(
            &desc,
            &m_samplerState
        )
    );
    {
        const CD3D11_BUFFER_DESC constantBufferDesc{
            sizeof(QuadModelConstantBuffer),
            D3D11_BIND_CONSTANT_BUFFER
        };

        DirectX::ThrowIfFailed(
            dev_res->GetD3DDevice()->CreateBuffer(
                &constantBufferDesc,
                nullptr,
                &m_modelConstantBuffer
            )
        );
    }
    {
        const CD3D11_BUFFER_DESC constantBufferDesc{
            sizeof(float4x4) * 2,
            D3D11_BIND_CONSTANT_BUFFER
        };

        DirectX::ThrowIfFailed(
            dev_res->GetD3DDevice()->CreateBuffer(
                &constantBufferDesc,
                nullptr,
                &m_renderingConstantBuffer
            )
        );
    }
}

void QuadRenderer::ReleaseDeviceDependentResources()
{
    m_vertexShader.Reset();
    m_inputLayout.Reset();
    m_pixelShaderRGB.Reset();
    m_geometryShader.Reset();

    m_modelConstantBuffer.Reset();
    m_renderingConstantBuffer.Reset();

    m_vertexBuffer.Reset();
    m_indexBuffer.Reset();

    m_samplerState.Reset();
}


NAMESPACE_PARALLEL_END
