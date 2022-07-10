#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


Uncamera::Uncamera() {
	orientation = AxesQuat(0,0,0);
}





VirtualStereoUncamera::VirtualStereoUncamera() {
	
}

VirtualStereoUncamera::TrackedPoint* VirtualStereoUncamera::FindTrackedPoint(const Descriptor& d) {
	TrackedPoint* best_tp_match = 0;
	int best_tp_dist = INT_MAX;
	for (TrackedPoint& p : tracked_points) {
		int dist = GetDescriptor8HammingDistance(p.descriptor, d.u);
		if (dist <= distance_limit && dist < best_tp_dist) {
			best_tp_dist = dist;
			best_tp_match = &p;
		}
	}
	
	return best_tp_match;
}

bool VirtualStereoUncamera::IsAlreadyInSameTriangle(const TrackedPoint& a, const TrackedPoint& b) {
	for(int i = 0; i < TrackedPoint::MAX_TRIANGLES; i++) {
		TrackedTriangle* tt = a.triangles[i];
		if (!tt) continue;
		if (tt->a == &b || tt->b == &b)
			return true;
	}
	return false;
}
void VirtualStereoUncamera::TrackedPoint::Attach(TrackedTriangle& tt) {
	ASSERT(triangle_count < MAX_TRIANGLES);
	for(int i = 0; i < MAX_TRIANGLES; i++) {
		if (!triangles[i]) {
			triangles[i] = &tt;
			++triangle_count;
			return;
		}
	}
}

void VirtualStereoUncamera::TrackedPoint::Detach(TrackedTriangle& tt) {
	ASSERT(triangle_count > 0);
	for(int i = 0; i < MAX_TRIANGLES; i++) {
		if (triangles[i] == &tt) {
			triangles[i] = 0;
			--triangle_count;
			return;
		}
	}
}

void VirtualStereoUncamera::TrackedTriangle::Track(TrackedPoint& tp0, TrackedPoint& tp1) {
	ASSERT(!a && !b);
	a = &tp0;
	b = &tp1;
	tp0.Attach(*this);
	tp1.Attach(*this);
}

void VirtualStereoUncamera::TrackedTriangle::Untrack() {
	ASSERT(a && b);
	a->Detach(*this);
	b->Detach(*this);
	a = 0;
	b = 0;
}

void VirtualStereoUncamera::Unrender(const DescriptorImage& l_img, const DescriptorImage& r_img, Octree& o) {
	ASSERT(l_img.GetResolution() == r_img.GetResolution());
	
	
	// Initialize LensPoly
	Size lsz = l_img.GetResolution();
	Size rsz = l_img.GetResolution();
	if (lsz != rsz)
		return;
	LensPoly::SetSize(lsz);
	
	
	// Reset temp vars
	int y_levels = max(lsz.cy / 10, rsz.cy / 10);
	l_desc.SetCount(y_levels);
	r_desc.SetCount(y_levels);
	for (auto& v : l_desc) {v.SetCount(0); v.Reserve(100);}
	for (auto& v : r_desc) {v.SetCount(0); v.Reserve(100);}
	for (TrackedPoint& tp : tracked_points) tp.ResetTemp();
	horz_match.SetCount(0);
	
	
	// Find previous frame matches or add to stereo-match queue
	for (const Descriptor& d : l_img.GetDescriptors()) {
		int yi = d.y / 10;
		if (yi >= 0 && yi < y_levels) {
			TrackedPoint* tp = FindTrackedPoint(d);
			if (tp)
				tp->l = &d;
			else
				l_desc[yi].Add(&d);

		}
	}
	for (const Descriptor& d : r_img.GetDescriptors()) {
		int yi = d.y / 10;
		if (yi >= 0 && yi < y_levels) {
			TrackedPoint* tp = FindTrackedPoint(d);
			if (tp)
				tp->r = &d;
			else
				r_desc[yi].Add(&d);
		}
	}
	
	
	// Update stereo targets
	int tp_i = -1;
	int seen_tracked_points = 0;
	for (TrackedPoint& tp : tracked_points) {
		tp_i++;
		if (!tp.l || !tp.r) {
			tp.has_stereo_target = false;
			continue;
		}
		axes2 l_axes = Unproject(vec2(tp.l->x, tp.l->y));
		axes2 r_axes = Unproject(vec2(tp.r->x, tp.r->y));
		tp.prev_stereo_tgt = tp.stereo_tgt;
		tp.has_prev_stereo_target = tp.has_stereo_target;
		TODO
		//tp.has_stereo_target = CalculateStereoTarget(l_dir, r_dir, eye_dist, tp.stereo_tgt);
		//LOG(tp_i << ": " << tp.stereo_tgt.ToString() << ", " << tp.prev_stereo_tgt.ToString());
		seen_tracked_points++;
	}
	//LOG("\tseen tracked points: " << seen_tracked_points);
	
	
	// Prune old tracked triangles
	if (tracked_triangles.GetCount() >= tracked_triangle_limit) {
		TODO
	}
	
	
	// Find new tracked triangles
	for (TrackedPoint& tp0 : tracked_points) {
		if (!tp0.has_stereo_target || !tp0.has_prev_stereo_target || tp0.IsMaxTriangles())
			continue;
		for (TrackedPoint& tp1 : tracked_points) {
			if (&tp0 == &tp1)
				break;
			if (!tp1.has_stereo_target || !tp1.has_prev_stereo_target ||
				tp1.IsMaxTriangles() || IsAlreadyInSameTriangle(tp0, tp1))
				continue;
			
			TrackedTriangle& tt = tracked_triangles.Add();
			tt.Track(tp0, tp1);
			
			if (tp0.IsMaxTriangles())
				break;
		}
	}
	
	
	// Update tracked triangles
	PositionOrientationAverage camera_average;
	int tri_i = -1;
	for (TrackedTriangle& tt : tracked_triangles) {
		tri_i++;
		
		if (!tt.a->has_stereo_target || !tt.b->has_stereo_target ||
			!tt.a->has_prev_stereo_target || !tt.b->has_prev_stereo_target)
			continue;
		
		/*if (iter == 7 && tri_i == 3) {
			LOG("");
		}*/
		
		// Position difference of the camera
		mat4 view_diff;
		if (!CalculateTriangleChange(
			vec3(0,0,0), // current local position
			tt.a->prev_stereo_tgt,
			tt.b->prev_stereo_tgt,
			tt.a->stereo_tgt,
			tt.b->stereo_tgt,
			view_diff))
			continue;
		
		// Orientation difference
		/*quat orient_diff = CalculateOrientationChange(
			tt.a->prev_stereo_tgt,
			tt.b->prev_stereo_tgt,
			tt.a->stereo_tgt - pos_diff,
			tt.b->stereo_tgt - pos_diff);*/
			
		//DUMP(view_diff);
	    quat rotation;
	    vec3 scale, translation, skew;
	    vec4 pers;
	    bool r = Decompose(view_diff, scale, rotation, translation, skew, pers);
	    //rotation.Normalize();
	    
		//DUMP(translation);
		vec3 axes;
		QuatAxes(rotation, axes);
		vec3 deg = axes / M_PI * 180;
		//DUMP(deg);
		//LOG("\t>>" << tri_i << ": " << deg[0]);
		
		#if 0
		DUMP(translation);
	    ASSERT(fabsf(translation[0]-0) < 0.1);
	    ASSERT(fabsf(translation[1]-0) < 0.1);
	    ASSERT(fabsf(translation[2]-0) < 0.1);
	    #endif
		
		
		// Add global values to average counter
		camera_average.Add(translation, rotation);
		
	}
	if (camera_average.GetCount()) {
		vec3 position = camera_average.GetMeanPosition();
		quat orientation = camera_average.GetMeanOrientation();
		
		vec3 axes;
		QuatAxes(orientation, axes);
		vec3 deg = axes / M_PI * 180;
		/*DUMP(position);
		DUMP(deg);
		LOG("");*/
		LOG("\t" << iter << ": + " << deg[0]);
		
		//LOG(position.ToString() << ", " << deg.ToString());
		
		mat4 view_change = Translate(position) * QuatMat(orientation);
		prev_view = view;
		prev_view_inv = view_inv;
		view = view * view_change;
		view_inv = view.GetInverse();
		
		if (1) {
			quat full_orient = MatQuat(view);
			vec3 full_axes;
			QuatAxes(full_orient, full_axes);
			full_axes = full_axes / M_PI * 180;
			vec3 pos_comp = view.GetTranslation();
			LOG("\t" << iter << ": " << full_axes[0] << ": " << pos_comp[0] << ", " << pos_comp[2]);
		}
	}
	else if (!tracked_triangles.IsEmpty()) {
		TODO
	}
	
	
	for (TrackedPoint& tp : tracked_points) {
		vec3 global_pos = (view_inv * tp.stereo_tgt.Embed()).Splice();
		UpdateOctreePosition(global_pos, tp);
	}
	
	
	// Find horizontal matches
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
				const Descriptor* r = best_match;
				axes2 l_dir = Unproject(vec2(l->x, l->y));
				axes2 r_dir = Unproject(vec2(r->x, r->y));
				vec3 tgt;
				TODO
				
				/*if (CalculateStereoTarget(l_dir, r_dir, eye_dist, tgt)) {
					float deg = VectorAngle(l_dir, r_dir) / M_PI * 180;
					//LOG(deg << ": " << tgt.ToString() << ", " << l_dir.ToString() << ", " << r_dir.ToString() << ", " << best_dist);
					//LOG(deg << ": " << tgt.ToString());
					
					HorizontalMatch& hm = horz_match.Add();
					hm.l = l;
					hm.r = r;
					hm.tgt = tgt;
					hm.global_tgt = (view_inv * tgt.Embed()).Splice();
				}*/
			}
		}
	}
	
	
	// Process new horizontal stereo point matches
	for (const HorizontalMatch& hm : horz_match) {
		const auto& descriptor_value = hm.l->u; // left eye by default
		
		float sphere_radius = 3; //error_factor * tgt.GetLength() * 10;
		OctreeDescriptorPoint* best_dp_match = 0;
		int best_dp_dist = INT_MAX;
		for (OctreeNode& n : o.GetCollection(Sphere(hm.global_tgt, sphere_radius))) {
			for (auto& one_obj : n.objs) {
				OctreeObject& obj = *one_obj;
				OctreeDescriptorPoint* dp = CastPtr<OctreeDescriptorPoint>(&obj);
				if (dp) {
					int dist = GetDescriptor8HammingDistance(dp->u, descriptor_value);
					if (dist <= distance_limit && dist < best_dp_dist) {
						best_dp_dist = dist;
						best_dp_match = dp;
					}
				}
			}
			//LOG(n.GetAABB().ToString());
		}
		
		OctreeDescriptorPoint* p = 0;
		if (best_dp_match) {
			// use old octree match
			p = best_dp_match;
			//LOG("use old dp");
		}
		else {
			// completele new match: create octree node and tracked point
			OctreeNode* n = o.GetAddNode(hm.global_tgt, -3);
			if (n) {
				//LOG("new dp");
				p = &n->Add<OctreeDescriptorPoint>();
			}
			else TODO
		}
		
		if (p) {
			OctreeDescriptorPoint& dp = *p;
			TrackedPoint& tp = tracked_points.Add();
			tp.dp = &dp;
			tp.stereo_tgt = hm.tgt;
			memcpy(tp.descriptor, descriptor_value, DESCRIPTOR_BYTES);
			
			UpdateOctreePosition(hm.global_tgt, tp);
		}
	}
	
	
	iter++;
}

void VirtualStereoUncamera::UpdateOctreePosition(const vec3& global_tgt, TrackedPoint& tp) {
	tp.global_pos = global_tgt;
	OctreeDescriptorPoint& dp = *tp.dp;
	dp.av.Add(global_tgt, this->orientation);
	vec3 pos = dp.av.GetMeanPosition();
	//LOG("add tgt " << global_tgt.ToString());
	//LOG("\t" << dp.GetPosition().ToString() << " --> " << pos.ToString());
	dp.SetPosition(pos);
}



NAMESPACE_TOPSIDE_END
