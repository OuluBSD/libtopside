#ifndef _Geometry4_Geometry4_h_
#define _Geometry4_Geometry4_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;



struct Tutorial4Dummy : public Component<Tutorial4Dummy> {
	float angle = 0;
	
	
};

struct Geometry4 :
	public Component<Geometry4>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Geometry4, ComponentT, BinderIfaceVideo)
	
	TimeStop ts;
	int phase = 0;
	int phases = 9;
	
	bool launched = false;
	Shape2DWrapper a, b;
	float a_avel, b_avel;
	float vel = 1;
	mat4 view;
	
	QuadtreeComponent* quad = NULL;
	
	
	Geometry4();
	~Geometry4();
	void Initialize() override;
	void Render(Draw& draw) override;
	void operator=(const Geometry4& t) {Panic("Can't copy Geometry4");}
	COMP_DEF_VISIT
	float RandomAngularVel() const {return (0.1 + Randomf() * 0.9) * M_2PI;}
	void ResetShape(Shape2DWrapper& s, ShapeId shape_type, bool is_right);
	
	
	void DrawLine(DrawGeometry& fb, vec2 a, vec2 b, Color clr);
	
};


#endif
