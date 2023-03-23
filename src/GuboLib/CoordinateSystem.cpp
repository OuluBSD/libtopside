#include "GuboLib.h"

NAMESPACE_GUBO_BEGIN


/*
Function to change the coordinate system:
	- gubo uses 3d extension from regular U++ 2D system
	  (y is negative: up is negative, down is positive)
	  (z is positive: forward is positive)
	- 3D graphics and physics system uses RHS for efficient calculations and clarity
	  (y is positive: up is positive)
	  (z is negative: forward is negative)
	--> invert y and z for simple conversion
*/

vec3 GuPtVec(const Point3f& pt) {
	vec3 v;
	v.data[0] =  pt.x;
	v.data[1] = -pt.y;
	v.data[2] = -pt.z;
	return v;
}

vec3 GuSzVec(const Volf& vol) {
	vec3 v;
	v.data[0] =  vol.cx;
	v.data[1] = -vol.cy;
	v.data[2] = -vol.cz;
	return v;
}


NAMESPACE_GUBO_END
