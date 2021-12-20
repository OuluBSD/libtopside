#ifndef _Tutorial5_Tutorial5_h_
#define _Tutorial5_Tutorial5_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;



struct Tutorial5 :
	public Component<Tutorial5>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Tutorial5, ComponentT, BinderIfaceVideo)
	
	ModelLoader loader;
	SdlCpuDataState state;
	TimeStop ts;
	double phase_time = 1.5;
	int iter = 0;
	int phase = 0;
	int phases = 2;
	int width, height;
	
	float *zbuffer = NULL;
	float *zbuffer_empty = NULL;
	
	
	Tutorial5();
	~Tutorial5();
	void operator=(const Tutorial5& t) {Panic("Can't copy Tutorial5");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	void Initialize() override;
	void Render(Draw& draw) override;
	
	vec3 Barycentric(vec3 pts[3], vec2 P);
	void Triangle4(Draw& fb, vec3 pts[3], vec2 tex[3], Texture* tex_img,
		float intensity, bool have_noise);
	void DrawObj(Draw& fb, bool use_texture);
	
};


#endif
