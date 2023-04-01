#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

void ForwardDCT1d(int values_size, const double* values, int size, double* params) {
	for(int i = 0; i < size; i++) {
		double part = (double)i / (double)values_size;
		double s = (i == 0) ? FastSqrt(0.5) : 1.0;
		double sum = 0;
		for(int j = 0; j < values_size; j++) {
			double v = s * values[j] * FastSin(M_PI * (j + 0.5) * part);
			sum += v;
		}
		params[i] = sum * FastSqrt(2.0 / (double)values_size);
	}
}



void BackwardDCT1d(int size, const double* params, int values_size, double* values) {
	double c0 = FastSqrt(0.5);
	double c1 = FastSqrt(2.0 / (double)values_size);
	for(int i = 0; i < values_size; i++) {
		double sum = 0;
		for(int j = 0; j < size; j++) {
			double part = (double)j / (double)values_size;
			double s = (j == 0) ? c0 : 1.0;
			sum += s * params[j] * FastSin(M_PI * (i + 0.5) * part);
		}
		values[i] = sum * c1;
	}
}

void ConvertToParamsHLine(const Vector<Pointf>& pts, int size, char* params) {
	if (pts.GetCount() < 2 || size <= 0) {
		for(int i = 0; i < size; i++)
			params[i] = 0;
		return;
	}
	
	const Pointf& begin = pts[0];
	const Pointf& end   = pts[pts.GetCount()-1];
	double width = end.x - begin.x;
	int widthi = (int)max(1.0, width + 0.5);
	
	MAKE_STATIC_LOCAL(Vector<double>, wave);
	MAKE_STATIC_LOCAL(Vector<double>, weight);
	MAKE_STATIC_LOCAL(Vector<double>, paramsf);
	wave.SetCount(widthi);
	weight.SetCount(widthi);
	paramsf.SetCount(size);
	for(double& y : wave) y = 0.0;
	for(double& w : weight) w = 0.0;
	for(const Pointf& pt : pts) {
		double paramf = pt.x - begin.x;
		double f = paramf - floor(paramf);
		int a = (int)paramf;
		int b = a + 1;
		if (a >= 0 && a < widthi) {
			double w = (1.0 - f);
			wave[a] += pt.y * w;
			weight[a] += w;
		}
		if (b >= 0 && b < widthi) {
			double w = f;
			wave[b] += pt.y * w;
			weight[b] += w;
		}
	}
	
	bool do_fix = false;
	double* w = weight.Begin();
	for(double& y : wave) {
		if (*w != 0.0)
			y /= *w;
		else
			do_fix = true;
		w++;
	}
	
	if (do_fix) {
		int i = 0;
		
		double* w_begin = weight.Begin();
		double* w_end = weight.End();
		double* w = w_begin;
		
		double* begin = wave.Begin();
		double* end = wave.End();
		double* y = begin;
		
		while(y != end) {
			if (*w == 0.0) {
				int closest = -1;
				int closest_dist = INT_MAX;
				int j = 0;
				double* w0 = w_begin;
				while(w0 != w_end) {
					int dist = abs(i - j);
					if (*w0 != 0 && dist < closest_dist) {
						closest_dist = dist;
						closest = j;
					}
					w0++;
					j++;
				}
				if (closest >= 0)
					*y = *(begin + closest);
			}
			i++, w++, y++;
		}
	}
	
	ForwardDCT1d(wave.GetCount(), wave.Begin(), size, paramsf.Begin());
	
	for(int i = 0; i < size; i++)
		params[i] = max(-127, min(127, (int)(paramsf[i] * param_mul_fwd + 0.5)));
}

void ConvertFromParamsHLine(int param_count, const char* params, int width, Vector<Pointf>& pts) {
	pts.SetCount(width);
	if(width < 2) {
		if (width == 1)
			pts[0] = Pointf(0,0);
		return;
	}
	
	static thread_local Vector<double> paramsf, wave;
	paramsf.SetCount(param_count);
	wave.SetCount(width);
	for(int i = 0; i < param_count; i++)
		paramsf[i] = params[i] * param_mul_bwd;
	
	BackwardDCT1d(param_count, paramsf.Begin(), width, wave.Begin());
	
	double* w = wave.Begin();
	int x = 0;
	for(Pointf& pt : pts) {
		pt.x = (double)x++;
		pt.y = (double)*w++;
	}
}

void ConvertToParamsLine(int point_count, const Point* pt, int size, char* params) {
	MAKE_STATIC_LOCAL(Vector<Pointf>, pts);
	
	const Point* begin = pt;
	const Point* end = pt + point_count - 1;
	Point diff = *end - *begin;
	//double len = FastSqrt((double)(diff.x * diff.x + diff.y * diff.y));
	//int steps = max((int)(max(diff.x, diff.y) / 2), 1);
	
	pts.SetCount(0);
	
	double line_angle = FastAtan2((float)diff.y, (float)diff.x);
	//double shift_angle = line_angle - M_PI / 2.0;
	
	const Point* it = begin;
	while (it != end) {
		if (it == begin) {
			pts.Add(Pointf(0,0));
		}
		else {
			Point diff = *it - *begin;
			double len = FastSqrt((double)(diff.x * diff.x + diff.y * diff.y));
			double pt_angle = FastAtan2((float)diff.y, (float)diff.x);
			double angle_diff = pt_angle - line_angle;
			if      (angle_diff < -M_PI) angle_diff += 2.0 * M_PI;
			else if (angle_diff > +M_PI) angle_diff -= 2.0 * M_PI;
			
			Pointf pt;
			pt.x = (double)FastCos(angle_diff) * len;
			pt.y = (double)-FastSin(angle_diff) * len;
			if (pt.x >= 0 && pt.x <= len)
				pts.Add(pt);
		}
		it++;
	}
	
	ConvertToParamsHLine(pts, size, params);
	
}

void ConvertFromParamsLineAppend(int param_count, const char* params, Point begin, Point end, Vector<Point>& pts) {
	MAKE_STATIC_LOCAL(Vector<Pointf>, hline);
	Point diff = end - begin;
	//double len = FastSqrt((double)(diff.x * diff.x + diff.y * diff.y));
	int steps = max((int)(max(diff.x, diff.y) / 2), 1);
	
	ConvertFromParamsHLine(param_count, params, steps, hline);
	
	pts.SetCount(pts.GetCount() + steps);
	
	Pointf step;
	step.x = (double)(diff.x / steps);
	step.y = (double)(diff.y / steps);
	Pointf it;
	it.x = (double)begin.x;
	it.y = (double)begin.y;
	double shift_angle = FastAtan2((float)diff.y, (float)diff.x) - M_PI / 2.0;
	Pointf shift(FastCos(shift_angle), FastSin(shift_angle));
	
	Pointf* hit = hline.Begin();
	Point* dst = pts.End() - steps;
	for(int i = 0; i < steps; i++) {
		Pointf pt = it;
		pt.x += hit->y * shift.x;
		pt.y += hit->y * shift.y;
		*dst = pt;
		
		it += step;
		hit++;
		dst++;
	}
	
	
}





// Length of input and output is 8
void ForwardDCT1d8LLM(const double* in, double* out) {
	// Constants:
	const double s1 = FastSin(1. * M_PI / 16.);
	const double c1 = FastCos(1. * M_PI / 16.);
	const double s3 = FastSin(3. * M_PI / 16.);
	const double c3 = FastCos(3. * M_PI / 16.);
	const double r2s6 = FastSqrt(2.) * FastSin(6. * M_PI / 16.);
	const double r2c6 = FastSqrt(2.) * FastCos(6. * M_PI / 16.);
	
	// After stage 1:
	const double s1_0 =  in[0] + in[7];
	const double s1_1 =  in[1] + in[6];
	const double s1_2 =  in[2] + in[5];
	const double s1_3 =  in[3] + in[4];
	const double s1_4 = -in[4] + in[3];
	const double s1_5 = -in[5] + in[2];
	const double s1_6 = -in[6] + in[1];
	const double s1_7 = -in[7] + in[0];
	
	// After stage 2:
	const double s2_0 =  s1_0 + s1_3;
	const double s2_1 =  s1_1 + s1_2;
	const double s2_2 = -s1_2 + s1_1;
	const double s2_3 = -s1_3 + s1_0;
	
	const double z1 = c3 * (s1_7 + s1_4);
	const double s2_4 = ( s3-c3) * s1_7 + z1;
	const double s2_7 = (-s3-c3) * s1_4 + z1;
	
	const double z2 = c1 * (s1_6 + s1_5);
	const double s2_5 = ( s1-c1) * s1_6 + z2;
	const double s2_6 = (-s1-c1) * s1_5 + z2;
	
	// After stage 3:
	const double s3_0 =  s2_0 + s2_1;
	const double s3_1 = -s2_1 + s2_0;
	
	const double z3 = r2c6 * (s2_3 + s2_2);
	const double s3_2 = ( r2s6-r2c6) * s2_3 + z3;
	const double s3_3 = (-r2s6-r2c6) * s2_2 + z3;
	
	const double s3_4 =  s2_4 + s2_6;
	const double s3_5 = -s2_5 + s2_7;
	const double s3_6 = -s2_6 + s2_4;
	const double s3_7 =  s2_7 + s2_5;
	
	// After stage 4:
	const double s4_4 = -s3_4 + s3_7;
	const double s4_5 =  s3_5 * FastSqrt(2.);
	const double s4_6 =  s3_6 * FastSqrt(2.);
	const double s4_7 =  s3_7 + s3_4;
	
	// Shuffle and scaling:
	out[0] = s3_0 / FastSqrt(8.);
	out[4] = s3_1 / FastSqrt(8.);
	out[2] = s3_2 / FastSqrt(8.);
	out[6] = s3_3 / FastSqrt(8.);
	out[7] = s4_4 / FastSqrt(8.);
	out[3] = s4_5 / FastSqrt(8.);  // Alternative: s3_5 / 2
	out[5] = s4_6 / FastSqrt(8.);
	out[1] = s4_7 / FastSqrt(8.);
}

// Length of input and output is 8
void ForwardDCT1d8AAN(const double* i, double* o) {
#if 1
	const double a1 = FastSqrt(0.5);
	const double a2 = FastSqrt(2.) * FastCos(3. / 16. * 2 * M_PI);
	const double a3 = a1;
	const double a4 = FastSqrt(2.) * FastCos(1. / 16. * 2 * M_PI);
	const double a5 = FastCos(3. / 16. * 2 * M_PI);
#else
	const double a1 = 0.707;
	const double a2 = 0.541;
	const double a3 = 0.707;
	const double a4 = 1.307;
	const double a5 = 0.383;
#endif
	
	double b0 = i[0] + i[7];
	double b1 = i[1] + i[6];
	double b2 = i[2] + i[5];
	double b3 = i[3] + i[4];
	double b4 = -i[4] + i[3];
	double b5 = -i[5] + i[2];
	double b6 = -i[6] + i[1];
	double b7 = -i[7] + i[0];
	
	double c0 = b0 + b3;
	double c1 = b1 + b2;
	double c2 = -b2 + b1;
	double c3 = -b3 + b0;
	double c4 = -b4 - b5;
	double c5 = b5 + b6;
	double c6 = b6 + b7;
	double c7 = b7;
	
	double d0 = c0 + c1;
	double d1 = -c1 + c0;
	double d2 = c2 + c3;
	double d3 = c3;
	double d4 = c4;
	double d5 = c5;
	double d6 = c6;
	double d7 = c7;
	
	double d8 = (d4 + d6) * a5;
	
	double e0 = d0;
	double e1 = d1;
	double e2 = d2 * a1;
	double e3 = d3;
	double e4 = -d4 * a2 - d8;
	double e5 = d5 * a3;
	double e6 = d6 * a4 - d8;
	double e7 = d7;
	
	double f0 = e0;
	double f1 = e1;
	double f2 = e2 + e3;
	double f3 = e3 - e2;
	double f4 = e4;
	double f5 = e5 + e7;
	double f6 = e6;
	double f7 = e7 - e5;
	
	double g0 = f0;
	double g1 = f1;
	double g2 = f2;
	double g3 = f3;
	double g4 = f4 + f7;
	double g5 = f5 + f6;
	double g6 = -f6 + f5;
	double g7 = f7 - f4;
	
	const double s0 = (FastCos(0.) * FastSqrt(0.5) / 2) / (1);   // 0.353553
	const double s1 = (FastCos(1.*M_PI / 16) / 2) / (-a5 + a4 + 1);  // 0.254898
	const double s2 = (FastCos(2.*M_PI / 16) / 2) / (a1 + 1);  // 0.270598
	const double s3 = (FastCos(3.*M_PI / 16) / 2) / (a5 + 1);  // 0.300672
	const double s4 = s0;  // (FastCos(4.*M_PI/16)/2)/(1       );
	const double s5 = (FastCos(5.*M_PI / 16) / 2) / (1 - a5);  // 0.449988
	const double s6 = (FastCos(6.*M_PI / 16) / 2) / (1 - a1);  // 0.653281
	const double s7 = (FastCos(7.*M_PI / 16) / 2) / (a5 - a4 + 1);  // 1.281458
	
	
	o[0] = g0 * s0;
	o[4] = g1 * s4;
	o[2] = g2 * s2;
	o[6] = g3 * s6;
	o[5] = g4 * s5;
	o[1] = g5 * s1;
	o[7] = g6 * s7;
	o[3] = g7 * s3;
}



NAMESPACE_TOPSIDE_END
