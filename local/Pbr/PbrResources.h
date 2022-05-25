#pragma once


NAMESPACE_TOPSIDE_BEGIN


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
struct Resources
{
	using DataState = DataStateT<Gfx>;
	
    explicit Resources(ID3D11Device* d3dDevice);

    // Sets the Bidirectional Reflectance Distribution Function Lookup Table texture, required by the shader to compute surface reflectance from the IBL.
    void SetBrdfLut(ID3D11ShaderResourceView* brdf_lut);

    // Create device-dependent resources.
    void CreateDeviceDependentResources(ID3D11Device* device);

    // Release device-dependent resources.
    void ReleaseDeviceDependentResources();

    // Get the D3D11Device that the PBR resources are associated with.
    ComPtr<ID3D11Device> GetDevice() const;

    // Set the directional light.
    void SetLight(const vec4& direction, const vec4& diffuse_color);

    // Set the specular and diffuse image-based lighting (IBL) maps. ShaderResourceViews must be TextureCubes.
    void SetEnvironmentMap(ID3D11DeviceContext3* context, ID3D11ShaderResourceView* specular_env_map, ID3D11ShaderResourceView* diffuse_env_map);

    // Set the current view and projection matrices.
    void SetViewProjection(const mat4& view_left, const mat4& view_right, const mat4& proj_left, const mat4& proj_right);

    // Many 1x1 pixel colored textures are used in the PBR system. This is used to create textures backed by a cache to reduce the number of textures created.
    ComPtr<ID3D11ShaderResourceView> CreateSolidColorTexture(const vec4& color) const;

    // Bind the the PBR resources to the current context.
    void Bind(ID3D11DeviceContext3* context) const;

private:
    struct Impl;
    Shared<Impl> impl;
};

}


NAMESPACE_TOPSIDE_END
