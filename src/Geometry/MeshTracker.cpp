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

const TrackedPoint* MeshTracker::FindTrackedPoint(const MeshTrackerFrame& from, const Descriptor& d) {
	const TrackedPoint* best_tp_match = 0;
	int best_tp_dist = INT_MAX;
	for (const TrackedPoint& p : from.tracked_points) {
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
		else return 0;
	}
	
	return p;
}

void MeshTracker::SolveTransform(const MeshTrackerFrame& from, MeshTrackerFrame& to) {

	// Update tracked triangles
	UpdateTrackedTriangles(from, to);
	UpdateOctreePositions(from, to);
	
}

void MeshTracker::ProcessTriangles(MeshTrackerFrame& to) {

	// Prune old tracked triangles
	PruneTriangles(to);
	
	// Find new tracked triangles
	FindTriangles(to);
	
}
	 
void MeshTracker::PruneTriangles(MeshTrackerFrame& to) {
	if (to.tracked_triangles.GetCount() < tracked_triangle_limit)
		return;
	
	TODO
	
}

void MeshTracker::FindTriangles(MeshTrackerFrame& to) {
	for (TrackedPoint& tp0 : to.tracked_points) {
		if (!tp0.has_next_local_tgt || !tp0.has_local_tgt || tp0.IsMaxTriangles())
			continue;
		for (TrackedPoint& tp1 : to.tracked_points) {
			if (&tp0 == &tp1)
				break;
			if (!tp1.has_next_local_tgt || !tp1.has_local_tgt ||
				tp1.IsMaxTriangles() || IsAlreadyInSameTriangle(tp0, tp1))
				continue;
			
			for (TrackedPoint& tp2 : to.tracked_points) {
				if (&tp1 == &tp2)
					break;
				if (!tp2.has_next_local_tgt || !tp2.has_local_tgt ||
					tp2.IsMaxTriangles() || IsAlreadyInSameTriangle(tp1, tp2))
					continue;
				
				TrackedTriangle& tt = to.tracked_triangles.Add();
				tt.Track(tp0, tp1, tp2);
				
				if (tp0.IsMaxTriangles() || tp1.IsMaxTriangles())
					break;
			}
			if (tp0.IsMaxTriangles())
				break;
		}
	}
}

void MeshTracker::UpdateTrackedTriangles(const MeshTrackerFrame& from, MeshTrackerFrame& to) {
	PositionOrientationAverage camera_average;
	int tri_i = -1;
	for (const TrackedTriangle& tt : from.tracked_triangles) {
		tri_i++;
		
		if (!tt.a->has_next_local_tgt || !tt.b->has_next_local_tgt ||
			!tt.a->has_local_tgt || !tt.b->has_local_tgt ||
			!tt.c->has_local_tgt || !tt.c->has_local_tgt)
			continue;
		
		
		mat4 view_diff;
		if (!CalculateTriangleChange(
			tt.a->local_tgt,
			tt.b->local_tgt,
			tt.c->local_tgt,
			tt.a->next_local_tgt,
			tt.b->next_local_tgt,
			tt.c->next_local_tgt,
			view_diff))
			continue;
		
	    quat rotation;
	    vec3 scale, translation, skew;
	    vec4 pers;
	    mat4 view_diff_inv = view_diff.GetInverse();
	    Decompose(view_diff_inv, scale, rotation, translation, skew, pers);
	    
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
		
		to.view_change = Translate(position) * QuatMat(orientation);
		to.view = from.view * to.view_change;
		to.view_inv = to.view.GetInverse();
		
		vec3 scale, skew;
		vec4 pers;
		Decompose(to.view, scale, to.orientation, to.position, skew, pers);
		to.orientation.Normalize();
		
		#if 1
		{
			quat full_orient = MatQuat(to.view);
			vec3 full_axes;
			QuatAxes(full_orient, full_axes);
			full_axes = full_axes / M_PIf * 180;
			vec3 pos_comp = to.view.GetTranslation();
			LOG("\t" << full_axes[0] << ": " << pos_comp[0] << ", " << pos_comp[2]);
		}
		#endif
	}
}

void MeshTracker::UpdateOctreePositions(const MeshTrackerFrame& from, MeshTrackerFrame& to) {
	for (const TrackedPoint& tp : from.tracked_points) {
		if (tp.has_next_local_tgt) {
			tp.next_global_tgt = (to.view_inv * tp.next_local_tgt.Embed()).Splice();
			
			#if 0
			if (&from == &to)
				UpdateOctreePosition(to, const_cast<TrackedPoint&>(tp), true);
			#endif
		}
	}
}

void MeshTracker::UpdateOctreePosition(MeshTrackerFrame& to, TrackedPoint& tp, bool local_value, bool next_value) {
	OctreeDescriptorPoint& dp = *tp.dp;
	
	if (local_value)
		dp.av.Add(tp.local_tgt, to.orientation);
	else if (next_value)
		dp.av.Add(tp.next_global_tgt, to.orientation);
	else
		dp.av.Add(tp.global_tgt, to.orientation);
	
	vec3 pos = dp.av.GetMeanPosition();
	//LOG("add tgt " << global_tgt.ToString());
	//LOG("\t" << dp.GetPosition().ToString() << " --> " << pos.ToString());
	dp.SetPosition(pos);
}














WmrMotionControllerTracker::WmrMotionControllerTracker() {
	
}


NAMESPACE_TOPSIDE_END
