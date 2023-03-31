// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IAudioFileOut_IAudioFileOut_h_
#define _IAudioFileOut_IAudioFileOut_h_

#include <ParallelLib/ParallelLib.h>

NAMESPACE_PARALLEL_BEGIN

#define AFO_CLS_LIST(x) \
	AFO_CLS(Sink, x) \

#define AFO_VNDR_LIST \
	AFO_VNDR(AFOCoreAudio) \

#define AFO_CLS(x, v) struct v##x;
#define AFO_VNDR(x) AFO_CLS_LIST(x)
AFO_VNDR_LIST
#undef AFO_VNDR
#undef AFO_CLS

struct AFOCoreAudio {
	struct NativeSink;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct AFOSink : public Atom {
	RTTI_DECL1(AFOSink, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~AFOSink() {}
};


template <class AFO> struct AudioFileOutSinkT : AFOSink {
	using CLASSNAME = AudioFileOutSinkT<AFO>;
	RTTI_DECL1(CLASSNAME, AFOSink)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) AFO::Sink_Visit(*dev, *this, vis);
		vis.VisitThis<AFOSink>(this);
	}
	typename AFO::NativeSink* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!AFO::Sink_Create(dev))
			return false;
		if (!AFO::Sink_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!AFO::Sink_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return AFO::Sink_Start(*dev, *this);
	}
	void Stop() override {
		AFO::Sink_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		AFO::Sink_Uninitialize(*dev, *this);
		AFO::Sink_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!AFO::Sink_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return AFO::Sink_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return AFO::Sink_Finalize(*dev, *this, cfg);
	}
	bool IsReady(PacketIO& io) override {
		return AFO::Sink_IsReady(*dev, *this, io);
	}
};

using CoreAudioSink = AudioFileOutSinkT<AFOCoreAudio>;

NAMESPACE_PARALLEL_END

#endif
