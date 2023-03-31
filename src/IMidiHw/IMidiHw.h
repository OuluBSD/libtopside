// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMidiHw_IMidiHw_h_
#define _IMidiHw_IMidiHw_h_

#include <ParallelLib/ParallelLib.h>
#include <MidiFile/MidiFile.h>

NAMESPACE_PARALLEL_BEGIN

#define MID_CLS_LIST(x) \
	MID_CLS(Source, x) \

#define MID_VNDR_LIST \
	MID_VNDR(MidPortmidi) \

#define MID_CLS(x, v) struct v##x;
#define MID_VNDR(x) MID_CLS_LIST(x)
MID_VNDR_LIST
#undef MID_VNDR
#undef MID_CLS

#if (defined flagPORTMIDI) || (defined flagBUILTIN_PORTMIDI)
struct MidPortmidi {
	struct NativeSource;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

struct MidSource : public Atom {
	RTTI_DECL1(MidSource, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~MidSource() {}
};


template <class Mid> struct MidiHwSourceT : MidSource {
	using CLASSNAME = MidiHwSourceT<Mid>;
	RTTI_DECL1(CLASSNAME, MidSource)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Mid::Source_Visit(*dev, *this, vis);
		vis.VisitThis<MidSource>(this);
	}
	typename Mid::NativeSource* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Mid::Source_Create(dev))
			return false;
		if (!Mid::Source_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Mid::Source_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Mid::Source_Start(*dev, *this);
	}
	void Stop() override {
		Mid::Source_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Mid::Source_Uninitialize(*dev, *this);
		Mid::Source_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Mid::Source_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool IsReady(PacketIO& io) override {
		return Mid::Source_IsReady(*dev, *this, io);
	}
};

#if (defined flagPORTMIDI) || (defined flagBUILTIN_PORTMIDI)
using PortmidiSource = MidiHwSourceT<MidPortmidi>;
#endif

NAMESPACE_PARALLEL_END

#endif
