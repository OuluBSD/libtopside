#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN

RemoteExchange::RemoteExchange() {
	
}

void RemoteExchange::SetTarget(GeomProject& p, GeomWorldState& s, GeomAnim& a, GeomStagedVideo& v) {
	prj = &p;
	state = &s;
	anim = &a;
	video = &v;
}

void RemoteExchange::SetRequireAllSync() {
	SetRequireDataSync();
	SetRequireKeypointSync();
}

void RemoteExchange::SetRequireDataSync() {
	data_sync = true;
}

void RemoteExchange::SetRequireKeypointSync() {
	keypoint_sync = true;
}

bool RemoteExchange::Update() {
	if (!prj || !state || !anim || !video)
		return false;
	
	write.Clear();
	
	GeomWorldState& state = *this->state;
	GeomScene& scene = state.GetActiveScene();
	GeomCamera& camera = state.program;
	
	bool updated = false;
	
	if (data_sync) {
		data_sync = false;
		GeomObjectCollection iter(scene);
		GeomObjectState os;
		for (GeomObject& go : iter) {
			os.obj = &go;
			SyncData(os);
		}
		updated = true;
	}
	
	if (keypoint_sync) {
		keypoint_sync = false;
		
		if (anim->is_playing) {
			TODO
		}
		else {
			GeomObjectCollection iter(scene);
			GeomObjectState os;
			for (GeomObject& go : iter) {
				os.obj = &go;
				SyncEntity(os);
			}
		}
		updated = true;
	}
	else {
		
		//LOG("TODO partial sync");
	}
	
	return updated;
}

void RemoteExchange::SyncData(const GeomObjectState& os) {
	GeomObject& go = *os.obj;
	//Size sz = GetSize();
	Color clr = White();
	int lw = 1;
	//bool z_cull = view_mode == VIEWMODE_PERSPECTIVE;
	
	//mat4 o_world = (QuatMat(os.orientation) * Translate(os.position)).GetInverse();
	//mat4 o_view = view * o_world;
	
	if (go.IsModel()) {
		if (!go.mdl)
			return;
		ASSERT(go.key != 0);
		
		const Model& mdl = *go.mdl;
		hash_t mdl_hash = (hash_t)&mdl;
		write.Set(GEOMVAR_MODEL, mdl);
		
	}
	else if (go.IsOctree()) {
		TODO
	}
}

void RemoteExchange::SyncEntity(const GeomObjectState& os) {
	GeomObject& go = *os.obj;
	//Size sz = GetSize();
	Color clr = White();
	int lw = 1;
	//bool z_cull = view_mode == VIEWMODE_PERSPECTIVE;
	
	//mat4 o_world = (QuatMat(os.orientation) * Translate(os.position)).GetInverse();
	//mat4 o_view = view * o_world;
	
	write.BindEntity(go.key);
	write.Set(GEOMVAR_SYSTEM_PATH, go.GetPath());
	write.Set(GEOMVAR_ORIENTATION, os.orientation);
	write.Set(GEOMVAR_POSITION, os.position);
	
	if (go.IsModel()) {
		// pass
	}
	else if (go.IsOctree()) {
		TODO
		/*Octree& o = go.octree_ptr ? *go.octree_ptr : go.octree.octree;
		OctreeFrustumIterator iter = o.GetFrustumIterator(frustum);
		
		while (iter) {
			const OctreeNode& n = *iter;
			
			for (const auto& one_obj : n.objs) {
				
				const OctreeObject& obj = *one_obj;
				vec3 pos = obj.GetPosition();
				
				if (!frustum.Intersects(pos))
					continue;
				
				vec3 cam_pos = VecMul(o_view, pos);
				
				float x = (cam_pos[0] + 1) * 0.5 * sz.cx;
				float y = (-cam_pos[1] + 1) * 0.5 * sz.cy;
				
				d.DrawRect(x, y, 1, 1, clr);
			}
			
			iter++;
		}*/
	}
	
	write.UnbindEntity();
}

NAMESPACE_TOPSIDE_END
