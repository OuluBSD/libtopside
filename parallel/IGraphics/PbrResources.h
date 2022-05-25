#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace Pbr {

namespace ShaderSlots {

enum VSResourceViews
{
    Transforms = 0,
};

enum PSMaterial // For both samplers and textures.
{
    BaseColor = 0,
    MetallicRoughness,
    Normal,
    Occlusion,
    Emissive,
    
    LastMaterialSlot = Emissive
};

enum Pbr // For both samplers and textures.
{
    Brdf = LastMaterialSlot + 1
};

enum EnvironmentMap // For both samplers and textures.
{
    SpecularTexture = Brdf + 1,
    DiffuseTexture = SpecularTexture + 1,
    env_map_sampler = Brdf + 1
};

enum ConstantBuffers
{
    Scene,          // Used by VS and PS
    Material,       // PS only
};

}

// Global PBR resources required for rendering a scene.
template <class Gfx>
struct ResourcesT
{
	using DataState = DataStateT<Gfx>;
	using NativeDeviceRef = typename Gfx::NativeDeviceRef;
	using NativeShaderResourcesRef = typename Gfx::NativeShaderResourcesRef;
	using NativeDeviceContextRef = typename Gfx::NativeDeviceContextRef;
	using NativeSamplerStateRef = typename Gfx::NativeSamplerStateRef;
	using NativeInputLayoutRef = typename Gfx::NativeInputLayoutRef;
	using NativeVertexShaderRef = typename Gfx::NativeVertexShaderRef;
	using NativeGeometryShaderRef = typename Gfx::NativeGeometryShaderRef;
	using NativePixelShaderRef = typename Gfx::NativePixelShaderRef;
	using NativeBufferRef = typename Gfx::NativeBufferRef;
	
    explicit ResourcesT(NativeDeviceRef d3dDevice);
	
    // Sets the Bidirectional Reflectance Distribution Function Lookup Table texture, required by the shader to compute surface reflectance from the IBL.
    void SetBrdfLut(NativeShaderResourcesRef brdf_lut);
	
    // Create device-dependent resources.
    void CreateDeviceDependentResources(NativeDeviceRef device);

    // Release device-dependent resources.
    void ReleaseDeviceDependentResources();

    // Get the D3D11Device that the PBR resources are associated with.
    NativeDeviceRef GetDevice() const;

    // Set the directional light.
    void SetLight(const vec4& direction, const vec4& diffuse_color);

    // Set the specular and diffuse image-based lighting (IBL) maps. ShaderResourceViews must be TextureCubes.
    void SetEnvironmentMap(NativeDeviceContextRef context, NativeShaderResourcesRef specular_env_map, NativeShaderResourcesRef diffuse_env_map);

    // Set the current view and projection matrices.
    void SetViewProjection(const mat4& view_left, const mat4& view_right, const mat4& proj_left, const mat4& proj_right);

    // Many 1x1 pixel colored textures are used in the PBR system. This is used to create textures backed by a cache to reduce the number of textures created.
    NativeShaderResourcesRef CreateSolidColorTexture(const vec4& color) const;

    // Bind the the PBR resources to the current context.
    void Bind(NativeDeviceContextRef context) const;

private:
    struct Impl;
    Shared<Impl> impl;
    
    
};

}


NAMESPACE_PARALLEL_END
