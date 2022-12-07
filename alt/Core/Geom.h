#ifndef _CoreAlt_Geom_h_
#define _CoreAlt_Geom_h_

NAMESPACE_UPP_BEGIN



template <class T>
struct Point_ : Moveable<Point_<T>> {
	T x = 0, y = 0;

	Point_() {}

	Point_(T x, T y) : x(x), y(y) {}

	Point_(const Point_& pt) : x(pt.x), y(pt.y) {}



	static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	static const char* GetTypeName() {return "Point_<T>";}
	
	bool IsEqual(const Point_& p) const {return x == p.x && y == p.y;}
	bool operator!=(const Point_& p) const {return !IsEqual(p);}
	bool operator==(const Point_& p) const {return IsEqual(p);}
	
	double Length() { return sqrt(x * x + y * y); }
	double Slope() { return y / x; }

	Point_ operator-() const { return Point_(-x, -y); }
	Point_ operator*(double k) const { return Point_(x * k, y * k); }
	Point_ operator/(double k) const { return Point_(x / k, y / k); }

	Point_ operator+(const Point_& b) const { return Point_(x + b.x, y + b.y); }
	Point_ operator-(const Point_& b) const { return Point_(x - b.x, y - b.y); }
	Point_ operator*(const Point_& b) const { return Point_(x * b.x, y * b.y); }
	Point_ operator/(const Point_& b) const { return Point_(x / b.x, y / b.y); }


	template <class V>
	Point_& operator=(const V& b) {
		x = (T)b.x;
		y = (T)b.y;
		return *this;
	}

	Point_& operator+=(const Point_& b) {
		x = (T)(x + b.x);
		y = (T)(y + b.y);
		return *this;
	}

	Point_& operator-=(const Point_& b) {
		x = (T)(x - b.x);
		y = (T)(y - b.y);
		return *this;
	}

	Point_& operator*=(const double k) {
		x = (T)(x * k);
		y = (T)(y * k);
		return *this;
	}

	Point_& operator/=(const double k) {
		x = (T)(x / k);
		y = (T)(y / k);
		return *this;
	}

	static void Dot(const Point_& a, const Point_& b, Point_& o) {
		//dot product: o = a dot b
		o.x = a.x * b.x;
		o.y = a.y * b.y;
	}

	Point_ DotProd(const Point_& b) const {
		//return dot product
		return Point(x * b.x, y * b.y);
	}
	
	String	ToString() const {return "Point(" + IntStr(x) + ", " + IntStr(y) + ")";}
	int		ToInt() const {return x * y;}
	double	ToDouble() const {return x * y;}
	hash_t	GetHashValue() const {return x * y;}
	
	operator Point_<int>() const {return Point_<int>(x,y);}
	operator Point_<double>() const {return Point_<double>(x,y);}
	
	bool	IsNull() const {return IsNull(x) || IsNull(y);}
	void	SetNull() const {SetNull(x); SetNull(y);}
	
};


typedef Point_<int> Point;
typedef Point_<float> PointF32;
typedef Point_<double> Pointf;



template <class T>
double GetSignedArea(const T& a, const T& b, const T& c) {
	double area = 0;
	area += (a.x * b.y - b.x * a.y);
	area += (b.x * c.y - c.x * b.y);
	area += (c.x * a.y - a.x * c.y);
	return area * 0.5;
}


template <class T>
struct Size_ : Moveable<Size_<T>> {
	T cx = 0, cy = 0;

	Size_() {}
	Size_(const Size_& sz) { *this = sz; }
	Size_(T cx, T cy) : cx(cx), cy(cy) {}
	
	static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	static const char* GetTypeName() {return "Size_<T>";}
	
	void Clear() {cx = 0; cy = 0;}
	bool IsEmpty() const {return cx == 0 && cy == 0;}
	bool IsPositive() const {return cx > 0 && cy > 0;}
	bool IsEqual(const Size_& sz) const {return cx == sz.cx && cy == sz.cy;}
	
	T		GetArea() const {return cx * cy;}
	int		ToInt() const {return cx * cy;}
	double	ToDouble() const {return cx * cy;}
	hash_t	GetHashValue() const {return cx * cy;}
	
	T&       operator[](int i)       {ASSERT(i == 0 || i == 1); if (i == 0) return &cx; if (i == 1) return &cy; Panic("invalid Size_<T> subscript pos"); NEVER();}
	const T& operator[](int i) const {ASSERT(i == 0 || i == 1); if (i == 0) return &cx; if (i == 1) return &cy; Panic("invalid Size_<T> subscript pos"); NEVER();}
	
	bool operator==(const Size_& sz) const {return IsEqual(sz);}
	bool operator!=(const Size_& sz) const {return !IsEqual(sz);}
	void operator=(const Size_& sz) {
		cx = sz.cx;
		cy = sz.cy;
	}

	Size_& operator+=(Size_ p)  { cx +=  p.cx; cy +=  p.cy; return *this; }
	Size_& operator+=(double t) { cx +=  t;    cy +=  t;    return *this; }
	Size_& operator-=(Size_ p)  { cx -=  p.cx; cy -=  p.cy; return *this; }
	Size_& operator-=(double t) { cx -=  t;    cy -=  t;    return *this; }
	Size_& operator*=(Size_ p)  { cx *=  p.cx; cy *=  p.cy; return *this; }
	Size_& operator*=(double t) { cx *=  t;    cy *=  t;    return *this; }
	Size_& operator/=(Size_ p)  { cx /=  p.cx; cy /=  p.cy; return *this; }
	Size_& operator/=(double t) { cx /=  t;    cy /=  t;    return *this; }
	Size_& operator<<=(int sh)  { cx <<= sh;   cy <<= sh;   return *this; }
	Size_& operator>>=(int sh)  { cx >>= sh;   cy >>= sh;   return *this; }
	
	Size_ operator*(double v) {return Size_(cx * v, cy * v);}
	Size_ operator/(double v) {return Size_(cx * v, cy * v);}
	String ToString() const {return "Size(" + IntStr(cx) + ", " + IntStr(cy) + ")";}
	
	operator Size_<int>() const {return Size_<int>(cx,cy);}
	operator Size_<double>() const {return Size_<double>(cx,cy);}
	
	bool	IsNull() const {return ::UPP::IsNull(cx) || ::UPP::IsNull(cy);}
	void	SetNull() const {SetNull(cx); SetNull(cy);}
	
};

template <class T>
bool operator==(const Size_<T>& a, const Size_<T>& b) {
	return a.cx == b.cx && a.cy == b.cy;
}

typedef Size_<int> Size;
typedef Size_<float> SizeF32;
typedef Size_<double> Sizef;



template <class T>
struct Rect_ : Moveable<Rect_<T>> {
	T left = 0, top = 0, right = 0, bottom = 0;

	typedef Point_<T>  Pt;
	typedef Size_<T>   Sz;
	
	static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	static const char* GetTypeName() {return "Rect_<T>";}
	
	Rect_() {}
	Rect_(const Rect_& r) { *this = r; }
	Rect_(const Size_<T>& sz) { right = sz.cx; bottom = sz.cy; }
	Rect_(T l, T t, T r, T b) : top(t), left(l), bottom(b), right(r) {}

	bool IsEqual(const Rect_& r) const {return top == r.top && left == r.left && bottom == r.bottom && right == r.right;}
	bool IsEmpty() const {return left == right && top == bottom;}
	
	bool operator==(const Rect_& r) const {return IsEqual(r);}
	bool operator!=(const Rect_& r) const {return !IsEqual(r);}
	void operator=(const Rect_& src) {
		top = src.top;
		left = src.left;
		bottom = src.bottom;
		right = src.right;
	}
	//bool operator!=(const Rect_& src) { return !(*this == src); }

	Point TopLeft() const { return Point(left, top); }
	Point TopRight() const { return Point(right, top); }
	Point BottomRight() const { return Point(right, bottom); }
	Point BottomLeft() const { return Point(left, bottom); }

	T GetWidth() const { return right - left; }
	T GetHeight() const { return bottom - top; }
	T Width() const { return right - left; }
	T Height() const { return bottom - top; }
	Sz GetSize() const { return Sz(Width(), Height()); }
	bool Contains(const Point_<T>& pt) const {return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom;}
	bool Contains(const Rect_<T>& r) const {return Contains(TopLeft()) && Contains(TopRight()) && Contains(BottomRight()) && Contains(BottomLeft());}
	bool Intersects(const Rect_<T>& r) const {
		if(IsNull() || r.IsNull()) return false;
		return r.right >= left && r.bottom >= top && r.left <= right && r.top <= bottom;
	}
	Point_<T> CenterPoint() const {return Point_<T>((right+left)/(T)2, (top+bottom)/(T)2);}
	int ToInt() const {return top * left * bottom * right;}
	
	void   InflateHorz(T dx) { left -= dx; right += dx; }
	void   InflateVert(T dy) { top -= dy; bottom += dy; }
	void   Inflate(T dx, T dy) { InflateHorz(dx); InflateVert(dy); }
	void   Inflate(Sz sz) { Inflate(sz.cx, sz.cy); }
	void   Inflate(T dxy) { Inflate(dxy, dxy); }
	void   Inflate(T l, T t, T r, T b) { left -= l; top -= t; right += r; bottom += b; }
	void   Inflate(const Rect_& r) { Inflate(r.left, r.top, r.right, r.bottom); }

	void   DeflateHorz(T dx) { InflateHorz(-dx); }
	void   DeflateVert(T dy) { InflateVert(-dy); }
	void   Deflate(T dx, T dy) { Inflate(-dx, -dy); }
	void   Deflate(Sz sz) { Inflate(-sz); }
	void   Deflate(T dxy) { Inflate(-dxy); }
	void   Deflate(T l, T t, T r, T b) { Inflate(-l, -t, -r, -b); }
	void   Deflate(const Rect_& r) { Deflate(r.left, r.top, r.right, r.bottom); }

	operator Rect_<int>() const {return Rect_<int>(left,top,right,bottom);}
	operator Rect_<double>() const {return Rect_<double>(left,top,right,bottom);}
	
	bool	IsNull() const {return ::UPP::IsNull(left) || ::UPP::IsNull(top) || ::UPP::IsNull(right) || ::UPP::IsNull(bottom);}
	void	SetNull() const {::UPP::SetNull(left); ::UPP::SetNull(top); ::UPP::SetNull(right); ::UPP::SetNull(bottom);}
	
	
	hash_t	GetHashValue() const {CombineHash c; c.Put(UPP::GetHashValue(left));  c.Put(UPP::GetHashValue(top));  c.Put(UPP::GetHashValue(right));  c.Put(UPP::GetHashValue(bottom)); return c;}
	String	ToString() const {String s; s << "[" << left << ", " << top << ", " << right << ", " << bottom << "](" << Width() << ", " << Height() << ")"; return s;}
	
};

template <class T>
bool operator==(const Rect_<T>& a, const Rect_<T>& b) {
	return
		a.top    == b.top &&
		a.left   == b.left &&
		a.bottom == b.bottom &&
		a.right  == b.right;
}

typedef Rect_<int> Rect;
typedef Rect_<double> Rectf;


inline Rect RectC(int x, int y, int w, int h) { return Rect(x, y, x + w, y + h); }




template <class T>
struct Tri_ : Moveable<Tri_<T>> {
	typedef Point_<T> Pt;

	Pt a, b, c;
	
	static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	static const char* GetTypeName() {return "Tri_<T>";}
	
	Tri_() {}
	Tri_(const Tri_& t) { *this = t; }
	Tri_(Pt a, Pt b, Pt c) : a(a), b(b), c(c) {}
	void operator=(const Tri_& t) {
		a = t.a;
		b = t.b;
		c = t.c;
	}
	void Set(const Pt& a, const Pt& b, const Pt& c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

typedef Tri_<int> Tri;
typedef Tri_<float> TriF32;
typedef Tri_<double> Trif;





Pointf Intersect(const Pointf& a, const Pointf& b, const Pointf& c, const Pointf& d);






template <class T>
struct Point3_ : Moveable<Point3_<T>> {
	T x = 0, y = 0, z = 0;

	Point3_() {}

	Point3_(T x, T y, T z) : x(x), y(y), z(z) {}

	Point3_(const Point3_& pt) : x(pt.x), y(pt.y), z(pt.z) {}



	static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	static const char* GetTypeName() {return "Point3_<T>";}
	
	bool IsEqual(const Point3_& p) const {return x == p.x && y == p.y && z == p.z;}
	bool operator!=(const Point3_& p) const {return !IsEqual(p);}
	bool operator==(const Point3_& p) const {return IsEqual(p);}
	
	double Length() { return sqrt(x * x + y * y + z * z); }
	double Slope() { return y / x; }

	Point3_ operator-() const { return Point3_(-x, -y, -z); }
	Point3_ operator*(double k) const { return Point3_(x * k, y * k, z * k); }
	Point3_ operator/(double k) const { return Point3_(x / k, y / k, z / k); }

	Point3_ operator+(const Point3_& b) const { return Point3_(x + b.x, y + b.y, z + b.z); }
	Point3_ operator-(const Point3_& b) const { return Point3_(x - b.x, y - b.y, z - b.z); }
	Point3_ operator*(const Point3_& b) const { return Point3_(x * b.x, y * b.y, z * b.z); }
	Point3_ operator/(const Point3_& b) const { return Point3_(x / b.x, y / b.y, z / b.y); }


	template <class V>
	Point3_& operator=(const V& b) {
		x = (T)b.x;
		y = (T)b.y;
		z = (T)b.z;
		return *this;
	}

	Point3_& operator+=(const Point3_& b) {
		x = (T)(x + b.x);
		y = (T)(y + b.y);
		z = (T)(z + b.z);
		return *this;
	}

	Point3_& operator-=(const Point3_& b) {
		x = (T)(x - b.x);
		y = (T)(y - b.y);
		z = (T)(z - b.z);
		return *this;
	}

	Point3_& operator*=(const double k) {
		x = (T)(x * k);
		y = (T)(y * k);
		z = (T)(z * k);
		return *this;
	}

	Point3_& operator/=(const double k) {
		x = (T)(x / k);
		y = (T)(y / k);
		z = (T)(z / k);
		return *this;
	}

	static void Dot(const Point3_& a, const Point3_& b, Point3_& o) {
		//dot product: o = a dot b
		o.x = a.x * b.x;
		o.y = a.y * b.y;
		o.z = a.z * b.z;
	}

	Point3_ DotProd(const Point3_& b) const {
		//return dot product
		return Point3(x * b.x, y * b.y, z * b.z);
	}
	
	String	ToString() const {return "Point3(" + IntStr(x) + ", " + IntStr(y) + ", " + IntStr(z) + ")";}
	int		ToInt() const {return x * y * z;}
	double	ToDouble() const {return x * y * z;}
	hash_t	GetHashValue() const {return x * y * z;}
	
	operator Point3_<int>() const {return Point3_<int>(x,y,z);}
	operator Point3_<double>() const {return Point3_<double>(x,y,z);}
	
	bool	IsNull() const {return IsNull(x) || IsNull(y) || IsNull(z);}
	void	SetNull() const {SetNull(x); SetNull(y); SetNull(z);}
	
};


typedef Point3_<int> Point3;
typedef Point3_<float> Point3F32;
typedef Point3_<double> Point3f;




template <class T>
struct Vol_ : Moveable<Vol_<T>> {
	T cx = 0, cy = 0, cz = 0;

	Vol_() {}
	Vol_(const Vol_& sz) { *this = sz; }
	Vol_(T cx, T cy, T cz) : cx(cx), cy(cy), cz(cz) {}
	
	static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	static const char* GetTypeName() {return "Vol_<T>";}
	
	void Clear() {cx = 0; cy = 0; cz = 0;}
	bool IsEmpty() const {return cx == 0 && cy == 0 && cz == 0;}
	bool IsPositive() const {return cx > 0 && cy > 0 && cz > 0;}
	bool IsEqual(const Vol_& sz) const {return cx == sz.cx && cy == sz.cy && cz == sz.cz;}
	
	T		GetVolume() const {return cx * cy * cz;}
	int		ToInt() const {return cx * cy * cz;}
	double	ToDouble() const {return cx * cy * cz;}
	hash_t	GetHashValue() const {return cx * cy * cz;}
	
	T&       operator[](int i)       {ASSERT(i >= 0 && i <= 2); if (i == 0) return &cx; if (i == 1) return &cy; if (i == 2) return &cz; Panic("invalid Vol_<T> subscript pos"); NEVER();}
	const T& operator[](int i) const {ASSERT(i >= 0 && i <= 2); if (i == 0) return &cx; if (i == 1) return &cy; if (i == 2) return &cz; Panic("invalid Vol_<T> subscript pos"); NEVER();}
	
	bool operator==(const Vol_& sz) const {return IsEqual(sz);}
	bool operator!=(const Vol_& sz) const {return !IsEqual(sz);}
	void operator=(const Vol_& sz) {
		cx = sz.cx;
		cy = sz.cy;
		cz = sz.cz;
	}

	Vol_& operator+=(Vol_ p)   { cx +=  p.cx; cy +=  p.cy; cz += p.cz;	return *this; }
	Vol_& operator+=(double t) { cx +=  t;    cy +=  t;    cz += t;		return *this; }
	Vol_& operator-=(Vol_ p)   { cx -=  p.cx; cy -=  p.cy; cz -= p.cz;	return *this; }
	Vol_& operator-=(double t) { cx -=  t;    cy -=  t;    cz -= t;		return *this; }
	Vol_& operator*=(Vol_ p)   { cx *=  p.cx; cy *=  p.cy; cz *= p.cz;	return *this; }
	Vol_& operator*=(double t) { cx *=  t;    cy *=  t;    cz *= t;		return *this; }
	Vol_& operator/=(Vol_ p)   { cx /=  p.cx; cy /=  p.cy; cz /= p.cz;	return *this; }
	Vol_& operator/=(double t) { cx /=  t;    cy /=  t;    cz /= t;		return *this; }
	Vol_& operator<<=(int sh)  { cx <<= sh;   cy <<= sh;   cz <<= sh;	return *this; }
	Vol_& operator>>=(int sh)  { cx >>= sh;   cy >>= sh;   cz >>= sh;	return *this; }
	
	Vol_ operator*(double v) {return Vol_(cx * v, cy * v, cz * v);}
	Vol_ operator/(double v) {return Vol_(cx * v, cy * v, cz * v);}
	String ToString() const {return "Vol(" + IntStr(cx) + ", " + IntStr(cy) + ", " + IntStr(cz) + ")";}
	
	operator Vol_<int>() const {return Vol_<int>(cx,cy,cz);}
	operator Vol_<double>() const {return Vol_<double>(cx,cy,cz);}
	
	bool	IsNull() const {return ::UPP::IsNull(cx) || ::UPP::IsNull(cy) || ::UPP::IsNull(cz);}
	void	SetNull() const {SetNull(cx); SetNull(cy); SetNull(cz);}
	
};

template <class T>
bool operator==(const Vol_<T>& a, const Vol_<T>& b) {
	return a.cx == b.cx && a.cy == b.cy && a.cz == b.cz;
}

typedef Vol_<int> Vol;
typedef Vol_<float> VolF32;
typedef Vol_<double> Volf;



template <class T>
struct Cub_ : Moveable<Cub_<T>> {
	T left = 0, top = 0, near = 0, right = 0, bottom = 0, far = 0;

	typedef Point_<T>  Pt2;
	typedef Point3_<T> Pt;
	typedef Size_<T>   Sz;
	typedef Rect_<T>   Rc;
	typedef Tri_<T>    Tri;
	typedef Vol_<T>    Vol;
	
	static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	static const char* GetTypeName() {return "Cub_<T>";}
	
	Cub_() {}
	Cub_(const Cub_& r) { *this = r; }
	Cub_(const Size_<T>& sz) { right = sz.cx; bottom = sz.cy; }
	Cub_(T l, T t, T n, T r, T b, T f) : top(t), left(l), near(n), bottom(b), right(r), far(f) {}

	bool IsEqual(const Cub_& r) const {return top == r.top && left == r.left && near == r.near && bottom == r.bottom && right == r.right && far == r.far;}
	bool IsEmpty() const {return left == right && top == bottom && near == far;}
	
	bool operator==(const Cub_& r) const {return IsEqual(r);}
	bool operator!=(const Cub_& r) const {return !IsEqual(r);}
	void operator=(const Cub_& src) {
		top = src.top;
		left = src.left;
		near = src.near;
		bottom = src.bottom;
		right = src.right;
		far = src.far;
	}

	Pt2 TopLeft() const { return Point(left, top); }
	Pt2 TopRight() const { return Point(right, top); }
	Pt2 BottomRight() const { return Point(right, bottom); }
	Pt2 BottomLeft() const { return Point(left, bottom); }
	Pt TopLeftNear() const { return Pt(left, top, near); }
	Pt TopRightNear() const { return Pt(right, top, near); }
	Pt BottomRightFar() const { return Pt(right, bottom, far); }
	Pt BottomLeftFar() const { return Pt(left, bottom, far); }

	T GetWidth() const { return right - left; }
	T GetHeight() const { return bottom - top; }
	T GetDepth() const { return far - near; }
	T Width() const { return right - left; }
	T Height() const { return bottom - top; }
	T Depth() const { return far - near; }
	Vol GetSize() const { return Vol(right - left, bottom - top, far - near); }
	bool Contains(const Pt& pt) const {return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom && pt.z >= near && pt.z <= far;}
	bool Contains(const Cub_<T>& r) const {return Contains(TopLeftNear()) && Contains(BottomRightFar());}
	bool Intersects(const Cub_<T>& r) const {
		if(IsNull() || r.IsNull()) return false;
		return	r.right >= left &&
				r.bottom >= top &&
				r.left <= right &&
				r.top <= bottom &&
				r.far >= near &&
				r.near <= far;
	}
	Pt CenterPoint() const {return Point_<T>((right+left)/(T)2, (top+bottom)/(T)2, (near+far)/(T)2);}
	int ToInt() const {return top * left * bottom * right;}
	
	void   InflateHorz(T dx) { left -= dx; right += dx; }
	void   InflateVert(T dy) { top -= dy; bottom += dy; }
	void   InflateZ(T dz) { near -= dz; far += dz; }
	void   Inflate(T dx, T dy, T dz) { InflateHorz(dx); InflateVert(dy); InflateZ(dz);}
	void   Inflate(Vol sz) { Inflate(sz.cx, sz.cy, sz.cz); }
	void   Inflate(T dxy) { Inflate(dxy, dxy, dxy); }
	void   Inflate(T l, T t, T n, T r, T b, T f) { left -= l; top -= t; right += r; bottom += b; near -= n; far += f;}
	void   Inflate(const Cub_& r) { Inflate(r.left, r.top, r.near, r.right, r.bottom, r.far); }

	void   DeflateHorz(T dx) { InflateHorz(-dx); }
	void   DeflateVert(T dy) { InflateVert(-dy); }
	void   DeflateZ(T dy) { InflateZ(-dy); }
	void   Deflate(T dx, T dy, T dz) { Inflate(-dx, -dy, -dz); }
	void   Deflate(Vol sz) { Inflate(-sz); }
	void   Deflate(T dxy) { Inflate(-dxy); }
	void   Deflate(T l, T t, T n, T r, T b, T f) { Inflate(-l, -t, -n, -r, -b, -f); }
	void   Deflate(const Cub_& r) { Deflate(r.left, r.top, r.near, r.right, r.bottom, r.far); }

	operator Cub_<int>() const {return Cub_<int>(left,top,near,right,bottom,far);}
	operator Cub_<double>() const {return Cub_<double>(left,top,near,right,bottom,far);}
	
	bool	IsNull() const {return ::UPP::IsNull(left) || ::UPP::IsNull(top) || ::UPP::IsNull(near) || ::UPP::IsNull(right) || ::UPP::IsNull(bottom) || ::UPP::IsNull(far);}
	void	SetNull() const {::UPP::SetNull(left); ::UPP::SetNull(top); ::UPP::SetNull(near); ::UPP::SetNull(right); ::UPP::SetNull(bottom); ::UPP::SetNull(far);}
	
	
	hash_t	GetHashValue() const {CombineHash c; c.Put(UPP::GetHashValue(left)); c.Put(UPP::GetHashValue(top)); c.Put(UPP::GetHashValue(near)); c.Put(UPP::GetHashValue(right)); c.Put(UPP::GetHashValue(bottom)); c.Put(UPP::GetHashValue(far)); return c;}
	String	ToString() const {String s; s << "[" << left << ", " << top << ", " << near << ", " << right << ", " << bottom << ", " << far << "](" << Width() << ", " << Height() << ", " << Depth() << ")"; return s;}
	
};

template <class T>
bool operator==(const Cub_<T>& a, const Cub_<T>& b) {
	return
		a.top    == b.top &&
		a.left   == b.left &&
		a.bottom == b.bottom &&
		a.right  == b.right &&
		a.near   == b.near &&
		a.far    == b.far;
}

typedef Cub_<int> Cub;
typedef Cub_<double> Cubf;


inline Cub CubC(int x, int y, int z, int w, int h, int d) { return Cub(x, y, z, x + w, y + h, z + d); }







NAMESPACE_UPP_END

#endif
