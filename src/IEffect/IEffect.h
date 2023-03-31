// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IEffect_IEffect_h_
#define _IEffect_IEffect_h_

#include <AudioCore/AudioCore.h>
#include <ParallelLib/ParallelLib.h>

NAMESPACE_PARALLEL_BEGIN

#define FX_CLS_LIST(x) \
	FX_CLS(Effect, x) \

#define FX_VNDR_LIST \
	FX_VNDR(FxAudioCore) \
	FX_VNDR(FxLV2) \

#define FX_CLS(x, v) struct v##x;
#define FX_VNDR(x) FX_CLS_LIST(x)
FX_VNDR_LIST
#undef FX_VNDR
#undef FX_CLS

struct FxAudioCore {
	struct NativeEffect;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#if defined flagLV2
struct FxLV2 {
	struct NativeEffect;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

struct FxEffect : public Atom {
	RTTI_DECL1(FxEffect, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FxEffect() {}
};


template <class Fx> struct EffectEffectT : FxEffect {
	using CLASSNAME = EffectEffectT<Fx>;
	RTTI_DECL1(CLASSNAME, FxEffect)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Fx::Effect_Visit(*dev, *this, vis);
		vis.VisitThis<FxEffect>(this);
	}
	typename Fx::NativeEffect* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Fx::Effect_Create(dev))
			return false;
		if (!Fx::Effect_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Fx::Effect_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Fx::Effect_Start(*dev, *this);
	}
	void Stop() override {
		Fx::Effect_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Fx::Effect_Uninitialize(*dev, *this);
		Fx::Effect_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Fx::Effect_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Fx::Effect_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Fx::Effect_Finalize(*dev, *this, cfg);
	}
	bool IsReady(PacketIO& io) override {
		return Fx::Effect_IsReady(*dev, *this, io);
	}
};

using AudioCoreEffect = EffectEffectT<FxAudioCore>;
#if defined flagLV2
using LV2Effect = EffectEffectT<FxLV2>;
#endif

NAMESPACE_PARALLEL_END

#endif
