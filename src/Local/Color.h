#ifndef _Local_Color_h_
#define _Local_Color_h_


NAMESPACE_TOPSIDE_BEGIN


struct RgbaRange : Moveable<RgbaRange> {
	RGBA* begin_ptr = NULL;
	RGBA* end_ptr = NULL;
	Size sz;
	
	
	RGBA* Begin() const {return begin_ptr;}
	RGBA* begin() const {return begin_ptr;}
	RGBA* End() const {return end_ptr;}
	RGBA* end() const {return end_ptr;}
	Size GetSize() const {return sz;}
};

inline int Dist(int a, int b) {return abs(a - b);}
inline int Dist(RGBA a, RGBA b) {return Dist(a.r, b.r) + Dist(a.g, b.g) + Dist(a.b, b.b);}


inline Color RandomColor(int begin=0, int range=256) { return Color(begin + Random(range), begin + Random(range) , begin + Random(range)); }

void FindColors(RgbaRange i, RGBA& fg, RGBA& bg);
Point FindWeightCenter(RgbaRange i, RGBA fg, RGBA bg);
int64 DifferenceSum(RgbaRange i0, Point a0, RgbaRange i1, Point a1, RGBA fg, RGBA bg);
RGBA BlendRGBA(RGBA a, RGBA b, double blend);

Color Rainbow(double progress);
Color CoolBlue(double progress);
//double GetKeypointFactor(const TesterProgram& prog, const FontTester& fnt, Image i, int x, int y);
double Interpolate(double x, double x0, double y0, double x1, double y1);
double JetPaletteBase( double val );
double JetPaletteRed( double gray );
double JetPaletteGreen( double gray );
double JetPaletteBlue( double gray );
Color JetPalette(double gray);

inline byte AtRGBA(RGBA rgba, int i) {
	ASSERT(i >= 0 && i < 4);
	switch (i) {
		case 0: return rgba.r;
		case 1: return rgba.g;
		case 2: return rgba.b;
		case 3: return rgba.a;
	}
	return 0;
}

RGBA RGBAC(byte r, byte g, byte b, byte a);
RGBA TransformHue(const RGBA& in, float angle);
RGBA InvertRGBA(const RGBA& c);
RGBA InvertRGBA_InvertHue(const RGBA& c);
RGBA InvertRGBA_GrayOnly(const RGBA& c, int gray_range=5);



NAMESPACE_TOPSIDE_END


#endif
