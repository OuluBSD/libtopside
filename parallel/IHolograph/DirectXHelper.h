#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace DX {


// Function that reads from a binary file asynchronously.
inline std::future<Vector<byte>> ReadDataAsync(const String& filename)
{
    //using namespace winrt::Windows::Storage;
    //using namespace winrt::Windows::Storage::Streams;
	
	TODO
	
    /*IBuffer fileBuffer = co_await PathIO::ReadBufferAsync(filename);
    
    Vector<byte> returnBuffer(fileBuffer.Length());
    DataReader::FromBuffer(fileBuffer).ReadBytes(winrt::array_view<uint8>(returnBuffer));
    co_return returnBuffer;*/
}

inline std::future<NativeShaderResourceViewRef> LoadDDSTextureAsync(ID3D11Device* device, const String& filename)
{
    const Vector<byte> fileData = co_await ReadDataAsync(filename);

    NativeShaderResourceViewRef tex_view;

    Holo::CheckResult(DirectX::CreateDDSTextureFromMemory(
        device,
        fileData.data(),
        fileData.size(),
        nullptr,
        tex_view.GetAddressOf()));

    co_return tex_view;
};

// Converts a length in device-independent pixels (DIPs) to a length in physical pixels.
inline float ConvertDipsToPixels(float dips, float dpi)
{
    constexpr float dips_per_inch = 96.0f;
    return floorf(dips * dpi / dips_per_inch + 0.5f); // Round to nearest integer.
}

#if defined(_DEBUG)
// Check for SDK Layer support.
inline bool SdkLayersAvailable()
{
	TODO
	/*
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

    return SUCCEEDED(hr);*/
}
#endif


}


NAMESPACE_PARALLEL_END
