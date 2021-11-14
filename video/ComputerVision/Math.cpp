#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


double hypot(double a, double b) {
	a = abs(a);
	b = abs(b);
	if (a > b) {
		b /= a;
		return a * FastSqrt(1.0 + b*b);
	}
	if (b > 0) {
		a /= b;
		return b * FastSqrt(1.0 + a*a);
	}
	return 0.0;
}

bool lu_solve(matrix_t<float>& A, matrix_t<float>& B) {
	//var i = 0, j = 0, k = 0, p = 1;
	int astep = A.cols;
	Vector<float>& ad = A.data;
	Vector<float>& bd = B.data;
	//var t, alpha, d, s;
	float t;
	int p = 1;
	
	for (int i = 0; i < astep; i++) {
		int k = i;
		for (int j = i + 1; j < astep; j++) {
			if (abs(ad[j*astep + i]) > abs(ad[k*astep+i])) {
				k = j;
			}
		}
		
		if (abs(ad[k*astep+i]) < EPSILON) {
			return false; // FAILED
		}
		
		if (k != i) {
			for (int j = i; j < astep; j++) {
				Swap(ad, i*astep + j, k*astep + j, t);
			}
			
			Swap(bd, i, k, t);
			p = -p;
		}
		
		double d = -1.0 / ad[i*astep+i];
		
		for (int j = i + 1; j < astep; j++) {
			int c = (int)(j*astep+i);
			double alpha = ad[c] * d;
			
			for (int k = i + 1; k < astep; k++) {
				int a = (int)(j*astep+k);
				int b = (int)(i*astep+k);
				ad[a] += (float)(alpha * ad[b]);
			}
			
			bd[j] += (float)(alpha * bd[i]);
		}
		
		ad[i*astep+i] = (float)-d;
	}
	
	for (int i = astep - 1; i >= 0; i--) {
		double s = bd[i];
		for (int k = i + 1; k < astep; k++) {
			s -= ad[i*astep+k] * bd[k];
		}
		bd[i] = (float)(s * ad[i*astep+i]);
	}
	
	return true; // OK
}


NAMESPACE_TOPSIDE_END
