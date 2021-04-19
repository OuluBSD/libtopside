#ifndef _Geometry2_Geometry2_h_
#define _Geometry2_Geometry2_h_

#include <Complete/Complete.h>
using namespace Oulu;



struct Geometry2 : public Component<Geometry2>, public DisplaySink {
	TimeStop ts;
	int phase = 0;
	int phases = 8;
	int phase_ms = 1000;
	float prev_phase_f = 0;
	
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	Geometry2();
	~Geometry2();
	void operator=(const Geometry2& t) {Panic("Can't copy Geometry2");}
	
	void DrawLine(GeometryDraw& fb, float scale, vec4 a, vec4 b, Color clr);
	void Render(SystemDraw& draw) override;
	
};


#endif
