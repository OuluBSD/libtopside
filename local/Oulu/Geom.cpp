#include "Oulu.h"


NAMESPACE_OULU_BEGIN


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


NAMESPACE_OULU_END
