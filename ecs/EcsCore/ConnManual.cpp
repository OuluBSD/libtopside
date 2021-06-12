#include "EcsCore.h"
NAMESPACE_TOPSIDE_BEGIN


bool ManualConnector::LinkManually(ComponentBaseRef src_comp, ComponentBaseRef dst_comp, TypeCls src_iface, TypeCls sink_iface) {
	InterfaceSourceBaseRef src = src_comp->FindSource(src_iface);
	InterfaceSinkBaseRef sink = dst_comp->FindSink(sink_iface);
	ASSERT(src && sink);
	if (!src || !sink)
		return false;
	ASSERT(src	->AsComponentBase()->GetEntity()->HasPoolParent(ConnectorBase::GetPool()));
	ASSERT(sink	->AsComponentBase()->GetEntity()->HasPoolParent(ConnectorBase::GetPool()));
	CookieRef src_cookie, sink_cookie;
	if (src->Accept(sink, src_cookie, sink_cookie)) {
		const auto& src_d = EcsFactory::SourceDataMap().Get(src_iface);
		if (src_d.sink_cls != sink_iface) {
			ASSERT(0);
			LOG("internal error: unexpected sink class type");
			return false;
		}
		
		TypeCls expt_type = src_d.expt_type;
		ASSERT(expt_type);
		ExchangePointRef ep = MetaExchangePoint::Add(expt_type);
		RTLOG("ManualConnector::LinkManually(TypeCls...): created " << ep->GetDynamicName() << " at " << HexStr(&ep->GetRTTI()));
		src->Link(ep, sink, src_cookie, sink_cookie);
		ep->Init(this);
		ep->Set(src, sink, src_cookie, sink_cookie);
		return true;
	}
	return false;
}



void ConnectManuallyInterfaces::Initialize() {
	Machine& m = ConnectorBase::GetPool()->GetMachine();
	sys = m.Get<EntityStore>();
	ASSERT_(sys, "EntityStore is required for MetaExchangePoints");
}

void ConnectManuallyInterfaces::Uninitialize() {
	UnlinkAll();
	sys.Clear();
}

void ConnectManuallyInterfaces::UnlinkAll() {
	Machine& mach = ConnectorBase::GetPool()->GetMachine();
	
	if (!mach.IsRunning()) {
		for (ExchangePointRef& pt : pts) {
			pt->Source()	->UnlinkAll();
			pt->Sink()		->UnlinkAll();
		}
	}
	else {
		for (ExchangePointRef& pt : pts) {
			pt->Source()	->Unlink(pt->Sink());
		}
	}
	
	pts.Clear();
}

void ConnectManuallyInterfaces::Update(double dt) {
	
}


NAMESPACE_TOPSIDE_END
