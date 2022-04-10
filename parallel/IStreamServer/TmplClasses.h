// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IStreamServer_TmplClasses_h_
#define _IStreamServer_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Svr> struct StreamServerStreamServerT;


template <class Svr>
struct StreamServerStreamServerT : SvrStreamServer {
	using CLASSNAME = StreamServerStreamServerT<Svr>;
	RTTI_DECL1(CLASSNAME, SvrStreamServer)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<SvrStreamServer>(this);}
	
	
	
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

