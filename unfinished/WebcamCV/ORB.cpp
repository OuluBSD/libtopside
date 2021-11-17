#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


void match_t::Set(int screen_idx, int pattern_lev, int pattern_idx, int distance) {
    this->screen_idx = screen_idx;
    this->pattern_lev = pattern_lev;
    this->pattern_idx = pattern_idx;
    this->distance = distance;
}



void OrbBase::train_pattern() {
	const auto& img_u8 = input;
	auto& lev0_img = tmp0;
	auto& lev_img = tmp1;
	auto& pattern_preview = tmp2;
    double sc = 1.0;
    int max_pattern_size = 512;
    int max_per_level = 300;
    double sc_inc = sqrt(2.0);
    lev0_img.SetSize(img_u8.cols, img_u8.rows, 1);
    lev_img.SetSize(img_u8.cols, img_u8.rows, 1);
    int new_width=0, new_height=0;
    int corners_num=0;

    int sc0 = min(max_pattern_size/img_u8.cols, max_pattern_size/img_u8.rows);
    new_width = (img_u8.cols*sc0);
    new_height = (img_u8.rows*sc0);

    resample(img_u8, lev0_img, new_width, new_height);

    // prepare preview
    pattern_preview.SetSize(new_width>>1, new_height>>1, 1);
    DownsamplePyramid(lev0_img, pattern_preview);
	
	pattern_corners.SetCount(num_train_levels);
	pattern_descriptors.SetCount(num_train_levels);
    for(int lev=0; lev < num_train_levels; ++lev) {
        Vector<keypoint_t>& lev_corners = pattern_corners[lev];

        // preallocate corners array
        int i = (new_width*new_height) >> lev;
        lev_corners.SetCount(i);
        while(--i >= 0) {
            lev_corners[i].Set(0,0,0,0,-1);
        }

        pattern_descriptors[lev].SetCount(max_per_level);
    }

    // do the first level
    {
	    Vector<keypoint_t>& lev_corners = pattern_corners[0];
	    Vector<BinDescriptor>& lev_descr = pattern_descriptors[0];
	
	    gaussian_blur(lev0_img, lev_img, blur_size); // this is more robust
	    corners_num = detect_keypoints(lev_img, lev_corners, max_per_level);
	    ASSERT(lev_corners.GetCount() == corners_num);
	    o.describe(lev_img, lev_corners, lev_descr);
	
	    LOG("train " << lev_img.cols << "x" << lev_img.rows << " points: " << corners_num);
	
	    sc /= sc_inc;
    }
    
    // lets do multiple scale levels
    // we can use Canvas context draw method for faster SetSize
    // but its nice to demonstrate that you can do everything with jsfeat
    for(int lev = 1; lev < num_train_levels; ++lev) {
        Vector<keypoint_t>& lev_corners = pattern_corners[lev];
        Vector<BinDescriptor>& lev_descr = pattern_descriptors[lev];

        int new_width = (int)(lev0_img.cols*sc);
        int new_height = (int)(lev0_img.rows*sc);

        resample(lev0_img, lev_img, new_width, new_height);
        gaussian_blur(lev_img, lev_img, blur_size);
        corners_num = detect_keypoints(lev_img, lev_corners, max_per_level);
        ASSERT(lev_corners.GetCount() == corners_num);
        o.describe(lev_img, lev_corners, lev_descr);

        // fix the coordinates due to scale level
        for (keypoint_t& corner : lev_corners) {
            corner.x = (int)(corner.x * 1./sc);
            corner.y = (int)(corner.y * 1./sc);
        }

        LOG("train " << lev_img.cols << "x" << lev_img.rows << " points: " << corners_num);

        sc /= sc_inc;
    }
}

void OrbBase::InitDefault() {
	auto& videoWidth = sz.cx;
	auto& videoHeight = sz.cy;

	match_threshold = 24;
	
    /*img_u8 = new jsfeat.matrix_t(sz.cx, sz.cy, jsfeat.U8_t | jsfeat.C1_t);
    // after blur
    img_u8_smooth = new jsfeat.matrix_t(sz.cx, sz.cy, jsfeat.U8_t | jsfeat.C1_t);*/
    
    // we wll limit to 500 strongest points
    screen_descriptors.Reserve(500);
    pattern_descriptors.SetCount(0);

    pattern_corners.SetCount(0);
    matches.SetCount(0);

    int i = 640*480;
    matches.SetCount(i);
    screen_corners.SetCount(i);
    for (keypoint_t& k : screen_corners)
        k.Set(0,0,0,0,-1);

    // transform matrix
    homo3x3.SetSize(3,3,1);
    match_mask.SetSize(500,1,1);
    
    Grayscale(input, tmp0);
    resample(tmp0, train_img, sz.cx * 0.25, sz.cy * 0.25);
    
    train_pattern();
    
}

void OrbBase::Process() {
	auto& img_u8 = tmp0;
	auto& img_u8_smooth = tmp1;
	auto& pattern_preview = tmp2;
	
    Grayscale(input, img_u8);
    
    gaussian_blur(img_u8, img_u8_smooth, blur_size);

    y.laplacian_threshold = lap_thres;
    y.min_eigen_value_threshold = eigen_thres;

    int num_corners = detect_keypoints(img_u8_smooth, screen_corners, 500);
    ASSERT(num_corners == screen_corners.GetCount());
    o.describe(img_u8_smooth, screen_corners, screen_descriptors);

    render_corners(img_u8, &train_img, screen_corners, output);

    // render pattern and matches
    int num_matches = match_pattern();
    ASSERT(matches.GetCount() == num_matches);
    int good_matches = find_transform(matches);
    
    if(num_matches) {
        render_matches(matches);
        if(good_matches > 8)
            render_pattern_shape();
    }
}


int OrbBase::detect_keypoints(const ByteMat& img, Vector<keypoint_t>& corners, int max_allowed) {
    // detect features
    int count = y.detect(img, corners, 17);

    // sort by score and reduce the count if needed
    if(count > max_allowed) {
        Sort(corners, keypoint_t());
        count = max_allowed;
        corners.SetCount(count);
    }

    // calculate dominant orientation for each keypoint
    for (keypoint_t& c : corners) {
        c.angle = ic_angle(img, c.x, c.y);
    }

    return count;
}

// central difference using image moments to find dominant orientation
const int OrbBase::u_max[] = {15,15,15,15,14,14,14,13,13,12,11,10,9,8,6,3,0};

double OrbBase::ic_angle(const ByteMat& img, int px, int py) {
    int half_k = 15; // half patch size
    int m_01 = 0, m_10 = 0;
    auto& src=img.data;
    int step=img.cols;
    int u=0, v=0, center_off=(py*step + px);
    int v_sum=0,d=0,val_plus=0,val_minus=0;

    // Treat the center line differently, v=0
    for (u = -half_k; u <= half_k; ++u)
        m_10 += u * src[center_off+u];

    // Go line by line in the circular patch
    for (v = 1; v <= half_k; ++v) {
        // Proceed over the two lines
        v_sum = 0;
        d = u_max[v];
        for (u = -d; u <= d; ++u) {
            val_plus = src[center_off+u+v*step];
            val_minus = src[center_off+u-v*step];
            v_sum += (val_plus - val_minus);
            m_10 += u * (val_plus + val_minus);
        }
        m_01 += v * v_sum;
    }

    return atan2(m_01, m_10);
}

// estimate homography transform between matched points
int OrbBase::find_transform(Vector<match_t>& matches) {
    
    // ransac params
    int num_model_points = 4;
    int reproj_threshold = 3;
    
    ransac_param.Init(num_model_points, reproj_threshold, 0.5, 0.99);

	int count = matches.GetCount();
    pattern_xy.SetCount(count);
    screen_xy.SetCount(count);

    // construct correspondences
    auto pattern_it = pattern_xy.Begin();
    auto screen_it = screen_xy.Begin();
    for (const match_t& m : matches) {
        auto& pat = *pattern_it; pattern_it++;
        auto& scr = *screen_it; screen_it++;
        const keypoint_t& s_kp = screen_corners[m.screen_idx];
        const keypoint_t& p_kp = pattern_corners[m.pattern_lev][m.pattern_idx];
        pat.x = p_kp.x;
        pat.y = p_kp.y;
        scr.x = s_kp.x;
        scr.y = s_kp.y;
    }

    // estimate motion
    bool ok = false;
    ok = mot.ransac(ransac_param, mm_kernel, pattern_xy, screen_xy, homo3x3, &match_mask, 1000);

    // extract good matches and re-estimate
    int good_cnt = 0;
    if (ok) {
        for(int i = 0; i < count; ++i) {
            if (match_mask.data[i]) {
                pattern_xy[good_cnt] = pattern_xy[i];
                screen_xy[good_cnt] = screen_xy[i];
                good_cnt++;
            }
        }
        pattern_xy.SetCount(good_cnt);
        screen_xy.SetCount(good_cnt);
        
        // run kernel directly with inliers only
        mm_kernel.run(pattern_xy, screen_xy, homo3x3);
    }
    else {
        identity_3x3(homo3x3, 1.0f);
    }

    return good_cnt;
}


// naive brute-force matching.
// each on screen point is compared to all pattern points
// to find the closest match
int OrbBase::match_pattern() {
    int q_cnt = screen_descriptors.GetCount();
    int qidx=0,lev=0,pidx=0,k=0;
    int num_matches = 0;
    matches.SetCount(0);
    matches.Reserve(256);

    for(qidx = 0; qidx < q_cnt; ++qidx) {
        const BinDescriptor& scr = screen_descriptors[qidx];
        int best_dist = 256;
        int best_dist2 = 256;
        int best_idx = -1;
        int best_lev = -1;

        for(lev = 0; lev < num_train_levels; ++lev) {
            auto& pattern = pattern_descriptors[lev];
            int ld_cnt = pattern.GetCount();

            for(pidx = 0; pidx < ld_cnt; ++pidx) {
                const BinDescriptor& lev_desc = pattern[pidx];
                int curr_d = 0;
                
                // our descriptor is 32 bytes so we have 8 Integers
                for(k=0; k < 8; ++k) {
                    curr_d += PopCount32( scr.u8[k] ^ lev_desc.u8[k] );
                }

                if(curr_d < best_dist) {
                    best_dist2 = best_dist;
                    best_dist = curr_d;
                    best_lev = lev;
                    best_idx = pidx;
                } else if(curr_d < best_dist2) {
                    best_dist2 = curr_d;
                }
            }
        }

        // filter out by some threshold
        if(best_dist < match_threshold) {
            auto& m = matches.Add();
            m.screen_idx = qidx;
            m.pattern_lev = best_lev;
            m.pattern_idx = best_idx;
            num_matches++;
        }
        //

        /* filter using the ratio between 2 closest matches
        if(best_dist < 0.8*best_dist2) {
            matches[num_matches].screen_idx = qidx;
            matches[num_matches].pattern_lev = best_lev;
            matches[num_matches].pattern_idx = best_idx;
            num_matches++;
        }
        */

    }

    return num_matches;
}

// project/transform rectangle corners with 3x3 Matrix
void OrbBase::tCorners(const Vector<float>& M, int w, int h) {
	corners.SetCount(0);
	corners.Reserve(4);
    corners << keypoint_t(0,0) << keypoint_t(w,0) << keypoint_t(w,h) << keypoint_t(0,h);
    double z=0.0;
    double px=0.0, py=0.0;

    for (keypoint_t& p : corners) {
        px = M[0]*p.x + M[1]*p.y + M[2];
        py = M[3]*p.x + M[4]*p.y + M[5];
        z = M[6]*p.x + M[7]*p.y + M[8];
        p.x = px/z;
        p.y = py/z;
    }
}

void OrbBase::render_matches(const Vector<match_t>& matches) {
	ASSERT(match_mask.data.GetCount() >= matches.GetCount());
	byte* mask = match_mask.data.Begin();
	lines.SetCount(0);
    for(const match_t& m : matches) {
        const auto& s_kp = screen_corners[m.screen_idx];
        const auto& p_kp = pattern_corners[m.pattern_lev][m.pattern_idx];
        
        byte b = 0, r,g;
        if (*mask++) {
            r = 0;
            g = 255;
        } else {
            r = 255;
            g = 0;
        }
        
        ColorLine& l = lines.Add();
        l.a.x = s_kp.x;
        l.a.y = s_kp.y;
        l.b.x = p_kp.x*0.25;
        l.b.y = p_kp.y*0.25;
        l.clr = Color(r,g,b);
    }
}

void OrbBase::render_pattern_shape() {
    // get the projected pattern corners
    tCorners(homo3x3.data, pattern_preview.cols*2, pattern_preview.rows*2);
	
	for(int i = 0; i < corners.GetCount(); i++) {
		const keypoint_t& a = corners[i];
		const keypoint_t& b = corners[(i + 1) % corners.GetCount()];
		
		ColorLine& l = lines.Add();
        l.a.x = a.x;
        l.a.y = a.y;
        l.b.x = b.x;
        l.b.y = b.y;
        l.clr = Color(0,255,0);
	}
}

/*function render_corners(corners, count, img, step) {
    var pix = (0xff << 24) | (0x00 << 16) | (0xff << 8) | 0x00;
    for(var i=0; i < count; ++i)
    {
        var x = corners[i].x;
        var y = corners[i].y;
        var off = (x + y * step);
        img[off] = pix;
        img[off-1] = pix;
        img[off+1] = pix;
        img[off-step] = pix;
        img[off+step] = pix;
    }
}*/

/*function render_mono_image(src, dst, sw, sh, dw) {
    var alpha = (0xff << 24);
    for(var i = 0; i < sh; ++i) {
        for(var j = 0; j < sw; ++j) {
            var pix = src[i*sw+j];
            dst[i*dw+j] = alpha | (pix << 16) | (pix << 8) | pix;
        }
    }
}*/


NAMESPACE_TOPSIDE_END
