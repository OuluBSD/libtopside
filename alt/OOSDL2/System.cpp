#include "System.h"

NAMESPACE_OULU_BEGIN


SDL2System::SDL2System(Machine& m) : System<SDL2System>(m) {
	
}

bool SDL2System::Initialize() {
	return img.Open() && fnt.Open();
}

void SDL2System::Start() {
	
}

void SDL2System::Update(float dt) {
	
}

void SDL2System::Stop() {
	
}

void SDL2System::Uninitialize() {
	img.Close();
	fnt.Close();
}

void SDL2System::AddContext(SDL2ContextComponent& comp) {
	VectorFindAdd(comps, &comp);
}

void SDL2System::RemoveContext(SDL2ContextComponent& comp) {
	VectorRemoveKey(comps, &comp);
}






#define OBJ_CREATE \
	auto* ev_ctx = GetEntity().Find<SDL2ContextComponent>(); \
	/*ASSERT(ev_ctx);*/ \
	if (ev_ctx) { \
		obj.Create(ev_ctx->GetOOSDL2()); \
	}

void SDL2TimerComponent::Initialize() {
	OBJ_CREATE
}

void SDL2TimerComponent::Uninitialize() {
	obj.Clear();
}



void SDL2AudioInputComponent::Initialize() {
	OBJ_CREATE
}

void SDL2AudioInputComponent::Uninitialize() {
	obj.Clear();
}

void SDL2AudioInputComponent::EmitAudioSource(float dt) {
	TODO
}

void SDL2AudioInputComponent::Play(const AudioSinkConfig& config, Sound& snd) {
	TODO
}



void SDL2AudioOutputComponent::Initialize() {
	aconfig.frames_after_sync = 0;
	SetAudioSyncInterval(15);
	if (VirtualSoundPtr == 0)
		VirtualSoundPtr = this;
	OBJ_CREATE
}

void SDL2AudioOutputComponent::Uninitialize() {
	if (VirtualSoundPtr == this)
		VirtualSoundPtr = 0;
	obj.Clear();
}

void SDL2AudioOutputComponent::RecvAudioSink(AudioSource& src, float dt) {
	DefaultRecvAudioSink(src, dt, obj->GetSystemSound());
}



#ifdef flagGUI

void SDL2ScreenComponent::Initialize() {
	config.dt = 0;
	SetFPS(60);
	OBJ_CREATE
	auto* ev_comp = GetEntity().Find<SDL2EventsComponent>();
	if (ev_comp)
		ev = ev_comp->GetOOSDL2();
}

void SDL2ScreenComponent::Uninitialize() {
	ev = 0;
	obj.Clear();
}

void SDL2ScreenComponent::RecvDisplaySink(DisplaySource& src, float dt) {
	frame_age += dt;
	config.dt += dt;
	
	if (frame_age >= config.fps_dt) {
		if (frame_age > 2 * config.fps_dt)
			frame_age = config.fps_dt;
		else
			frame_age = Modulus(frame_age, config.fps_dt);
		
		
		SystemDraw& draw = obj->BeginDraw();
		
		if (!src.Render(config, draw))
			frame_age = config.fps_dt; // force redraw
		
		obj->CommitDraw();
	}
}

void SDL2ScreenComponent::SetTitle(String s) {
	if (obj)
		obj->SetTitle(s);
}

#endif




void SDL2EventsComponent::Initialize() {
	OBJ_CREATE
	
	Ref<EventSystem> ev_sys = GetEntity().GetMachine().Get<EventSystem>();
	if (!ev_sys)
		return;
	
	ev_sys -> AddControllable(*this);
}

void SDL2EventsComponent::Uninitialize() {
	obj.Clear();
	
	Ref<EventSystem> ev_sys = GetEntity().GetMachine().Get<EventSystem>();
	if (ev_sys)
		ev_sys->RemoveControllable(*this);
}

void SDL2EventsComponent::EmitController() {
	if (obj) {
		ev.ctrl.SetCount(1);
		CtrlEvent& e = ev.ctrl[0];
		
		while (obj->Poll(e)) {
			if (e.type == EVENT_SHUTDOWN) {
				GetMachine().SetNotRunning();
			}
			for(ControllerSink* sink : ControllerSource::GetSinks())
				sink->RecvController(ev);
		}
	}
}





void SDL2JoystickComponent::Initialize() {
	OBJ_CREATE
}

void SDL2JoystickComponent::Uninitialize() {
	obj.Clear();
}

void SDL2JoystickComponent::EmitController() {
	TODO
}





void SDL2GameControllerComponent::Initialize() {
	OBJ_CREATE
}

void SDL2GameControllerComponent::Uninitialize() {
	obj.Clear();
}

void SDL2GameControllerComponent::EmitController() {
	TODO
}





void SDL2SensorComponent::Initialize() {
	OBJ_CREATE
}

void SDL2SensorComponent::Uninitialize() {
	obj.Clear();
}

void SDL2SensorComponent::EmitController() {
	TODO
}







void SDL2ImageComponent::Initialize() {
	
}

void SDL2ImageComponent::Uninitialize() {
	img.Clear();
}

bool SDL2ImageComponent::LoadFileAny(String path) {
	img.Clear();
	
	if (path.Left(9) == "<cubemap>") {
		path = path.Mid(9);
		
		String dir = GetFileDirectory(path);
		String title = GetFileTitle(path);
		String ext = GetFileExt(path);
		
		for(int i = 0; i < 6; i++) {
			if (i)
				path = AppendFileName(dir, title + "_" + IntStr(i) + ext);
			
			SDL_Surface* surf = IMG_Load(path);
			if (!surf) {
				last_error = IMG_GetError();
				return false;
			}
			
			img << Image(surf);
		}
		EmitStatic();
		return true;
	}
	else {
		SDL_Surface* surf = IMG_Load(path);
		if (!surf) {
			last_error = IMG_GetError();
			return false;
		}
		img << Image(surf);
		EmitStatic();
		return true;
	}
}

Size SDL2ImageComponent::GetResolution() const {
	if (img.GetCount())
		return img[0].GetSize();
	return Size(0,0);
}

void SDL2ImageComponent::EmitStatic() {
	int id = 0;
	for(Image& img : this->img) {
		int w = img.GetWidth();
		int h = img.GetHeight();
		int d = 1;
		int stride = img.GetStride();
		int pitch = img.GetPitch();
		const byte* img_data = img.Begin();
		
		StaticSinkData data;
		data.obj_i = id;
		data.w = w;
		data.h = h;
		data.d = d;
		data.stride = stride;
		data.pitch = pitch;
		data.data = img_data;
		
		for(StaticSink* sink : StaticSource::GetSinks())
			sink->RecvStatic(data);
		id++;
	}
}









void SDL2FontComponent::Initialize() {
	
}

void SDL2FontComponent::Uninitialize() {
	fnt.Clear();
}

void SDL2FontComponent::EmitStatic() {
	TODO
}





SDL2ContextComponent::SDL2ContextComponent() {
	obj.Create();
	
	
}

void SDL2ContextComponent::Initialize() {
	DLOG("SDL2ContextComponent::Initialize");
	Entity& e = GetEntity();
	
	Ref<SDL2System> sdl2_sys = e.GetMachine().Get<SDL2System>();
	if (sdl2_sys)
		sdl2_sys	-> AddContext(*this);
	
	SDL2TimerComponent* tim				= e.Find<SDL2TimerComponent>();
	SDL2AudioInputComponent* ain		= e.Find<SDL2AudioInputComponent>();
	SDL2AudioOutputComponent* aout		= e.Find<SDL2AudioOutputComponent>();
#ifdef flagGUI
	SDL2ScreenComponent* scr			= e.Find<SDL2ScreenComponent>();
#endif
	
	SDL2EventsComponent* ev				= e.Find<SDL2EventsComponent>();
	SDL2JoystickComponent* joy			= e.Find<SDL2JoystickComponent>();
	SDL2GameControllerComponent* gc		= e.Find<SDL2GameControllerComponent>();
	SDL2SensorComponent* sens			= e.Find<SDL2SensorComponent>();
	
	#define AddObj(x) if(x) {obj->Add(x->GetObj()); comps.Add(x);}
	
	AddObj(tim);
	AddObj(ain);
	AddObj(aout);
#ifdef flagGUI
	AddObj(scr);
#endif
	
	AddObj(ev);
	AddObj(joy);
	AddObj(gc);
	AddObj(sens);
	
	#undef AddObj
	
	if (!obj->Open()) {
		LOG("SDL2ContextComponent::Initialize: error: " << obj->GetLastError());
		GetMachine().SetNotRunning();
	}
}

void SDL2ContextComponent::Uninitialize() {
	Ref<SDL2System> sdl2_sys = GetEntity().GetMachine().Get<SDL2System>();
	if (sdl2_sys)
		sdl2_sys	-> RemoveContext(*this);
	
	obj->Close();
}


NAMESPACE_OULU_END
