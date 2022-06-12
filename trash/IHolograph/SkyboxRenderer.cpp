#include "IHolograph.h"

#if 0

NAMESPACE_PARALLEL_BEGIN



SkyboxRenderer::SkyboxRenderer(
    Shared<GfxDevResources> dev_resources,
    NativeShaderResourceViewRef skybox_tex) :
    dev_res(std::move(dev_resources)),
    skybox_tex(skybox_tex)
{
    CreateDeviceDependentResources();
}

void SkyboxRenderer::SetTexture(NativeShaderResourceViewRef skybox_tex)
{
    this->skybox_tex = skybox_tex;
}

void SkyboxRenderer::SetViewProjection(
    const mat4& camera_to_view_left,
    const mat4& view_to_proj_left,
    const mat4& camera_to_view_right,
    const mat4& view_to_proj_right)
{
    mat4 inv_view_projection[2];

    fail_fast_if(!invert(camera_to_view_left * view_to_proj_left, &inv_view_projection[0]));
    fail_fast_if(!invert(camera_to_view_right * view_to_proj_right, &inv_view_projection[1]));

    inv_view_projection[0] = transpose(inv_view_projection[0]);
    inv_view_projection[1] = transpose(inv_view_projection[1]);

    dev_res->GetD3DDeviceContext()->UpdateSubresource(constant_buffer.Get(), 0, nullptr, &inv_view_projection, 0, 0);
}

void SkyboxRenderer::CreateDeviceDependentResources()
{
	TODO
	
	#if 0
    const auto device = dev_res->GetD3DDevice();

    Holo::ThrowIfFailed(device->CreatePixelShader(
        g_SkyBoxPixelShader, sizeof(g_SkyBoxPixelShader), nullptr, &pixel_shader));

    const bool use_vprt = dev_res->GetDeviceSupportsVprt();
    const void* vertex_shader = (use_vprt) ? g_SkyBoxVertexShaderVprt : g_SkyBoxVertexShaderNoVprt;
    const size_t vertex_shader_size = (use_vprt) ? _countof(g_SkyBoxVertexShaderVprt) : _countof(g_SkyBoxVertexShaderNoVprt);

    if (!use_vprt) {
        Holo::ThrowIfFailed(device->CreateGeometryShader(
            g_SkyBoxGeometryShaderNoVprt, sizeof(g_SkyBoxGeometryShaderNoVprt), nullptr, &geom_shader));
    }

    Holo::ThrowIfFailed(device->CreateVertexShader(
        vertex_shader, vertex_shader_size, nullptr, &vertex_shader));

    {
        const CD3D11_SAMPLER_DESC desc{ CD3D11_DEFAULT() };

        Holo::ThrowIfFailed(device->CreateSamplerState(
            &desc, &sampler_state));
    }
    {
        static const float4 ndc_quad[] = {
            { -1.0f, +1.0f, 1.0f, 1.0f },
            { +1.0f, +1.0f, 1.0f, 1.0f },
            { +1.0f, -1.0f, 1.0f, 1.0f },

            { -1.0f, +1.0f, 1.0f, 1.0f },
            { +1.0f, -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f, 1.0f },
        };

        const CD3D11_BUFFER_DESC desc{
            sizeof(ndc_quad),
            D3D11_BIND_VERTEX_BUFFER
        };

        const D3D11_SUBRESOURCE_DATA data{
            ndc_quad, 0, 0
        };

        Holo::ThrowIfFailed(device->CreateBuffer(
            &desc, &data, &vertex_buffer));
    }
    {
        const CD3D11_BUFFER_DESC desc{
            sizeof(mat4) * 2,
            D3D11_BIND_CONSTANT_BUFFER
        };

        Holo::ThrowIfFailed(device->CreateBuffer(
            &desc, nullptr, &constant_buffer));
    }
    {
        CD3D11_DEPTH_STENCIL_DESC desc{
            CD3D11_DEFAULT()
        };

        desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
        desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

        Holo::ThrowIfFailed(device->CreateDepthStencilState(
            &desc, &depth_stencil_state));
    }

    const D3D11_INPUT_ELEMENT_DESC NdcDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    Holo::ThrowIfFailed(device->CreateInputLayout(
        NdcDesc, _countof(NdcDesc), vertex_shader, vertex_shader_size, &input_layout));
    
    #endif
}

void SkyboxRenderer::ReleaseDeviceDependentResources()
{
    skybox_tex = nullptr;
    vertex_shader = nullptr;
    geom_shader = nullptr;
    pixel_shader = nullptr;
    sampler_state = nullptr;
    depth_stencil_state = nullptr;
    vertex_buffer = nullptr;
    constant_buffer = nullptr;
    input_layout = nullptr;
}

void SkyboxRenderer::Bind()
{
    const auto context = dev_res->GetD3DDeviceContext();

    context->OMGetDepthStencilState(&depth_stencil_state_backup, &stencil_backup);

    const uint32 strides[1] = { sizeof(float4) };
    const uint32 offsets[1] = { 0 };
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(input_layout.Get());
    context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), strides, offsets);
    context->OMSetDepthStencilState(depth_stencil_state.Get(), 0);

    context->VSSetShader(vertex_shader.Get(), nullptr, 0);
    context->GSSetShader(geom_shader.Get(), nullptr, 0);
    context->PSSetShader(pixel_shader.Get(), nullptr, 0);

    context->VSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
    context->PSSetShaderResources(0, 1, skybox_tex.GetAddressOf());
    context->PSSetSamplers(0, 1, sampler_state.GetAddressOf());
}

void SkyboxRenderer::Render()
{
    const auto context = dev_res->GetD3DDeviceContext();

    // Fullscreen Quad: 6 vertices
    context->DrawInstanced(6, 2, 0, 0);
}

void SkyboxRenderer::Unbind()
{
    const auto context = dev_res->GetD3DDeviceContext();

    context->OMSetDepthStencilState(depth_stencil_state_backup.Get(), stencil_backup);

    depth_stencil_state_backup = nullptr;
    stencil_backup = 0;
}


NAMESPACE_PARALLEL_END

#endif
