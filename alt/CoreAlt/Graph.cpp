#include "Core.h"

NAMESPACE_UPP_BEGIN

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
	int r = r_sum / edge_count;
	int g = g_sum / edge_count;
	int b = b_sum / edge_count;
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
	bg.r = r_sum / edge_count;
	bg.g = g_sum / edge_count;
	bg.b = b_sum / edge_count;
	bg.a = 255;
	
	double opp_r_sum = 0, opp_g_sum = 0, opp_b_sum = 0, opp_sum = 0;
	const RGBA *it = begin;
	while (it != end) {
		double r_diff = (int)it->r - r;
		double g_diff = (int)it->g - g;
		double b_diff = (int)it->b - b;
		double dist = sqrt(r_diff * r_diff + g_diff * g_diff + b_diff * b_diff);
		opp_r_sum += it->r * dist;
		opp_g_sum += it->g * dist;
		opp_b_sum += it->b * dist;
		opp_sum += dist;
		it++;
	}
	fg.r = opp_r_sum / opp_sum;
	fg.g = opp_g_sum / opp_sum;
	fg.b = opp_b_sum / opp_sum;
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
	Point pt(x_sum / weight_sum, y_sum / weight_sum);
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
	out.r = a.r * amul + b.r * bmul;
	out.g = a.g * amul + b.g * bmul;
	out.b = a.b * amul + b.b * bmul;
	out.a = a.a * amul + b.a * bmul;
	return out;
}

#if 0
double GetKeypointFactor(const TesterProgram& prog, const FontTester& fnt, Image i, int x, int y) {
	Size sz(i.GetSize());
	const RGBA* begin = i.Begin();
	const RGBA* it = begin + y * sz.cx + x;
	double factor = 0.0;
	
	int bg_limit = 255/2;
	int brightness = GetBrightness(sz, begin, x, y, 255);
	if (brightness >= bg_limit)
		return 0;
	
	// - check if there is other angles with the same edge value
	// - angles close to 90 degress contributes to increased factor
	for(int i = 0; i < TesterProgram::RING_LIMIT; i++) {
		const Ring& r = prog.circles[i];
		Ring c;
		
		// Convolute edges in the circle
		int max_edge_value = INT_MIN;
		for(int j = 0; j < r.full_circle_size; j++) {
			int j0 = j == 0 ? r.full_circle_size - 1 : j-1;
			int j1 = j;
			int j2 = (j + 1) % r.full_circle_size;
			
			const XY& pos0 = r.full_circle[j0];
			const XY& pos1 = r.full_circle[j1];
			const XY& pos2 = r.full_circle[j2];
			
			int b0 = GetBrightness(sz, begin, x + pos0.x, y + pos0.y, 255);
			int b1 = GetBrightness(sz, begin, x + pos1.x, y + pos1.y, 255);
			int b2 = GetBrightness(sz, begin, x + pos2.x, y + pos2.y, 255);
			
			int edge =
				(+1 * b0) +
				(-2 * b1) +
				(+1 * b2);
			
			c.full_circle[j].x = edge;
			c.full_circle[j].y = b1;
			
			max_edge_value = max(max_edge_value, edge);
		}
		
		if (!max_edge_value)
			continue;
		
		// Find angles of background value
		int edge_limit = max_edge_value/2;
		for(int j = 0; j < r.full_circle_size; j++) {
			int brightness = c.full_circle[j].y;
			if (brightness >= bg_limit) {
				int begin = -1, end = -1;
				int ccw = 0, cw = 0;
				for(; ccw < r.full_circle_size; ccw++) {
					int pos = j - ccw;
					if (pos < 0) pos += r.full_circle_size;
					int edge = c.full_circle[pos].x;
					if (edge >= edge_limit) {
						begin = pos;
						break;
					}
				}
				for(; cw < r.full_circle_size; cw++) {
					int pos = (j + cw) % r.full_circle_size;
					int edge = c.full_circle[pos].x;
					if (edge >= edge_limit) {
						end = pos;
						break;
					}
				}
				if (begin >= 0 && end >= 0) {
					int size = cw + ccw;
					if (size > 0 && size < r.full_circle_size) {
						double degree = 360 * size / r.full_circle_size;
						double dist180 = fabs(degree - 180);
						double dist90 = fabs(dist180 - 90);
						double value = 90 - dist90;
						factor += value;
					}
				}
			}
		}
		
		
	}
	
	return factor;
}
#endif



Color CoolBlue(double progress) {
	double alpha = progress - (int)progress;
	Color a = Color(28, 170, 255);
	Color b = Color(28, 42, 200);
	return Blend(a, b, alpha * 0x100);
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
		JetPaletteRed(gray),
		JetPaletteGreen(gray),
		JetPaletteBlue(gray));
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

NAMESPACE_UPP_END
