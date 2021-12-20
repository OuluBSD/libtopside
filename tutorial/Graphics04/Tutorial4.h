#ifndef _Tutorial4_Tutorial4_h_
#define _Tutorial4_Tutorial4_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;



struct Tutorial4 :
	public Component<Tutorial4>,
	public BinderIfaceVideo

{
	RTTI_DECL2(Tutorial4, ComponentT, BinderIfaceVideo)
	
	ModelLoader loader;
	SdlCpuDataState state;
	Color yellow {255, 255, 0};
	Color white {255, 255, 255};
	Color red {255, 0, 0};
	Color green {0, 255, 0};
	int width, height;
	int iters_in_phase = 3*60;
	int iter = 0;
	int phase = 0;
	int phases = 8;
	
	float *zbuffer = NULL;
	float *zbuffer_empty = NULL;
	
	Vector<line3> lines, trans_lines;
	line3 unit_y, unit_x;
	
	
	Tutorial4();
	~Tutorial4();
	void operator=(const Tutorial4& t) {Panic("Can't copy Tutorial4");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	
	void Begin();
	void DrawLine(Draw& fb, const line3& l, Color clr);
	void Draw0(Draw& fb);
	void MultiplyBy(mat2 v);
	void MultiplyBy(mat3 v);
	void Add(vec2 v);
	void Project();
	void Initialize() override;
	void Render(Draw& draw) override;
	
	
	vec3 Barycentric(vec3 pts[3], vec2 P);
	void Triangle4(Draw& fb, vec3 pts[3], vec2 tex[3], Texture* tex_img,
		float intensity, bool have_noise);
	void DrawObj(float f2, Draw& fb, bool use_texture);
	
};


#endif
