#pragma once


NAMESPACE_PARALLEL_BEGIN


// TextRenderer
// Responsible for rendering text onto a 2D texture provided a string
template <class Holo>
class TextRendererT
{
public:
	using GfxDevResources = typename Holo::GfxDevResources;
	using NativeShaderResourceViewRef = typename Holo::NativeShaderResourceViewRef;
	using NativeSamplerStateRef = typename Holo::NativeSamplerStateRef;
	using NativeTexture2DRef = typename Holo::NativeTexture2DRef;
	using NativeRenderTargetViewRef = typename Holo::NativeRenderTargetViewRef;
	using NativeRenderTargetRef = typename Holo::NativeRenderTargetRef;
	using NativeSolidColorBrushRef = typename Holo::NativeSolidColorBrushRef;
	using NativeWriteTextFormatRef = typename Holo::NativeWriteTextFormatRef;
	
	
    TextRendererT(
        Shared<GfxDevResources> dev_resources,
        uint32 tex_width,
        uint32 tex_height,
        float font_size);

    ~TextRendererT();

    void RenderTextOffscreen(const String& str);

    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    NativeShaderResourceViewRef	GetTexture() const { return shader_resource_view; };
    NativeSamplerStateRef		GetSampler() const { return point_sampler; };

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

