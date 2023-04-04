// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IScreen_IScreen_h_
#define _IScreen_IScreen_h_

#include <ParallelLib/ParallelLib.h>
#include <IGraphics/IGraphics.h>

NAMESPACE_PARALLEL_BEGIN

#define SCR_CLS_LIST(x) \
	SCR_CLS(SinkDevice, x) \
	SCR_CLS(Context, x) \
	SCR_CLS(EventsBase, x) \

#define SCR_VNDR_LIST \
	SCR_VNDR(ScrX11) \
	SCR_VNDR(ScrX11Sw) \
	SCR_VNDR(ScrX11Ogl) \
	SCR_VNDR(ScrWin) \
	SCR_VNDR(ScrWinDx) \

#define SCR_CLS(x, v) struct v##x;
#define SCR_VNDR(x) SCR_CLS_LIST(x)
SCR_VNDR_LIST
#undef SCR_VNDR
#undef SCR_CLS

#if (defined flagPOSIXDESKTOP && defined flagSCREEN)
struct ScrX11 {
	struct NativeSinkDevice;
	struct NativeContext;
	struct NativeEventsBase;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagPOSIXDESKTOP && defined flagSCREEN)
struct ScrX11Sw {
	struct NativeSinkDevice;
	struct NativeContext;
	struct NativeEventsBase;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagPOSIXDESKTOP && defined flagSCREEN && defined flagOGL)
struct ScrX11Ogl {
	struct NativeSinkDevice;
	struct NativeContext;
	struct NativeEventsBase;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagWIN32 && defined flagSCREEN)
struct ScrWin {
	struct NativeSinkDevice;
	struct NativeContext;
	struct NativeEventsBase;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagWIN32 && defined flagSCREEN && defined flagDX)
struct ScrWinDx {
	struct NativeSinkDevice;
	struct NativeContext;
	struct NativeEventsBase;
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

struct ScrSinkDevice : public Atom {
	RTTI_DECL1(ScrSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrSinkDevice() {}
};

struct ScrContext : public Atom {
	RTTI_DECL1(ScrContext, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrContext() {}
};

struct ScrEventsBase : public Atom {
	RTTI_DECL1(ScrEventsBase, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrEventsBase() {}
};


template <class Scr> struct ScreenSinkDeviceT : ScrSinkDevice {
	using CLASSNAME = ScreenSinkDeviceT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrSinkDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Scr::SinkDevice_Visit(*dev, *this, vis);
		vis.VisitThis<ScrSinkDevice>(this);
	}
	typename Scr::NativeSinkDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Scr::SinkDevice_Create(dev))
			return false;
		if (!Scr::SinkDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Scr::SinkDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Scr::SinkDevice_Start(*dev, *this);
	}
	void Stop() override {
		Scr::SinkDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Scr::SinkDevice_Uninitialize(*dev, *this);
		Scr::SinkDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Scr::SinkDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Scr::SinkDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Scr::SinkDevice_Finalize(*dev, *this, cfg);
	}
	bool IsReady(PacketIO& io) override {
		return Scr::SinkDevice_IsReady(*dev, *this, io);
	}
	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override {
		return Scr::SinkDevice_NegotiateSinkFormat(*dev, *this, link, sink_ch, new_fmt);
	}
};
template <class Scr> struct ScreenContextT : ScrContext {
	using CLASSNAME = ScreenContextT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrContext)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Scr::Context_Visit(*dev, *this, vis);
		vis.VisitThis<ScrContext>(this);
	}
	typename Scr::NativeContext* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Scr::Context_Create(dev))
			return false;
		if (!Scr::Context_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Scr::Context_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Scr::Context_Start(*dev, *this);
	}
	void Stop() override {
		Scr::Context_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Scr::Context_Uninitialize(*dev, *this);
		Scr::Context_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Scr::Context_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Scr::Context_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Scr::Context_Finalize(*dev, *this, cfg);
	}
	bool IsReady(PacketIO& io) override {
		return Scr::Context_IsReady(*dev, *this, io);
	}
	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override {
		return Scr::Context_NegotiateSinkFormat(*dev, *this, link, sink_ch, new_fmt);
	}
};
template <class Scr> struct ScreenEventsBaseT : ScrEventsBase {
	using CLASSNAME = ScreenEventsBaseT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrEventsBase)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Scr::EventsBase_Visit(*dev, *this, vis);
		vis.VisitThis<ScrEventsBase>(this);
	}
	typename Scr::NativeEventsBase* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Scr::EventsBase_Create(dev))
			return false;
		if (!Scr::EventsBase_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Scr::EventsBase_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Scr::EventsBase_Start(*dev, *this);
	}
	void Stop() override {
		Scr::EventsBase_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Scr::EventsBase_Uninitialize(*dev, *this);
		Scr::EventsBase_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Scr::EventsBase_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Scr::EventsBase_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Scr::EventsBase_Finalize(*dev, *this, cfg);
	}
	bool IsReady(PacketIO& io) override {
		return Scr::EventsBase_IsReady(*dev, *this, io);
	}
	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override {
		return Scr::EventsBase_NegotiateSinkFormat(*dev, *this, link, sink_ch, new_fmt);
	}
};

#if (defined flagPOSIXDESKTOP && defined flagSCREEN)
using X11SinkDevice = ScreenSinkDeviceT<ScrX11>;
using X11Context = ScreenContextT<ScrX11>;
using X11EventsBase = ScreenEventsBaseT<ScrX11>;
#endif
#if (defined flagPOSIXDESKTOP && defined flagSCREEN)
using X11SwSinkDevice = ScreenSinkDeviceT<ScrX11Sw>;
using X11SwContext = ScreenContextT<ScrX11Sw>;
using X11SwEventsBase = ScreenEventsBaseT<ScrX11Sw>;
#endif
#if (defined flagPOSIXDESKTOP && defined flagSCREEN && defined flagOGL)
using X11OglSinkDevice = ScreenSinkDeviceT<ScrX11Ogl>;
using X11OglContext = ScreenContextT<ScrX11Ogl>;
using X11OglEventsBase = ScreenEventsBaseT<ScrX11Ogl>;
#endif
#if (defined flagWIN32 && defined flagSCREEN)
using WinSinkDevice = ScreenSinkDeviceT<ScrWin>;
using WinContext = ScreenContextT<ScrWin>;
using WinEventsBase = ScreenEventsBaseT<ScrWin>;
#endif
#if (defined flagWIN32 && defined flagSCREEN && defined flagDX)
using WinDxSinkDevice = ScreenSinkDeviceT<ScrWinDx>;
using WinDxContext = ScreenContextT<ScrWinDx>;
using WinDxEventsBase = ScreenEventsBaseT<ScrWinDx>;
#endif

NAMESPACE_PARALLEL_END

#endif
