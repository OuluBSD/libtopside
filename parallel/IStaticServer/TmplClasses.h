// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IStaticServer_TmplClasses_h_
#define _IStaticServer_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Svt> struct StaticServerServerInstanceT;



template <class Svt>
struct StaticServerServerInstanceT : SvtServerInstance {
	using CLASSNAME = StaticServerServerInstanceT<Svt>;
	RTTI_DECL1(CLASSNAME, SvtServerInstance)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<SvtServerInstance>(this);}
	
	
	
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

