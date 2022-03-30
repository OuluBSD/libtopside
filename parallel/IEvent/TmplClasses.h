// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

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

	void Uninitialize() override {
		Ev::SourceDevice_Uninitialize(dev);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Ev::SourceDevice_ProcessPacket(dev, v))
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

