#if 0
#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


// Implementation is in the Gltf library so this isn't needed: #define STB_IMAGE_IMPLEMENTATION

//using namespace Microsoft::WRL;
//using namespace DirectX;

#define TRIANGLE_VERTEX_COUNT 3 // #define so it can be used in lambdas without capture

namespace Pbr {

namespace Internal {

void ThrowIfFailed(dword hr)
{
    if (hr != 0)
    {
        String s;
        s << "Error in PBR renderer: " << HexStr(hr);
        throw Exc(s);
    }
}

}

/*const D3D11_INPUT_ELEMENT_DESC Vertex::vtx_desc[5] =
{
    { "POSITION",       0, DXGI_FORMAT_R32G32B32_FLOAT,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",         0, DXGI_FORMAT_R32G32B32_FLOAT,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TANGENT",        0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD",       0, DXGI_FORMAT_R32G32_FLOAT,        0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TRANSFORMINDEX", 0, DXGI_FORMAT_R16_UINT,            0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};*/

void Texture::SetSolidColorTexture(const vec4& color) {
	const RGBA rgba = CreateRGBA(color);
	Set(rgba, 1, 1, 1, 4);
}

// Based on code from DirectXTK
void MeshBuilder::CreateSphere(Mesh& prim, float diameter, uint32 tessellation, Pbr::NodeIndex transform_idx)
{
    if (tessellation < 3) {
        throw std::out_of_range("tesselation parameter out of range");
    }
    
    auto& vertices = prim.vertices;
    auto& indices = prim.indices;

    const uint32 vert_segments = tessellation;
    const uint32 horz_segments = tessellation * 2;

    const float radius = diameter / 2;

    const uint32 start_vtx_idx = (uint32)vertices.GetCount();

    // Create rings of vertices at progressively higher latitudes.
    for (uint32 i = 0; i <= vert_segments; i++)
    {
        const float v = 1 - (float)i / vert_segments;

        const float latitude = (i * M_PI / vert_segments) - M_PIDIV2;
        float dy, dxz;
        ScalarSinCos(&dy, &dxz, latitude);

        // Create a single ring of vertices at this latitude.
        for (uint32 j = 0; j <= horz_segments; j++)
        {
            const float longitude = j * M_2PI / horz_segments;
            float dx, dz;
            ScalarSinCos(&dx, &dz, longitude);
            dx *= dxz;
            dz *= dxz;

            // Compute tangent at 90 degrees along longitude.
            float tdx, tdz;
            ScalarSinCos(&tdx, &tdz, longitude + M_PI);
            tdx *= dxz;
            tdz *= dxz;

            const vec4 normal = VectorSet(dx, dy, dz, 0);
            const vec4 tangent = VectorSet(tdx, 0, tdz, 0);

            const float u = (float)j / horz_segments;
            const vec4 tex_coord = VectorSet(u, v, 0, 0);

            Pbr::Vertex vert;
            StoreVec3(&vert.position, normal * radius);
            StoreVec3(&vert.normal, normal);
            StoreVec4(&vert.tangent, tangent);
            StoreVec2(&vert.tex_coord, tex_coord);

            vert.mdl_transform_idx = transform_idx;
            vertices.Add(vert);
        }
    }

    // Fill the index buffer with triangles joining each pair of latitude rings.
    const uint32 stride = horz_segments + 1;
    const uint32 start_indices_idx = (uint32)indices.GetCount();
    for (uint32 i = 0; i < vert_segments; i++)
    {
        for (uint32 j = 0; j <= horz_segments; j++)
        {
            uint32 next_i = i + 1;
            uint32 next_j = (j + 1) % stride;

            indices.Add(start_vtx_idx + (i * stride + j));
            indices.Add(start_vtx_idx + (next_i * stride + j));
            indices.Add(start_vtx_idx + (i * stride + next_j));

            indices.Add(start_vtx_idx + (i * stride + next_j));
            indices.Add(start_vtx_idx + (next_i * stride + j));
            indices.Add(start_vtx_idx + (next_i * stride + next_j));
        }
    }
}

// Based on code from DirectXTK
void MeshBuilder::CreateCube(Mesh& prim, float side_length, Pbr::NodeIndex transform_idx)
{
    auto& vertices = prim.vertices;
    auto& indices = prim.indices;
    
    // A box has six faces, each one pointing in a different direction.
    const int face_count = 6;

    static const vec4 face_normals[face_count] =
    {
        { {  0,  0,  1, 0 } } ,
        { {  0,  0, -1, 0 } },
        { {  1,  0,  0, 0 } },
        { { -1,  0,  0, 0 } },
        { {  0,  1,  0, 0 } },
        { {  0, -1,  0, 0 } },
    };

    static const vec4 tex_coords[4] =
    {
        { { 1, 0, 0, 0 } },
        { { 1, 1, 0, 0 } },
        { { 0, 1, 0, 0 } },
        { { 0, 0, 0, 0 } },
    };

    // Create each face in turn.
    const float half_side_length = side_length / 2;
    for (int i = 0; i < face_count; i++)
    {
        vec4 normal = face_normals[i];
        vec4 tangent = face_normals[i];

        // Get two vectors perpendicular both to the face normal and to each other.
        vec4 basis = (i >= 4) ? IdentityR2 : IdentityR1;

        vec4 side1 = VectorCross(normal, basis);
        vec4 side2 = VectorCross(normal, side1);

        // Six indices (two triangles) per face.
        size_t vbase = vertices.GetCount();
        indices.Add((uint32)vbase + 0);
        indices.Add((uint32)vbase + 1);
        indices.Add((uint32)vbase + 2);

        indices.Add((uint32)vbase + 0);
        indices.Add((uint32)vbase + 2);
        indices.Add((uint32)vbase + 3);

        const vec4 positions[4] =
        {
            { (normal - side1 - side2) * half_side_length },
            { (normal - side1 + side2) * half_side_length },
            { (normal + side1 + side2) * half_side_length },
            { (normal + side1 - side2) * half_side_length }
        };

        for (int i = 0; i < 4; i++)
        {
            Pbr::Vertex vert;
            StoreVec3(&vert.position, positions[i]);
            StoreVec3(&vert.normal, normal);
            StoreVec4(&vert.tangent, side1); // TODO arbitrarily picked side 1
            StoreVec2(&vert.tex_coord, tex_coords[i]);
            vert.mdl_transform_idx = transform_idx;
            vertices.Add(vert);
        }
    }
}

#if 0

namespace Texture {

ShaderResources& LoadImage(NativeDeviceRef device, const byte* file_data, uint32 file_size)
{
	TODO
	
    /*auto free_img_data = [](unsigned char* ptr) { ::free(ptr); };
    using stbi_unique_ptr = std::unique_ptr<unsigned char, decltype(free_img_data)>;

    int w, h, c;
    stbi_unique_ptr rgba_data(stbi_load_from_memory(file_data, file_size, &w, &h, &c, 4), free_img_data);
    if (!rgba_data)
    {
        throw Exc("Failed to load image file data.");
    }

    return CreateTexture(device, rgba_data.get(), w * h * c, w, h, DXGI_FORMAT_R8G8B8A8_UNORM);*/
}

ShaderResources& CreateFlatCubeTexture(NativeDeviceRef device, const vec4& color, DXGI_FORMAT format)
{
	TODO
	
    /*D3D11_TEXTURE2D_DESC desc{};
    desc.Width = 1;
    desc.Height = 1;
    desc.MipLevels = 1;
    desc.ArraySize = 6;
    desc.Format = format;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

    // Each side is a 1x1 pixel (RGBA) image.
    const RGBA rgba_clr = CreateRGBA(color);
    D3D11_SUBRESOURCE_DATA init_data[6];
    for (int i = 0; i < _countof(init_data); i++)
    {
        init_data[i].pSysMem = rgba_clr.data();
        init_data[i].SysMemPitch = init_data[i].SysMemSlicePitch = 4;
    }

    ComPtr<ID3D11Texture2D> cube_tex;
    Internal::ThrowIfFailed(device->CreateTexture2D(&desc, init_data, &cube_tex));

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{};
    srv_desc.Format = desc.Format;
    srv_desc.view_dimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
    srv_desc.Texture2D.MipLevels = desc.MipLevels;
    srv_desc.Texture2D.MostDetailedMip = 0;

    ShaderResources& tex_view;
    Internal::ThrowIfFailed(device->CreateShaderResourceView(cube_tex.Get(), &srv_desc, &tex_view));

    return tex_view;*/
}

ShaderResources& CreateTexture(NativeDeviceRef device, const byte* rgba, uint32 size, int width, int height, DXGI_FORMAT format)
{
    TODO
	
    /*D3D11_TEXTURE2D_DESC desc{};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = format;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA init_data{};
    init_data.pSysMem = rgba;
    init_data.SysMemPitch = size / height;
    init_data.SysMemSlicePitch = size;

    ComPtr<ID3D11Texture2D> texture2D;
    Internal::ThrowIfFailed(device->CreateTexture2D(&desc, &init_data, &texture2D));

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{};
    srv_desc.Format = desc.Format;
    srv_desc.view_dimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MipLevels = desc.MipLevels;
    srv_desc.Texture2D.MostDetailedMip = desc.MipLevels - 1;

    ShaderResources& tex_view;
    Internal::ThrowIfFailed(device->CreateShaderResourceView(texture2D.Get(), &srv_desc, &tex_view));

    return tex_view;*/
}

SamplerState& CreateSampler(NativeDeviceRef device, D3D11_TEXTURE_ADDRESS_MODE addressMode)
{
    TODO
	
    /*CD3D11_SAMPLER_DESC sampler_desc(CD3D11_DEFAULT{});
    sampler_desc.AddressU = sampler_desc.AddressV = sampler_desc.addr_w = addressMode;

    SamplerState& sampler_state;
    Pbr::Internal::ThrowIfFailed(device->CreateSamplerState(&sampler_desc, &sampler_state));
    return sampler_state;*/
}

}

#endif

}

NAMESPACE_TOPSIDE_END


#endif
