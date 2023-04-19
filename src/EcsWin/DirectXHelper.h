#pragma once


NAMESPACE_TOPSIDE_BEGIN


// Function that reads from a binary file asynchronously.
inline std::future<std::vector<byte>> ReadDataAsync(const std::wstring& filename)
{
    using namespace winrt::Windows::Storage;
    using namespace winrt::Windows::Storage::Streams;

    IBuffer fileBuffer = co_await PathIO::ReadBufferAsync(filename);
    
    std::vector<byte> returnBuffer(fileBuffer.Length());
    DataReader::FromBuffer(fileBuffer).ReadBytes(winrt::array_view<uint8_t>(returnBuffer));
    co_return returnBuffer;
}

inline std::future<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> LoadDDSTextureAsync(ID3D11Device* device, const std::wstring& filename)
{
    const std::vector<byte> fileData = co_await ReadDataAsync(filename);

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;

    winrt::check_hresult(DirectX::CreateDDSTextureFromMemory(
        device,
        fileData.data(),
        fileData.size(),
        nullptr,
        textureView.GetAddressOf()));

    co_return textureView;
};

// Converts a length in device-independent pixels (DIPs) to a length in physical pixels.
inline float ConvertDipsToPixels(float dips, float dpi)
{
    constexpr float dipsPerInch = 96.0f;
    return floorf(dips * dpi / dipsPerInch + 0.5f); // Round to nearest integer.
}

#if defined(_DEBUG)
// Check for SDK Layer support.
inline bool SdkLayersAvailable()
{
    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
        0,
        D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
        nullptr,                    // Any feature level will do.
        0,
        D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
        nullptr,                    // No need to keep the D3D device reference.
        nullptr,                    // No need to know the feature level.
        nullptr                     // No need to keep the D3D device context reference.
        );

    return SUCCEEDED(hr);
}
#endif


inline DirectX::XMVECTOR ToDxVec(const vec4& v) {
	return DirectX::XMVECTOR {v[0], v[1], v[2], v[3]};
}

inline vec4 ToTs(const DirectX::XMVECTORF32& v) {
	return vec4(v.f[0], v.f[1], v.f[2], v.f[3]);
}

using winrt::Windows::Foundation::Numerics::float3;
using winrt::Windows::Foundation::Numerics::float4;
using winrt::Windows::Foundation::Numerics::quaternion;
using winrt::Windows::Foundation::Numerics::float4x4;
using DirectX::XMMATRIX;

inline vec3 ToTs(const float3& v) {
	return vec3(v.x, v.y, v.z);
}

inline vec4 ToTs(const float4& v) {
	return vec4(v.x, v.y, v.z, v.w);
}

inline quat ToTs(const quaternion& v) {
	return quat(v.x, v.y, v.z, v.w);
}

inline mat4 ToTs(const float4x4& v) {
	mat4 m;
	m.data[0].data[0] = v.m11;
	m.data[0].data[1] = v.m12;
	m.data[0].data[2] = v.m13;
	m.data[0].data[3] = v.m14;
	m.data[1].data[0] = v.m21;
	m.data[1].data[1] = v.m22;
	m.data[1].data[2] = v.m23;
	m.data[1].data[3] = v.m24;
	m.data[2].data[0] = v.m31;
	m.data[2].data[1] = v.m32;
	m.data[2].data[2] = v.m33;
	m.data[2].data[3] = v.m34;
	m.data[3].data[0] = v.m41;
	m.data[3].data[1] = v.m42;
	m.data[3].data[2] = v.m43;
	m.data[3].data[3] = v.m44;
	return m;
}

inline mat4 ToTs(const XMMATRIX& v) {
	mat4 m;
	m.data[0].data[0] = v.r[0].m128_f32[0];
	m.data[0].data[1] = v.r[0].m128_f32[1];
	m.data[0].data[2] = v.r[0].m128_f32[2];
	m.data[0].data[3] = v.r[0].m128_f32[3];
	m.data[1].data[0] = v.r[1].m128_f32[0];
	m.data[1].data[1] = v.r[1].m128_f32[1];
	m.data[1].data[2] = v.r[1].m128_f32[2];
	m.data[1].data[3] = v.r[1].m128_f32[3];
	m.data[2].data[0] = v.r[2].m128_f32[0];
	m.data[2].data[1] = v.r[2].m128_f32[1];
	m.data[2].data[2] = v.r[2].m128_f32[2];
	m.data[2].data[3] = v.r[2].m128_f32[3];
	m.data[3].data[0] = v.r[3].m128_f32[0];
	m.data[3].data[1] = v.r[3].m128_f32[1];
	m.data[3].data[2] = v.r[3].m128_f32[2];
	m.data[3].data[3] = v.r[3].m128_f32[3];
	return m;
}

NAMESPACE_TOPSIDE_END
