// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 12:22:22

#ifndef _IEvent_TmplClasses_h_
#define _IEvent_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Ev> struct EventSourceDeviceT;


template <class Ev>
struct EventSourceDeviceT : EvSourceDevice {
	using CLASSNAME = EventSourceDeviceT<Ev>;
	RTTI_DECL1(CLASSNAME, EvSourceDevice)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<EvSourceDevice>(this);}
	
	typename Ev::NativeSourceDevice dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Ev::SourceDevice_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Ev::SourceDevice_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Ev::SourceDevice_Start(dev, *this);
	}

	void Stop() override {
		Ev::SourceDevice_Stop(dev, *this);
	}

	void Uninitialize() override {
		Ev::SourceDevice_Uninitialize(dev, *this);
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Ev::SourceDevice_ProcessPacket(dev, *this, in, out))
			return false;
		return true;
	}

	bool Poll(UPP::CtrlEvent& e) {
		return Ev::SourceDevice_Poll(this->dev, e);
	}
	
	uint32 GetTickCount() {
		return Ev::SourceDevice_GetTickCount(this->dev);
	}
	
	void WaitEvent(int ms) {
		Ev::SourceDevice_WaitEvent(this->dev, ms);
	}
	
	bool IsWaitingEvent() {
		return Ev::SourceDevice_IsWaitingEvent(this->dev);
	}
	
	
};

#if 0
using SdlSourceDevice = EventSourceDeviceT<EvSdl>;
#endif

#if 0
using GlfwSourceDevice = EventSourceDeviceT<EvGlfw>;
#endif

#if 0
using X11SourceDevice = EventSourceDeviceT<EvX11>;
#endif

#if 0
using Win32SourceDevice = EventSourceDeviceT<EvWin32>;
#endif


NAMESPACE_PARALLEL_END



#endif

