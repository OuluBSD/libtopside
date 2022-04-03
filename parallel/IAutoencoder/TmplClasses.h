// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 11:11:55

#ifndef _IAutoencoder_TmplClasses_h_
#define _IAutoencoder_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Aenc> struct AutoencoderSystemT;


template <class Aenc>
struct AutoencoderSystemT : AencSystem {
	using CLASSNAME = AutoencoderSystemT<Aenc>;
	RTTI_DECL1(CLASSNAME, AencSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AencSystem>(this);}
	
	
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

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

