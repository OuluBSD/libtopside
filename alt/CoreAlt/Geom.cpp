#include "Core.h"

NAMESPACE_UPP_BEGIN


Pointf Intersect(const Pointf& a, const Pointf& b, const Pointf& c, const Pointf& d) {
	double a1 = b.y - a.y;
	double b1 = a.x - b.x;
	double c1 = a1*(a.x) + b1*(a.y);
	
	double a2 = d.y - c.y;
	double b2 = c.x - d.x;
	double c2 = a2*(c.x)+ b2*(c.y);
	
	double determinant = a1*b2 - a2*b1;
	
	if (determinant == 0) {
		return (a + b + c + d) / 4;
	}
	else {
		double x = (b2*c1 - b1*c2)/determinant;
		double y = (a1*c2 - a2*c1)/determinant;
		return Pointf(x, y);
	}
}


NAMESPACE_UPP_END
