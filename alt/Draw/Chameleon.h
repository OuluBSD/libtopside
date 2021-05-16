#ifndef _DrawAlt_Chameleon_h_
#define _DrawAlt_Chameleon_h_

NAMESPACE_UPP


template <class T>
struct ChStyle {
	byte status;
	byte registered;
	T   *standard;

	const T& Standard() const      { return *standard; }
	T&       Write() const         { T& x = *(T *)this; x.status = 2; return x; }
	void     Assign(const T& src)  { *(T *)this = src; }

	ChStyle()                      { status = 0; registered = 0; standard = NULL; }
};


END_UPP_NAMESPACE

#endif
