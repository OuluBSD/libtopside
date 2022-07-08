#ifndef _Math_GeomCommon_h_
#define _Math_GeomCommon_h_


NAMESPACE_TOPSIDE_BEGIN


struct Interval {
	float min;
	float max;
};

template <int I>
struct IntervalT {
	using Value = Vec<float, I>;
	
	Value min, max;
	
	
};

typedef Interval     ival1;
typedef IntervalT<2> ival2;
typedef IntervalT<3> ival3;




template <class T, int I, class F=float>
struct Line : Moveable<Line<T,I,F>> {
	typedef Vec<T,I> vec;
	
	union {
		vec start;
		vec a;
	};
	union {
		vec end;
		vec b;
	};
	
	
	Line() {}
	Line(const vec& a, const vec& b) : a(a), b(b) {}
	Line(const Line& l) : a(l.a), b(l.b) {}
	
	Line& Set(const vec& a, const vec& b) {this->a = a; this->b = b; return *this;}
	
	F GetLength() const {return (b - a).GetLength();}
	F GetLengthSquared() const {return (b - a).GetLengthSquared();}
	vec GetVector() const {return b - a;}
	vec GetCenter() const {return (a + b) * 0.5;}
	
	bool Contains(const vec& pt, F accepted_error = 0.0001) const {
		vec d = b - a;
		if (d[0] == 0 || d[1] == 0) return false;
		F a = d[1] / d[0]; // calculate slope: a = y / x
		F b = a[1] - a * a[0]; // calculate y-intercept: b = y - a * x
		F cmp_y = a * pt[0] + b; // expected y: y = a * x + b
		F cmp_d = pt[1] - cmp_y; // difference between expected and actual y
		return cmp_d >= -accepted_error && cmp_d <= +accepted_error;
	}
	
	bool Intersects(const Line& l) const {
		vec b = this->b - this->a;
		vec d = l.b - l.a;
		float dot_dperp = b[0] * d[1] - b[1] * d[0];
		
		// if b dot d == 0, it means the lines are parallel so have infinite
		// intersection points
		if (dot_dperp == 0)
			return false;
		
		vec c = l.a - a;
		float t = (c[0] * d[1] - c[1] * d[0]) / dot_dperp;
		if (t < 0 || t > 1)
			return false;
		
		float u = (c[0] * b[1] - c[1] * b[0]) / dot_dperp;
		if (u < 0 || u > 1)
			return false;
		
		return t >= 0.0f && t <= 1.0f;
	}

};

typedef Line<float, 2> line2;
typedef Line<float, 3> line3;
typedef Line<int, 2> iline2;
typedef Line<int, 3> iline3;






template <class T, int I>
struct Triangle : Moveable<Triangle<T,I> > {
	typedef T Unit;
	typedef Vec<T,I> vec;
	
	union {
		struct {
			vec a;
			vec b;
			vec c;
		};
		struct {
			vec p1;
			vec p2;
			vec p3;
		};

		vec points[3];
		float values[vec::size * 3];
	};
	

	Triangle() {}
	Triangle(const vec& a, const vec& b, const vec& c) {Set(a,b,c);}
	Triangle(const Triangle& t) { *this = t; }
	void operator=(const Triangle& t) {memcpy(this, &t, sizeof(Triangle));}
	void Set(const vec& a, const vec& b, const vec& c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

typedef Triangle<int, 2> itri2;
typedef Triangle<int, 3> itri3;
typedef Triangle<float, 2> tri2;
typedef Triangle<float, 3> tri3;







template <class S0, class S1, class V>
bool IntersectsSAT(const S0& s0, const S1& s1) {
	
	// Test the face normals of objects as the separating axis
	const Vector<V>& normals0 = s0.GetFaceNormals();
	for(const V& norm: normals0)
		if (s0.OverlapsOnAxis(s1, norm))
			return true;
	
	const Vector<V>& normals1 = s0.GetFaceNormals();
	for(const V& norm: normals1)
		if (s1.OverlapsOnAxis(s0, norm))
			return true;
	
	// Check the normalized cross product of each shapes edges.
	const Vector<V>& edges0 = s0.GetEdges();
	const Vector<V>& edges1 = s1.GetEdges();
	for(const V& e0 : edges0) {
		for(const V& e1 : edges1) {
			V test_axis = e0.GetCrossProduct(e1);
			if (!s0.OverlapsOnAxis(s1, test_axis))
				return true;
		}
	}
	
	// No separating axis found, the objects do not intersect
	return false;
};


NAMESPACE_TOPSIDE_END


#endif
