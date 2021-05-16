#ifndef _ComputerVision_ImageProcessing_h_
#define _ComputerVision_ImageProcessing_h_


NAMESPACE_TOPSIDE_BEGIN

void Grayscale(const VideoInputFrame& src, int w, int h, VideoOutputFrame& dst, int code = COLOR_RGBA2GRAY);



#if 0

void _resample_u8(src, dst, int nw, int nh) {
	int xofs_count = 0;
	int ch = src.channel;
	int w = src.cols;
	v h = src.rows;
	var src_d = src.data;
	dst_d = dst.data;
	double scale_x = (double)w / nw;
	double scale_y = (double)h / nh;
	int inv_scale_256 = (scale_x * scale_y * 0x10000);
	//var dx = 0, dy = 0, sx = 0, sy = 0, sx1 = 0, sx2 = 0, i = 0, k = 0, fsx1 = 0.0, fsx2 = 0.0;
	//var a = 0, b = 0, dxn = 0, alpha = 0, beta = 0, beta1 = 0;
	
	var buf_node = cache.get_buffer((nw * ch) << 2);
	var sum_node = cache.get_buffer((nw * ch) << 2);
	var xofs_node = cache.get_buffer((w * 2 * 3) << 2);
	
	var buf = buf_node.i32;
	var sum = sum_node.i32;
	var xofs = xofs_node.i32;
	
	for (int dx = 0; dx < nw; dx++) {
		double fsx1 = dx * scale_x;
		double fsx2 = fsx1 + scale_x;
		double sx1 = (fsx1 + 1.0 - 1e-6);
		double sx2 = fsx2;
		double sx1 = min(sx1, w - 1.0);
		double sx2 = min(sx2, w - 1.0);
		
		if (sx1 > fsx1) {
			xofs[k++] = (dx * ch);
			xofs[k++] = ((sx1 - 1) * ch);
			xofs[k++] = ((sx1 - fsx1) * 0x100);
			xofs_count++;
		}
		for (int sx = sx1; sx < sx2; sx++) {
			xofs_count++;
			xofs[k++] = (dx * ch);
			xofs[k++] = (sx * ch);
			xofs[k++] = 256;
		}
		if (fsx2 - sx2 > 1e-3) {
			xofs_count++;
			xofs[k++] = (dx * ch);
			xofs[k++] = (sx2 * ch);
			xofs[k++] = ((fsx2 - sx2) * 256);
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
				buf[dxn + i] += src_d[a+sx1+i] * alpha;
			}
		}
		if ((dy + 1) * scale_y <= sy + 1 || sy == h - 1) {
			double beta = (max(sy + 1 - (dy + 1) * scale_y, 0.0) * 256);
			double beta1 = 256 - beta;
			int b = nw * dy;
			int c = nw * ch;
			if (beta <= 0) {
				for (int dx = 0; dx < c; dx++) {
					dst_d[b+dx] = min(max((sum[dx] + buf[dx] * 256) / inv_scale_256, 0), 255);
					sum[dx] = buf[dx] = 0;
				}
			}
			else {
				for (int dx = 0; dx < c; dx++) {
					dst_d[b+dx] = min(max((sum[dx] + buf[dx] * beta1) / inv_scale_256, 0), 255);
					sum[dx] = buf[dx] * beta;
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
	
	cache.put_buffer(sum_node);
	cache.put_buffer(buf_node);
	cache.put_buffer(xofs_node);
}

void _resample(src, dst, int nw, int nh) {
	int xofs_count = 0;
	int ch = src.channel;
	int w = src.cols;
	int h = src.rows;
	var src_d = src.data;
	var dst_d = dst.data;
	double scale_x = (double)w / nw;
	double scale_y = (double)h / nh;
	double scale = 1.0 / (scale_x * scale_y);
	//var dx = 0, dy = 0, sx = 0, sy = 0, sx1 = 0, sx2 = 0, i = 0, k = 0, fsx1 = 0.0, fsx2 = 0.0;
	//var a = 0, b = 0, dxn = 0, alpha = 0.0, beta = 0.0, beta1 = 0.0;
	
	var buf_node = cache.get_buffer((nw * ch) << 2);
	var sum_node = cache.get_buffer((nw * ch) << 2);
	var xofs_node = cache.get_buffer((w * 2 * 3) << 2);
	
	var buf = buf_node.f32;
	var sum = sum_node.f32;
	var xofs = xofs_node.f32;
	
	for (int dx = 0; dx < nw; dx++) {
		double fsx1 = dx * scale_x;
		double fsx2 = fsx1 + scale_x;
		double sx1 = (fsx1 + 1.0 - 1e-6);
		double sx2 = fsx2;
		double sx1 = min(sx1, w - 1);
		double sx2 = min(sx2, w - 1);
		
		if (sx1 > fsx1) {
			xofs_count++;
			xofs[k++] = ((sx1 - 1) * ch);
			xofs[k++] = (dx * ch);
			xofs[k++] = (sx1 - fsx1) * scale;
		}
		for (int sx = sx1; sx < sx2; sx++) {
			xofs_count++;
			xofs[k++] = (sx * ch);
			xofs[k++] = (dx * ch);
			xofs[k++] = scale;
		}
		if (fsx2 - sx2 > 1e-3) {
			xofs_count++;
			xofs[k++] = (sx2 * ch);
			xofs[k++] = (dx * ch);
			xofs[k++] = (fsx2 - sx2) * scale;
		}
	}
	
	for (int dx = 0; dx < nw * ch; dx++) {
		buf[dx] = 0;
		sum[dx] = 0;
	}
	
	for (int sy = 0, dy = 0; sy < h; sy++) {
		int a = w * sy;
		for (int k = 0; k < xofs_count; k++) {
			int sx1 = xofs[k*3];
			int dxn = xofs[k*3+1];
			double alpha = xofs[k*3+2];
			for (int i = 0; i < ch; i++) {
				buf[dxn + i] += src_d[a+sx1+i] * alpha;
			}
		}
		if ((dy + 1) * scale_y <= sy + 1 || sy == h - 1) {
			double beta = max(sy + 1 - (dy + 1) * scale_y, 0.0);
			double beta1 = 1.0 - beta;
			int b = nw * dy;
			if (abs(beta) < 1e-3) {
				for (int dx = 0; dx < nw * ch; dx++) {
					dst_d[b+dx] = sum[dx] + buf[dx];
					sum[dx] = buf[dx] = 0;
				}
			}
			else {
				for (int dx = 0; dx < nw * ch; dx++) {
					dst_d[b+dx] = sum[dx] + buf[dx] * beta1;
					sum[dx] = buf[dx] * beta;
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
	
	cache.put_buffer(sum_node);
	cache.put_buffer(buf_node);
	cache.put_buffer(xofs_node);
}

void _convol_u8(buf, src_d, dst_d, int w, int h, filter, kernel_size, half_kernel) {
	//var i = 0, j = 0, k = 0, sp = 0, dp = 0, sum = 0, sum1 = 0, sum2 = 0, sum3 = 0, f0 = filter[0], fk = 0;
	//var w2 = w << 1, w3 = w * 3, w4 = w << 2;
	
	// hor pass
	for (int i = 0, dp = 0, sp = 0; i < h; ++i) {
		sum = src_d[sp];
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
				sum = buf[j] * f0,
					  sum1 = buf[j+1] * f0,
							 sum2 = buf[j+2] * f0,
									sum3 = buf[j+3] * f0;
				for (k = 1; k < kernel_size; ++k) {
					fk = filter[k];
					sum += buf[k + j] * fk;
					sum1 += buf[k + j+1] * fk;
					sum2 += buf[k + j+2] * fk;
					sum3 += buf[k + j+3] * fk;
				}
				dst_d[dp+j] = min(sum >> 8, 255);
				dst_d[dp+j+1] = min(sum1 >> 8, 255);
				dst_d[dp+j+2] = min(sum2 >> 8, 255);
				dst_d[dp+j+3] = min(sum3 >> 8, 255);
			}
			for (; j < w; ++j) {
				sum = buf[j] * f0;
				for (k = 1; k < kernel_size; ++k) {
					sum += buf[k + j] * filter[k];
				}
				dst_d[dp+j] = min(sum >> 8, 255);
			}
		}
		
		sp += w;
		dp += w;
	}
	
	// vert pass
	for (int i = 0; i < w; ++i) {
		sum = dst_d[i];
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
				sum = buf[j] * f0;
				sum1 = buf[j+1] * f0;
				sum2 = buf[j+2] * f0;
				sum3 = buf[j+3] * f0;
				for (int k = 1; k < kernel_size; ++k) {
					fk = filter[k];
					sum += buf[k + j] * fk;
					sum1 += buf[k + j+1] * fk;
					sum2 += buf[k + j+2] * fk;
					sum3 += buf[k + j+3] * fk;
				}
				dst_d[dp] = min(sum >> 8, 255);
				dst_d[dp+w] = min(sum1 >> 8, 255);
				dst_d[dp+w2] = min(sum2 >> 8, 255);
				dst_d[dp+w3] = min(sum3 >> 8, 255);
			}
			for (; j < h; ++j, dp += w) {
				sum = buf[j] * f0;
				for (k = 1; k < kernel_size; ++k) {
					sum += buf[k + j] * filter[k];
				}
				dst_d[dp] = min(sum >> 8, 255);
			}
		}
	}
}

void _convol(buf, src_d, dst_d, w, h, filter, kernel_size, half_kernel) {
	//var i = 0, j = 0, k = 0, sp = 0, dp = 0
	//double sum = 0.0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, f0 = filter[0], fk = 0.0;
	//var w2 = w << 1, w3 = w * 3, w4 = w << 2;
	// hor pass
	for (int i = 0, sp = 0, dp = 0; i < h; ++i) {
		sum = src_d[sp];
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
		for (j = w; j < half_kernel + w; ++j) {
			buf[j + half_kernel] = sum;
		}
		
		{
			int j;
			for (j = 0; j <= w - 4; j += 4) {
				sum = buf[j] * f0;
				sum1 = buf[j+1] * f0;
				sum2 = buf[j+2] * f0;
				sum3 = buf[j+3] * f0;
				for (k = 1; k < kernel_size; ++k) {
					fk = filter[k];
					sum += buf[k + j] * fk;
					sum1 += buf[k + j+1] * fk;
					sum2 += buf[k + j+2] * fk;
					sum3 += buf[k + j+3] * fk;
				}
				dst_d[dp+j] = sum;
				dst_d[dp+j+1] = sum1;
				dst_d[dp+j+2] = sum2;
				dst_d[dp+j+3] = sum3;
			}
			for (; j < w; ++j) {
				sum = buf[j] * f0;
				for (k = 1; k < kernel_size; ++k) {
					sum += buf[k + j] * filter[k];
				}
				dst_d[dp+j] = sum;
			}
		}
		sp += w;
		dp += w;
	}
	
	// vert pass
	for (int i = 0; i < w; ++i) {
		sum = dst_d[i];
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
				sum = buf[j] * f0,
					  sum1 = buf[j+1] * f0,
							 sum2 = buf[j+2] * f0,
									sum3 = buf[j+3] * f0;
				for (k = 1; k < kernel_size; ++k) {
					fk = filter[k];
					sum += buf[k + j] * fk;
					sum1 += buf[k + j+1] * fk;
					sum2 += buf[k + j+2] * fk;
					sum3 += buf[k + j+3] * fk;
				}
				dst_d[dp] = sum;
				dst_d[dp+w] = sum1;
				dst_d[dp+w2] = sum2;
				dst_d[dp+w3] = sum3;
			}
			for (; j < h; ++j, dp += w) {
				sum = buf[j] * f0;
				for (k = 1; k < kernel_size; ++k) {
					sum += buf[k + j] * filter[k];
				}
				dst_d[dp] = sum;
			}
		}
	}
}


void resample(src, dst, nw, nh) {
	int h = src.rows;
	int w = src.cols;
	if (h > nh && w > nw) {
		dst.Resize(nw, nh, src.channel);
		
		// using the fast alternative (fix point scale, 0x100 to avoid overflow)
		if (src.type&U8_t && dst.type&U8_t && h * w / (nh * nw) < 0x100) {
			_resample_u8(src, dst, nw, nh);
		}
		else {
			_resample(src, dst, nw, nh);
		}
	}
},

void box_blur_gray(src, dst, radius, dword options = 0) {
	if (typeof options == = "undefined") {
		options = 0;
	}
	int w = src.cols;
	int h = src.rows;
	int h2 = h << 1;
	int w2 = w << 1;
	//var i = 0, x = 0, y = 0, end = 0;
	int windowSize = ((radius << 1) + 1);
	int radiusPlusOne = (radius + 1);
	int radiusPlus2 = (radiusPlusOne + 1);
	double scale = options & BOX_BLUR_NOSCALE ? 1.0 : (1.0 / (windowSize * windowSize));
	
	var tmp_buff = cache.get_buffer((w * h) << 2);
	
	int sum = 0, srcIndex = 0, nextPixelIndex = 0, previousPixelIndex = 0;
	var data_i32 = tmp_buff.i32; // to prevent overflow
	var data_u8 = src.data;
	var hold = 0;
	
	dst.resize(w, h, src.channel);
	
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
	data_u8 = dst.data;
	
	// dont scale result
	if (scale == 1) {
		for (int y = 0; y < w; ++y) {
			int dstIndex = y;
			int sum = radiusPlusOne * data_i32[srcIndex];
			
			for (i = (srcIndex + 1), end = (srcIndex + radius); i <= end; ++i) {
				sum += data_i32[i];
			}
			
			nextPixelIndex = srcIndex + radiusPlusOne;
			previousPixelIndex = srcIndex;
			hold = data_i32[previousPixelIndex];
			
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
		for (y = 0; y < w; ++y) {
			int dstIndex = y;
			int sum = radiusPlusOne * data_i32[srcIndex];
			
			for (i = (srcIndex + 1), end = (srcIndex + radius); i <= end; ++i) {
				sum += data_i32[i];
			}
			
			nextPixelIndex = srcIndex + radiusPlusOne;
			previousPixelIndex = srcIndex;
			hold = data_i32[previousPixelIndex];
			
			int x;
			for (x = 0; x < radius; ++x, dstIndex += w) {
				data_u8[dstIndex] = sum * scale;
				sum += data_i32[nextPixelIndex] - hold;
				nextPixelIndex ++;
			}
			for (; x < h - radiusPlus2; x += 2, dstIndex += w2) {
				data_u8[dstIndex] = sum * scale;
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				
				data_u8[dstIndex+w] = sum * scale;
				sum += data_i32[nextPixelIndex+1] - data_i32[previousPixelIndex+1];
				
				nextPixelIndex += 2;
				previousPixelIndex += 2;
			}
			for (; x < h - radiusPlusOne; ++x, dstIndex += w) {
				data_u8[dstIndex] = sum * scale;
				
				sum += data_i32[nextPixelIndex] - data_i32[previousPixelIndex];
				nextPixelIndex ++;
				previousPixelIndex ++;
			}
			hold = data_i32[nextPixelIndex-1];
			for (; x < h; ++x, dstIndex += w) {
				data_u8[dstIndex] = sum * scale;
				
				sum += hold - data_i32[previousPixelIndex];
				previousPixelIndex ++;
			}
			
			srcIndex += h;
		}
	}
	
	cache.put_buffer(tmp_buff);
},

gaussian_blur(src, dst, int kernel_size = 0, double sigma = 0.0) {
	if (kernel_size == 0)
		kernel_size = max(1, (4.0 * sigma + 1.0 - 1e-8)) * 2 + 1;
		
	int half_kernel = kernel_size >> 1;
	int w = src.cols;
	int h = src.rows;
	var data_type = src.type;
	is_u8 = data_type & U8_t;
	
	dst.Resize(w, h, src.channel);
	
	var src_d = src.data;
	dst_d = dst.data;
	var buf, filter;
	int buf_sz = (kernel_size + max(h, w));
	
	var buf_node = cache.get_buffer(buf_sz << 2);
	var filt_node = cache.get_buffer(kernel_size << 2);
	
	if (is_u8) {
		buf = buf_node.i32;
		filter = filt_node.i32;
	}
	else
		if (data_type&S32_t) {
			buf = buf_node.i32;
			filter = filt_node.f32;
		}
		else {
			buf = buf_node.f32;
			filter = filt_node.f32;
		}
		
	get_gaussian_kernel(kernel_size, sigma, filter, data_type);
	
	if (is_u8) {
		_convol_u8(buf, src_d, dst_d, w, h, filter, kernel_size, half_kernel);
	}
	else {
		_convol(buf, src_d, dst_d, w, h, filter, kernel_size, half_kernel);
	}
	
	cache.put_buffer(buf_node);
	cache.put_buffer(filt_node);
}

Vector<Pointf> hough_transform(img, double rho_res, double theta_res, threshold) {
	var image = img.data;
	
	int width = img.cols;
	int height = img.rows;
	int step = width;
	
	double min_theta = 0.0;
	double max_theta = M_PI;
	
	int numangle = round((max_theta - min_theta) / theta_res);
	int numrho = round(((width + height) * 2 + 1) / rho_res);
	double irho = 1.0 / rho_res;
	
	
	Vector<int> accum;
	Vector<double> tabSin, tabCos;
	
	accum.SetCount((numangle + 2) * (numrho + 2), 0);
	tabSin.SetCount(numangle);
	tabCos.SetCount(numangle);
	
	double ang = min_theta;
	for (int n = 0; n < numangle; n++) {
		tabSin[n] = FastSin(ang) * irho;
		tabCos[n] = FastCos(ang) * irho;
		ang += theta_res
		   }
	       
		   // stage 1. fill accumulator
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (image[i * step + j] != 0) {
				//console.log(r, (n+1) * (numrho+2) + r+1, tabCos[n], tabSin[n]);
				for (int n = 0; n < numangle; n++) {
					double r = round(j * tabCos[n] + i * tabSin[n]);
					r += (numrho - 1) / 2;
					accum[(n+1) * (numrho+2) + r+1] += 1;
				}
			}
		}
	}
	
	// stage 2. find local maximums
	//TODO: Consider making a vector class that uses typed arrays
	Vector<int> _sort_buf;
	for (int r = 0; r < numrho; r++) {
		for (int n = 0; n < numangle; n++) {
			int base = (n + 1) * (numrho + 2) + r + 1;
			auto value = accum[base];
			if (value > threshold &&
				value > accum[base - 1] &&
				value >= accum[base + 1] &&
				value > accum[base - numrho - 2] &&
				value >= accum[base + numrho + 2]) {
				_sort_buf.Add(base);
			}
		}
	}
	
	// stage 3. sort the detected lines by accumulator value
	_sort_buf.sort([](l1, l2) {
		return accum[l1] > accum[l2] || (accum[l1] == accum[l2] && l1 < l2);
	}
				  );
	              
	// stage 4. store the first min(total,linesMax) lines to the output buffer
	int linesMax = min(numangle * numrho, _sort_buf.length);
	double scale = 1.0 / (numrho + 2);
	Vector<Pointf> lines;
	for (int i = 0; i < linesMax; i++) {
		int idx = _sort_buf[i];
		int n = floor(idx * scale) - 1;
		int r = idx - (n + 1) * (numrho + 2) - 1;
		double lrho = (r - (numrho - 1) * 0.5) * rho_res;
		double langle = n * theta_res;
		lines.Add(Pointf(lrho, langle));
	}
	return lines;
}



void scharr_derivatives(src, dst) {
	int w = src.cols;
	int h = src.rows;
	int dstep = w << 1;
	//int a, b, c, d, e, f;
	var srow0 = 0, srow1 = 0, srow2 = 0, drow = 0;
	var trow0, trow1;
	
	dst.Resize(w, h, 2); // 2 channel output gx, gy
	
	var img = src.data;
	gxgy = dst.data;
	
	var buf0_node = cache.get_buffer((w + 2) << 2);
	var buf1_node = cache.get_buffer((w + 2) << 2);
	
	if (src.type&U8_t || src.type&S32_t) {
		trow0 = buf0_node.i32;
		trow1 = buf1_node.i32;
	}
	else {
		trow0 = buf0_node.f32;
		trow1 = buf1_node.f32;
	}
	
	for (int y = 0; y < h; ++y, srow1 += w) {
		srow0 = ((y > 0 ? y - 1 : 1) * w);
		srow2 = ((y < h - 1 ? y + 1 : h - 2) * w);
		drow = (y * dstep);
		
		// do vertical convolution
		int x, x1;
		for (x = 0, x1 = 1; x <= w - 2; x += 2, x1 += 2) {
			a = img[srow0+x], b = img[srow2+x];
			trow0[x1] = ((a + b) * 3 + (img[srow1+x]) * 10);
			trow1[x1] = (b - a);
			//
			a = img[srow0+x+1], b = img[srow2+x+1];
			trow0[x1+1] = ((a + b) * 3 + (img[srow1+x+1]) * 10);
			trow1[x1+1] = (b - a);
		}
		for (; x < w; ++x, ++x1) {
			a = img[srow0+x], b = img[srow2+x];
			trow0[x1] = ((a + b) * 3 + (img[srow1+x]) * 10);
			trow1[x1] = (b - a);
		}
		
		// make border
		int x = (w + 1);
		trow0[0] = trow0[1];
		trow0[x] = trow0[w];
		trow1[0] = trow1[1];
		trow1[x] = trow1[w];
		// do horizontal convolution, interleave the results and store them
		for (x = 0; x <= w - 4; x += 4) {
			a = trow1[x+2], b = trow1[x+1], c = trow1[x+3], d = trow1[x+4],
								e = trow0[x+2], f = trow0[x+3];
			gxgy[drow++] = (e - trow0[x]);
			gxgy[drow++] = ((a + trow1[x]) * 3 + b * 10);
			gxgy[drow++] = (f - trow0[x+1]);
			gxgy[drow++] = ((c + b) * 3 + a * 10);
			
			gxgy[drow++] = ((trow0[x+4] - e));
			gxgy[drow++] = (((d + a) * 3 + c * 10));
			gxgy[drow++] = ((trow0[x+5] - f));
			gxgy[drow++] = (((trow1[x+5] + c) * 3 + d * 10));
		}
		for (; x < w; ++x) {
			gxgy[drow++] = ((trow0[x+2] - trow0[x]));
			gxgy[drow++] = (((trow1[x+2] + trow1[x]) * 3 + trow1[x+1] * 10));
		}
	}
	
	cache.put_buffer(buf0_node);
	cache.put_buffer(buf1_node);
},

// compute gradient using Sobel kernel [1 2 1] * [-1 0 1]^T
// dst: [gx,gy,...]
void sobel_derivatives(src, dst) {
	int w = src.cols, h = src.rows;
	int dstep = w << 1;
	//a, b, c, d, e, f;
	var srow0 = 0, srow1 = 0, srow2 = 0, drow = 0;
	var trow0, trow1;
	
	dst.Resize(w, h, 2); // 2 channel output gx, gy
	
	var img = src.data, gxgy = dst.data;
	
	var buf0_node = cache.get_buffer((w + 2) << 2);
	var buf1_node = cache.get_buffer((w + 2) << 2);
	
	if (src.type&U8_t || src.type&S32_t) {
		trow0 = buf0_node.i32;
		trow1 = buf1_node.i32;
	}
	else {
		trow0 = buf0_node.f32;
		trow1 = buf1_node.f32;
	}
	
	for (int y = 0; y < h; ++y, srow1 += w) {
		srow0 = ((y > 0 ? y - 1 : 1) * w);
		srow2 = ((y < h - 1 ? y + 1 : h - 2) * w);
		drow = (y * dstep);
		// do vertical convolution
		int x, x1;
		for (x = 0, x1 = 1; x <= w - 2; x += 2, x1 += 2) {
			a = img[srow0+x], b = img[srow2+x];
			trow0[x1] = ((a + b) + (img[srow1+x] * 2));
			trow1[x1] = (b - a);
			//
			a = img[srow0+x+1], b = img[srow2+x+1];
			trow0[x1+1] = ((a + b) + (img[srow1+x+1] * 2));
			trow1[x1+1] = (b - a);
		}
		for (; x < w; ++x, ++x1) {
			a = img[srow0+x], b = img[srow2+x];
			trow0[x1] = ((a + b) + (img[srow1+x] * 2));
			trow1[x1] = (b - a);
		}
		// make border
		x = (w + 1);
		trow0[0] = trow0[1];
		trow0[x] = trow0[w];
		trow1[0] = trow1[1];
		trow1[x] = trow1[w];
		// do horizontal convolution, interleave the results and store them
		for (x = 0; x <= w - 4; x += 4) {
			a = trow1[x+2], b = trow1[x+1], c = trow1[x+3], d = trow1[x+4],
								e = trow0[x+2], f = trow0[x+3];
			gxgy[drow++] = (e - trow0[x]);
			gxgy[drow++] = (a + trow1[x] + b * 2);
			gxgy[drow++] = (f - trow0[x+1]);
			gxgy[drow++] = (c + b + a * 2);
			
			gxgy[drow++] = (trow0[x+4] - e);
			gxgy[drow++] = (d + a + c * 2);
			gxgy[drow++] = (trow0[x+5] - f);
			gxgy[drow++] = (trow1[x+5] + c + d * 2);
		}
		for (; x < w; ++x) {
			gxgy[drow++] = (trow0[x+2] - trow0[x]);
			gxgy[drow++] = (trow1[x+2] + trow1[x] + trow1[x+1] * 2);
		}
	}
	cache.put_buffer(buf0_node);
	cache.put_buffer(buf1_node);
},

// please note:
// dst_(type) size should be cols = src.cols+1, rows = src.rows+1
void compute_integral_image(src, dst_sum, dst_sqsum, dst_tilted) {
	var w0 = src.cols, h0 = src.rows, src_d = src.data;
	var w1 = (w0 + 1);
	//var s = 0, s2 = 0, p = 0, pup = 0, i = 0, j = 0, v = 0, k = 0;
	
	if (dst_sum && dst_sqsum) {
		// fill first row with zeros
		for (int i = 0; i < w1; ++i) {
			dst_sum[i] = 0, dst_sqsum[i] = 0;
		}
		int p = (w1 + 1), pup = 1;
		for (int i = 0, k = 0; i < h0; ++i, ++p, ++pup) {
			int s = 0;
			int s2 = 0;
			for (j = 0; j <= w0 - 2; j += 2, k += 2, p += 2, pup += 2) {
				v = src_d[k];
				s += v, s2 += v * v;
				dst_sum[p] = dst_sum[pup] + s;
				dst_sqsum[p] = dst_sqsum[pup] + s2;
				
				v = src_d[k+1];
				s += v, s2 += v * v;
				dst_sum[p+1] = dst_sum[pup+1] + s;
				dst_sqsum[p+1] = dst_sqsum[pup+1] + s2;
			}
			for (; j < w0; ++j, ++k, ++p, ++pup) {
				v = src_d[k];
				s += v, s2 += v * v;
				dst_sum[p] = dst_sum[pup] + s;
				dst_sqsum[p] = dst_sqsum[pup] + s2;
			}
		}
	}
	else
		if (dst_sum) {
			// fill first row with zeros
			for (int i = 0; i < w1; ++i) {
				dst_sum[i] = 0;
			}
			int p = (w1 + 1);
			int pup = 1;
			for (int i = 0, k = 0; i < h0; ++i, ++p, ++pup) {
				s = 0;
				int j;
				for (j = 0; j <= w0 - 2; j += 2, k += 2, p += 2, pup += 2) {
					s += src_d[k];
					dst_sum[p] = dst_sum[pup] + s;
					s += src_d[k+1];
					dst_sum[p+1] = dst_sum[pup+1] + s;
				}
				for (; j < w0; ++j, ++k, ++p, ++pup) {
					s += src_d[k];
					dst_sum[p] = dst_sum[pup] + s;
				}
			}
		}
		else
			if (dst_sqsum) {
				// fill first row with zeros
				for (int i = 0; i < w1; ++i) {
					dst_sqsum[i] = 0;
				}
				int p = (w1 + 1), pup = 1;
				for (int i = 0, k = 0; i < h0; ++i, ++p, ++pup) {
					int j;
					int s2 = 0;
					for (j = 0; j <= w0 - 2; j += 2, k += 2, p += 2, pup += 2) {
						v = src_d[k];
						s2 += v * v;
						dst_sqsum[p] = dst_sqsum[pup] + s2;
						v = src_d[k+1];
						s2 += v * v;
						dst_sqsum[p+1] = dst_sqsum[pup+1] + s2;
					}
					for (; j < w0; ++j, ++k, ++p, ++pup) {
						v = src_d[k];
						s2 += v * v;
						dst_sqsum[p] = dst_sqsum[pup] + s2;
					}
				}
			}
			
	if (dst_tilted) {
		// fill first row with zeros
		for (i = 0; i < w1; ++i) {
			dst_tilted[i] = 0;
		}
		// diagonal
		int p = (w1 + 1), pup = 0;
		for (int i = 0, k = 0; i < h0; ++i, ++p, ++pup) {
			for (j = 0; j <= w0 - 2; j += 2, k += 2, p += 2, pup += 2) {
				dst_tilted[p] = src_d[k] + dst_tilted[pup];
				dst_tilted[p+1] = src_d[k+1] + dst_tilted[pup+1];
			}
			for (; j < w0; ++j, ++k, ++p, ++pup) {
				dst_tilted[p] = src_d[k] + dst_tilted[pup];
			}
		}
		// diagonal
		p = (w1 + w0), pup = w0;
		for (int i = 0; i < h0; ++i, p += w1, pup += w1) {
			dst_tilted[p] += dst_tilted[pup];
		}
		
		for (int j = w0 - 1; j > 0; --j) {
			p = j + h0 * w1, pup = p - w1;
			for (int i = h0; i > 0; --i, p -= w1, pup -= w1) {
				dst_tilted[p] += dst_tilted[pup] + dst_tilted[pup+1];
			}
		}
	}
}

voidi equalize_histogram(src, dst) {
	int w = src.cols;
	int h = src.rows;
	int src_d = src.data;
	
	dst.Resize(w, h, src.channel);
	
	var dst_d = dst.data;
	int size = w * h;
	//var i = 0, prev = 0, hist0, norm;
	
	var hist0_node = cache.get_buffer(256 << 2);
	int hist0 = hist0_node.i32;
	for (int i = 0; i < 256; ++i)
		hist0[i] = 0;
	for (int i = 0; i < size; ++i) {
		++hist0[src_d[i]];
	}
	
	int prev = hist0[0];
	for (int i = 1; i < 256; ++i) {
		prev = hist0[i] += prev;
	}
	
	double norm = 255.0 / size;
	for (int i = 0; i < size; ++i) {
		dst_d[i] = (hist0[src_d[i]] * norm + 0.5);
	}
	cache.put_buffer(hist0_node);
},

void canny(src, dst, low_thresh, high_thresh) {
	int w = src.cols;
	int h = src.rows
			src_d = src.data;
	        
	dst.Resize(w, h, src.channel);
	
	var dst_d = dst.data;
	//var i = 0, j = 0, grad = 0, w2 = w << 1, _grad = 0, suppress = 0, f = 0, x = 0, y = 0, s = 0;
	//var tg22x = 0, tg67x = 0;
	
	// cache buffers
	var dxdy_node = cache.get_buffer((h * w2) << 2);
	var buf_node = cache.get_buffer((3 * (w + 2)) << 2);
	var map_node = cache.get_buffer(((h + 2) * (w + 2)) << 2);
	var stack_node = cache.get_buffer((h * w) << 2);
	
	
	var buf = buf_node.i32;
	var map = map_node.i32;
	var stack = stack_node.i32;
	var dxdy = dxdy_node.i32;
	matrix_t dxdy_m(w, h, S32C2_t, dxdy_node.data);
	int row0 = 1;
	int row1 = (w + 2 + 1);
	int row2 = (2 * (w + 2) + 1);
	int map_w = (w + 2);
	int map_i = (map_w + 1);
	int stack_i = 0;
	
	sobel_derivatives(src, dxdy_m);
	
	if (low_thresh > high_thresh) {
		i = low_thresh;
		low_thresh = high_thresh;
		high_thresh = i;
	}
	
	for (int i = (3 * (w + 2)); --i >= 0;) {
		buf[i] = 0;
	}
	
	for (int i = ((h + 2) * (w + 2)); --i >= 0;) {
		map[i] = 0;
	}
	
	for (int j = 0; j < w; ++j, grad += 2) {
		//buf[row1+j] = abs(dxdy[grad]) + abs(dxdy[grad+1]);
		x = dxdy[grad], y = dxdy[grad+1];
		//buf[row1+j] = x*x + y*y;
		buf[row1+j] = ((x ^(x >> 31)) - (x >> 31)) + ((y ^(y >> 31)) - (y >> 31));
	}
	
	for (int i = 1; i <= h; ++i, grad += w2) {
		if (i == h) {
			for (int j = row2 + w; --j >= row2;) {
				buf[j] = 0;
			}
		}
		else {
			for (int j = 0; j < w; j++) {
				//buf[row2+j] =  abs(dxdy[grad+(j<<1)]) + abs(dxdy[grad+(j<<1)+1]);
				x = dxdy[grad+(j<<1)], y = dxdy[grad+(j<<1)+1];
				//buf[row2+j] = x*x + y*y;
				buf[row2+j] = ((x ^(x >> 31)) - (x >> 31)) + ((y ^(y >> 31)) - (y >> 31));
			}
		}
		_grad = (grad - w2);
		map[map_i-1] = 0;
		suppress = 0;
		for (int j = 0; j < w; ++j, _grad += 2) {
			f = buf[row1+j];
			if (f > low_thresh) {
				x = dxdy[_grad];
				y = dxdy[_grad+1];
				s = x ^ y;
				// seems ot be faster than abs
				x = ((x ^(x >> 31)) - (x >> 31));
				y = ((y ^(y >> 31)) - (y >> 31));
				//x * tan(22.5) x * tan(67.5) == 2 * x + x * tan(22.5)
				tg22x = x * 13573;
				tg67x = tg22x + ((x + x) << 15);
				y <<= 15;
				if (y < tg22x) {
					if (f > buf[row1+j-1] && f >= buf[row1+j+1]) {
						if (f > high_thresh && !suppress && map[map_i+j-map_w] != 2) {
							map[map_i+j] = 2;
							suppress = 1;
							stack[stack_i++] = map_i + j;
						}
						else {
							map[map_i+j] = 1;
						}
						continue;
					}
				}
				else
					if (y > tg67x) {
						if (f > buf[row0+j] && f >= buf[row2+j]) {
							if (f > high_thresh && !suppress && map[map_i+j-map_w] != 2) {
								map[map_i+j] = 2;
								suppress = 1;
								stack[stack_i++] = map_i + j;
							}
							else {
								map[map_i+j] = 1;
							}
							continue;
						}
					}
					else {
						s = s < 0 ? -1 : 1;
						if (f > buf[row0+j-s] && f > buf[row2+j+s]) {
							if (f > high_thresh && !suppress && map[map_i+j-map_w] != 2) {
								map[map_i+j] = 2;
								suppress = 1;
								stack[stack_i++] = map_i + j;
							}
							else {
								map[map_i+j] = 1;
							}
							continue;
						}
					}
			}
			map[map_i+j] = 0;
			suppress = 0;
		}
		map[map_i+w] = 0;
		map_i += map_w;
		j = row0;
		row0 = row1;
		row1 = row2;
		row2 = j;
	}
	
	{
		int j = map_i - map_w - 1;
		for (i = 0; i < map_w; ++i, ++j) {
			map[j] = 0;
		}
	}
	
	// path following
	while (stack_i > 0) {
		map_i = stack[--stack_i];
		map_i -= map_w + 1;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
		map_i += 1;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
		map_i += 1;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
		map_i += map_w;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
		map_i -= 2;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
		map_i += map_w;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
		map_i += 1;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
		map_i += 1;
		if (map[map_i] == 1)
			map[map_i] = 2, stack[stack_i++] = map_i;
	}
	
	map_i = map_w + 1;
	row0 = 0;
	for (int i = 0; i < h; ++i, map_i += map_w) {
		for (int j = 0; j < w; ++j) {
			dst_d[row0++] = (map[map_i+j] == 2) * 0xff;
		}
	}
	
	// free buffers
	cache.put_buffer(dxdy_node);
	cache.put_buffer(buf_node);
	cache.put_buffer(map_node);
	cache.put_buffer(stack_node);
},

// transform is 3x3 matrix_t
void warp_perspective(src, dst, transform, int fill_value = 0) {
	var src_width = src.cols, src_height = src.rows, dst_width = dst.cols, dst_height = dst.rows;
	var src_d = src.data, dst_d = dst.data;
	var x = 0, y = 0, off = 0, ixs = 0, iys = 0, xs = 0.0, ys = 0.0, xs0 = 0.0, ys0 = 0.0, ws = 0.0, sc = 0.0, a = 0.0, b = 0.0, p0 = 0.0, p1 = 0.0;
	var td = transform.data;
	var m00 = td[0];
	m01 = td[1];
	m02 = td[2];
	m10 = td[3];
	m11 = td[4];
	m12 = td[5];
	m20 = td[6];
	m21 = td[7];
	m22 = td[8];
	
	for (int dptr = 0; y < dst_height; ++y) {
		xs0 = m01 * y + m02;
		ys0 = m11 * y + m12;
		ws  = m21 * y + m22;
		for (int x = 0; x < dst_width; ++x, ++dptr, xs0 += m00, ys0 += m10, ws += m20) {
			sc = 1.0 / ws;
			xs = xs0 * sc, ys = ys0 * sc;
			ixs = xs, iys = ys;
			
			if (xs > 0 && ys > 0 && ixs < (src_width - 1) && iys < (src_height - 1)) {
				a = max(xs - ixs, 0.0);
				b = max(ys - iys, 0.0);
				off = (src_width * iys + ixs);
				
				p0 = src_d[off] +  a * (src_d[off+1] - src_d[off]);
				p1 = src_d[off+src_width] + a * (src_d[off+src_width+1] - src_d[off+src_width]);
				
				dst_d[dptr] = p0 + b * (p1 - p0);
			}
			else
				dst_d[dptr] = fill_value;
		}
	}
}

// transform is 3x3 or 2x3 matrix_t only first 6 values referenced
void warp_affine(src, dst, transform, int fill_value = 0) {
	var src_width = src.cols, src_height = src.rows, dst_width = dst.cols, dst_height = dst.rows;
	var src_d = src.data, dst_d = dst.data;
	//var x = 0, y = 0, off = 0, ixs = 0, iys = 0;
	//xs = 0.0, ys = 0.0, a = 0.0, b = 0.0, p0 = 0.0, p1 = 0.0;
	var td = transform.data;
	var m00 = td[0], m01 = td[1], m02 = td[2],
			  m10 = td[3], m11 = td[4], m12 = td[5];
	          
	for (int dptr = 0; y < dst_height; ++y) {
		xs = m01 * y + m02;
		ys = m11 * y + m12;
		for (int x = 0; x < dst_width; ++x, ++dptr, xs += m00, ys += m10) {
			ixs = xs;
			iys = ys;
			
			if (ixs >= 0 && iys >= 0 && ixs < (src_width - 1) && iys < (src_height - 1)) {
				a = xs - ixs;
				b = ys - iys;
				off = src_width * iys + ixs;
				
				p0 = src_d[off] +  a * (src_d[off+1] - src_d[off]);
				p1 = src_d[off+src_width] + a * (src_d[off+src_width+1] - src_d[off+src_width]);
				
				dst_d[dptr] = p0 + b * (p1 - p0);
			}
			else
				dst_d[dptr] = fill_value;
		}
	}
}

// Basic RGB Skin detection filter
// from http://popscan.blogspot.fr/2012/08/skin-detection-in-digital-images.html
void skindetector(src, dst) {
	int i = src.width * src.height;
	while (i--) {
		int j = i * 4;
		int r = src.data[j];
		int g = src.data[j+1];
		int b = src.data[j+2];
		if ((r > 95) &&
			(g > 40) &&
			(b > 20) &&
			(r > g) &&
			(r > b) &&
			(r - min(g, b) > 15) &&
			(abs(r - g) > 15)) {
			dst[i] = 255;
		}
		else {
			dst[i] = 0;
		}
	}
}


#endif


NAMESPACE_TOPSIDE_END

#endif
