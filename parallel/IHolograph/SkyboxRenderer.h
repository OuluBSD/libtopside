#pragma once


NAMESPACE_PARALLEL_BEGIN


////////////////////////////////////////////////////////////////////////////////
// SkyboxRenderer
// Responsible for rendering a cube-map Skybox in a 3D scene provided a cube-map texture
class SkyboxRenderer
{
public:
    SkyboxRenderer(
        Shared<GfxDevResources> deviceResources,
        ID3D11ShaderResourceView* skyboxTexture);

    ~SkyboxRenderer() = default;

    void SetTexture(
        ID3D11ShaderResourceView* skyboxTexture);

    void SetViewProjection(
        const mat4& cameraToViewLeft,
        const mat4& viewToProjLeft,
        const mat4& cameraToViewRight,
        const mat4& viewToProjRight);
        
    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    void Bind();
    void Render();
    void Unbind();

private:
    Shared<GfxDevResources> dev_res;

    NativeShaderResourceViewRef		m_skyboxTexture;
    NativeVertexShaderRef			m_vertexShader;
    NativeGeometryShaderRef			m_geometryShader;
    NativePixelShaderRef			m_pixelShader;
    NativeSamplerStateRef			m_samplerState;
    NativeDepthStencilStateRef		m_depthStencilState;
    NativeBufferRef					m_vertexBuffer;
    NativeBufferRef					m_constantBuffer;
    NativeInputLayoutRef			m_inputLayout;

    NativeDepthStencilStateRef		m_depthStencilState_Backup;
    
    uint32							m_stencilRef_Backup;
    
};


NAMESPACE_PARALLEL_END
