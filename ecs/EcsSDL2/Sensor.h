#ifndef _EcsSDL2_Sensor_h_
#define _EcsSDL2_Sensor_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2SensorComponent :
	public Component<SDL2SensorComponent>,
	public HumanSource
{
	One<OOSDL2::Sensor> obj;
	
public:
	RTTI_COMP1(SDL2SensorComponent, HumanSource)
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
	HumanStream&		GetStream(HumCtx) override {TODO}
	void				BeginStream(HumCtx) override {TODO}
	void				EndStream(HumCtx) override {TODO}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Sensor* GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_TOPSIDE_END

#endif
