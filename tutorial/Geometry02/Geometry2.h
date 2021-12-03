#ifndef _Geometry2_Geometry2_h_
#define _Geometry2_Geometry2_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;



struct Geometry2 :
	public Component<Geometry2>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Geometry2, ComponentT, BinderIfaceVideo)
	
	TimeStop ts;
	int phase = 0;
	int phases = 8;
	int phase_ms = 1000;
	float prev_phase_f = 0;
	
	Geometry2();
	~Geometry2();
	void Initialize() override;
	void operator=(const Geometry2& t) {Panic("Can't copy Geometry2");}
	void DrawLine(DrawGeometry& fb, float scale, vec4 a, vec4 b, Color clr);
	void Render(Draw& draw) override;
	
};


#endif
