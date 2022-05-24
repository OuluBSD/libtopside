// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMidiHw_TmplClasses_h_
#define _IMidiHw_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Mid> struct MidiHwSourceT;



template <class Mid>
struct MidiHwSourceT : MidSource {
	using CLASSNAME = MidiHwSourceT<Mid>;
	RTTI_DECL1(CLASSNAME, MidSource)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<MidSource>(this);}
	
	typename Mid::NativeSource dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Mid::Source_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Mid::Source_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Mid::Source_Start(dev, *this);
	}

	void Stop() override {
		Mid::Source_Stop(dev, *this);
	}

	void Uninitialize() override {
		Mid::Source_Uninitialize(dev, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Mid::Source_Send(dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool IsReady(PacketIO& io) override {
		return Mid::Source_IsReady(dev, *this, io);
	}

	
};

#if defined flagPORTMIDI
using PortmidiSource = MidiHwSourceT<MidPortmidi>;
#endif


NAMESPACE_PARALLEL_END

#endif

