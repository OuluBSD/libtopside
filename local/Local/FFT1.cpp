#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;



FFT1::FFT1()
{
	orig_sz = Size(0,0);
	length = 0;
}

FFT1::FFT1(const Vector<float>& input )
{
	this->input <<= input;
	length = input.GetCount();
}

FFT1::FFT1(const Vector<Complex>& input )
{
	length = input.GetCount();
	fourier <<= input;
}

void FFT1::ForwardFFT()
{
	Resize1D(fourier, length);
	float* in = input.Begin();
	for(Complex& c : fourier) {
		c.real(*in++);
		c.imag(0);
	}
	Process(fourier, output, 1);
}

void FFT1::InverseFFT()
{
	Process(fft_normal, output, -1);
	float* in = input.Begin();
	for(const Complex& c : output) {
		*in++ = Magnitude(c);
	}
}

void FFT1::FFTShift()
{
	Resize1D(fft_shifted, length);
	
	int half = length / 2;
	Complex* c = fft_shifted.Begin();
	Complex* o = output.Begin();
	Complex* c0 = c;
	Complex* c1 = c + half;
	Complex* o0 = o + half;
	Complex* o1 = o;
	for(int i = 0; i < half; i++ ) {
		*c0++ = *o0++;
		*c1++ = *o1++;
	}
}

void FFT1::RemoveFFTShift()
{
	Resize1D(fft_normal, length);
	
	int half = length / 2;
	Complex* c = fft_normal.Begin();
	Complex* o = fft_shifted.Begin();
	Complex* c0 = c;
	Complex* c1 = c + half;
	Complex* o0 = o + half;
	Complex* o1 = o;
	for(int i = 0; i < half; i++ ) {
		*c0++ = *o0++;
		*c1++ = *o1++;
	}
}

/*
void FFT1::FFTPlot(const Vector<Complex>& src )
{
	Resize1D(fft_log, ni);
	Resize1D(fft_phase_log, ni);
	
	Resize1D(fourier_magnitude, ni);
	Resize1D(fourier_phase, ni);
	
	Resize1D(fft_normalized, ni);
	Resize1D(fft_phase_normalized, ni);
	
	const Complex* o = src.Begin();
	float* fmag = fourier_magnitude.Begin();
	float* fpha = fourier_phase.Begin();
	float* flog = fft_log.Begin();
	float* fplog = fft_phase_log.Begin();
	for(int i = 0; i < length; i++ ) {
		*fmag = Magnitude(*o);
		*fpha = Phase(*o++);
		*flog++ = log_fast(1 + *fmag++);
		*fplog++ = log_fast(1 + fabs(*fpha++));
	}
	
	float max = -FLT_MAX;
	for(float& f : fft_log)
		max = std::max(max, f);
	
	float* fn = fft_normalized.Begin();
	for(float& f : fft_log) {
		f /= max;
		*fn++ = 2000 * f;
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
*/

void FFT1::Process(const Vector<Complex>& input, Vector<Complex>& output, int dir )
{
	ASSERT(input.GetCount() == length);
	output.SetCount(length);
	int m = (int)log2(length);
	FFT1D(dir, m, input, output);
}

void FFT1::FFT1D(int dir, int m, const Vector<Complex>& input, Vector<Complex>& output)
{
	const Complex* in = input.Begin();
	Complex* out = output.Begin();
	
	int nn, i1, k, i2, l, l1, l2;
	double c1, c2, t1, t2, u1, u2, z;
	
	// Calculate the number of points
	nn = 1;

	for(int i = 0; i < m; i++ )
		nn *= 2;

	// Do the bit reversal
	i2 = nn >> 1;

	int j = 0;

	for(int i = 0; i < nn - 1; i++ )
	{
		if(i < j )
		{
			const Complex& ii = in[i];
			const Complex& ij = in[j];
			Complex& oi = out[i];
			Complex& oj = out[j];
			oj = ii;
			oi = ij;
		}

		k = i2;

		while(k <= j )
		{
			j -= k;
			k >>= 1;
		}

		j += k;
	}

	// Compute the FFT
	c1 = -1.0;

	c2 = 0.0;

	l2 = 1;

	for(l = 0; l < m; l++ )
	{
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;

		for(j = 0; j < l1; j++) {
			for(int i = j; i < nn; i += l2) {
				i1 = i + l1;
				Complex& ci1 = out[i1];
				Complex& ci = out[i];
				t1 = u1 * -u2 * ci1.imag();
				t2 = u1 * ci1.imag() + u2 * ci1.real();
				ci1.real(ci.real() - t1);
				ci1.imag(ci.imag() - t2);
				ci.real(ci.real() + t1);
				ci.imag(ci.imag() + t2);
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

	// Scaling for forward transform

	if (dir == 1) {
		for (Complex& c : output) {
			c.real(c.real());
			c.imag(c.imag());
		}
		/*for(int i = 0; i < nn; i++ )
		{
			x[i] /= nn;
			y[i] /= nn;
		}*/
	}
}

float FFT1::GetMagnitude(int pos) const {
	return Magnitude(output[pos]);
}





NAMESPACE_TOPSIDE_END
