#ifndef _CoreAlt_Gtypes_h_
#define _CoreAlt_Gtypes_h_

NAMESPACE_UPP_BEGIN



template <class T>
struct Point_ : Moveable<Point_<T>> {
	RTTI_SECONDARY(Point)
	
	T x = 0, y = 0;

	Point_() {}
	Point_(T v) : x(v), y(v) {}
	Point_(T x, T y) : x(x), y(y) {}
	Point_(const Point_& pt) : x(pt.x), y(pt.y) {}
	Point_(const Nuller& n) : x(n), y(n) {}
	
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


	Point_& operator=(const Nuller& n) {
		x = n;
		y = n;
		return *this;
	}
	
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
struct Size_ : Moveable<Size_<T>> {
	RTTI_SECONDARY(Size)
	
	T cx = 0, cy = 0;

	Size_() {}
	Size_(const Size_& sz) { *this = sz; }
	Size_(T v) : cx(v), cy(v) {}
	Size_(T cx, T cy) : cx(cx), cy(cy) {}
	
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
	
	void operator=(const Size_& sz) {
		cx = sz.cx;
		cy = sz.cy;
	}
	
	Size_& operator=(const Nuller& n) {
		cx = n;
		cy = n;
		return *this;
	}
	
	Size_&        operator+=(Size_ p)          { cx  += p.cx; cy  += p.cy; return *this; }
	Size_&        operator+=(T t)              { cx  += t;    cy  += t;    return *this; }
	Size_&        operator-=(Size_ p)          { cx  -= p.cx; cy  -= p.cy; return *this; }
	Size_&        operator-=(T t)              { cx  -= t;    cy  -= t;    return *this; }
	Size_&        operator*=(Size_ p)          { cx  *= p.cx; cy  *= p.cy; return *this; }
	Size_&        operator*=(T t)              { cx  *= t;    cy  *= t;    return *this; }
	Size_&        operator/=(Size_ p)          { cx  /= p.cx; cy  /= p.cy; return *this; }
	Size_&        operator/=(T t)              { cx  /= t;    cy  /= t;    return *this; }
	Size_&        operator<<=(int sh)          { cx <<= sh;   cy <<= sh;   return *this; }
	Size_&        operator>>=(int sh)          { cx >>= sh;   cy >>= sh;   return *this; }

	Size_&        operator++()                 { ++cx; ++cy; return *this; }
	Size_&        operator--()                 { --cx; --cy; return *this; }

	friend Size_  operator+(Size_ s)           { return s; }
	friend Size_  operator-(Size_ s)           { return Size_(-s.cx, -s.cy); }

	friend Size_  operator+(Size_ a, Size_ b)  { return a += b; }
	friend Size_  operator+(Size_ a, T t)      { return a += t; }
	friend Size_  operator+(T t, Size_ b)      { return b += t; }
	friend Size_  operator-(Size_ a, Size_ b)  { return a -= b; }
	friend Size_  operator-(Size_ a, T t)      { return a -= t; }
	friend Size_  operator-(T t, Size_ b)      { b = -b; return b += t; }
	friend Size_  operator*(Size_ a, Size_ b)  { return a *= b; }
	friend Size_  operator*(Size_ a, T b)      { return a *= b; }
	friend Size_  operator*(T a, Size_ b)      { return b *= a; }
	friend Size_  operator/(Size_ a, Size_ b)  { return a /= b; }
	friend Size_  operator/(Size_ a, T b)      { return a /= b; }
	friend Size_  operator<<(Size_ a, int sh)  { return a <<= sh; }
	friend Size_  operator>>(Size_ a, int sh)  { return a >>= sh; }

	friend bool   operator==(Size_ a, Size_ b) { return a.cx == b.cx && a.cy == b.cy; }
	friend bool   operator!=(Size_ a, Size_ b) { return !(a == b); }

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
	RTTI_SECONDARY(Rect)
	
	T left = 0, top = 0, right = 0, bottom = 0;

	typedef Point_<T>  Pt;
	typedef Size_<T>   Sz;
	
	Rect_() {}
	Rect_(const Rect_& r) { *this = r; }
	Rect_(const Size_<T>& sz) { right = sz.cx; bottom = sz.cy; }
	Rect_(T l, T t, T r, T b) : top(t), left(l), bottom(b), right(r) {}
	Rect_(const Nuller& n) : left(n), top(n), right(n), bottom(n) {}
	Rect_(const Pt& pt, const Sz& sz) : left(pt.x), top(pt.y), right(pt.x + sz.cx), bottom(pt.y + sz.cy) {}
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
	Rect_& operator=(const Nuller& n) {
		top = n;
		left = n;
		bottom = n;
		right = n;
		return *this;
	}
	
	//bool operator!=(const Rect_& src) { return !(*this == src); }
	void Set(T l, T t, T r, T b) { left = l; top = t; right = r; bottom = b; }
	void Set(const Rect_& r) { Set(r.left, r.top, r.right, r.bottom); }
	
	Point FirstCorner() const { return Point(left, top); }
	Point TopLeft() const { return Point(left, top); }
	Point TopRight() const { return Point(right, top); }
	Point BottomRight() const { return Point(right, bottom); }
	Point BottomLeft() const { return Point(left, bottom); }

	T GetWidth() const { return right - left; }
	T GetHeight() const { return bottom - top; }
	T Width() const { return right - left; }
	T Height() const { return bottom - top; }
	Sz GetSize() const { return Sz(Width(), Height()); }
	Sz Size() const { return Sz(Width(), Height()); }
	bool Contains(const Point_<T>& pt) const {return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom;}
	bool Contains(const Rect_<T>& r) const {return Contains(TopLeft()) && Contains(TopRight()) && Contains(BottomRight()) && Contains(BottomLeft());}
	bool Intersects(const Rect_<T>& r) const {
		if(IsNull() || r.IsNull()) return false;
		return r.right >= left && r.bottom >= top && r.left <= right && r.top <= bottom;
	}
	Point_<T> CenterPoint() const {return Point_<T>((right+left)/(T)2, (top+bottom)/(T)2);}
	int ToInt() const {return top * left * bottom * right;}
	
	Pt     CenterPos(T cx, T cy) const;
	Pt     CenterPos(Sz sz) const           { return CenterPos(sz.cx, sz.cy); }
	Rect_  CenterRect(Sz sz) const          { return Rect_(CenterPos(sz), sz); }
	Rect_  CenterRect(T cx, T cy) const     { return CenterRect(Sz(cx, cy)); }

	void   InflateHorz(T dx) { left -= dx; right += dx; }
	void   InflateVert(T dy) { top -= dy; bottom += dy; }
	void   Inflate(T dx, T dy) { InflateHorz(dx); InflateVert(dy); }
	void   Inflate(Sz sz) { Inflate(sz.cx, sz.cy); }
	void   Inflate(T dxy) { Inflate(dxy, dxy); }
	void   Inflate(T l, T t, T r, T b) { left -= l; top -= t; right += r; bottom += b; }
	void   Inflate(const Rect_& r) { Inflate(r.left, r.top, r.right, r.bottom); }
	
	Rect_  InflatedHorz(T dx) const             { Rect_ r = *this; r.InflateHorz(dx); return r; }
	Rect_  InflatedVert(T dy) const             { Rect_ r = *this; r.InflateVert(dy); return r; }
	Rect_  Inflated(T dx, T dy) const           { Rect_ r = *this; r.Inflate(dx, dy); return r; }
	Rect_  Inflated(Sz sz) const                { Rect_ r = *this; r.Inflate(sz); return r; }
	Rect_  Inflated(T dxy) const                { Rect_ r = *this; r.Inflate(dxy); return r; }
	Rect_  Inflated(T l, T t, T r, T b) const   { Rect_ m = *this; m.Inflate(l, t, r, b); return m; }
	Rect_  Inflated(const Rect_& q) const       { Rect_ r = *this; r.Inflate(q); return r; }
	
	void   DeflateHorz(T dx) { InflateHorz(-dx); }
	void   DeflateVert(T dy) { InflateVert(-dy); }
	void   Deflate(T dx, T dy) { Inflate(-dx, -dy); }
	void   Deflate(Sz sz) { Inflate(-sz); }
	void   Deflate(T dxy) { Inflate(-dxy); }
	void   Deflate(T l, T t, T r, T b) { Inflate(-l, -t, -r, -b); }
	void   Deflate(const Rect_& r) { Deflate(r.left, r.top, r.right, r.bottom); }
	
	void   OffsetHorz(T dx)                     { left += dx; right += dx; }
	void   OffsetVert(T dy)                     { top += dy; bottom += dy; }
	void   Offset(T dx, T dy)                   { OffsetHorz(dx); OffsetVert(dy); }
	void   Offset(Sz sz)                        { Offset(sz.cx, sz.cy); }
	void   Offset(Pt p)                         { Offset(p.x, p.y); }
	
	Rect_  OffsetedHorz(T dx) const             { Rect_ r = *this; r.OffsetHorz(dx); return r; }
	Rect_  OffsetedVert(T dy) const             { Rect_ r = *this; r.OffsetVert(dy); return r; }
	Rect_  Offseted(T dx, T dy) const           { Rect_ r = *this; r.Offset(dx, dy); return r; }
	Rect_  Offseted(Sz sz) const                { Rect_ r = *this; r.Offset(sz); return r; }
	Rect_  Offseted(Pt p) const                 { Rect_ r = *this; r.Offset(p); return r; }
	
	void   Union(Pt p);
	void   Union(const Rect_& rc);
	void   Intersect(const Rect_& rc);
	
	Rect_& operator+=(Sz sz)                                { Offset(sz); return *this; }
	Rect_& operator+=(Pt p)                                 { Offset(p); return *this; }
	Rect_& operator+=(const Rect_& b);
	Rect_& operator-=(Sz sz)                                { Offset(-sz); return *this; }
	Rect_& operator-=(Pt p)                                 { Offset(-p); return *this; }
	Rect_& operator-=(const Rect_& b);
	Rect_& operator*=(T t)                                  { left *= t; right *= t; top *= t; bottom *= t; return *this; }
	Rect_& operator/=(T t)                                  { left /= t; right /= t; top /= t; bottom /= t; return *this; }
	
	friend Rect_ operator+(Rect_ a, Sz b)                   { return a += b; }
	friend Rect_ operator+(Sz a, Rect_ b)                   { return b += a; }
	friend Rect_ operator+(Rect_ a, Pt b)                   { return a += b; }
	friend Rect_ operator+(Pt a, Rect_ b)                   { return b += a; }
	friend Rect_ operator+(Rect_ a, const Rect_& b)         { return a += b; }
	friend Rect_ operator-(Rect_ a, Sz b)                   { return a -= b; }
	friend Rect_ operator-(Rect_ a, Pt b)                   { return a -= b; }
	friend Rect_ operator-(Rect_ a, const Rect_& b)         { return a -= b; }
	friend Rect_ operator*(Rect_ a, T t)                    { return a *= t; }
	friend Rect_ operator*(T t, Rect_ a)                    { return a *= t; }
	friend Rect_ operator/(Rect_ a, T t)                    { return a /= t; }
	friend Rect_ operator&(Rect_ a, Rect_ b)                { a.Intersect(b); return a; }
	friend Rect_ operator|(Rect_ a, Rect_ b)                { a.Union(b); return a; }
	friend bool  operator&&(const Rect_& a, const Rect_& b) { return a.Intersects(b); }
	friend bool  operator>=(const Rect_& a, Pt b)           { return a.Contains(b); }
	friend bool  operator<=(Pt a, const Rect_& b)           { return b.Contains(a); }
	friend bool  operator<=(const Rect_& a, const Rect_& b) { return b.Contains(a); }
	friend bool  operator>=(const Rect_& b, const Rect_& a) { return a.Contains(b); }

	operator Rect_<int>() const {return Rect_<int>(left,top,right,bottom);}
	operator Rect_<double>() const {return Rect_<double>(left,top,right,bottom);}
	
	bool	IsNull() const {return ::UPP::IsNull(left) || ::UPP::IsNull(top) || ::UPP::IsNull(right) || ::UPP::IsNull(bottom);}
	bool	IsNullInstance() const {return ::UPP::IsNull(left) || ::UPP::IsNull(top) || ::UPP::IsNull(right) || ::UPP::IsNull(bottom);}
	void	SetNull() const {::UPP::SetNull(left); ::UPP::SetNull(top); ::UPP::SetNull(right); ::UPP::SetNull(bottom);}
	
	hash_t	GetHashValue() const {CombineHash c; c.Put(UPP::GetHashValue(left));  c.Put(UPP::GetHashValue(top));  c.Put(UPP::GetHashValue(right));  c.Put(UPP::GetHashValue(bottom)); return c;}
	String	ToString() const {String s; s << "[" << left << ", " << top << ", " << right << ", " << bottom << "](" << Width() << ", " << Height() << ")"; return s;}
	
	static bool	IsNull(const Rect_& r) {return r.IsNull();}
	
};

template <class T>
T GHalf_(T t) { return t >> 1; }

template <class T>
Point_<T> Rect_<T>::CenterPos(T cx, T cy) const {
	return Point_<T>(left + GHalf_(Width() - cx), top + GHalf_(Height() - cy));
}

template <class T>
void Rect_<T>::Intersect(const Rect_<T>& r) {
	if(r.left > left) left = r.left;
	if(r.top > top) top = r.top;
	if(right < left) right = left;
	if(r.right < right) right = r.right;
	if(r.bottom < bottom) bottom = r.bottom;
	if(bottom < top) bottom = top;
}

template <class T>
void Rect_<T>::Union(const Rect_<T>& r) {
	if(IsNull(r)) return;
	if(IsNullInstance()) {
		Set(r);
		return;
	}
	if(r.left < left) left = r.left;
	if(r.top < top) top = r.top;
	if(r.right > right) right = r.right;
	if(r.bottom > bottom) bottom = r.bottom;
}



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
typedef Rect_<int16> Rect16;


inline Rect RectC(int x, int y, int w, int h) { return Rect(x, y, x + w, y + h); }







Size        GetFitSize(Size objsize, int cx, int cy);
inline Size GetFitSize(Size objsize, Size intosize) { return GetFitSize(objsize, intosize.cx, intosize.cy); }







NAMESPACE_UPP_END

#endif
