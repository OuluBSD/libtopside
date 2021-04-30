#ifndef _OOSDL2_System_h_
#define _OOSDL2_System_h_

#include <EcsLib/EcsLib.h>
#include <OOSDL2/OOSDL2.h>

NAMESPACE_OULU_BEGIN


class SDL2TimerComponent :
	public Component<SDL2TimerComponent>
{
	One<OOSDL2::Timer> obj;
	
public:
	COPY_PANIC(SDL2TimerComponent);
	
	SDL2TimerComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Timer* GetOOSDL2() {return &*obj;}
	
};

class SDL2AudioInputComponent :
	public Component<SDL2AudioInputComponent>,
	public AudioSource
{
	One<OOSDL2::AudioInput> obj;
	
public:
	COPY_PANIC(SDL2AudioInputComponent);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	
	SDL2AudioInputComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitAudioSource(double dt) override;
	void Play(const AudioSinkConfig& config, Sound& snd) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::AudioInput* GetOOSDL2() {return &*obj;}
	
};

class SDL2AudioOutputComponent :
	public Component<SDL2AudioOutputComponent>,
	public AudioSink
{
	One<OOSDL2::AudioOutput> obj;
	SystemSound empty_snd;
    AudioSinkConfig aconfig;
	
	
public:
	COPY_PANIC(SDL2AudioOutputComponent);
	IFACE_CB(AudioSink);
	IFACE_GENERIC;
	
	SDL2AudioOutputComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void RecvAudio(AudioSource& src, double dt) override;
	
	SystemSound&	BeginPlay() override {return obj ? obj->GetSystemSound() : empty_snd;}
	void			CommitPlay() override {}
	void			UndoPlay() override {ASSERT_(0, "UndoPlay is not implemented");}
	bool			IsAudioSampleFloating() override {return obj ? obj->IsSampleFloating() : 0;}
	int				GetAudioSampleRate() override {return obj ? obj->GetSampleRate() : 0;}
	int				GetAudioChannels() override {return obj ? obj->GetChannels() : 0;}
	int				GetAudioFrequency() override {return obj ? obj->GetFrequency() : 0;}
	int				GetAudioSampleSize() override {return obj ? obj->GetSampleSize() : 0;}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::AudioOutput* GetOOSDL2() {return &*obj;}
	
	void SetAudioSyncInterval(double seconds) {aconfig.sync_dt = seconds;}
	
};

#ifdef flagGUI

class SDL2ScreenComponent :
	public Component<SDL2ScreenComponent>,
	public DisplaySink
{
	One<OOSDL2::Screen> obj;
    DisplaySinkConfig config;
	OOSDL2::Events* ev = 0;
	double frame_age = 0;
	
public:
	COPY_PANIC(SDL2ScreenComponent);
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	SDL2ScreenComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void RecvDisplay(DisplaySource& src, double dt) override;
	void SetTitle(String s) override;
	uint32 GetTickCount() override {return ev ? ev->GetTickCount() : 0;}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Screen* GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {config.fps = fps; config.fps_dt = 1.0 / fps;}
	
};

#endif

class SDL2EventsComponent :
	public Component<SDL2EventsComponent>,
	public ControllerSource
{
	One<OOSDL2::Events> obj;
	EventFrame ev;
	
public:
	COPY_PANIC(SDL2EventsComponent);
	IFACE_CB(ControllerSource);
	IFACE_GENERIC;
	
	SDL2EventsComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitController() override;
	bool IsSupported(CtrlType type) override {return type == CTRL_SYSTEM || type == CTRL_KEYBOARD || type == CTRL_MOUSE;}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Events* GetOOSDL2() {return &*obj;}
	
};

class SDL2JoystickComponent :
	public Component<SDL2JoystickComponent>,
	public ControllerSource
{
	One<OOSDL2::Joystick> obj;
	
public:
	COPY_PANIC(SDL2JoystickComponent);
	IFACE_CB(ControllerSource);
	IFACE_GENERIC;
	
	SDL2JoystickComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitController() override;
	bool IsSupported(CtrlType type) override {return type == CTRL_JOYSTICK;}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Joystick* GetOOSDL2() {return &*obj;}
	
};

class SDL2GameControllerComponent :
	public Component<SDL2GameControllerComponent>,
	public ControllerSource
{
	One<OOSDL2::GameController> obj;
	
public:
	COPY_PANIC(SDL2GameControllerComponent);
	IFACE_CB(ControllerSource);
	IFACE_GENERIC;
	
	SDL2GameControllerComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitController() override;
	bool IsSupported(CtrlType type) override {return type == CTRL_GAMEPAD;}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::GameController* GetOOSDL2() {return &*obj;}
	
};

class SDL2SensorComponent :
	public Component<SDL2SensorComponent>,
	public ControllerSource
{
	One<OOSDL2::Sensor> obj;
	
public:
	COPY_PANIC(SDL2SensorComponent);
	IFACE_CB(ControllerSource);
	IFACE_GENERIC;
	
	SDL2SensorComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitController() override;
	bool IsSupported(CtrlType type) override {return type == CTRL_SENSOR;}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Sensor* GetOOSDL2() {return &*obj;}
	
};

class SDL2ImageComponent :
	public Component<SDL2ImageComponent>,
	public StaticSource
{
	Vector<Image> img;
	String last_error;
	
	
public:
	COPY_PANIC(SDL2ImageComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
	
	SDL2ImageComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	bool LoadFileAny(String path) override;
	Size GetResolution() const override;
	void EmitStatic() override;
	
	String GetLastError() const {return last_error;}
	
	static bool AllowDuplicates() {return true;}
	
};

class SDL2FontComponent :
	public Component<SDL2FontComponent>,
	public StaticSource
{
	Font fnt;
	
public:
	COPY_PANIC(SDL2FontComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
	
	SDL2FontComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitStatic() override;
	
	static bool AllowDuplicates() {return true;}
	
};

class SDL2ContextComponent :
	public Component<SDL2ContextComponent>
{
	One<OOSDL2::Context> obj;
	Vector<ComponentBase*> comps;
	
public:
	COPY_PANIC(SDL2ContextComponent);
	
	SDL2ContextComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	OOSDL2::Context* GetOOSDL2() {return &*obj;}
	
};








class SDL2System : public System<SDL2System> {
	Oulu::OOSDL2::Context ctx;
	Vector<SDL2ContextComponent*> comps;
	OOSDL2::Image img;
	OOSDL2::Font fnt;
	
public:
	SDL2System(Machine& m);
	
	const Vector<SDL2ContextComponent*>& GetContext() const {return comps;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
protected:
	friend class SDL2ContextComponent;
	void AddContext(SDL2ContextComponent& comp);
	void RemoveContext(SDL2ContextComponent& comp);
	
};






#ifdef flagGUI

struct SDL2StandaloneWindow : EntityPrefab<
	SDL2TimerComponent,
	SDL2EventsComponent,
	//SDL2AudioInputComponent,
	SDL2AudioOutputComponent,
	SDL2ScreenComponent,
	SDL2JoystickComponent,
	SDL2GameControllerComponent,
	SDL2SensorComponent,
	SDL2ImageComponent,
	SDL2FontComponent,
	SDL2ContextComponent,
	DirectWindow>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		return components;
    }
};

#endif

struct SDL2StandaloneConsole : EntityPrefab<
	SDL2TimerComponent,
	SDL2EventsComponent,
	//SDL2AudioInputComponent,
	SDL2AudioOutputComponent,
	// Never: SDL2ScreenComponent,
	SDL2JoystickComponent,
	SDL2GameControllerComponent,
	SDL2SensorComponent,
	SDL2ImageComponent,
	SDL2FontComponent,
	SDL2ContextComponent,
	// Never: DirectWindow,>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		return components;
    }
};



struct StandaloneLineIn : EntityPrefab<
	SDL2AudioInputComponent,
	SDL2ContextComponent>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		return components;
    }
};



NAMESPACE_OULU_END

#endif
