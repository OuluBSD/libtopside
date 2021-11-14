#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


bool have_collinear_points(Vector<Point>& points, int count) {
	int i = (count - 1);
	double dx1 = 0.0, dy1 = 0.0, dx2 = 0.0, dy2 = 0.0;
	
	// check that the i-th selected point does not belong
	// to a line connecting some previously selected points
	for (int j = 0; j < i; ++j) {
		dx1 = points[j].x - points[i].x;
		dy1 = points[j].y - points[i].y;
		for (int k = 0; k < j; ++k) {
			dx2 = points[k].x - points[i].x;
			dy2 = points[k].y - points[i].y;
			if (abs(dx2*dy1 - dy2*dx1) <= EPSILON*(abs(dx1) + abs(dy1) + abs(dx2) + abs(dy2)))
				return true;
		}
	}
	return false;
}


NAMESPACE_TOPSIDE_END
