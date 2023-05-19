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
		
		server->AddStream(NET_GEOM_SERIALIZER, THISBACK(ReceiveGeoms));
	}
	
}

void EcsService::Stop() {
	
}

void EcsService::Deinit() {
	
}

void EcsService::ReceiveGeoms(Ether& in, Ether& out) {
	
	in % read;
	
	LOG(read.GetCount());
	
	LOG("TODO write to ecs Engine");
	
	Ecs::Engine& eng = GetActiveMachine().GetEngine();
	
	for (GeomSerializer::Item& item : read.items) {
		TODO
		
		switch (item.type) {
		case GEOMVAR_ENTITY_KEY:
			break;
		case GEOMVAR_RESET_ENTITY_KEY:
			break;
		case GEOMVAR_SYSTEM_PATH:
			break;
		case GEOMVAR_ORIENTATION:
			break;
		case GEOMVAR_POSITION:
			break;
		case GEOMVAR_MODEL:
			break;
		case GEOMVAR_NULL:
			break;
		default:
			break;
		}
	}
}

NAMESPACE_TOPSIDE_END
