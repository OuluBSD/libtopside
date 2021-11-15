#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN


void _resample_u8(const pyra8::Mat& src, pyra8::Mat& dst, int nw, int nh) {
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

void _resample(const pyraf::Mat& src, pyraf::Mat& dst, int nw, int nh) {
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

void resample(const pyra8::Mat& src, pyra8::Mat& dst, int nw, int nh) {
	int h = src.rows;
	int w = src.cols;
	if (h > nh && w > nw) {
		dst.SetSize(nw, nh, src.channels);
		_resample_u8(src, dst, nw, nh);
	}
}

void resample(const pyraf::Mat& src, pyraf::Mat& dst, int nw, int nh) {
	int h = src.rows;
	int w = src.cols;
	if (h > nh && w > nw) {
		dst.SetSize(nw, nh, src.channels);
		_resample(src, dst, nw, nh);
	}
}


void box_blur_gray(ByteMat& src, ByteMat& dst, int radius, dword options) {
	int w = src.cols;
	int h = src.rows;
	int h2 = h << 1;
	int w2 = w << 1;
	//var i = 0, x = 0, y = 0, end = 0;
	int windowSize = ((radius << 1) + 1);
	int radiusPlusOne = (radius + 1);
	int radiusPlus2 = (radiusPlusOne + 1);
	double scale = options & BOX_BLUR_NOSCALE ? 1.0 : (1.0 / (windowSize * windowSize));
	
	int sum = 0, srcIndex = 0, nextPixelIndex = 0, previousPixelIndex = 0;
	static thread_local Vector<int> data_i32;
	auto& data_u8 = src.data;
	int hold = 0;
	
	data_i32.SetCount((w * h) << 2);
	
	dst.SetSize(w, h, src.channels);
	
	// first pass
	// no need to scale
	//data_u8 = src.data;
	//data_i32 = tmp;
	for (int y = 0; y < h; ++y) {
		int dstIndex = y;
		int sum = radiusPlusOne * data_u8[srcIndex];
		
		for (int i = (srcIndex + 1), end = (srcIndex + radius); i <= end; ++i) {
			sum += data_u8[i];
		}
		
		nextPixelIndex = (srcIndex + radiusPlusOne);
		previousPixelIndex = srcIndex;
		hold = data_u8[previousPixelIndex];
		
		int x;
		for (x = 0; x < radius; ++x, dstIndex += h) {
			data_i32[dstIndex] = sum;
			sum += data_u8[nextPixelIndex] - hold;
			nextPixelIndex ++;
		}
		for (; x < w - radiusPlus2; x += 2, dstIndex += h2) {
			data_i32[dstIndex] = sum;
			sum += data_u8[nextPixelIndex] - data_u8[previousPixelIndex];
			
			data_i32[dstIndex+h] = sum;
			sum += data_u8[nextPixelIndex+1] - data_u8[previousPixelIndex+1];
			
			nextPixelIndex += 2;
			previousPixelIndex += 2;
		}
		for (; x < w - radiusPlusOne; ++x, dstIndex += h) {
			data_i32[dstIndex] = sum;
			sum += data_u8[nextPixelIndex] - data_u8[previousPixelIndex];
			
			nextPixelIndex ++;
			previousPixelIndex ++;
		}
		
		hold = data_u8[nextPixelIndex-1];
		for (; x < w; ++x, dstIndex += h) {
			data_i32[dstIndex] = sum;
			
			sum += hold - data_u8[previousPixelIndex];
			previousPixelIndex ++;
		}
		
		srcIndex += w;
	}
	
	// second pass
	srcIndex = 0;
	//data_i32 = tmp; // this is a transpose
	data_u8 <<= dst.data;
	
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
				data_u8[dstIndex] = sum;
				sum += data_i32[nextPixelIndex] - hold;
				nextPixelIndex ++;
			}
			for (; x < h - radiusPlus2; x += 2, dstIndex += w2) {
				data_u8[dstIndex] = sum;
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				
				data_u8[dstIndex+w] = sum;
				sum += data_i32[nextPixelIndex+1] - data_i32[previousPixelIndex+1];
				
				nextPixelIndex += 2;
				previousPixelIndex += 2;
			}
			for (; x < h - radiusPlusOne; ++x, dstIndex += w) {
				data_u8[dstIndex] = sum;
				
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				nextPixelIndex ++;
				previousPixelIndex ++;
			}
			hold = data_i32[nextPixelIndex-1];
			for (; x < h; ++x, dstIndex += w) {
				data_u8[dstIndex] = sum;
				
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
				data_u8[dstIndex] = (byte)(sum * scale);
				sum += data_i32[nextPixelIndex] - hold;
				nextPixelIndex ++;
			}
			for (; x < h - radiusPlus2; x += 2, dstIndex += w2) {
				data_u8[dstIndex] = (byte)(sum * scale);
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				
				data_u8[dstIndex+w] = (byte)(sum * scale);
				sum += data_i32[nextPixelIndex+1] - data_i32[previousPixelIndex+1];
				
				nextPixelIndex += 2;
				previousPixelIndex += 2;
			}
			for (; x < h - radiusPlusOne; ++x, dstIndex += w) {
				data_u8[dstIndex] = (byte)(sum * scale);
				
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				nextPixelIndex ++;
				previousPixelIndex ++;
			}
			hold = data_i32[nextPixelIndex-1];
			for (; x < h; ++x, dstIndex += w) {
				data_u8[dstIndex] = (byte)(sum * scale);
				
				sum += hold - data_i32[previousPixelIndex];
				previousPixelIndex ++;
			}
			
			srcIndex += h;
		}
	}
}


// TODO: add support for RGB/BGR order
// for raw arrays
void Grayscale(const ByteMat& src_, int w, int h, ByteMat& dst, int code) {
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
	
	dst.SetSize(w, h, 1);
	byte* dst_u8 = dst.data.Begin();
	const byte* src = src_.data.Begin();
	ASSERT(src_.data.GetCount() == w * h * cn);
	
	for (int y = 0, i = 0, j = 0; y < h; ++y, j += w, i += w * cn) {
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
}


NAMESPACE_TOPSIDE_END
