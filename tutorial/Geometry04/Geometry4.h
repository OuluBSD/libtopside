#ifndef _Geometry4_Geometry4_h_
#define _Geometry4_Geometry4_h_

#include <Complete/Complete.h>
using namespace TS;



struct Tutorial4Dummy : public Component<Tutorial4Dummy> {
	float angle = 0;
	
	
};

struct Geometry4 : public Component<Geometry4>, public DisplaySink {
	TimeStop ts;
	int phase = 0;
	int phases = 9;
	
	bool launched = false;
	Shape2DWrapper a, b;
	float a_avel, b_avel;
	float vel = 1;
	mat4 view;
	
	QuadtreeComponent* quad = NULL;
	
	
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	Geometry4();
	~Geometry4();
	void operator=(const Geometry4& t) {Panic("Can't copy Geometry4");}
	COMP_DEF_VISIT
	float RandomAngularVel() const {return (0.1 + Randomf() * 0.9) * M_2PI;}
	void ResetShape(Shape2DWrapper& s, ShapeId shape_type, bool is_right);
	
	void Initialize() override;
	
	void DrawLine(DrawGeometry& fb, vec2 a, vec2 b, Color clr);
	void Render(SystemDraw& draw) override;
	
};


#endif
