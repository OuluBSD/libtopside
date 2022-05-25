#pragma once


NAMESPACE_PARALLEL_BEGIN


////////////////////////////////////////////////////////////////////////////////
// QuadRenderer
// Responsible for rendering quads in a 3D scene provided a transform matrix and texture
class QuadRenderer
{
public:
    QuadRenderer(Shared<GfxDevResources> deviceResources);

    void SetViewProjection(
        const mat4& worldToViewLeft,
        const mat4& viewToProjLeft,
        const mat4& worldToViewRight,
        const mat4& viewToProjRight);

    void CreateDeviceDependentResources();
    void ReleaseDeviceDependentResources();

    void Bind();
    void Render(
        mat4 const& matrix,
        ID3D11ShaderResourceView* texture);
    void Unbind();

private:
    // Cached pointer to device resources.
    Shared<GfxDevResources> dev_res;

    // Direct3D resources for quad geometry.
    NativeInputLayoutRef		m_inputLayout;
    NativeBufferRef				m_vertexBuffer;
    NativeBufferRef				m_indexBuffer;
    NativeVertexShaderRef		m_vertexShader;
    NativeGeometryShaderRef		m_geometryShader;
    NativePixelShaderRef		m_pixelShaderRGB;
	NativeBufferRef				m_modelConstantBuffer;
    NativeBufferRef				m_renderingConstantBuffer;

    // Direct3D resources for the default texture.
    NativeSamplerStateRef		m_samplerState;

    // System resources for quad geometry.
    uint32                                              m_indexCount = 0;
};


NAMESPACE_PARALLEL_END
