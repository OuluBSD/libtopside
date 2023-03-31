#include "IEffect.h"

#ifdef flagLV2

NAMESPACE_PARALLEL_BEGIN



bool FxLV2::Effect_Create(NativeEffect*& dev){
	
}

void FxLV2::Effect_Destroy(NativeEffect*& dev){
	
}

bool FxLV2::Effect_Initialize(NativeEffect&, AtomBase&, const Script::WorldState&){
	
}

bool FxLV2::Effect_PostInitialize(NativeEffect&, AtomBase&){
	
}

bool FxLV2::Effect_Start(NativeEffect&, AtomBase&){
	
}

void FxLV2::Effect_Stop(NativeEffect&, AtomBase&){
	
}

void FxLV2::Effect_Uninitialize(NativeEffect&, AtomBase&){
	
}

bool FxLV2::Effect_Send(NativeEffect&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch){
	
}

void FxLV2::Effect_Visit(NativeEffect&, AtomBase&, RuntimeVisitor& vis){
	
}

bool FxLV2::Effect_Recv(NativeEffect&, AtomBase&, int, const Packet&){
	
}

void FxLV2::Effect_Finalize(NativeEffect&, AtomBase&, RealtimeSourceConfig&){
	
}

bool FxLV2::Effect_IsReady(NativeEffect&, AtomBase&, PacketIO& io){
	
}



NAMESPACE_PARALLEL_END

#endif
