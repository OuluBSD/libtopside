#ifndef _SDL2_SDL2_h_
#define _SDL2_SDL2_h_


#if !defined UPP_VERSION && defined flagGUI
	#include <CtrlLib/CtrlLib.h>
	#include <Graphics/GL.h>
#else
	#include <Draw/Draw.h>
	#include <Geometry/Geometry.h>
#endif


#define NAMESPACE_SDL2_NAME		OOSDL2
#define NAMESPACE_SDL2_BEGIN	namespace NAMESPACE_TOPSIDE_NAME { namespace NAMESPACE_SDL2_NAME {
#define NAMESPACE_SDL2_END		}}

NAMESPACE_SDL2_BEGIN


class Context;


class Stateful {
	
protected:
	bool is_open = false;
	
	virtual bool Open0() = 0;
	virtual void Close0() = 0;
	
public:
	Stateful() = default;
	virtual ~Stateful() {Close(); }
	
	bool Open() {if (!is_open && Open0()) is_open = true; return is_open;}
	void Close() {if (is_open) Close0(); is_open = false;}
	bool IsOpen() const {return is_open;}
	
};

class Component : public Stateful {
	
protected:
	friend class Context;
	Context* ctx = 0;
	
	virtual uint32 GetInitFlag() const = 0;
	
public:
	Component(Context* ctx) : ctx(ctx) {}
	
	Context* GetContext() const {return ctx;}
	
};


class Timer : public Component {
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_TIMER;}
	
public:
	Timer(Context* ctx) : Component(ctx) {}
	
};


class AudioInput : public Component {
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_AUDIO;}
	
public:
	AudioInput(Context* ctx) : Component(ctx) {}
	
	
};


class AudioOutput : public Component {
	SDL_AudioSpec audio_fmt, audio_desired;
	SDL_AudioDeviceID audio_dev = 0;
	VolatileAudioBuffer snd_buf;
	SystemAudio sys_aud;
	dword frames = 0;
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_AUDIO;}
	
public:
	AudioOutput(Context* ctx);
	
	void			Put(Uint8* stream, int len);
	void			SetDesiredAudioFmt(int sample_freq, int sample_bytes, bool is_var_floating, int channels, int sample_rate);
	int				GetSampleRate() {return audio_fmt.samples;}
	int				GetChannels() {return audio_fmt.channels;}
	int				GetFrequency() {return audio_fmt.freq;}
	int				GetSampleSize();
	dword			GetFrameCount() const {return frames;}
	bool			IsSampleFloating() const;
	bool			IsSampleSigned() const;
	Audio&			GetAudio() {return snd_buf;}
	SystemAudio&	GetSystemAudio() {return sys_aud;}
	
};


#ifdef flagGUI

class Screen : public Component {
	
protected:
	friend class Events;
	
    SDL_Window*				win = NULL;
    SDL_Renderer*			rend = NULL;
    SDL_Texture*			fb = NULL;
    SDL_RendererInfo		rend_info;
    Rect					desired_rect;
	Size					screen_sz;
	String					title;
	SDL_GLContext			glcontext = 0;
	CpuRenderer				sw_rend;
	CpuFramebufferDraw		sw_draw;
	OpenGLRenderer			hw_rend;
	OpenGLFramebufferDraw	hw_draw;
	SystemDraw				sysdraw;
	bool is_opengl = false;
	bool is_dx11 = false;
	bool full_screen = false;
	bool is_maximized = false;
	bool is_sizeable = false;
	bool mouse_captured = false;
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_VIDEO;}
	
	void SetWindowRect(Rect r);
	
public:
	Screen(Context* ctx) : Component(ctx) {desired_rect = RectC(0,0,1280,720);}
	
	void			Maximize(bool b=true);
	Screen&			Sizeable(bool b=true) {is_sizeable = b; return *this;}
	void            SetTitle(String title);
	void			SetRect(Rect r);
	SystemDraw&     BeginDraw();
	void            CommitDraw();
	
	Size            GetSize();
	bool			IsCaptured() const {return mouse_captured;}
	
};

#endif

void EnableOpenGLDebugMessages(bool b);


class Events : public Component {
	bool is_lalt = false, is_lshift = false, is_lctrl = false;
	bool is_ralt = false, is_rshift = false, is_rctrl = false;
	Point prev_mouse_pt;
	//Point mouse_pt;
	//uint32 key = 0;
	//uint32 mouse_code;
	//int mouse_zdelta, x, y, w, h, dx, dy;
	SDL_TimerID waketimer_id = -1;
	
	bool			Open0() override;
	void			Close0() override;
	uint32			GetInitFlag() const override {return SDL_INIT_EVENTS;}
	void			WokeUp() {waketimer_id = -1;}
	
	static unsigned int WakeCb(Uint32 interval, void* param);
	
public:
	Events(Context* ctx) : Component(ctx) {}
	
	void			PutKeyFlags(dword& key);
	bool            Poll(Upp::CtrlEvent& e);
	uint32          GetTickCount();
	void            WaitEvent(int ms);
	bool            IsWaitingEvent();
	void            WakeUpEventThread();
	
};


class Joystick : public Component {
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_JOYSTICK;}
	
public:
	Joystick(Context* ctx) : Component(ctx) {}
	
	
};


class GameController : public Component {
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_GAMECONTROLLER;}
	
public:
	GameController(Context* ctx) : Component(ctx) {}
	
	
};


class Sensor : public Component {
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_SENSOR;}
	
public:
	Sensor(Context* ctx) : Component(ctx) {}
	
	
};


class Image : public Stateful {
	
	bool Open0() override;
	void Close0() override;
	
public:
	Image() {}
	
	
};


class Font : public Stateful {
	
	bool Open0() override;
	void Close0() override;
	
public:
	Font() {}
	
	
};




class Context : public Stateful {
	Vector<Component*> comps;
	String last_error;
	
	bool Open0() override;
	void Close0() override;
	
	static int count;
	
public:
	typedef Context CLASSNAME;
	Context() = default;
	
	void Add(Component& c) {comps.Add(&c);}
	
	String GetLastError() const {return last_error;}
	
	template <class T>
	T* FindContextComponent() {
		T* o;
		for(Component* c : comps)
			if ((o = dynamic_cast<T*>(c)))
				return o;
		return 0;
	}
	static Context* Current();
	
};


class Bundle : public Context {
	Array<Component> comps;
	dword enabled = 0xFFFFFFFF;
	
public:
	Bundle() = default;
	
	bool Open();
	void Close();
	
	void AddDefaultComponents();
	
	void Set(int comp_i, bool v) {if (!v) Disable(comp_i); else Enable(comp_i);}
	void Enable(int comp_i) {enabled |= 1 << comp_i;}
	void Disable(int comp_i) {enabled &= ~(1 << comp_i);}
	bool IsEnabled(int comp_i) const {return enabled & (1 << comp_i);}
	
	template <class T>
	T* FindComponent() {
		T* o;
		for(Component& c : comps)
			if ((o = dynamic_cast<T*>(&c)))
				return o;
		return 0;
	}
	template <class T>
	T& GetAddComponent() {
		T* o = FindComponent<T>();
		if (o) return *o;
		o = new T(this);
		comps.Add(o);
		return *o;
	}
	
	enum {
		AUDIO_IN,
		AUDIO_OUT,
		SCREEN,
		EVENTS,
		JOYSTICK,
		GAMECTRL,
		SENSOR,
		IMAGE,
		FONT
	};
	
	
};


bool IsSDL2Open();


NAMESPACE_SDL2_END

#endif
