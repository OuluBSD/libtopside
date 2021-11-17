#ifndef _ComputerVision_ImageProcessing_h_
#define _ComputerVision_ImageProcessing_h_


NAMESPACE_TOPSIDE_BEGIN


void Grayscale(const ByteMat& src, ByteMat& dst);


void ResampleByte(const pyra8::Mat& src, pyra8::Mat& dst, int nw, int nh);
void ResampleFloat(const pyraf::Mat& src, pyraf::Mat& dst, int nw, int nh);



template <class T,class Temp>
void ConvoluteByte(Vector<Temp>& buf, const Vector<T>& src_d, Vector<T>& dst_d, int w, int h, Vector<double>& filter, int kernel_size, int half_kernel) {
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


template <class T,class Temp>
void Convolute(Vector<Temp>& buf, const Vector<T>& src_d, Vector<T>& dst_d, int w, int h, Vector<double>& filter, int kernel_size, int half_kernel) {
	int  w2 = w << 1, w3 = w * 3, w4 = w << 2;
	double f0 = filter[0];
	
	// hor pass
	for (int i = 0, sp = 0, dp = 0; i < h; ++i) {
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
					sum  += buf[k + j]   * fk;
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
				int sum = buf[j] * f0;
				for (int k = 1; k < kernel_size; ++k) {
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
				sum = buf[j] * f0;
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
				dst_d[dp] = sum;
				dst_d[dp+w] = sum1;
				dst_d[dp+w2] = sum2;
				dst_d[dp+w3] = sum3;
			}
			for (; j < h; ++j, dp += w) {
				sum = buf[j] * f0;
				for (int k = 1; k < kernel_size; ++k) {
					sum += buf[k + j] * filter[k];
				}
				dst_d[dp] = sum;
			}
		}
	}
}


void Resample(const pyra8::Mat& src, pyra8::Mat& dst, int nw, int nh);
void Resample(const pyraf::Mat& src, pyraf::Mat& dst, int nw, int nh);


void BoxBlurGray(ByteMat& src, ByteMat& dst, int radius, dword options = 0);

template <class T=byte, class Temp=int> // <byte, int>, <float, float>
void GaussianBlur(const DMatrix<T>& src, DMatrix<T>& dst, int kernel_size = 0, double sigma = 0.0) {
	if (kernel_size == 0)
		kernel_size = (int)(max<double>(1, (4.0 * sigma + 1.0 - 1e-8)) * 2 + 1);
		
	int half_kernel = kernel_size >> 1;
	int w = src.cols;
	int h = src.rows;
	
	dst.SetSize(w, h, src.channels);
	
	auto& src_d = src.data;
	auto& dst_d = dst.data;
	
	int buf_sz = (kernel_size + max(h, w));
	Vector<Temp> buf;
	Vector<double> filter;
	
	buf.SetCount(buf_sz << 2);
	filter.SetCount(kernel_size);
	
	GetGaussianKernel(kernel_size, sigma, filter);
	
	if (std::is_same<T, byte>::value) {
		ConvoluteByte<T,Temp>(buf, src_d, dst_d, w, h, filter, kernel_size, half_kernel);
	}
	else {
		Convolute<T,Temp>(buf, src_d, dst_d, w, h, filter, kernel_size, half_kernel);
	}
}

template <class T>
Vector<Pointf> HoughTransform(DMatrix<T>& img, double rho_res, double theta_res, double threshold) {
	auto& image = img.data;
	
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
				//LOG(r, (n+1) * (numrho+2) + r+1, tabCos[n], tabSin[n]);
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


template <class T, class P>
void ScharrDerivatives(const P& src, DMatrix<T>& dst) {
	int w = src.cols;
	int h = src.rows;
	int dstep = w << 1;
	int srow0 = 0, srow1 = 0, srow2 = 0, drow = 0;
	thread_local static Vector<T> trow0, trow1;
	trow0.SetCount((w + 2) << 2);
	trow1.SetCount((w + 2) << 2);

	dst.SetSize(w, h, 2); // 2 channel output gx, gy
	
	const auto& img = src.data;
	auto& gxgy = dst.data;
	
	for (int y = 0; y < h; ++y, srow1 += w) {
		srow0 = ((y > 0 ? y - 1 : 1) * w);
		srow2 = ((y < h - 1 ? y + 1 : h - 2) * w);
		drow = (y * dstep);
		
		// do vertical convolution
		int x, x1;
		for (x = 0, x1 = 1; x <= w - 2; x += 2, x1 += 2) {
			{
				auto& a = img[srow0+x];
				auto& b = img[srow2+x];
				trow0[x1] = ((a + b) * 3 + (img[srow1+x]) * 10);
				trow1[x1] = (b - a);
			} {
				auto& a = img[srow0+x+1];
				auto& b = img[srow2+x+1];
				trow0[x1+1] = ((a + b) * 3 + (img[srow1+x+1]) * 10);
				trow1[x1+1] = (b - a);
			}
		}
		for (; x < w; ++x, ++x1) {
			auto& a = img[srow0+x];
			auto& b = img[srow2+x];
			trow0[x1] = ((a + b) * 3 + (img[srow1+x]) * 10);
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
			auto& a = trow1[x+2];
			auto& b = trow1[x+1];
			auto& c = trow1[x+3];
			auto& d = trow1[x+4];
			auto& e = trow0[x+2];
			auto& f = trow0[x+3];
			
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
	
}

// compute gradient using Sobel kernel [1 2 1] * [-1 0 1]^T
// dst: [gx,gy,...]
template <class T=byte, class Temp=int>
void SobelDerivatives(const DMatrix<T>& src, DMatrix<Temp>& dst) {
	int w = src.cols;
	int h = src.rows;
	int dstep = w << 1;
	Temp a, b, c, d, e, f;
	int srow0 = 0, srow1 = 0, srow2 = 0, drow = 0;
	Vector<Temp> trow0;
	Vector<Temp> trow1;
	
	dst.SetSize(w, h, 2); // 2 channel output gx, gy
	trow0.SetCount((w + 2) << 2);
	trow1.SetCount((w + 2) << 2);
	
	auto& img = src.data;
	auto& gxgy = dst.data;
	
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
}

// please note:
// dst_(type) size should be cols = src.cols+1, rows = src.rows+1
template <class T>
void ComputeIntegralImage(const DMatrix<T>& src, Vector<int>& dst_sum, Vector<int>* dst_sqsum, Vector<int>* dst_tilted) {
	int w0 = src.cols, h0 = src.rows;
	auto& src_d = src.data;
	int w1 = (w0 + 1);
	int h1 = (h0 + 1);
	int s = 0, s2 = 0, p = 0, pup = 0, i = 0, j = 0, v = 0, k = 0;
	auto& sq = *dst_sqsum;
	
	if (dst_sum && dst_sqsum) {
		// fill first row with zeros
		dst_sum.SetCount(w1*h1);
		sq.SetCount(w1*h1);
		for (auto& v : dst_sum) v = 0;
		for (auto& v : sq) v = 0;
		
		int p = (w1 + 1), pup = 1;
		for (int i = 0, k = 0; i < h0; ++i, ++p, ++pup) {
			int s = 0;
			int s2 = 0;
			for (j = 0; j <= w0 - 2; j += 2, k += 2, p += 2, pup += 2) {
				v = src_d[k];
				s += v, s2 += v * v;
				dst_sum[p] = dst_sum[pup] + s;
				sq[p] = sq[pup] + s2;
				
				v = src_d[k+1];
				s += v, s2 += v * v;
				dst_sum[p+1] = dst_sum[pup+1] + s;
				sq[p+1] = sq[pup+1] + s2;
			}
			for (; j < w0; ++j, ++k, ++p, ++pup) {
				v = src_d[k];
				s += v, s2 += v * v;
				dst_sum[p] = dst_sum[pup] + s;
				sq[p] = sq[pup] + s2;
			}
		}
	}
	else if (dst_sum) {
		// fill first row with zeros
		dst_sum.SetCount(w1*h1);
		for (auto& v : dst_sum) v = 0;
		
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
	else if (dst_sqsum) {
		auto& sq = *dst_sqsum;
		
		// fill first row with zeros
		sq.SetCount(w1*h1);
		for (auto& v : sq) v = 0;
		
		int p = (w1 + 1), pup = 1;
		for (int i = 0, k = 0; i < h0; ++i, ++p, ++pup) {
			int j;
			int s2 = 0;
			for (j = 0; j <= w0 - 2; j += 2, k += 2, p += 2, pup += 2) {
				v = src_d[k];
				s2 += v * v;
				sq[p] = sq[pup] + s2;
				v = src_d[k+1];
				s2 += v * v;
				sq[p+1] = sq[pup+1] + s2;
			}
			for (; j < w0; ++j, ++k, ++p, ++pup) {
				v = src_d[k];
				s2 += v * v;
				sq[p] = sq[pup] + s2;
			}
		}
	}
			
	if (dst_tilted) {
		auto& dt = *dst_tilted;
		
		// fill first row with zeros
		dt.SetCount(w1*h1);
		for (auto& v : dt) v = 0;
		
		// diagonal
		int p = (w1 + 1), pup = 0;
		for (int i = 0, k = 0; i < h0; ++i, ++p, ++pup) {
			for (j = 0; j <= w0 - 2; j += 2, k += 2, p += 2, pup += 2) {
				dt[p] = src_d[k] + dt[pup];
				dt[p+1] = src_d[k+1] + dt[pup+1];
			}
			for (; j < w0; ++j, ++k, ++p, ++pup) {
				dt[p] = src_d[k] + dt[pup];
			}
		}
		// diagonal
		p = (w1 + w0), pup = w0;
		for (int i = 0; i < h0; ++i, p += w1, pup += w1) {
			dt[p] += dt[pup];
		}
		
		for (int j = w0 - 1; j > 0; --j) {
			p = j + h0 * w1, pup = p - w1;
			for (int i = h0; i > 0; --i, p -= w1, pup -= w1) {
				dt[p] += dt[pup] + dt[pup+1];
			}
		}
	}
}

template <class T>
void EqualizeHistogram(const DMatrix<T>& src, DMatrix<T>& dst) {
	int w = src.cols;
	int h = src.rows;
	auto& src_d = src.data;
	
	dst.SetSize(w, h, src.channels);
	
	auto& dst_d = dst.data;
	int size = w * h;
	
	static thread_local Vector<int> hist0;
	hist0.SetCount(256 << 2);
	
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
		dst_d[i] = (T)(hist0[src_d[i]] * norm + 0.5);
	}
}

template <class T>
void Canny(const DMatrix<T>& src, DMatrix<T>& dst, int low_thresh, int high_thresh) {
	int w = src.cols;
	int h = src.rows;
	auto& src_d = src.data;
	        
	dst.SetSize(w, h, src.channels);
	
	auto& dst_d = dst.data;
	int i = 0, j = 0, grad = 0;
	int w2 = w << 1, _grad = 0, suppress = 0, f = 0, x = 0, y = 0, s = 0;
	int tg22x = 0, tg67x = 0;
	
	// cache buffers
	static thread_local Vector<int> buf;
	static thread_local Vector<int> map;
	static thread_local Vector<int> stack;
	
	buf.SetCount((3 * (w + 2)) << 2);
	map.SetCount(((h + 2) * (w + 2)) << 2);
	stack.SetCount((h * w) << 2);
	
	DMatrix<int> dxdy_m(w, h, 2);
	auto& dxdy = dxdy_m.data;
	int row0 = 1;
	int row1 = (w + 2 + 1);
	int row2 = (2 * (w + 2) + 1);
	int map_w = (w + 2);
	int map_i = (map_w + 1);
	int stack_i = 0;
	
	SobelDerivatives(src, dxdy_m);
	
	if (low_thresh > high_thresh) {
		i = low_thresh;
		low_thresh = high_thresh;
		high_thresh = i;
	}
	
	memset(buf.Begin(), 0, buf.GetCount() * sizeof(int));
	memset(map.Begin(), 0, map.GetCount() * sizeof(int));
	
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
				uint32 u = ((x ^(x >> 31)) - (x >> 31)) + ((y ^(y >> 31)) - (y >> 31));
				buf[row2+j] = u;
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
				else if (y > tg67x) {
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
	
}

// transform is 3x3 DMatrix
void WarpPerspective(const ByteMat& src, ByteMat& dst, const FloatMat& transform, int fill_value = 0);


// transform is 3x3 or 2x3 DMatrix only first 6 values referenced
void WarpAffine(const ByteMat& src, ByteMat& dst, const FloatMat& transform, int fill_value = 0);

// Basic RGB Skin detection filter
// from http://popscan.blogspot.fr/2012/08/skin-detection-in-digital-images.html
template <class T>
void SkinDetector(const DMatrix<T>& src, DMatrix<T>& dst) {
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



NAMESPACE_TOPSIDE_END

#endif
