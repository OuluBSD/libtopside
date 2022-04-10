// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _INeural_TmplClasses_h_
#define _INeural_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Nrl> struct NeuralNetworkT;


template <class Nrl>
struct NeuralNetworkT : NrlNetwork {
	using CLASSNAME = NeuralNetworkT<Nrl>;
	RTTI_DECL1(CLASSNAME, NrlNetwork)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<NrlNetwork>(this);}
	
	
	
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

