// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IAircraftSimulator_TmplClasses_h_
#define _IAircraftSimulator_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Asim> struct AircraftSimulatorSystemT;



template <class Asim>
struct AircraftSimulatorSystemT : AsimSystem {
	using CLASSNAME = AircraftSimulatorSystemT<Asim>;
	RTTI_DECL1(CLASSNAME, AsimSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AsimSystem>(this);}
	
	
	
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

