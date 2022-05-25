#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace DX {


// Function that reads from a binary file asynchronously.
inline std::future<std::vector<byte>> ReadDataAsync(const String& filename)
{
    //using namespace winrt::Windows::Storage;
    //using namespace winrt::Windows::Storage::Streams;
	
	TODO
	
    /*IBuffer fileBuffer = co_await PathIO::ReadBufferAsync(filename);
    
    std::vector<byte> returnBuffer(fileBuffer.Length());
    DataReader::FromBuffer(fileBuffer).ReadBytes(winrt::array_view<uint8_t>(returnBuffer));
    co_return returnBuffer;*/
}

inline std::future<NativeShaderResourceViewRef> LoadDDSTextureAsync(ID3D11Device* device, const String& filename)
{
    const std::vector<byte> fileData = co_await ReadDataAsync(filename);

    NativeShaderResourceViewRef textureView;

    Holo::CheckResult(DirectX::CreateDDSTextureFromMemory(
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
