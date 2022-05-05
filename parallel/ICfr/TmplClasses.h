// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

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

