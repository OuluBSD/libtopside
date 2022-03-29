// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IAircraftSimulator_TmplClasses_h_
#define _IAircraftSimulator_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Asim> struct AircraftSimulatorSystemT;


template <class Asim>
struct AircraftSimulatorSystemT : AsimSystem {
	
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

