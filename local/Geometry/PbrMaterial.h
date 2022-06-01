#if 0
#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr {
	
struct Resources;

// A Material contains the metallic roughness parameters and textures.
// Primitives specify which Material to use when being rendered.

struct Material
{
	/*using Resources = Resources;
	using ShaderResources& = typename Gfx::ShaderResources&;
	using SamplerState& = typename Gfx::SamplerState&;
	using GfxContext& = typename Gfx::GfxContext&;
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
    Material();
    //Material(const Resources& pbr_res);

    // Create a clone of this material.
    Shared<Material> Copy(const Resources& pbr_res) const;

    // Create a flat (no texture) material.
    void SetFlat(
        const vec4&			base_color_factor,
        float				roughness_factor = 1.0f,
        float				metallic_factor = 0.0f,
        const vec4&			emissive_factor = vec4{0,0,0,1});

    // Set a Metallic-Roughness texture.
    void SetTexture(ShaderSlots::PSMaterial slot, Texture& tex_view);

    // Bind this material to current context.
    //void Bind(GfxContext& context) const;
	
	
	void IncRef();
	void DecRef();
	
    String								name;
    TrackChanges<ConstantBufferData>	parameters;
    bool								hidden { false };

protected:
	friend class Resources;
	friend class Model;
	Resources* res = 0;
	int refs = 0;
	
private:
	static const int C = ShaderSlots::LastMaterialSlot + 1;
    FixedArray<Texture*, C>				textures;
    FixedArray<const SamplerState*, C>	samplers;
    BlendState							blend_state;
    DataBuffer							constant_buffer;
    mutable uint32						constant_buffer_bookmark{ (uint32)-1 };
    
    
};

}

NAMESPACE_TOPSIDE_END


#endif
