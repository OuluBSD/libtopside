#ifndef _Geometry3_Geometry3_h_
#define _Geometry3_Geometry3_h_

#include <AtomComplete/AtomComplete.h>
using namespace TS;



struct Geometry3 : public Component<Geometry3>, public DisplaySink {
	TimeStop ts;
	int phase = 0;
	int phases = 9;
	
	bool launched = false;
	Shape2DWrapper a, b;
	float a_avel, b_avel;
	float vel = 1;
	mat4 view;
	
	
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	Geometry3();
	~Geometry3();
	void operator=(const Geometry3& t) {Panic("Can't copy Geometry3");}
	COMP_DEF_VISIT
	float RandomAngularVel() const {return (0.1 + Randomf() * 0.9) * M_2PI;}
	void ResetShape(Shape2DWrapper& s, ShapeId shape_type, bool is_right);
	
	void DrawLine(DrawGeometry& fb, vec2 a, vec2 b, Color clr);
	void Render(SystemDraw& draw) override;
	
};


#endif
