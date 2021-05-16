#ifndef _Local_Geom_h_
#define _Local_Geom_h_


NAMESPACE_TOPSIDE_BEGIN


template <class T>
struct Size3_ : Moveable<Size3_<T>> {
	T cx = 0, cy = 0, cz = 0;

	Size3_() {}
	Size3_(const Size3_& sz) { *this = sz; }
	Size3_(T cx, T cy, T cz) : cx(cx), cy(cy), cz(cz) {}
	
	bool IsEmpty() const {return cx == 0 && cy == 0 && cz == 0;}
	bool IsPositive() const {return cx > 0 && cy > 0 && cz > 0;}
	bool IsEqual(const Size3_& sz) const {return cx == sz.cx && cy == sz.cy && cz == sz.cz;}
	
	bool operator==(const Size3_& sz) {return IsEqual(sz);}
	bool operator!=(const Size3_& sz) {return !IsEqual(sz);}
	void operator=(const Size3_& sz) {
		cx = sz.cx;
		cy = sz.cy;
		cz = sz.cz;
	}

	Size3_& operator+=(Size3_ p) { cx += p.cx; cy += p.cy; cz += p.cz; return *this; }
	Size3_& operator+=(T t)      { cx += t;    cy += t;    cz += t;    return *this; }
	Size3_& operator-=(Size3_ p) { cx -= p.cx; cy -= p.cy; cz -= p.cz; return *this; }
	Size3_& operator-=(T t)      { cx -= t;    cy -= t;    cz -= t;    return *this; }
	Size3_& operator*=(Size3_ p) { cx *= p.cx; cy *= p.cy; cz *= p.cz; return *this; }
	Size3_& operator*=(T t)      { cx *= t;    cy *= t;    cz *= t;    return *this; }
	Size3_& operator/=(Size3_ p) { cx /= p.cx; cy /= p.cy; cz /= p.cz; return *this; }
	Size3_& operator/=(T t)      { cx /= t;    cy /= t;    cz /= t;    return *this; }
	Size3_& operator<<=(int sh)  { cx <<= sh;  cy <<= sh;  cz <<= sh;  return *this; }
	Size3_& operator>>=(int sh)  { cx >>= sh;  cy >>= sh;  cz >>= sh;  return *this; }
	
	String ToString() const {return "Size3(" + IntStr(cx) + ", " + IntStr(cy) + ", " + IntStr(cz) + ")";}
};

template <class T>
bool operator==(const Size3_<T>& a, const Size3_<T>& b) {
	return a.cx == b.cx && a.cy == b.cy && a.cz == b.cz;
}

typedef Size3_<int> Size3;
typedef Size3_<float> Size3f;
typedef Size3_<double> Size3d;




bool IsColliding(Pointf a, Pointf b, Pointf c, Pointf d);

NAMESPACE_TOPSIDE_END

#endif
