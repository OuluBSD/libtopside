// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ISynth_ISynth_h_
#define _ISynth_ISynth_h_

#include <ParallelLib/ParallelLib.h>
#include <SoftInstru/SoftInstru.h>
#include <SoftSynth/SoftSynth.h>
#include <AudioCore/AudioCore.h>
#include <ports/fluidlite/fluidlite.h>

NAMESPACE_PARALLEL_BEGIN

#define SYN_CLS_LIST(x) \
	SYN_CLS(Instrument, x) \

#define SYN_VNDR_LIST \
	SYN_VNDR(SynSoft) \
	SYN_VNDR(SynFluidsynth) \
	SYN_VNDR(SynFmSynth) \
	SYN_VNDR(SynCoreSynth) \

#define SYN_CLS(x, v) struct v##x;
#define SYN_VNDR(x) SYN_CLS_LIST(x)
SYN_VNDR_LIST
#undef SYN_VNDR
#undef SYN_CLS

struct SynSoft {
	struct NativeInstrument;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#if defined flagFLUIDSYNTH
struct SynFluidsynth {
	struct NativeInstrument;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
struct SynFmSynth {
	struct NativeInstrument;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
struct SynCoreSynth {
	struct NativeInstrument;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct SynInstrument : public Atom {
	RTTI_DECL1(SynInstrument, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~SynInstrument() {}
};


template <class Syn> struct SynthInstrumentT : SynInstrument {
	using CLASSNAME = SynthInstrumentT<Syn>;
	RTTI_DECL1(CLASSNAME, SynInstrument)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Syn::Instrument_Visit(*dev, *this, vis);
		vis.VisitThis<SynInstrument>(this);
	}
	One<typename Syn::NativeInstrument> dev;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Syn::Instrument_Create(dev))
			return false;
		if (!Syn::Instrument_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Syn::Instrument_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Syn::Instrument_Start(*dev, *this);
	}
	void Stop() override {
		Syn::Instrument_Stop(*dev, *this);
	}
	void Uninitialize() override {
		Syn::Instrument_Uninitialize(*dev, *this);
		Syn::Instrument_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Syn::Instrument_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Syn::Instrument_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Syn::Instrument_Finalize(*dev, *this, cfg);
	}
	bool IsReady(PacketIO& io) override {
		return Syn::Instrument_IsReady(*dev, *this, io);
	}
};

using SoftInstrument = SynthInstrumentT<SynSoft>;
#if defined flagFLUIDSYNTH
using FluidsynthInstrument = SynthInstrumentT<SynFluidsynth>;
#endif
using FmSynthInstrument = SynthInstrumentT<SynFmSynth>;
using CoreSynthInstrument = SynthInstrumentT<SynCoreSynth>;

NAMESPACE_PARALLEL_END

#endif
