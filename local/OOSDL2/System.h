#ifndef _OOSDL2_System_h_
#define _OOSDL2_System_h_

#include <EcsLib/EcsLib.h>
#include <OOSDL2/OOSDL2.h>

NAMESPACE_TOPSIDE_BEGIN


class SDL2TimerComponent :
	public Component<SDL2TimerComponent>
{
	One<OOSDL2::Timer> obj;
	
public:
	VIS_COMP_0_0
	COPY_PANIC(SDL2TimerComponent);
	
	SDL2TimerComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Timer* GetOOSDL2() {return &*obj;}
	
};

class SDL2AudioInputComponent :
	public Component<SDL2AudioInputComponent>,
	public AudioSource
{
	One<OOSDL2::AudioInput> obj;
	
public:
	VIS_COMP_1_0(Audio)
	COPY_PANIC(SDL2AudioInputComponent);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	
	SDL2AudioInputComponent() = default;
	
	void				Initialize() override;
	void				Uninitialize() override;
	void				Visit(RuntimeVisitor& vis) override {}
	AudioStream&		GetStream(AudCtx) override;
	void				BeginStream(AudCtx) override;
	void				EndStream(AudCtx) override;
	//void				EmitAudioSource(double dt) override;
	//void				Play(const RealtimeSourceConfig& config, Audio& aud) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::AudioInput* GetOOSDL2() {return &*obj;}
	
};

class SDL2AudioOutputComponent :
	public Component<SDL2AudioOutputComponent>,
	public AudioSink
{
	One<OOSDL2::AudioOutput> obj;
	AudioProxy empty_aud;
    RealtimeSourceConfig aconfig;
	
	
public:
	VIS_COMP_0_1(Audio)
	COPY_PANIC(SDL2AudioOutputComponent);
	IFACE_CB(AudioSink);
	IFACE_GENERIC;
	
	SDL2AudioOutputComponent() = default;
	
	void			Initialize() override;
	void			Uninitialize() override;
	void			Visit(RuntimeVisitor& vis) override {}
	
	AudioFormat		GetFormat(AudCtx) override;
	Audio&			GetValue(AudCtx) override;
	
	/*SystemAudio&	BeginPlay() override {return obj ? obj->GetSystemAudio() : empty_aud;}
	void			CommitPlay() override {}
	void			UndoPlay() override {ASSERT_(0, "UndoPlay is not implemented");}
	bool			IsAudioSampleFloating() override {return obj ? obj->IsSampleFloating() : 0;}
	int				GetAudioSampleRate() override {return obj ? obj->GetSampleRate() : 0;}
	int				GetAudioChannels() override {return obj ? obj->GetChannels() : 0;}
	int				GetAudioFrequency() override {return obj ? obj->GetFrequency() : 0;}
	int				GetAudioSampleSize() override {return obj ? obj->GetSampleSize() : 0;}*/
	
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
    DisplayFormat fmt;
	OOSDL2::Events* ev = 0;
	double dt = 0;
	double frame_age = 0;
	
public:
	VIS_COMP_0_1(Display)
	COPY_PANIC(SDL2ScreenComponent);
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	SDL2ScreenComponent() = default;
	
	void			Initialize() override;
	void			Uninitialize() override;
	void			Visit(RuntimeVisitor& vis) override {}
	//void			SetTitle(String s) override;
	
	DisplayFormat	GetFormat(DisCtx) override;
	Display&		GetValue(DisCtx) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Screen* GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.fps = fps;}
	
};

#endif

class SDL2EventsComponent :
	public Component<SDL2EventsComponent>,
	public DeviceSource
{
	One<OOSDL2::Events> obj;
	EventFrame ev;
	
public:
	VIS_COMP_1_0(Device)
	COPY_PANIC(SDL2EventsComponent);
	IFACE_CB(DeviceSource);
	IFACE_GENERIC;
	
	SDL2EventsComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//void EmitController(double dt) override;
	//bool IsSupported(CtrlType type) override {return type == CTRL_SYSTEM || type == CTRL_KEYBOARD || type == CTRL_MOUSE;}
	DeviceStream&		GetStream(DevCtx) override;
	void				BeginStream(DevCtx) override;
	void				EndStream(DevCtx) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Events* GetOOSDL2() {return &*obj;}
	
};

class SDL2JoystickComponent :
	public Component<SDL2JoystickComponent>,
	public HumanSource
{
	One<OOSDL2::Joystick> obj;
	
public:
	VIS_COMP_1_0(Human)
	COPY_PANIC(SDL2JoystickComponent);
	IFACE_CB(HumanSource);
	IFACE_GENERIC;
	
	SDL2JoystickComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//void EmitController(double dt) override;
	//bool IsSupported(CtrlType type) override {return type == CTRL_JOYSTICK;}
	HumanStream&		GetStream(HumCtx) override;
	void				BeginStream(HumCtx) override;
	void				EndStream(HumCtx) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Joystick* GetOOSDL2() {return &*obj;}
	
};

class SDL2GameControllerComponent :
	public Component<SDL2GameControllerComponent>,
	public HumanSource
{
	One<OOSDL2::GameController> obj;
	
public:
	VIS_COMP_1_0(Human)
	COPY_PANIC(SDL2GameControllerComponent);
	IFACE_CB(HumanSource);
	IFACE_GENERIC;
	
	SDL2GameControllerComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//void EmitController(double dt) override;
	//bool IsSupported(CtrlType type) override {return type == CTRL_GAMEPAD;}
	HumanStream&		GetStream(HumCtx) override;
	void				BeginStream(HumCtx) override;
	void				EndStream(HumCtx) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::GameController* GetOOSDL2() {return &*obj;}
	
};

class SDL2SensorComponent :
	public Component<SDL2SensorComponent>,
	public HumanSource
{
	One<OOSDL2::Sensor> obj;
	
public:
	VIS_COMP_1_0(Human)
	COPY_PANIC(SDL2SensorComponent);
	IFACE_CB(HumanSource);
	IFACE_GENERIC;
	
	SDL2SensorComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//void EmitController(double dt) override;
	//bool IsSupported(CtrlType type) override {return type == CTRL_SENSOR;}
	HumanStream&		GetStream(HumCtx) override;
	void				BeginStream(HumCtx) override;
	void				EndStream(HumCtx) override;
	
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
	VIS_COMP_1_0(Static)
	COPY_PANIC(SDL2ImageComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
	
	SDL2ImageComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//bool LoadFileAny(String path) override;
	//Size GetResolution() const override;
	//void EmitStatic() override;
	StaticStream&		GetStream(StcCtx) override;
	void				BeginStream(StcCtx) override;
	void				EndStream(StcCtx) override;
	
	String GetLastError() const {return last_error;}
	
	static bool AllowDuplicates() {return true;}
	
};

class SDL2FontComponent :
	public Component<SDL2FontComponent>,
	public StaticSource
{
	Font fnt;
	
public:
	VIS_COMP_1_0(Static)
	COPY_PANIC(SDL2FontComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
	
	SDL2FontComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//void EmitStatic() override;
	StaticStream&		GetStream(StcCtx) override;
	void				BeginStream(StcCtx) override;
	void				EndStream(StcCtx) override;
	
	static bool AllowDuplicates() {return true;}
	
};

class SDL2ContextComponent :
	public Component<SDL2ContextComponent>
{
	One<OOSDL2::Context> obj;
	LinkedList<ComponentBaseRef> comps;
	
public:
	VIS_COMP_0_0
	COPY_PANIC(SDL2ContextComponent);
	
	SDL2ContextComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	OOSDL2::Context* GetOOSDL2() {return &*obj;}
	
};


using SDL2ContextComponentRef		= Ref<SDL2ContextComponent,			RefParent1<Entity>>;







class SDL2System : public System<SDL2System> {
	LinkedList<SDL2ContextComponentRef> comps;
	
	Topside::OOSDL2::Context ctx;
	OOSDL2::Image img;
	OOSDL2::Font fnt;
	
	
	void Visit(RuntimeVisitor& vis) override {vis && comps;}
	
public:
	SYS_CTOR(SDL2System)
	
	const LinkedList<SDL2ContextComponentRef>& GetContext() const {return comps;}
	
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
	void AddContext(SDL2ContextComponentRef comp);
	void RemoveContext(SDL2ContextComponentRef comp);
	
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
	SDL2ContextComponent
	// Never: DirectWindow,
>
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



NAMESPACE_TOPSIDE_END

#endif
