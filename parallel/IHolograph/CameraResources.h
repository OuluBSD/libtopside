#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace DX {

	
class DeviceResources;


// Manages DirectX device resources that are specific to a holographic camera, such as the
// back buffer, ViewProjection constant buffer, and viewport.
class CameraResources
{
public:
    CameraResources(const HoloCam& holographicCamera);

    void CreateResourcesForBackBuffer(
        const GfxDevResources* pDeviceResources,
        const HoloCamRendParams& cameraParameters
        );
    void ReleaseResourcesForBackBuffer(
        const GfxDevResources* pDeviceResources
        );

    bool GetViewProjectionTransform(
        Shared<GfxDevResources> deviceResources,
        const HoloCamPose& cameraPose,
        const SpatialCoordinateSystem& coordinateSystem,
        _Out_ HoloStereoTransform* viewTransform,
        _Out_ HoloStereoTransform* projectionTransform);

    void CommitDirect3D11DepthBuffer(
        const HoloCamRendParams& renderingParameters) const;

    // Direct3D device resources.
    NativeRenderTargetViewRef	GetBackBufferRenderTargetView()     const { return m_d3dRenderTargetView.Get();     }
    NativeDepthStencilViewRef	GetDepthStencilView()               const { return m_d3dDepthStencilView.Get();     }
    NativeTexture2DRef			GetBackBufferTexture2D()            const { return m_d3dBackBuffer.Get();           }
    D3D11_VIEWPORT          GetViewport()                       const { return m_d3dViewport;                   }
    DXGI_FORMAT             GetBackBufferDXGIFormat()           const { return m_dxgiFormat;                    }

    // Render target properties.
    vec2 GetRenderTargetSize()      const& { return m_d3dRenderTargetSize;           }
    bool                    IsRenderingStereoscopic()           const  { return m_isStereo;                      }

    // The holographic camera these resources are for.
    HoloCam const& GetHolographicCamera() const { return m_holographicCamera; }

private:
    // Direct3D rendering objects. Required for 3D.
    NativeRenderTargetViewRef				m_d3dRenderTargetView;
    NativeDepthStencilViewRef				m_d3dDepthStencilView;
    NativeTexture2DRef						m_d3dDepthStencil;
    NativeTexture2DRef						m_d3dBackBuffer;

    // Direct3D rendering properties.
    DXGI_FORMAT                                                 m_dxgiFormat;
    vec2                            m_d3dRenderTargetSize;
    D3D11_VIEWPORT                                              m_d3dViewport;

    // Indicates whether the camera supports stereoscopic rendering.
    bool                                                        m_isStereo = false;

    // Pointer to the holographic camera these resources are for.
    HoloCam    m_holographicCamera = nullptr;
};

}


NAMESPACE_PARALLEL_END
