#ifndef _EcsLib_RenderingSystem_h_
#define _EcsLib_RenderingSystem_h_

NAMESPACE_TOPSIDE_BEGIN

#if 0

class RenderingSystem : public System<DisplaySystem> {
	Ref<EntityStore> ents;
	LinkedList<DisplaySourceRef> srcs;
	LinkedList<DisplaySinkRef> sinks;
	LinkedList<DisplayExchangePointRef> expts;
	
	bool invalid;
	Size vscreen_sz;
	
	
	void Visit(RuntimeVisitor& vis) override {
		vis & ents
			&& srcs;
	}
public:
	RenderingSystem(Machine& m);
	
	void Add(DisplaySourceRef r);
	void Add(DisplaySinkRef r);
	void Add(DisplayExchangePointRef r);
	void Remove(DisplaySourceRef r);
	void Remove(DisplaySinkRef r);
	void Remove(DisplayExchangePointRef r);
	
	void RunTest();
	
	Size GetVirtualScreenSize() const {ASSERT(vscreen_sz.cx > 0 && vscreen_sz.cy > 0); return vscreen_sz;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
};

#endif


#ifdef flagGUI

class DefaultRenderApp :
	public Component<DefaultRenderApp>,
	public DisplaySource,
	public HumanSource
{
	One<Shader> simple_shader;
	EntityStoreRef ents;
	
	VectorRendModel rends;
	
public:
	VIS_COMP_2_0(Display, Human)
	COPY_PANIC(DefaultRenderApp);
	IFACE_CB(DisplaySource);
	IFACE_CB(HumanSource);
	IFACE_GENERIC;
	
	DefaultRenderApp();
	
	// Component
	void					Initialize() override;
	void					Uninitialize() override;
	void					Visit(RuntimeVisitor& vis) override {TODO vis & ents;}
	
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
