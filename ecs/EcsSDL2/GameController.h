#ifndef _EcsSDL2_GameController_h_
#define _EcsSDL2_GameController_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2GameControllerComponent :
	public Component<SDL2GameControllerComponent>,
	public HumanSource
{
	One<OOSDL2::GameController> obj;
	
public:
	RTTI_COMP1(SDL2GameControllerComponent, HumanSource)
	VIS_COMP_1_0(Human)
	COPY_PANIC(SDL2GameControllerComponent);
	IFACE_CB(HumanSource);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	
	SDL2GameControllerComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	//void EmitController(double dt) override;
	//bool IsSupported(CtrlType type) override {return type == CTRL_GAMEPAD;}
	HumanStream&		GetStream(HumCtx) override {TODO}
	void				BeginStream(HumCtx) override {TODO}
	void				EndStream(HumCtx) override {TODO}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::GameController* GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_TOPSIDE_END

#endif
