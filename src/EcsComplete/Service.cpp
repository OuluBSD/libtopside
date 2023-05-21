#include "EcsComplete.h"

NAMESPACE_TOPSIDE_BEGIN


EcsService::EcsService() {
	
}

bool EcsService::Init(String name) {
	
	return true;
}

void EcsService::Update() {
	
	// Require EnetServiceClient
	if (!server) {
		server = base->FindServiceT<EnetServiceServer>();
		if (!server)
			return;
		
		server->AddStream(NET_GEOM_LOAD_ENGINE, THISBACK(ReceiveGeoms));
		server->AddStream(NET_GEOM_STORE_ENGINE, THISBACK(SendEngine));
	}
	
}

void EcsService::Stop() {
	
}

void EcsService::Deinit() {
	
}

void EcsService::ReceiveGeoms(Ether& in, Ether& out) {
	Parallel::Machine& mach = GetActiveMachine();
	Ecs::Engine& eng = mach.GetEngine();
	Ecs::PoolRef root = eng.Get<Ecs::EntityStore>()->GetRoot();
	
	in % *root;
	
	/*for (GeomSerializer::Item& item : read.items) {
		
		switch (item.type) {
		case GEOMVAR_ENTITY_KEY:
			bound_entity = ResolveEntity(root, item.str);
			break;
		case GEOMVAR_RESET_ENTITY_KEY:
			bound_entity.Clear();
			break;
		case GEOMVAR_ORIENTATION: {
				if (!bound_entity) {LOG("EcsService::ReceiveGeoms: error: no entity"); return;}
				Ecs::TransformRef trans = bound_entity->GetAdd<Ecs::Transform>();
				for(int i = 0; i < 4; i++)
					trans->data.orientation.data.data[i] = item.f[i];
			}
			break;
		case GEOMVAR_POSITION: {
				if (!bound_entity) {LOG("EcsService::ReceiveGeoms: error: no entity"); return;}
				Ecs::TransformRef trans = bound_entity->GetAdd<Ecs::Transform>();
				for(int i = 0; i < 3; i++)
					trans->data.position.data[i] = item.f[i];
			}
			break;
		case GEOMVAR_MODEL: {
				if (!bound_entity) {LOG("EcsService::ReceiveGeoms: error: no entity"); return;}
				ModelCacheRef mc = mach.Find<ModelCache>();
				if (!mc) {LOG("EcsService::ReceiveGeoms: error: no ModelCache"); return;}
				ModelRef mdl = mc->Attach(read.DetachModel(item.mdl));
				Ecs::ModelComponentRef comp = bound_entity->GetAdd<Ecs::ModelComponent>();
				comp->SetModel(mdl);
			}
			break;
		case GEOMVAR_NULL:
			break;
		default:
			break;
		}
	}*/
	
}

void EcsService::SendEngine(Ether& in, Ether& out) {
	
	Parallel::Machine& mach = GetActiveMachine();
	Ecs::Engine& eng = mach.GetEngine();
	Ecs::PoolRef root = eng.Get<Ecs::EntityStore>()->GetRoot();
	
	out % *root;
	
}

Ecs::EntityRef EcsService::ResolveEntity(Ecs::PoolRef& root, String path) {
	Vector<String> names = Split(path, "/");
	if (names.IsEmpty())
		return Ecs::EntityRef();
	
	Ecs::PoolRef pool = root;
	for(int i = 0; i < names.GetCount()-1; i++) {
		String n = names[i];
		pool = pool->GetAddPool(n);
	}
	
	Ecs::EntityRef ent = pool->GetAddEmpty(names.Top());
	
	return ent;
}


NAMESPACE_TOPSIDE_END
