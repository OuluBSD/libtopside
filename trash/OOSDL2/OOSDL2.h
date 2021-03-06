#ifndef _SDL2_SDL2_h_
#define _SDL2_SDL2_h_



#if defined LIBTOPSIDE && (defined flagSCREEN || defined flagGUI)
	#include <Draw/Draw.h>
	//#include <Graphics/Graphics.h>
#else
	#include <Draw/Draw.h>
	#include <Geometry/Geometry.h>
#endif

#include <SerialMach/SerialMach.h>


#define NAMESPACE_SDL2_NAME		OOSDL2
#define NAMESPACE_SDL2_BEGIN	namespace NAMESPACE_TOPSIDE_NAME { namespace NAMESPACE_SERIAL_NAME { namespace NAMESPACE_SDL2_NAME {
#define NAMESPACE_SDL2_END		}}}

namespace TS {class SdlOglBuffer;}


#include "Base.h"
#include "ScreenT.h"


NAMESPACE_TOPSIDE_BEGIN
struct SdlOglGfx;
struct SdlCpuGfx;
NAMESPACE_TOPSIDE_END

NAMESPACE_SDL2_BEGIN


class Timer : public Component {
	RTTI_DECL1(Timer, Component)
	
private:
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_TIMER;}
	
public:
	Timer(Context* ctx, AtomBase* ab) : Component(ctx, ab) {}
	
};


class AudioInput : public Component {
	RTTI_DECL1(AudioInput, Component)
	
private:
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_AUDIO;}
	
public:
	AudioInput(Context* ctx, AtomBase* ab) : Component(ctx, ab) {}
	
	
};


class AudioOutput :
	public Component
{
	RTTI_DECL1(AudioOutput, Component)
	
private:
	SDL_AudioSpec			audio_fmt;
	SDL_AudioSpec			audio_desired;
	SDL_AudioDeviceID		audio_dev = 0;
	Parallel::Format		fmt;
	dword					frames = 0;
	
	#ifdef flagDEBUG
	byte val = 0;
	float flt = 0;
	#endif
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_AUDIO;}
	
public:
	AudioOutput(Context* ctx, AtomBase* ab);
	
	void			SinkCallback(Uint8* stream, int len);
	void			SetDesiredAudioFmt(int sample_freq, int sample_bytes, bool is_var_floating, int channels, int sample_rate);
	int				GetSampleRate() {return audio_fmt.samples;}
	int				GetChannels() {return audio_fmt.channels;}
	int				GetFrequency() {return audio_fmt.freq;}
	int				GetSampleSize();
	dword			GetFrameCount() const {return frames;}
	bool			IsSampleFloating() const;
	bool			IsSampleSigned() const;
	void			UpdateSinkFormat();
	//Value&			GetValue() {return buf;}
	
};


#ifdef flagSCREEN


using OglScreen = ScreenT<SdlOglGfx>;
using CpuScreen = ScreenT<SdlCpuGfx>;


#if 0
class Screen : public Component {
	RTTI_DECL1(Screen, Component)
	
	
	SdlOglBuffer*	ogl_buf = 0;
	
	
	
	enum {
		VAR_RESOLUTION,
		VAR_FRAMES,
		
		VAR_COUNT
	};
	static const char** VarNames() {
		static const char* names[VAR_COUNT+1] = {
			"iResolution",
			"iFrame",
			0
		};
		return names;
	}
	
	struct OpenGL_TestImage {
		int			frames = 0;
		GLint		prog = -1;
		uint32		stage = 0;
		GLuint		color_buf = 0;
		String		glsl;
		GLint		var_idx[VAR_COUNT];
		bool		is_vars_searched = 0;
	} gltest;
	
	
	bool ImageInitialize();
	void TestImageRender(const RealtimeSourceConfig& cfg);
	bool Ogl_Initialize();
	void Ogl_Render();
	void Ogl_FindVariables();
	void Ogl_SetVars();
	void Ogl_ClearPipeline();
	void Ogl_CreatePipeline();
	void Ogl_ClearTex();
	void Ogl_ClearProg();
	void Ogl_CreateTex(Size sz);
	bool Ogl_CompilePrograms();
	bool Ogl_CompileFragmentShader();
	bool Ogl_CompileProgram(String shader_source);
	GLint Ogl_CompileShader(String shader_source);
	bool Ogl_LinkStages();
	bool Ogl_LinkProgram();
	void Ogl_TexFlags(int type);
	void Ogl_SetVar(int var);
	void Ogl_RefreshPipeline();
	
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
	SdlOglRenderer			rend;
	SdlOglStateDraw			draw;
	SystemDraw				sysdraw;
	Packet					last_packet;
	bool is_opengl = false;
	bool is_dx11 = false;
	bool full_screen = false;
	bool is_maximized = false;
	bool is_sizeable = false;
	bool mouse_captured = false;
	bool is_ogl_buf = false;
	String frag_path;
	String vtx_path;
	String library_paths;
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_VIDEO;}
	
	void SetWindowRect(Rect r);
	
public:
	Screen(Context* ctx, AtomBase* ab) : Component(ctx, ab) {desired_rect = RectC(0,0,1280,720);}
	
	void			Maximize(bool b=true);
	void			Fullscreen(bool b=true);
	Screen&			Sizeable(bool b=true) {is_sizeable = b; return *this;}
	void            SetTitle(String title);
	void			SetRect(Rect r);
	void            Render(const RealtimeSourceConfig& cfg);
	bool            Recv(int ch_i, const Packet& p);
	SystemDraw&     BeginDraw();
	void            CommitDraw();
	void            SetBuffer(SdlOglBuffer& buf) {ogl_buf = &buf;}
	
	Size            GetSize();
	bool			IsCaptured() const {return mouse_captured;}
	
	void			SetShaderFile(String frag_path, String vtx_path, String library_paths) {this->frag_path = frag_path; this->vtx_path = vtx_path; this->library_paths = library_paths;}
	void			SetFragmentShader(bool b) {is_ogl_buf = b;}
	
};

class CpuScreen : public Component {
	RTTI_DECL1(CpuScreen, Component)
	
protected:
	friend class Events;
	
    SDL_Window*				win = NULL;
    SDL_Renderer*			rend = NULL;
    SDL_Texture*			fb = NULL;
    SDL_RendererInfo		rend_info;
    Rect					desired_rect;
	Size					screen_sz;
	int						fb_stride;
	String					title;
	SdlCpuBuffer*			buf = 0;
	SdlCpuRenderer			rend;
	SdlCpuStateDraw			sw_draw;
	SystemDraw				sysdraw;
	Packet					last_packet;
	bool full_screen = false;
	bool is_maximized = false;
	bool is_sizeable = false;
	bool mouse_captured = false;
	
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_VIDEO;}
	
	void SetWindowRect(Rect r);
	void RenderTestColors();
	
public:
	CpuScreen(Context* ctx, AtomBase* ab) : Component(ctx, ab) {desired_rect = RectC(0,0,1280,720);}
	
	void			Maximize(bool b=true);
	void			Fullscreen(bool b=true);
	CpuScreen&		Sizeable(bool b=true) {is_sizeable = b; return *this;}
	void            SetTitle(String title);
	void			SetRect(Rect r);
	void            Render(const RealtimeSourceConfig& cfg);
	bool            Recv(int ch_i, const Packet& p);
	SystemDraw&     BeginDraw();
	void            CommitDraw();
	void            SetTestShader(int type);
	void            SetBuffer(SdlCpuBuffer& buf) {this->buf = &buf;}
	
	Size            GetSize();
	bool			IsCaptured() const {return mouse_captured;}
	
};

#endif
#endif



class Events : public Component {
	RTTI_DECL1(Events, Component)
	
private:
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
	Events(Context* ctx, AtomBase* ab) : Component(ctx, ab) {}
	
	void			PutKeyFlags(dword& key);
	bool            Poll(UPP::CtrlEvent& e);
	uint32          GetTickCount();
	void            WaitEvent(int ms);
	bool            IsWaitingEvent();
	void            WakeUpEventThread();
	
};


class Joystick : public Component {
	RTTI_DECL1(Joystick, Component)
	
private:
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_JOYSTICK;}
	
public:
	Joystick(Context* ctx, AtomBase* ab) : Component(ctx, ab) {}
	
	
};


class GameController : public Component {
	RTTI_DECL1(GameController, Component)
	
private:
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_GAMECONTROLLER;}
	
public:
	GameController(Context* ctx, AtomBase* ab) : Component(ctx, ab) {}
	
	
};


class Sensor : public Component {
	RTTI_DECL1(Sensor, Component)
	
private:
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return SDL_INIT_SENSOR;}
	
public:
	Sensor(Context* ctx, AtomBase* ab) : Component(ctx, ab) {}
	
	
};


class Image : public Component {
	RTTI_DECL1(Image, Stateful)
	
private:
	bool Open0() override;
	void Close0() override;
	uint32 GetInitFlag() const override {return 0;}
	
public:
	Image(Context* ctx, AtomBase* ab) : Component(ctx, ab) {}
	
	
};


class Font : public Stateful {
	RTTI_DECL1(Font, Stateful)
	
private:
	bool Open0() override;
	void Close0() override;
	
public:
	Font() {}
	
	
};




class Context : public Stateful {
	RTTI_DECL1(Context, Stateful)
	
private:
	Vector<Component*> comps;
	String last_error;
	
	bool Open0() override;
	void Close0() override;
	
	static int count;
	
	
public:
	typedef Context CLASSNAME;
	Context() = default;
	
	void Add(Component& c) {comps.Add(&c);}
	void CloseComponents();
	void SetError(String s) {last_error = s;}
	
	String GetLastError() const {return last_error;}
	
	template <class T>
	T* FindContextConnector() {
		T* o;
		for(Component* c : comps)
			if ((o = CastPtr<T>(c)))
				return o;
		return 0;
	}
	static Context* Current();
	
};


class Bundle : public Context {
	RTTI_DECL1(Bundle, Context)
	
private:
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
			if ((o = CastPtr<T>(&c)))
				return o;
		return 0;
	}
	
	template <class T>
	T& GetAddComponent() {
		T* o = FindComponent<T>();
		if (o) return *o;
		o = new T(this, 0);
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
