#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


Uncamera::Uncamera() {
	orientation = AxesQuat(0,0,0);
}





VirtualStereoUncamera::VirtualStereoUncamera() {
	
}

void VirtualStereoUncamera::Unrender(const DescriptorImage& l_img, const DescriptorImage& r_img, Octree& o) {
	ASSERT(l_img.GetResolution() == r_img.GetResolution());
	
	// Initialize LensPoly
	InitializeLensPoly(l_img, r_img);
	
	// Reset temp vars
	ResetTempVariables();
	
	// Find previous frame matches or add to stereo-match queue
	FindPreviousFrameMatches(l_img, r_img);
	
	// Update stereo targets
	UpdateStereoTargets();
	MeshTracker::TriangleUpdate();
	
	// Find horizontal matches
	FindHorizontalMatches();
	
	// Process new horizontal stereo point matches
	ProcessHorizontalMatches(o);
	
	iter++;
}

void VirtualStereoUncamera::InitializeLensPoly(const DescriptorImage& l_img, const DescriptorImage& r_img) {
	Size lsz = l_img.GetResolution();
	Size rsz = r_img.GetResolution();
	if (lsz != rsz)
		return;
	LensPoly::SetSize(lsz);
	
	y_levels = max(lsz.cy / y_level_h, rsz.cy / y_level_h) + 1;
}

void VirtualStereoUncamera::ResetTempVariables() {
	ASSERT(y_levels);
	l_desc.SetCount(y_levels);
	r_desc.SetCount(y_levels);
	for (auto& v : l_desc) {v.SetCount(0); v.Reserve(100);}
	for (auto& v : r_desc) {v.SetCount(0); v.Reserve(100);}
	for (TrackedPoint& tp : tracked_points) tp.ResetTemp();
	horz_match.SetCount(0);
}

void VirtualStereoUncamera::FindPreviousFrameMatches(const DescriptorImage& l_img, const DescriptorImage& r_img) {
	for (const Descriptor& d : l_img.GetDescriptors()) {
		int yi = d.y / y_level_h;
		if (yi >= 0 && yi < y_levels) {
			TrackedPoint* tp = FindTrackedPoint(d);
			if (tp)
				tp->l = &d;
			else
				l_desc[yi].Add(&d);

		}
	}
	for (const Descriptor& d : r_img.GetDescriptors()) {
		int yi = d.y / y_level_h;
		if (yi >= 0 && yi < y_levels) {
			TrackedPoint* tp = FindTrackedPoint(d);
			if (tp)
				tp->r = &d;
			else
				r_desc[yi].Add(&d);
		}
	}
}

void VirtualStereoUncamera::UpdateStereoTargets() {
	int tp_i = -1;
	int seen_tracked_points = 0;
	for (TrackedPoint& tp : tracked_points) {
		tp_i++;
		if (!tp.l || !tp.r) {
			tp.has_local_tgt = false;
			continue;
		}
		axes2 l_axes = Unproject(0, vec2(tp.l->x, tp.l->y));
		axes2 r_axes = Unproject(1, vec2(tp.r->x, tp.r->y));
		axes2s eyes = AxesMonoStereo(l_axes, r_axes);
		tp.prev_local_tgt = tp.local_tgt;
		tp.has_prev_local_tgt = tp.has_local_tgt;
		tp.has_local_tgt = CalculateStereoTarget(eyes, eye_dist, tp.local_tgt);
		
		//LOG(tp_i << ": " << tp.local_tgt.ToString() << ", " << tp.prev_local_tgt.ToString());
		seen_tracked_points++;
	}
	//LOG("\tseen tracked points: " << seen_tracked_points);
}

void VirtualStereoUncamera::FindHorizontalMatches() {
	for(int i = 0; i < y_levels; i++) {
		Vector<const Descriptor*>& lv = l_desc[i];
		Vector<const Descriptor*>& rv = r_desc[i];
		for (const Descriptor* l : lv) {
			int best_dist = 32*8;
			const Descriptor* best_match = 0;
			
			for (const Descriptor* r : rv) {
				int dist = 0;
				for(int j = 0; j < 8; j++) {
					dist += PopCount32(l->u[j] ^ r->u[j]);
				}
				
				if (dist < best_dist && dist <= distance_limit) {
					best_match = r;
					best_dist = dist;
				}
			}
			
			if (best_match) {
				const Descriptor* r = best_match;
				axes2 l_eye = Unproject(0, vec2(l->x, l->y));
				axes2 r_eye = Unproject(1, vec2(r->x, r->y));
				axes2s eyes = AxesMonoStereo(l_eye, r_eye);
				vec3 local_tgt;
				
				if (CalculateStereoTarget(eyes, eye_dist, local_tgt)) {
					//float deg = VectorAngle(l_dir, r_dir) / M_PI * 180;
					//LOG(deg << ": " << tgt.ToString() << ", " << l_dir.ToString() << ", " << r_dir.ToString() << ", " << best_dist);
					//LOG(deg << ": " << tgt.ToString());
					
					HorizontalMatch& hm = horz_match.Add();
					hm.l = l;
					hm.r = r;
					hm.eyes = eyes;
					hm.local_tgt = local_tgt;
					hm.global_tgt = (view_inv * local_tgt.Embed()).Splice();
				}
			}
		}
	}
}

void VirtualStereoUncamera::ProcessHorizontalMatches(Octree& o) {
	for (const HorizontalMatch& hm : horz_match) {
		const auto& descriptor_value = hm.l->u; // left eye by default
		
		OctreeDescriptorPoint* p = MeshTracker::GetAddNode(hm.global_tgt, descriptor_value, o);
		
		if (p) {
			OctreeDescriptorPoint& dp = *p;
			TrackedPoint& tp = tracked_points.Add();
			tp.dp = &dp;
			tp.local_tgt = hm.local_tgt;
			memcpy(tp.descriptor, descriptor_value, DESCRIPTOR_BYTES);
			
			UpdateOctreePosition(hm.global_tgt, tp);
		}
	}
}




NAMESPACE_TOPSIDE_END
