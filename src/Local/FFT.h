#ifndef _Local_FFT_h_
#define _Local_FFT_h_

NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;

#if 1
inline float Magnitude(const Complex& c) {
	float r = (float)c.real();
	float i = (float)c.imag();
	return powf_fast(r * r + i * i, 0.5f);
}
#else
inline double Magnitude(const Complex& c) {
	double r = c.real();
	double i = c.imag();
	return pow_fast(r * r + i * i, 0.5);
}
#endif

inline double Phase(const Complex& c) {
	return atan(c.imag() / c.real());
}

Image GetImageFromSquared(const Image& img, Size orig_sz);
Image GetSquareImage(const Image& img);

template <class T>
void CopyToImageBuffer(const T& src, ImageBuffer& dest) {
	dest.Clear();
	dest.Create(src.GetSize());
	const RGBA* src_it = src.Begin();
	const RGBA* src_end = src.End();
	RGBA* dest_it = dest.Begin();
	while (src_it != src_end) {
		*dest_it = *src_it;
		src_it++;
		dest_it++;
	}
}

class FFT1 : Moveable<FFT1> {
	Vector<Complex> fourier;
	Vector<Complex> fft_shifted;
	Vector<Complex> output;
	Vector<Complex> fft_normal;
	Vector<float>   fourier_magnitude;
	Vector<float>   fourier_phase;
	Vector<float>   fft_log;
	Vector<float>   fft_phase_log;
	Vector<float>   input;
	Vector<float>   fft_normalized;
	Vector<float>   fft_phase_normalized;
	int length;
	Size orig_sz;
	
public:
	FFT1();
	FFT1(const Vector<float>& input);
	FFT1(const Vector<Complex>& input);

	void ForwardFFT();
	void FFTShift();
	void RemoveFFTShift();
	void InverseFFT();
	void Process(const Vector<Complex>& input, Vector<Complex>& output, int dir);
	void FFT1D(int dir, int m, const Vector<Complex>& input, Vector<Complex>& output);
	
	const Vector<Complex>& GetFFTShifted() const {return fft_shifted;}
	int GetLength()  const{return length;}
	float GetMagnitude(int pos) const;
	
};



class FFT2 : Moveable<FFT2> {
	Vector<Vector<Complex> > fourier;
	Vector<Vector<Complex> > fft_shifted;
	Vector<Vector<Complex> > output;
	Vector<Vector<Complex> > fft_normal;
	Vector<Vector<double> >  fourier_magnitude;
	Vector<Vector<double> >  fourier_phase;
	Vector<Vector<double> >  fft_log;
	Vector<Vector<double> >  fft_phase_log;
	Vector<Vector<int> >     input;
	Vector<Vector<int> >     fft_normalized;
	Vector<Vector<int> >     fft_phase_normalized;
	ImageBuffer obj;
	ImageBuffer fourier_plot;
	ImageBuffer phase_plot;
	int nx, ny, width, height;
	Size orig_sz;
	
public:
	FFT2() {}
	FFT2(const Image& input);
	FFT2(const Vector<Vector<int> >& input);
	FFT2(const Vector<Vector<Complex> >& input);

	void ReadImage();

	void DisplayImage(Vector<Vector<int> >& image, ImageBuffer& buffer);

	void ForwardFFT();
	void FFTShift();
	void RemoveFFTShift();
	void FFTPlot(const Vector<Vector<Complex> >& output);
	void FFTPlotShifted() {FFTPlot(fft_shifted);}
	void InverseFFT();
	void FFT2D(const Vector<Vector<Complex> >& c, Vector<Vector<Complex> >& output, int nx, int ny, int dir);
	void FFT1D(int dir, int m, Vector<double>&  x, Vector<double>&  y);
	
	const Vector<Vector<Complex> >& GetFFTShifted() const {return fft_shifted;}
	int GetWidth() const {return width;}
	void MultiplyShift(const Image& mask) const;
	double GetMagnitude(int pos) const;
	
};

NAMESPACE_TOPSIDE_END

#endif
