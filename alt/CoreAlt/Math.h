#ifndef _CoreAlt_Math_h_
#define _CoreAlt_Math_h_

NAMESPACE_UPP_BEGIN


struct Complex : public std::complex<double>, Moveable<Complex> {
	typedef std::complex<double> cmx;

	Complex()                              {}
	Complex(double r) : cmx(r)             {}
	Complex(double r, double i) : cmx(r,i) {}
	Complex(const cmx& c) : cmx(c)         {}
	
	bool operator==(const Complex& c) const { return (const cmx&)(*this) == (const cmx&)c; }
	bool operator!=(const Complex& c) const { return (const cmx&)(*this) != (const cmx&)c; }
	
};


template <class T>
int NumberCompare__(const T& a, const T& b)
{
	if(a < b) return -1;
	if(a > b) return 1;
	return 0;
}

inline int SgnCompare(const int& a, const int& b)                         { return NumberCompare__(a, b); }
inline int SgnCompare(const int64& a, const int64& b)                     { return NumberCompare__(a, b); }
inline int SgnCompare(const double& a, const double& b)                   { return NumberCompare__(a, b); }


NAMESPACE_UPP_END

#endif
