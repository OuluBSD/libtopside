#include "Core.h"

NAMESPACE_UPP_BEGIN


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


NAMESPACE_UPP_END
