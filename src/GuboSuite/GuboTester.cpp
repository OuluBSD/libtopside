#include "GuboSuite.h"

NAMESPACE_GUBO_BEGIN



Ground::Ground() {
	SetSize(3);
}

Ground& Ground::SetSize(float len) {
	float h = 0.1;
	Cubf c = CubfC(-len, 0, -len, 2*len, h, 2*len);
	SetFrameBox(c);
	return *this;
}

void Ground::Paint(Draw3& d) {
	Cubf c = GetFrameBox().GetSize();
	d.DrawBox(c, Green());
}





Box::Box() {
	SetFrameBox(CubfC(-1,-1,-1,2,2,2));
}

Box& Box::Move(const Point3f& pt) {
	Cubf c = GetFrameBox();
	Volf sz = c.GetSize();
	c = CubfC(pt, sz);
	SetFrameBox(c);
	return *this;
}

void Box::Paint(Draw3& d) {
	Cubf c = GetFrameBox().GetSize();
	d.DrawBox(c, Brown());
}





GuboTester::GuboTester() {
	Add(gnd);
	
	for(int i = 0; i < 3; i++) {
		Box& b = boxes.Add();
		Point3f pt(
			-2 + Randomf() * 4,
			1,
			-2 + Randomf() * 4);
		b.Move(pt);
		Add(b);
	}
}

GuboTester::~GuboTester() {
	
}



NAMESPACE_GUBO_END
