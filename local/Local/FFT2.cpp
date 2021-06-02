#include "Local.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;

FFT2::FFT2(const Image& input )
{
	orig_sz = input.GetSize();
	Image img = GetSquareImage(input);
	
	CopyToImageBuffer(img, obj);
	Size sz(img.GetSize());
	width = nx = sz.cx;
	height = ny = sz.cy;
	ReadImage();
}

FFT2::FFT2(const Vector<Vector<int> >& input )
{
	this->input <<= input;
	width = nx = input.GetCount();
	height = ny = input[0].GetCount();
}

FFT2::FFT2(const Vector<Vector<Complex> >& input )
{
	nx = width = input.GetCount();
	ny = height = input[0].GetCount();
	fourier <<= input;
}

void FFT2::ReadImage()
{
	Resize2D(input, width, height);
	ImageBuffer image = obj;
	Size sz = image.GetSize();
	
	const RGBA* it = image.Begin();
	for(int i = 0; i < sz.cy; i++ )
	{
		for(int j = 0; j < sz.cx; j++ )
		{
			input[j][i] = (it->r + it->g + it->b) / 3.0;
			it++;
		}
	}
}

void FFT2::DisplayImage(Vector<Vector<int> >& image, ImageBuffer& output)
{
	int width = image.GetCount();
	int height = image[0].GetCount();
	
	output.Clear();
	output.Create(width, height);
	
	RGBA* it = output.Begin();
	for(int i = 0; i < height; i++ )
	{
		for(int j = 0; j < width; j++ )
		{
			int value = image[j][i];
			if (value > 255) value = 255;
			it->a = 255;
			it->r = value;
			it->g = value;
			it->b = value;
			it++;
		}
	}
}

void FFT2::ForwardFFT2()
{
	Resize2D(fourier, width, height);
	for (int i = 0;i < width; i++ ) {
		for (int j = 0; j < height; j++ )
		{
			fourier[i][j].real(input[i][j]);
			fourier[i][j].imag(0);
		}
	}
	FFT22D(fourier, output, nx, ny, 1);
}

void FFT2::InverseFFT2()
{
	FFT22D(fft_normal, output, nx, ny, -1);
	
	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			input[i][j] = Magnitude(output[i][j]);
		}
	}
	DisplayImage(input, obj);
}

void FFT2::FFT2Shift()
{
	Resize2D(fft_shifted, nx, ny);

	for(int i = 0; i < (nx / 2); i++ ) {
		for(int j = 0; j < (ny / 2); j++ )
		{
			fft_shifted[i +(nx / 2 )][j +(ny / 2 ) ] = output[i][j];
			fft_shifted[i][j] = output[i +(nx / 2 )][j + (ny / 2 )];
			fft_shifted[i +(nx / 2 )][j] = output[i][j + (ny / 2 )];
			fft_shifted[i][j +(nx / 2 ) ] = output[i +(nx / 2 )][j];
		}
	}
}

void FFT2::RemoveFFT2Shift()
{
	Resize2D(fft_normal, nx, ny);

	for(int i = 0; i < (nx / 2); i++ ) {
		for(int j = 0; j < (ny / 2); j++ )
		{
			fft_normal[i +(nx / 2 )][j +(ny / 2 ) ] = fft_shifted[i][j];
			fft_normal[i][j] = fft_shifted[i +(nx / 2 )][j +(ny / 2 ) ];
			fft_normal[i +(nx / 2 )][j] = fft_shifted[i][j +(ny / 2 ) ];
			fft_normal[i][j +(nx / 2 ) ] = fft_shifted[i +(nx / 2 )][j];
		}
	}
}

void FFT2::FFT2Plot(const Vector<Vector<Complex> >& output )
{
	double max;

	Resize2D(fft_log, nx, ny);
	Resize2D(fft_phase_log, nx, ny);

	Resize2D(fourier_magnitude, nx, ny);
	Resize2D(fourier_phase, nx, ny);

	Resize2D(fft_normalized, nx, ny);
	Resize2D(fft_phase_normalized, nx, ny);

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			fourier_magnitude[i][j] = Magnitude(output[i][j]);
			fourier_phase[i][j] = Phase(output[i][j]);
			fft_log[i][j] = log(1 + fourier_magnitude[i][j]);
			fft_phase_log[i][j] = log(1 + fabs(fourier_phase[i][j] ));
		}
	}

	max = fft_log[0][0];

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			if(fft_log[i][j] > max )
				max = fft_log[i][j];
		}
	}

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			fft_log[i][j] = fft_log[i][j] / max;
		}
	}

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			fft_normalized[i][j] = 2000 * fft_log[i][j];
		}
	}
	
	DisplayImage(fft_normalized, fourier_plot);
	fft_phase_log[0][0] = 0;

	max = fft_phase_log[1][1];

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			if(fft_phase_log[i][j] > max )
				max = fft_phase_log[i][j];
		}
	}

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			fft_phase_log[i][j] = fft_phase_log[i][j] / max;
		}
	}

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height; j++ )
		{
			fft_phase_normalized[i][j] = 255 * fft_phase_log[i][j];
		}
	}

	DisplayImage(fft_phase_normalized, phase_plot);
}


void FFT2::FFT22D(const Vector<Vector<Complex> >& c, Vector<Vector<Complex> >& output, int nx, int ny, int dir )
{
	int m;
	Vector<double> real;
	Vector<double> imag;
	
	output <<= c;
	real.SetCount(nx) ;
	imag.SetCount(nx);

	for(int j = 0;j < ny;j++ )
	{
		for(int i = 0;i < nx;i++ )
		{
			real[i] = c[i][j].real();
			imag[i] = c[i][j].imag();
		}

		m = log2(nx);

		FFT1D(dir, m, real, imag);

		for(int i = 0; i < nx;i++ )
		{
			output[i][j].real(real[i]);
			output[i][j].imag(imag[i]);
		}
	}

	real.SetCount(ny);
	imag.SetCount(ny);

	for(int i = 0;i < nx;i++ )
	{
		for(int j = 0;j < ny;j++ )
		{
			real[j] = output[i][j].real();
			imag[j] = output[i][j].imag();
		}

		m = log2(ny);

		FFT2D(dir, m, real, imag);

		for(int j = 0;j < ny;j++ )
		{
			output[i][j].real(real[j]);
			output[i][j].imag(imag[j]);
		}
	}
}

void FFT2::FFT21D(int dir, int m, Vector<double>& x, Vector<double>&  y )
{
	int nn, i1, k, i2, l, l1, l2;
	double c1, c2, tx, ty, t1, t2, u1, u2, z;
	/* Calculate the number of points */
	nn = 1;

	for(int i = 0; i < m; i++ )
		nn *= 2;

	/* Do the bit reversal */
	i2 = nn >> 1;

	int j = 0;

	for(int i = 0; i < nn - 1; i++ )
	{
		if(i < j )
		{
			tx = x[i];
			ty = y[i];
			x[i] = x[j];
			y[i] = y[j];
			x[j] = tx;
			y[j] = ty;
		}

		k = i2;

		while(k <= j )
		{
			j -= k;
			k >>= 1;
		}

		j += k;
	}

	/* Compute the FFT2 */
	c1 = -1.0;

	c2 = 0.0;

	l2 = 1;

	for(l = 0; l < m; l++ )
	{
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;

		for(j = 0; j < l1; j++ )
		{
			for(int i = j; i < nn; i += l2 )
			{
				i1 = i + l1;
				t1 = u1 * x[i1] - u2 * y[i1];
				t2 = u1 * y[i1] + u2 * x[i1];
				x[i1] = x[i] - t1;
				y[i1] = y[i] - t2;
				x[i] += t1;
				y[i] += t2;
			}

			z = u1 * c1 - u2 * c2;

			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}

		c2 = sqrt(( 1.0 - c1 ) / 2.0);

		if(dir == 1 )
			c2 = -c2;

		c1 = sqrt(( 1.0 + c1 ) / 2.0);
	}

	/* Scaling for forward transform */

	if(dir == 1 )
	{
		for(int i = 0; i < nn; i++ )
		{
			x[i] /= nn;
			y[i] /= nn;

		}
	}
}

void FFT2::MultiplyShift(const Image& mask) {
	Size mask_sz = mask.GetSize();
	if (mask_sz.cx != width || mask_sz.cy != height)
		return;
	
	const RGBA* it = mask.Begin();
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			Complex& c = fft_shifted[j][i];
			c.real(c.real() * it->a / 255);
			c.imag(c.imag() * it->a / 255);
			it++;
		}
	}
}






Image GetImageFromSquared(const Image& img, Size orig_sz) {
	Size img_sz = img.GetSize();
	if (img_sz == orig_sz) return img;
	
	int x_off = img_sz.cx / 2 - orig_sz.cx / 2;
	int y_off = img_sz.cy / 2 - orig_sz.cy / 2;
	
	ImageBuffer ib(orig_sz);
	
	const RGBA *begin = img.Begin(), *end = img.End();
	const RGBA *src = begin;
	RGBA *dst_begin = ib.Begin(), *dst_end = ib.End();
	RGBA *dest = dst_begin;
	for(int i = 0; i < img_sz.cy; i++) {
		for(int j = 0; j < img_sz.cx; j++) {
			int x = j - x_off;
			int y = i - y_off;
			if (x >= 0 && x < orig_sz.cx && y >= 0 && y < orig_sz.cy) {
				*dest = *src;
				dest++;
			}
			src++;
			
			if (src == end || dest == dst_end) return ib;
		}
	}
	
	return ib;
}

Image GetSquareImage(const Image& img) {
	Size sz(img.GetSize());
	int bigger_side = max(sz.cx, sz.cy);
	int p2 = 1;
	while (p2 < bigger_side) p2 *= 2;
	int x_off = p2 / 2 - sz.cx / 2;
	int y_off = p2 / 2 - sz.cy / 2;
	
	int64 average = 0;
	const RGBA *begin, *it, *end;
	begin = img.Begin();
	end = img.End();
	for (it = begin; it != end; it++) {
		average += it->r + it->g + it->b;
	}
	average /= sz.cx * sz.cy * 3;
	
	ImageBuffer ib(p2, p2);
	RGBA *dst_begin = ib.Begin(), *dst_it, *dst_end = ib.End();
	
	it = begin;
	dst_it = dst_begin;
	for(int i = 0; i < p2; i++) {
		for(int j = 0; j < p2; j++) {
			int x = j - x_off;
			int y = i - y_off;
			if (x >= 0 && x < sz.cx && y >= 0 && y < sz.cy) {
				*dst_it = *it;
				it++;
			} else {
				dst_it->a = 255;
				dst_it->r = average;
				dst_it->g = average;
				dst_it->b = average;
			}
			dst_it++;
		}
	}
	
	return ib;
}

NAMESPACE_TOPSIDE_END

#endif
