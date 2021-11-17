#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN



keypoint_motion_estimator::keypoint_motion_estimator(int motionModel) :
	mm_kernel(motionModel == MM_AFFINE ? (TransformationKernel&)aff : (TransformationKernel&)homo),
	motionModel(motionModel)
{
	
}

void keypoint_motion_estimator::Init(Size size) {
	// ransac params
	ransac_param.Init(4, 2, 0.5, 0.99);
	
	if (motionModel == MM_AFFINE) {
		ransac_param.size = 3;
	}

	// transform matrix
	mm3x3.SetSize(3,3,1);

	// pyr flow LK
	curr_img_pyr.SetSize(size.cx, size.cy, 1, 3);
    prev_img_pyr.SetSize(size.cx, size.cy, 1, 3);

    max_points = 100;
    point_count = 0;
    point_status.SetCount(max_points);
    prev_xy.SetCount(max_points*2);
    curr_xy.SetCount(max_points*2);

    match_mask.SetSize(max_points,1,1);

    corners0.SetCount(0);
    corners1.SetCount(0);
    int i = (size.cx*size.cy) >> 1;
    for (auto& c: corners0) c.Clear();
    for (auto& c: corners1) c.Clear();
};

const FloatMat& keypoint_motion_estimator::estimate(ByteMat& frame0, ByteMat& frame1) {
	ASSERT(!prev_img_pyr.IsEmpty());
	ASSERT(!curr_img_pyr.IsEmpty());
	
	// update pyramids
    //frame0.copy_to(prev_img_pyr.data[0]);
    //frame1.copy_to(curr_img_pyr.data[0]);
    box_blur_gray(frame0, prev_img_pyr.data[0], 2, 0);
    box_blur_gray(frame1, curr_img_pyr.data[0], 2, 0);

	// find keypoints
    int count = y.detect(prev_img_pyr.data[0], corners0);
    if(count > max_points) {
		Sort(corners0, keypoint_t());
		count = max_points;
    }

    //LOG("keypoints: " + count + " [" + corners0[0].score + ", " + corners0[10].score + "]");

    // extract coords from keypoints
    int i=0;
    for (; i < count; ++i) {
        prev_xy[i<<1] = corners0[i].x;
        prev_xy[(i<<1)+1] = corners0[i].y;
    }

    curr_img_pyr.Build(curr_img_pyr.data[0], true);
    prev_img_pyr.Build(prev_img_pyr.data[0], true);

    // find correspondences
    int lk_win = 20;
	int lk_iters = 30;
    double lk_epsilon = 0.01;
    double lk_min_eigen = 0.001;
	of.track(prev_img_pyr, curr_img_pyr, prev_xy, curr_xy, count,
		  lk_win|0, lk_iters|0, point_status, lk_epsilon, lk_min_eigen);

    // leave good correspondences only

    int good_cnt = 0;
    corners1.SetCount(0);
    corners1.Reserve(1024);
    for (i = 0; i < count; ++i) {
        if (point_status[i]) {
            const auto& f0 = corners0[i];
            auto& c0 = corners0[good_cnt];
            auto& c1 = corners1.Add();
			c0.x = f0.x;
			c0.y = f0.y;
			
			c1.x = curr_xy[i<<1];
			c1.y = curr_xy[(i<<1)+1];
			
			good_cnt++;
        }
    }
	corners0.SetCount(good_cnt);
	
	
    //LOG("lk tracked: " + good_cnt);

    // perform outlier rejection
    // todo or not todo

    // estimate motion
    bool ok = false;
    if (motionModel == MM_AFFINE) {
		ok = aff_me.ransac(ransac_param, aff,
						   corners0, corners1, mm3x3, &match_mask, 1000);
    } else {
		ok = homo_me.lmeds(ransac_param, homo,
						   corners0, corners1, mm3x3, &match_mask, 1000);
    }

	// extract good matches and re-etimate
	if (ok && good_cnt > 15) {
		count = good_cnt;
		good_cnt = 0;
		for(i=0; i < count; ++i) {
			if(match_mask.data[i]) {
				corners0[good_cnt].x = corners0[i].x;
				corners0[good_cnt].y = corners0[i].y;
				corners1[good_cnt].x = corners1[i].x;
				corners1[good_cnt].y = corners1[i].y;
				good_cnt++;
			}
		}
		corners0.SetCount(good_cnt);
		corners1.SetCount(good_cnt);
		//LOG("mask: " + good_cnt);
		mm_kernel.run(corners0, corners1, mm3x3);
	}
	else {
		identity_3x3(mm3x3, 1.0f);
	}
	
	return mm3x3;
}


NAMESPACE_TOPSIDE_END
