#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


Uncamera::Uncamera() {
	
}





VirtualStereoUncamera::VirtualStereoUncamera() {
	
}

void VirtualStereoUncamera::Unrender(const UncameraFrame& from, UncameraFrame& to) {
	ASSERT(from.l_img.GetResolution() == from.r_img.GetResolution());
	StageStereoKeypoints(from, to);
	MeshTracker::SolveTransform(from, to);
	StageProcessTransform(from, to);
	iter++;
}

void VirtualStereoUncamera::StageStereoKeypoints(const UncameraFrame& from, UncameraFrame& to) {
	
	// Initialize LensPoly
	InitializeLensPoly(to);
	
	// Reset temp vars
	ResetTempVariables(to);
	
	// Convert descriptor image coordinates to axes
	TODO
	
	// Find previous frame matches or add to stereo-match queue
	FindPreviousFrameMatches(from, to);
	
	// Find horizontal matches
	FindHorizontalMatches(to);
	
	// Update stereo targets
	UpdateStereoTargets(from);
	
	// Process new horizontal stereo point matches
	AddHorizontalMatches(from, to);
	
}

void VirtualStereoUncamera::StageProcessTransform(const UncameraFrame& from, UncameraFrame& to) {
	
	ProcessHorizontalMatches(to);
	
}

void VirtualStereoUncamera::InitializeLensPoly(UncameraFrame& to) {
	Size lsz = to.l_img.GetSize();
	Size rsz = to.r_img.GetSize();
	ASSERT(lsz.cx > 0 && lsz.cy > 0);
	ASSERT(rsz.cx > 0 && rsz.cy > 0);
	if (lsz != rsz)
		return;
	LensPoly::SetSize(lsz);
	
	y_levels = max(lsz.cy / y_level_h, rsz.cy / y_level_h) + 1;
}

void VirtualStereoUncamera::ResetTempVariables(UncameraFrame& to) {
	ASSERT(y_levels);
	to.l_desc.SetCount(y_levels);
	to.r_desc.SetCount(y_levels);
	for (auto& v : to.l_desc) {v.SetCount(0); v.Reserve(100);}
	for (auto& v : to.r_desc) {v.SetCount(0); v.Reserve(100);}
	for (TrackedPoint& tp : to.tracked_points) tp.ResetTemp();
	to.horz_match.SetCount(0);
}

void VirtualStereoUncamera::FindPreviousFrameMatches(const UncameraFrame& from, UncameraFrame& to) {
	for (const Descriptor& d : to.l_dimg.GetDescriptors()) {
		int yi = (int)(d.y / y_level_h);
		if (yi >= 0 && yi < y_levels) {
			const TrackedPoint* tp = FindTrackedPoint(from, d);
			if (tp)
				tp->l = &d;
			else
				to.l_desc[yi].Add(&d);
		}
	}
	for (const Descriptor& d : to.r_dimg.GetDescriptors()) {
		int yi = (int)(d.y / y_level_h);
		if (yi >= 0 && yi < y_levels) {
			const TrackedPoint* tp = FindTrackedPoint(from, d);
			if (tp)
				tp->r = &d;
			else
				to.r_desc[yi].Add(&d);
		}
	}
}

void VirtualStereoUncamera::UpdateStereoTargets(const UncameraFrame& from) {
	int tp_i = -1;
	int seen_tracked_points = 0;
	for (const TrackedPoint& tp : from.tracked_points) {
		tp_i++;
		if (!tp.l || !tp.r) {
			tp.has_next_local_tgt = false;
			continue;
		}
		axes2 l_axes = Unproject(0, vec2(tp.l->x, tp.l->y));
		axes2 r_axes = Unproject(1, vec2(tp.r->x, tp.r->y));
		axes2s eyes = AxesMonoStereo(l_axes, r_axes);
		tp.has_next_local_tgt = CalculateStereoTarget(eyes, eye_dist, tp.next_local_tgt);
		
		//LOG(tp_i << ": " << tp.local_tgt.ToString() << ", " << tp.prev_local_tgt.ToString());
		seen_tracked_points++;
	}
	//LOG("\tseen tracked points: " << seen_tracked_points);
}

void VirtualStereoUncamera::FindHorizontalMatches(UncameraFrame& to) {
	for(int i = 0; i < y_levels; i++) {
		Vector<const Descriptor*>& lv = to.l_desc[i];
		Vector<const Descriptor*>& rv = to.r_desc[i];
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
					#if 0
					float deg = VectorAngle(l_eye, r_eye) / M_PI * 180;
					LOG(deg << ": " << local_tgt.ToString() << ", " << l_eye.ToString() << ", " << r_eye.ToString() << ", " << best_dist);
					//LOG(deg << ": " << local_tgt.ToString());
					#endif
					
					HorizontalMatch& hm = to.horz_match.Add();
					hm.l = l;
					hm.r = r;
					hm.eyes = eyes;
					hm.local_tgt = local_tgt;
				}
			}
		}
	}
}

void VirtualStereoUncamera::GetAddTrackedPoint(UncameraFrame& to, TrackedPoint& tp) {
	Octree& o = to.otree;
	
	OctreeDescriptorPoint* p = MeshTracker::GetAddNode(tp.local_tgt, tp.descriptor, o);
	if (p) {
		OctreeDescriptorPoint& dp = *p;
		tp.dp = &dp;
		
		UpdateOctreePosition(to, tp, true, false);
	}
}

void VirtualStereoUncamera::AddHorizontalMatches(const UncameraFrame& from, UncameraFrame& to) {
	Octree& o = to.otree;
	
	for (const TrackedPoint& f : from.tracked_points) {
		TrackedPoint& t = to.tracked_points.Add();
		t.local_tgt = f.next_local_tgt;
		t.has_local_tgt = true;
		memcpy(t.descriptor, f.descriptor, DESCRIPTOR_BYTES);
		
		#if 1
		GetAddTrackedPoint(to, t);
		#endif
	}
	
	for (HorizontalMatch& hm : to.horz_match) {
		const auto& descriptor_value = hm.l->u; // left eye by default
		
		TrackedPoint& tp = to.tracked_points.Add();
		hm.tp = &tp;
		tp.local_tgt = hm.local_tgt;
		tp.has_local_tgt = true;
		memcpy(tp.descriptor, descriptor_value, DESCRIPTOR_BYTES);
		
		#if 1
		GetAddTrackedPoint(to, tp);
		#endif
	}
}

void VirtualStereoUncamera::ProcessHorizontalMatches(UncameraFrame& to) {
	Octree& o = to.otree;
	
	for (HorizontalMatch& hm : to.horz_match) {
		hm.global_tgt = (to.view_inv * hm.local_tgt.Embed()).Splice();
		
		#if 0
		const auto& descriptor_value = hm.l->u; // left eye by default
		
		OctreeDescriptorPoint* p = MeshTracker::GetAddNode(hm.global_tgt, descriptor_value, o);
		
		if (p) {
			OctreeDescriptorPoint& dp = *p;
			TrackedPoint& tp = *hm.tp;
			tp.dp = &dp;
			tp.global_tgt = hm.global_tgt;
			
			UpdateOctreePosition(to, tp, false);
		}
		#else
		if (hm.tp)
			hm.tp->global_tgt = hm.global_tgt;
		#endif
	}
}




NAMESPACE_TOPSIDE_END
