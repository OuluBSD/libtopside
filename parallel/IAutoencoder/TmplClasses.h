// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IAutoencoder_TmplClasses_h_
#define _IAutoencoder_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Aenc> struct AutoencoderSystemT;


template <class Aenc>
struct AutoencoderSystemT : AencSystem {
	
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

