#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr
{


Material::Material() {
	
}

#if 0
Material::Material(Resources const& pbr_res)
{
	TODO
	
    /*const CD3D11_BUFFER_DESC constant_buffer_desc(sizeof(ConstantBufferData), D3D11_BIND_CONSTANT_BUFFER);
    Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateBuffer(&constant_buffer_desc, nullptr, &constant_buffer));

    D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc;
    rtBlendDesc.BlendEnable = TRUE;
    rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ZERO;
    rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
    rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    CD3D11_BLEND_DESC blend_state_desc(D3D11_DEFAULT);
    for (UINT i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        blend_state_desc.RenderTarget[i] = rtBlendDesc;
    }

    Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateBlendState(&blend_state_desc, &blend_state));*/
}
#endif



/*Shared<Material> Material::Copy(const Resources& pbr_res) const
{
    auto clone = MakeShared<Material>(pbr_res);
    clone->name = name;
    clone->parameters = parameters;
    clone->hidden = hidden;
    clone->textures = textures;
    clone->samplers = samplers;
    return clone;
}*/


void Material::SetFlat(const vec4& base_color_factor, float roughness_factor /* = 1.0f */, float metallic_factor /* = 0.0f */, const vec4& emissive_factor /* = XMFLOAT3(0, 0, 0) */)
{
    parameters.Set([&](Pbr::Material::ConstantBufferData& data) {
        StoreVec4(&data.base_clr_factor, base_color_factor);
        StoreVec3(&data.emissive_factor, emissive_factor);
        data.metallic_factor = metallic_factor;
        data.roughness_factor = roughness_factor;
    });
	
	ASSERT(res);
	
    SetTexture(ShaderSlots::BaseColor,			res->CreateSolidColorTexture(vec4{ 1, 1, 1, 1 }));
    SetTexture(ShaderSlots::MetallicRoughness,	res->CreateSolidColorTexture(vec4{ 1, 1, 1, 1 }));
    SetTexture(ShaderSlots::Occlusion,			res->CreateSolidColorTexture(vec4{ 1, 1, 1, 1 })); // No occlusion.
    SetTexture(ShaderSlots::Normal,				res->CreateSolidColorTexture(vec4{ 0.5f, 0.5f, 1, 1 })); // Flat normal.
    SetTexture(ShaderSlots::Emissive,			res->CreateSolidColorTexture(vec4{ 1, 1, 1, 1 }));
	
}

void Material::SetTexture(ShaderSlots::PSMaterial slot, Texture& tex_view)
{
    textures[slot] = &tex_view;
    //samplers[slot] = &sampler;
}

void Material::IncRef() {
	refs++;
}

void Material::DecRef() {
	refs--;
	if (refs <= 0 && res)
		res->RemoveMaterial(this);
}

/*void Material::Bind(GfxContext& context) const
{
    // If the parameters of the constant buffer have changed, update the constant buffer.
    if (parameters.UpdateChangeCountBookmark(&constant_buffer_bookmark))
    {
        context->UpdateSubresource(constant_buffer.Get(), 0, nullptr, &parameters.Get(), 0, 0);
    }

    context->OMSetBlendState(blend_state.Get(), nullptr, 0xFFFFFF);

    NativeBufferRef constant_buf[] = { constant_buffer.Get() };
    context->PSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Material, 1, constant_buf);

    static_assert(Pbr::ShaderSlots::BaseColor == 0, "BaseColor must be the first slot");
    
    context->PSSetShaderResources(Pbr::ShaderSlots::BaseColor, (uint32)textures.GetCount(), textures[0].GetAddressOf());
    context->PSSetSamplers(Pbr::ShaderSlots::BaseColor, (uint32)samplers.GetCount(), samplers[0].GetAddressOf());
}*/

}

NAMESPACE_TOPSIDE_END

