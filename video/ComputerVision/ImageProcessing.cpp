#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN


#if 0

// TODO: add support for RGB/BGR order
// for raw arrays
void Grayscale(const VideoInputFrame& src, int w, int h, VideoOutputFrame& dst, int code) {
	TODO
	#if 0
	//var x = 0, y = 0, i = 0, j = 0, ir = 0, jr = 0;
	int coeff_r = 4899, coeff_g = 9617, coeff_b = 1868, cn = 4;
	
	if (code == COLOR_BGRA2GRAY || code == COLOR_BGR2GRAY) {
		coeff_r = 1868;
		coeff_b = 4899;
	}
	if (code == COLOR_RGB2GRAY || code == COLOR_BGR2GRAY) {
		cn = 3;
	}
	int cn2 = cn << 1;
	int cn3 = cn * 3;
	
	dst.Resize(w, h, 1);
	var dst_u8 = dst.data;
	
	for (int y = 0, i = 0; y < h; ++y, j += w, i += w * cn) {
		int x = 0, ir = i, jr = j;
		for (; x <= w - 4; x += 4, ir += cn << 2, jr += 4) {
			dst_u8[jr]     = (src[ir] * coeff_r + src[ir+1] * coeff_g + src[ir+2] * coeff_b + 8192) >> 14;
			dst_u8[jr + 1] = (src[ir+cn] * coeff_r + src[ir+cn+1] * coeff_g + src[ir+cn+2] * coeff_b + 8192) >> 14;
			dst_u8[jr + 2] = (src[ir+cn2] * coeff_r + src[ir+cn2+1] * coeff_g + src[ir+cn2+2] * coeff_b + 8192) >> 14;
			dst_u8[jr + 3] = (src[ir+cn3] * coeff_r + src[ir+cn3+1] * coeff_g + src[ir+cn3+2] * coeff_b + 8192) >> 14;
		}
		for (; x < w; ++x, ++jr, ir += cn) {
			dst_u8[jr] = (src[ir] * coeff_r + src[ir+1] * coeff_g + src[ir+2] * coeff_b + 8192) >> 14;
		}
	}
	#endif
}
#endif


NAMESPACE_TOPSIDE_END
