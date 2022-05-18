#ifndef _EcsLib_Gui_h_
#define _EcsLib_Gui_h_

NAMESPACE_ECS_BEGIN


#ifdef flagGUI
struct DefaultGuiAppComponent :
	public Component<DefaultGuiAppComponent>,
	public BinderIfaceVideo
{
	RTTI_DECL2(DefaultGuiAppComponent, ComponentT, BinderIfaceVideo)
	
	WindowSystemRef wins;
	
	
	DefaultGuiAppComponent();
	void operator=(const DefaultGuiAppComponent& t) {Panic("Can't copy DefaultGuiAppComponent");}
	void Visit(RuntimeVisitor& vis) override {/*if (test) vis % *test;*/}
	void Initialize() override;
	void Uninitialize() override;
	void Update(double dt) override;
	bool Render(Draw& d) override;
	
	void DrawObj(GfxStateDraw& fb, bool use_texture);
	void StateStartup(GfxDataState& s);
	
	
};
#endif


NAMESPACE_ECS_END

#endif
