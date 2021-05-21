#ifndef _EcsLib_DisplaySystem_h_
#define _EcsLib_DisplaySystem_h_

NAMESPACE_TOPSIDE_BEGIN

#ifdef flagGUI

class DefaultRenderApp :
	public Component<DefaultRenderApp>,
	public DisplaySource,
	public HumanSource
{
	struct DefDisplay : public SimpleDisplay {
		DefaultRenderApp& app;
		DefDisplay(DefaultRenderApp* app) : app(*app) {}
		void StorePacket(DisplayPacket& p) override;
	};
	
	struct DefDisplayStream : public SimpleDisplayStream {
		DefaultRenderApp& app;
		DefDisplayStream(DefaultRenderApp* app) : app(*app) {Set(app->dis);}
		bool Render(SystemDraw& draw);
	};
	
	One<Shader>			simple_shader;
	EntityStoreRef		ents;
	VectorRendModel		rends;
	DefDisplayStream	dis_str;
	DefDisplay			dis;
	
	bool Render(SystemDraw& draw);
	
public:
	RTTI_COMP2(DefaultRenderApp, DisplaySource, HumanSource)
	VIS_COMP_2_0(Display, Human)
	COPY_PANIC(DefaultRenderApp);
	IFACE_CB(DisplaySource);
	IFACE_CB(HumanSource);
	IFACE_GENERIC;
	
	DefaultRenderApp();
	
	// Component
	void					Initialize() override;
	void					Uninitialize() override;
	void					Visit(RuntimeVisitor& vis) override;
	
	// DisplaySource
	DisplayStream&			GetStream(DisCtx) override;
	void					BeginStream(DisCtx) override;
	void					EndStream(DisCtx) override;
	
	// HumanSource
	HumanStream&			GetStream(HumCtx) override;
	void					BeginStream(HumCtx) override;
	void					EndStream(HumCtx) override;
	
};

#endif

NAMESPACE_TOPSIDE_END

#endif
