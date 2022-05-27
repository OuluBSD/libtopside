#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


struct SceneConstantBuffer
{
    alignas(16) mat4 view_proj[2];
    alignas(16) vec4 eye_pos[2];
    alignas(16) vec3 light_dir{};
    alignas(16) vec3 light_diffuse_clr{};
    alignas(16) int specular_mip_level_count{ 1 };
};



namespace Pbr {

template <class Gfx>
struct ResourcesT<Gfx>::Impl
{
    void Initialize(NativeDeviceRef device)
    {
        TODO
    
    	/*
		// Set up pixel shader.
        Internal::ThrowIfFailed(device->CreatePixelShader(g_psPbrMain, sizeof(g_psPbrMain), nullptr, &resources.PixelShader));

        // Check for device support for the optional feature that allows setting the render target array index from the vertex shader stage.
        D3D11_FEATURE_DATA_D3D11_OPTIONS3 options{};
        device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS3, &options, sizeof(options));
        if (options.VPAndRTArrayIndexFromAnyShaderFeedingRasterizer)
        {
            // Set up vertex shader with VPRT support.
            Internal::ThrowIfFailed(device->CreateInputLayout(Pbr::Vertex::vtx_desc, ARRAYSIZE(Pbr::Vertex::vtx_desc), g_vsPbrVprtMain, sizeof(g_vsPbrVprtMain), &resources.input_layout));
            Internal::ThrowIfFailed(device->CreateVertexShader(g_vsPbrVprtMain, sizeof(g_vsPbrVprtMain), nullptr, &resources.VertexShader));
        }
        else
        {
            // Set up vertex shader with geometry shader due to no VPRT support.
            Internal::ThrowIfFailed(device->CreateInputLayout(Pbr::Vertex::vtx_desc, ARRAYSIZE(Pbr::Vertex::vtx_desc), g_vsPbrNoVprtMain, sizeof(g_vsPbrNoVprtMain), &resources.input_layout));
            Internal::ThrowIfFailed(device->CreateVertexShader(g_vsPbrNoVprtMain, sizeof(g_vsPbrNoVprtMain), nullptr, &resources.VertexShader));
            Internal::ThrowIfFailed(device->CreateGeometryShader(g_gsPbrNoVprtMain, sizeof(g_gsPbrNoVprtMain), nullptr, &resources.GeometryShader));
        }

        // Set up the constant buffers.
        static_assert((sizeof(SceneConstantBuffer) % 16) == 0, "Constant Buffer must be divisible by 16 bytes");
        const CD3D11_BUFFER_DESC pbr_constant_buffer_desc(sizeof(SceneConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
        Internal::ThrowIfFailed(device->CreateBuffer(&pbr_constant_buffer_desc, nullptr, &resources.ConstantBuffer));

        // Samplers for environment map and BRDF.
        resources.env_map_sampler = Texture::CreateSampler(device);
        resources.brdf_sampler = Texture::CreateSampler(device);*/
    }

    struct DeviceResources
    {
        NativeSamplerStateRef			brdf_sampler;
        NativeSamplerStateRef			env_map_sampler;
        NativeInputLayoutRef			input_layout;
        NativeVertexShaderRef			vtx_shader;
        NativeGeometryShaderRef			geom_shader;
        NativePixelShaderRef			pixel_shader;
        NativeBufferRef					constant_buffer;
        NativeShaderResourcesRef		brdf_lut;
        NativeShaderResourcesRef		specular_env_map;
        NativeShaderResourcesRef		diffuse_env_map;
        
        mutable VectorMap<uint32, NativeShaderResourcesRef> solid_clr_tex_cache;
    };

    DeviceResources						resources;
    TrackChanges<SceneConstantBuffer>	scene_buffer;
    uint32								scene_change_count_bookmark { 0 };
    
};

template <class Gfx>
ResourcesT<Gfx>::ResourcesT(NativeDeviceRef device)
    : impl(MakeShared<Impl>())
{
    impl->Initialize(device);
}

template <class Gfx>
void ResourcesT<Gfx>::SetBrdfLut(NativeShaderResourcesRef brdf_lut)
{
    impl->resources.brdf_lut = brdf_lut;
}

template <class Gfx>
void ResourcesT<Gfx>::CreateDeviceDependentResources(NativeDeviceRef device)
{
    impl->Initialize(device);
}

template <class Gfx>
void ResourcesT<Gfx>::ReleaseDeviceDependentResources()
{
    impl->Resources = {};
}

template <class Gfx>
typename Gfx::NativeDeviceRef
ResourcesT<Gfx>::GetDevice() const
{
    NativeDeviceRef device;
    impl->resources.constant_buffer->GetDevice(&device);
    return device;
}

template <class Gfx>
void ResourcesT<Gfx>::SetLight(const vec4& direction, const vec4& diffuse_color)
{
    impl->scene_buffer.Set([&](SceneConstantBuffer& scene_buffer) {
        StoreVec3(&scene_buffer.light_dir, direction);
        StoreVec3(&scene_buffer.light_diffuse_clr, diffuse_color);
    });
}

template <class Gfx>
void ResourcesT<Gfx>::SetViewProjection(const mat4& view_left, const mat4& view_right, const mat4& proj_left, const mat4& proj_right)
{
    impl->scene_buffer.Set([&](SceneConstantBuffer& scene_buffer) {
        StoreMatrix(&scene_buffer.view_proj[0], MatrixTranspose(MultiplyMatrix(view_left, proj_left)));
        StoreMatrix(&scene_buffer.view_proj[1], MatrixTranspose(MultiplyMatrix(view_right, proj_right)));
        StoreVec4(&scene_buffer.eye_pos[0], MatrixInverse(nullptr, view_left)[3]);
        StoreVec4(&scene_buffer.eye_pos[1], MatrixInverse(nullptr, view_right)[3]);
    });
}

template <class Gfx>
void ResourcesT<Gfx>::SetEnvironmentMap(NativeDeviceContextRef context, NativeShaderResourcesRef specular_env_map, NativeShaderResourcesRef diffuse_env_map)
{
	TODO
	
	/*
    D3D11_SHADER_RESOURCE_VIEW_DESC desc;
    diffuse_env_map->GetDesc(&desc);
    if (desc.view_dimension != D3D_SRV_DIMENSION_TEXTURECUBE)
    {
        throw Exc("Diffuse Resource View Type is not D3D_SRV_DIMENSION_TEXTURECUBE");
    }

    specular_env_map->GetDesc(&desc);
    if (desc.view_dimension != D3D_SRV_DIMENSION_TEXTURECUBE)
    {
        throw Exc("Specular Resource View Type is not D3D_SRV_DIMENSION_TEXTURECUBE");
    }
    
    impl->scene_buffer.Set([&](SceneConstantBuffer& scene_buffer) {
        scene_buffer.specular_mip_level_count = desc.TextureCube.MipLevels;
    });
    impl->resources.specular_env_map = specular_env_map;
    impl->resources.diffuse_env_map = diffuse_env_map;
    */
}

template <class Gfx>
typename Gfx::NativeShaderResourcesRef
ResourcesT<Gfx>::CreateSolidColorTexture(const vec4& color) const
{
	TODO
    /*const RGBA rgba = Texture::CreateRGBA(color);

    // Check cache to see if this flat texture already exists.
    const uint32 color_key = *reinterpret_cast<const uint32*>(rgba.data());
    auto texture_iter = impl->resources.solid_clr_tex_cache.find(color_key);
    if (texture_iter != impl->resources.solid_clr_tex_cache.end())
    {
        return texture_iter->b;
    }

    NativeShaderResourcesRef texture = Pbr::Texture::CreateTexture(GetDevice().Get(), rgba.data(), 1, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM);
    impl->resources.solid_clr_tex_cache.insert(std::make_pair(color_key, texture));
    return texture;*/
}

template <class Gfx>
void ResourcesT<Gfx>::Bind(NativeDeviceContextRef context) const
{
    TODO
	/*
	// If the constant buffer parameters changed, update the D3D constant buffer.
    if (impl->scene_buffer.UpdateChangeCountBookmark(&impl->scene_change_count_bookmark))
    {
        context->UpdateSubresource(impl->resources.constant_buffer.Get(), 0, nullptr, &impl->scene_buffer, 0, 0);
    }

    context->VSSetShader(impl->resources.vtx_shader.Get(), nullptr, 0);
    context->PSSetShader(impl->resources.pixel_shader.Get(), nullptr, 0);
    context->GSSetShader(impl->resources.geom_shader.Get(), nullptr, 0);

    NativeBufferRef buffers[] = { impl->resources.constant_buffer.Get() };
    context->VSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Scene, _countof(buffers), buffers);
    context->PSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Scene, _countof(buffers), buffers);
    context->IASetinput_layout(impl->resources.input_layout.Get());

    static_assert(ShaderSlots::DiffuseTexture == ShaderSlots::SpecularTexture + 1, "Diffuse must follow Specular slot");
    static_assert(ShaderSlots::SpecularTexture == ShaderSlots::Brdf + 1, "Specular must follow BRDF slot");
    
    NativeShaderResourcesRef shader_resources[] = {
		impl->resources.brdf_lut.Get(),
		impl->resources.specular_env_map.Get(),
		impl->Resources.diffuse_env_map.Get()
	};
    context->PSSetShaderResources(Pbr::ShaderSlots::Brdf, _countof(shader_resources), shader_resources);
    
    NativeSamplerStateRef samplers[] = {
		impl->resources.brdf_sampler.Get(),
		impl->resources.env_map_sampler.Get()
	};
    context->PSSetSamplers(ShaderSlots::Brdf, _countof(samplers), samplers);*/
}

}


NAMESPACE_PARALLEL_END