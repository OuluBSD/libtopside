#if X11IMPL
#define ScanCodeName COMBINE(KeySymToTSScancode, ABBR)
#define CLASSNAME COMBINE(ScrX11, ABBR)
#define CONTEXT COMBINE(COMBINE(X11, ABBR), Context)


bool CLASSNAME::EventsBase_Create(NativeEventsBase*& dev) {
	dev = new NativeEventsBase;
	return true;
}

void CLASSNAME::EventsBase_Destroy(NativeEventsBase*& dev) {
	delete dev;
}

void CLASSNAME::EventsBase_Visit(NativeEventsBase& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool CLASSNAME::EventsBase_Initialize(NativeEventsBase& ev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<CONTEXT>(1);
	ASSERT(ctx_);
	if (!ctx_) {RTLOG("error: could not find X11 context"); return false;}
	ev.ctx = &*ctx_->dev;
	
	
	return true;
}

bool CLASSNAME::EventsBase_PostInitialize(NativeEventsBase& ev, AtomBase& a) {
	if (!ev.ctx->win) {
		LOG("CLASSNAME::EventsBase_PostInitialize: error: context has no window");
		return false;
	}
	
	return true;
}

bool CLASSNAME::EventsBase_Start(NativeEventsBase& ev, AtomBase& a) {
	
	return true;
}

void CLASSNAME::EventsBase_Stop(NativeEventsBase& ev, AtomBase& a) {
	
}

void CLASSNAME::EventsBase_Uninitialize(NativeEventsBase& ev, AtomBase& a) {
	
}

bool CLASSNAME::EventsBase_Send(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.ev_sendable);
	if (!dev.ev_sendable)
		return false;
	

	Format fmt = out.GetFormat();
	RTLOG("CLASSNAME::EventsBase_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		out.seq = dev.seq++;
		CtrlEventCollection& dst = out.SetData<CtrlEventCollection>();
		dst <<= dev.ev;
		dev.ev_sendable = false;
	}
	
	return true;
}

bool CLASSNAME::EventsBase_Recv(NativeEventsBase& ev, AtomBase& a, int sink_ch, const Packet&) {
	
	return true;
}

int ConvertX11Keycode(CLASSNAME::NativeEventsBase&, int key);

void X11Events__PutKeyFlags(CLASSNAME::NativeEventsBase& dev, dword& key) {
	if (dev.is_lalt   || dev.is_ralt)		key |= K_ALT;
	if (dev.is_lshift || dev.is_rshift)		key |= K_SHIFT;
	if (dev.is_lctrl  || dev.is_rctrl)		key |= K_CTRL;
}

bool X11Events__Poll(CLASSNAME::NativeEventsBase& dev, AtomBase& a) {
	Vector<UPP::CtrlEvent>& evec = dev.ev;
	evec.SetCount(0);
	evec.Reserve(100);
	
	while (XPending(dev.ctx->display)) {
		UPP::CtrlEvent& e = evec.Add();
		
		XNextEvent(dev.ctx->display, &dev.xev);
		::KeySym xkey;
		Point mouse_pt;
		dword key = 0;
		int mouse_code = 0;
		
		switch (dev.xev.type) {
		
		case KeyPress:
			xkey = XLookupKeysym(&dev.xev.xkey, 0);
			switch (xkey) {
				//case XK_Escape:		break;
				case XK_Alt_L:			dev.is_lalt = true; break;
				case XK_Alt_R:			dev.is_ralt = true; break;
				case XK_Shift_L:		dev.is_lshift = true; break;
				case XK_Shift_R:		dev.is_rshift = true; break;
				case XK_Control_L:		dev.is_lctrl = true; break;
				case XK_Control_R:		dev.is_rctrl = true; break;
				default: break;
			}
			
			key = ConvertX11Keycode(dev, xkey);
			X11Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_KEYDOWN;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			return true;
		
		case KeyRelease:
			xkey = XLookupKeysym(&dev.xev.xkey, 0);
			switch (xkey) {
				//case XK_Escape:		break;
				case XK_Alt_L:			dev.is_lalt = false; break;
				case XK_Alt_R:			dev.is_ralt = false; break;
				case XK_Shift_L:		dev.is_lshift = false; break;
				case XK_Shift_R:		dev.is_rshift = false; break;
				case XK_Control_L:		dev.is_lctrl = false; break;
				case XK_Control_R:		dev.is_rctrl = false; break;
				default: break;
			}
			
			key = ConvertX11Keycode(dev, xkey);
			X11Events__PutKeyFlags(dev, key);
			
			key = key | K_KEYUP;
			
			e.type = EVENT_KEYUP;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			return true;
			
		case MotionNotify:
			mouse_pt = Point(dev.xev.xmotion.x, dev.xev.xmotion.y);
			key = 0;
			X11Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_MOUSEMOVE;
			e.value = key;
			e.pt = mouse_pt;
			
			dev.prev_mouse_pt = mouse_pt;
			return true;
		
			
		case ButtonPress:
		case ButtonRelease:
			mouse_code = 0;
			if (dev.xev.type == ButtonPress) {
				// single click only
				if (1) {
					if (dev.xev.xbutton.button == Button1)
						mouse_code = MOUSE_LEFTDOWN;
					else if (dev.xev.xbutton.button == Button2)
						mouse_code = MOUSE_MIDDLEDOWN;
					else if (dev.xev.xbutton.button == Button3)
						mouse_code = MOUSE_RIGHTDOWN;
				}
			}
			else {
				if (dev.xev.xbutton.button == Button1)
					mouse_code = MOUSE_LEFTUP;
				else if (dev.xev.xbutton.button == Button2)
					mouse_code = MOUSE_MIDDLEUP;
				else if (dev.xev.xbutton.button == Button3)
					mouse_code = MOUSE_RIGHTUP;
			}
		
			
			if (mouse_code) {
				mouse_pt = Point(dev.xev.xbutton.x, dev.xev.xbutton.y);
				X11Events__PutKeyFlags(dev, key);
				
				e.type = EVENT_MOUSE_EVENT;
				e.value = key;
				e.pt = mouse_pt;
				e.n = mouse_code;
				
				dev.prev_mouse_pt = mouse_pt;
				return true;
			}
			break;
			
        case ClientMessage:
            if (dev.xev.xclient.data.l[0] == dev.ctx->wmDeleteMessage) {
                dev.ctx->running = false;
                a.GetMachine().SetNotRunning();
                GetActiveMachine().SetNotRunning();
                XDestroyWindow(dev.ctx->display, dev.ctx->win);
            }
			return true;
			
		default:
			evec.Pop();
		}
	}
	
	return false;
}

bool CLASSNAME::EventsBase_IsReady(NativeEventsBase& dev, AtomBase& a, PacketIO& io) {
	bool b = io.full_src_mask == 0;
	if (b) {
		if (X11Events__Poll(dev, a)) {
			dev.ev_sendable = true;
		}
		else {
			dev.ev_sendable = false;
			b = false;
		}
	}
	RTLOG("CLASSNAME::EventsBase_IsReady: " << (b ? "true" : "false"));
	return b;
}


void CLASSNAME::EventsBase_Finalize(NativeEventsBase& ev, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool CLASSNAME::EventsBase_NegotiateSinkFormat(NativeEventsBase& ev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	
	return false;
}






static const struct {
    int keycode;
    int scancode;
} ScanCodeName[] = {
    { XK_Return, '\r' },
    { XK_Escape, '\x1B' },
    { XK_BackSpace, '\b' },
    { XK_Tab, '\t' },
    { XK_Caps_Lock, TS_SCANCODE_CAPSLOCK },
    { XK_F1, TS_SCANCODE_F1 },
    { XK_F2, TS_SCANCODE_F2 },
    { XK_F3, TS_SCANCODE_F3 },
    { XK_F4, TS_SCANCODE_F4 },
    { XK_F5, TS_SCANCODE_F5 },
    { XK_F6, TS_SCANCODE_F6 },
    { XK_F7, TS_SCANCODE_F7 },
    { XK_F8, TS_SCANCODE_F8 },
    { XK_F9, TS_SCANCODE_F9 },
    { XK_F10, TS_SCANCODE_F10 },
    { XK_F11, TS_SCANCODE_F11 },
    { XK_F12, TS_SCANCODE_F12 },
    { XK_Print, TS_SCANCODE_PRINTSCREEN },
    { XK_Scroll_Lock, TS_SCANCODE_SCROLLLOCK },
    { XK_Pause, TS_SCANCODE_PAUSE },
    { XK_Insert, TS_SCANCODE_INSERT },
    { XK_Home, TS_SCANCODE_HOME },
    { XK_Prior, TS_SCANCODE_PAGEUP },
    { XK_Delete, TS_SCANCODE_DELETE },
    { XK_End, TS_SCANCODE_END },
    { XK_Next, TS_SCANCODE_PAGEDOWN },
    { XK_Right, TS_SCANCODE_RIGHT },
    { XK_Left, TS_SCANCODE_LEFT },
    { XK_Down, TS_SCANCODE_DOWN },
    { XK_Up, TS_SCANCODE_UP },
    { XK_Num_Lock, TS_SCANCODE_NUMLOCKCLEAR },
    { XK_KP_Divide, TS_SCANCODE_KP_DIVIDE },
    { XK_KP_Multiply, TS_SCANCODE_KP_MULTIPLY },
    { XK_KP_Subtract, TS_SCANCODE_KP_MINUS },
    { XK_KP_Add, TS_SCANCODE_KP_PLUS },
    { XK_KP_Enter, TS_SCANCODE_KP_ENTER },
    { XK_KP_Delete, TS_SCANCODE_KP_PERIOD },
    { XK_KP_End, TS_SCANCODE_KP_1 },
    { XK_KP_Down, TS_SCANCODE_KP_2 },
    { XK_KP_Next, TS_SCANCODE_KP_3 },
    { XK_KP_Left, TS_SCANCODE_KP_4 },
    { XK_KP_Begin, TS_SCANCODE_KP_5 },
    { XK_KP_Right, TS_SCANCODE_KP_6 },
    { XK_KP_Home, TS_SCANCODE_KP_7 },
    { XK_KP_Up, TS_SCANCODE_KP_8 },
    { XK_KP_Prior, TS_SCANCODE_KP_9 },
    { XK_KP_Insert, TS_SCANCODE_KP_0 },
    { XK_KP_Decimal, TS_SCANCODE_KP_PERIOD },
    { XK_KP_1, TS_SCANCODE_KP_1 },
    { XK_KP_2, TS_SCANCODE_KP_2 },
    { XK_KP_3, TS_SCANCODE_KP_3 },
    { XK_KP_4, TS_SCANCODE_KP_4 },
    { XK_KP_5, TS_SCANCODE_KP_5 },
    { XK_KP_6, TS_SCANCODE_KP_6 },
    { XK_KP_7, TS_SCANCODE_KP_7 },
    { XK_KP_8, TS_SCANCODE_KP_8 },
    { XK_KP_9, TS_SCANCODE_KP_9 },
    { XK_KP_0, TS_SCANCODE_KP_0 },
    { XK_KP_Decimal, TS_SCANCODE_KP_PERIOD },
    { XK_Hyper_R, TS_SCANCODE_APPLICATION },
    { XK_KP_Equal, TS_SCANCODE_KP_EQUALS },
    { XK_F13, TS_SCANCODE_F13 },
    { XK_F14, TS_SCANCODE_F14 },
    { XK_F15, TS_SCANCODE_F15 },
    { XK_F16, TS_SCANCODE_F16 },
    { XK_F17, TS_SCANCODE_F17 },
    { XK_F18, TS_SCANCODE_F18 },
    { XK_F19, TS_SCANCODE_F19 },
    { XK_F20, TS_SCANCODE_F20 },
    { XK_F21, TS_SCANCODE_F21 },
    { XK_F22, TS_SCANCODE_F22 },
    { XK_F23, TS_SCANCODE_F23 },
    { XK_F24, TS_SCANCODE_F24 },
    { XK_Execute, TS_SCANCODE_EXECUTE },
    { XK_Help, TS_SCANCODE_HELP },
    { XK_Menu, TS_SCANCODE_MENU },
    { XK_Select, TS_SCANCODE_SELECT },
    { XK_Cancel, TS_SCANCODE_STOP },
    { XK_Redo, TS_SCANCODE_AGAIN },
    { XK_Undo, TS_SCANCODE_UNDO },
    { XK_Find, TS_SCANCODE_FIND },
    { XK_KP_Separator, TS_SCANCODE_KP_COMMA },
    { XK_Sys_Req, TS_SCANCODE_SYSREQ },
    { XK_Control_L, TS_SCANCODE_LCTRL },
    { XK_Shift_L, TS_SCANCODE_LSHIFT },
    { XK_Alt_L, TS_SCANCODE_LALT },
    { XK_Meta_L, TS_SCANCODE_LGUI },
    { XK_Super_L, TS_SCANCODE_LGUI },
    { XK_Control_R, TS_SCANCODE_RCTRL },
    { XK_Shift_R, TS_SCANCODE_RSHIFT },
    { XK_Alt_R, TS_SCANCODE_RALT },
    { XK_ISO_Level3_Shift, TS_SCANCODE_RALT },
    { XK_Meta_R, TS_SCANCODE_RGUI },
    { XK_Super_R, TS_SCANCODE_RGUI },
    { XK_Mode_switch, TS_SCANCODE_MODE },
    { XK_period, TS_SCANCODE_PERIOD },
    { XK_comma, TS_SCANCODE_COMMA },
    { XK_slash, TS_SCANCODE_SLASH },
    { XK_backslash, TS_SCANCODE_BACKSLASH },
    { XK_minus, TS_SCANCODE_MINUS },
    { XK_equal, TS_SCANCODE_EQUALS },
    { XK_space, TS_SCANCODE_SPACE },
    { XK_grave, TS_SCANCODE_GRAVE },
    { XK_apostrophe, TS_SCANCODE_APOSTROPHE },
    { XK_bracketleft, TS_SCANCODE_LEFTBRACKET },
    { XK_bracketright, TS_SCANCODE_RIGHTBRACKET },
};

#define TS_arraysize(array)    (sizeof(array)/sizeof(array[0]))

int ConvertX11Keycode(CLASSNAME::NativeEventsBase& dev, int keycode)
{
    for (int i = 0; i < TS_arraysize(ScanCodeName); ++i) {
        if (keycode == ScanCodeName[i].keycode) {
            return ScanCodeName[i].scancode;
        }
    }
    return keycode;
}

#endif



#if WINIMPL

#endif

#if WIND11IMPL


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
DeviceResources::DeviceResources()
{

};


//-----------------------------------------------------------------------------
//
// Method 1: Create device and swap chain at the same time.
//
// Benefit:  It's easy.
// Drawback: You have to create a new device, and therefore
//           reload all DirectX device resources, every time
//           you recreate the swap chain.
//
//-----------------------------------------------------------------------------
HRESULT DeviceResources::CreateDeviceResources(HWND hWnd)
{
    HRESULT hr = S_OK;

    D3D_FEATURE_LEVEL levels [] = {
        D3D_FEATURE_LEVEL_9_1,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1
    };

    // This flag adds support for surfaces with a color-channel ordering different
    // from the API default. It is required for compatibility with Direct2D.
    UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(DEBUG) || defined(_DEBUG)
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    desc.Windowed = TRUE;
    desc.BufferCount = 2;
    desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;      //multisampling setting
    desc.SampleDesc.Quality = 0;    //vendor-specific flag
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    desc.OutputWindow = hWnd;

    Microsoft::WRL::ComPtr<ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

    hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        deviceFlags,
        levels,
        ARRAYSIZE(levels),
        D3D11_SDK_VERSION,
        &desc,
        swapChain.GetAddressOf(),
        device.GetAddressOf(),
        &m_featureLevel,
        context.GetAddressOf()
        );

    device.As(&m_pd3dDevice);
    context.As(&m_pd3dDeviceContext);
    swapChain.As(&m_pDXGISwapChain);

    // Configure the back buffer and viewport.
    hr = m_pDXGISwapChain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**) &m_pBackBuffer);

    m_pBackBuffer->GetDesc(&m_bbDesc);

    ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
    m_viewport.Height = (float) m_bbDesc.Height;
    m_viewport.Width = (float) m_bbDesc.Width;
    m_viewport.MinDepth = 0;
    m_viewport.MaxDepth = 1;


    m_pd3dDeviceContext->RSSetViewports(
        1,
        &m_viewport
        );

    hr = m_pd3dDevice->CreateRenderTargetView(
        m_pBackBuffer.Get(),
        nullptr,
        m_pRenderTarget.GetAddressOf()
        );

    return hr;
}

//-----------------------------------------------------------------------------
//
// Method 2: Create the device and swap chain separately.
//
// Benefit:  You can recreate the swap chain on-the-fly.
// Drawback: Slight increase in your initial investment.
//
//-----------------------------------------------------------------------------
HRESULT DeviceResources::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_9_1,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1
    };

    // This flag adds support for surfaces with a color-channel ordering different
    // from the API default. It is required for compatibility with Direct2D.
    UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(DEBUG) || defined(_DEBUG)
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // Create the Direct3D 11 API device object and a corresponding context.
    Microsoft::WRL::ComPtr<ID3D11Device>        device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

    hr = D3D11CreateDevice(
        nullptr,                    // Specify nullptr to use the default adapter.
        D3D_DRIVER_TYPE_HARDWARE,   // Create a device using the hardware graphics driver.
        0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
        deviceFlags,                // Set debug and Direct2D compatibility flags.
        levels,                     // List of feature levels this app can support.
        ARRAYSIZE(levels),          // Size of the list above.
        D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
        &device,                    // Returns the Direct3D device created.
        &m_featureLevel,            // Returns feature level of device created.
        &context                    // Returns the device immediate context.
        );

    if (FAILED(hr))
    {
        // Handle device interface creation failure if it occurs.
        // For example, reduce the feature level requirement, or fail over 
        // to WARP rendering.
    }

    // Store pointers to the Direct3D 11.1 API device and immediate context.
    device.As(&m_pd3dDevice);
    context.As(&m_pd3dDeviceContext);

    return hr;
}

//-----------------------------------------------------------------------------
// Method 2, continued. Creates the swap chain.
//-----------------------------------------------------------------------------
HRESULT DeviceResources::CreateWindowResources(HWND hWnd)
{
    HRESULT hr = S_OK;


    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    desc.Windowed = TRUE; // Sets the initial state of full-screen mode.
    desc.BufferCount = 2;
    desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;      //multisampling setting
    desc.SampleDesc.Quality = 0;    //vendor-specific flag
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    desc.OutputWindow = hWnd;

    // Create the DXGI device object to use in other factories, such as Direct2D.
    Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
    m_pd3dDevice.As(&dxgiDevice);

    // Create swap chain.
    Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
    Microsoft::WRL::ComPtr<IDXGIFactory> factory;

    hr = dxgiDevice->GetAdapter(&adapter);

    if (SUCCEEDED(hr))
    {
        adapter->GetParent(IID_PPV_ARGS(&factory));

        hr = factory->CreateSwapChain(
            m_pd3dDevice.Get(),
            &desc,
            &m_pDXGISwapChain
            );
    }

    // Configure the back buffer, stencil buffer, and viewport.
    hr = ConfigureBackBuffer();

    return hr;
}

HRESULT DeviceResources::ConfigureBackBuffer()
{
    HRESULT hr = S_OK;

    hr = m_pDXGISwapChain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**) &m_pBackBuffer);

    hr = m_pd3dDevice->CreateRenderTargetView(
        m_pBackBuffer.Get(),
        nullptr,
        m_pRenderTarget.GetAddressOf()
        );

    m_pBackBuffer->GetDesc(&m_bbDesc);

    // Create a depth-stencil view for use with 3D rendering if needed.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        static_cast<UINT> (m_bbDesc.Width),
        static_cast<UINT> (m_bbDesc.Height),
        1, // This depth stencil view has only one texture.
        1, // Use a single mipmap level.
        D3D11_BIND_DEPTH_STENCIL
        );

    m_pd3dDevice->CreateTexture2D(
        &depthStencilDesc,
        nullptr,
        &m_pDepthStencil
        );

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

    m_pd3dDevice->CreateDepthStencilView(
        m_pDepthStencil.Get(),
        &depthStencilViewDesc,
        &m_pDepthStencilView
        );


    ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
    m_viewport.Height = (float) m_bbDesc.Height;
    m_viewport.Width = (float) m_bbDesc.Width;
    m_viewport.MinDepth = 0;
    m_viewport.MaxDepth = 1;
    
    m_pd3dDeviceContext->RSSetViewports(
        1,
        &m_viewport
        );

    return hr;
}

HRESULT DeviceResources::ReleaseBackBuffer()
{
    HRESULT hr = S_OK;

    // Release the render target view based on the back buffer:
    m_pRenderTarget.Reset();

    // Release the back buffer itself:
    m_pBackBuffer.Reset();

    // The depth stencil will need to be resized, so release it (and view):
    m_pDepthStencilView.Reset();
    m_pDepthStencil.Reset();

    // After releasing references to these resources, we need to call Flush() to 
    // ensure that Direct3D also releases any references it might still have to
    // the same resources - such as pipeline bindings.
    m_pd3dDeviceContext->Flush();

    return hr;
}

HRESULT DeviceResources::GoFullScreen()
{
    HRESULT hr = S_OK;

    hr = m_pDXGISwapChain->SetFullscreenState(TRUE, NULL);

    // Swap chains created with the DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL flag need to
    // call ResizeBuffers in order to realize a full-screen mode switch. Otherwise, 
    // your next call to Present will fail.

    // Before calling ResizeBuffers, you have to release all references to the back 
    // buffer device resource.
    ReleaseBackBuffer();

    // Now we can call ResizeBuffers.
    hr = m_pDXGISwapChain->ResizeBuffers(
        0,                   // Number of buffers. Set this to 0 to preserve the existing setting.
        0, 0,                // Width and height of the swap chain. Set to 0 to match the screen resolution.
        DXGI_FORMAT_UNKNOWN, // This tells DXGI to retain the current back buffer format.
        0
        );

    // Then we can recreate the back buffer, depth buffer, and so on.
    hr = ConfigureBackBuffer();

    return hr;
}

HRESULT DeviceResources::GoWindowed()
{
    HRESULT hr = S_OK;

    hr = m_pDXGISwapChain->SetFullscreenState(FALSE, NULL);

    // Swap chains created with the DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL flag need to
    // call ResizeBuffers in order to realize a change to windowed mode. Otherwise, 
    // your next call to Present will fail.

    // Before calling ResizeBuffers, you have to release all references to the back 
    // buffer device resource.
    ReleaseBackBuffer();

    // Now we can call ResizeBuffers.
    hr = m_pDXGISwapChain->ResizeBuffers(
        0,                   // Number of buffers. Set this to 0 to preserve the existing setting.
        0, 0,                // Width and height of the swap chain. MUST be set to a non-zero value. For example, match the window size.
        DXGI_FORMAT_UNKNOWN, // This tells DXGI to retain the current back buffer format.
        0
        );

    // Then we can recreate the back buffer, depth buffer, and so on.
    hr = ConfigureBackBuffer();

    return hr;
}

//-----------------------------------------------------------------------------
// Returns the aspect ratio of the back buffer.
//-----------------------------------------------------------------------------
float DeviceResources::GetAspectRatio()
{
    return static_cast<float>(m_bbDesc.Width) / static_cast<float>(m_bbDesc.Height);
}

//-----------------------------------------------------------------------------
// Present frame:
// Show the frame on the primary surface.
//-----------------------------------------------------------------------------
void DeviceResources::Present()
{
    m_pDXGISwapChain->Present(1, 0);
}


//-----------------------------------------------------------------------------
// Destructor.
//-----------------------------------------------------------------------------
DeviceResources::~DeviceResources()
{

}











LRESULT CALLBACK WinD11_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT(active_ScrWinD11_NativeSinkDevice);
	ScrWinD11::NativeSinkDevice& dev = *active_ScrWinD11_NativeSinkDevice;
	
    switch (uMsg)
    {
    
    case WM_CREATE: {
            //RECT r;
            //GetClientRect(hWnd, &r);
            //SetWinD11dowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(new graphic_buffers(r.right - r.left, r.bottom - r.top)));
            //SetTimer(dev.ctx->hwnd, kTimerID, 1, NULL);
        }
        break;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        
        dev.atom->GetMachine().SetNotRunning();
        
        return 0;

	case WM_SIZE:
		word width = lParam & 0xFFFF;
		word height = (lParam >> 16) & 0xFFFF;
		if (!TS::default_width) {
			TS::default_width = width;
			TS::default_height = height;
		}
		dev.sz.cx = width;
		dev.sz.cy = height;
		
		// TODO also NativeEventsBase
		
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


#endif
