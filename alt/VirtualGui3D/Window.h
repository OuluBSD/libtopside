#ifndef _VirtualGui3D_Window_h_
#define _VirtualGui3D_Window_h_


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
	String						GetTitle() override;
	
	
	TS::Ecs::CoreWindow* GetWindow();
	static TS::Ecs::Windows* GetWindows();
	
	
private:
	TS::Ecs::CoreWindow* cw = NULL;
	int id;
	
	void CreateCoreWindow();
	void UpdateFromTransform2D();
	
	
public:
	void Init(TS::Ecs::CoreWindow* cw, int id);
	
	TS::Ecs::CoreWindow* GetWindow() const {return cw;}
	TS::Ecs::WindowManager* GetWindowManager() const;
	
};


END_UPP_NAMESPACE


#endif
