#ifndef _VirtualGui3D_Window_h_
#define _VirtualGui3D_Window_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN
namespace Ecs {
	class CoreWindow;
}
NAMESPACE_TOPSIDE_END


NAMESPACE_UPP


class AbsoluteWindow :
	public AbsoluteWindowInterface
{
	
public:
	RTTI_DECL1(AbsoluteWindow, AbsoluteWindowInterface)
	AbsoluteWindow();
	virtual ~AbsoluteWindow() {}
	
	void						Title(const String& title) override;
	AbsoluteWindowInterface&	Sizeable(bool b=true) override;
	AbsoluteWindowInterface&	MaximizeBox(bool b=true) override;
	AbsoluteWindowInterface&	MinimizeBox(bool b=true) override;
	int							Run(bool appmodal=false) override;
	String						GetTitle() const override;
	
	
	TS::Ecs::CoreWindow* GetWindow();
	TS::Ecs::Windows* GetWindows();
	
	static Image OverrideCursor(const Image& m);
	static Image DefaultCursor();
	
protected:
	TS::Ecs::CoreWindow* cw = NULL;
	int id;
	
	
public:
	void Init(TS::Ecs::CoreWindow* cw, int id);
	
	TS::Ecs::CoreWindow* GetWindow() const {return cw;}
	TS::Ecs::WindowManager* GetWindowManager() const;
	
};


END_UPP_NAMESPACE


#endif
#endif
