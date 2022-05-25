#pragma once


NAMESPACE_PARALLEL_BEGIN


////////////////////////////////////////////////////////////////////////////////
// QuadRenderer
// Responsible for rendering quads in a 3D scene provided a transform matrix and texture
class QuadRenderer
{
public:
    QuadRenderer(Shared<GfxDevResources> dev_resources);

    void SetViewProjection(
        const mat4& world_to_view_left,
        const mat4& view_to_proj_left,
        const mat4& world_to_view_right,
        const mat4& view_to_proj_right);

    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    void Bind();
    void Render(
        const mat4& matrix,
        ID3D11ShaderResourceView* texture);
    void Unbind();

private:
    // Cached pointer to device resources.
    Shared<GfxDevResources>		dev_res;

    // Direct3D resources for quad geometry.
    NativeInputLayoutRef		input_layout;
    NativeBufferRef				vertex_buffer;
    NativeBufferRef				index_buffer;
    NativeVertexShaderRef		vertex_shader;
    NativeGeometryShaderRef		geom_shader;
    NativePixelShaderRef		pixel_shader_rgb;
	NativeBufferRef				model_constant_buffer;
    NativeBufferRef				rendering_constant_buffer;

    // Direct3D resources for the default texture.
    NativeSamplerStateRef		sampler_state;

    // System resources for quad geometry.
    uint32						index_count = 0;
    
};


NAMESPACE_PARALLEL_END
