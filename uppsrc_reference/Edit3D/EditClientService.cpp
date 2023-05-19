#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


bool EditClientService::Init(String name) {
	
	return true;
}

void EditClientService::Update() {
	
	// Require EnetServiceClient
	if (!client) {
		client = base->FindServiceT<EnetServiceClient>();
		if (!client)
			return;
	}
	
	if (client->IsConnected()) {
		// Update GeomSerializer
		if (!is_calling && sync.Update()) {
			is_calling = true;
			
			// Actually send the serialized geom state vector
			client->CallSerialized(NET_GEOM_SERIALIZER, sync.write, sync.read, [this]() {
				is_calling = false;
			});
		}
	}
}

void EditClientService::Stop() {
	LOG("TODO");
}

void EditClientService::Deinit() {
	LOG("TODO");
}



NAMESPACE_TOPSIDE_END
