#ifndef _Local_DCT_h_
#define _Local_DCT_h_

NAMESPACE_TOPSIDE_BEGIN

static constexpr double param_mul_bwd = 4.0;
static constexpr double param_mul_fwd = 1.0 / param_mul_bwd;

void ForwardDCT1d(int values_size, const double* values, int size, double* params);
void BackwardDCT1d(int size, const double* params, int values_size, double* values);
void ConvertToParamsHLine(const Vector<Pointf>& pts, int size, char* params);
void ConvertFromParamsHLine(int param_count, const char* params, int width, Vector<Pointf>& pts);
void ConvertToParamsLine(int point_count, const Point* pt, int size, char* params);
void ConvertFromParamsLineAppend(int param_count, const char* params, Point begin, Point end, Vector<Point>& pts);

// Length of input and output is 8
void ForwardDCT1d8LLM(const double* i, double* o);
void ForwardDCT1d8AAN(const double* i, double* o);

NAMESPACE_TOPSIDE_END

#endif
