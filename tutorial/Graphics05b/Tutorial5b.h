#ifndef _Tutorial5b_Tutorial5b_h_
#define _Tutorial5b_Tutorial5b_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;



class VertexShader5 : public SoftShaderBase {
	
public:
	void Process(SdlCpuVertexShaderArgs& args) override;
	
};

class FragmentShader5 : public SoftShaderBase {
	
public:
	void Process(SdlCpuFragmentShaderArgs& args) override;
	
};

struct Tutorial5b :
	public Component<Tutorial5b>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Tutorial5b, ComponentT, BinderIfaceVideo)
	
	ModelLoader loader;
	TimeStop ts;
	double phase_time = 1.5;
	int iter = 0;
	int frame = 0;
	int phase = 0;
	int phases = 2;
	int width, height;
	
	
	Tutorial5b();
	void operator=(const Tutorial5b& t) {Panic("Can't copy Tutorial5b");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	void Initialize() override;
	void Render(Draw& draw) override;
	
	void DrawObj(SdlCpuStateDraw& fb, bool use_texture);
	
};


#endif
