#ifndef _ComputerVision_FAST_h_
#define _ComputerVision_FAST_h_


NAMESPACE_TOPSIDE_BEGIN

class fast_corners {
	typedef Vector<int> PixVec;
	
	Vector<uint8> threshold_tab;
	PixVec pixel_off;
	Vector<int> score_diff;
	int _threshold = 20;
	
public:
	static const int offsets16[];
	
	
	
	fast_corners() {
		threshold_tab.SetCount(512);
		pixel_off.SetCount(25);
		score_diff.SetCount(25);
	}
	
	
private:
	void _cmp_offsets(const PixVec& pixel, int step, pattern_size) {
		var offsets = offsets16;
		for (int k = 0; k < pattern_size; ++k) {
			pixel[k] = offsets[k<<1] + offsets[(k<<1)+1] * step;
		}
		for (int k = 0; k < 25; ++k) {
			pixel[k] = pixel[k - pattern_size];
		}
	}
	
	void _cmp_score_16(src, off, pixel, d, threshold) {
		int N = 25;
		auto v = src[off];
		
		for (int k = 0; k < N; ++k) {
			d[k] = v - src[off+pixel[k]];
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
	
	
	void set_threshold(int threshold) {
		_threshold = min(max(threshold, 0), 255);
		for (int i = -255; i <= 255; ++i) {
			threshold_tab[(i + 255)] = (i < -_threshold ? 1 : (i > _threshold ? 2 : 0));
		}
		return _threshold;
	}
	
	int detect(src, corners, int border = 3) {
		int K = 8, N = 25;
		const auto& img = src.data;
		int w = src.cols;
		int h = src.rows;
		var buf_node = cache.get_buffer(3 * w); // static
		var cpbuf_node = cache.get_buffer(((w + 1) * 3) << 2);
		var buf = buf_node.u8;
		var cpbuf = cpbuf_node.i32;
		var pixel = pixel_off;
		var sd = score_diff;
		int sy = max(3, border);
		int ey = min((h - 2), (h - border));
		int sx = max(3, border);
		int ex = min((w - 3), (w - border));
		int _count = 0, corners_cnt = 0, pt;
		var score_func = _cmp_score_16;
		var thresh_tab = threshold_tab;
		var threshold = _threshold;
		
		var v = 0, tab = 0, d = 0, ncorners = 0, cornerpos = 0, curr = 0, ptr = 0, prev = 0, pprev = 0;
		var jp1 = 0, jm1 = 0, score = 0;
		
		_cmp_offsets(pixel, w, 16);
		
		// local vars are faster?
		var pixel0 = pixel[0];
		var pixel1 = pixel[1];
		var pixel2 = pixel[2];
		var pixel3 = pixel[3];
		var pixel4 = pixel[4];
		var pixel5 = pixel[5];
		var pixel6 = pixel[6];
		var pixel7 = pixel[7];
		var pixel8 = pixel[8];
		var pixel9 = pixel[9];
		var pixel10 = pixel[10];
		var pixel11 = pixel[11];
		var pixel12 = pixel[12];
		var pixel13 = pixel[13];
		var pixel14 = pixel[14];
		var pixel15 = pixel[15];
		
		for (int i = 0; i < w*3; ++i) {
			buf[i] = 0;
		}
		
		for (int i = sy; i < ey; ++i) {
			ptr = ((i * w) + sx);
			int m3 = (i - 3) % 3;
			curr = (m3 * w);
			cornerpos = (m3 * (w + 1));
			for (int j = 0; j < w; ++j)
				buf[curr+j] = 0;
			ncorners = 0;
			
			if (i < (ey - 1)) {
				for (int j = sx; j < ex; ++j, ++ptr) {
					v = img[ptr];
					tab = (- v + 255);
					d = (thresh_tab[tab+img[ptr+pixel0]] | thresh_tab[tab+img[ptr+pixel8]]);
					
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
			prev = (m3 * w);
			cornerpos = (m3 * (w + 1));
			m3 = (i - 5 + 3) % 3;
			pprev = (m3 * w);
			
			ncorners = cpbuf[cornerpos+w];
			
			for (int k = 0; k < ncorners; ++k) {
				j = cpbuf[cornerpos+k];
				jp1 = (j + 1);
				jm1 = (j - 1);
				score = buf[prev+j];
				if ((score > buf[prev+jp1] && score > buf[prev+jm1] &&
					 score > buf[pprev+jm1] && score > buf[pprev+j] && score > buf[pprev+jp1] &&
					 score > buf[curr+jm1] && score > buf[curr+j] && score > buf[curr+jp1])) {
					// save corner
					pt = corners[corners_cnt];
					pt.x = j, pt.y = (i - 1), pt.score = score;
					corners_cnt++;
				}
			}
		} // y loop
		
		cache.put_buffer(buf_node);
		cache.put_buffer(cpbuf_node);
		return corners_cnt;
	}
	
};


NAMESPACE_TOPSIDE_END

#endif
