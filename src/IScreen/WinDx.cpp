#include "IScreen.h"

#if defined flagWIN32 && defined flagDX


#include <IGraphics/dxstdafx.h>
#include <windows.h>


/*
	Info: https://learn.microsoft.com/en-us/windows/win32/direct3dgetstarted/complete-code-sample-for-using-a-corewindow-with-directx
*/

NAMESPACE_PARALLEL_BEGIN


class DeviceResources
{
public:
    DeviceResources();
    ~DeviceResources();

    HRESULT CreateDeviceResources( HWND hWnd );
    HRESULT CreateDeviceResources( );
    HRESULT CreateWindowResources( HWND hWnd );

    HRESULT ConfigureBackBuffer();
    HRESULT ReleaseBackBuffer();
    HRESULT GoFullScreen();
    HRESULT GoWindowed();

    float GetAspectRatio();

    ID3D11Device*           GetDevice() { return m_pd3dDevice.Get(); };
    ID3D11DeviceContext*    GetDeviceContext() { return m_pd3dDeviceContext.Get(); };
    ID3D11RenderTargetView* GetRenderTarget() { return m_pRenderTarget.Get(); }
    ID3D11DepthStencilView* GetDepthStencil() { return m_pDepthStencilView.Get(); }
    
    void Present();

private:

    //-----------------------------------------------------------------------------
    // Direct3D device
    //-----------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Device>        m_pd3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3dDeviceContext; // immediate context
    Microsoft::WRL::ComPtr<IDXGISwapChain>      m_pDXGISwapChain;


    //-----------------------------------------------------------------------------
    // DXGI swap chain device resources
    //-----------------------------------------------------------------------------
    Microsoft::WRL::ComPtr < ID3D11Texture2D>        m_pBackBuffer;
    Microsoft::WRL::ComPtr < ID3D11RenderTargetView> m_pRenderTarget;


    //-----------------------------------------------------------------------------
    // Direct3D device resources for the depth stencil
    //-----------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_pDepthStencil;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;


    //-----------------------------------------------------------------------------
    // Direct3D device metadata and device resource metadata
    //-----------------------------------------------------------------------------
    D3D_FEATURE_LEVEL       m_featureLevel;
    D3D11_TEXTURE2D_DESC    m_bbDesc;
    D3D11_VIEWPORT          m_viewport;
};




struct ScrWinDx::NativeContext {
    bool running = false;
    //void* WinDx;
    
    HRESULT CreateDesktopWindow();
    
    HWND GetWindowHandle() { return hwnd; };

    static LRESULT CALLBACK StaticWindowProc(
        HWND hWnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
        );

    /*HRESULT Run(
        std::shared_ptr<DeviceResources> deviceResources,
        std::shared_ptr<Renderer> renderer
        );*/
	
	
    std::shared_ptr<DeviceResources> deviceResources;
    //std::shared_ptr<Renderer> renderer;
    
	HINSTANCE		m_hInstance;
	std::string		m_windowClassName;
    HWND			hwnd;
    HMENU			m_hMenu;
    RECT			m_rc;
	
	
};









struct ScrWinDx::NativeSinkDevice {
    WNDCLASS wc = { };
    String title;
	const char* CLASS_NAME = "ScrWinDx_NativeWinDxdow";
    
    //GfxAccelAtom<WinDxGfx> accel;
    NativeContext* ctx;
    AtomBase* atom = 0;
    Size sz;
    
};

struct ScrWinDx::NativeEventsBase {
    NativeContext* ctx;
    int time;
    dword seq;
    Vector<UPP::CtrlEvent> ev;
    Size sz;
    bool ev_sendable;
    bool is_lalt;
    bool is_ralt;
    bool is_lshift;
    bool is_rshift;
    bool is_lctrl;
    bool is_rctrl;
    Point prev_mouse_pt;
};


ScrWinDx::NativeSinkDevice* active_ScrWinDx_NativeSinkDevice;
ScrWinDx::NativeEventsBase* active_ScrWinDx_NativeEventsBase;

LRESULT CALLBACK WinDx_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);





HRESULT ScrWinDx::NativeContext::CreateDesktopWindow() {
	// Window resources are dealt with here.
    
    if(m_hInstance == NULL)
        m_hInstance = (HINSTANCE)GetModuleHandle(NULL);

    HICON hIcon = NULL;
    //WCHAR szExePath[MAX_PATH];
    //GetModuleFileName(NULL, szExePath, MAX_PATH);
    
    // If the icon is NULL, then use the first one found in the exe
    //if(hIcon == NULL)
    //    hIcon = ExtractIcon(m_hInstance, szExePath, 0);

    // Register the windows class
    WNDCLASS wndClass;
    wndClass.style = CS_DBLCLKS;
    wndClass.lpfnWndProc = WinDx_WindowProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = hIcon;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = m_windowClassName.c_str();

    if(!RegisterClass(&wndClass))
    {
        DWORD dwError = GetLastError();
        if(dwError != ERROR_CLASS_ALREADY_EXISTS)
            return HRESULT_FROM_WIN32(dwError);
    }
    
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;

    // No menu in this example.
    m_hMenu = NULL;

    // This example uses a non-resizable 1280 by 720 viewport for simplicity.
    int nDefaultWidth = 1280;
    int nDefaultHeight = 720;
    SetRect(&m_rc, 0, 0, nDefaultWidth, nDefaultHeight);
    AdjustWindowRect(
        &m_rc,
        WS_OVERLAPPEDWINDOW,
        (m_hMenu != NULL) ? true : false
        );

    // Create the window for our viewport.
    hwnd = CreateWindow(
        m_windowClassName.c_str(),
        "Cube11",
        WS_OVERLAPPEDWINDOW,
        x, y,
        (m_rc.right-m_rc.left), (m_rc.bottom-m_rc.top),
        0,
        m_hMenu,
        m_hInstance,
        0
        );

    if(hwnd == NULL)
    {
        DWORD dwError = GetLastError();
        return HRESULT_FROM_WIN32(dwError);
    }

    return S_OK;
}










bool ScrWinDx::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void ScrWinDx::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
}

void ScrWinDx::SinkDevice_Visit(NativeSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrWinDx::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<WinDxContext>(1);
	if (!ctx_) {RTLOG("error: could not find WinDx context"); return false;}
	auto& ctx = *ctx_->dev;
	dev.ctx = &ctx;
	dev.atom = &a;
	
	if (active_ScrWinDx_NativeSinkDevice) {
		LOG("rWinDx::SinkDevice_Initialize: error: only one  can be opened");
		return false;
	}
	active_ScrWinDx_NativeSinkDevice = &dev;
	
	a.SetDependency(&*ctx_);
	
	bool fullscreen = ws.GetBool(".fullscreen", false);
	
	
	// Begin initialization
	
	ctx.m_windowClassName = "Direct3DWindowClass";
    ctx.m_hInstance = NULL;
    
    // Create a window.
    HRESULT hr = ctx.CreateDesktopWindow();

    if (!SUCCEEDED(hr)) {
        LOG("ScrWinDx::SinkDevice_Initialize: error: window creation failed");
        return false;
    }
    
    // Instantiate the device manager class.
    ctx.deviceResources = std::shared_ptr<DeviceResources>(new DeviceResources());
    
    // Create device resources.
    ctx.deviceResources->CreateDeviceResources();
	
    // Instantiate the renderer.
    //ctx.renderer = std::shared_ptr<Renderer>(new Renderer(ctx.deviceResources));
    //renderer->CreateDeviceDependentResources();
	
    // We have a window, so initialize window size-dependent resources.
    ctx.deviceResources->CreateWindowResources(ctx.GetWindowHandle());
    //ctx.renderer->CreateWindowSizeDependentResources();
	
    // Go full-screen.
    if (fullscreen)
		ctx.deviceResources->GoFullScreen();
	
    // Whoops! We resized the "window" when we went full-screen. Better
    // tell the renderer.
    //ctx.renderer->CreateWindowSizeDependentResources();
	
    // Run the program.
    /*hr = ctx.winMain->Run(ctx.deviceResources, ctx.renderer);
    
    if (!SUCCEEDED(hr)) {
        LOG("ScrWinDx::SinkDevice_Initialize: error: could not run the program");
        return false;
    }*/
    
    
	return true;
}

bool ScrWinDx::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool ScrWinDx::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	if (!IsWindowVisible(dev.ctx->hwnd))
		ShowWindow(dev.ctx->hwnd, SW_SHOWNORMAL);
	
	/*LPRECT lp_rect {0};
	
	// Crash
	if (GetWinDxdowRect(dev.ctx->hwnd, lp_rect)) {
		int width = lp_rect->right - lp_rect->left;
		int height = lp_rect->bottom - lp_rect->top;
		ASSERT(width > 0 && height > 0);
		
		TS::default_width = width;
		TS::default_height = height;
	}*/
	
	return true;
}

void ScrWinDx::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	auto& ctx = *dev.ctx;
	
	
	ShowWindow(dev.ctx->hwnd, SW_HIDE);
	
}

void ScrWinDx::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	a.SetDependency(0);
	
	auto& ctx = *dev.ctx;
	
	CloseWindow(dev.ctx->hwnd);
	
	active_ScrWinDx_NativeSinkDevice = 0;
}

bool ScrWinDx::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	TODO //return dev.accel.Recv(ch_i, p);
}

void ScrWinDx::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
	
}

bool ScrWinDx::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool ScrWinDx::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	TODO
	return false;
}

bool ScrWinDx::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io) {
	// Run the message loop.
    MSG msg = { };
    while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return true;
}







bool ScrWinDx::Context_Create(NativeContext*& dev) {
	dev = new NativeContext;
	return true;
}

void ScrWinDx::Context_Destroy(NativeContext*& dev) {
	delete dev;
}

void ScrWinDx::Context_Visit(NativeContext& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrWinDx::Context_Initialize(NativeContext& ctx, AtomBase& a, const Script::WorldState& ws) {
	return true;
}

bool ScrWinDx::Context_PostInitialize(NativeContext& ctx, AtomBase& a) {
	return true;
}

bool ScrWinDx::Context_Start(NativeContext& ctx, AtomBase& a) {
	return true;
}

void ScrWinDx::Context_Stop(NativeContext& ctx, AtomBase& a) {
	
}

void ScrWinDx::Context_Uninitialize(NativeContext& ctx, AtomBase& a) {
	
}

bool ScrWinDx::Context_Send(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return false;
}

bool ScrWinDx::Context_Recv(NativeContext& ctx, AtomBase& a, int sink_ch, const Packet&) {
	return false;
}

void ScrWinDx::Context_Finalize(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrWinDx::Context_NegotiateSinkFormat(NativeContext& ctx, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}

bool ScrWinDx::Context_IsReady(NativeContext& dev, AtomBase&, PacketIO& io) {
	return true;
}




#define ABBR
#define WINDXIMPL 1
#include "Impl.inl"
#undef ABBR



NAMESPACE_PARALLEL_END
#endif
