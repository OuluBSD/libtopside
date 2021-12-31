#ifndef _Geometry_Frustum_h_
#define _Geometry_Frustum_h_

NAMESPACE_TOPSIDE_BEGIN


struct Frustum {
	union {
		struct {
			Plane top;
			Plane bottom;
			Plane left;
			Plane right;
			Plane _near;
			Plane _far;
		};
		Plane planes[6];
	};

	Frustum() {}
	Frustum(const Frustum& m) {
		for(int i = 0; i < 6; i++)
			planes[i] = m.planes[i];
	}
};


NAMESPACE_TOPSIDE_END

#endif
