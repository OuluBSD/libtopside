#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace Pbr {

// A Material contains the metallic roughness parameters and textures.
// Primitives specify which Material to use when being rendered.
struct Material
{
    // Coefficients used by the shader. Each texture is sampled and multiplied by these coefficients.
    struct ConstantBufferData
    {
        alignas(16) // packoffset(c0)
        vec4 base_clr_factor{ 1, 1, 1, 1 };
        alignas(16) // packoffset(c1.x and c1.y)
        float metallic_factor{ 1 };
        float roughness_factor{ 1 };
        alignas(16) // packoffset(c2)
        vec3 emissive_factor{ 1, 1, 1 };
        alignas(16) // packoffset(c3.x and c3.y)
        float normal_scale{ 1 };
        float occlusion_strength{ 1 };
    };

    static_assert((sizeof(ConstantBufferData) % 16) == 0, "Constant Buffer must be divisible by 16 bytes");

    // Create a uninitialized material. Textures and shader coefficients must be set.
    Material(Pbr::Resources const& pbr_res);

    // Create a clone of this material.
    Shared<Material> Clone(Pbr::Resources const& pbr_res) const;

    // Create a flat (no texture) material.
    static Shared<Material> CreateFlat(
        const Resources& pbr_res,
        const vec4& base_color_factor,
        float roughness_factor = 1.0f,
        float metallic_factor = 0.0f,
        const vec4& emissive_factor = DirectX::Colors::Black);

    // Set a Metallic-Roughness texture.
    void SetTexture(ShaderSlots::PSMaterial slot, ID3D11ShaderResourceView* tex_view, ID3D11SamplerState* sampler=0);

    // Bind this material to current context.
    void Bind(ID3D11DeviceContext3* context) const;

    String name;
    TrackChanges<ConstantBufferData> parameters;
    bool hidden{ false };

private:
    ComPtr<ID3D11BlendState> blend_state;
    FixedArray<ComPtr<ID3D11ShaderResourceView>, ShaderSlots::LastMaterialSlot + 1> textures;
    FixedArray<ComPtr<ID3D11SamplerState>, ShaderSlots::LastMaterialSlot + 1> samplers;
    ComPtr<ID3D11Buffer> constant_buffer;
    mutable uint32 constant_buffer_bookmark{ (uint32)-1 };
};

}

NAMESPACE_PARALLEL_END

