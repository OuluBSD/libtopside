#ifndef _EcsSDL2_Joystick_h_
#define _EcsSDL2_Joystick_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2JoystickComponent :
	public Component<SDL2JoystickComponent>,
	public HumanSource
{
	One<OOSDL2::Joystick> obj;
	
public:
	RTTI_COMP1(SDL2JoystickComponent, HumanSource)
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
	HumanStream&		GetStream(HumCtx) override {TODO}
	void				BeginStream(HumCtx) override {TODO}
	void				EndStream(HumCtx) override {TODO}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Joystick* GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_TOPSIDE_END

#endif
