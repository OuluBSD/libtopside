#include "EcsCore.h"


NAMESPACE_OULU_BEGIN



ExchangePoint::ExchangePoint() {
	
}

void ExchangePoint::Set(InterfaceBaseRef src, InterfaceBaseRef sink) {
	this->src	= src;
	this->sink	= sink;
	
}













MetaExchangePoint::MetaExchangePoint() {
	
}

void MetaExchangePoint::Init(PoolComponentBase* comp) {
	this->comp = comp;
	
}

String MetaExchangePoint::ToString() const {
	
	TODO
	
}

ExchangePointRef MetaExchangePoint::Add() {
	ExchangePointRef pt = pts.Add();
	
	return pt;
}

void MetaExchangePoint::UnlinkAll() {
	ASSERT(comp);
	Machine& mach = comp->GetPool().GetMachine();
	
	if (!mach.IsRunning()) {
		for (ExchangePointRef& pt : pts) {
			pt->src  ->UnlinkAll();
			pt->sink ->UnlinkAll();
		}
	}
	else {
		for (ExchangePointRef& pt : pts) {
			pt->src->UnlinkManually(*pt->sink);
		}
	}
	
	pts.Clear();
}

NAMESPACE_OULU_END
