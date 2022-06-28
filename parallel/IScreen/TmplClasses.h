// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IScreen_TmplClasses_h_
#define _IScreen_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Scr> struct ScreenSinkDeviceT;
template <class Scr> struct ScreenEventsBaseT;
template <class Scr> struct ScreenContextT;



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

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Scr::SinkDevice_Send(dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool Recv(int sink_ch, const Packet& in) override {
		return Scr::SinkDevice_Recv(dev, *this, sink_ch, in);
	}

	void Finalize(RealtimeSourceConfig& cfg) override {
		return Scr::SinkDevice_Finalize(dev, *this, cfg);
	}

	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override {
		return Scr::SinkDevice_NegotiateSinkFormat(dev, *this, link, sink_ch, new_fmt);
	}

	bool IsReady(PacketIO& io) override {
		return Scr::SinkDevice_IsReady(dev, *this, io);
	}

	
};


template <class Scr>
struct ScreenEventsBaseT : ScrEventsBase {
	using CLASSNAME = ScreenEventsBaseT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrEventsBase)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ScrEventsBase>(this);}
	
	typename Scr::NativeEventsBase ev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Scr::EventsBase_Initialize(ev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Scr::EventsBase_PostInitialize(ev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Scr::EventsBase_Start(ev, *this);
	}

	void Stop() override {
		Scr::EventsBase_Stop(ev, *this);
	}

	void Uninitialize() override {
		Scr::EventsBase_Uninitialize(ev, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Scr::EventsBase_Send(ev, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool Recv(int sink_ch, const Packet& in) override {
		return Scr::EventsBase_Recv(ev, *this, sink_ch, in);
	}

	void Finalize(RealtimeSourceConfig& cfg) override {
		return Scr::EventsBase_Finalize(ev, *this, cfg);
	}

	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override {
		return Scr::EventsBase_NegotiateSinkFormat(ev, *this, link, sink_ch, new_fmt);
	}

	bool IsReady(PacketIO& io) override {
		return Scr::EventsBase_IsReady(ev, *this, io);
	}

	
};


template <class Scr>
struct ScreenContextT : ScrContext {
	using CLASSNAME = ScreenContextT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrContext)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ScrContext>(this);}
	
	typename Scr::NativeContext ctx;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Scr::Context_Initialize(ctx, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Scr::Context_PostInitialize(ctx, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Scr::Context_Start(ctx, *this);
	}

	void Stop() override {
		Scr::Context_Stop(ctx, *this);
	}

	void Uninitialize() override {
		Scr::Context_Uninitialize(ctx, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Scr::Context_Send(ctx, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool Recv(int sink_ch, const Packet& in) override {
		return Scr::Context_Recv(ctx, *this, sink_ch, in);
	}

	void Finalize(RealtimeSourceConfig& cfg) override {
		return Scr::Context_Finalize(ctx, *this, cfg);
	}

	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override {
		return Scr::Context_NegotiateSinkFormat(ctx, *this, link, sink_ch, new_fmt);
	}

	bool IsReady(PacketIO& io) override {
		return Scr::Context_IsReady(ctx, *this, io);
	}

	
};

#if (defined flagLINUX) || (defined flagFREEBSD)
using X11SinkDevice = ScreenSinkDeviceT<ScrX11>;
using X11EventsBase = ScreenEventsBaseT<ScrX11>;
using X11Context = ScreenContextT<ScrX11>;
#endif

#if (defined flagLINUX) || (defined flagFREEBSD)
using X11SwSinkDevice = ScreenSinkDeviceT<ScrX11Sw>;
using X11SwEventsBase = ScreenEventsBaseT<ScrX11Sw>;
using X11SwContext = ScreenContextT<ScrX11Sw>;
#endif

#if defined flagOGL
using X11OglSinkDevice = ScreenSinkDeviceT<ScrX11Ogl>;
using X11OglEventsBase = ScreenEventsBaseT<ScrX11Ogl>;
using X11OglContext = ScreenContextT<ScrX11Ogl>;
#endif


NAMESPACE_PARALLEL_END

#endif

