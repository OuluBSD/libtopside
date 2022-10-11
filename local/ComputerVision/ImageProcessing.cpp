#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN


void ResampleByte(const pyra8::Mat& src, pyra8::Mat& dst, int nw, int nh) {
	int xofs_count = 0;
	int ch = src.channels;
	int w = src.cols;
	int h = src.rows;
	const auto& src_d = src.data;
	auto& dst_d = dst.data;
	double scale_x = (double)w / nw;
	double scale_y = (double)h / nh;
	double inv_scale_256 = (scale_x * scale_y * 0x10000);
	
	static thread_local Vector<int> buf;
	static thread_local Vector<int> sum;
	static thread_local Vector<int> xofs;
	
	buf.SetCount((nw * ch) << 2);
	sum.SetCount((nw * ch) << 2);
	xofs.SetCount((w * 2 * 3) << 2);
	
	int k = 0;
	for (int dx = 0; dx < nw; dx++) {
		double fsx1 = dx * scale_x;
		double fsx2 = fsx1 + scale_x;
		double sx1 = (fsx1 + 1.0 - 1e-6);
		double sx2 = fsx2;
		sx1 = min(sx1, w - 1.0);
		sx2 = min(sx2, w - 1.0);
		
		if (sx1 > fsx1) {
			xofs[k++] = (int)(dx * ch);
			xofs[k++] = (int)((sx1 - 1) * ch);
			xofs[k++] = (int)((sx1 - fsx1) * 0x100);
			xofs_count++;
		}
		for (double sx = sx1; sx < sx2; sx += 1.0) {
			xofs_count++;
			xofs[k++] = (int)(dx * ch);
			xofs[k++] = (int)(sx * ch);
			xofs[k++] = 256;
		}
		if (fsx2 - sx2 > 1e-3) {
			xofs_count++;
			xofs[k++] = (int)(dx * ch);
			xofs[k++] = (int)(sx2 * ch);
			xofs[k++] = (int)((fsx2 - sx2) * 256);
		}
	}
	
	for (int dx = 0; dx < nw * ch; dx++) {
		buf[dx] = 0;
		sum[dx] = 0;
	}
	
	for (int sy = 0, dy = 0; sy < h; sy++) {
		int a = w * sy;
		for (int k = 0; k < xofs_count; k++) {
			int dxn = xofs[k*3];
			int sx1 = xofs[k*3+1];
			double alpha = xofs[k*3+2];
			for (int i = 0; i < ch; i++) {
				buf[dxn + i] += (int)(src_d[a+sx1+i] * alpha);
			}
		}
		if ((dy + 1) * scale_y <= sy + 1 || sy == h - 1) {
			double beta = (max(sy + 1 - (dy + 1) * scale_y, 0.0) * 256);
			double beta1 = 256 - beta;
			int b = nw * dy;
			int c = nw * ch;
			if (beta <= 0) {
				for (int dx = 0; dx < c; dx++) {
					dst_d[b+dx] = (int)min(max((sum[dx] + buf[dx] * 256) / inv_scale_256, 0.0), 255.0);
					sum[dx] = buf[dx] = 0;
				}
			}
			else {
				for (int dx = 0; dx < c; dx++) {
					dst_d[b+dx] = (int)min(max((sum[dx] + buf[dx] * beta1) / inv_scale_256, 0.0), 255.0);
					sum[dx] = (int)(buf[dx] * beta);
					buf[dx] = 0;
				}
			}
			dy++;
		}
		else {
			for (int dx = 0; dx < nw * ch; dx++) {
				sum[dx] += buf[dx] * 256;
				buf[dx] = 0;
			}
		}
	}
	
}

void ResampleFloat(const pyraf::Mat& src, pyraf::Mat& dst, int nw, int nh) {
	int xofs_count = 0;
	int ch = src.channels;
	int w = src.cols;
	int h = src.rows;
	const auto& src_d = src.data;
	auto& dst_d = dst.data;
	double scale_x = (double)w / nw;
	double scale_y = (double)h / nh;
	double scale = 1.0 / (scale_x * scale_y);
	
	Vector<float> buf;
	Vector<float> sum;
	Vector<float> xofs;
	
	buf.SetCount((nw * ch) << 2);
	sum.SetCount((nw * ch) << 2);
	xofs.SetCount((w * 2 * 3) << 2);
	
	int k = 0;
	for (int dx = 0; dx < nw; dx++) {
		double fsx1 = dx * scale_x;
		double fsx2 = fsx1 + scale_x;
		double sx1 = (fsx1 + 1.0 - 1e-6);
		double sx2 = fsx2;
		sx1 = min(sx1, w - 1.0);
		sx2 = min(sx2, w - 1.0);
		
		if (sx1 > fsx1) {
			xofs_count++;
			xofs[k++] = (float)((sx1 - 1) * ch);
			xofs[k++] = (float)(dx * ch);
			xofs[k++] = (float)((sx1 - fsx1) * scale);
		}
		for (double sx = sx1; sx < sx2; sx += 1.0) {
			xofs_count++;
			xofs[k++] = (float)(sx * ch);
			xofs[k++] = (float)(dx * ch);
			xofs[k++] = (float)scale;
		}
		if (fsx2 - sx2 > 1e-3) {
			xofs_count++;
			xofs[k++] = (float)(sx2 * ch);
			xofs[k++] = (float)(dx * ch);
			xofs[k++] = (float)((fsx2 - sx2) * scale);
		}
	}
	
	for (int dx = 0; dx < nw * ch; dx++) {
		buf[dx] = 0;
		sum[dx] = 0;
	}
	
	for (int sy = 0, dy = 0; sy < h; sy++) {
		int a = w * sy;
		for (int k = 0; k < xofs_count; k++) {
			float sx1 = xofs[k*3];
			float dxn = xofs[k*3+1];
			double alpha = xofs[k*3+2];
			for (int i = 0; i < ch; i++) {
				int j = (int)(a+sx1+i);
				int k = (int)(dxn + i);
				buf[k] += (float)(src_d[j] * alpha);
			}
		}
		if ((dy + 1) * scale_y <= sy + 1 || sy == h - 1) {
			double beta = max(sy + 1 - (dy + 1) * scale_y, 0.0);
			double beta1 = 1.0 - beta;
			int b = nw * dy;
			if (abs(beta) < 1e-3) {
				for (int dx = 0; dx < nw * ch; dx++) {
					dst_d[b+dx] = (byte)(sum[dx] + buf[dx]);
					sum[dx] = buf[dx] = 0;
				}
			}
			else {
				for (int dx = 0; dx < nw * ch; dx++) {
					dst_d[b+dx] = (byte)(sum[dx] + buf[dx] * beta1);
					sum[dx] = (float)(buf[dx] * beta);
					buf[dx] = 0;
				}
			}
			dy++;
		}
		else {
			for (int dx = 0; dx < nw * ch; dx++) {
				sum[dx] += buf[dx];
				buf[dx] = 0;
			}
		}
	}
	
}

void ConvoluteByte(Vector<int>& buf, const Vector<byte>& src_d, Vector<byte>& dst_d, int w, int h, Vector<double>& filter, int kernel_size, int half_kernel) {
	int  w2 = w << 1, w3 = w * 3, w4 = w << 2;
	
	double f0 = filter[0];
	
	// hor pass
	for (int i = 0, dp = 0, sp = 0; i < h; ++i) {
		int sum = src_d[sp];
		for (int j = 0; j < half_kernel; ++j) {
			buf[j] = sum;
		}
		{
			int j;
			for (j = 0; j <= w - 2; j += 2) {
				buf[j + half_kernel] = src_d[sp+j];
				buf[j + half_kernel+1] = src_d[sp+j+1];
			}
			for (; j < w; ++j) {
				buf[j + half_kernel] = src_d[sp+j];
			}
		}
		
		sum = src_d[sp+w-1];
		for (int j = w; j < half_kernel + w; ++j) {
			buf[j + half_kernel] = sum;
		}
		
		{
			int j;
			for (j = 0; j <= w - 4; j += 4) {
				int sum  = buf[j]   * f0;
				int sum1 = buf[j+1] * f0;
				int sum2 = buf[j+2] * f0;
				int sum3 = buf[j+3] * f0;
				
				for (int k = 1; k < kernel_size; ++k) {
					double fk = filter[k];
					sum  += buf[k + j] * fk;
					sum1 += buf[k + j+1] * fk;
					sum2 += buf[k + j+2] * fk;
					sum3 += buf[k + j+3] * fk;
				}
				dst_d[dp+j]   = min(sum,  255);
				dst_d[dp+j+1] = min(sum1, 255);
				dst_d[dp+j+2] = min(sum2, 255);
				dst_d[dp+j+3] = min(sum3, 255);
			}
			for (; j < w; ++j) {
				int sum = buf[j] * f0;
				for (int k = 1; k < kernel_size; ++k) {
					sum += buf[k + j] * filter[k];
				}
				dst_d[dp+j] = min(sum, 255);
			}
		}
		
		sp += w;
		dp += w;
	}
	
	// vert pass
	for (int i = 0; i < w; ++i) {
		int sum = dst_d[i];
		for (int j = 0; j < half_kernel; ++j) {
			buf[j] = sum;
		}
		
		{
			int k = i;
			int j;
			for (j = 0; j <= h - 2; j += 2, k += w2) {
				buf[j+half_kernel] = dst_d[k];
				buf[j+half_kernel+1] = dst_d[k+w];
			}
			for (; j < h; ++j, k += w) {
				buf[j+half_kernel] = dst_d[k];
			}
		}
		sum = dst_d[(h-1)*w + i];
		for (int j = h; j < half_kernel + h; ++j) {
			buf[j + half_kernel] = sum;
		}
		{
			int dp = i;
			int j;
			for (j = 0; j <= h - 4; j += 4, dp += w4) {
				int sum  = buf[j]   * f0;
				int sum1 = buf[j+1] * f0;
				int sum2 = buf[j+2] * f0;
				int sum3 = buf[j+3] * f0;
				for (int k = 1; k < kernel_size; ++k) {
					double fk = filter[k];
					sum += buf[k + j] * fk;
					sum1 += buf[k + j+1] * fk;
					sum2 += buf[k + j+2] * fk;
					sum3 += buf[k + j+3] * fk;
				}
				dst_d[dp] = min(sum, 255);
				dst_d[dp+w] = min(sum1, 255);
				dst_d[dp+w2] = min(sum2, 255);
				dst_d[dp+w3] = min(sum3, 255);
			}
			for (; j < h; ++j, dp += w) {
				sum = buf[j] * f0;
				for (int k = 1; k < kernel_size; ++k) {
					sum += buf[k + j] * filter[k];
				}
				dst_d[dp] = min(sum, 255);
			}
		}
	}
}


void Resample(const pyra8::Mat& src, pyra8::Mat& dst, int nw, int nh) {
	int h = src.rows;
	int w = src.cols;
	if (h > nh && w > nw) {
		dst.SetSize(nw, nh, src.channels);
		ResampleByte(src, dst, nw, nh);
	}
	else {
		dst = src;
	}
}

void Resample(const pyraf::Mat& src, pyraf::Mat& dst, int nw, int nh) {
	int h = src.rows;
	int w = src.cols;
	if (h > nh && w > nw) {
		dst.SetSize(nw, nh, src.channels);
		ResampleFloat(src, dst, nw, nh);
	}
	else {
		dst = src;
	}
}


void BoxBlurGray(ByteMat& src, ByteMat& dst, int radius, dword options) {
	int w = src.cols;
	int h = src.rows;
	int h2 = h << 1;
	int w2 = w << 1;
	int windowSize = ((radius << 1) + 1);
	int radiusPlusOne = (radius + 1);
	int radiusPlus2 = (radiusPlusOne + 1);
	double scale = options & BOX_BLUR_NOSCALE ? 1.0 : (1.0 / (windowSize * windowSize));
	
	int sum = 0, srcIndex = 0, nextPixelIndex = 0, previousPixelIndex = 0;
	static thread_local Vector<int> data_i32;
	auto& src_data = src.data;
	int hold = 0;
	
	data_i32.SetCount((w * h) << 2);
	
	dst.SetSize(w, h, src.channels);
	
	// first pass
	// no need to scale
	for (int y = 0; y < h; ++y) {
		int dstIndex = y;
		int sum = radiusPlusOne * src_data[srcIndex];
		
		for (int i = (srcIndex + 1), end = (srcIndex + radius); i <= end; ++i) {
			sum += src_data[i];
		}
		
		nextPixelIndex = (srcIndex + radiusPlusOne);
		previousPixelIndex = srcIndex;
		hold = src_data[previousPixelIndex];
		
		int x;
		for (x = 0; x < radius; ++x, dstIndex += h) {
			data_i32[dstIndex] = sum;
			sum += src_data[nextPixelIndex] - hold;
			nextPixelIndex ++;
		}
		for (; x < w - radiusPlus2; x += 2, dstIndex += h2) {
			data_i32[dstIndex] = sum;
			sum += src_data[nextPixelIndex] - src_data[previousPixelIndex];
			
			data_i32[dstIndex+h] = sum;
			sum += src_data[nextPixelIndex+1] - src_data[previousPixelIndex+1];
			
			nextPixelIndex += 2;
			previousPixelIndex += 2;
		}
		for (; x < w - radiusPlusOne; ++x, dstIndex += h) {
			data_i32[dstIndex] = sum;
			sum += src_data[nextPixelIndex] - src_data[previousPixelIndex];
			
			nextPixelIndex ++;
			previousPixelIndex ++;
		}
		
		hold = src_data[nextPixelIndex-1];
		for (; x < w; ++x, dstIndex += h) {
			data_i32[dstIndex] = sum;
			
			sum += hold - src_data[previousPixelIndex];
			previousPixelIndex ++;
		}
		
		srcIndex += w;
	}
	
	// second pass
	srcIndex = 0;
	auto& dst_data = dst.data;
	
	// dont scale result
	if (scale == 1) {
		for (int y = 0; y < w; ++y) {
			int dstIndex = y;
			int sum = radiusPlusOne * data_i32[srcIndex];
			
			for (int i = (srcIndex + 1), end = (srcIndex + radius); i <= end; ++i) {
				sum += data_i32[i];
			}
			
			nextPixelIndex = srcIndex + radiusPlusOne;
			previousPixelIndex = srcIndex;
			hold = data_i32[previousPixelIndex];
			
			int x;
			for (x = 0; x < radius; ++x, dstIndex += w) {
				dst_data[dstIndex] = sum;
				sum += data_i32[nextPixelIndex] - hold;
				nextPixelIndex ++;
			}
			for (; x < h - radiusPlus2; x += 2, dstIndex += w2) {
				dst_data[dstIndex] = sum;
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				
				dst_data[dstIndex+w] = sum;
				sum += data_i32[nextPixelIndex+1] - data_i32[previousPixelIndex+1];
				
				nextPixelIndex += 2;
				previousPixelIndex += 2;
			}
			for (; x < h - radiusPlusOne; ++x, dstIndex += w) {
				dst_data[dstIndex] = sum;
				
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				nextPixelIndex ++;
				previousPixelIndex ++;
			}
			hold = data_i32[nextPixelIndex-1];
			for (; x < h; ++x, dstIndex += w) {
				dst_data[dstIndex] = sum;
				
				sum += hold - data_i32[previousPixelIndex];
				previousPixelIndex ++;
			}
			
			srcIndex += h;
		}
	}
	else {
		for (int y = 0; y < w; ++y) {
			int dstIndex = y;
			int sum = radiusPlusOne * data_i32[srcIndex];
			
			for (int i = (srcIndex + 1), end = (srcIndex + radius); i <= end; ++i) {
				sum += data_i32[i];
			}
			
			nextPixelIndex = srcIndex + radiusPlusOne;
			previousPixelIndex = srcIndex;
			hold = data_i32[previousPixelIndex];
			
			int x;
			for (x = 0; x < radius; ++x, dstIndex += w) {
				dst_data[dstIndex] = (byte)(sum * scale);
				sum += data_i32[nextPixelIndex] - hold;
				nextPixelIndex ++;
			}
			for (; x < h - radiusPlus2; x += 2, dstIndex += w2) {
				dst_data[dstIndex] = (byte)(sum * scale);
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				
				dst_data[dstIndex+w] = (byte)(sum * scale);
				sum += data_i32[nextPixelIndex+1] - data_i32[previousPixelIndex+1];
				
				nextPixelIndex += 2;
				previousPixelIndex += 2;
			}
			for (; x < h - radiusPlusOne; ++x, dstIndex += w) {
				dst_data[dstIndex] = (byte)(sum * scale);
				
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				nextPixelIndex ++;
				previousPixelIndex ++;
			}
			hold = data_i32[nextPixelIndex-1];
			for (; x < h; ++x, dstIndex += w) {
				dst_data[dstIndex] = (byte)(sum * scale);
				
				sum += hold - data_i32[previousPixelIndex];
				previousPixelIndex ++;
			}
			
			srcIndex += h;
		}
	}
}


void Grayscale(const ByteMat& src, ByteMat& dst) {
	int w = src.cols;
	int h = src.rows;
	dst.SetSize(w, h, 1);
	
	const byte* from = src.data.Begin();
	byte* to = dst.data.Begin();
	byte* end = dst.data.End();
	int cn = min(src.channels, 3);
	int step = src.channels;
	double mul = 1.0 / cn;
	
	if (cn == 3) {
		while (to != end) {
			int av = 0;
			for(int i = 0; i < 3; i++)
				av += from[i];
			av *= mul;
			*to++ = (byte)av;
			from += step;
		}
	}
	else {
		while (to != end) {
			int av = 0;
			for(int i = 0; i < cn; i++)
				av += from[i];
			av *= mul;
			*to++ = (byte)av;
			from += step;
		}
	}
}

void WarpPerspective(const ByteMat& src, ByteMat& dst, const FloatMat& transform, int fill_value) {
	if (dst.IsEmpty())
		dst.SetSize(src.cols, src.rows, src.channels);
	
	int src_width = src.cols;
	int src_height = src.rows;
	int src_len = src.data.GetCount();
	int dst_width = dst.cols;
	int dst_height = dst.rows;
	
	auto& src_d = src.data;
	auto& dst_d = dst.data;
	double xs = 0.0, ys = 0.0, xs0 = 0.0, ys0 = 0.0, ws = 0.0, sc = 0.0, a = 0.0, b = 0.0, p0 = 0.0, p1 = 0.0;
	auto& td = transform.data;
	auto m00 = td[0];
	auto m01 = td[1];
	auto m02 = td[2];
	auto m10 = td[3];
	auto m11 = td[4];
	auto m12 = td[5];
	auto m20 = td[6];
	auto m21 = td[7];
	auto m22 = td[8];
	
	auto dst_iter = dst_d.Begin();
	ASSERT(dst_d.GetCount() == dst_height * dst_width);
	
	for (int y = 0; y < dst_height; ++y) {
		xs0 = m01 * y + m02;
		ys0 = m11 * y + m12;
		ws  = m21 * y + m22;
		for (int x = 0; x < dst_width; ++x, xs0 += m00, ys0 += m10, ws += m20) {
			sc = 1.0 / ws;
			xs = xs0 * sc, ys = ys0 * sc;
			int ixs = xs;
			int iys = ys;
			
			if (ixs >= 0 && iys >= 0 && ixs < (src_width - 1) && iys < (src_height - 1)) {
				double a = xs - ixs;
				double b = ys - iys;
				int off0 = (int)(src_width * iys + ixs);
				int off1 = off0 + src_width;
				
				byte v0 = src_d[off0];
				byte v1 = src_d[off0 + 1];
				byte v10 = off1 < src_len ? src_d[off1] : v0;
				byte v11 = off1 < src_len ? src_d[off1+1] : v1;
				
				double p0 =		v0  + a *  (v1 -  v0);
				double p1 =		v10 + a * (v11 - v10);
				
				auto v = (p0 + b * (p1 - p0));
				*dst_iter = v;
			}
			else
				*dst_iter = fill_value;
			
			dst_iter++;
		}
	}
}

void WarpAffine(const ByteMat& src, ByteMat& dst, const FloatMat& transform, int fill_value) {
	if (dst.IsEmpty())
		dst.SetSize(src.cols, src.rows, src.channels);
	
	int src_width = src.cols;
	int src_height = src.rows;
	int src_len = src.data.GetCount();
	int dst_width = dst.cols;
	int dst_height = dst.rows;
	const auto& src_d = src.data;
	auto& dst_d = dst.data;
	
	const auto& td = transform.data;
	double m00 = td[0];
	double m01 = td[1];
	double m02 = td[2];
	double m10 = td[3];
	double m11 = td[4];
	double m12 = td[5];
	
	auto dst_iter = dst_d.Begin();
	ASSERT(dst_d.GetCount() == dst_height * dst_width);
	
	for (int y = 0; y < dst_height; ++y) {
		double xs = m01 * y + m02;
		double ys = m11 * y + m12;
		
		for (int x = 0; x < dst_width; ++x, xs += m00, ys += m10) {
			int ixs = xs;
			int iys = ys;
			
			if (ixs >= 0 && iys >= 0 && ixs < (src_width - 1) && iys < (src_height - 1)) {
				double a = xs - ixs;
				double b = ys - iys;
				int off0 = (int)(src_width * iys + ixs);
				int off1 = off0 + src_width;
				
				byte v0 = src_d[off0];
				byte v1 = src_d[off0 + 1];
				byte v10 = off1 < src_len ? src_d[off1] : v0;
				byte v11 = off1 < src_len ? src_d[off1+1] : v1;
				
				double p0 =		v0  + a *  (v1 -  v0);
				double p1 =		v10 + a * (v11 - v10);
				
				auto v = (p0 + b * (p1 - p0));
				*dst_iter = v;
			}
			else
				*dst_iter = fill_value;
			
			dst_iter++;
		}
	}
}


NAMESPACE_TOPSIDE_END
