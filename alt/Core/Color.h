#ifndef _CoreAlt_Color_h_
#define _CoreAlt_Color_h_

NAMESPACE_UPP_BEGIN



template <class T>
struct RGBAT : Moveable<RGBAT<T>> {
	T r, g, b, a;

	RGBAT() {}
	RGBAT(const RGBAT& c) { *this = c; }

	RGBAT(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}

	void operator=(const RGBAT& c) {
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}
	
	T& operator[](int i) {ASSERT(i >= 0 && i < 4); return *(&r + i);}
	
	
	String ToString() const {return "[" + AsString(r) + ", " + AsString(g) + ", " + AsString(b) + ", " + AsString(a) + "]";}
	
	
	unsigned GetHashValue() const {
		if (sizeof(T) == 1)	return *reinterpret_cast<const uint32*>(&r);
		else				return CombineHash().Put(r).Put(g).Put(b).Put(a);
	}
};

typedef RGBAT<byte>		RGBA;
typedef RGBAT<float>	RGBAf32;
typedef RGBAT<double>	RGBAf;

bool operator==(const RGBA& a, const RGBA& b);
bool operator==(const RGBAf& a, const RGBAf& b);


inline RGBA RGBAZero() {RGBA r{0,0,0,0}; return r;}





template <class T>
struct RGBA1T : Moveable<RGBA1T<T>> {
	T r, g, b, a;

	RGBA1T() {}
	RGBA1T(const RGBA1T& c) { *this = c; }

	RGBA1T(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}

	void operator=(const RGBA1T& c) {
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}
	bool operator==(const RGBA1T& p) {return MemoryCompare(this, &p, sizeof(RGBA1T)) == 0;}
	
};

typedef RGBA1T<byte>	RGBA1;
typedef RGBA1T<float>	RGBA1f32;
typedef RGBA1T<double>	RGBA1f;









#ifndef PLATFORM_WIN32
inline int        GetRValue(dword c)             { return (byte)(c >> 0); }
inline int        GetGValue(dword c)             { return (byte)(c >> 8); }
inline int        GetBValue(dword c)             { return (byte)(c >> 16); }
inline dword      RGB(byte r, byte g, byte b)    { return r | (g << 8) | (b << 16); }
#endif





class Color : public ValueType<Color, COLOR_V, Moveable<Color> > {
protected:
	dword    color;

	dword Get() const;

public:
	RTTI_SECONDARY(Color)
	
	dword    GetRaw() const            { return color; }

	int      GetR() const              { return GetRValue(Get()); }
	int      GetG() const              { return GetGValue(Get()); }
	int      GetB() const              { return GetBValue(Get()); }

	void     SetNull()                 { color = 0xffffffff; }
	bool     IsNullInstance() const    { return color == 0xffffffff; }
	hash_t   GetHashValue() const      { return color; }
	bool     operator==(Color c) const { return color == c.color; }
	bool     operator==(const RGBA& c) const { return c == operator RGBA(); }
	bool     operator!=(Color c) const { return color != c.color; }

	void     Serialize(Stream& s)      { s % color; }
	void     Jsonize(JsonIO& jio);
	void     Xmlize(XmlIO& xio);

	Color()                            { SetNull(); }
	Color(int r, int g, int b)         { color = RGB(r, g, b); }

	Color(const Nuller&)               { SetNull(); }

	operator Value() const             { return Value(*this); }
	Color(const Value& q)              { color = q.Get<Color>().color; }

	operator RGBA() const;
	Color(RGBA rgba);

	Color(Color (*fn)())               { color = (*fn)().color; }

	static Color FromRaw(dword co)     { Color c; c.color = co; return c; }
	static Color Special(int n)        { Color c; c.color = 0x80000000 | n; return c; }
	
	int  GetSpecial() const            { return color & 0x80000000 ? color & 0x7fffffff : -1; }

#ifdef PLATFORM_WIN32
	operator COLORREF() const          { return (COLORREF) Get(); }
	static  Color FromCR(COLORREF cr)  { Color c; c.color = (dword)cr; return c; }
#else
	operator dword() const             { return Get(); }
#endif

private:
	Color(int);
};

#if 0
template <class T>
class ColorT : Moveable<ColorT<T>> {
	T r, g, b;
public:
	
	ColorT() {}
	ColorT(const ColorT& c) {*this = c;}
	ColorT(T r, T g, T b) : r(r), g(g), b(b) {}
	ColorT(const Nuller&) : r(0), g(0), b(0) {}
	ColorT(const RGBA& c) : r(c.r), g(c.g), b(c.b) {}
	ColorT(ColorT(*fn)()) {if (fn) *this = fn();}
	template <class K> ColorT(const ColorT<K>& c) {*this = c;}
	
	bool IsEqual(const ColorT& c) {return r == c.r && g == c.g && b == c.b;}
	bool IsNullInstance() const {return r == 0 && g == 0 && b == 0;}
	
	void operator=(const ColorT& c) {
		r = c.r;
		g = c.g;
		b = c.b;
	}
	
	T GetR() const {return r;}
	T GetG() const {return g;}
	T GetB() const {return b;}
	
	template <class K>
	void operator=(const ColorT<K>& c) {
		r = (T)c.r;
		g = (T)c.g;
		b = (T)c.b;
	}
	
	bool operator==(const ColorT& c) {return IsEqual(c);}
	bool operator!=(const ColorT& c) {return !IsEqual(c);}
	
	operator RGBA() const {RGBA c; c.r = r; c.g = g; c.b = b; c.a = 255; return c;}
	
	void Mul(double d) {r *= d; g *= d; b *= d;}
	void Div(double d) {r /= d; g /= d; b /= d;}
	void ToRange1() {Div(255.0);}
	void FromRange1() {Mul(255.0);}
	
	hash_t GetHashValue() const {CombineHash c; c.Put(r); c.Put(g); c.Put(b); return c;}
	
};

using Color		= ColorT<byte>;
using Colorf32	= ColorT<float>;
using Colorf	= ColorT<double>;
#endif

enum {
	SPCLR_DEFAULT_INK = 254,
};

Color SpecialColor(int code);

inline Color GrayColor(byte gray = 128) {return Color(gray, gray, gray);}

inline Color Blend(Color a_, Color b_, double blend=0.5) {
	RGBA a = a_;
	RGBA b = b_;
	RGBA out;
	out.r = (byte)((a.r * (1.0 - blend)) + (b.r * blend));
	out.g = (byte)((a.g * (1.0 - blend)) + (b.g * blend));
	out.b = (byte)((a.b * (1.0 - blend)) + (b.b * blend));
	out.a = 0;
	return out;
}


typedef Color(*ColorF)();

inline Color Black()     { return Color(0, 0, 0); }
inline Color Gray()      { return Color(128, 128, 128); }
inline Color LtGray()    { return Color(192, 192, 192); }
inline Color WhiteGray() { return Color(224, 224, 224); }
inline Color White()     { return Color(255, 255, 255); }

inline Color Red()       { return Color(128, 0, 0); }
inline Color Green()     { return Color(0, 128, 0); }
inline Color Brown()     { return Color(128, 128, 0); }
inline Color Blue()      { return Color(0, 0, 128); }
inline Color Magenta()   { return Color(128, 0, 255); }
inline Color Cyan()      { return Color(0, 128, 128); }
inline Color Yellow()    { return Color(255, 255, 0); }
inline Color LtRed()     { return Color(255, 0, 0); }
inline Color LtGreen()   { return Color(0, 255, 0); }
inline Color LtYellow()  { return Color(255, 255, 192); }
inline Color LtBlue()    { return Color(0, 0, 255); }
inline Color LtMagenta() { return Color(255, 0, 255); }
inline Color LtCyan()    { return Color(0, 255, 255); }


int  Grayscale(const Color& c);
bool IsDark(Color c);
bool IsLight(Color c);










template <class T>
struct HSL_ : Moveable<HSL_<T>> {
	T hue, saturation, lightness;
	
	template <class K>
	void operator=(const K& o) {
		hue = o.hue;
		saturation = o.saturation;
		lightness = o.lightness;
	}
	void Reset() {hue = 0; saturation = 0; lightness = 0;}
};

typedef HSL_<byte> HSL;
typedef HSL_<double> HSLf;



inline int GetBrightness(Size sz, const RGBA* begin, int x, int y, int default_value) {
	if (x < 0 || y < 0 || x >= sz.cx || y >= sz.cy)
		return default_value;
	
	const RGBA* it = begin + y * sz.cx + x;
	int brightness = (it->r + it->g + it->b) / 3;
	return brightness;
}

inline int GetBrightness(const RGBA& i) {
	return (i.r + i.g + i.b) / 3;
}


inline double GetBrightnessf(const RGBA& i) {
	static constexpr double mul = 1.0 / 255.0 / 3.0;
	return (i.r + i.g + i.b) * mul;
}


Color DarkTheme(Color color);
Color DarkThemeCached(Color c);


Color Rainbow(float progress);
Color Heatmap(float progress);
Color HeatmapBlue(float progress);
Color HeatmapBlack(float progress);

NAMESPACE_UPP_END

#endif
