#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


VirtualStereoUncamera::VirtualStereoUncamera() {
	
}

void VirtualStereoUncamera::Unrender(const DescriptorImage& l_img, const DescriptorImage& r_img, Octree& o) {
	ASSERT(l_img.GetResolution() == r_img.GetResolution());
	
	Size lsz = l_img.GetResolution();
	Size rsz = l_img.GetResolution();
	if (lsz != rsz)
		return;
	
	LensPoly::SetSize(lsz);
	
	// Find horizontal matches
	
	int y_levels = max(lsz.cy / 10, rsz.cy / 10);
	l_desc.SetCount(y_levels);
	r_desc.SetCount(y_levels);
	for (auto& v : l_desc) {v.SetCount(0); v.Reserve(100);}
	for (auto& v : r_desc) {v.SetCount(0); v.Reserve(100);}
	
	for (const Descriptor& d : l_img.GetDescriptors()) {
		int yi = d.y / 10;
		if (yi >= 0 && yi < y_levels)
			l_desc[yi].Add(&d);
	}
	
	for (const Descriptor& d : r_img.GetDescriptors()) {
		int yi = d.y / 10;
		if (yi >= 0 && yi < y_levels)
			r_desc[yi].Add(&d);
	}
	
	for(int i = 0; i < y_levels; i++) {
		Vector<const Descriptor*>& lv = l_desc[i];
		Vector<const Descriptor*>& rv = r_desc[i];
		for (const Descriptor* l : lv) {
			int best_dist = 32*8;
			int dist_treshold = 100;
			const Descriptor* best_match = 0;
			
			for (const Descriptor* r : rv) {
				int dist = 0;
				for(int j = 0; j < 8; j++) {
					dist += PopCount32(l->u[j] ^ r->u[j]);
				}
				
				if (dist < best_dist && dist < dist_treshold) {
					best_match = r;
					best_dist = dist;
				}
			}
			
			if (best_match) {
				vec3 l_dir = Unproject(vec2(l->x, l->y));
				vec3 r_dir = Unproject(vec2(best_match->x, best_match->y));
				vec3 tgt;
				if (CalculateStereoTarget(l_dir, r_dir, eye_dist, tgt)) {
					
					float deg = VectorAngle(l_dir, r_dir) / M_PI * 180;
					//LOG(deg << ": " << tgt.ToString() << ", " << l_dir.ToString() << ", " << r_dir.ToString() << ", " << best_dist);
					LOG(deg << ": " << tgt.ToString());
					
					TODO
				}
			}
		}
	}
	
	
	// Find previous frame matches
	
	
	
	TODO
	
	
}



NAMESPACE_TOPSIDE_END
