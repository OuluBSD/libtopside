#ifndef _EcsVirtualGui_EcsVirtualGui_h_
#define _EcsVirtualGui_EcsVirtualGui_h_

#include <EcsLocal/EcsLocal.h>


NAMESPACE_ECS_BEGIN

class VirtualGuiSystem;


class VirtualGui : public VirtualGui3D
{
	
	
protected:
	friend class VirtualGuiSystem;
	
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
	bool            Poll(UPP::CtrlEvent& e) override;
	Size            GetSize() override;
	void            SetTitle(String title) override;
	SystemDraw&     BeginDraw() override;
	void            CommitDraw() override;
	uint32          GetTickCount() override;
	void            WaitEvent(int ms) override;
	bool            IsWaitingEvent() override;
	void            WakeUpGuiThread() override;
	
	bool			Open();
	void			Close();
	void			Clear();
	void			RecvAudio(byte* stream, int len);
	
	void			RenderFrame();
	void			RenderWindows();
	
	VirtualGui(VirtualGuiSystem* sys);
	~VirtualGui();
	
	static VirtualGui* Current();
	
};



NAMESPACE_ECS_END


#include "System.h"


#endif
