#pragma once

#if 0

NAMESPACE_PARALLEL_BEGIN


// TextRenderer
// Responsible for rendering text onto a 2D texture provided a string
class TextRenderer
{
public:
	/*using GfxDevResources = typename Holo::GfxDevResources;
	using NativeShaderResourceViewRef = typename Holo::NativeShaderResourceViewRef;
	using NativeSamplerStateRef = typename Holo::NativeSamplerStateRef;
	using NativeTexture2DRef = typename Holo::NativeTexture2DRef;
	using NativeRenderTargetViewRef = typename Holo::NativeRenderTargetViewRef;
	using NativeRenderTargetRef = typename Holo::NativeRenderTargetRef;
	using NativeSolidColorBrushRef = typename Holo::NativeSolidColorBrushRef;
	using NativeWriteTextFormatRef = typename Holo::NativeWriteTextFormatRef;
	*/
	
    TextRenderer(
        Shared<GfxDevResources> dev_resources,
        uint32 tex_width,
        uint32 tex_height,
        float font_size);

    ~TextRenderer();

    void RenderTextOffscreen(const String& str);

    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    NativeShaderResourceViewRef	GetTexture() const { return shader_resource_view; };
    NativeSamplerStateRef		GetSampler() const { return point_sampler; };

private:
    // Cached pointer to device resources.
    Shared<GfxDevResources> dev_res;

    // graphics resources for rendering text to an off-screen render target.
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

#endif
