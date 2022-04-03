// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 22:44:00

#ifndef _IElectricSimulator_TmplClasses_h_
#define _IElectricSimulator_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Esim> struct ElectricSimulatorSystemT;


template <class Esim>
struct ElectricSimulatorSystemT : EsimSystem {
	using CLASSNAME = ElectricSimulatorSystemT<Esim>;
	RTTI_DECL1(CLASSNAME, EsimSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<EsimSystem>(this);}
	
	
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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

