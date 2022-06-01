#if 0
#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN




namespace Pbr {

#if 0
struct Resources::Impl
{
    void Initialize(GfxDevice& device)
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
        SamplerState				brdf_sampler;
        SamplerState				env_map_sampler;
        InputLayout					input_layout;
        VertexShader				vtx_shader;
        GeometryShader				geom_shader;
        PixelShader					pixel_shader;
        DataBuffer					constant_buffer;
        ShaderResources				brdf_lut;
        ShaderResources				specular_env_map;
        ShaderResources				diffuse_env_map;
        
        mutable ArrayMap<uint32, ShaderResources> solid_clr_tex_cache;
    };

    DeviceResources						resources;
    TrackChanges<SceneConstantBuffer>	scene_buffer;
    uint32								scene_change_count_bookmark { 0 };
    
};

Resources::Resources(/*GfxDevice& device*/)
{
	//impl.Create();
    //impl->Initialize(device);
}

#endif

/*void Resources::SetBrdfLut(ShaderResources& brdf_lut)
{
    impl->resources.brdf_lut = brdf_lut;
}


void Resources::CreateDeviceDependentResources(NativeDeviceRef device)
{
    impl->Initialize(device);
}


void Resources::ReleaseDeviceDependentResources()
{
    impl->Resources = {};
}


typename Gfx::NativeDeviceRef
Resources::GetDevice() const
{
    NativeDeviceRef device;
    impl->resources.constant_buffer->GetDevice(&device);
    return device;
}*/


void Resources::SetLight(const vec4& direction, const vec4& diffuse_color)
{
    scene_buffer.Set([&](SceneConstantBuffer& scene_buffer) {
        StoreVec3(&scene_buffer.light_dir, direction);
        StoreVec3(&scene_buffer.light_diffuse_clr, diffuse_color);
    });
}


void Resources::SetViewProjection(const mat4& view_left, const mat4& view_right, const mat4& proj_left, const mat4& proj_right)
{
    scene_buffer.Set([&](SceneConstantBuffer& scene_buffer) {
        StoreMatrix(&scene_buffer.view_proj[0], transpose(MultiplyMatrix(view_left, proj_left)));
        StoreMatrix(&scene_buffer.view_proj[1], transpose(MultiplyMatrix(view_right, proj_right)));
        StoreVec4(&scene_buffer.eye_pos[0], inverse(view_left)[3]);
        StoreVec4(&scene_buffer.eye_pos[1], inverse(view_right)[3]);
    });
}

Pbr::Material& Resources::AddMaterial() {
	Material& m = materials.Add();
	m.res = this;
	return m;
}

Texture& Resources::AddTexture() {
	Texture& t = textures.Add();
	//t.res = this;
	return t;
}

SamplerState& Resources::AddSampler() {
	SamplerState& s = samplers.Add();
	//s.res = this;
	return s;
}

void Resources::RemoveMaterial(Pbr::Material* mat) {
	int i = 0;
	for (Material& m : materials) {
		if (&m == mat) {
			materials.Remove(i);
			break;
		}
		i++;
	}
}

#if 0
void Resources::SetEnvironmentMap(GfxContext& context, ShaderResources& specular_env_map, ShaderResources& diffuse_env_map)
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

#endif

Texture& Resources::CreateSolidColorTexture(const vec4& color) const
{
	const RGBA rgba = CreateRGBA(color);

    // Check cache to see if this flat texture already exists.
    int i = resources.solid_clr_tex_cache.Find(rgba);
    if (i >= 0) {
        return resources.solid_clr_tex_cache[i];
    }

    Texture& texture = resources.solid_clr_tex_cache.Add(rgba);
    texture.Set(rgba, 1, 1, 1, 4);
	return texture;
}

#if 0

void Resources::Bind(GfxContext& context) const
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

    DataBuffer buffers[] = { impl->resources.constant_buffer.Get() };
    context->VSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Scene, _countof(buffers), buffers);
    context->PSSetConstantBuffers(Pbr::ShaderSlots::ConstantBuffers::Scene, _countof(buffers), buffers);
    context->IASetinput_layout(impl->resources.input_layout.Get());

    static_assert(ShaderSlots::DiffuseTexture == ShaderSlots::SpecularTexture + 1, "Diffuse must follow Specular slot");
    static_assert(ShaderSlots::SpecularTexture == ShaderSlots::Brdf + 1, "Specular must follow BRDF slot");
    
    ShaderResources& shader_resources[] = {
		impl->resources.brdf_lut.Get(),
		impl->resources.specular_env_map.Get(),
		impl->Resources.diffuse_env_map.Get()
	};
    context->PSSetShaderResources(Pbr::ShaderSlots::Brdf, _countof(shader_resources), shader_resources);
    
    SamplerState& samplers[] = {
		impl->resources.brdf_sampler.Get(),
		impl->resources.env_map_sampler.Get()
	};
    context->PSSetSamplers(ShaderSlots::Brdf, _countof(samplers), samplers);*/
}

#endif

}


NAMESPACE_TOPSIDE_END

#endif
