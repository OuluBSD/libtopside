#include "EcsCore.h"

NAMESPACE_OULU_BEGIN



void ConnectorSystem::Uninitialize() {
	if (es.IsEmpty())
		es = machine.Get<EntityStore>();
	
	for(void* ptr : conns) {
		Connector* conn = (Connector*)ptr;
		
		for(InterfaceBase* iface : conn->GetSourceInterfaces())
			iface->UnlinkAll();
	}
	
	for(void* ptr : conns) {
		Connector* conn = (Connector*)ptr;
		
		for(InterfaceBase* iface : conn->GetSinkInterfaces())
			iface->UnlinkAll();
	}
}

void ConnectorSystem::Update(double dt) {
	if (es.IsEmpty())
		es = machine.Get<EntityStore>();
	
	for(void* ptr : conns) {
		Connector* conn = (Connector*)ptr;
		
		if (conn->IsUpdateInterfaces()) {
			conn->SetUpdateInterfaces(false);
			conn->ClearInterfaces();
			Entity& e = conn->GetEntity();
			e.UpdateInterfaces();
		}
		
		for(int i = 0; i < CONNAREA_COUNT; i++) {
			ConnectorArea a = (ConnectorArea)i;
			
			if (conn->IsConnectAny(a)) {
				uint64 iface_bits = conn->GetConnectBits(a);
				conn->ClearConnectBits(a);
				Ref<EntityStore> es = machine.Get<EntityStore>();
				
				#define IFACE___(x, Source, src, Sink, sink, src_, sink_, visitor)\
				if (iface_bits & (1ULL << (uint64)IFACE_##x##Source)) {\
					Vector<x##Source*> src_ifaces = conn->GetEntity().FindInterfaces<x##Source>();\
					for(auto src: src_ifaces) {\
						if (src && src->IsLinkable()) {\
							ComponentBase* src_cbase = src->AsComponentBase(); \
							ASSERT(src_cbase); \
							if (src_cbase) for(visitor ev(src_cbase->GetEntity()); ev; ev++) {\
								Vector<x##Sink*> sink_ifaces = ev->FindInterfaces<x##Sink>();\
								for(auto* sink : sink_ifaces) {\
									if (sink && sink->IsLinkable()) {\
										ComponentBase* sink_cbase = sink->AsComponentBase(); \
										if (src_cbase != sink_cbase && \
											src_->Link0(*sink_) && !src->IsLinkable())\
											break;\
									}\
								}\
								if (!src->IsLinkable())\
									break;\
							}\
						}\
					}\
				}
				#define IFACE(x) IFACE_SRC(x) IFACE_SINK(x)
				
				if (a == CONNAREA_INTERNAL) {
					#define IFACE_SRC(x)  IFACE___(x, Source, src, Sink, sink, src, sink, EntityDummyVisitor)
					#define IFACE_SINK(x) IFACE___(x, Sink, sink, Source, src, src, sink, EntityDummyVisitor)
					IFACE_LIST
					#undef IFACE_SRC
					#undef IFACE_SINK
				}
				else if (a == CONNAREA_POOL_CURRENT) {
					#define IFACE_SRC(x)  IFACE___(x, Source, src, Sink, sink, src, sink, EntityCurrentVisitor)
					#define IFACE_SINK(x) IFACE___(x, Sink, sink, Source, src, src, sink, EntityCurrentVisitor)
					IFACE_LIST
					#undef IFACE_SRC
					#undef IFACE_SINK
				}
				else if (a == CONNAREA_POOL_CHILDREN_ONLY) {
					#define IFACE_SRC(x)  IFACE___(x, Source, src, Sink, sink, src, sink, EntityChildrenVisitor)
					#define IFACE_SINK(x) IFACE___(x, Sink, sink, Source, src, src, sink, EntityParentVisitor)
					IFACE_LIST
					#undef IFACE_SRC
					#undef IFACE_SINK
				}
				else if (a == CONNAREA_POOL_PARENTS_ONLY) {
					#define IFACE_SRC(x)  IFACE___(x, Source, src, Sink, sink, src, sink, EntityParentVisitor)
					#define IFACE_SINK(x) IFACE___(x, Sink, sink, Source, src, src, sink, EntityChildrenVisitor)
					IFACE_LIST
					#undef IFACE_SRC
					#undef IFACE_SINK
				}
				#undef IFACE
				#undef IFACE___
			}
		}
		
		if (conn->IsSignalAny()) {
			uint64 iface_bits = conn->GetSignalBits();
			conn->ClearSignalBits();
			
			#define IFACE_SRC(x)\
			if (iface_bits & (1ULL << (uint64)IFACE_##x##Source)) {\
				x##Source* in = conn->GetEntity().FindInterface<x##Source>();\
				if (in) in->Signal();\
			}
			#define IFACE_SINK(x)\
			if (iface_bits & (1ULL << (uint64)IFACE_##x##Sink)) {\
				x##Sink* out = conn->GetEntity().FindInterface<x##Sink>();\
				if (out) out->Signal();\
			}
			
			#define IFACE(x) IFACE_SRC(x) IFACE_SINK(x)
			IFACE_LIST
			#undef IFACE
			#undef IFACE_
			#undef IFACE_SRC
			#undef IFACE_SINK
			
		}
	}
}











Connector::Connector() {
	for(int i = 0; i < CONNAREA_COUNT; i++)
		connect_bits[i] = 0;
	signal_bits = 0;
}

void Connector::Initialize() {
	Ref<ConnectorSystem> sys = GetEntity().GetMachine().TryGet<ConnectorSystem>();
	if (sys)
		sys->Add(this);
}

void Connector::Uninitialize() {
	Ref<ConnectorSystem> sys = GetEntity().GetMachine().TryGet<ConnectorSystem>();
	if (sys)
		sys->Remove(this);
}



void Connector::ConnectAll(ConnectorArea a) {
	#define IFACE(x) Connect##x##Source (a); Connect##x##Sink (a);
	IFACE_LIST
	#undef IFACE
}

#define IFACE(x)\
void Connector::Connect##x##Source (ConnectorArea a) {connect_bits[a] |= 1ULL << (uint64)IFACE_##x##Source;} \
void Connector::Connect##x##Sink (ConnectorArea a) {connect_bits[a] |= 1ULL << (uint64)IFACE_##x##Sink;}
IFACE_LIST
#undef IFACE




void Connector::SignalAll() {
	#define IFACE(x) Signal##x##Source (); Signal##x##Sink ();
	IFACE_LIST
	#undef IFACE
}

#define IFACE(x)\
void Connector::Signal##x##Source () {signal_bits |= 1ULL << (uint64)IFACE_##x##Source;} \
void Connector::Signal##x##Sink () {signal_bits |= 1ULL << (uint64)IFACE_##x##Sink;}
IFACE_LIST
#undef IFACE

void Connector::UnlinkAll() {
	for(InterfaceBase* iface : src_ifaces)
		iface->UnlinkAll();
	
	for(InterfaceBase* iface : sink_ifaces)
		iface->UnlinkAll();
}

NAMESPACE_OULU_END
