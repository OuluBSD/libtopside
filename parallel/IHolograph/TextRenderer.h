#pragma once


NAMESPACE_PARALLEL_BEGIN

	
////////////////////////////////////////////////////////////////////////////////
// TextRenderer
// Responsible for rendering text onto a 2D texture provided a string
class TextRenderer
{
public:
    TextRenderer(
        Shared<GfxDevResources> dev_resources,
        uint32 tex_width,
        uint32 tex_height,
        float font_size);

    ~TextRenderer();

    void RenderTextOffscreen(const String& str);

    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    ID3D11ShaderResourceView*	GetTexture() const { return shader_resource_view.Get(); };
    NativeSamplerStateRef		GetSampler() const { return point_sampler.Get(); };

private:
    // Cached pointer to device resources.
    Shared<GfxDevResources> dev_res;

    // Direct3D resources for rendering text to an off-screen render target.
    NativeTexture2DRef              texture;
    NativeShaderResourceViewRef		shader_resource_view;
    NativeSamplerStateRef			point_sampler;
    NativeRenderTargetViewRef		render_target_view;
    NativeRenderTargetRef			rend2d_tgt;
    NativeSolidColorBrushRef		white_brush;
    NativeWriteTextFormatRef		text_format;

    // CPU-based variables for configuring the offscreen render target.
    const uint32 tex_width;
    const uint32 tex_height;
    const float font_size;
    
};


NAMESPACE_PARALLEL_END

