#ifndef _Oulu_Color_h_
#define _Oulu_Color_h_


NAMESPACE_OULU_BEGIN

inline Color RandomColor(int begin=0, int range=256) { return Color(begin + Random(range), begin + Random(range) , begin + Random(range)); }

double Interpolate( double val, double y0, double x0, double y1, double x1 );
double JetPaletteBase( double val );
double JetPaletteRed( double gray );
double JetPaletteGreen( double gray );
double JetPaletteBlue( double gray );

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

NAMESPACE_OULU_END


#endif
