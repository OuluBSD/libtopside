// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ISynth_TmplClasses_h_
#define _ISynth_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Syn> struct SynthInstrumentT;



template <class Syn>
struct SynthInstrumentT : SynInstrument {
	using CLASSNAME = SynthInstrumentT<Syn>;
	RTTI_DECL1(CLASSNAME, SynInstrument)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<SynInstrument>(this);}
	
	typename Syn::NativeInstrument dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Syn::Instrument_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Syn::Instrument_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Syn::Instrument_Start(dev, *this);
	}

	void Stop() override {
		Syn::Instrument_Stop(dev, *this);
	}

	void Uninitialize() override {
		Syn::Instrument_Uninitialize(dev, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Syn::Instrument_Send(dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool Recv(int sink_ch, const Packet& in) override {
		return Syn::Instrument_Recv(dev, *this, sink_ch, in);
	}

	void Finalize(RealtimeSourceConfig& cfg) override {
		return Syn::Instrument_Finalize(dev, *this, cfg);
	}

	bool IsReady(PacketIO& io) override {
		return Syn::Instrument_IsReady(dev, *this, io);
	}

	
};

#if 1
using SoftInstrument = SynthInstrumentT<SynSoft>;
#endif

#if defined flagFLUIDSYNTH
using FluidsynthInstrument = SynthInstrumentT<SynFluidsynth>;
#endif


NAMESPACE_PARALLEL_END

#endif

