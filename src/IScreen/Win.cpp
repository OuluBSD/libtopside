#include "IScreen.h"

#if (defined flagWIN32)


#include <windows.h>


/*#ifdef flagMSC
	#include <Windowsx.h>
#endif
#include <d2d1.h>
#pragma comment(lib, "d2d1")*/


/*
	Note: to transfer data pointers via hwnd see https://stackoverflow.com/questions/70620450/draw-raw-array-of-pixels-onto-a-window-c-winapi
*/

NAMESPACE_PARALLEL_BEGIN

struct ScrWinSinkBase {
	HRESULT CreateGraphicsResources();
	void DiscardGraphicsResources();
	void OnPaint();
	void Resize();
	void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
	void OnLButtonUp();
	void OnMouseMove(int pixelX, int pixelY, DWORD flags);
	void OnKeyDown(UINT vkey);
	
    HBITMAP hbm;
	byte* data = 0;
	int bytes_per_line = 0;
	int bits_per_pixel = 0;
	Size data_sz;
};

struct ScrWin::NativeContext {
    bool running = false;
    union {
		HWND hwnd;
		void* win;
    };
};

struct ScrWin::NativeSinkDevice : ScrWinSinkBase {
    WNDCLASS wc = { };
    String title;
	const char* CLASS_NAME = "ScrWin_NativeWindow";
    
    NativeContext* ctx;
    ProgImage pi;
    One<ImageDraw> id;
    Size sz;
    AtomBase* atom = 0;
};

struct ScrWin::NativeEventsBase {
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


ScrWin::NativeSinkDevice* active_ScrWin_NativeSinkDevice;
ScrWin::NativeEventsBase* active_ScrWin_NativeEventsBase;


LRESULT CALLBACK Win_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool ScrWin::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void ScrWin::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
}

void ScrWin::SinkDevice_Visit(NativeSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrWin::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<WinContext>(1);
	if (!ctx_) {RTLOG("error: could not find Win context"); return false;}
	auto& ctx = *ctx_->dev;
	dev.ctx = &ctx;
	dev.atom = &a;
	
	if (active_ScrWin_NativeSinkDevice) {
		LOG("rWin::SinkDevice_Initialize: error: only one  can be opened");
		return false;
	}
	active_ScrWin_NativeSinkDevice = &dev;
	
	a.SetDependency(&*ctx_);
	
	HINSTANCE instance = (HINSTANCE)GetWin32Instance();
	if (!instance) {
		LOG("ScrWin::SinkDevice_Initialize: error: no gui instance");
		return false;
	}
	
	
	dev.title = ws.GetString(".title", "libtopside");
	dev.wc.lpfnWndProc   = Win_WindowProc;
    dev.wc.hInstance     = instance;
    dev.wc.lpszClassName = dev.CLASS_NAME;
    
    RegisterClass(&dev.wc);
    
    
    dev.sz.cx = ws.GetInt(".width", 1280);
    dev.sz.cy = ws.GetInt(".height", 720);
    
    dev.ctx->hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        dev.CLASS_NAME,                 // Window class
        dev.title.Begin(),              // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT,
        //CW_USEDEFAULT, CW_USEDEFAULT,
        dev.sz.cx, dev.sz.cy,

        NULL,         // Parent window
        NULL,         // Menu
        instance,     // Instance handle
        NULL          // Additional application data
        );

    if (dev.ctx->hwnd == NULL) {
        return 0;
    }
    
    
    // Create graphics buffer
    HDC hdcScreen = GetDC(NULL);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = dev.sz.cx;
    bmi.bmiHeader.biHeight = -dev.sz.cy; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    dev.hbm = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**)&dev.data, NULL, NULL);

    ReleaseDC(NULL, hdcScreen);
    
    
	int src_ch = a.FindSinkWithValDev(VD(CENTER,VIDEO));
	if (src_ch < 0)
		return false;
    Format fmt = a.GetSink()->GetValue(src_ch).GetFormat();
    VideoFormat& vfmt = fmt;
    vfmt.SetType(LightSampleFD::RGB_U8_LE);
    a.GetSink()->GetValue(src_ch).SetFormat(fmt);
    dev.bits_per_pixel = bmi.bmiHeader.biBitCount;
    
	return true;
}

bool ScrWin::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool ScrWin::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	ShowWindow(dev.ctx->hwnd, SW_SHOWNORMAL);
	
	/*LPRECT lp_rect {0};
	
	// Crash
	if (GetWindowRect(dev.ctx->hwnd, lp_rect)) {
		int width = lp_rect->right - lp_rect->left;
		int height = lp_rect->bottom - lp_rect->top;
		ASSERT(width > 0 && height > 0);
		
		TS::default_width = width;
		TS::default_height = height;
	}*/
	
	return true;
}

void ScrWin::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	auto& ctx = *dev.ctx;
	
	
	ShowWindow(dev.ctx->hwnd, SW_HIDE);
	
}

void ScrWin::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	a.SetDependency(0);
	
	auto& ctx = *dev.ctx;
	
	CloseWindow(dev.ctx->hwnd);
	
	active_ScrWin_NativeSinkDevice = 0;
}

bool ScrWin::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	auto& ctx = *dev.ctx;
	
	Format fmt = in->GetFormat();
	if (fmt.IsVideo()) {
		const Vector<byte>& pixmap = in->Data();
	    
		VideoFormat& vfmt = fmt;
		int frame_sz = vfmt.GetFrameSize();
		ASSERT(pixmap.GetCount() == frame_sz);
		
		dev.data_sz.cx = vfmt.res[0];
		dev.data_sz.cy = vfmt.res[1];
	    //dev.data = (const byte*)pixmap.Begin();
	    dev.bytes_per_line = vfmt.res[0] * vfmt.GetPackedCount();
	    
	    int scr_bpp = dev.bits_per_pixel / 8;
	    memcpy(dev.data, pixmap.Begin(), frame_sz);
	    
	    ASSERT(scr_bpp == vfmt.GetPackedCount());
	    ASSERT(frame_sz == dev.data_sz.GetArea() * scr_bpp);
	    
	    InvalidateRect(dev.ctx->hwnd, NULL, FALSE);
	    
	    /*ASSERT(dev.data_sz == dev.sz);
	    if (dev.data_sz != dev.sz) {
	        LOG("ScrWin::SinkDevice_ProcessPacket: error: invalid resolution");
	        return false;
	    }*/
	    
	}
	else if (fmt.IsProg()) {
		TODO
		/*
		Size sz(ctx.fb->width, ctx.fb->height);
		ASSERT(!sz.IsEmpty());
		if (dev.id.IsEmpty()) {
			#if IS_UPP_CORE
			dev.id = new ImageDraw(sz);
			#else
			dev.id.Create(sz, 4);
			#endif
		}
		
		InternalPacketData& data = in->GetData<InternalPacketData>();
		DrawCommand* begin = (DrawCommand*)data.ptr;
		
		#if 1
		{
			DrawCommand* it = begin;
			int i = 0;
			while (it) {
				LOG(i++ << " " << it->ToString());
				it = it->next;
			}
		}
		#endif
		
		while (begin && begin->type != DRAW_BIND_WINDOW) begin = begin->next;
		if (!begin) {
			LOG("HalSdl::CenterVideoSinkDevice_Recv: error: no ptr");
			return false;
		}
		ASSERT(begin->type == DRAW_BIND_WINDOW);
		
		DrawCommand* end = begin;
		while (end) {
			if (end->type == DRAW_UNBIND_WINDOW) {
				end = end->next;
				break;
			}
			end = end->next;
		}
		
		dev.id->DrawRect(sz, Black());
		dev.pi.Paint(begin, end, *dev.id);
		
		#if IS_UPP_CORE
		TODO
		#else
		dev.id->SwapRG();
		
		ASSERT(ctx.fb);
		ASSERT(!ctx.fb->data);
		int bpp = dev.id->GetStride();
		int id_len = dev.id->Data().GetCount();
	    ctx.fb->data = (char*)(const unsigned char*)dev.id->Data().Begin();
	    ctx.fb->bytes_per_line = sz.cx * bpp;
	    
	    int scr_bpp = ctx.fb->bits_per_pixel / 8;
	    int img_bpp = bpp;
	    //ASSERT(scr_bpp == img_bpp);
	    
	    ASSERT(sz.cx == ctx.fb->width);
	    ASSERT(sz.cy == ctx.fb->height);
	    if (sz.cx != ctx.fb->width || sz.cy != ctx.fb->height) {
	        LOG("ScrWin::SinkDevice_ProcessPacket: error: invalid resolution");
	        return false;
	    }
	    
	    int rc = XPutImage(	ctx.display,
							ctx.win,
							ctx.gc,
							ctx.fb,
							0,0,
							0,0,
							sz.cx,
							sz.cy);
	    
	    if (rc == BadMatch) {
	        LOG("ScrWin::SinkDevice_ProcessPacket: error: XPutImage returned BadMatch");
	        ctx.fb->data = 0;
	        return false;
	    }
	    #endif
	    
		XFlush(ctx.display);
		//XSync(dev.display, False);
		
		ctx.fb->data = 0;
		*/
		return true;
	}
	
	return true;
}

void ScrWin::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
	
}

bool ScrWin::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool ScrWin::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	TODO
	return false;
}

bool ScrWin::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io) {
	// Run the message loop.
    MSG msg = { };
    while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return true;
}







bool ScrWin::Context_Create(NativeContext*& dev) {
	dev = new NativeContext;
	return true;
}

void ScrWin::Context_Destroy(NativeContext*& dev) {
	delete dev;
}

void ScrWin::Context_Visit(NativeContext& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrWin::Context_Initialize(NativeContext& ctx, AtomBase& a, const Script::WorldState& ws) {
	return true;
}

bool ScrWin::Context_PostInitialize(NativeContext& ctx, AtomBase& a) {
	return true;
}

bool ScrWin::Context_Start(NativeContext& ctx, AtomBase& a) {
	return true;
}

void ScrWin::Context_Stop(NativeContext& ctx, AtomBase& a) {
	
}

void ScrWin::Context_Uninitialize(NativeContext& ctx, AtomBase& a) {
	
}

bool ScrWin::Context_Send(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return false;
}

bool ScrWin::Context_Recv(NativeContext& ctx, AtomBase& a, int sink_ch, const Packet&) {
	return false;
}

void ScrWin::Context_Finalize(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrWin::Context_NegotiateSinkFormat(NativeContext& ctx, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}

bool ScrWin::Context_IsReady(NativeContext& dev, AtomBase&, PacketIO& io) {
	return true;
}




//constexpr int kTimerID = 101;


LRESULT CALLBACK Win_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT(active_ScrWin_NativeSinkDevice);
	ScrWin::NativeSinkDevice& dev = *active_ScrWin_NativeSinkDevice;
	
    switch (uMsg)
    {
    
    case WM_CREATE: {
            //RECT r;
            //GetClientRect(hWnd, &r);
            //SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(new graphic_buffers(r.right - r.left, r.bottom - r.top)));
            //SetTimer(dev.ctx->hwnd, kTimerID, 1, NULL);
        }
        break;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        
        dev.atom->GetMachine().SetNotRunning();
        
        return 0;

    /*case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.
			
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;*/
    
    case WM_PAINT:{
	        PAINTSTRUCT ps;
	        HDC hdc = BeginPaint(dev.ctx->hwnd, &ps);
	        if (dev.data) {
		        HDC hdc_bmp = CreateCompatibleDC(hdc);
		        
				auto old_bmp = SelectObject(hdc_bmp, dev.hbm);
				
		        BitBlt(hdc, 0, 0, dev.data_sz.cx, dev.data_sz.cy, hdc_bmp, 0, 0, SRCCOPY);
		
		        SelectObject(hdc, old_bmp);
				DeleteDC(hdc_bmp);
	        }
	        EndPaint(dev.ctx->hwnd, &ps);
	        return 0;
	    }
        
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



#define ABBR
#define WINIMPL 1
#include "Impl.inl"
#undef ABBR



NAMESPACE_PARALLEL_END
#endif
