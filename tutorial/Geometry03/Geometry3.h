#ifndef _Geometry3_Geometry3_h_
#define _Geometry3_Geometry3_h_

#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;



struct Geometry3 :
	public Component<Geometry3>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Geometry3, ComponentT, BinderIfaceVideo)
	
	TimeStop ts;
	int phase = 0;
	int phases = 9;
	
	bool launched = false;
	Shape2DWrapper a, b;
	float a_avel, b_avel;
	float vel = 1;
	mat4 view;
	
	
	Geometry3();
	~Geometry3();
	void Initialize() override;
	void Render(Draw& draw) override;
	void operator=(const Geometry3& t) {Panic("Can't copy Geometry3");}
	float RandomAngularVel() const {return (0.1 + Randomf() * 0.9) * M_2PI;}
	void ResetShape(Shape2DWrapper& s, ShapeId shape_type, bool is_right);
	void DrawLine(DrawGeometry& fb, vec2 a, vec2 b, Color clr);
	
};


#endif
