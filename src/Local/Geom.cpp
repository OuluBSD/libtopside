#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


bool IsColliding(Pointf a, Pointf b, Pointf c, Pointf d) {
	double denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
    double numerator1  = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
    double numerator2  = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

    // Detect coincident lines (has a problem, read below)
    if (denominator == 0)
		return numerator1 == 0 && numerator2 == 0;
    
    double r = numerator1 / denominator;
    double s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}


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

NAMESPACE_TOPSIDE_END
