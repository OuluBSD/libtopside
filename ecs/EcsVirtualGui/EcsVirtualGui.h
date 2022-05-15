#ifndef _EcsVirtualGui_EcsVirtualGui_h_
#define _EcsVirtualGui_EcsVirtualGui_h_

#include <EcsLocal/EcsLocal.h>


NAMESPACE_ECS_BEGIN

class VirtualGuiSystem;


class VirtualGui : public VirtualGui3D
{
	
	
protected:
	friend class VirtualGuiSystem;
	//EcsVirtualGui_MachineData* data = 0;
	
	/*TS::OOSDL2::AudioOutput* aout = 0;
	TS::OOSDL2::Screen* scr = 0;
	TS::OOSDL2::Events* ev = 0;*/
	
	//TS::AudioProxy			empty_aud;
	Windows*					windows = 0;
	SystemDraw					empty_draw;
	VirtualGuiSystem*			sys;
	Ecs::RenderingSystemRef		rend;
	Ecs::EntityStoreRef			ents;
	Ref<Entity>					cam;
	GfxBuffer*					buf = 0;
	
	String						title;
	Size						screen_sz;
	
public:
	bool            Poll(UPP::CtrlEvent& e) override;// {return ev ? ev->Poll(e) : false;}
	Size            GetSize() override;// {return scr ? scr->GetSize() : Size(0,0);}
	void            SetTitle(String title) override;// {desired_title = title; if (scr) scr->SetTitle(title);}
	SystemDraw&     BeginDraw() override;// {return scr ? scr->BeginDraw() : empty_draw;}
	void            CommitDraw() override;// {if (scr) scr->CommitDraw();}
	uint32          GetTickCount() override;// {return ev ? ev->GetTickCount() : 0;}
	void            WaitEvent(int ms) override;// {if (ev) ev->WaitEvent(ms);}
	bool            IsWaitingEvent() override;// {return ev ? ev->IsWaitingEvent() : false;}
	void            WakeUpGuiThread() override;// {if (ev) ev->WakeUpEventThread();}
	
	/*dword           GetMouseButtons() override;
	dword           GetModKeys() override;
	bool            IsMouseIn() override;
	void            SetMouseCursor(const Image& image) override;
	void            Quit() override {Close();}*/

	
	
	
	bool			Open();
	void			Close();
	void			Clear();
	//bool			IsOpen() const {return is_open;}
	//EcsVirtualGui_MachineData* GetData() {return data;}
	void			RecvAudio(byte* stream, int len);
	//void			Render(bool do_render) override;
	
	//bool			InitMachine();
	//bool			DeinitMachine();
	//void			Render(bool do_render);
	void			RenderFrame();
	//void			RenderCamera();
	void			RenderWindows();
	
	VirtualGui(VirtualGuiSystem* sys);
	~VirtualGui();
	
	static VirtualGui* Current();
	
};



NAMESPACE_ECS_END


#include "System.h"


#endif
