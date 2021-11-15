#include "ComputerVision.h"



NAMESPACE_TOPSIDE_BEGIN


void eigenVV(const FloatMat& A, const FloatMat* vects, const FloatMat* vals) {
	ASSERT(vects || vals);
	int n = A.cols;
	int dt = 1;
	
	FloatMat a_mt(n, n, dt);
	FloatMat w_mt(1, n, dt);
	
	int i = n * n;
	while (--i >= 0) {
		a_mt.data[i] = A.data[i];
	}
	
	JacobiImpl(a_mt.data, n, w_mt.data, vects ? vects.data : NULL, n, n);
	
	if (vals) {
		while (--n >= 0) {
			vals.data[n] = w_mt.data[n];
		}
	}
}


NAMESPACE_TOPSIDE_END
