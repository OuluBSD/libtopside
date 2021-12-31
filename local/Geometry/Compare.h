#ifndef _Geometry_Compare_h_
#define _Geometry_Compare_h_

NAMESPACE_TOPSIDE_BEGIN


union Float_t {
	Float_t(float num = 0.0f) : f(num) {}
	
	bool Negative() const;
	int32 GetRawMantissa() const;
	int32 GetRawExponent() const;

	int32 i;
	float f;
#ifdef _DEBUG
	struct {
		uint32 mantissa : 23;
		uint32 exponent : 8;
		uint32 sign : 1;
	} parts;
#endif
};

bool AlmostEqualRelative(float A, float B, float max_rel_diff = FLT_EPSILON);
bool AlmostEqualUlpsAndAbs(float A, float B, float max_diff, int max_ulps_diff);
bool AlmostEqualRelativeAndAbs(float A, float B, float max_diff, float max_rel_diff = FLT_EPSILON);
bool CMP(float x, float y);

NAMESPACE_TOPSIDE_END

#endif
