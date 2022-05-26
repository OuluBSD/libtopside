#include "IHolograph.h"


NAMESPACE_PARALLEL_BEGIN


template <class Holo>
TextRendererT<Holo>::TextRendererT(
    Shared<GfxDevResources> dev_resources,
    uint32 tex_width,
    uint32 tex_height,
    float font_size) :
    dev_res(std::move(dev_resources)),
    tex_width(tex_width),
    tex_height(tex_height),
    font_size(font_size)
{
    CreateDeviceDependentResources();
}

template <class Holo>
TextRendererT<Holo>::~TextRendererT() = default;

template <class Holo>
void TextRendererT<Holo>::RenderTextOffscreen(const String& str)
{
    // Clear the off-screen render target.
    dev_res->GetD3DDeviceContext()->ClearRenderTargetView(render_target_view.Get(), Colors::Transparent);

    // Begin drawing with D2D.
    rend2d_tgt->BeginDraw();

    // Create a text layout to match the screen.
    Microsoft::WRL::ComPtr<IDWriteTextLayout> text_layout;
    dev_res->GetDWriteFactory()->CreateTextLayout(
        str.c_str(),
        static_cast<uint32>(str.length()),
        text_format.Get(),
        (float)tex_width,
        (float)tex_height,
        &text_layout
    );

    // Get the text metrics from the text layout.
    DWRITE_TEXT_METRICS metrics;
    Holo::ThrowIfFailed(text_layout->GetMetrics(&metrics));

    // In this example, we position the text in the center of the off-screen render target.
    D2D1::Matrix3x2F screen_translation = D2D1::Matrix3x2F::Translation(
        tex_width * 0.5f,
        tex_height * 0.5f + metrics.height * 0.5f
    );
    white_brush->SetTransform(screen_translation);

    // Render the text using DirectWrite.
    rend2d_tgt->DrawTextLayout(
        D2D1::Point2F(0.0f, 0.0f),
        text_layout.Get(),
        white_brush.Get()
    );

    // End drawing with D2D.
    HRESULT hr = rend2d_tgt->EndDraw();
    if (hr != D2DERR_RECREATE_TARGET)
    {
        // Catch errors from D2D.
        Holo::ThrowIfFailed(hr);
    }
}

template <class Holo>
void TextRendererT<Holo>::ReleaseDeviceDependentResources()
{
    texture.Reset();
    shader_resource_view.Reset();
    point_sampler.Reset();
    render_target_view.Reset();
    rend2d_tgt.Reset();
    white_brush.Reset();
    text_format.Reset();
}

template <class Holo>
void TextRendererT<Holo>::CreateDeviceDependentResources()
{
    // Create a default sampler state, which will use point sampling.
    const CD3D11_SAMPLER_DESC desc{ CD3D11_DEFAULT{} };
    Holo::ThrowIfFailed(dev_res->GetD3DDevice()->CreateSamplerState(&desc, &point_sampler));

    // Create the texture that will be used as the offscreen render target.
    const CD3D11_TEXTURE2D_DESC textureDesc{
        DXGI_FORMAT_B8G8R8A8_UNORM,
        tex_width,
        tex_height,
        1,
        1,
        D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET
    };
    Holo::ThrowIfFailed(dev_res->GetD3DDevice()->CreateTexture2D(&textureDesc, nullptr, &texture));

    // Create read and write views for the offscreen render target.
    Holo::ThrowIfFailed(dev_res->GetD3DDevice()->CreateShaderResourceView(texture.Get(), nullptr, &shader_resource_view));

    Holo::ThrowIfFailed(dev_res->GetD3DDevice()->CreateRenderTargetView(texture.Get(), nullptr, &render_target_view));

    // In this example, we are using D2D and DirectWrite; so, we need to create a D2D render target as well.
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96,
        96
    );

    // The DXGI surface is used to create the render target.
    NativeGfxLibSurfaceRef gfxlib_surface;
    Holo::ThrowIfFailed(texture.As(&gfxlib_surface));
    Holo::ThrowIfFailed(dev_res->GetD2DFactory()->CreateDxgiSurfaceRenderTarget(gfxlib_surface.Get(), &props, &rend2d_tgt));

    // Create a solid color brush that will be used to render the text.
    Holo::ThrowIfFailed(rend2d_tgt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Cornsilk), &white_brush));

    // This is where we format the text that will be written on the render target.
    Holo::ThrowIfFailed(
        dev_res->GetDWriteFactory()->CreateTextFormat(
            "Consolas",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            font_size,
            "",
            text_format.ReleaseAndGetAddressOf()
        )
    );
    Holo::ThrowIfFailed(text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING));
    Holo::ThrowIfFailed(text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR));
}


NAMESPACE_PARALLEL_END
