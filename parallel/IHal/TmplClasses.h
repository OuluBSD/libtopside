// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IHal_TmplClasses_h_
#define _IHal_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Hal> struct HalAudioSinkDeviceT;
template <class Hal> struct HalContextBaseT;


template <class Hal>
struct HalAudioSinkDeviceT : HalAudioSinkDevice {
	using CLASSNAME = HalAudioSinkDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalAudioSinkDevice)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<HalAudioSinkDevice>(this);}
	
	typename Hal::NativeAudioSinkDevice dev;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::AudioSinkDevice_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Hal::AudioSinkDevice_PostInitialize(dev))
			return false;
		return true;
	}

	bool Start() override {
		return Hal::AudioSinkDevice_Start(dev);
	}

	void Stop() override {
		Hal::AudioSinkDevice_Stop(dev);
	}

	void Uninitialize() override {
		Hal::AudioSinkDevice_Uninitialize(dev);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Hal::AudioSinkDevice_ProcessPacket(dev, v))
			return false;
		return true;
	}

	
};

template <class Hal>
struct HalContextBaseT : HalContextBase {
	using CLASSNAME = HalContextBaseT<Hal>;
	RTTI_DECL1(CLASSNAME, HalContextBase)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<HalContextBase>(this);}
	
	typename Hal::NativeContextBase ctx;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::ContextBase_Initialize(ctx, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Hal::ContextBase_PostInitialize(ctx))
			return false;
		return true;
	}

	bool Start() override {
		return Hal::ContextBase_Start(ctx);
	}

	void Stop() override {
		Hal::ContextBase_Stop(ctx);
	}

	void Uninitialize() override {
		Hal::ContextBase_Uninitialize(ctx);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Hal::ContextBase_ProcessPacket(ctx, v))
			return false;
		return true;
	}

	
};

#if defined flagSDL2
using Sdl2AudioSinkDevice = HalAudioSinkDeviceT<HalSdl2>;
using Sdl2ContextBase = HalContextBaseT<HalSdl2>;
#endif


NAMESPACE_PARALLEL_END



#endif

