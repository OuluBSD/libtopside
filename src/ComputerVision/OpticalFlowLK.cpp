#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN


void OpticalFlowLK::Track(const pyra8& prev_pyr, pyra8& curr_pyr,
	const Vector<float>& prev_xy, Vector<float>& curr_xy, int count,
	int win_size, int max_iter, Vector<uint8>& status,
	double eps, double min_eigen_threshold) {
	if (max_iter <= 0) max_iter = 30;
	
	status.SetCount(count);
	
	double half_win = (win_size - 1) * 0.5;
	int win_area = (win_size * win_size);
	int win_area2 = win_area << 1;
	const auto&  prev_imgs = prev_pyr.data;
	auto& next_imgs = curr_pyr.data;
	const auto&  img_prev = prev_imgs[0].data;
	auto& img_next = next_imgs[0].data;
	int w0 = prev_imgs[0].cols;
	int h0 = prev_imgs[0].rows;
	int lw = 0, lh = 0;
	
	DMatrix<int> deriv_m(w0, h0, 2);
	
	thread_local static Vector<int> iwin_buf;
	thread_local static Vector<int> deriv_iwin;
	auto& deriv_lev = deriv_m.data;
	
	iwin_buf  .SetCount(win_area << 2);
	deriv_iwin.SetCount(win_area << 2);
	memset(iwin_buf.Begin(), 0, iwin_buf.GetCount() * sizeof(int));
	memset(deriv_iwin.Begin(), 0, deriv_iwin.GetCount() * sizeof(int));
	
	int dstep = 0, iptr = 0, diptr = 0, jptr = 0;
	double lev_sc = 0.0, prev_x = 0.0, prev_y = 0.0, next_x = 0.0, next_y = 0.0;
	double prev_delta_x = 0.0, prev_delta_y = 0.0, delta_x = 0.0, delta_y = 0.0;
	double iprev_x = 0, iprev_y = 0, inext_x = 0, inext_y = 0;
	int brd_tl = 0, brd_r = 0, brd_b = 0;
	double a = 0.0, b = 0.0, b1 = 0.0, b2 = 0.0;
	
	// fixed point math
	int W_BITS14 = 14;
	int W_BITS4 = 14;
	int W_BITS1m5 = W_BITS4 - 5;
	int W_BITS1m51 = (1 << ((W_BITS1m5) - 1));
	int W_BITS14_ = (1 << W_BITS14);
	int W_BITS41 = (1 << ((W_BITS4) - 1));
	double FLT_SCALE = 1.0 / (1 << 20);
	double iw00 = 0, iw01 = 0, iw10 = 0, iw11 = 0;
	int ival = 0, ixval = 0, iyval = 0;
	double A11 = 0.0, A12 = 0.0, A22 = 0.0, D = 0.0, min_eig = 0.0;
	
	#ifndef FLT_EPSILON
	double FLT_EPSILON = 0.00000011920929;
	#endif
	
	eps *= eps;
	
	// reset status
	for (auto& v : status)
		v = 1;
	
	int max_level = (prev_pyr.GetLevels() - 1);
	
	for (int level = max_level; level >= 0; --level) {
		lev_sc = (1.0 / (1 << level));
		lw = w0 >> level;
		lh = h0 >> level;
		dstep = lw << 1;
		const auto& img_prev = prev_imgs[level].data;
		const auto& img_next = next_imgs[level].data;
		int prev_len = img_prev.GetCount();
		int next_len = img_next.GetCount();
		
		brd_r = (lw - win_size);
		brd_b = (lh - win_size);
		
		// calculate level derivatives
		ScharrDerivatives(prev_imgs[level], deriv_m);
		int dlen = deriv_lev.GetCount();
		
		// iterate through points
		for (int ptid = 0; ptid < count; ++ptid) {
			int i = ptid << 1;
			int j = i + 1;
			prev_x = prev_xy[i] * lev_sc;
			prev_y = prev_xy[j] * lev_sc;
			
			if (level == max_level) {
				next_x = prev_x;
				next_y = prev_y;
			}
			else {
				next_x = curr_xy[i] * 2.0;
				next_y = curr_xy[j] * 2.0;
			}
			curr_xy[i] = next_x;
			curr_xy[j] = next_y;
			
			prev_x -= half_win;
			prev_y -= half_win;
			iprev_x = prev_x;
			iprev_y = prev_y;
			
			// border check
			bool is_border = (iprev_x <= brd_tl) || (iprev_x >= brd_r) || (iprev_y <= brd_tl) || (iprev_y >= brd_b);
			if (is_border != 0) {
				if (level == 0) {
					status[ptid] = 0;
				}
				continue;
			}
			
			a = prev_x - iprev_x;
			b = prev_y - iprev_y;
			iw00 = (((1.0 - a) * (1.0 - b) * W_BITS14_) + 0.5);
			iw01 = ((a * (1.0 - b) * W_BITS14_) + 0.5);
			iw10 = (((1.0 - a) * b * W_BITS14_) + 0.5);
			iw11 = (W_BITS14_ - iw00 - iw01 - iw10);
			
			A11 = 0.0, A12 = 0.0, A22 = 0.0;
			
			// extract the patch from the first image, compute covariation matrix of derivatives
			for (int y = 0; y < win_size; ++y) {
				int src = (int)((y + iprev_y) * lw + iprev_x);
				int dsrc = src << 1;
				
				int iptr = (y * win_size);
				int diptr = iptr << 1;
				for (int x = 0 ; x < win_size; ++x, ++src, ++iptr, dsrc += 2) {
					int s1 = src+lw;
					int d1 = dsrc+dstep;
					byte v0 = img_prev[src];
					byte v1 = img_prev[src+1];
					byte v00 = s1   < prev_len ? img_prev[s1] : v0;
					byte v01 = s1+1 < prev_len ? img_prev[s1+1] : v00;
					byte l0 = deriv_lev[dsrc];
					byte l1 = deriv_lev[dsrc+1];
					byte l2 = deriv_lev[dsrc+2];
					byte l3 = deriv_lev[dsrc+3];
					byte l00 = d1   < dlen ? deriv_lev[d1] : l0;
					byte l01 = d1+1 < dlen ? deriv_lev[d1+1] : l01;
					byte l02 = d1+2 < dlen ? deriv_lev[d1+2] : l02;
					byte l03 = d1+3 < dlen ? deriv_lev[d1+3] : l03;
					
					ival = (int)((v0) * iw00 + v1 * iw01 + v00 * iw10 + v01 * iw11);
					ival = ((ival + W_BITS1m51) >> (W_BITS1m5));
					ixval = (int)(l0 * iw00 + l2 * iw01 + l00 * iw10 + l02 * iw11);
					ixval = (((ixval) + W_BITS41) >> (W_BITS4));
					iyval = (int)(l1 * iw00 + l3 * iw01 + l01 * iw10 + l03 * iw11);
					iyval = (int)(((iyval) + W_BITS41) >> (W_BITS4));
					
					iwin_buf[iptr] = ival;
					deriv_iwin[diptr++] = ixval;
					deriv_iwin[diptr++] = iyval;
					
					A11 += ixval * ixval;
					A12 += ixval * iyval;
					A22 += iyval * iyval;
				}
			}
			
			A11 *= FLT_SCALE;
			A12 *= FLT_SCALE;
			A22 *= FLT_SCALE;
			
			D = A11 * A22 - A12 * A12;
			min_eig = (A22 + A11 - FastSqrt((A11 - A22) * (A11 - A22) + 4.0 * A12 * A12)) / win_area2;
			
			if (min_eig < min_eigen_threshold || D < FLT_EPSILON) {
				if (level == 0) {
					status[ptid] = 0;
				}
				continue;
			}
			
			D = 1.0 / D;
			
			next_x -= half_win;
			next_y -= half_win;
			prev_delta_x = 0.0;
			prev_delta_y = 0.0;
			
			for (int iter = 0; iter < max_iter; ++iter) {
				inext_x = next_x;
				inext_y = next_y;
				
				bool is_border = (inext_x <= brd_tl) || (inext_x >= brd_r) || (inext_y <= brd_tl) || (inext_y >= brd_b);
				if (is_border != 0) {
					if (level == 0) {
						status[ptid] = 0;
					}
					break;
				}
				
				a = next_x - inext_x;
				b = next_y - inext_y;
				iw00 = (((1.0 - a) * (1.0 - b) * W_BITS14_) + 0.5);
				iw01 = ((a * (1.0 - b) * W_BITS14_) + 0.5);
				iw10 = (((1.0 - a) * b * W_BITS14_) + 0.5);
				iw11 = (W_BITS14_ - iw00 - iw01 - iw10);
				b1 = 0.0, b2 = 0.0;
				
				for (int y = 0; y < win_size; ++y) {
					jptr = (int)((y + inext_y) * lw + inext_x);
					iptr = (int)(y * win_size);
					diptr = iptr << 1;
					for (int x = 0 ; x < win_size; ++x, ++jptr, ++iptr) {
						int o1 = jptr+lw;
						byte n0 = img_next[jptr];
						byte n1 = img_next[jptr+1];
						byte n00 = o1   < next_len ? img_next[o1] : n0;
						byte n01 = o1+1 < next_len ? img_next[o1+1] : n00;
						
						ival = (int)(n0 * iw00 + n1 * iw01 + n00 * iw10 + n01 * iw11);
						ival = ((ival + W_BITS1m51) >> (W_BITS1m5));
						ival = (ival - iwin_buf[iptr]);
						
						b1 += ival * deriv_iwin[diptr++];
						b2 += ival * deriv_iwin[diptr++];
					}
				}
				
				b1 *= FLT_SCALE;
				b2 *= FLT_SCALE;
				
				delta_x = ((A12 * b2 - A22 * b1) * D);
				delta_y = ((A12 * b1 - A11 * b2) * D);
				
				next_x += delta_x;
				next_y += delta_y;
				curr_xy[i] = next_x + half_win;
				curr_xy[j] = next_y + half_win;
				
				if (delta_x*delta_x + delta_y*delta_y <= eps) {
					break;
				}
				
				if (iter > 0 && abs(delta_x + prev_delta_x) < 0.01 &&
					abs(delta_y + prev_delta_y) < 0.01) {
					curr_xy[i] -= delta_x * 0.5;
					curr_xy[j] -= delta_y * 0.5;
					break;
				}
				
				prev_delta_x = delta_x;
				prev_delta_y = delta_y;
			}
		}
	}
}


NAMESPACE_TOPSIDE_END
