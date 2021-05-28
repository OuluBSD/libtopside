#ifndef _EcsSDL2_Timer_h_
#define _EcsSDL2_Timer_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2TimerComponent :
	public Component<SDL2TimerComponent>
{
	One<OOSDL2::Timer> obj;
	
public:
	RTTI_COMP0(SDL2TimerComponent)
	VIS_COMP_0_0
	COPY_PANIC(SDL2TimerComponent);
	
	SDL2TimerComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Timer* GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_TOPSIDE_END

#endif
