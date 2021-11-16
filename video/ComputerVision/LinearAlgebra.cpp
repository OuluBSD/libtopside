#include "ComputerVision.h"



NAMESPACE_TOPSIDE_BEGIN


void eigenVV(const FloatMat& A, FloatMat* vects, FloatMat* vals) {
	ASSERT(vects || vals);
	int n = A.cols;
	int dt = 1;
	
	FloatMat a_mt(n, n, dt);
	FloatMat w_mt(1, n, dt);
	
	int i = n * n;
	while (--i >= 0) {
		a_mt.data[i] = A.data[i];
	}
	
	JacobiImpl(a_mt.data, n, w_mt.data, (vects ? &vects->data : NULL), n, n);
	
	if (vals) {
		ASSERT(vals->data.GetCount() == w_mt.data.GetCount());
		memcpy(w_mt.data.Begin(), vals->data.Begin(), sizeof(float) * vals->data.GetCount());
	}
}


NAMESPACE_TOPSIDE_END
