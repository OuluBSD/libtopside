// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 12:22:22

#ifndef _IHal_TmplClasses_h_
#define _IHal_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Hal> struct HalAudioSinkDeviceT;
template <class Hal> struct HalCenterVideoSinkDeviceT;
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
		if (!Hal::AudioSinkDevice_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Hal::AudioSinkDevice_Start(dev, *this);
	}

	void Stop() override {
		Hal::AudioSinkDevice_Stop(dev, *this);
	}

	void Uninitialize() override {
		Hal::AudioSinkDevice_Uninitialize(dev, *this);
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Hal::AudioSinkDevice_ProcessPacket(dev, *this, in, out))
			return false;
		return true;
	}

	
};

template <class Hal>
struct HalCenterVideoSinkDeviceT : HalCenterVideoSinkDevice {
	using CLASSNAME = HalCenterVideoSinkDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalCenterVideoSinkDevice)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<HalCenterVideoSinkDevice>(this);}
	
	typename Hal::NativeVideoSink dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::CenterVideoSinkDevice_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Hal::CenterVideoSinkDevice_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Hal::CenterVideoSinkDevice_Start(dev, *this);
	}

	void Stop() override {
		Hal::CenterVideoSinkDevice_Stop(dev, *this);
	}

	void Uninitialize() override {
		Hal::CenterVideoSinkDevice_Uninitialize(dev, *this);
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Hal::CenterVideoSinkDevice_ProcessPacket(dev, *this, in, out))
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
		if (!Hal::ContextBase_PostInitialize(ctx, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Hal::ContextBase_Start(ctx, *this);
	}

	void Stop() override {
		Hal::ContextBase_Stop(ctx, *this);
	}

	void Uninitialize() override {
		Hal::ContextBase_Uninitialize(ctx, *this);
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Hal::ContextBase_ProcessPacket(ctx, *this, in, out))
			return false;
		return true;
	}

	bool AttachContext(AtomBase& a) override {
		return Hal::ContextBase_AttachContext(ctx, *this, a);
	}

	void DetachContext(AtomBase& a) override {
		Hal::ContextBase_DetachContext(ctx, *this, a);
	}

	
};

#if defined flagSDL2
using Sdl2AudioSinkDevice = HalAudioSinkDeviceT<HalSdl2>;
using Sdl2CenterVideoSinkDevice = HalCenterVideoSinkDeviceT<HalSdl2>;
using Sdl2ContextBase = HalContextBaseT<HalSdl2>;
#endif


NAMESPACE_PARALLEL_END



#endif

