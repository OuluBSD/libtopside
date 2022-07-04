#ifndef _Geometry_Frustum_h_
#define _Geometry_Frustum_h_

NAMESPACE_TOPSIDE_BEGIN


struct Frustum {
	Plane top;
	Plane bottom;
	Plane left;
	Plane right;
	Plane _near;
	Plane _far;

	Frustum() {}
	Frustum(const Frustum& m) {
		for(int i = 0; i < 6; i++)
			(*this)[i] = m[i];
	}
	
	Plane& operator[](int i) {
		switch (i) {
			case 0: return top;
			case 1: return bottom;
			case 2: return left;
			case 3: return right;
			case 4: return _near;
			case 5: return _far;
		}
		Panic("invalid [] pos");
		NEVER();
		TODO
	}
	
	const Plane& operator[](int i) const {
		switch (i) {
			case 0: return top;
			case 1: return bottom;
			case 2: return left;
			case 3: return right;
			case 4: return _near;
			case 5: return _far;
		}
		Panic("invalid [] pos");
		NEVER();
		TODO
	}
};


NAMESPACE_TOPSIDE_END

#endif
