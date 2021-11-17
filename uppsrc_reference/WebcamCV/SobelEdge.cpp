#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void SobelEdgeBase::Process() {
	auto& img_u8 = tmp1;

    Grayscale(input, tmp0);
    
    GaussianBlur(tmp0, img_u8, 3);
    
    SobelDerivatives(img_u8, img_gxgy);
    
    int i = img_u8.cols*img_u8.rows, gx = 0, gy = 0;
    int x=0,y=0,dx=0,dy=0;
    int agx=0, agy=0;
    
    auto& gd=img_gxgy.data;
    auto& mag=img_mag.data;
    auto& id=img_u8.data;
	img_mag.SetSize(img_u8.cols, img_u8.rows, 1);
	
    while(--i >= 0) {
        gx = gd[i<<1];
        gy = gd[(i<<1)+1];
        mag[i] = gx*gx + gy*gy;
    }

    for(y = 1; y < img_u8.rows - 1; ++y) {
        i = (y * img_u8.cols + 1);
        for(x = 1 ; x < img_u8.cols - 1; ++x, ++i) {

            gx = gd[i<<1];
            gy = gd[(i<<1)+1];
            agx = ((gx ^ (gx >> 31)) - (gx >> 31));
            agy = ((gy ^ (gy >> 31)) - (gy >> 31));

            if(gx > 0) dx = 1;
            else dx = -1;

            if(gy > 0) dy = img_u8.cols;
            else dy = -img_u8.cols;

            int a1, a2, b1, b2, A, B, point;
            if(agx > agy) {
                a1 = mag[i+dx];
                a2 = mag[i+dx+(-dy)];
                b1 = mag[i-dx];
                b2 = mag[i-dx+dy];
                A = (agx - agy)*a1 + agy*a2;
                B = (agx - agy)*b1 + agy*b2;
                point = mag[i] * agx;
                if(point >= A && point > B) {
                    id[i] = agx&0xff;
                }
                else {
                    id[i] = 0x0;
                }
            } else  {
                a1 = mag[i+(-dy)];
                a2 = mag[i+dx+(-dy)];
                b1 = mag[i+dy];
                b2 = mag[i-dx+dy];
                A = (agy - agx)*a1 + agx*a2;
                B = (agy - agx)*b1 + agx*b2;
                point = mag[i] * agy;
                if(point >= A && point > B) {
                    id[i] = agy&0xff;
                }
                else {
                    id[i] = 0x0;
                }
            }
        }
    }


    OutputFromGray(img_u8);
}


NAMESPACE_TOPSIDE_END
