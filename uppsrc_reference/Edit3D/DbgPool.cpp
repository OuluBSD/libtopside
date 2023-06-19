#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


void EngineSerializer::EtherizePool(Ether& e, DbgPool& p) {
	byte magic = 0, chk = 0xaf;
	int dbg_i = 0;
	
	if (e.IsLoading()) {
		e.GetT(magic);
		ASSERT(magic == chk);
		
		//p.Clear();
		
		int pc = 0, ec = 0;
		e.GetT(pc);
		e.GetT(ec);
		p.pools.SetCount(pc);
		p.ents.SetCount(ec);
		
		for (DbgPool& p0 : p.pools) {
			e.GetT(magic);
			ASSERT(magic == chk);
			p0.name = e.GetString();
			
			EtherizePool(e, p0);
			
			e.GetT(magic);
			ASSERT(magic == chk);
			dbg_i++;
		}
		
		dbg_i = 0;
		for (DbgEntity& o0 : p.ents) {
			e.GetT(magic);
			ASSERT(magic == chk);
			o0.name = e.GetString();
			
			EtherizeEntity(e, o0);
			
			e.GetT(magic);
			ASSERT(magic == chk);
			dbg_i++;
		}
		
	}
	else {
		e.PutT(chk);
		
		int pc = p.pools.GetCount();
		int ec = p.ents.GetCount();
		
		e.PutT(pc);
		e.PutT(ec);
		
		for (DbgPool& p0 : p.pools) {
			e.PutT(chk);
			
			e.Put(p0.name);
			
			EtherizePool(e, p0);
			
			e.PutT(chk);
			dbg_i++;
		}
		
		dbg_i = 0;
		for (DbgEntity& o0 : p.ents) {
			e.PutT(chk);
			e.Put(o0.name);
			
			EtherizeEntity(e, o0);
			
			e.PutT(chk);
			dbg_i++;
		}
		
	}
}

void EngineSerializer::EtherizeEntity(Ether& e, DbgEntity& o) {
	byte magic = 0, chk = 0xA0;
	int dbg_i = 0;
	
	if (e.IsLoading()) {
		e.GetT(magic);
		ASSERT(magic == chk);
		
		int c = 0;
		e.GetT(c);
		o.comps.SetCount(c);
		for(DbgComponent& c : o.comps) {
			e.GetT(magic);
			ASSERT(magic == chk);
			
			c.Clear();
			c.cls_name = e.GetString();
			EtherizeComponent(e, c);
			
			e.GetT(magic);
			ASSERT(magic == chk);
			
			dbg_i++;
		}
		
		e.GetT(magic);
		ASSERT(magic == chk);
	}
	else {
		e.PutT(chk);
		
		int c = o.comps.GetCount();
		e.PutT(c);
		
		for(DbgComponent& c : o.comps) {
			e.PutT(chk);
			
			e.Put(c.cls_name);
			EtherizeComponent(e, c);
			
			e.PutT(chk);
			
			dbg_i++;
		}
		
		e.PutT(chk);
	}
}

void EngineSerializer::EtherizeComponent(Ether& e, DbgComponent& c) {
	dword chk = 0xFF, magic = 0;
	if (e.IsLoading()) {
		int dbg_i = 0;
		while (!e.IsEof()) {
			dword obj_type = 0;
			e.GetT(obj_type);
			if (!obj_type)
				break;
			
			bool is_ref = obj_type & (1ULL << 31);
			obj_type &= ~(1ULL << 31);
			
			byte key_len = 0;
			e.GetT(key_len);
			char key[256];
			e.Get(key, key_len);
			key[key_len] = 0;
			String key_str(key, key_len);
			
			if (is_ref) {
				DbgComponent::RefLink& link = c.refs.Add();
				link.type = obj_type;
				
				bool has_ref_value = false;
				e.GetT(has_ref_value);
				
				if (has_ref_value) {
					e % link.path;
				}
			}
			else {
				Object& o = c.vars.Add(key_str);
				if (o.CreateType(obj_type)) {
					o.GetObjectA()->Etherize(e);
				}
				else {
					LOG("EngineSerializer::EtherizeComponent: error: could not create type " << IntStr64(obj_type));
					break;
				}
			}
			
			e.GetT(magic);
			ASSERT(magic == chk);
			
			dbg_i++;
		}
	}
	else {
		for(int i = 0; i < c.vars.GetCount(); i++) {
			Object& o = c.vars[i];
			String key_str = c.vars.GetKey(i);
			
			dword type = o.GetType();
			e.PutT(type);
			
			
			byte key_len = key_str.GetCount();
			e.PutT(key_len);
			e.Put(key_str.Begin(), key_len);
			
			o.GetObjectA()->Etherize(e);
			
			e.PutT(chk);
		}
		
		dword trail = 0;
		e.PutT(trail);
	}
}

void EngineSerializer::Etherize(Ether& e) {
	if (e.IsLoading())
		lock.EnterWrite();
	else
		lock.EnterRead();
	
	EtherizePool(e, pool);
	
	if (e.IsLoading())
		lock.LeaveWrite();
	else
		lock.LeaveRead();
}

void EngineSerializer::Load(GeomScene& scene, GeomCamera& camera) {
	lock.EnterWrite();
	
	pool.Clear();
	pool.LoadScene(scene);
	pool.LoadCamera(camera);
	
	lock.LeaveWrite();
}

void DbgPool::LoadScene(GeomScene& scene) {
	name = scene.name;
	if (name.IsEmpty())
		name = "Unnamed Scene";
	
	for (GeomDirectory& dir : scene.subdir.GetValues()) {
		GeomScene* scene0 = CastPtr<GeomScene>(&dir);
		if (scene0) {
			DbgPool& sub = pools.Add();
			sub.LoadScene(*scene0);
		}
	}
	
	for (GeomObject& obj : scene.objs) {
		if (obj.type == GeomObject::O_MODEL) {
			DbgEntity& ent = this->ents.Add();
			ent.LoadObject(obj);
		}
	}
	
}

void DbgPool::LoadCamera(GeomCamera& cam) {
	{
		DbgEntity& body = ents.Add();
		body.name = "player.body";
		DbgComponent& trans			= body.GetAddComponent("Transform");
		DbgComponent& physics_body	= body.GetAddComponent("PhysicsBody");
		DbgComponent& player_body	= body.GetAddComponent("PlayerBodyComponent");
		
		TransformMatrix& trans_data		= trans.AddVar<TransformMatrix>("data");
		trans_data.position = cam.position;
		trans_data.orientation = cam.orientation;
		trans_data.FillFromOrientation();
	}
	
	{
		DbgEntity& head = ents.Add();
		head.name = "player.head";
		DbgComponent& trans		= head.GetAddComponent("Transform");
		DbgComponent& viewable	= head.GetAddComponent("Viewable");
		DbgComponent& viewport	= head.GetAddComponent("Viewport");
		DbgComponent& chasecam	= head.GetAddComponent("ChaseCam");
		DbgComponent& headcomp	= head.GetAddComponent("PlayerHeadComponent");
		
		TransformMatrix& trans_data		= trans.AddVar<TransformMatrix>("data");
	}
}

void DbgEntity::LoadObject(GeomObject& obj) {
	name = obj.name;
	
	name.Replace(" ", "_");
	
	if (obj.type == GeomObject::O_MODEL) {
		DbgComponent& trans			= GetAddComponent("Transform");
		DbgComponent& rigidbody		= GetAddComponent("RigidBody");
		DbgComponent& model			= GetAddComponent("ModelComponent");
		DbgComponent& physicsbody	= GetAddComponent("PhysicsBody");
		
		//TransformMatrix& trans_data		= trans.AddVar<TransformMatrix>("data");
		/*vec3& trans_size				= trans.AddVar<vec3>("size");
		vec3& trans_relative_position	= trans.AddVar<vec3>("relative_position");
		vec3& trans_anchor_position		= trans.AddVar<vec3>("anchor_position");
		quat& trans_anchor_orientation	= trans.AddVar<quat>("anchor_orientation");
		bool& trans_verbose				= trans.AddVar<bool>("trans_verbose");
		
		trans_size = vec3(1,1,1);
		trans_relative_position = vec3(0,0,0);
		trans_anchor_position = vec3(0,0,0);
		trans_anchor_orientation = quat(0,0,0,0);
		trans_verbose = false;*/
		
	}
}

DbgComponent& DbgEntity::GetAddComponent(String cls_name) {
	for (DbgComponent& comp : comps) {
		if (comp.cls_name == cls_name)
			return comp;
	}
	DbgComponent& comp = comps.Add();
	comp.cls_name = cls_name;
	return comp;
}

NAMESPACE_TOPSIDE_END
