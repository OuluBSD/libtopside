#include "IScreen.h"


#if defined flagGUI && defined flagUPPCORE
#include <CtrlLib/CtrlLib.h>

NAMESPACE_PARALLEL_BEGIN

struct ScrUppCtrl::NativeContext {
    ::UPP::TopWindow* win;
    ::UPP::ImageBuffer* fb;
    bool running = false;
};

struct ScrUppCtrl::NativeSinkDevice {
    NativeContext* ctx;
    Packet last_frame;
    SpinLock lock;
    Callback cb;
    bool last_frame_waiting = false;
};

struct ScrUppCtrl::NativeEventsBase {
    NativeContext* ctx;
    int time;
    dword seq;
    Vector<UPP::CtrlEvent> ev;
    Size sz;
    bool ev_sendable;
    bool is_lalt;
    bool is_ralt;
    bool is_lshift;
    bool is_rshift;
    bool is_lctrl;
    bool is_rctrl;
    Point prev_mouse_pt;
};


bool ScrUppCtrl::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void ScrUppCtrl::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
}

void ScrUppCtrl::SinkDevice_Visit(NativeSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrUppCtrl::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	return true;
}

bool ScrUppCtrl::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool ScrUppCtrl::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void ScrUppCtrl::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	auto& ctx = *dev.ctx;
}

void ScrUppCtrl::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	a.SetDependency(0);
	auto& ctx = *dev.ctx;
}

bool ScrUppCtrl::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	auto& ctx = *dev.ctx;
	
	dev.lock.Enter();
	dev.last_frame = in;
	dev.lock.Leave();
	
	if (!dev.last_frame_waiting) {
		dev.last_frame_waiting = true;
		dev.cb();
	}
	
	return true;
}

void ScrUppCtrl::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool ScrUppCtrl::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool ScrUppCtrl::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	TODO
	return false;
}

bool ScrUppCtrl::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}







bool ScrUppCtrl::Context_Create(NativeContext*& dev) {
	dev = new NativeContext;
	return true;
}

void ScrUppCtrl::Context_Destroy(NativeContext*& dev) {
	delete dev;
}

void ScrUppCtrl::Context_Visit(NativeContext& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrUppCtrl::Context_Initialize(NativeContext& ctx, AtomBase& a, const Script::WorldState& ws) {
	return true;
}

bool ScrUppCtrl::Context_PostInitialize(NativeContext& ctx, AtomBase& a) {
	return true;
}

bool ScrUppCtrl::Context_Start(NativeContext& ctx, AtomBase& a) {
	return true;
}

void ScrUppCtrl::Context_Stop(NativeContext& ctx, AtomBase& a) {
	
}

void ScrUppCtrl::Context_Uninitialize(NativeContext& ctx, AtomBase& a) {
	
}

bool ScrUppCtrl::Context_Send(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return false;
}

bool ScrUppCtrl::Context_Recv(NativeContext& ctx, AtomBase& a, int sink_ch, const Packet&) {
	return false;
}

void ScrUppCtrl::Context_Finalize(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrUppCtrl::Context_NegotiateSinkFormat(NativeContext& ctx, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}

bool ScrUppCtrl::Context_IsReady(NativeContext& dev, AtomBase&, PacketIO& io) {
	return true;
}





bool ScrUppCtrl::EventsBase_Create(NativeEventsBase*& dev) {
	dev = new NativeEventsBase;
	return true;
}

void ScrUppCtrl::EventsBase_Destroy(NativeEventsBase*& dev) {
	delete dev;
}

void ScrUppCtrl::EventsBase_Visit(NativeEventsBase& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrUppCtrl::EventsBase_Initialize(NativeEventsBase& ev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<UppCtrlContext>(1);
	ASSERT(ctx_);
	if (!ctx_) {RTLOG("error: could not find UppCtrl context"); return false;}
	
	TODO
	#if 0
	ev.ctx = &*ctx_->dev;
	#endif
	
	return true;
}

bool ScrUppCtrl::EventsBase_PostInitialize(NativeEventsBase& ev, AtomBase& a) {
	if (!ev.ctx->win) {
		LOG("ScrUppCtrl::EventsBase_PostInitialize: error: context has no window");
		return false;
	}
	
	return true;
}

bool ScrUppCtrl::EventsBase_Start(NativeEventsBase& ev, AtomBase& a) {
	
	return true;
}

void ScrUppCtrl::EventsBase_Stop(NativeEventsBase& ev, AtomBase& a) {
	
}

void ScrUppCtrl::EventsBase_Uninitialize(NativeEventsBase& ev, AtomBase& a) {
	
}

bool ScrUppCtrl::EventsBase_Send(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.ev_sendable);
	if (!dev.ev_sendable)
		return false;
	

	Format fmt = out.GetFormat();
	RTLOG("ScrUppCtrl::EventsBase_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		out.seq = dev.seq++;
		CtrlEventCollection& dst = out.SetData<CtrlEventCollection>();
		dst <<= dev.ev;
		dev.ev_sendable = false;
	}
	
	return true;
}

bool ScrUppCtrl::EventsBase_Recv(NativeEventsBase& ev, AtomBase& a, int sink_ch, const Packet&) {
	
	return true;
}

bool UppCoreEvents__Poll(ScrUppCtrl::NativeEventsBase& dev, AtomBase& a) {
	Vector<UPP::CtrlEvent>& evec = dev.ev;
	evec.SetCount(0);
	evec.Reserve(100);
	
	return false;
}

bool ScrUppCtrl::EventsBase_IsReady(NativeEventsBase& dev, AtomBase& a, PacketIO& io) {
	bool b = io.full_src_mask == 0;
	if (b) {
		if (UppCoreEvents__Poll(dev, a)) {
			dev.ev_sendable = true;
		}
		else {
			dev.ev_sendable = false;
			b = false;
		}
	}
	RTLOG("ScrUppCtrl::EventsBase_IsReady: " << (b ? "true" : "false"));
	return b;
}


void ScrUppCtrl::EventsBase_Finalize(NativeEventsBase& ev, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrUppCtrl::EventsBase_NegotiateSinkFormat(NativeEventsBase& ev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	
	return false;
}


NAMESPACE_PARALLEL_END

NAMESPACE_UPP_BEGIN


void ScrUppCtrl_SetCallback(Parallel::ScrUppCtrl::NativeSinkDevice* dev, Callback cb) {
	if (dev)
		dev->cb = cb;
}

Parallel::Packet ScrUppCtrl_GetLastFrame(Parallel::ScrUppCtrl::NativeSinkDevice* dev) {
	if (dev) {
		dev->lock.Enter();
		Parallel::Packet p = dev->last_frame;
		dev->last_frame_waiting = false;
		dev->lock.Leave();
		return p;
	}
	return Parallel::Packet();
}

NAMESPACE_UPP_END

#endif
