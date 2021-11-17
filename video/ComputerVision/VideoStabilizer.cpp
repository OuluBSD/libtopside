#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


int GetRingIndex(int idx, int len) {
	if( idx < 0 ) idx -= (((idx-len+1)/len)*len);
	if( idx >= len ) idx %= len;
    return idx;
}

void GetMotion(FloatMat& M, int from, int to, Vector<FloatMat>& motions) {
	M.SetSize(3,3,1);
	
    int i=0;
    int n = motions.GetCount();

    Identity3x3(M, 1.0f);

    if (to > from) {
        for (i = from; i < to; ++i) {
			Multiply3x3(M, GetAt(i, n, motions), M);
        }
    }
    else if (from > to) {
        for (i = to; i < from; ++i) {
            Multiply3x3(M, GetAt(i, n, motions), M);
        }
        Invert3x3(M, M);
    }
    
}


NAMESPACE_TOPSIDE_END
