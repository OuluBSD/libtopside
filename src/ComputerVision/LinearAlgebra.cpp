#include "ComputerVision.h"



NAMESPACE_TOPSIDE_BEGIN


void EigenVV(const FloatMat& A, FloatMat* vects, FloatMat* vals) {
	ASSERT(vects || vals);
	int n = A.cols;
	int dt = 1;
	
	static thread_local FloatMat a_mt;
	static thread_local FloatMat w_mt;
	a_mt.SetSize(n, n, dt);
	w_mt.SetSize(1, n, dt);
	
	ASSERT(a_mt.data.GetCount() == A.data.GetCount());
	memcpy(a_mt.data.Begin(), A.data.Begin(), sizeof(float) * a_mt.data.GetCount());
	
	JacobiImpl(a_mt.data, n, w_mt.data, (vects ? &vects->data : NULL), n, n);
	
	if (vals) {
		ASSERT(vals->data.GetCount() == w_mt.data.GetCount());
		memcpy(w_mt.data.Begin(), vals->data.Begin(), sizeof(float) * vals->data.GetCount());
	}
}


NAMESPACE_TOPSIDE_END
