#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN



void gauss_motion_filter::setup(int radius, double stdev) {
    this->radius = radius;
    this->stdev = stdev > 0.0 ? stdev : sqrt(radius);
    
    weight.SetCount(2 * radius + 1);

    double sum = 0.0;
    double stdev2 = stdev*stdev;
    int i = -radius;
    for (; i <= radius; ++i) {
        sum += weight[radius + i] = exp(-i*i/(stdev2));
    }
    for (i = -radius; i <= radius; ++i) {
        weight[radius + i] /= sum;
    }
    
    m33.SetSize(3,3,1);
}


FloatMat& gauss_motion_filter::stabilize(int idx, Vector<FloatMat>& motions, int from_idx, int to_idx) {
    FloatMat cur;
    FloatMat& res = m33;
    Vector<float>& resd = res.data;
    double sum = 0.0, val=0.0;
    int iMin = max(idx - radius, from_idx);
    int iMax = min(idx + radius, to_idx);
    int i = iMin;

    double res0=0.0,res1=0.0,res2=0.0;
    double res3=0.0,res4=0.0,res5=0.0;
    double res6=0.0,res7=0.0,res8=0.0;

    for (; i <= iMax; ++i) {
		val = weight[radius + i - idx];
		get_motion(cur, idx, i, motions);
		auto& curd = cur.data;
        res0 += val * curd[0]; res1 += val * curd[1]; res2 += val * curd[2];
        res3 += val * curd[3]; res4 += val * curd[4]; res5 += val * curd[5];
        res6 += val * curd[6]; res7 += val * curd[7]; res8 += val * curd[8];
        sum += val;
    }
    
    if(sum > 0.0) {
		sum = 1.0 / sum;
		resd[0]=res0*sum; resd[1]=res1*sum; resd[2]=res2*sum;
		resd[3]=res3*sum; resd[4]=res4*sum; resd[5]=res5*sum;
		resd[6]=res6*sum; resd[7]=res7*sum; resd[8]=res8*sum;
    }
    else {
		identity_3x3(res, 1.0f);
    }
    
    return res;
}


NAMESPACE_TOPSIDE_END
