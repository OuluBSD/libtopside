// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IEffect_TmplClasses_h_
#define _IEffect_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Fx> struct EffectEffectT;



template <class Fx>
struct EffectEffectT : FxEffect {
	using CLASSNAME = EffectEffectT<Fx>;
	RTTI_DECL1(CLASSNAME, FxEffect)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FxEffect>(this);}
	
	typename Fx::NativeEffect dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Fx::Effect_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Fx::Effect_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Fx::Effect_Start(dev, *this);
	}

	void Stop() override {
		Fx::Effect_Stop(dev, *this);
	}

	void Uninitialize() override {
		Fx::Effect_Uninitialize(dev, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Fx::Effect_Send(dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool Recv(int sink_ch, const Packet& in) override {
		return Fx::Effect_Recv(dev, *this, sink_ch, in);
	}

	void Finalize(RealtimeSourceConfig& cfg) override {
		return Fx::Effect_Finalize(dev, *this, cfg);
	}

	bool IsReady(PacketIO& io) override {
		return Fx::Effect_IsReady(dev, *this, io);
	}

	
};

#if 1
using AudioCoreEffect = EffectEffectT<FxAudioCore>;
#endif


NAMESPACE_PARALLEL_END

#endif

