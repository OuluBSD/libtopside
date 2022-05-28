#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr {

// Global PBR resources required for rendering a scene.
struct Resources : RTTIBase
{
	RTTI_DECL0(Resources)
	
	/*using DataState = DataState;
	using NativeDeviceRef = typename Gfx::NativeDeviceRef;
	using ShaderResources& = typename Gfx::ShaderResources&;
	using GfxContext& = typename Gfx::GfxContext&;
	using SamplerState& = typename Gfx::SamplerState&;
	using NativeInputLayoutRef = typename Gfx::NativeInputLayoutRef;
	using NativeVertexShaderRef = typename Gfx::NativeVertexShaderRef;
	using NativeGeometryShaderRef = typename Gfx::NativeGeometryShaderRef;
	using NativePixelShaderRef = typename Gfx::NativePixelShaderRef;
	using NativeBufferRef = typename Gfx::NativeBufferRef;
	*/
	
	Resources(){}
    explicit Resources(GfxDevice& dev);
	
 /*	// Sets the Bidirectional Reflectance Distribution Function Lookup Table texture, required by the shader to compute surface reflectance from the IBL.
    void SetBrdfLut(ShaderResources& brdf_lut);
	
    // Create device-dependent resources.
    void CreateDeviceDependentResources(NativeDeviceRef device);

    // Release device-dependent resources.
    void ReleaseDeviceDependentResources();

    // Get the D3D11Device that the PBR resources are associated with.
    NativeDeviceRef GetDevice() const;
*/
    // Set the directional light.
    void SetLight(const vec4& direction, const vec4& diffuse_color);

    // Set the specular and diffuse image-based lighting (IBL) maps. ShaderResourceViews must be TextureCubes.
    //void SetEnvironmentMap(GfxContext& context, ShaderResources& specular_env_map, ShaderResources& diffuse_env_map);

    // Set the current view and projection matrices.
    void SetViewProjection(const mat4& view_left, const mat4& view_right, const mat4& proj_left, const mat4& proj_right);

    // Many 1x1 pixel colored textures are used in the PBR system. This is used to create textures backed by a cache to reduce the number of textures created.
    Texture& CreateSolidColorTexture(const vec4& color) const;

    // Bind the the PBR resources to the current context.
    /*void Bind(GfxContext& context) const;
	
	
	
	static Resources& Local() {static Resources r; return r;}*/
	
	Pbr::Material& AddMaterial();
	Pbr::SamplerState& AddSampler();
	Pbr::Texture& AddTexture();
	
private:
    //struct Impl;
    //One<Impl> impl;
    
    Array<Material> materials;
    Array<SamplerState> samplers;
    Array<Texture> textures;
    
    
public:
	
	struct SceneConstantBuffer
	{
	    alignas(16) mat4 view_proj[2];
	    alignas(16) vec4 eye_pos[2];
	    alignas(16) vec3 light_dir{};
	    alignas(16) vec3 light_diffuse_clr{};
	    alignas(16) int specular_mip_level_count{ 1 };
	};

    struct DeviceResources
    {
        SamplerState		brdf_sampler;
        SamplerState		env_map_sampler;
        InputLayout			input_layout;
        VertexShader		vtx_shader;
        GeometryShader		geom_shader;
        PixelShader			pixel_shader;
        DataBuffer			constant_buffer;
        Texture				brdf_lut;
        Texture				specular_env_map;
        Texture				diffuse_env_map;
        
        mutable ArrayMap<RGBA, Texture> solid_clr_tex_cache;
    };

    DeviceResources						resources;
    TrackChanges<SceneConstantBuffer>	scene_buffer;
    uint32								scene_change_count_bookmark { 0 };
    
};

}


NAMESPACE_TOPSIDE_END
