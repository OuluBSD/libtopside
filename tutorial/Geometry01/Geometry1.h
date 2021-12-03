#ifndef _Geometry1_Geometry1_h_
#define _Geometry1_Geometry1_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;


struct Geometry1 :
	public Component<Geometry1>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Geometry1, ComponentT, BinderIfaceVideo)
	
	TimeStop ts;
	int phase = 0;
	int phases = 6;
	int phase_ms = 1000;
	float prev_phase_f = 0;
	
	Geometry1();
	~Geometry1();
	void Initialize() override;
	void Render(Draw& draw) override;
	void operator=(const Geometry1& t) {Panic("Can't copy Geometry1");}
	
};


#endif
