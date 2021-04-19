#ifndef _Math_Common_h_
#define _Math_Common_h_

NAMESPACE_OULU_BEGIN


inline float Determinant3(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3) {
	return	a1 * (b2 * c3 - b3 * c2) -
			b1 * (a2 * c3 - a3 * c2) +
			c1 * (a2 * b3 - a3 * b2);
}


NAMESPACE_OULU_END

#endif
