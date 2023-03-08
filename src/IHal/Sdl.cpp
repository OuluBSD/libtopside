#include "IHal.h"

#if defined flagSDL2

#include <CtrlCore/CtrlCore.h>
#if IS_UPP_CORE
#include <GLDraw/GLDraw.h>
#endif

NAMESPACE_UPP

#if IS_UPP_CORE
extern VirtualGui *VirtualGuiPtr;
#endif
extern dword lastbdowntime[8];
extern dword isdblclick[8];
extern dword mouseb;
extern dword modkeys;
extern bool sdlMouseIsIn;
bool GetCtrl();
bool GetAlt();
bool GetShift();
END_UPP_NAMESPACE

#ifdef flagMSC
	#include <SDL.h>
	#include <SDL_ttf.h>
	#include <SDL_image.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_image.h>
#endif

NAMESPACE_PARALLEL_BEGIN


SDL_TimerID waketimer_id;


 struct HalSdl::NativeCenterVideoSinkDevice {
    void* display;
    SDL_Window* win;
    SDL_Renderer* rend;
    FramebufferT<SdlCpuGfx> fb;
    One<ImageDraw> id;
    Size sz;
    ProgImage pi;
};

struct HalSdl::NativeCenterFboSinkDevice {
    SDL_Window* win;
    SDL_Renderer* rend;
    ::SDL_RendererInfo rend_info;
    void* display;
    SDL_Texture* fb;
    GfxAccelAtom<SdlSwGfx> accel;
};

#if defined flagOGL
struct HalSdl_CommonOgl {
    ::SDL_Window* win;
    ::SDL_Renderer* rend;
    ::SDL_RendererInfo rend_info;
    ::SDL_GLContext gl_ctx;
    Size screen_sz;
    bool is_fullscreen;
    bool is_sizeable;
    bool is_maximized;
	
};

struct HalSdl::NativeOglVideoSinkDevice : HalSdl_CommonOgl {
    void* display;
    uint32 fb;
    GfxAccelAtom<SdlOglGfx> accel;
};

struct HalSdl::NativeUppOglDevice : HalSdl_CommonOgl {
	GLDraw gldraw;
	Size sz;
	static NativeUppOglDevice* last;
};

HalSdl::NativeUppOglDevice* HalSdl::NativeUppOglDevice::last;

#endif

struct HalSdl::NativeEventsBase {
    double time;
    dword seq;
    CtrlEventCollection ev;
    Size sz;
    bool ev_sendable;
    bool is_lalt;
    bool is_ralt;
    bool is_lshift;
    bool is_rshift;
    bool is_lctrl;
    bool is_rctrl;
    Point prev_mouse_pt;
    Vector<int> invalids;
    #if IS_UPP_CORE
    Ref<WindowSystem> wins;
    #endif
    Ref<Gu::SurfaceSystem> surfs;
    Ref<Gu::GuboSystem> gubos;
    
    void Clear() {
        time = 0;
        seq = 0;
        ev_sendable = 0;
        prev_mouse_pt = Point(0,0);
        sz.Clear();
        #if IS_UPP_CORE
        wins.Clear();
        #endif
        surfs.Clear();
        gubos.Clear();
    }
};

struct HalSdl::NativeAudioSinkDevice {
	SDL_AudioDeviceID id;
};

struct HalSdl::NativeContextBase {
	void* p;
};

struct HalSdl::NativeUppEventsBase {
	#if IS_UPP_CORE
    Ref<WindowSystem> wins;
    #endif
    Ref<Gu::SurfaceSystem> surfs;
    Ref<Gu::GuboSystem> gubos;
    double time;
    dword seq;
    
    // use directly values in VirtualGui/Atom
    #if 0
	dword lastbdowntime[8] = {0};
	dword isdblclick[8] = {0};
	dword mouseb;
	dword modkeys;
	bool  sdlMouseIsIn;
	#endif

    
    void Clear() {
        time = 0;
        seq = 0;
        #if IS_UPP_CORE
        wins.Clear();
        #endif
        surfs.Clear();
        gubos.Clear();
    }
};



void StaticAudioOutputSinkCallback(void* userdata, Uint8* stream, int len) {
	if (!userdata) {
		memset(stream, 0, len);
		return;
	}
	
	AtomBase* atom = (AtomBase*)userdata;
	if (!Serial_Link_ForwardAsyncMem(atom->GetLink(), (byte*)stream, len)) {
		RTLOG("StaticAudioOutputSinkCallback: reading memory failed");
		memset(stream, 0, len);
	}
	else {
		float* flt = (float*)stream;
		RTLOG("StaticAudioOutputSinkCallback: reading success");
	}
}



bool HalSdl::AudioSinkDevice_Create(One<NativeAudioSinkDevice>& dev) {
	dev.Create();
	return true;
}

void HalSdl::AudioSinkDevice_Destroy(One<NativeAudioSinkDevice>& dev) {
	dev.Clear();
}

void HalSdl::AudioSinkDevice_Visit(NativeAudioSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HalSdl::AudioSinkDevice_Initialize(NativeAudioSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	auto ev_ctx = a.GetSpace()->template FindNearestAtomCast<SdlContextBase>(1);
	ASSERT(ev_ctx);
	if (!ev_ctx) {RTLOG("error: could not find SDL2 context"); return false;}
	
	if (!ev_ctx->AttachContext(a))
		return false;
	
	// Set init flag
	dword sdl_flag = SDL_INIT_AUDIO;
	ev_ctx->UserData().MapGetAdd("dependencies").MapGetAdd(a).MapSet("sdl_flag", (int64)sdl_flag);
	
	//a.SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	
	return true;
}

bool HalSdl::AudioSinkDevice_PostInitialize(NativeAudioSinkDevice& dev, AtomBase& a) {
	AtomBase* dep = a.GetDependency();
	if (dep == 0) {
		LOG("HalSdl::AudioSinkDevice_PostInitialize: expected dependency atom but got null");
		return false;
	}
	
	if (!dep->IsRunning()) {
		LOG("HalSdl::AudioSinkDevice_PostInitialize: context is not running");
	}
	
	RTLOG("HalSdl::AudioSinkDevice_PostInitialize");
	
	SDL_AudioSpec audio_fmt;
	SDL_AudioSpec audio_desired;
	SDL_AudioDeviceID audio_dev;
	
	SDL_zero(audio_desired);
	audio_desired.freq = 44100;
	audio_desired.format = AUDIO_U16;
	audio_desired.channels = 2;
	audio_desired.samples = 1024;
	audio_desired.callback = StaticAudioOutputSinkCallback;
	audio_desired.userdata = &a;
	
	SDL_zero(audio_fmt);
	
	dev.id = SDL_OpenAudioDevice(NULL, 0, &audio_desired, &audio_fmt, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (dev.id == 0) {
	    RTLOG("HalSdl::AudioSinkDevice_PostInitialize: error: failed to open audio: " << SDL_GetError());
	    return false;
	}
	
    if (audio_fmt.format != audio_desired.format) {
		// we let this one thing change.
        RTLOG("HalSdl::AudioSinkDevice_PostInitialize: warning: couldn't get desired audio format.");
    }
    
    SoundSample::Type st = SoundSample::FLT_LE;
    #if CPU_LITTLE_ENDIAN
    if (audio_fmt.format != AUDIO_F32) {
        switch (audio_fmt.format) {
            case AUDIO_S8:  st = SoundSample::S8_LE;  break;
            case AUDIO_S16: st = SoundSample::S16_LE; break;
            case AUDIO_S32: st = SoundSample::S32_LE; break;
            case AUDIO_U16: st = SoundSample::U16_LE; break;
            default: break;
            case AUDIO_U8:  st = SoundSample::U8_LE;  break;
        }
    }
    #else
    #error TODO
    #endif
    
    Format f;
    f.SetAudio(DevCls::CENTER, st, audio_fmt.channels, audio_fmt.freq, audio_fmt.samples);
    AudioFormat& fmt = f;
    
    //buf.SetFormat(fmt, 4*MIN_AUDIO_BUFFER_SAMPLES);
	
    SDL_PauseAudioDevice(dev.id, 0); // start audio playing.
    
    RTLOG("HalSdl::AudioSinkDevice_PostInitialize: opened format: " << fmt.ToString());
    
    a.UpdateSinkFormat(ValCls::AUDIO, f);
    
	return true;
}

bool HalSdl::AudioSinkDevice_Start(NativeAudioSinkDevice& dev, AtomBase& a) {
	
	return true;
}

void HalSdl::AudioSinkDevice_Stop(NativeAudioSinkDevice& dev, AtomBase& a) {
	a.ClearDependency();
}

void HalSdl::AudioSinkDevice_Uninitialize(NativeAudioSinkDevice& dev, AtomBase& a) {
	
	if (dev.id) {
		SDL_PauseAudioDevice(dev.id, 1);
		SDL_CloseAudioDevice(dev.id);
		dev.id = 0;
	}
}

bool HalSdl::AudioSinkDevice_Send(NativeAudioSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool HalSdl::AudioSinkDevice_Recv(NativeAudioSinkDevice& dev, AtomBase&, int, const Packet&) {
	return true;
}

void HalSdl::AudioSinkDevice_Finalize(NativeAudioSinkDevice& dev, AtomBase&, RealtimeSourceConfig&) {
	
}

void HalSdl::AudioSinkDevice_Update(NativeAudioSinkDevice& dev, AtomBase&, double dt) {
	
}

bool HalSdl::AudioSinkDevice_IsReady(NativeAudioSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}

bool HalSdl::AudioSinkDevice_AttachContext(NativeAudioSinkDevice&, AtomBase& a, AtomBase& other) {
	return true;
}

void HalSdl::AudioSinkDevice_DetachContext(NativeAudioSinkDevice&, AtomBase& a, AtomBase& other) {
	
}





bool HalSdl::ContextBase_Create(One<NativeContextBase>& dev) {
	dev.Create();
	return true;
}

void HalSdl::ContextBase_Destroy(One<NativeContextBase>& dev) {
	dev.Clear();
}

void HalSdl::ContextBase_Visit(NativeContextBase& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HalSdl::ContextBase_Initialize(NativeContextBase& ctx, AtomBase& a, const Script::WorldState& ws) {
	RTLOG("HalSdl::ContextBase_Initialize");
	return true;
}

bool HalSdl::ContextBase_PostInitialize(NativeContextBase& ctx, AtomBase& a) {
	RTLOG("HalSdl::ContextBase_PostInitialize");
	
	// SDL
	uint32 sdl_flags = 0;
	HiValue deps = a.UserData()("dependencies");
	if (!deps.IsMap())
		deps.SetEmptyMap();
	const auto& map = deps.GetMap();
	for(int i = 0; i < map.GetCount(); i++) {
		HiValue hi_atom = map.GetKey(i);
		ASSERT(hi_atom.IsAtom());
		AtomBase& other = hi_atom.GetAtom();
		HiValue hi_data = map[i];
		HiValue hi_flag = hi_data("sdl_flag");
		ASSERT(hi_flag.IsInt64());
		uint32 flag = (uint32)hi_flag.GetInt64();
		sdl_flags |= flag;
	}
	
	if (SDL_Init(sdl_flags) < 0) {
		String last_error = SDL_GetError();
		LOG("SDL2::Context: error: " << last_error);
		return false;
	}
	
	if (TTF_Init() < 0) {
		String last_error = TTF_GetError();
		LOG("SDL2::Context: TTF init failed. error: " << last_error);
	}
	
	
	return true;
}

bool HalSdl::ContextBase_Start(NativeContextBase& ctx, AtomBase& a) {
	return true;
}

void HalSdl::ContextBase_Stop(NativeContextBase& ctx, AtomBase& a) {
	
}

void HalSdl::ContextBase_Uninitialize(NativeContextBase& ctx, AtomBase& a) {
	RTLOG("HalSdl::ContextBase_Uninitialize");
	TTF_Quit();
	SDL_Quit();
}

bool HalSdl::ContextBase_Send(NativeContextBase& ctx, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool HalSdl::ContextBase_AttachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other) {
	if (other.GetDependency()) {
		LOG("HalSdl::ContextBase_AttachContext: atom already has dependency");
		return false;
	}
	other.SetDependency(&a);
	return true;
}

void HalSdl::ContextBase_DetachContext(NativeContextBase& ctx, AtomBase& a, AtomBase& other) {
	if (other.GetDependency() == &a)
		other.SetDependency(0);
}

bool HalSdl::ContextBase_Recv(NativeContextBase& ctx, AtomBase&, int, const Packet&) {
	return true;
}

void HalSdl::ContextBase_Finalize(NativeContextBase& ctx, AtomBase&, RealtimeSourceConfig&) {
	
}

void HalSdl::ContextBase_Update(NativeContextBase& ctx, AtomBase&, double dt) {
	
}

bool HalSdl::ContextBase_IsReady(NativeContextBase& ctx, AtomBase&, PacketIO& io) {
	return true;
}


	

bool HalSdl::CenterVideoSinkDevice_Create(One<NativeCenterVideoSinkDevice>& dev) {
	dev.Create();
	return true;
}

void HalSdl::CenterVideoSinkDevice_Destroy(One<NativeCenterVideoSinkDevice>& dev) {
	dev.Clear();
}

void HalSdl::CenterVideoSinkDevice_Visit(NativeCenterVideoSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HalSdl::CenterVideoSinkDevice_Initialize(NativeCenterVideoSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	auto ev_ctx = a.GetSpace()->template FindNearestAtomCast<SdlContextBase>(1);
	ASSERT(ev_ctx);
	if (!ev_ctx) {RTLOG("error: could not find SDL2 context"); return false;}

	if (!ev_ctx->AttachContext(a))
		return false;

	String title = ws.GetString(".title", "SDL2 Window");
	dev.sz = ws.GetSize(".cx", ".cy", Size(1280,720));
	bool fullscreen = ws.GetBool(".fullscreen", false);
	bool sizeable = ws.GetBool(".sizeable", false);
	bool maximized = ws.GetBool(".maximized", false);

	HiValue& data = a.UserData();
	data.Set("cx", dev.sz.cx);
	data.Set("cy", dev.sz.cy);
	data.Set("fullscreen", fullscreen);
	data.Set("sizeable", sizeable);
	data.Set("maximized", maximized);
	data.Set("title", title);

	//dev.render_src = RENDSRC_BUF;
	
	// Set init flag
	dword sdl_flag = SDL_INIT_VIDEO;
	ev_ctx->UserData().MapGetAdd("dependencies").MapGetAdd(a).MapSet("sdl_flag", (int64)sdl_flag);

	return true;
}

bool HalSdl::CenterVideoSinkDevice_PostInitialize(NativeCenterVideoSinkDevice& dev, AtomBase& a) {
	AppFlags& app_flags = GetAppFlags();
	dev.win = 0;
	dev.rend = 0;

	HiValue& data = a.UserData();
	Size screen_sz(data["cx"], data["cy"]);
	bool is_fullscreen = data("fullscreen").GetInt();
	bool is_sizeable = data("sizeable").GetInt();
	bool is_maximized = data("maximized").GetInt();
	String title = data("title");

	// Window
	uint32 flags = 0;

	if (is_fullscreen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;

	if (SDL_CreateWindowAndRenderer(screen_sz.cx, screen_sz.cy, flags, &dev.win, &dev.rend) == -1)
        return false;
	SDL_SetWindowTitle(dev.win, title);
    
    
    
    // Renderer
    #if IS_UPP_CORE
    int fb_stride = 4;
    SDL_Texture* fb = SDL_CreateTexture(dev.rend, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, screen_sz.cx, screen_sz.cy);
	#else
    int fb_stride = 3;
    SDL_Texture* fb = SDL_CreateTexture(dev.rend, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, screen_sz.cx, screen_sz.cy);
	#endif

	if (!fb) {
		LOG("error: couldn't create framebuffer texture");
		return false;
	}

	SDL_SetRenderTarget(dev.rend, fb);

	auto& rend_fb = dev.fb;
	rend_fb.Init(fb, screen_sz.cx, screen_sz.cy, fb_stride);
	//rend_fb.SetWindowFbo();

	if (is_fullscreen)
		SDL_SetWindowFullscreen(dev.win, SDL_WINDOW_FULLSCREEN);

	return true;
}

bool HalSdl::CenterVideoSinkDevice_Start(NativeCenterVideoSinkDevice& dev, AtomBase& a) {

	return true;
}

void HalSdl::CenterVideoSinkDevice_Stop(NativeCenterVideoSinkDevice& dev, AtomBase& a) {
	a.ClearDependency();
}

void HalSdl::CenterVideoSinkDevice_Uninitialize(NativeCenterVideoSinkDevice& dev, AtomBase& a) {
	
	if (dev.rend) {
		SDL_DestroyRenderer(dev.rend);
		dev.rend = 0;
	}
	if (dev.win) {
		SDL_DestroyWindow(dev.win);
		dev.win = 0;
	}
}

bool HalSdl::CenterVideoSinkDevice_Send(NativeCenterVideoSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool HalSdl::CenterVideoSinkDevice_Recv(NativeCenterVideoSinkDevice& dev, AtomBase&, int ch_i, const Packet& p) {
	Format fmt = p->GetFormat();
	if (fmt.IsVideo()) {
		const Vector<byte>& data = p->GetData();
		const byte* mem = (const byte*)data.Begin();
		int len = data.GetCount();
		VideoFormat& vfmt = fmt;
		int frame_size = vfmt.GetFrameSize();
		
		if (mem && len > 0 && len == frame_size) {
			dev.fb.DrawFill(mem, len);
		}
		
		return true;
	}
	else if (fmt.IsProg()) {
		if (dev.id.IsEmpty()) {
			#if IS_UPP_CORE
			dev.id = new ImageDraw(dev.sz);
			#else
			dev.id.Create(dev.sz, 3);
			#endif
		}
		
		InternalPacketData& data = p->GetData<InternalPacketData>();
		DrawCommand* begin = (DrawCommand*)data.ptr;
		#if 0
		{
			DrawCommand* it = begin;
			int i = 0;
			while (it) {
				LOG(i++ << " " << it->ToString());
				it = it->next;
			}
		}
		ASSERT(0);
		#endif
		#if 0
		while (begin && begin->type != DRAW_BIND_WINDOW) begin = begin->next;
		if (!begin) {
			LOG("HalSdl::CenterVideoSinkDevice_Recv: error: no ptr");
			ASSERT(0);
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
		#else
		DrawCommand* end = begin;
		while (end->next) {
			end = end->next;
		}
		#endif
		
		dev.id->DrawRect(dev.sz, Black());
		dev.pi.Paint(begin, end, *dev.id);
		Image img = *dev.id;
		
		#if 0
		if (0) {
			String path = GetHomeDirFile("debug.png");
			PNGEncoder enc;
			enc.SaveFile(path, img);
		}
		#endif
		
		{
			RTLOG("HalSdl::CenterVideoSinkDevice_Recv: warning: slow screen buffer copy");
			
			auto fb = dev.fb.GetActiveColorBuffer();
			ASSERT(fb);
			uint32 fmt = 0;
			int access, w = 0, h = 0;
			if (SDL_QueryTexture(fb, &fmt, &access, &w, &h) < 0 || w == 0 || h == 0)
				return false;
			SDL_Surface* surf = 0;
			SDL_Rect r {0, 0, w, h};
			if (SDL_LockTextureToSurface(fb, &r, &surf) < 0 || !surf)
				return false;
			int stride = surf->format->BytesPerPixel;
			int pitch = surf->pitch;
			byte* pixels = (byte*)surf->pixels;
			int len = h * pitch;
			#if IS_UPP_CORE
			const RGBA* begin = img.Begin();
			int id_len = img.GetLength() * 4;
			int id_h = img.GetHeight();
			#else
			int id_len = dev.id->Data().GetCount();
			int id_h = dev.id->GetHeight();
			#endif
			ASSERT(len == id_len);
			if (len == id_len) {
				#if IS_UPP_CORE
				memcpy(pixels, (byte*)begin, len);
				#else
				memcpy(pixels, (byte*)dev.id->Data().Begin(), len);
				#endif
			}
			#if 0
			else if (id_h == h) {
				byte* to = pixels;
				#if IS_UPP_CORE
				byte* from = (byte*)begin;
				#else
				byte* from = dev.id->Data().Begin();
				#endif
				// optional vertical invert (1 is on)
				#if 0
				for (int y = 0; y < h; y++) {
					memcpy(to, from, pitch);
					to += pitch;
					from += pitch;
				}
				#else
				from += (h - 1) * pitch;
				for (int y = 0; y < h; y++) {
					memcpy(to, from, pitch);
					to += pitch;
					from -= pitch;
				}
				#endif
			}
			#endif
			//memset(pixels, Random(0x100), len);
			SDL_UnlockTexture(fb);
		}
		
		return true;
	}
	else return false;
}

void HalSdl::CenterVideoSinkDevice_Finalize(NativeCenterVideoSinkDevice& dev, AtomBase&, RealtimeSourceConfig& cfg) {
	SDL_RenderCopy(dev.rend, dev.fb.GetActiveColorBuffer(), NULL, NULL);
	SDL_RenderPresent(dev.rend);
}

void HalSdl::CenterVideoSinkDevice_Update(NativeCenterVideoSinkDevice& dev, AtomBase&, double dt) {
	// pass
}

bool HalSdl::CenterVideoSinkDevice_IsReady(NativeCenterVideoSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}

bool HalSdl::CenterVideoSinkDevice_AttachContext(NativeCenterVideoSinkDevice&, AtomBase& a, AtomBase& other) {
	return true;
}

void HalSdl::CenterVideoSinkDevice_DetachContext(NativeCenterVideoSinkDevice&, AtomBase& a, AtomBase& other) {
	
}












bool HalSdl::CenterFboSinkDevice_Create(One<NativeCenterFboSinkDevice>& dev) {
	dev.Create();
	return true;
}

void HalSdl::CenterFboSinkDevice_Destroy(One<NativeCenterFboSinkDevice>& dev) {
	dev.Clear();
}

void HalSdl::CenterFboSinkDevice_Visit(NativeCenterFboSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	vis % dev.accel;
}

bool HalSdl::CenterFboSinkDevice_Initialize(NativeCenterFboSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	
	if (!dev.accel.Initialize(a, ws))
		return false;
	
	auto ev_ctx = a.GetSpace()->template FindNearestAtomCast<SdlContextBase>(1);
	ASSERT(ev_ctx);
	if (!ev_ctx) {RTLOG("error: could not find SDL2 context"); return false;}
	
	if (!ev_ctx->AttachContext(a))
		return false;
	
	String title = ws.GetString(".title", "SDL2 Window");
	Size sz = ws.GetSize(".cx", ".cy", Size(1280,720));
	bool fullscreen = ws.GetBool(".fullscreen", false);
	bool sizeable = ws.GetBool(".sizeable", false);
	bool maximized = ws.GetBool(".maximized", false);
	
	HiValue& data = a.UserData();
	data.Set("cx", sz.cx);
	data.Set("cy", sz.cy);
	data.Set("fullscreen", fullscreen);
	data.Set("sizeable", sizeable);
	data.Set("maximized", maximized);
	data.Set("title", title);
	
	
	// Set init flag
	dword sdl_flag = SDL_INIT_VIDEO;
	ev_ctx->UserData().MapGetAdd("dependencies").MapGetAdd(a).MapSet("sdl_flag", (int64)sdl_flag);
	
	return true;
}

bool HalSdl::CenterFboSinkDevice_PostInitialize(NativeCenterFboSinkDevice& dev, AtomBase& a) {
	AppFlags& app_flags = GetAppFlags();
	dev.win = 0;
	dev.rend = 0;
	
	HiValue& data = a.UserData();
	Size screen_sz(data["cx"], data["cy"]);
	bool is_fullscreen = data("fullscreen").GetInt();
	bool is_sizeable = data("sizeable").GetInt();
	bool is_maximized = data("maximized").GetInt();
	String title = data["title"];
	
	// Window
	uint32 flags = 0;
	
	if (is_fullscreen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;
	
	if (SDL_CreateWindowAndRenderer(screen_sz.cx, screen_sz.cy, flags, &dev.win, &dev.rend) == -1)
        return false;
	SDL_SetWindowTitle(dev.win, title);
    
    
    
    // Renderer
    int fb_stride = 3;
	
	dev.fb = SDL_CreateTexture(dev.rend, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, screen_sz.cx, screen_sz.cy);
	if (!dev.fb) {
		LOG("error: couldn't create framebuffer texture");
		return false;
	}
	
	SDL_SetRenderTarget(dev.rend, dev.fb);
	
	dev.accel.SetNative(dev.display, dev.win, &dev.rend, dev.fb);
	
	if (!dev.accel.Open(screen_sz, fb_stride)) {
		LOG("HalSdl::CenterFboSinkDevice_PostInitialize: error: could not open opengl atom");
		return false;
	}
	
	if (is_fullscreen)
		SDL_SetWindowFullscreen(dev.win, SDL_WINDOW_FULLSCREEN);
	
	return true;
}

bool HalSdl::CenterFboSinkDevice_Start(NativeCenterFboSinkDevice& dev, AtomBase& a) {
	
	return true;
}

void HalSdl::CenterFboSinkDevice_Stop(NativeCenterFboSinkDevice& dev, AtomBase& a) {
	a.ClearDependency();
}

void HalSdl::CenterFboSinkDevice_Uninitialize(NativeCenterFboSinkDevice& dev, AtomBase& a) {
	
	dev.accel.Uninitialize();
	
	if (dev.rend) {
		SDL_DestroyRenderer(dev.rend);
		dev.rend = 0;
	}
	if (dev.win) {
		SDL_DestroyWindow(dev.win);
		dev.win = 0;
	}
}

bool HalSdl::CenterFboSinkDevice_Recv(NativeCenterFboSinkDevice& dev, AtomBase&, int ch_i, const Packet& p) {
	return dev.accel.Recv(ch_i, p);
}

void HalSdl::CenterFboSinkDevice_Finalize(NativeCenterFboSinkDevice& dev, AtomBase&, RealtimeSourceConfig& cfg) {
	dev.accel.Render(cfg);
}

bool HalSdl::CenterFboSinkDevice_Send(NativeCenterFboSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

void HalSdl::CenterFboSinkDevice_Update(NativeCenterFboSinkDevice& dev, AtomBase&, double dt) {
	
}

bool HalSdl::CenterFboSinkDevice_IsReady(NativeCenterFboSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}

bool HalSdl::CenterFboSinkDevice_AttachContext(NativeCenterFboSinkDevice& dev, AtomBase& a, AtomBase& other) {
	return true;
}

void HalSdl::CenterFboSinkDevice_DetachContext(NativeCenterFboSinkDevice& dev, AtomBase& a, AtomBase& other) {
	
}











#ifdef flagOGL
bool HalSdl::OglVideoSinkDevice_Create(One<NativeOglVideoSinkDevice>& dev) {
	dev.Create();
	return true;
}

void HalSdl::OglVideoSinkDevice_Destroy(One<NativeOglVideoSinkDevice>& dev) {
	dev.Clear();
}

void HalSdl::OglVideoSinkDevice_Visit(NativeOglVideoSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	vis % dev.accel;
}

bool HalSdl::OglVideoSinkDevice_Initialize(NativeOglVideoSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	
	if (!dev.accel.Initialize(a, ws))
		return false;
	
	auto ev_ctx = a.GetSpace()->template FindNearestAtomCast<SdlContextBase>(1);
	ASSERT(ev_ctx);
	if (!ev_ctx) {RTLOG("error: could not find SDL2 context"); return false;}
	
	if (!ev_ctx->AttachContext(a))
		return false;
	
	String title = ws.GetString(".title", "SDL2 Window");
	Size sz = ws.GetSize(".cx", ".cy", Size(1280,720));
	bool fullscreen = ws.GetBool(".fullscreen", false);
	bool sizeable = ws.GetBool(".sizeable", false);
	bool maximized = ws.GetBool(".maximized", false);
	
	HiValue& data = a.UserData();
	data.Set("cx", sz.cx);
	data.Set("cy", sz.cy);
	data.Set("fullscreen", fullscreen);
	data.Set("sizeable", sizeable);
	data.Set("maximized", maximized);
	data.Set("title", title);
	
	
	// Set init flag
	dword sdl_flag = SDL_INIT_VIDEO | SDL_WINDOW_OPENGL;
	ev_ctx->UserData().MapGetAdd("dependencies").MapGetAdd(a).MapSet("sdl_flag", (int64)sdl_flag);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	return true;
}

template <class T>
bool HalSdl_Ogl_PostInitialize(T& dev, AtomBase& a) {
	AppFlags& app_flags = GetAppFlags();
	dev.win = 0;
	dev.rend = 0;
	
	HiValue& data = a.UserData();
	dev.screen_sz = Size(data["cx"], data["cy"]);
	dev.is_fullscreen = (int)data["fullscreen"];
	dev.is_sizeable = (int)data["sizeable"];
	dev.is_maximized = (int)data["maximized"];
	String title = data["title"];
	
	// Window
	uint32 flags = 0;
	
	flags |= SDL_WINDOW_OPENGL;
	
	if (dev.is_fullscreen)	flags |= SDL_WINDOW_FULLSCREEN;
	if (dev.is_sizeable)	flags |= SDL_WINDOW_RESIZABLE;
	if (dev.is_maximized)	flags |= SDL_WINDOW_MAXIMIZED;
	
	if (SDL_CreateWindowAndRenderer(dev.screen_sz.cx, dev.screen_sz.cy, flags, &dev.win, &dev.rend) == -1) {
		LOG("HalSdl::OglVideoSinkDevice_PostInitialize: error: could not create window and renderer");
        return false;
	}
	SDL_SetWindowTitle(dev.win, title);
    
    
    
    // Renderer
    SDL_GetRendererInfo(dev.rend, &dev.rend_info);
	if ((dev.rend_info.flags & SDL_RENDERER_ACCELERATED) == 0 ||
        (dev.rend_info.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
        LOG("HalSdl::OglVideoSinkDevice_PostInitialize: error: renderer does not have acceleration");
        return false;
    }
	
	// GL context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	
	MemoryIgnoreLeaksBegin();
	dev.gl_ctx = SDL_GL_CreateContext(dev.win);
	GetAppFlags().SetOpenGLContextOpen();
	MemoryIgnoreLeaksEnd();
	
	if (!dev.gl_ctx) {
		LOG("Could not open opengl context: " << SDL_GetError());
		return false;
	}
	
	// Glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		LOG("Glew error: " << (const char*)glewGetErrorString(err));
		return false;
	}
    
    return true;
}

bool HalSdl::OglVideoSinkDevice_PostInitialize(NativeOglVideoSinkDevice& dev, AtomBase& a) {
	if (!HalSdl_Ogl_PostInitialize(dev, a))
		return false;
	
	dev.accel.SetNative(dev.display, dev.win, &dev.rend, 0);
	
    int fb_stride = 3;
	if (!dev.accel.Open(dev.screen_sz, fb_stride)) {
		LOG("HalSdl::OglVideoSinkDevice_PostInitialize: error: could not open opengl atom");
		return false;
	}
	
	if (!dev.accel.PostInitialize())
		return false;
	
	if (dev.is_fullscreen)
		SDL_SetWindowFullscreen(dev.win, SDL_WINDOW_FULLSCREEN);
	
	return true;
}

bool HalSdl::OglVideoSinkDevice_Start(NativeOglVideoSinkDevice& dev, AtomBase&) {
	
	return true;
}

void HalSdl::OglVideoSinkDevice_Stop(NativeOglVideoSinkDevice& dev, AtomBase& a) {
	a.ClearDependency();
}

void HalSdl::OglVideoSinkDevice_Uninitialize(NativeOglVideoSinkDevice& dev, AtomBase& a) {
	
	dev.accel.Uninitialize();
	
	#if 0
	// This SHOULD be done, but buggy SDL crashes sometimes (see test 06f_toyshader_keyboard)
	// and skipping this doesn't seem to create problems.
	if (dev.rend) {
		SDL_DestroyRenderer(dev.rend);
		dev.rend = 0;
	}
	#endif
	
	if (dev.win) {
		SDL_DestroyWindow(dev.win);
		dev.win = 0;
	}
}

bool HalSdl::OglVideoSinkDevice_Send(NativeOglVideoSinkDevice& dev, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	dev.accel.Render(cfg);
	return true;
}

bool HalSdl::OglVideoSinkDevice_Recv(NativeOglVideoSinkDevice& dev, AtomBase&, int ch_i, const Packet& p) {
	return dev.accel.Recv(ch_i, p);
}

void HalSdl::OglVideoSinkDevice_Finalize(NativeOglVideoSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

void HalSdl::OglVideoSinkDevice_Update(NativeOglVideoSinkDevice& dev, AtomBase& a, double dt) {
	dev.accel.Update(dt);
}

bool HalSdl::OglVideoSinkDevice_IsReady(NativeOglVideoSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}

bool HalSdl::OglVideoSinkDevice_AttachContext(NativeOglVideoSinkDevice&, AtomBase& a, AtomBase& other) {
	return true;
}

void HalSdl::OglVideoSinkDevice_DetachContext(NativeOglVideoSinkDevice&, AtomBase& a, AtomBase& other) {
	
}

#endif








Image HalSdl__GetMouseCursor(void* ptr) {
	SDL_Cursor* cursor = SDL_GetCursor();
	if (!cursor)
		return Image();
	Image img;
	#if IS_TS_CORE
	img.Set(cursor, Image::SDL_CURSOR, 0);
	#endif
	return img;
}

void HalSdl__SetMouseCursor(void* ptr, const Image& image)
{
	GuiLock __;
	static Image fbCursorImage;
	static Point fbCursorPos;
	static SDL_Cursor  *sdl_default_cursor;
	static SDL_Cursor  *sdl_cursor;
	static SDL_Surface *sdl_cursor_surface;
	static Buffer<RGBA> data;
	if (!sdl_default_cursor)
		sdl_default_cursor = SDL_GetCursor();
	if (image.IsEmpty()) {
		if (sdl_default_cursor)
			SDL_SetCursor(sdl_default_cursor);
		fbCursorImage.Clear();
	}
	else if (image.GetSerialId() != fbCursorImage.GetSerialId()) {
		fbCursorImage = image;
		fbCursorPos = Null;
		SDL_ShowCursor(true);
		if(sdl_cursor)
			SDL_FreeCursor(sdl_cursor);
		if(sdl_cursor_surface)
			SDL_FreeSurface(sdl_cursor_surface);
		int64 a = image.GetAuxData();
		if(a)
			sdl_cursor = SDL_CreateSystemCursor(SDL_SystemCursor(a - 1));
		else {
			sdl_cursor = NULL;
			data.Alloc(image.GetLength());
			MemoryCopy(data.begin(), image.Begin(), image.GetLength());
			sdl_cursor_surface = SDL_CreateRGBSurfaceFrom(~data, image.GetWidth(), image.GetHeight(),
			                                              32, sizeof(RGBA) * image.GetWidth(),
			                                              0xff0000, 0xff00, 0xff, 0xff000000);
			Point h = image.GetHotSpot();
			if(sdl_cursor_surface)
				sdl_cursor = SDL_CreateColorCursor(sdl_cursor_surface, h.x, h.y);
		}
		if(sdl_cursor)
			SDL_SetCursor(sdl_cursor);
	}
}




void HalSdl__HandleSDLEvent(HalSdl::NativeUppEventsBase& dev, SDL_Event* event);

bool HalSdl::EventsBase_Create(One<NativeEventsBase>& dev) {
	dev.Create();
	return true;
}

void HalSdl::EventsBase_Destroy(One<NativeEventsBase>& dev) {
	dev.Clear();
}

void HalSdl::EventsBase_Visit(NativeEventsBase& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HalSdl::EventsBase_Initialize(NativeEventsBase& dev, AtomBase& a, const Script::WorldState&) {
	dev.Clear();
	
	
	auto ev_ctx = a.GetSpace()->template FindNearestAtomCast<SdlContextBase>(1);
	ASSERT(ev_ctx);
	if (!ev_ctx) {RTLOG("error: could not find SDL2 context"); return false;}
	
	if (!ev_ctx->AttachContext(a))
		return false;
	
	// Set init flag
	dword sdl_flag = SDL_INIT_EVENTS;
	ev_ctx->UserData().MapGetAdd("dependencies").MapGetAdd(a).MapSet("sdl_flag", (int64)sdl_flag);
	
	
	return true;
}

bool HalSdl::EventsBase_PostInitialize(NativeEventsBase& dev, AtomBase& a) {
	AtomBase* dep = a.GetDependency();
	if (!dep) {
		LOG("HalSdl::EventsBase_PostInitialize: expected dependency atom but got null");
		return false;
	}
	
	if (!dep->IsInitialized()) {
		LOG("HalSdl::EventsBase_PostInitialize: context is not running");
	}
	
	RTLOG("HalSdl::EventsBase_PostInitialize");
	
	a.AddAtomToUpdateList();
	
	
	{
		Machine& m = a.GetMachine();
		dev.surfs = m.Get<Gu::SurfaceSystem>();
		dev.gubos = m.Get<Gu::GuboSystem>();
		
		if (dev.surfs) {
			TODO
			/*dev.wins->Set_SetMouseCursor(&HalSdl__SetMouseCursor, &dev);
			dev.wins->Set_GetMouseCursor(&HalSdl__GetMouseCursor, &dev);*/
		}
		
		#if IS_UPP_CORE
		dev.wins = m.Get<WindowSystem>();
		if (dev.wins) {
			dev.wins->Set_SetMouseCursor(&HalSdl__SetMouseCursor, &dev);
			dev.wins->Set_GetMouseCursor(&HalSdl__GetMouseCursor, &dev);
		}
		#endif
	}
	
	return true;
}

bool HalSdl::EventsBase_Start(NativeEventsBase& dev, AtomBase& a) {
	// pass
	return true;
}

void HalSdl::EventsBase_Stop(NativeEventsBase& dev, AtomBase& a) {
	a.ClearDependency();
}

void HalSdl::EventsBase_Uninitialize(NativeEventsBase& dev, AtomBase& a) {
	#if IS_UPP_CORE
	dev.wins.Clear();
	#endif
	dev.surfs.Clear();
	dev.gubos.Clear();
	
	a.RemoveAtomFromUpdateList();
}

bool HalSdl::EventsBase_Send(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.ev_sendable);
	if (!dev.ev_sendable)
		return false;
	

	Format fmt = out.GetFormat();
	RTLOG("HalSdl::EventsBase_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		out.seq = dev.seq++;
		CtrlEventCollection& dst = out.SetData<CtrlEventCollection>();
		dst <<= dev.ev;
		dev.ev_sendable = false;
	}
	
	return true;
}

bool HalSdl::EventsBase_Recv(NativeEventsBase& dev, AtomBase& a, int sink_ch, const Packet& p) {
	return true;
}

void HalSdl::EventsBase_Finalize(NativeEventsBase& dev, AtomBase&, RealtimeSourceConfig&) {
	
}

void HalSdl::EventsBase_Update(NativeEventsBase& dev, AtomBase&, double dt) {
	dev.time += dt;
}

#ifdef flagSCREEN
void Events__PutKeyFlags(HalSdl::NativeEventsBase& dev, dword& key) {
	if (dev.is_lalt   || dev.is_ralt)		key |= K_ALT;
	if (dev.is_lshift || dev.is_rshift)		key |= K_SHIFT;
	if (dev.is_lctrl  || dev.is_rctrl)		key |= K_CTRL;
}
#endif

bool Events__Poll(HalSdl::NativeEventsBase& dev, AtomBase& a) {
	dev.ev.SetCount(0);
	
	SDL_Event event;
	Size screen_sz;
	Point mouse_pt;
#ifdef flagSCREEN
	auto s = a.GetSpace();
	auto v_sink   = s->template FindNearestAtomCast<SdlCenterVideoSinkDevice>(2);
	auto sw_sink  = s->template FindNearestAtomCast<SdlCenterFboSinkDevice>(2);
	::SDL_Renderer* rend = 0;
	if (v_sink)   rend = v_sink->dev->rend;
	if (sw_sink)  rend = sw_sink->dev->rend;
#ifdef flagOGL
	auto ogl_sink = s->template FindNearestAtomCast<SdlOglVideoSinkDevice>(2);
	if (ogl_sink) rend = ogl_sink->dev->rend;
#endif
#endif
	dword key;
	int mouse_code;
	
	bool succ = true;
	
	// Process the events
	while (SDL_PollEvent(&event)) {
		UPP::CtrlEvent& e = dev.ev.Add();
		e.Clear();
		
		switch (event.type) {
			
#ifdef flagSCREEN
			
		case SDL_WINDOWEVENT:
			
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				e.type = EVENT_SHUTDOWN;
				continue;
			}
			else if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				screen_sz.cx = event.window.data1;
				screen_sz.cy = event.window.data2;
				dev.sz = screen_sz;
				e.type = EVENT_WINDOW_RESIZE;
				e.sz = screen_sz;
				#ifdef flagOGL
				if (HalSdl::NativeUppOglDevice::last)
					HalSdl::NativeUppOglDevice::last->sz = screen_sz;
				#endif
				continue;
			}
			break;
		
			
		case SDL_KEYDOWN:
		
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:	event.type = SDL_QUIT; break;
				case SDLK_LALT:		dev.is_lalt = true; break;
				case SDLK_RALT:		dev.is_ralt = true; break;
				case SDLK_LSHIFT:	dev.is_lshift = true; break;
				case SDLK_RSHIFT:	dev.is_rshift = true; break;
				case SDLK_LCTRL:	dev.is_lctrl = true; break;
				case SDLK_RCTRL:	dev.is_rctrl = true; break;
			}
			
			key = event.key.keysym.sym;
			if (key & SDLK_SCANCODE_MASK) {
				key &= ~SDLK_SCANCODE_MASK;
				
				// TODO handle codes separately
				if (0 /*key == */) {
					
				}
				else key = 0;
			}
			Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_KEYDOWN;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			continue;
			
		case SDL_KEYUP:
		
			switch (event.key.keysym.sym) {
				case SDLK_LALT:		dev.is_lalt = false; break;
				case SDLK_RALT:		dev.is_ralt = false; break;
				case SDLK_LSHIFT:	dev.is_lshift = false; break;
				case SDLK_RSHIFT:	dev.is_rshift = false; break;
				case SDLK_LCTRL:	dev.is_lctrl = false; break;
				case SDLK_RCTRL:	dev.is_rctrl = false; break;
			}
			
			key = event.key.keysym.sym | K_KEYUP;
			if (key & SDLK_SCANCODE_MASK) {
				key &= ~SDLK_SCANCODE_MASK;
				
				// TODO handle codes separately
				if (0 /*key == */) {
					
				}
				else key = 0;
			}
			Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_KEYUP;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			continue;
			
		case SDL_MOUSEMOTION:
			mouse_pt = Point(event.motion.x, event.motion.y);
			key = 0;
			Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_MOUSEMOVE;
			e.value = key;
			e.pt = mouse_pt;
			
			dev.prev_mouse_pt = mouse_pt;
			continue;
		
		case SDL_MOUSEWHEEL:
			key = 0;
			Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_MOUSEWHEEL;
			e.value = key;
			e.pt = dev.prev_mouse_pt;
			e.n = event.wheel.y;
			
			continue;
			
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			
			mouse_code = 0;
			//mouse_zdelta = 0;
			if (event.button.state == SDL_PRESSED) {
				if (event.button.clicks == 1) {
					if (event.button.button == SDL_BUTTON_LEFT)
						mouse_code = MOUSE_LEFTDOWN;
					else if (event.button.button == SDL_BUTTON_MIDDLE)
						mouse_code = MOUSE_MIDDLEDOWN;
					else if (event.button.button == SDL_BUTTON_RIGHT)
						mouse_code = MOUSE_RIGHTDOWN;
				}
				else if (event.button.clicks == 2) {
					if (event.button.button == SDL_BUTTON_LEFT)
						mouse_code = MOUSE_LEFTDOUBLE;
					else if (event.button.button == SDL_BUTTON_MIDDLE)
						mouse_code = MOUSE_MIDDLEDOUBLE;
					else if (event.button.button == SDL_BUTTON_RIGHT)
						mouse_code = MOUSE_RIGHTDOUBLE;
				}
				else {
					if (event.button.button == SDL_BUTTON_LEFT)
						mouse_code = MOUSE_LEFTTRIPLE;
					else if (event.button.button == SDL_BUTTON_MIDDLE)
						mouse_code = MOUSE_MIDDLETRIPLE;
					else if (event.button.button == SDL_BUTTON_RIGHT)
						mouse_code = MOUSE_RIGHTTRIPLE;
				}
				
			}
			else if (event.button.state == SDL_RELEASED) {
				if (event.button.button == SDL_BUTTON_LEFT)
					mouse_code = MOUSE_LEFTUP;
				else if (event.button.button == SDL_BUTTON_MIDDLE)
					mouse_code = MOUSE_MIDDLEUP;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					mouse_code = MOUSE_RIGHTUP;
			}
			
			if (mouse_code) {
				mouse_pt = Point(event.button.x, event.button.y);
				key = 0;
				Events__PutKeyFlags(dev, key);
				
				e.type = EVENT_MOUSE_EVENT;
				e.value = key;
				e.pt = mouse_pt;
				e.n = mouse_code;
				
				dev.prev_mouse_pt = mouse_pt;
				continue;
			}
			
#endif
			
		default:
			break;
		}
	}
	
	dev.invalids.SetCount(0);
	int i = 0;
	for (auto& ev : dev.ev) {
		if (ev.type == EVENT_INVALID)
			dev.invalids.Add(i);
		i++;
	}
	dev.ev.Remove(dev.invalids);
	
	if (dev.ev.IsEmpty())
		return false;
	
	#if IS_UPP_CORE
	if (dev.wins) {
		dev.wins->DoEvents(dev.ev);
	}
	#endif
	if (dev.surfs) {
		dev.surfs->DoEvents(dev.ev);
	}
	if (dev.gubos) {
		// copy dev.wins
	}
	
	return true;
}

bool HalSdl::EventsBase_IsReady(NativeEventsBase& dev, AtomBase& a, PacketIO& io) {
	bool b = io.full_src_mask == 0;
	if (b) {
		if (dev.seq == 0) {
			UPP::CtrlEvent& e = dev.ev.Add();
			
			auto s = a.GetSpace();
			e.type = EVENT_WINDOW_RESIZE;
			auto v_sink   = s->template FindNearestAtomCast<SdlCenterVideoSinkDevice>(2);
			auto sw_sink  = s->template FindNearestAtomCast<SdlCenterFboSinkDevice>(2);
			#ifdef flagOGL
			auto ogl_sink = s->template FindNearestAtomCast<SdlOglVideoSinkDevice>(2);
			#endif
			
			int x = 0, y = 0;
			if (v_sink) {
				SDL_GetWindowPosition(v_sink->dev->win, &x, &y);
				dev.ev_sendable = true;
			}
			else if (sw_sink) {
				SDL_GetWindowPosition(sw_sink->dev->win, &x, &y);
				dev.ev_sendable = true;
			}
			#ifdef flagOGL
			else if (ogl_sink) {
				SDL_GetWindowPosition(ogl_sink->dev->win, &x, &y);
				dev.ev_sendable = true;
			}
			#endif
			else {
				RTLOG("HalSdl::EventsBase_IsReady: skipping windows resize, because no screen is in context");
				dev.seq++;
				b = false;
			}
			dev.sz = Size(x,y);
		}
		else if (Events__Poll(dev, a)) {
			dev.ev_sendable = true;
		}
		else {
			dev.ev_sendable = false;
			b = false;
		}
	}
	RTLOG("HalSdl::EventsBase_IsReady: " << (b ? "true" : "false"));
	return b;
}

bool HalSdl::EventsBase_AttachContext(NativeEventsBase&, AtomBase& a, AtomBase& other) {
	return true;
}

void HalSdl::EventsBase_DetachContext(NativeEventsBase&, AtomBase& a, AtomBase& other) {
	
}





extern SDL_TimerID waketimer_id;

bool HalSdl::UppEventsBase_Create(One<NativeUppEventsBase>& dev) {
	dev.Create();
	return true;
}

void HalSdl::UppEventsBase_Destroy(One<NativeUppEventsBase>& dev) {
	dev.Clear();
}

bool HalSdl::UppEventsBase_Initialize(NativeUppEventsBase& dev, AtomBase& a, const Script::WorldState&) {
	dev.Clear();
	
	
	auto ev_ctx = a.GetSpace()->template FindNearestAtomCast<SdlContextBase>(1);
	ASSERT(ev_ctx);
	if (!ev_ctx) {RTLOG("error: could not find SDL2 context"); return false;}
	
	if (!ev_ctx->AttachContext(a))
		return false;
	
	// Set init flag
	dword sdl_flag = SDL_INIT_EVENTS;
	ev_ctx->UserData().MapGetAdd("dependencies").MapGetAdd(a).MapSet("sdl_flag", (int64)sdl_flag);
	
	
	return true;
}

bool HalSdl::UppEventsBase_PostInitialize(NativeUppEventsBase& dev, AtomBase& a) {
	AtomBase* dep = a.GetDependency();
	if (!dep) {
		LOG("HalSdl::EventsBase_PostInitialize: expected dependency atom but got null");
		return false;
	}
	
	if (!dep->IsInitialized()) {
		LOG("HalSdl::EventsBase_PostInitialize: context is not running");
	}
	
	RTLOG("HalSdl::EventsBase_PostInitialize");
	
	a.AddAtomToUpdateList();
	
	
	{
		Machine& m = a.GetMachine();
		
		dev.surfs = m.Get<Gu::SurfaceSystem>();
		dev.gubos = m.Get<Gu::GuboSystem>();
		
		#if IS_UPP_CORE
		dev.wins = m.Get<WindowSystem>();
		if (dev.wins) {
			dev.wins->Set_SetMouseCursor(&HalSdl__SetMouseCursor, &dev);
			dev.wins->Set_GetMouseCursor(&HalSdl__GetMouseCursor, &dev);
		}
		#endif
	}
	
	return true;
}

bool HalSdl::UppEventsBase_Start(NativeUppEventsBase&, AtomBase&) {
	// pass
	return true;
}

void HalSdl::UppEventsBase_Stop(NativeUppEventsBase&, AtomBase& a) {
	a.ClearDependency();
}

void HalSdl::UppEventsBase_Uninitialize(NativeUppEventsBase& dev, AtomBase& a) {
	#if IS_UPP_CORE
	dev.wins.Clear();
	#endif
	dev.surfs.Clear();
	dev.gubos.Clear();
	
	a.RemoveAtomFromUpdateList();
}

bool HalSdl::UppEventsBase_Send(NativeUppEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(out.GetFormat().IsReceipt());
	return true;
}

void HalSdl::UppEventsBase_Visit(NativeUppEventsBase&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HalSdl::UppEventsBase_Recv(NativeUppEventsBase&, AtomBase&, int, const Packet&) {
	return true;
}

void HalSdl::UppEventsBase_Finalize(NativeUppEventsBase&, AtomBase&, RealtimeSourceConfig&) {
	
}

void HalSdl::UppEventsBase_Update(NativeUppEventsBase& dev, AtomBase&, double dt) {
	dev.time += dt;
}

bool HalSdl::UppEventsBase_IsReady(NativeUppEventsBase& dev, AtomBase&, PacketIO& io) {
	bool ret = false;
	SDL_Event event;
	if(SDL_PollEvent(&event)) {
		//if(event.type == SDL_QUIT && quit)
		//	*quit = true;
		HalSdl__HandleSDLEvent(dev, &event);
		ret = true;
	}
	return ret;
}

bool HalSdl::UppEventsBase_AttachContext(NativeUppEventsBase&, AtomBase& a, AtomBase& other) {
	return true;
}

void HalSdl::UppEventsBase_DetachContext(NativeUppEventsBase&, AtomBase& a, AtomBase& other) {
	
}


#if defined flagOGL
bool HalSdl::UppOglDevice_Create(One<NativeUppOglDevice>& dev) {
	dev.Create();
	NativeUppOglDevice::last = &*dev;
	return true;
}

void HalSdl::UppOglDevice_Destroy(One<NativeUppOglDevice>& dev) {
	dev.Clear();
}

bool HalSdl::UppOglDevice_Initialize(NativeUppOglDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	
	auto ev_ctx = a.GetSpace()->template FindNearestAtomCast<SdlContextBase>(1);
	ASSERT(ev_ctx);
	if (!ev_ctx) {RTLOG("error: could not find SDL2 context"); return false;}
	
	if (!ev_ctx->AttachContext(a))
		return false;
	
	String title = ws.GetString(".title", "SDL2 Window");
	dev.sz = ws.GetSize(".cx", ".cy", Size(1280,720));
	bool fullscreen = ws.GetBool(".fullscreen", false);
	bool sizeable = ws.GetBool(".sizeable", false);
	bool maximized = ws.GetBool(".maximized", false);
	
	HiValue& data = a.UserData();
	data.Set("cx", dev.sz.cx);
	data.Set("cy", dev.sz.cy);
	data.Set("fullscreen", fullscreen);
	data.Set("sizeable", sizeable);
	data.Set("maximized", maximized);
	data.Set("title", title);
	
	
	// Set init flag
	dword sdl_flag = SDL_INIT_VIDEO | SDL_WINDOW_OPENGL;
	ev_ctx->UserData().MapGetAdd("dependencies").MapGetAdd(a).MapSet("sdl_flag", (int64)sdl_flag);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	return true;
}

bool HalSdl::UppOglDevice_PostInitialize(NativeUppOglDevice& dev, AtomBase& a) {
	if (!HalSdl_Ogl_PostInitialize(dev, a))
		return false;
	
	
	return true;
}

bool HalSdl::UppOglDevice_Start(NativeUppOglDevice&, AtomBase&) {
	
	return true;
}

void HalSdl::UppOglDevice_Stop(NativeUppOglDevice&, AtomBase& a) {
	a.ClearDependency();
}

void HalSdl::UppOglDevice_Uninitialize(NativeUppOglDevice& dev, AtomBase& a) {
	if(dev.gl_ctx) {
		SDL_GL_DeleteContext(dev.gl_ctx);
		dev.gl_ctx = NULL;
		GLDraw::ResetCache();
	}
	if(dev.win) {
		SDL_RemoveTimer(waketimer_id);
		SDL_DestroyWindow(dev.win);
		dev.win = NULL;
	}
}

bool HalSdl::UppOglDevice_Send(NativeUppOglDevice&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

void HalSdl::UppOglDevice_Visit(NativeUppOglDevice&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HalSdl::UppOglDevice_Recv(NativeUppOglDevice&, AtomBase&, int, const Packet&) {
	return true;
}

void HalSdl::UppOglDevice_Finalize(NativeUppOglDevice& dev, AtomBase& a, RealtimeSourceConfig&) {
	ASSERT(!dev.sz.IsEmpty());
	dev.gldraw.Init(dev.sz, (uint64)dev.gl_ctx);
	SystemDraw& sysdraw = UPP::VirtualGuiPtr->BeginDraw();
	sysdraw.SetTarget(&dev.gldraw);
	
	//Ctrl::PaintAll();
	Ctrl::EventLoopIteration(NULL);
	
	dev.gldraw.Finish();
	SDL_GL_SwapWindow(dev.win);
}

void HalSdl::UppOglDevice_Update(NativeUppOglDevice&, AtomBase&, double dt) {
	TODO
}

bool HalSdl::UppOglDevice_IsReady(NativeUppOglDevice&, AtomBase&, PacketIO& io) {
	return true;
}

bool HalSdl::UppOglDevice_AttachContext(NativeUppOglDevice& dev, AtomBase& a, AtomBase& other) {
	return true;
}

void HalSdl::UppOglDevice_DetachContext(NativeUppOglDevice& dev, AtomBase& a, AtomBase& other) {
	
}

#endif







#define LLOG(x)

const static VectorMap<dword, dword> SDL_key_map = {
//	{ SDLK_BACKSPACE, K_BACK        },
	{ SDLK_BACKSPACE, K_BACKSPACE   },
	{ SDLK_TAB,       K_TAB         },
	{ SDLK_SPACE,     K_SPACE       },
	{ SDLK_RETURN,    K_RETURN      },

	{ SDLK_LSHIFT,   K_SHIFT_KEY    },
	{ SDLK_LCTRL,    K_CTRL_KEY     },
	{ SDLK_LALT,     K_ALT_KEY      },
	{ SDLK_CAPSLOCK, K_CAPSLOCK     },
	{ SDLK_ESCAPE,   K_ESCAPE       },
	{ SDLK_PAGEUP,   K_PAGEUP       },
	{ SDLK_PAGEDOWN, K_PAGEDOWN     },
	{ SDLK_END,      K_END          },
	{ SDLK_HOME,     K_HOME         },
	{ SDLK_LEFT,     K_LEFT         },
	{ SDLK_UP,       K_UP           },
	{ SDLK_RIGHT,    K_RIGHT        },
	{ SDLK_DOWN,     K_DOWN         },
	{ SDLK_INSERT,   K_INSERT       },
	{ SDLK_DELETE,   K_DELETE       },

	{ SDLK_KP_0, K_NUMPAD0 },
	{ SDLK_KP_1, K_NUMPAD1 },
	{ SDLK_KP_2, K_NUMPAD2 },
	{ SDLK_KP_3, K_NUMPAD3 },
	{ SDLK_KP_4, K_NUMPAD4 },
	{ SDLK_KP_5, K_NUMPAD5 },
	{ SDLK_KP_6, K_NUMPAD6 },
	{ SDLK_KP_7, K_NUMPAD7 },
	{ SDLK_KP_8, K_NUMPAD8 },
	{ SDLK_KP_9, K_NUMPAD9 },
	{ SDLK_KP_MULTIPLY, K_MULTIPLY  },
	{ SDLK_KP_PLUS,     K_ADD       },
	{ SDLK_KP_PERIOD,   K_SEPARATOR },
	{ SDLK_KP_MINUS,    K_SUBTRACT  },
	{ SDLK_KP_PERIOD,   K_DECIMAL   },
	{ SDLK_KP_DIVIDE,   K_DIVIDE    },
	{ SDLK_SCROLLLOCK,  K_SCROLL    },
	{ SDLK_KP_ENTER,    K_ENTER     },
	
	{ SDLK_F1,  K_F1  },
	{ SDLK_F2,  K_F2  },
	{ SDLK_F3,  K_F3  },
	{ SDLK_F4,  K_F4  },
	{ SDLK_F5,  K_F5  },
	{ SDLK_F6,  K_F6  },
	{ SDLK_F7,  K_F7  },
	{ SDLK_F8,  K_F8  },
	{ SDLK_F9,  K_F9  },
	{ SDLK_F10, K_F10 },
	{ SDLK_F11, K_F11 },
	{ SDLK_F12, K_F12 },

	{ SDLK_a, K_A },
	{ SDLK_b, K_B },
	{ SDLK_c, K_C },
	{ SDLK_d, K_D },
	{ SDLK_e, K_E },
	{ SDLK_f, K_F },
	{ SDLK_g, K_G },
	{ SDLK_h, K_H },
	{ SDLK_i, K_I },
	{ SDLK_j, K_J },
	{ SDLK_k, K_K },
	{ SDLK_l, K_L },
	{ SDLK_m, K_M },
	{ SDLK_n, K_N },
	{ SDLK_o, K_O },
	{ SDLK_p, K_P },
	{ SDLK_q, K_Q },
	{ SDLK_r, K_R },
	{ SDLK_s, K_S },
	{ SDLK_t, K_T },
	{ SDLK_u, K_U },
	{ SDLK_v, K_V },
	{ SDLK_w, K_W },
	{ SDLK_x, K_X },
	{ SDLK_y, K_Y },
	{ SDLK_z, K_Z },
	{ SDLK_0, K_0 },
	{ SDLK_1, K_1 },
	{ SDLK_2, K_2 },
	{ SDLK_3, K_3 },
	{ SDLK_4, K_4 },
	{ SDLK_5, K_5 },
	{ SDLK_6, K_6 },
	{ SDLK_7, K_7 },
	{ SDLK_8, K_8 },
	{ SDLK_9, K_9 },

	{ K_CTRL|219,  K_CTRL_LBRACKET   },
	{ K_CTRL|221,  K_CTRL_RBRACKET   },
	{ K_CTRL|0xbd, K_CTRL_MINUS      },
	{ K_CTRL|0xc0, K_CTRL_GRAVE      },
	{ K_CTRL|0xbf, K_CTRL_SLASH      },
	{ K_CTRL|0xdc, K_CTRL_BACKSLASH  },
	{ K_CTRL|0xbc, K_CTRL_COMMA      },
	{ K_CTRL|0xbe, K_CTRL_PERIOD     },
	{ K_CTRL|0xbe, K_CTRL_SEMICOLON  },
	{ K_CTRL|0xbb, K_CTRL_EQUAL      },
	{ K_CTRL|0xde, K_CTRL_APOSTROPHE },

	{ SDLK_PAUSE, K_BREAK }, // Is it really?

	{ SDLK_PLUS,      K_PLUS      },
	{ SDLK_MINUS,     K_MINUS     },
	{ SDLK_COMMA,     K_COMMA     },
	{ SDLK_PERIOD,    K_PERIOD    },
	{ SDLK_SEMICOLON, K_SEMICOLON },

	{ SDLK_SLASH,        K_SLASH     },
	{ SDLK_CARET,        K_GRAVE     },
	{ SDLK_LEFTBRACKET,  K_LBRACKET  },
	{ SDLK_BACKSLASH,    K_BACKSLASH },
	{ SDLK_RIGHTBRACKET, K_RBRACKET  },
	{ SDLK_QUOTEDBL,     K_QUOTEDBL  }
};

dword fbKEYtoK(dword chr)
{
	int i = SDL_key_map.Find(chr);

	if(i >= 0) {
		chr = SDL_key_map[i];
		if(findarg(chr, K_ALT_KEY, K_CTRL_KEY, K_SHIFT_KEY) >= 0)
			return chr;
	}
	else
		chr |= K_DELTA;

	if(UPP::GetCtrl())  chr |= K_CTRL;
	if(UPP::GetAlt())   chr |= K_ALT;
	if(UPP::GetShift()) chr |= K_SHIFT;

	return chr;
}


void HalSdl__HandleSDLEvent(HalSdl::NativeUppEventsBase& dev, SDL_Event* event)
{
	#if 1
	dword& mouseb = ::UPP::mouseb;
	dword& modkeys = ::UPP::modkeys;
	bool&  sdlMouseIsIn = ::UPP::sdlMouseIsIn;
	auto& isdblclick = ::UPP::isdblclick;
	auto& lastbdowntime = ::UPP::lastbdowntime;
	#else
	dword& mouseb = dev.mouseb;
	dword& modkeys = dev.modkeys;
	bool&  sdlMouseIsIn = dev.sdlMouseIsIn;
	auto& isdblclick = dev.isdblclick;
	auto& lastbdowntime = dev.lastbdowntime;
	#endif
	
	LLOG("HandleSDLEvent " << event->type);
	SDL_Event next_event;
	dword keycode;
	switch(event->type) {
//		case SDL_ACTIVEEVENT: //SDL_ActiveEvent
//			break;
	case SDL_TEXTINPUT: {
			//send respective keyup things as char events as well
		WString text = String(event->text.text).ToWString();
		for(int i = 0; i < text.GetCount(); i++) {
			int c = text[i];
			if(c != 127)
				Ctrl::DoKeyFB(c, 1);
		}
		break;
	}
	case SDL_KEYDOWN:
		switch(event->key.keysym.sym) {
			case SDLK_LSHIFT: modkeys |= KM_LSHIFT; break;
			case SDLK_RSHIFT: modkeys |= KM_RSHIFT; break;
			case SDLK_LCTRL: modkeys |= KM_LCTRL; break;
			case SDLK_RCTRL: modkeys |= KM_RCTRL; break;
			case SDLK_LALT: modkeys |= KM_LALT; break;
			case SDLK_RALT: modkeys |= KM_RALT; break;
		}
		
		keycode = fbKEYtoK((dword)event->key.keysym.sym);
		
		if(keycode != K_SPACE) { //dont send space on keydown
			static int repeat_count;
			SDL_PumpEvents();
			if(SDL_PeepEvents(&next_event, 1, SDL_PEEKEVENT, SDL_KEYDOWN, SDL_KEYDOWN) &&
			   next_event.key.keysym.sym == event->key.keysym.sym) {
				repeat_count++; // Keyboard repeat compression
				break;
			}
			Ctrl::DoKeyFB(keycode, 1 + repeat_count);
			repeat_count = 0;
		}
		break;
	case SDL_KEYUP: //SDL_KeyboardEvent
		switch(event->key.keysym.sym) {
			case SDLK_LSHIFT: modkeys &= ~KM_LSHIFT; break;
			case SDLK_RSHIFT: modkeys &= ~KM_RSHIFT; break;
			case SDLK_LCTRL: modkeys &= ~KM_LCTRL; break;
			case SDLK_RCTRL: modkeys &= ~KM_RCTRL; break;
			case SDLK_LALT: modkeys &= ~KM_LALT; break;
			case SDLK_RALT: modkeys &= ~KM_RALT; break;
		}

		Ctrl::DoKeyFB(fbKEYtoK((dword)event->key.keysym.sym) | K_KEYUP, 1);
		break;
	case SDL_MOUSEMOTION:
		SDL_PumpEvents();
		if(SDL_PeepEvents(&next_event, 1, SDL_PEEKEVENT, SDL_MOUSEMOTION, SDL_MOUSEMOTION) > 0)
			break; // MouseMove compression
		Ctrl::DoMouseFB(Ctrl::MOUSEMOVE, Point(event->motion.x, event->motion.y));
		break;
	case SDL_MOUSEWHEEL:
		Ctrl::DoMouseFB(Ctrl::MOUSEWHEEL, GetMousePos(), sgn((int)event->wheel.y) * 120);
		break;
	case SDL_MOUSEBUTTONDOWN: {
			Point p(event->button.x, event->button.y);
			int bi = event->button.button;
			dword ct = SDL_GetTicks();
			if(isdblclick[bi] && (abs(int(ct) - int(lastbdowntime[bi])) < 400))
			{
				switch(bi)
				{
					case SDL_BUTTON_LEFT: Ctrl::DoMouseFB(Ctrl::LEFTDOUBLE, p); break;
					case SDL_BUTTON_RIGHT: Ctrl::DoMouseFB(Ctrl::RIGHTDOUBLE, p); break;
					case SDL_BUTTON_MIDDLE: Ctrl::DoMouseFB(Ctrl::MIDDLEDOUBLE, p); break;
				}
				isdblclick[bi] = 0; //reset, to go ahead sending repeats
			}
			else
			{
				lastbdowntime[bi] = ct;
				isdblclick[bi] = 0; //prepare for repeat
				switch(bi)
				{
					case SDL_BUTTON_LEFT: mouseb |= (1<<0); Ctrl::DoMouseFB(Ctrl::LEFTDOWN, p); break;
					case SDL_BUTTON_RIGHT: mouseb |= (1<<1); Ctrl::DoMouseFB(Ctrl::RIGHTDOWN, p); break;
					case SDL_BUTTON_MIDDLE: mouseb |= (1<<2); Ctrl::DoMouseFB(Ctrl::MIDDLEDOWN, p); break;
				}
			}
		}
		break;
	case SDL_MOUSEBUTTONUP: {
			int bi = event->button.button;
			isdblclick[bi] = 1; //indicate maybe a dblclick
	
			Point p(event->button.x, event->button.y);
			switch(bi)
			{
				case SDL_BUTTON_LEFT: mouseb &= ~(1<<0); Ctrl::DoMouseFB(Ctrl::LEFTUP, p); break;
				case SDL_BUTTON_RIGHT: mouseb &= ~(1<<1); Ctrl::DoMouseFB(Ctrl::RIGHTUP, p); break;
				case SDL_BUTTON_MIDDLE: mouseb &= ~(1<<2); Ctrl::DoMouseFB(Ctrl::MIDDLEUP, p); break;
			}
		}
		break;
/*		case SDL_VIDEORESIZE: //SDL_ResizeEvent
		{
			width = event->resize.w;
			height = event->resize.h;
	
			SDL_FreeSurface(screen);
			screen = CreateScreen(width, height, bpp, videoflags);
			ASSERT(screen);
			Ctrl::SetFramebufferSize(Size(width, height));
		}
			break;
		case SDL_VIDEOEXPOSE: //SDL_ExposeEvent
			break;*/
	case SDL_WINDOWEVENT:
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            break;
        case SDL_WINDOWEVENT_MOVED:
            break;
//		case SDL_WINDOWEVENT_SIZE_CHANGED:
//			SDLwidth = event->window.data1;
//			SDLheight = event->window.data2;
//      	break;
        case SDL_WINDOWEVENT_RESIZED:
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            break;
        case SDL_WINDOWEVENT_RESTORED:
            break;
        case SDL_WINDOWEVENT_ENTER:
			sdlMouseIsIn = true;
			Ctrl::PaintAll();
            break;
        case SDL_WINDOWEVENT_LEAVE:
			sdlMouseIsIn = false;
			Ctrl::PaintAll();
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            break;
        case SDL_WINDOWEVENT_CLOSE:
            break;
        }
		break;
	case SDL_QUIT: //SDL_QuitEvent
		Ctrl::EndSession();
		break;
	}
	
	
	
}


NAMESPACE_PARALLEL_END
#endif

