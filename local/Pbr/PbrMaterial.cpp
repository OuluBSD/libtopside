#include "Pbr.h"


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr
{
Material::Material(Pbr::Resources const& pbr_res)
{
    const CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ConstantBufferData), D3D11_BIND_CONSTANT_BUFFER);
    Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, &constant_buffer));

    D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc;
    rtBlendDesc.BlendEnable = TRUE;
    rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ZERO;
    rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
    rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    CD3D11_BLEND_DESC blendStateDesc(D3D11_DEFAULT);
    for (UINT i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        blendStateDesc.RenderTarget[i] = rtBlendDesc;
    }

    Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateBlendState(&blendStateDesc, &blend_state));
}

Shared<Material> Material::Clone(Pbr::Resources const& pbr_res) const
{
    auto clone = std::make_shared<Material>(pbr_res);
    clone->name = Name;
    clone->parameters = parameters;
    clone->hidden = hidden;
    clone->textures = textures;
    clone->samplers = samplers;
    return clone;
}

/* static */
Shared<Material> Material::CreateFlat(const Resources& pbr_res, Cvec4 base_color_factor, float roughness_factor /* = 1.0f */, float metallic_factor /* = 0.0f */, Cvec4 emissive_factor /* = XMFLOAT3(0, 0, 0) */)
{
    Shared<Material> material = std::make_shared<Material>(pbr_res);

    material->parameters.Set([&](Pbr::Material::ConstantBufferData& data) {
        XMStoreFloat4(&data.base_clr_factor, base_color_factor);
        XMStoreFloat3(&data.emissive_factor, emissive_factor);
        data.metallic_factor = metallic_factor;
        data.roughness_factor = roughness_factor;
    });

    const ComPtr<ID3D11SamplerState> defaultSampler = Pbr::Texture::CreateSampler(pbr_res.GetDevice().Get());
    material->SetTexture(ShaderSlots::BaseColor, pbr_res.CreateSolidColorTexture(vec4loader{ 1, 1, 1, 1 }).Get(), defaultSampler.Get());
    material->SetTexture(ShaderSlots::MetallicRoughness, pbr_res.CreateSolidColorTexture(vec4loader{ 1, 1, 1, 1 }).Get(), defaultSampler.Get());
    material->SetTexture(ShaderSlots::Occlusion, pbr_res.CreateSolidColorTexture(vec4loader{ 1, 1, 1, 1 }).Get(), defaultSampler.Get()); // No occlusion.
    material->SetTexture(ShaderSlots::normal, pbr_res.CreateSolidColorTexture(vec4loader{ 0.5f, 0.5f, 1, 1 }).Get(), defaultSampler.Get()); // Flat normal.
    material->SetTexture(ShaderSlots::Emissive, pbr_res.CreateSolidColorTexture(vec4loader{ 1, 1, 1, 1 }).Get(), defaultSampler.Get());

    return material;
}

void Material::SetTexture(ShaderSlots::PSMaterial slot, ID3D11ShaderResourceView* tex_view, _In_opt_ ID3D11SamplerState* sampler)
{
    textures[slot] = tex_view;
    samplers[slot] = sampler;
}

void Material::Bind(ID3D11DeviceContext3* context) const
{
    // If the parameters of the constant buffer have changed, update the constant buffer.
    if (parameters.UpdateChangeCountBookmark(&constant_buffer_bookmark))
    {
        context->UpdateSubresource(constant_buffer.Get(), 0, nullptr, &parameters.Get(), 0, 0);
    }

    context->OMSetBlendState(blend_state.Get(), nullptr, 0xFFFFFF);

    ID3D11Buffer* psConstantBuffers[] = { constant_buffer.Get() };
    context->PSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Material, 1, psConstantBuffers);

    static_assert(Pbr::ShaderSlots::BaseColor == 0, "BaseColor must be the first slot");
    context->PSSetShaderResources(Pbr::ShaderSlots::BaseColor, (uint32)textures.size(), textures[0].GetAddressOf());
    context->PSSetSamplers(Pbr::ShaderSlots::BaseColor, (uint32)samplers.size(), samplers[0].GetAddressOf());
}

}

NAMESPACE_TOPSIDE_END

