// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.8 19:22:44

#ifndef _INetFile_TmplClasses_h_
#define _INetFile_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Nef> struct NetFileNetFileT;


template <class Nef>
struct NetFileNetFileT : NefNetFile {
	using CLASSNAME = NetFileNetFileT<Nef>;
	RTTI_DECL1(CLASSNAME, NefNetFile)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<NefNetFile>(this);}
	
	
	
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

