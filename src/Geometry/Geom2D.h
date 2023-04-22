#ifndef _Math_Geom2D_h_
#define _Math_Geom2D_h_


NAMESPACE_TOPSIDE_BEGIN



struct Circle {
	typedef float F;
	
	union {
		vec2 ct;
		vec2 position;
	};
	union {
		float rad;
		float radius;
	};
	
	Circle() : ct(0,0), radius(1.0f) {}
	Circle(vec2 ct, float rad) : ct(ct), rad(rad) {}
	Circle(float x, float y, float rad) : rad(rad) {ct[0] = x; ct[1] = y;}
	Circle(Circle&& c) {*this = c;}
	Circle(const Circle& c) {*this = c;}
	
	void operator=(const Circle& c) {ct = c.ct; rad = c.rad;}
	
	void SetContainerFromPoints(const Vector<vec2>& pts);
	
	void Clear() {ct.Clear(); rad = 1.0f;}
	
	bool Contains(const vec2& pt) const;
	bool Intersects(const line2& l) const;
	bool Intersects(const Circle& c) const;
	
};


// Note: TS::TS::Rectangle differs from TS::Rect:
//	- it's origin + size, not min + max
//  - it's positive y value upwards, not downwards (as is easier in 2d gui)

struct FixedRectangle {
	typedef float F;
	typedef Vec<F, 2> vec2;
	
	union {
		vec2 origin;
		vec2 pos;
	};
	union {
		vec2 size;
		vec2 sz;
	};
	
	FixedRectangle() {}
	FixedRectangle(const FixedRectangle& r) { *this = r; }
	FixedRectangle(const vec2& sz) : sz(sz) {pos.Clear(); }
	FixedRectangle(const vec2& pos, const vec2& sz) : pos(pos), sz(sz) {}

	void operator=(const FixedRectangle& src) {
		pos = src.pos;
		sz = src.sz;
	}
	
	void SetContainerFromPoints(const Vector<vec2>& pts);
	
	F Width() const { return sz[0]; }
	F Height() const { return sz[1]; }
	vec2 GetSize() const { return sz; }
	vec2 GetCenter() const { return pos + sz.Multiply(0.5); }
	vec2 GetMin() const {vec2 p = pos + sz; return vec2 {std::min(pos[0], p[0]), std::min(pos[1], p[1])};}
	vec2 GetMax() const {vec2 p = pos + sz; return vec2 {std::max(pos[0], p[0]), std::max(pos[1], p[1])};}
	bool Contains(const vec2& pt) const;
	bool Intersects(const line2& l) const;
	bool Intersects(const Circle& c) const;
	bool Intersects(const FixedRectangle& r) const;
	bool IntersectsSAT(const FixedRectangle& r) const;
	ival1 GetInterval(const vec2& axis) const;
	bool OverlapsOnAxis(const FixedRectangle& r, const vec2& axis) const;
	
	FixedRectangle& SetFromMinMax(vec2 min, vec2 max) {pos = min; sz = max - min; return *this;}

};




// OrientedRectangle differs from Rectangle by:
//  - having center point and half-extents instead of origin and size
struct OrientedRectangle {
	typedef float F;
	typedef Vec<F, 2> vec2;
	
	union {
		vec2 position;
		vec2 ct;
	};
	union {
		vec2 halfExtents;
		vec2 hext;
	};
	union {
		float rot;
		float rotation;
	};
	
	OrientedRectangle() {}
	OrientedRectangle(const FixedRectangle& r) { *this = r; }
	OrientedRectangle(const OrientedRectangle& r) { *this = r; }
	OrientedRectangle(const vec2& ct, const vec2& hext, float rot) : ct(ct), hext(hext), rot(rot) {}

	void operator=(const OrientedRectangle& src) {memcpy(this, &src, sizeof(OrientedRectangle));}
	void operator=(const FixedRectangle& src) {
		ct = src.GetCenter();
		hext = src.GetSize() * 0.5;
		rot = 0;
	}
	
	
	bool Contains(const vec2& pt) const;
	bool Intersects(const line2& l) const;
	bool Intersects(const Circle& c) const;
	bool Intersects(const FixedRectangle& r) const;
	bool Intersects(const OrientedRectangle& r) const;
	ival1 GetInterval(const vec2& axis) const;
	bool OverlapsOnAxis(const FixedRectangle& r, const vec2& axis) const;

	
};




typedef enum {
	SHAPE2_LINE,
	SHAPE2_CIRCLE,
	SHAPE2_RECT,
	SHAPE2_ORIENTRECT,
} ShapeId;

inline ShapeId GetRandomShape2() {return (ShapeId)Random(4);}



struct Shape2DWrapper : Moveable<Shape2DWrapper> {
	
	struct ShapeBase :
		RTTIBase
	{
		RTTI_DECL0(ShapeBase)
		virtual ~ShapeBase() {}
		virtual bool Intersects(const line2&) = 0;
		virtual bool Intersects(const Circle&) = 0;
		virtual bool Intersects(const FixedRectangle&) = 0;
		virtual bool Intersects(const OrientedRectangle&) = 0;
		virtual vec2 GetPos() = 0;
		virtual void Move(const vec2& v) = 0;
		virtual void Rotate(float rad) = 0;
		virtual void GetFaces(Vector<line2>& faces) = 0;
		virtual void GetFaces(Vector<tri3>& faces) = 0;
		
		bool Intersects(const ShapeBase& b);
	};
	
	struct ShapeLine : public ShapeBase {
		RTTI_DECL1(ShapeLine, ShapeBase)
		line2 l;
		ShapeLine(line2 l) : l(l) {}
		bool Intersects(const line2& l) override {THROW(Exc("Not implemented"));}
		bool Intersects(const Circle& c) override {return c.Intersects(l);}
		bool Intersects(const FixedRectangle& r) override {return r.Intersects(l);}
		bool Intersects(const OrientedRectangle& o) override {return o.Intersects(l);}
		vec2 GetPos() override {return (l.a + l.b) * 0.5;}
		void Move(const vec2& v) override {l.a += v; l.b += v;}
		void Rotate(float rad) override;
		void GetFaces(Vector<line2>& faces) override {faces.Add(l);}
		void GetFaces(Vector<tri3>& faces) override;
	};
	
	struct ShapeCircle : public ShapeBase {
		RTTI_DECL1(ShapeCircle, ShapeBase)
		Circle c;
		ShapeCircle(Circle c) : c(c) {}
		bool Intersects(const line2& l) override {return c.Intersects(l);}
		bool Intersects(const Circle& c) override {return this->c.Intersects(c);}
		bool Intersects(const FixedRectangle& r) override {return r.Intersects(c);}
		bool Intersects(const OrientedRectangle& o) override {return o.Intersects(c);}
		vec2 GetPos() override {return c.ct;}
		void Move(const vec2& v) override {c.ct += v;}
		void Rotate(float rad) override {}
		void GetFaces(Vector<line2>& faces) override;
		void GetFaces(Vector<tri3>& faces) override;
	};
	
	struct ShapeRect : public ShapeBase {
		RTTI_DECL1(ShapeRect, ShapeBase)
		FixedRectangle& r;
		ShapeRect(FixedRectangle r) : r(r) {}
		bool Intersects(const line2& l) override {return r.Intersects(l);}
		bool Intersects(const Circle& c) override {return r.Intersects(c);}
		bool Intersects(const FixedRectangle& r) override {return this->r.Intersects(r);}
		bool Intersects(const OrientedRectangle& o) override {return o.Intersects(r);}
		vec2 GetPos() override {return r.GetCenter();}
		void Move(const vec2& v) override {r.pos += v;}
		void Rotate(float rad) override {}
		void GetFaces(Vector<line2>& faces) override;
		void GetFaces(Vector<tri3>& faces) override;
	};
	
	struct ShapeOrientedRect : public ShapeBase {
		RTTI_DECL1(ShapeOrientedRect, ShapeBase)
		OrientedRectangle o;
		ShapeOrientedRect(OrientedRectangle o) : o(o) {}
		bool Intersects(const line2& l) override {return o.Intersects(l);}
		bool Intersects(const Circle& c) override {return o.Intersects(c);}
		bool Intersects(const FixedRectangle& r) override {return o.Intersects(r);}
		bool Intersects(const OrientedRectangle& o) override {return this->o.Intersects(o);}
		vec2 GetPos() override {return o.ct;}
		void Move(const vec2& v) override {o.ct += v;}
		void Rotate(float rad) override {o.rot = fmodf(o.rot + rad, (float)M_2PI); }
		void GetFaces(Vector<line2>& faces) override;
		void GetFaces(Vector<tri3>& faces) override;
	};
	
	
	One<ShapeBase> shape;
	
	
	void Create(ShapeId type, vec2 a, vec2 b, float f);
	void Create(ShapeId type, const vec2& ax_vec);
};




struct BoundingShape {
	Vector<line2> lines;
	Vector<Circle> circles;
	Vector<FixedRectangle> rects;
	Vector<OrientedRectangle> orects;
	
	
	bool Intersects(const line2& l) const;
	bool Intersects(const Circle& c) const;
	bool Intersects(const FixedRectangle& r) const;
	bool Intersects(const OrientedRectangle& r) const;
	
};


struct Frustum2Rect {
	
	
};






class Triangulate {

public:

	static bool Process(const Vector<vec2>& contour, Vector<float>& result);

	static double Area(const Vector<vec2>& contour);

	static bool InsideTriangle(double Ax, double Ay,
		double Bx, double By,
		double Cx, double Cy,
		double Px, double Py);


private:
	static bool Snip(const Vector<vec2>& contour, int u, int v, int w, int n, int* V);

};


NAMESPACE_TOPSIDE_END

#endif
