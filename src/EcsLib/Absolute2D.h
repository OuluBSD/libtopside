#ifndef _EcsLib_Abs2D_h_
#define _EcsLib_Abs2D_h_


NAMESPACE_TOPSIDE_BEGIN
namespace Ecs {
	class Geom2DComponent;
}
NAMESPACE_TOPSIDE_END


NAMESPACE_UPP


class Absolute2D :
	public Absolute2DInterface
{
	
public:
	RTTI_DECL1(Absolute2D, Absolute2DInterface)
	Absolute2D();
	virtual ~Absolute2D() {}
	
	void						Title(const String& title) override;
	Absolute2DInterface&		Sizeable(bool b=true) override;
	Absolute2DInterface&		MaximizeBox(bool b=true) override;
	Absolute2DInterface&		MinimizeBox(bool b=true) override;
	int							Run(bool appmodal=false) override;
	String						GetTitle() const override;
	
	
	TS::Ecs::Geom2DComponent* GetWindow();
	TS::Ecs::Windows* GetWindows();
	
	static Image OverrideCursor(const Image& m);
	static Image DefaultCursor();
	
protected:
	TS::Ecs::Geom2DComponent* cw = NULL;
	int id;
	
	
public:
	void Init(TS::Ecs::Geom2DComponent* cw, int id);
	
	TS::Ecs::Geom2DComponent* GetWindow() const {return cw;}
	TS::Ecs::WindowManager* GetWindowManager() const;
	
};


END_UPP_NAMESPACE


#endif
