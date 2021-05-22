#ifndef _SDL2GUI3D_SDL2GUI3D_h_
#define _SDL2GUI3D_SDL2GUI3D_h_

#include <OOSDL2/OOSDL2.h>


NAMESPACE_UPP


class SDL2GUI3D;


class SDL2GUI3D : VirtualGui3DAlt
{
	
	
protected:
	friend class SDL2GUI3DSystem;
	//SDL2GUI3D_MachineData* data = 0;
	
	Topside::OOSDL2::AudioOutput* aout = 0;
	Topside::OOSDL2::Screen* scr = 0;
	Topside::OOSDL2::Events* ev = 0;
	
	Topside::AudioProxy			empty_aud;
	SystemDraw					empty_draw;
	String						desired_title;
	void*						sys;
	
	
public:
	bool            Poll(Upp::CtrlEvent& e) override {return ev ? ev->Poll(e) : false;}
	Size            GetSize() override {return scr ? scr->GetSize() : Size(0,0);}
	void            SetTitle(String title) override {desired_title = title; if (scr) scr->SetTitle(title);}
	SystemDraw&     BeginDraw() override {return scr ? scr->BeginDraw() : empty_draw;}
	void            CommitDraw() override {if (scr) scr->CommitDraw();}
	uint32          GetTickCount() override {return ev ? ev->GetTickCount() : 0;}
	void            WaitEvent(int ms) override {if (ev) ev->WaitEvent(ms);}
	bool            IsWaitingEvent() override {return ev ? ev->IsWaitingEvent() : false;}
	void            WakeUpGuiThread() override {if (ev) ev->WakeUpEventThread();}
	
	/*dword           GetMouseButtons() override;
	dword           GetModKeys() override;
	bool            IsMouseIn() override;
	void            SetMouseCursor(const Image& image) override;
	void            Quit() override {Close();}*/

	
	
	
	bool			Open();
	void			Close();
	//bool			IsOpen() const {return is_open;}
	//SDL2GUI3D_MachineData* GetData() {return data;}
	void			RecvAudio(Uint8* stream, int len);
	
	
	//bool			InitMachine();
	//bool			DeinitMachine();
	//void			Render(bool do_render);
	//void			RenderFrame();
	//void			RenderCamera();
	//void			RenderWindows();
	
	SDL2GUI3D(void* sys);
	~SDL2GUI3D();
	
	static SDL2GUI3D* Current();
	
};



END_UPP_NAMESPACE


#endif
