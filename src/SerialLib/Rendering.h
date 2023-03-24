#ifndef _SerialLib_Rendering_h_
#define _SerialLib_Rendering_h_

NAMESPACE_PARALLEL_BEGIN



struct RendererBase :
	public BinderIfaceVideo
{
	RTTI_DECL1(RendererBase, BinderIfaceVideo)
	
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
	
	RendererBase();
	void operator=(const RendererBase& t) {Panic("Can't copy RendererBase");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	void Initialize() override;
	void Uninitialize() override;
	bool Render(Draw& draw) override;
	bool Arg(const String& key, const String& value) override;
	
	void DrawObj(GfxStateDraw& fb, bool use_texture);
	
};


NAMESPACE_PARALLEL_END

#endif
