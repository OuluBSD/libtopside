#include "TemplatesLib.h"

NAMESPACE_TOPSIDE_BEGIN


TMPL_DEVMACH(void) ExchangePoint::Init(ConnectorBase* conn) {
	USING_DEVLIB(System)
	this->conn = conn;
	if (conn) {
		PoolRef pool = GetConnectorBasePool(conn);
		Machine& mach = GetPoolMachine(pool);
		Ref<System> sys = mach.Get<System>();
		ASSERT(sys);
		if (sys)
			sys->Add(AsRef<ExchangePoint>());
	}
}
TMPL_DEVMACH(void) ExchangePoint::Deinit() {
	USING_DEVLIB(System)
	if (conn) {
		PoolRef pool = GetConnectorBasePool(conn);
		Machine& mach = GetPoolMachine(pool);
		Ref<System> sys = mach.Get<System>();
		ASSERT(sys);
		if (sys)
			sys->Remove(AsRef<ExchangePoint>());
		conn = 0;
	}
}
TMPL_DEVMACH(void) ExchangePoint::Update0(double dt) {TODO}


// touch all function impl here
#define DEV(x) \
void ____touch_##x##_expt() {\
	auto init = &ScopeDevMachT<x##Spec>::ExchangePoint::Init; \
	auto deinit = &ScopeDevMachT<x##Spec>::ExchangePoint::Deinit; \
	auto update = &ScopeDevMachT<x##Spec>::ExchangePoint::Update0; \
}
DEV_LIST
#undef DEV




NAMESPACE_TOPSIDE_END
