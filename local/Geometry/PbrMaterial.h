#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace Pbr {

// A Material contains the metallic roughness parameters and textures.
// Primitives specify which Material to use when being rendered.

struct Material
{
	/*using Resources = Resources<Gfx>;
	using NativeShaderResourcesRef = typename Gfx::NativeShaderResourcesRef;
	using NativeSamplerStateRef = typename Gfx::NativeSamplerStateRef;
	using NativeDeviceContextRef = typename Gfx::NativeDeviceContextRef;
	using NativeBlendStateRef = typename Gfx::NativeBlendStateRef;
	using NativeBufferRef = typename Gfx::NativeBufferRef;*/
	
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
    Material(const Resources& pbr_res);

    // Create a clone of this material.
    Shared<Material> Clone(const Resources& pbr_res) const;

    // Create a flat (no texture) material.
    static Shared<Material> CreateFlat(
        const Resources&	pbr_res,
        const vec4&			base_color_factor,
        float				roughness_factor = 1.0f,
        float				metallic_factor = 0.0f,
        const vec4&			emissive_factor = vec4{0,0,0,1});

    // Set a Metallic-Roughness texture.
    void SetTexture(ShaderSlots::PSMaterial slot, NativeShaderResourcesRef tex_view, NativeSamplerStateRef sampler=0);

    // Bind this material to current context.
    void Bind(NativeDeviceContextRef context) const;

    String								name;
    TrackChanges<ConstantBufferData>	parameters;
    bool								hidden { false };

private:
    FixedArray<NativeShaderResourcesRef, ShaderSlots::LastMaterialSlot + 1>		textures;
    FixedArray<NativeSamplerStateRef, ShaderSlots::LastMaterialSlot + 1>		samplers;
    NativeBlendStateRef					blend_state;
    NativeBufferRef						constant_buffer;
    mutable uint32						constant_buffer_bookmark{ (uint32)-1 };
    
    
};

}

NAMESPACE_PARALLEL_END

