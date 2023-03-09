#ifndef _CtrlCore_VirtualGui_h_
#define _CtrlCore_VirtualGui_h_


NAMESPACE_UPP_BEGIN

struct VirtualGui : RTTIBase
{
	RTTI_DECL0(VirtualGui)
	
	virtual dword       GetOptions();
	virtual Size        GetSize() = 0;
	virtual dword       GetMouseButtons() = 0;
	virtual dword       GetModKeys() = 0;
	virtual bool        IsMouseIn() = 0;
	virtual bool        ProcessEvent(bool *quit) = 0;
	virtual void        WaitEvent(int ms) = 0;
	virtual void        WakeUpGuiThread() = 0;
	virtual void        SetMouseCursor(const Image& image);
	virtual void        SetCaret(const Rect& caret);
	virtual void        Quit() = 0;
	virtual bool        IsWaitingEvent() = 0;
	virtual SystemDraw& BeginDraw() = 0;
	virtual void        CommitDraw() = 0;
};


extern VirtualGui* VirtualGuiPtr;


NAMESPACE_UPP_END

#endif
