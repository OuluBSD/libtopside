// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IMath_TmplClasses_h_
#define _IMath_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Math> struct MathSystemT;


template <class Math>
struct MathSystemT : MathSystem {
	
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

