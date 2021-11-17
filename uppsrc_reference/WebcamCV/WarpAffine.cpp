#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


WarpAffineBase::WarpAffineBase() {
	mat_affine.SetSize(3,2,1);
    mat_affine.data[0] = 1.1548494156391083;
    mat_affine.data[1] = 0.4783542904563622;
    mat_affine.data[2] = -164.3568427140416;
    mat_affine.data[3] = -0.4783542904563622;
    mat_affine.data[4] = 1.1548494156391083;
    mat_affine.data[5] = 115.90951319264985;
    
}

void WarpAffineBase::Process() {
    Grayscale(input, tmp0);
    
    WarpAffine(tmp0, tmp1, mat_affine, 0);
    
    OutputFromGray(tmp1);
}


NAMESPACE_TOPSIDE_END
