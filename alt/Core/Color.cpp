#include "Core.h"

NAMESPACE_UPP_BEGIN

bool operator==(const RGBA& a, const RGBA& b) {return MemoryCompare(&a, &b, sizeof(RGBA)) == 0;}
bool operator==(const RGBAf& a, const RGBAf& b) {return MemoryCompare(&a, &b, sizeof(RGBAf)) == 0;}


Color DarkTheme(Color color)
{
	if(IsNull(color))
		return Null;
	
	double v[3];
	v[0] = color.GetR();
	v[1] = color.GetG();
	v[2] = color.GetB();

// this represent physiological perception of brightness of R,G,B. Sum = 1
//	static double c[3] = { 0.21, 0.72, 0.07 }; // physiologically correct values
	static double c[3] = { 0.3, 0.5, 0.2 }; // with this set, blues and reds are more pronounced

	double m0 = c[0] * v[0] + c[1] * v[1] + c[2] * v[2]; // base brightness
	
	const int middle = 155; // this value represents gamma-like feature, imbalance of perception of dark vs bright
	const double up = (256.0 - middle) / middle;
	const double down = 1 / up;

	double m;
	if(m0 < middle)
		m = middle + (middle - m0) * up;
	else
		m = middle - (m0 - middle) * down;
	
	int i0 = 0;
	int i1 = 1;
	int i2 = 2;
	
	if(v[i0] > v[i1])
		Swap(i0, i1);
	if(v[i1] > v[i2])
		Swap(i1, i2);
	if(v[i0] > v[i1])
		Swap(i0, i1);

	if(m0 < m) {
		m -= m0;
		double a = min(v[i2] + m, 255.0) - v[i2];
		v[i0] += a;
		v[i1] += a;
		v[i2] += a;
		m -= a;

		a = min(v[i1] + m / (c[i0] + c[i1]), 255.0) - v[i1];
		v[i0] += a;
		v[i1] += a;
		m -= (c[i0] + c[i1]) * a;

		v[i0] = min(v[i0] + m / c[i1], 255.0);
	}
	else {
		m = m0 - m;
		double a = v[i0] - max(v[i0] - m, 0.0);
		v[i0] -= a;
		v[i1] -= a;
		v[i2] -= a;
		m -= a;

		a = v[i1] - max(v[i1] - m / (c[i1] + c[i2]), 0.0);
		v[i1] -= a;
		v[i2] -= a;
		m -= (c[i1] + c[i2]) * a;

		v[i2] = max(v[i2] - m / c[i2], 0.0);
	}
	
	return Color((int)v[0], (int)v[1], (int)v[2]);
}

Color DarkThemeCached(Color c)
{
	const int N = 8;
	thread_local struct Cache {
		Color icolor[N];
		Color ocolor[N];
		int   ii = 0;
		
		Cache() {
			for(int i = 0; i < N; i++) {
				icolor[i] = Color(0, 0, 0);
				ocolor[i] = Color(255, 255, 255);
			}
		}
	} cache;
	#define DO(i) if(cache.icolor[i] == c) return cache.ocolor[i];
	DO(0); DO(1); DO(2); DO(3); DO(4); DO(5); DO(6); DO(7);
	cache.ii = (cache.ii + 1) & (N - 1);
	cache.icolor[cache.ii] = c;
	c = DarkTheme(c);
	cache.ocolor[cache.ii] = c;
	return c;
}

Color::Color(RGBA rgba)
{
	if(rgba.a == 0)
		color = 0xffffffff;
	else {
		if(rgba.a == 255)
			color = RGB(rgba.r, rgba.g, rgba.b);
		else {
			int alpha = 65536 / rgba.a;
			color = RGB((alpha * rgba.r) >> 8, (alpha * rgba.g) >> 8, (alpha * rgba.b) >> 8);
		}
	}
}

Color::operator RGBA() const
{
	RGBA color;
	if(IsNullInstance())
		Zero(color);
	else {
		color.r = GetR();
		color.g = GetG();
		color.b = GetB();
		color.a = 255;
	}
	return color;
}

dword Color::Get() const
{
	if(IsNullInstance()) return 0;
	dword c = color;
	return c & 0xffffff;
}

int  Grayscale(const Color& c)
{
	return (77 * c.GetR() + 151 * c.GetG() + 28 * c.GetB()) >> 8;
}

bool IsDark(Color c)
{
	return Grayscale(c) < 80;
}

bool IsLight(Color c)
{
	return Grayscale(c) > 255 - 80;
}

NAMESPACE_UPP_END
