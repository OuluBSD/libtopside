// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IStreamServer_TmplClasses_h_
#define _IStreamServer_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Svr> struct StreamServerStreamServerT;


template <class Svr>
struct StreamServerStreamServerT : SvrStreamServer {
	
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

