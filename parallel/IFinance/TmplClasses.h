// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IFinance_TmplClasses_h_
#define _IFinance_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Fin> struct FinanceSystemT;



template <class Fin>
struct FinanceSystemT : FinSystem {
	using CLASSNAME = FinanceSystemT<Fin>;
	RTTI_DECL1(CLASSNAME, FinSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FinSystem>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END

#endif

