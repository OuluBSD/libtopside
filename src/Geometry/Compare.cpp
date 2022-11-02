#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


bool Float_t::Negative() const { return i < 0; }
int32 Float_t::GetRawMantissa() const { return i & ((1 << 23) - 1); }
int32 Float_t::GetRawExponent() const { return (i >> 23) & 0xFF; }


bool AlmostEqualRelative(float A, float B, float max_rel_diff) {
	float diff = fabs(A - B);
	A = fabs(A);
	B = fabs(B);
	float largest = (B > A) ? B : A;

	if (diff <= largest * max_rel_diff) {
		return true;
	}
	return false;
}

bool AlmostEqualUlpsAndAbs(float A, float B, float max_diff, int max_ulps_diff) {
	float absDiff = fabs(A - B);
	if (absDiff <= max_diff) {
		return true;
	}

	Float_t uA(A);
	Float_t uB(B);

	if (uA.Negative() != uB.Negative()) {
		return false;
	}

	int ulpsDiff = abs(uA.i - uB.i);
	if (ulpsDiff <= max_ulps_diff)
		return true;

	return false;
}

bool AlmostEqualRelativeAndAbs(float A, float B, float max_diff, float max_rel_diff) {
	float diff = fabs(A - B);
	if (diff <= max_diff) {
		return true;
	}

	A = fabs(A);
	B = fabs(B);
	float largest = (B > A) ? B : A;

	if (diff <= largest * max_rel_diff) {
		return true;
	}
	return false;
}

bool CMP(float x, float y) {return AlmostEqualRelativeAndAbs(x, y, 0.005f);}


NAMESPACE_TOPSIDE_END
