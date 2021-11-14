#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN

const int fast_corners::offsets16[] = {0, 3, 1, 3, 2, 2, 3, 1, 3, 0, 3, -1, 2, -2, 1, -3, 0, -3, -1, -3, -2, -2, -3, -1, -3, 0, -3, 1, -2, 2, -1, 3};


fast_corners::fast_corners() {
	threshold_tab.SetCount(512);
	pixel_off.SetCount(25);
	score_diff.SetCount(25);
}

void fast_corners::_cmp_offsets(PixVec& pixel, int step, int pattern_size) {
	const int* offsets = offsets16;
	for (int k = 0; k < pattern_size; ++k) {
		int j = k << 1;
		ASSERT(j >= 0 && j < sizeof(offsets16) / sizeof(int));
		pixel[k] = offsets[j] + offsets[j+1] * step;
	}
	for (int k = 0; k < 25; ++k) {
		pixel[k] = pixel[k - pattern_size];
	}
}

int fast_corners::_cmp_score_16(const Vector<byte>& src, int off, const PixVec& pixel, Vector<int>& d, int threshold) {
	int N = 25;
	int v = src[off];
	
	for (int k = 0; k < N; ++k) {
		d[k] = v - (int)src[off+pixel[k]];
	}
	
	int a0 = threshold;
	for (int k = 0; k < 16; k += 2) {
		int a;
		a = min(d[k+1], d[k+2]);
		a = min(a, d[k+3]);
		
		if (a <= a0)
			continue;
			
		a = min(a, d[k+4]);
		a = min(a, d[k+5]);
		a = min(a, d[k+6]);
		a = min(a, d[k+7]);
		a = min(a, d[k+8]);
		a0 = max(a0, min(a, d[k]));
		a0 = max(a0, min(a, d[k+9]));
	}
	
	int b0 = -a0;
	for (int k = 0; k < 16; k += 2) {
		int b;
		b = max(d[k+1], d[k+2]);
		b = max(b, d[k+3]);
		b = max(b, d[k+4]);
		b = max(b, d[k+5]);
		
		if (b >= b0)
			continue;
		b = max(b, d[k+6]);
		b = max(b, d[k+7]);
		b = max(b, d[k+8]);
		b0 = min(b0, max(b, d[k]));
		b0 = min(b0, max(b, d[k+9]));
	}
	
	return -b0 - 1;
}


int fast_corners::set_threshold(int threshold) {
	int _threshold = min(max(threshold, 0), 255);
	for (int i = -255; i <= 255; ++i) {
		threshold_tab[(i + 255)] = (i < -_threshold ? 1 : (i > _threshold ? 2 : 0));
	}
	return _threshold;
}

int fast_corners::detect(const ByteMat& src, Vector<keypoint_t>& corners, int border) {
	int K = 8, N = 25;
	const auto& img = src.data;
	int w = src.cols;
	int h = src.rows;
	
	static thread_local Vector<byte> buf;
	static thread_local Vector<int> cpbuf;
	buf.SetCount(3 * w);
	cpbuf.SetCount(((w + 1) * 3) << 2);
	
	PixVec& pixel = pixel_off;
	Vector<int>& sd = score_diff;
	int sy = max(3, border);
	int ey = min((h - 2), (h - border));
	int sx = max(3, border);
	int ex = min((w - 3), (w - border));
	int _count = 0;
	int corners_cnt = 0;
	int (*score_func)(const Vector<byte>&, int, const PixVec&, Vector<int>&, int)
		= _cmp_score_16;
	Vector<byte>& thresh_tab = threshold_tab;
	int threshold = _threshold;
	
	_cmp_offsets(pixel, w, 16);
	
	// local vars are faster?
	int pixel0 = pixel[0];
	int pixel1 = pixel[1];
	int pixel2 = pixel[2];
	int pixel3 = pixel[3];
	int pixel4 = pixel[4];
	int pixel5 = pixel[5];
	int pixel6 = pixel[6];
	int pixel7 = pixel[7];
	int pixel8 = pixel[8];
	int pixel9 = pixel[9];
	int pixel10 = pixel[10];
	int pixel11 = pixel[11];
	int pixel12 = pixel[12];
	int pixel13 = pixel[13];
	int pixel14 = pixel[14];
	int pixel15 = pixel[15];
	
	for (int i = 0; i < w*3; ++i) {
		buf[i] = 0;
	}
	
	for (int i = sy; i < ey; ++i) {
		int ptr = ((i * w) + sx);
		int m3 = (i - 3) % 3;
		int curr = (m3 * w);
		int cornerpos = (m3 * (w + 1));
		
		for (int j = 0; j < w; ++j)
			buf[curr+j] = 0;
		int ncorners = 0;
		
		if (i < (ey - 1)) {
			for (int j = sx; j < ex; ++j, ++ptr) {
				auto v = img[ptr];
				int tab = (-v + 255);
				byte d = (thresh_tab[tab+img[ptr+pixel0]] | thresh_tab[tab+img[ptr+pixel8]]);
				
				if (d == 0) {
					continue;
				}
				
				d &= (thresh_tab[tab+img[ptr+pixel2]] | thresh_tab[tab+img[ptr+pixel10]]);
				d &= (thresh_tab[tab+img[ptr+pixel4]] | thresh_tab[tab+img[ptr+pixel12]]);
				d &= (thresh_tab[tab+img[ptr+pixel6]] | thresh_tab[tab+img[ptr+pixel14]]);
				
				if (d == 0) {
					continue;
				}
				
				d &= (thresh_tab[tab+img[ptr+pixel1]] | thresh_tab[tab+img[ptr+pixel9]]);
				d &= (thresh_tab[tab+img[ptr+pixel3]] | thresh_tab[tab+img[ptr+pixel11]]);
				d &= (thresh_tab[tab+img[ptr+pixel5]] | thresh_tab[tab+img[ptr+pixel13]]);
				d &= (thresh_tab[tab+img[ptr+pixel7]] | thresh_tab[tab+img[ptr+pixel15]]);
				
				if (d & 1) {
					int vt = (v - threshold);
					_count = 0;
					
					for (int k = 0; k < N; ++k) {
						int x = img[(ptr+pixel[k])];
						if (x < vt) {
							++_count;
							if (_count > K) {
								++ncorners;
								cpbuf[cornerpos+ncorners] = j;
								buf[curr+j] = score_func(img, ptr, pixel, sd, threshold);
								break;
							}
						}
						else {
							_count = 0;
						}
					}
				}
				
				if (d & 2) {
					int vt = (v + threshold);
					_count = 0;
					
					for (int k = 0; k < N; ++k) {
						int x = img[(ptr+pixel[k])];
						if (x > vt) {
							++_count;
							if (_count > K) {
								++ncorners;
								cpbuf[cornerpos+ncorners] = j;
								buf[curr+j] = score_func(img, ptr, pixel, sd, threshold);
								break;
							}
						}
						else {
							_count = 0;
						}
					}
				}
			}
		}
		
		cpbuf[cornerpos+w] = ncorners;
		
		if (i == sy) {
			continue;
		}
		
		m3 = (i - 4 + 3) % 3;
		int prev = (m3 * w);
		cornerpos = (m3 * (w + 1));
		m3 = (i - 5 + 3) % 3;
		int pprev = (m3 * w);
		
		ncorners = cpbuf[cornerpos+w];
		
		for (int k = 0; k < ncorners; ++k) {
			int j = cpbuf[cornerpos+k];
			int jp1 = (j + 1);
			int jm1 = (j - 1);
			auto score = buf[prev+j];
			if ((score > buf[prev+jp1] && score > buf[prev+jm1] &&
				 score > buf[pprev+jm1] && score > buf[pprev+j] && score > buf[pprev+jp1] &&
				 score > buf[curr+jm1] && score > buf[curr+j] && score > buf[curr+jp1])) {
				// save corner
				keypoint_t& pt = corners[corners_cnt];
				pt.x = j;
				pt.y = (i - 1);
				pt.score = score;
				corners_cnt++;
			}
		}
	} // y loop
	
	return corners_cnt;
}



NAMESPACE_TOPSIDE_END

