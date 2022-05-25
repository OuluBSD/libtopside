#include "WinLib.h"


NAMESPACE_PARALLEL_BEGIN


struct QuadModelConstantBuffer
{
    mat4 model;
};

struct QuadRenderingParametersConstantBuffer
{
    mat4 view_proj[2];
};


// Assert that the constant buffer remains 16-byte aligned (best practice).
static_assert((sizeof(QuadModelConstantBuffer) % (sizeof(float) * 4)) == 0, "Model constant buffer size must be 16-byte aligned (16 bytes is the length of four floats).");


struct VertexPositionTex
{
    vec3 pos;
    vec2 tex;
};

// Loads vertex and pixel shaders from files and instantiates the quad geometry.
QuadRenderer::QuadRenderer(Shared<GfxDevResources> dev_resources) :
    dev_res(std::move(dev_resources))
{
    CreateDeviceDependentResources();
}

void QuadRenderer::Bind()
{
    const auto context = dev_res->GetD3DDeviceContext();

    const uint32 strides[] = { sizeof(VertexPositionTex) };
    const uint32 offsets[] = { 0 };

    context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), strides, offsets);
    context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(input_layout.Get());

    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->VSSetConstantBuffers(0, 1, model_constant_buffer.GetAddressOf());
    context->VSSetConstantBuffers(1, 1, rendering_constant_buffer.GetAddressOf());

    if (!dev_res->GetDeviceSupportsVprt())
    {
        // On devices that do not support the D3D11_FEATURE_D3D11_OPTIONS3::
        // VPAndRTArrayIndexFromAnyShaderFeedingRasterizer optional feature,
        // a pass-through geometry shader sets the render target ID.
        context->GSSetShader(geom_shader.Get(), nullptr, 0);
    }

    context->PSSetShader(pixel_shader_rgb.Get(), nullptr, 0);
    context->PSSetSamplers(0, 1, sampler_state.GetAddressOf());
}

void QuadRenderer::Render(mat4 const& matrix, ID3D11ShaderResourceView* texture)
{
    const auto context = dev_res->GetD3DDeviceContext();

    QuadModelConstantBuffer cb;
    cb.model = transpose(matrix);

    context->UpdateSubresource(model_constant_buffer.Get(), 0, nullptr, &cb, 0, 0);

    context->PSSetShaderResources(0, 1, &texture);

    context->DrawIndexedInstanced(index_count, 2, 0, 0, 0);
}

void QuadRenderer::Unbind()
{}

void QuadRenderer::SetViewProjection(
    const mat4& world_to_view_left,
    const mat4& view_to_proj_left,
    const mat4& world_to_view_right,
    const mat4& view_to_proj_right)
{
    mat4 view_projection[2];

    view_projection[0] = transpose(world_to_view_left * view_to_proj_left);
    view_projection[1] = transpose(world_to_view_right * view_to_proj_right);

    dev_res->GetD3DDeviceContext()->UpdateSubresource(rendering_constant_buffer.Get(), 0, nullptr, &view_projection, 0, 0);
}

void QuadRenderer::CreateDeviceDependentResources()
{
    const bool using_vprt = dev_res->GetDeviceSupportsVprt();
    const void* vertex_shader = (using_vprt) ? g_QuadVPRTVertexShader : g_QuadVertexShader;
    const size_t vertex_shader_size = (using_vprt) ? _countof(g_QuadVPRTVertexShader) : _countof(g_QuadVertexShader);

    Holo::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateVertexShader(
            vertex_shader,
            vertex_shader_size,
            nullptr,
            &vertex_shader
        )
    );

    constexpr FixedArray<D3D11_INPUT_ELEMENT_DESC, 2> vtx_desc = {{
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    }};

    Holo::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateInputLayout(
            vtx_desc.data(),
            static_cast<uint32>(vtx_desc.size()),
            vertex_shader,
            vertex_shader_size,
            &input_layout
        )
    );

    Holo::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreatePixelShader(
            g_QuadPixelShaderRGB,
            _countof(g_QuadPixelShaderRGB),
            nullptr,
            &pixel_shader_rgb
        )
    );

    if (!using_vprt)
    {
        Holo::ThrowIfFailed(
            dev_res->GetD3DDevice()->CreateGeometryShader(
                g_QuadGeometryShader,
                _countof(g_QuadGeometryShader),
                nullptr,
                &geom_shader
            )
        );
    }

    static const FixedArray<VertexPositionTex, 4> quadVertices = {{
        { vec3(-0.5f, +0.5f, +0.0f), float2(+0.0f, +0.0f) },
        { vec3(+0.5f, +0.5f, +0.0f), float2(+1.0f, +0.0f) },
        { vec3(+0.5f, -0.5f, +0.0f), float2(+1.0f, +1.0f) },
        { vec3(-0.5f, -0.5f, +0.0f), float2(+0.0f, +1.0f) },
    }};

    const D3D11_SUBRESOURCE_DATA vertex_buffer_data = { quadVertices.data() };

    const CD3D11_BUFFER_DESC vertex_buffer_desc{
        static_cast<uint32>(sizeof(VertexPositionTex) * quadVertices.size()),
        D3D11_BIND_VERTEX_BUFFER
    };

    Holo::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateBuffer(
            &vertex_buffer_desc,
            &vertex_buffer_data,
            &vertex_buffer
        )
    );

    constexpr FixedArray<uint16, 12> quad_indices = {{
        // -z
        0,2,3,
        0,1,2,

        // +z
        2,0,3,
        1,0,2,
    }};

    index_count = static_cast<uint32>(quad_indices.size());

    const D3D11_SUBRESOURCE_DATA index_buffer_data = { quad_indices.data() };

    const CD3D11_BUFFER_DESC index_buffer_desc {
        static_cast<uint32>(sizeof(uint16) * quad_indices.size()),
        D3D11_BIND_INDEX_BUFFER
    };
    Holo::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateBuffer(
            &index_buffer_desc,
            &index_buffer_data,
            &index_buffer
        )
    );

    const D3D11_SAMPLER_DESC desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());

    Holo::ThrowIfFailed(
        dev_res->GetD3DDevice()->CreateSamplerState(
            &desc,
            &sampler_state
        )
    );
    {
        const CD3D11_BUFFER_DESC constant_buffer_desc{
            sizeof(QuadModelConstantBuffer),
            D3D11_BIND_CONSTANT_BUFFER
        };

        Holo::ThrowIfFailed(
            dev_res->GetD3DDevice()->CreateBuffer(
                &constant_buffer_desc,
                nullptr,
                &model_constant_buffer
            )
        );
    }
    {
        const CD3D11_BUFFER_DESC constant_buffer_desc{
            sizeof(mat4) * 2,
            D3D11_BIND_CONSTANT_BUFFER
        };

        Holo::ThrowIfFailed(
            dev_res->GetD3DDevice()->CreateBuffer(
                &constant_buffer_desc,
                nullptr,
                &rendering_constant_buffer
            )
        );
    }
}

void QuadRenderer::ReleaseDeviceDependentResources()
{
    vertex_shader.Reset();
    input_layout.Reset();
    pixel_shader_rgb.Reset();
    geom_shader.Reset();

    model_constant_buffer.Reset();
    rendering_constant_buffer.Reset();

    vertex_buffer.Reset();
    index_buffer.Reset();

    sampler_state.Reset();
}


NAMESPACE_PARALLEL_END
