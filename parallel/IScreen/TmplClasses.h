// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.7 0:44:33

#ifndef _IScreen_TmplClasses_h_
#define _IScreen_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Scr> struct ScreenSinkDeviceT;


template <class Scr>
struct ScreenSinkDeviceT : ScrSinkDevice {
	using CLASSNAME = ScreenSinkDeviceT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrSinkDevice)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ScrSinkDevice>(this);}
	
	typename Scr::NativeSinkDevice dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Scr::SinkDevice_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Scr::SinkDevice_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Scr::SinkDevice_Start(dev, *this);
	}

	void Stop() override {
		Scr::SinkDevice_Stop(dev, *this);
	}

	void Uninitialize() override {
		Scr::SinkDevice_Uninitialize(dev, *this);
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Scr::SinkDevice_ProcessPacket(dev, *this, in, out))
			return false;
		return true;
	}

	
};

#if (defined flagLINUX) || (defined flagFREEBSD)
using X11SinkDevice = ScreenSinkDeviceT<ScrX11>;
#endif

#if defined flagOGL
using X11GlxSinkDevice = ScreenSinkDeviceT<ScrX11Glx>;
#endif


NAMESPACE_PARALLEL_END



#endif

