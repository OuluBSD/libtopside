#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


void TrackedPoint::Attach(TrackedTriangle& tt) {
	ASSERT(triangle_count < MAX_TRIANGLES);
	for(int i = 0; i < MAX_TRIANGLES; i++) {
		if (!triangles[i]) {
			triangles[i] = &tt;
			++triangle_count;
			return;
		}
	}
}

void TrackedPoint::Detach(TrackedTriangle& tt) {
	ASSERT(triangle_count > 0);
	for(int i = 0; i < MAX_TRIANGLES; i++) {
		if (triangles[i] == &tt) {
			triangles[i] = 0;
			--triangle_count;
			return;
		}
	}
}







void TrackedTriangle::Track(TrackedPoint& tp0, TrackedPoint& tp1, TrackedPoint& tp2) {
	ASSERT(!a && !b && !c);
	a = &tp0;
	b = &tp1;
	c = &tp2;
	tp0.Attach(*this);
	tp1.Attach(*this);
}

void TrackedTriangle::Untrack() {
	ASSERT(a && b && c);
	a->Detach(*this);
	b->Detach(*this);
	c->Detach(*this);
	a = 0;
	b = 0;
	c = 0;
}









MeshTracker::MeshTracker() {
	
}

TrackedPoint* MeshTracker::FindTrackedPoint(const Descriptor& d) {
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

bool MeshTracker::IsAlreadyInSameTriangle(const TrackedPoint& a, const TrackedPoint& b) {
	for(int i = 0; i < TrackedPoint::MAX_TRIANGLES; i++) {
		TrackedTriangle* tt = a.triangles[i];
		if (!tt) continue;
		if (tt->a == &b || tt->b == &b)
			return true;
	}
	return false;
}

OctreeDescriptorPoint* MeshTracker::GetAddNode(const vec3& global_tgt, const uint32* descriptor_value, Octree& o) {
	OctreeDescriptorPoint* p = 0;
	
	float sphere_radius = 3; //error_factor * tgt.GetLength() * 10;
	OctreeDescriptorPoint* best_dp_match = 0;
	int best_dp_dist = INT_MAX;
	for (OctreeNode& n : o.GetCollection(Sphere(global_tgt, sphere_radius))) {
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
	
	if (best_dp_match) {
		// use old octree match
		p = best_dp_match;
		//LOG("use old dp");
	}
	else {
		// completele new match: create octree node and tracked point
		OctreeNode* n = o.GetAddNode(global_tgt, -3);
		if (n) {
			//LOG("new dp");
			p = &n->Add<OctreeDescriptorPoint>();
		}
		else TODO
	}
	
	return p;
}

void MeshTracker::TriangleUpdate() {

	// Prune old tracked triangles
	PruneTriangles();
	
	// Find new tracked triangles
	FindTriangles();
	
	// Update tracked triangles
	UpdateTrackedTriangles();
	UpdateOctreePositions();
	
}

void MeshTracker::PruneTriangles() {
	if (tracked_triangles.GetCount() < tracked_triangle_limit)
		return;
	
	TODO
	
}

void MeshTracker::FindTriangles() {
	for (TrackedPoint& tp0 : tracked_points) {
		if (!tp0.has_local_tgt || !tp0.has_prev_local_tgt || tp0.IsMaxTriangles())
			continue;
		for (TrackedPoint& tp1 : tracked_points) {
			if (&tp0 == &tp1)
				break;
			if (!tp1.has_local_tgt || !tp1.has_prev_local_tgt ||
				tp1.IsMaxTriangles() || IsAlreadyInSameTriangle(tp0, tp1))
				continue;
			
			for (TrackedPoint& tp2 : tracked_points) {
				if (&tp1 == &tp2)
					break;
				if (!tp2.has_local_tgt || !tp2.has_prev_local_tgt ||
					tp2.IsMaxTriangles() || IsAlreadyInSameTriangle(tp1, tp2))
					continue;
				
				TrackedTriangle& tt = tracked_triangles.Add();
				tt.Track(tp0, tp1, tp2);
				
				if (tp0.IsMaxTriangles() || tp1.IsMaxTriangles())
					break;
			}
			if (tp0.IsMaxTriangles())
				break;
		}
	}
}

void MeshTracker::UpdateTrackedTriangles() {
	PositionOrientationAverage camera_average;
	int tri_i = -1;
	for (TrackedTriangle& tt : tracked_triangles) {
		tri_i++;
		
		if (!tt.a->has_local_tgt || !tt.b->has_local_tgt ||
			!tt.a->has_prev_local_tgt || !tt.b->has_prev_local_tgt ||
			!tt.c->has_prev_local_tgt || !tt.c->has_prev_local_tgt)
			continue;
		
		/*if (iter == 7 && tri_i == 3) {
			LOG("");
		}*/
		
		mat4 view_diff;
		if (!CalculateTriangleChange(
			tt.a->prev_local_tgt,
			tt.b->prev_local_tgt,
			tt.c->prev_local_tgt,
			tt.a->local_tgt,
			tt.b->local_tgt,
			tt.c->local_tgt,
			view_diff))
			continue;
		
	    quat rotation;
	    vec3 scale, translation, skew;
	    vec4 pers;
	    mat4 view_diff_inv = view_diff.GetInverse();
	    bool r = Decompose(view_diff_inv, scale, rotation, translation, skew, pers);
	    
		// Add global values to average counter
		camera_average.Add(translation, rotation);
		
	}
	if (camera_average.GetCount()) {
		vec3 position = camera_average.GetMeanPosition();
		quat orientation = camera_average.GetMeanOrientation();
		
		#if 0
		vec3 axes;
		QuatAxes(orientation, axes);
		vec3 deg = axes / M_PI * 180;
		LOG("\t" << iter << ": + " << deg[0]);
		//LOG(position.ToString() << ", " << deg.ToString());
		#endif
		
		mat4 view_change = Translate(position) * QuatMat(orientation);
		//prev_view = view;
		//prev_view_inv = view_inv;
		view = view * view_change;
		view_inv = view.GetInverse();
		
		vec3 scale, skew;
		vec4 pers;
		Decompose(view, scale, this->orientation, this->position, skew, pers);
		this->orientation.Normalize();
		
		#if 1
		{
			quat full_orient = MatQuat(view);
			vec3 full_axes;
			QuatAxes(full_orient, full_axes);
			full_axes = full_axes / M_PI * 180;
			vec3 pos_comp = view.GetTranslation();
			LOG("\t" << full_axes[0] << ": " << pos_comp[0] << ", " << pos_comp[2]);
		}
		#endif
	}
	else if (!tracked_triangles.IsEmpty()) {
		TODO
	}
}

void MeshTracker::UpdateOctreePositions() {
	for (TrackedPoint& tp : tracked_points) {
		vec3 global_pos = (view_inv * tp.local_tgt.Embed()).Splice();
		UpdateOctreePosition(global_pos, tp);
	}
}

void MeshTracker::UpdateOctreePosition(const vec3& global_tgt, TrackedPoint& tp) {
	tp.global_pos = global_tgt;
	OctreeDescriptorPoint& dp = *tp.dp;
	dp.av.Add(global_tgt, this->orientation);
	vec3 pos = dp.av.GetMeanPosition();
	//LOG("add tgt " << global_tgt.ToString());
	//LOG("\t" << dp.GetPosition().ToString() << " --> " << pos.ToString());
	dp.SetPosition(pos);
}














WmrMotionControllerTracker::WmrMotionControllerTracker() {
	
}


NAMESPACE_TOPSIDE_END
