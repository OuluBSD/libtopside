#ifndef _SoftPhysTests_Ecs_h_
#define _SoftPhysTests_Ecs_h_


NAMESPACE_ECS_BEGIN


class LocalVertexShader : public SoftShaderBase {
	
public:
	void Process(SdlCpuVertexShaderArgs& args) override;
	
};

class LocalFragmentShader : public SoftShaderBase {
	
public:
	void Process(SdlCpuFragmentShaderArgs& args) override;
	
};

struct LocalApp :
	public Component<LocalApp>,
	public BinderIfaceVideo
{
	RTTI_DECL2(LocalApp, ComponentT, BinderIfaceVideo)
	
	One<TestBase> test;
	TimeStop ts;
	double phase_time = 1.5;
	int iter = 0;
	int frame = 0;
	int phase = 0;
	int phases = 2;
	int width, height;
	
	
	LocalApp();
	void operator=(const LocalApp& t) {Panic("Can't copy LocalApp");}
	void Visit(RuntimeVisitor& vis) override {/*if (test) vis % *test;*/}
	void Initialize() override;
	void Uninitialize() override;
	void Update(double dt) override;
	void Render(Draw& draw) override;
	
	void DrawObj(SdlCpuStateDraw& fb, bool use_texture);
	void StateStartup(GfxDataState& s);
	
	
};


NAMESPACE_ECS_END

#endif
