#ifndef _Core_Complex_h_
#define _Core_Complex_h_

NAMESPACE_UPP_BEGIN


#undef Complex

struct Complex : public std::complex<double>, Moveable<Complex> {
	typedef std::complex<double> cmx;

	Complex()                              {}
	Complex(double r) : cmx(r)             {}
	Complex(double r, double i) : cmx(r,i) {}
	Complex(const cmx& c) : cmx(c)         {}
	
	bool operator==(const Complex& c) const { return (const cmx&)(*this) == (const cmx&)c; }
	bool operator!=(const Complex& c) const { return (const cmx&)(*this) != (const cmx&)c; }
	
};

inline bool IsFin(float f)	{return ::isfinite(f);}
inline bool IsNaN(double d)	{return std::isnan(d);}
inline bool IsInf(double d)	{return std::isinf(d);}
inline bool IsFin(double d)	{return !IsNaN(d) && !IsInf(d);}

NAMESPACE_UPP_END

#endif
