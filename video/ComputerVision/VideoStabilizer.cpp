#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


int get_ring_ind(int idx, int len) {
	if( idx < 0 ) idx -= (((idx-len+1)/len)*len);
	if( idx >= len ) idx %= len;
    return idx;
}

void get_motion(FloatMat& M, int from, int to, Vector<FloatMat>& motions) {
	M.SetSize(3,3,1);
	
    int i=0;
    int n = motions.GetCount();

    identity_3x3(M, 1.0f);

    if (to > from) {
        for (i = from; i < to; ++i) {
			multiply_3x3(M, get_at(i, n, motions), M);
        }
    }
    else if (from > to) {
        for (i = to; i < from; ++i) {
            multiply_3x3(M, get_at(i, n, motions), M);
        }
        invert_3x3(M, M);
    }
    
}


NAMESPACE_TOPSIDE_END
