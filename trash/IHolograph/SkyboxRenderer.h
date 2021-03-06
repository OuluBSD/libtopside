#pragma once

#if 0

NAMESPACE_PARALLEL_BEGIN


// SkyboxRenderer
// Responsible for rendering a cube-map Skybox in a 3D scene provided a cube-map texture
class SkyboxRenderer
{
public:
	/*using GfxDevResources = typename Holo::GfxDevResources;
	using NativeShaderResourceViewRef = typename Holo::NativeShaderResourceViewRef;
	using NativeVertexShaderRef = typename Holo::NativeVertexShaderRef;
	using NativeGeometryShaderRef = typename Holo::NativeGeometryShaderRef;
	using NativePixelShaderRef = typename Holo::NativePixelShaderRef;
	using NativeSamplerStateRef = typename Holo::NativeSamplerStateRef;
	using NativeDepthStencilStateRef = typename Holo::NativeDepthStencilStateRef;
	using NativeBufferRef = typename Holo::NativeBufferRef;
	using NativeInputLayoutRef = typename Holo::NativeInputLayoutRef;
	*/
	
    SkyboxRenderer(
        Shared<GfxDevResources> dev_resources,
        NativeShaderResourceViewRef skybox_tex);

    ~SkyboxRenderer() = default;

    void SetTexture(
        NativeShaderResourceViewRef skybox_tex);

    void SetViewProjection(
        const mat4& camera_to_view_left,
        const mat4& view_to_proj_left,
        const mat4& camera_to_view_right,
        const mat4& view_to_proj_right);
        
    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    void Bind();
    void Render();
    void Unbind();

private:
    Shared<GfxDevResources>			dev_res;
    NativeShaderResourceViewRef		skybox_tex;
    NativeVertexShaderRef			vertex_shader;
    NativeGeometryShaderRef			geom_shader;
    NativePixelShaderRef			pixel_shader;
    NativeSamplerStateRef			sampler_state;
    NativeDepthStencilStateRef		depth_stencil_state;
    NativeBufferRef					vertex_buffer;
    NativeBufferRef					constant_buffer;
    NativeInputLayoutRef			input_layout;
	NativeDepthStencilStateRef		depth_stencil_state_backup;
    uint32							stencil_backup;
    
};


NAMESPACE_PARALLEL_END

#endif
