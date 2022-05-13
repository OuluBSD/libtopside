// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMath_TmplClasses_h_
#define _IMath_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Math> struct MathSystemT;



template <class Math>
struct MathSystemT : MathSystem {
	using CLASSNAME = MathSystemT<Math>;
	RTTI_DECL1(CLASSNAME, MathSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<MathSystem>(this);}
	
	
	
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

