#ifndef _Geometry1_Geometry1_h_
#define _Geometry1_Geometry1_h_

#include <Complete/Complete.h>
using namespace Oulu;






struct Geometry1 : public Component<Geometry1>, public DisplaySink {
	TimeStop ts;
	int phase = 0;
	int phases = 6;
	int phase_ms = 1000;
	float prev_phase_f = 0;
	
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	Geometry1();
	~Geometry1();
	void operator=(const Geometry1& t) {Panic("Can't copy Geometry1");}
	void Render(SystemDraw& draw) override;
	
};


#endif
