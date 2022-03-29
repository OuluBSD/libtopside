// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IFinance_TmplClasses_h_
#define _IFinance_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Fin> struct FinanceSystemT;


template <class Fin>
struct FinanceSystemT : FinSystem {
	
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

