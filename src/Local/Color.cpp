#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

void FindColors(RgbaRange i, RGBA& fg, RGBA& bg) {
	Size sz(i.GetSize());
	int64 r_sum = 0, g_sum = 0, b_sum = 0, edge_count = 0;
	const RGBA* begin = i.Begin();
	const RGBA* end = i.End();
	const RGBA *it0, *it1;
	it0 = begin;
	it1 = begin + (sz.cy - 1) * sz.cx;
	for(int x = 0; x < sz.cx; x++) {
		r_sum += (int64)it0->r;
		r_sum += (int64)it1->r;
		g_sum += (int64)it0->g;
		g_sum += (int64)it1->g;
		b_sum += (int64)it0->b;
		b_sum += (int64)it1->b;
		edge_count += 2;
		it0++;
		it1++;
	}
	int64 r = r_sum / edge_count;
	int64 g = g_sum / edge_count;
	int64 b = b_sum / edge_count;
	it0 = begin + sz.cx;
	it1 = begin + (sz.cx - 1) + sz.cx;
	for(int y = 1; y < sz.cy-1; y++) {
		r_sum += (int64)it0->r;
		r_sum += (int64)it1->r;
		g_sum += (int64)it0->g;
		g_sum += (int64)it1->g;
		b_sum += (int64)it0->b;
		b_sum += (int64)it1->b;
		edge_count += 2;
		it0 += sz.cx;
		it1 += sz.cx;
	}
	bg.r = (byte)(r_sum / edge_count);
	bg.g = (byte)(g_sum / edge_count);
	bg.b = (byte)(b_sum / edge_count);
	bg.a = 255;
	
	double opp_r_sum = 0, opp_g_sum = 0, opp_b_sum = 0, opp_sum = 0;
	const RGBA *it = begin;
	while (it != end) {
		double r_diff = (double)it->r - (double)r;
		double g_diff = (double)it->g - (double)g;
		double b_diff = (double)it->b - (double)b;
		double dist = sqrt(r_diff * r_diff + g_diff * g_diff + b_diff * b_diff);
		opp_r_sum += it->r * dist;
		opp_g_sum += it->g * dist;
		opp_b_sum += it->b * dist;
		opp_sum += dist;
		it++;
	}
	fg.r = (byte)(opp_r_sum / opp_sum);
	fg.g = (byte)(opp_g_sum / opp_sum);
	fg.b = (byte)(opp_b_sum / opp_sum);
	fg.a = 255;
}


Point FindWeightCenter(RgbaRange i, RGBA fg, RGBA bg) {
	Size sz(i.GetSize());
	int64 edge_sum = 0, edge_count = 0;
	const RGBA* begin = i.Begin();
	int64 x_sum = 0, y_sum = 0, weight_sum = 0;
	if (fg == bg)
		return Point(sz.cx/2, sz.cy/2);
	const RGBA *it = begin;
	for(int y = 0; y < sz.cy; y++) {
		for(int x = 0; x < sz.cx; x++) {
			int64 fg_dist = Dist(fg, *it);
			int64 bg_dist = Dist(bg, *it);
			int64 total = fg_dist + bg_dist;
			int64 weight = bg_dist * 1000 / total;
			x_sum += x * weight;
			y_sum += y * weight;
			weight_sum += weight;
			it++;
		}
	}
	if (!weight_sum)
		return Point(sz.cx/2, sz.cy/2);
	Point pt(
		(byte)(x_sum / weight_sum),
		(byte)(y_sum / weight_sum));
	return pt;
}

int64 DifferenceSum(RgbaRange i0, Point a0, RgbaRange i1, Point a1, RGBA fg, RGBA bg) {
	int64 res = 0, count = 0;
	Size sz0(i0.GetSize());
	Size sz1(i1.GetSize());
	const RGBA* begin0 = i0.Begin();
	const RGBA* begin1 = i1.Begin();
	int left = min(a0.x, a1.x);
	int top = min(a0.y, a1.y);
	ASSERT(a0.y - top >= 0 && a1.y - top >= 0);
	ASSERT(a0.x - left >= 0 && a1.x - left >= 0);
	for(int y0 = a0.y - top, y1 = a1.y - top; y0 < sz0.cy && y1 < sz1.cy; y0++, y1++) {
		const RGBA* it0 = begin0 + y0 * sz0.cx + (a0.x - left);
		const RGBA* it1 = begin1 + y1 * sz1.cx + (a1.x - left);
		for(int x0 = a0.x - left, x1 = a1.x - left; x0 < sz0.cx && x1 < sz1.cx; x0++, x1++) {
			int brightness0 = (int)it0->r + (int)it0->g + (int)it0->b;
			int brightness1 = (int)it1->r + (int)it1->g + (int)it1->b;
			int diff = abs(brightness0 - brightness1);
			res += (int64)diff;
			it0++;
			it1++;
			count++;
		}
	}
	if (count < 16)
		return INT64_MAX;
	
	int64 av = res * 10000LL / count;
	return av;
}


RGBA BlendRGBA(RGBA a, RGBA b, double blend) {
	double amul = blend;
	double bmul = 1.0 - blend;
	RGBA out;
	out.r = (byte)(a.r * amul + b.r * bmul);
	out.g = (byte)(a.g * amul + b.g * bmul);
	out.b = (byte)(a.b * amul + b.b * bmul);
	out.a = (byte)(a.a * amul + b.a * bmul);
	return out;
}

Color CoolBlue(double progress) {
	double alpha = progress - (int)progress;
	Color a = Color(28, 170, 255);
	Color b = Color(28, 42, 200);
	return Blend(a, b, (int)(alpha * 0x100));
}

Color Rainbow(double progress) {
    double div = (fabs(progress - (int)progress) * 6);
    int ascending = (int) ((div - (int)div) * 255);
    int descending = 255 - ascending;

    switch ((int) div)
    {
        case 0:
            return Color(255, ascending, 0);
        case 1:
            return Color(descending, 255, 0);
        case 2:
            return Color(0, 255, ascending);
        case 3:
            return Color(0, descending, 255);
        case 4:
            return Color(ascending, 0, 255);
        default: // case 5:
            return Color(255, 0, descending);
    }
}

double Interpolate(double x, double x0, double y0, double x1, double y1) {
    return (x-x0) * (y1-y0) / (x1-x0) + y0;
}

double JetPaletteBase(double val) {
    if ( val <= -0.75 ) return 0;
    else if ( val <= -0.25 ) return Interpolate( val, -0.75, 0.0, -0.25, 1.0);
    else if ( val <= 0.25 ) return 1.0;
    else if ( val <= 0.75 ) return Interpolate( val, 0.25, 1.0, 0.75, 0.0);
    else return 0.0;
}

double JetPaletteRed(double gray) {
    return JetPaletteBase(gray - 0.5);
}

double JetPaletteGreen(double gray) {
    return JetPaletteBase(gray);
}

double JetPaletteBlue(double gray) {
    return JetPaletteBase(gray + 0.5);
}

Color JetPalette(double gray) {
	return Color(
		(byte)JetPaletteRed(gray),
		(byte)JetPaletteGreen(gray),
		(byte)JetPaletteBlue(gray));
}

























Color Rainbow(float progress) {
    float div = (fabs(progress - (int)progress) * 6);
    int ascending = (int) ((div - (int)div) * 255);
    int descending = 255 - ascending;

    switch ((int) div)
    {
        case 0:
            return Color(255, ascending, 0);
        case 1:
            return Color(descending, 255, 0);
        case 2:
            return Color(0, 255, ascending);
        case 3:
            return Color(0, descending, 255);
        case 4:
            return Color(ascending, 0, 255);
        default: // case 5:
            return Color(255, 0, descending);
    }
}

Color Heatmap(float progress) {
    float div = (fabs(progress - (int)progress) * 6);
    int ascending = (int) ((div - (int)div) * 255);
    int descending = 255 - ascending;

    switch ((int) div)
    {
        case 0:
            return Color(0, 0, ascending);
        case 1:
            return Color(0, ascending, 255);
        case 2:
            return Color(0, 255, descending);
        case 3:
            return Color(ascending, 255, 0);
        case 4:
            return Color(255, descending, 0);
        default:
            return Color(255, ascending, ascending);
    }
}

Color HeatmapBlue(float progress) {
    float div = (fabs(progress - (int)progress) * 6);
    int ascending = (int) ((div - (int)div) * 255);
    int descending = 255 - ascending;

    switch ((int) div)
    {
        case 0:
            return Color(ascending, 0, 0);
        case 1:
            return Color(255, 0, ascending);
        case 2:
            return Color(descending, 0, 255);
        case 3:
            return Color(0, ascending, 255);
        case 4:
            return Color(0, 255, descending);
        default:
            return Color(ascending, 255, ascending);
    }
}

Color HeatmapBlack(float progress) {
    float div = (fabs(progress - (int)progress) * 4);
    int ascending = (int) ((div - (int)div) * 255);
    int descending = 255 - ascending;

    switch ((int) div)
    {
        case 0:
            return Color(255, descending, 0);
        case 1:
            return Color(descending, 0, 0);
        case 2:
            return Color(0, 0, ascending);
        default:
            return Color(0, ascending, 255);
    }
}

RGBA InvertRGBA(const RGBA& c) {
	RGBA a;
	a.r = ~c.r;
	a.g = ~c.g;
	a.b = ~c.b;
	a.a = 255;
	return a;
}

RGBA TransformHue(const RGBA& in, float angle) {
	double U = cos(angle * M_PI / 180);
	double W = sin(angle * M_PI / 180);
	
	RGBA ret;
	double r =  (.299 + .701 * U + .168 * W) * in.r
			  + (.587 - .587 * U + .330 * W) * in.g
			  + (.114 - .114 * U - .497 * W) * in.b;
	double g =  (.299 - .299 * U - .328 * W) * in.r
			  + (.587 + .413 * U + .035 * W) * in.g
			  + (.114 - .114 * U + .292 * W) * in.b;
	double b =  (.299 - .3   * U + 1.25 * W) * in.r
			  + (.587 - .588 * U - 1.05 * W) * in.g
			  + (.114 + .886 * U - .203 * W) * in.b;
	ret.r = min(255, max(0, (int)r));
	ret.g = min(255, max(0, (int)g));
	ret.b = min(255, max(0, (int)b));
	ret.a = in.a;
	return ret;
}


RGBA InvertRGBA_InvertHue(const RGBA& c) {
	RGBA a;
	//if (c.r == 255 && c.g == 255 && c.r == 255) {a = Black(); a.a = c.a; return a;}
	//if (c.r ==   0 && c.g ==   0 && c.r ==   0) {a = White(); a.a = c.a; return a;}
	a.r = ~c.r;
	a.g = ~c.g;
	a.b = ~c.b;
	a.a = 255;
	return TransformHue(a, 180);
}

RGBA InvertRGBA_GrayOnly(const RGBA& c, int gray_range) {
	int av = ((int)c.r + (int)c.g + (int)c.b) / 3;
	int r = av - (int)c.r;
	int g = av - (int)c.g;
	int b = av - (int)c.b;
	int dist_sum = abs(r) + abs(g) + abs(b);
	if (dist_sum < 3*gray_range) {
		RGBA a;
		#if 0
		a.r = ~c.r;
		a.g = ~c.g;
		a.b = ~c.b;
		#else
		av = 255 - av;
		a.r = min(255, max(0, av + r));
		a.g = min(255, max(0, av + g));
		a.b = min(255, max(0, av + b));
		#endif
		a.a = c.a;
		return a;
	}
	else
		return c;
}

RGBA RGBAC(byte r, byte g, byte b, byte a) {
	RGBA o;
	o.r = r;
	o.g = g;
	o.b = b;
	o.a = a;
	return o;
}


NAMESPACE_TOPSIDE_END
