#ifndef _EcsSDL2_Screen_h_
#define _EcsSDL2_Screen_h_

NAMESPACE_TOPSIDE_BEGIN


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
	RTTI_COMP1(SDL2ScreenComponent, DisplaySink)
	VIS_COMP_0_1(Display)
	COPY_PANIC(SDL2ScreenComponent);
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	
	SDL2ScreenComponent() = default;
	
	void			Initialize() override;
	void			Uninitialize() override;
	//void			SetTitle(String s) override;
	
	DisplayFormat	GetFormat(DisCtx) override;
	Display&		GetValue(DisCtx) override;
	
	OOSDL2::Component& GetObj() {return *obj;}
	OOSDL2::Screen* GetOOSDL2() {return &*obj;}
	
	void SetFPS(int fps) {fmt.SetFPS(fps);}
	
};

#endif


NAMESPACE_TOPSIDE_END

#endif
