#ifndef _IGraphics_GuiProg_h_
#define _IGraphics_GuiProg_h_


NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct GuiProgT :
	public BinderIfaceVideo
{
	RTTI_DECL1(GuiProgT, BinderIfaceVideo)
	
	ModelLoader loader;
	String obj;
	TimeStop ts;
	double phase_time = 3.0;
	int iter = 0;
	int frame = 0;
	int phase = 0;
	int phases = 2;
	bool use_pbr = false;
	Size sz;
	
	bool have_skybox = false;
	String skybox_diffuse, skybox_irradiance;
	
	GuiProgT();
	void operator=(const GuiProgT& t) {Panic("Can't copy GuiProgT");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	void Initialize() override;
	void Uninitialize() override;
	bool Render(Draw& draw) override;
	bool Arg(const String& key, const String& value) override;
	
	void DrawObj(StateDrawT<Gfx>& fb, bool use_texture);
	
};


NAMESPACE_PARALLEL_END


#endif
