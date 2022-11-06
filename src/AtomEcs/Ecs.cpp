#include "AtomEcs.h"
#include <SerialLib/SerialLib.h>
#include <EcsLocal/EcsLocal.h>
#include <EcsVirtualGui/EcsVirtualGui.h>

NAMESPACE_PARALLEL_BEGIN



Callback1<EcsEventsBase*> EcsEventsBase::WhenInitialize;

EcsEventsBase* EcsEventsBase::latest;

EcsEventsBase::EcsEventsBase() {
	latest = this;
}

bool EcsEventsBase::Initialize(const Script::WorldState& ws) {
	
	target = ws.Get(".target");
	if (target.IsEmpty()) {
		LOG("EcsEventsBase::Initialize: error: target state argument is required");
		return false;
	}
	
	Space& space = GetParent();
	state = space.FindNearestState(target);
	if (!state) {
		LOG("EcsEventsBase::Initialize: error: state '" << target << "' not found in parent space: " << space.GetDeepName());
		return false;
	}
	
	#if 0
	if (!WhenInitialize) {
		LOG("EcsEventsBase::Initialize: internal error: expected ecs system to prepare this");
		return false;
	}
	
	WhenInitialize(this);
	#endif
	
	return true;
}

bool EcsEventsBase::PostInitialize() {
	return true;
}

void EcsEventsBase::Uninitialize() {
	
}

bool EcsEventsBase::IsReady(PacketIO& io) {
	if (!state) return false;
	int keyboard_iter = state->GetInt(KEYBOARD_STATE_ITER);
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0 &&
		keyboard_iter != prev_iter;
	RTLOG("EcsEventsBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EcsEventsBase::Recv(int sink_ch, const Packet& in) {
	return true;
}

void EcsEventsBase::Finalize(RealtimeSourceConfig& cfg) {
	
}

bool EcsEventsBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}







#if defined flagSCREEN

Vector<BinderIfaceVideo*> EcsVideoBase::binders;

EcsVideoBase::EcsVideoBase() {
	
}

bool EcsVideoBase::Initialize(const Script::WorldState& ws) {
	ISourceRef src = this->GetSource();
	int src_count = src->GetSourceCount();
	Value& val = src->GetSourceValue(src_count-1);
	src_type = val.GetFormat().vd;
	
	draw_mem = ws.Get(".drawmem") == "true";
	
	#ifdef flagGUI
	ents = GetMachine().Get<EntitySystem>();
	if (ents) {
		wins = ents->GetEngine().Get<Ecs::WindowSystem>();
	}
	#endif
	
	return true;
}

bool EcsVideoBase::PostInitialize() {
	
	// Remove alpha channel
	if (src_type == VD(CENTER, VIDEO)) {
		ISourceRef src = this->GetSource();
		int src_count = src->GetSourceCount();
		Serial::Link* link = GetLink();
		int src_ch = link->SideSinks().GetCount() == 1 ? link->SideSources().First().local_ch_i : src_count-1;
		Value& val = src->GetSourceValue(src_ch);
		Format fmt = val.GetFormat();
		fmt.vid.SetType(LightSampleFD::RGB_U8_LE);
		if (!link->NegotiateSourceFormat(src_ch, fmt))
			return false;
	}
	
	return true;
}

void EcsVideoBase::Uninitialize() {
	state.Clear();
	ents.Clear();
	#ifdef flagGUI
	wins.Clear();
	#endif
}

void EcsVideoBase::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<Atom>(this);
	vis & state & ents;
	#ifdef flagGUI
	vis & wins;
	#endif
}

bool EcsVideoBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	#ifdef flagGUI
	Size sz = VirtualGui3DPtr ? VirtualGui3DPtr->GetSize() : Size(800, 600);
	#else
	Size sz = Size(800, 600);
	#endif
	
	if (pd.GetPageSize() != sz)
		pd.Create(sz);
	
	bool render_win = false;
	#ifdef flagGUI
	if (wins && screen_id < wins->GetScreenCount()) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		ProgPainter& pp = pd.GetProgPainter();
		Ecs::Windows& w = wins->GetScreen(screen_id);
		
		#if 0
		ProgDraw sub;
		sub.Create(sz, w.GetCommandBegin(), w.GetCommandEnd());
		render_win = w.CheckRender();
		sub.DetachTo(pp);
		#else
		pd.cmd_screen_begin.Check();
		pp.Attach(w.GetCommandBegin(), w.GetCommandEnd());
		pd.cmd_screen_begin.Check();
		render_win = w.CheckRender();
		#endif
		pd.cmd_screen_begin.Check();
		
		render_win = true;
		//LOG("EcsVideoBase::IsReady: prog:"); LOG(pd.Dump());
	}
	#endif
	
	bool b =	io.active_sink_mask == iface_sink_mask &&
				io.full_src_mask == 0 &&
				(binders.GetCount() > 0 || render_win);
	RTLOG("EcsVideoBase::IsReady: " << (b ? "true" : "false") << " (binders " << binders.GetCount() << ", " << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	
	return b;
}

bool EcsVideoBase::Recv(int sink_ch, const Packet& in) {
	
	Format fmt = in->GetFormat();
	if (fmt.IsOrder()) {
		return true;
	}
	
	TODO
	return false;
}

bool EcsVideoBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	
	Format fmt = out.GetFormat();
	if (fmt.IsProg()) {
		
		for (BinderIfaceVideo* b : binders)
			b->Render(pd);
		
		pd.cmd_screen_begin.Check();
		
		InternalPacketData& data = out.SetData<InternalPacketData>();
		data.ptr = &pd.cmd_screen_begin;
	}
	else {
		TODO
	}
	
	return true;
}

void EcsVideoBase::AddBinder(BinderIfaceVideo* iface) {
	VectorFindAdd(binders, iface);
}

void EcsVideoBase::RemoveBinder(BinderIfaceVideo* iface) {
	VectorRemoveKey(binders, iface);
}

#endif



#if 0
Callback1<EcsOglBase*> EcsOglBase::WhenInitialize;


EcsOglBase::EcsOglBase() {
	
}

bool EcsOglBase::Initialize(const Script::WorldState& ws) {
	
	if (!WhenInitialize) {
		LOG("EcsOglBase::Initialize: internal error: expected ecs system to prepare this");
		return false;
	}
	
	WhenInitialize(this);
	
	return true;
}

bool EcsOglBase::PostInitialize() {
	return true;
}

void EcsOglBase::Uninitialize() {
	
}

bool EcsOglBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0;
	RTLOG("EcsOglBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EcsOglBase::Recv(int sink_ch, const Packet& in) {
	TODO
}

bool EcsOglBase::end(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

void EcsOglBase::AddBinder(BinderIfaceOgl* iface) {
	VectorFindAdd(binders, iface);
}

void EcsOglBase::RemoveBinder(BinderIfaceOgl* iface) {
	VectorRemoveKey(binders, iface);
}
#endif


NAMESPACE_PARALLEL_END
