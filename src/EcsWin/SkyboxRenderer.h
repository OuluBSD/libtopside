#pragma once


NAMESPACE_PARALLEL_BEGIN


////////////////////////////////////////////////////////////////////////////////
// SkyboxRenderer
// Responsible for rendering a cube-map Skybox in a 3D scene provided a cube-map texture
class SkyboxRenderer
{
public:
    SkyboxRenderer(
        std::shared_ptr<DeviceResources> deviceResources,
        ID3D11ShaderResourceView* skyboxTexture);

    ~SkyboxRenderer() = default;

    void SetTexture(
        ID3D11ShaderResourceView* skyboxTexture);

    void SetViewProjection(
        const winrt::Windows::Foundation::Numerics::float4x4& cameraToViewLeft,
        const winrt::Windows::Foundation::Numerics::float4x4& viewToProjLeft,
        const winrt::Windows::Foundation::Numerics::float4x4& cameraToViewRight,
        const winrt::Windows::Foundation::Numerics::float4x4& viewToProjRight);
        
    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    void Bind();
    void Render();
    void Unbind();

private:
    std::shared_ptr<DeviceResources> m_deviceResources;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_skyboxTexture;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
    Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState_Backup;
    UINT m_stencilRef_Backup;
};


NAMESPACE_PARALLEL_END
