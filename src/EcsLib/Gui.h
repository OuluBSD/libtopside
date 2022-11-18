#ifndef _EcsLib_Gui_h_
#define _EcsLib_Gui_h_

NAMESPACE_ECS_BEGIN


#ifdef flagGUI
struct DefaultGuiAppComponent :
	public Component<DefaultGuiAppComponent>,
	public BinderIfaceVideo,
	public BinderIfaceEvents
{
	RTTI_DECL2(DefaultGuiAppComponent, ComponentT, BinderIfaceVideo)
	
	Point prev_mouse;
	
	WindowSystemRef wins;
	CoreWindowRef cw;
	TransformRef trans;
	Transform2DRef trans2;
	
	DefaultGuiAppComponent();
	void operator=(const DefaultGuiAppComponent& t) {Panic("Can't copy DefaultGuiAppComponent");}
	void Visit(RuntimeVisitor& vis) override;
	void Initialize() override;
	void Uninitialize() override;
	void Update(double dt) override;
	bool Render(Draw& d) override;
	bool RenderProg(DrawCommand*& begin, DrawCommand*& end) override;
	void Dispatch(const CtrlEvent& state) override;
	bool Arg(const String& key, const String& value) override;
	
	void DrawObj(GfxStateDraw& fb, bool use_texture);
	void StateStartup(GfxDataState& s);
	
	
};
#endif


NAMESPACE_ECS_END

#endif
