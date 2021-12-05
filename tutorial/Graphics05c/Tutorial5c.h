#ifndef _Tutorial5c_Tutorial5c_h_
#define _Tutorial5c_Tutorial5c_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;



class VertexShader5 : public OglShader {
	
public:
	void Process(OglVertexShaderArgs& args) override;
	
};

class FragmentShader5 : public OglShader {
	
public:
	void Process(OglFragmentShaderArgs& state) override;
	
};

struct Tutorial5c :
	public Component<Tutorial5c>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Tutorial5c, ComponentT, BinderIfaceVideo)
	
	ModelLoader loader;
	FragmentShader5 frag;
	VertexShader5 vtx;
	TimeStop ts;
	double phase_time = 1.5;
	int iter = 0;
	int frame = 0;
	int phase = 0;
	int phases = 2;
	int width, height;
	
	float *zbuffer = NULL;
	float *zbuffer_empty = NULL;
	
	
	Tutorial5c();
	~Tutorial5c();
	void operator=(const Tutorial5c& t) {Panic("Can't copy Tutorial5c");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	void Initialize() override;
	void Render(Draw& draw) override;
	
	/*vec3 Barycentric(vec3 pts[3], vec2 P);
	void Triangle4(Draw& fb, vec3 pts[3], vec2 tex[3], Texture* tex_img,
		float intensity, bool have_noise);*/
	void DrawObj(StateDraw& fb, bool use_texture);
	
};


#endif
