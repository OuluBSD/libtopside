// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

#ifndef _ICfr_TmplClasses_h_
#define _ICfr_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Cfr> struct CfrSystemT;


template <class Cfr>
struct CfrSystemT : CfrSystem {
	using CLASSNAME = CfrSystemT<Cfr>;
	RTTI_DECL1(CLASSNAME, CfrSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<CfrSystem>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

