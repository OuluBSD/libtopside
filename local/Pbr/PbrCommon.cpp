#include "Pbr.h"

// Implementation is in the Gltf library so this isn't needed: #define STB_IMAGE_IMPLEMENTATION

using namespace Microsoft::WRL;
using namespace DirectX;

#define TRIANGLE_VERTEX_COUNT 3 // #define so it can be used in lambdas without capture

namespace Pbr {

namespace Internal
{
    void ThrowIfFailed(dword hr)
    {
        if (hr != 0)
        {
            StringStream ss;
            ss << std::hex << "Error in PBR renderer: 0x" << hr;
            throw std::exception(ss.str().c_str());
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

// Based on code from DirectXTK
PrimitiveBuilder& PrimitiveBuilder::AddSphere(float diameter, uint32 tessellation, Pbr::NodeIndex_t transform_idx)
{
    if (tessellation < 3)
    {
        throw std::out_of_range("tesselation parameter out of range");
    }

    const uint32 verticalSegments = tessellation;
    const uint32 horizontalSegments = tessellation * 2;

    const float radius = diameter / 2;

    const uint32 startVertexIndex = (uint32)vertices.size();

    // Create rings of vertices at progressively higher latitudes.
    for (uint32 i = 0; i <= verticalSegments; i++)
    {
        const float v = 1 - (float)i / verticalSegments;

        const float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
        float dy, dxz;
        XMScalarSinCos(&dy, &dxz, latitude);

        // Create a single ring of vertices at this latitude.
        for (uint32 j = 0; j <= horizontalSegments; j++)
        {
            const float longitude = j * XM_2PI / horizontalSegments;
            float dx, dz;
            XMScalarSinCos(&dx, &dz, longitude);
            dx *= dxz;
            dz *= dxz;

            // Compute tangent at 90 degrees along longitude.
            float tdx, tdz;
            XMScalarSinCos(&tdx, &tdz, longitude + XM_PI);
            tdx *= dxz;
            tdz *= dxz;

            const vec4 normal = XMVectorSet(dx, dy, dz, 0);
            const vec4 tangent = XMVectorSet(tdx, 0, tdz, 0);

            const float u = (float)j / horizontalSegments;
            const vec4 textureCoordinate = XMVectorSet(u, v, 0, 0);

            Pbr::Vertex vert;
            XMStoreFloat3(&vert.position, normal * radius);
            XMStoreFloat3(&vert.normal, normal);
            XMStoreFloat4(&vert.tangent, tangent);
            XMStoreFloat2(&vert.tex_coord, textureCoordinate);

            vert.mdl_transform_idx = transform_idx;
            vertices.push_back(vert);
        }
    }

    // Fill the index buffer with triangles joining each pair of latitude rings.
    const uint32 stride = horizontalSegments + 1;
    const uint32 startindicesIndex = (uint32)indices.size();
    for (uint32 i = 0; i < verticalSegments; i++)
    {
        for (uint32 j = 0; j <= horizontalSegments; j++)
        {
            uint32 nextI = i + 1;
            uint32 nextJ = (j + 1) % stride;

            indices.push_back(startVertexIndex + (i * stride + j));
            indices.push_back(startVertexIndex + (nextI * stride + j));
            indices.push_back(startVertexIndex + (i * stride + nextJ));

            indices.push_back(startVertexIndex + (i * stride + nextJ));
            indices.push_back(startVertexIndex + (nextI * stride + j));
            indices.push_back(startVertexIndex + (nextI * stride + nextJ));
        }
    }

    return *this;
}

// Based on code from DirectXTK
PrimitiveBuilder& PrimitiveBuilder::AddCube(float sideLength, Pbr::NodeIndex_t transform_idx)
{
    // A box has six faces, each one pointing in a different direction.
    const int FaceCount = 6;

    static const vec4loader facenormals[FaceCount] =
    {
        { { {  0,  0,  1, 0 } } },
        { { {  0,  0, -1, 0 } } },
        { { {  1,  0,  0, 0 } } },
        { { { -1,  0,  0, 0 } } },
        { { {  0,  1,  0, 0 } } },
        { { {  0, -1,  0, 0 } } },
    };

    static const vec4loader textureCoordinates[4] =
    {
        { { { 1, 0, 0, 0 } } },
        { { { 1, 1, 0, 0 } } },
        { { { 0, 1, 0, 0 } } },
        { { { 0, 0, 0, 0 } } },
    };

    // Create each face in turn.
    const float halfSideLength = sideLength / 2;
    for (int i = 0; i < FaceCount; i++)
    {
        vec4 normal = facenormals[i];
        vec4 tangent = facenormals[i];

        // Get two vectors perpendicular both to the face normal and to each other.
        vec4 basis = (i >= 4) ? g_XMIdentityR2 : g_XMIdentityR1;

        vec4 side1 = XMVector3Cross(normal, basis);
        vec4 side2 = XMVector3Cross(normal, side1);

        // Six indices (two triangles) per face.
        size_t vbase = vertices.size();
        indices.push_back((uint32)vbase + 0);
        indices.push_back((uint32)vbase + 1);
        indices.push_back((uint32)vbase + 2);

        indices.push_back((uint32)vbase + 0);
        indices.push_back((uint32)vbase + 2);
        indices.push_back((uint32)vbase + 3);

        const vec4 positions[4] =
        {
            { (normal - side1 - side2) * halfSideLength },
            { (normal - side1 + side2) * halfSideLength },
            { (normal + side1 + side2) * halfSideLength },
            { (normal + side1 - side2) * halfSideLength }
        };

        for (int i = 0; i < 4; i++)
        {
            Pbr::Vertex vert;
            XMStoreFloat3(&vert.position, positions[i]);
            XMStoreFloat3(&vert.normal, normal);
            XMStoreFloat4(&vert.tangent, side1); // TODO arbitrarily picked side 1
            XMStoreFloat2(&vert.tex_coord, textureCoordinates[i]);
            vert.mdl_transform_idx = transform_idx;
            vertices.push_back(vert);
        }
    }

    return *this;
}

namespace Texture {

FixedArray<byte, 4> CreateRGBA(const vec4& color)
{
    vec4 colorf;
    DirectX::XMStoreFloat4(&colorf, DirectX::XMVectorScale(color, 255));
    return FixedArray<byte, 4> { (byte)colorf.x, (byte)colorf.y, (byte)colorf.z, (byte)colorf.w };
}

ComPtr<ID3D11ShaderResourceView> LoadImage(ID3D11Device* device, const byte* file_data, uint32 file_size)
{
    auto freeImageData = [](unsigned char* ptr) { ::free(ptr); };
    using stbi_unique_ptr = std::unique_ptr<unsigned char, decltype(freeImageData)>;

    int w, h, c;
    stbi_unique_ptr rgbaData(stbi_load_from_memory(file_data, file_size, &w, &h, &c, 4), freeImageData);
    if (!rgbaData)
    {
        throw std::exception("Failed to load image file data.");
    }

    return CreateTexture(device, rgbaData.get(), w * h * c, w, h, DXGI_FORMAT_R8G8B8A8_UNORM);
}

ComPtr<ID3D11ShaderResourceView> CreateFlatCubeTexture(ID3D11Device* device, const vec4& color, DXGI_FORMAT format)
{
    D3D11_TEXTURE2D_DESC desc{};
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
    const FixedArray<byte, 4> rgbaColor = CreateRGBA(color);
    D3D11_SUBRESOURCE_DATA init_data[6];
    for (int i = 0; i < _countof(init_data); i++)
    {
        init_data[i].pSysMem = rgbaColor.data();
        init_data[i].SysMemPitch = init_data[i].SysMemSlicePitch = 4;
    }

    ComPtr<ID3D11Texture2D> cubeTexture;
    Internal::ThrowIfFailed(device->CreateTexture2D(&desc, init_data, &cubeTexture));

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{};
    srv_desc.Format = desc.Format;
    srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
    srv_desc.Texture2D.MipLevels = desc.MipLevels;
    srv_desc.Texture2D.MostDetailedMip = 0;

    ComPtr<ID3D11ShaderResourceView> tex_view;
    Internal::ThrowIfFailed(device->CreateShaderResourceView(cubeTexture.Get(), &srv_desc, &tex_view));

    return tex_view;
}

ComPtr<ID3D11ShaderResourceView> CreateTexture(ID3D11Device* device, const byte* rgba, uint32 size, int width, int height, DXGI_FORMAT format)
{
    D3D11_TEXTURE2D_DESC desc{};
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
    srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MipLevels = desc.MipLevels;
    srv_desc.Texture2D.MostDetailedMip = desc.MipLevels - 1;

    ComPtr<ID3D11ShaderResourceView> tex_view;
    Internal::ThrowIfFailed(device->CreateShaderResourceView(texture2D.Get(), &srv_desc, &tex_view));

    return tex_view;
}

ComPtr<ID3D11SamplerState> CreateSampler(ID3D11Device* device, D3D11_TEXTURE_ADDRESS_MODE addressMode)
{
    CD3D11_SAMPLER_DESC samplerDesc(CD3D11_DEFAULT{});
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = addressMode;

    ComPtr<ID3D11SamplerState> samplerState;
    Pbr::Internal::ThrowIfFailed(device->CreateSamplerState(&samplerDesc, &samplerState));
    return samplerState;
}

}

}

NAMESPACE_TOPSIDE_END

