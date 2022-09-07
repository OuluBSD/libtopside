#ifndef _Tutorial5_Tutorial5_h_
#define _Tutorial5_Tutorial5_h_

#include <Complete/Complete.h>
using namespace TS;





struct Tutorial5 : public Component<Tutorial5>, public DisplaySink {
	ModelLoader loader;
	int iters_in_phase = 60;
	int iter = 0;
	int phase = 0;
	int phases = 2;
	int width, height;
	
	float *zbuffer = NULL;
	float *zbuffer_empty = NULL;
	
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	Tutorial5();
	~Tutorial5();
	void operator=(const Tutorial5& t) {Panic("Can't copy Tutorial5");}
	void Visit(RuntimeVisitor& vis) override {TODO}
	
	void Render(SystemDraw& draw) override;
	
	vec3 Barycentric(vec3 pts[3], vec2 P);
	void Triangle4(SystemDraw& fb, vec3 pts[3], vec2 tex[3], Texture* tex_img,
		float intensity, bool have_noise);
	void DrawObj(SystemDraw& fb, bool use_texture);
	
};


#endif
