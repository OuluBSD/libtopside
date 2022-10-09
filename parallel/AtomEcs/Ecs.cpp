#include "AtomEcs.h"
#include <SerialLib/SerialLib.h>
#include <EcsLocal/EcsLocal.h>

NAMESPACE_PARALLEL_BEGIN



Callback1<EcsEventsBase*> EcsEventsBase::WhenInitialize;


EcsEventsBase::EcsEventsBase() {
	
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
	
	
	if (!WhenInitialize) {
		LOG("EcsEventsBase::Initialize: internal error: expected ecs system to prepare this");
		return false;
	}
	
	WhenInitialize(this);
	
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
	TODO
}

bool EcsEventsBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

/*
bool EcsEventsBase::ProcessPackets(PacketIO& io) {
	
	RTLOG("EcsEventsBase::ProcessPackets: TODO");
	
	prev_iter = state->GetInt(
	KEYBOARD_STATE_ITER);
	
	if (io.sink.GetCount() == 1) {
		PacketIO::Sink& sink = io.sink[0];
		PacketIO::Source& src = io.src[0];
		
		ASSERT(sink.p);
		sink.may_remove = true;
		src.from_sink_ch = 0;
		src.p = ReplyPacket(0, sink.p);
	}
	else {
		TODO
	}
	
	return true;
}
*/
void EcsEventsBase::AddBinder(BinderIfaceEvents* iface) {
	VectorFindAdd(binders, iface);
}

void EcsEventsBase::RemoveBinder(BinderIfaceEvents* iface) {
	VectorRemoveKey(binders, iface);
}







#if defined flagSCREEN

EcsVideoBase* EcsVideoBase::latest;
EcsVideoBase& EcsVideoBase::Latest() {ASSERT(latest); return *latest;}


EcsVideoBase::EcsVideoBase() {
	latest = this;
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
	RTLOG("EcsVideoBase::IsReady: " << (b ? "true" : "false") << " (binders " << binders.GetCount() << ", " << io.nonempty_sinks << ", " << io.sink.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	
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
		
		/*if (wins && screen_id < wins->GetScreenCount()) {
			Ecs::Windows& w = wins->GetScreen(screen_id);
			ProgPainter& pp = pd.GetProgPainter();
			pp.Attach(w.GetCommandBegin(), w.GetCommandEnd());
			TODO // redraw, not w.CheckRender();
		}*/
		
		//LOG("EcsVideoBase::Send: prog:"); LOG(pd.cmd_screen_begin.GetQueueString());
		pd.cmd_screen_begin.Check();
		
		InternalPacketData& data = out.SetData<InternalPacketData>();
		data.ptr = &pd.cmd_screen_begin;
	}
	else {
		TODO
	}
	
	return true;
}
/*
bool EcsVideoBase::ProcessPackets(PacketIO& io) {
	RTLOG("EcsVideoBase::ProcessPackets:");
	
	int src_ch = io.src.GetCount() > 1 ? 1 : 0;
	int sink_ch = 0; //io.sink.GetCount() > 1 ? 1 : 0;
	
	if (src_type == VD(CENTER, PROG)) {
		
	}
	else if (src_type == VD(CENTER, VIDEO)) {
		Format fmt = io.src[src_ch].val->GetFormat();
		ASSERT(fmt.IsVideo());
		
		Size sz = fmt.vid.GetSize();
		int stride = fmt.vid.GetPackedCount();
		
		// render to memory
		if (draw_mem) {
			id.Create(sz, stride);
			for (BinderIfaceVideo* b : binders)
				b->Render(id);
			id.Finish();
			
			if (io.sink.GetCount() == 1) {
				PacketIO::Sink& sink = io.sink[sink_ch];
				PacketIO::Source& src = io.src[src_ch];
				
				ASSERT(sink.p);
				sink.may_remove = true;
				src.from_sink_ch = 0;
				src.p = ReplyPacket(src_ch, sink.p);
				
				#if 0
				Swap(src.p->Data(), id.Data());
				#else
				InternalPacketData& data = src.p->SetData<InternalPacketData>();
				data.ptr = (byte*)id.Data().Begin();
				data.count = id.Data().GetCount();
				data.SetText("gfxvector");
				#endif
			}
			else {
				TODO
			}
		}
		// render to state
		else {
			cpu_fb.size = sz;
			cpu_fb.channels = stride;
			cpu_fb.sample = GVar::SAMPLE_U8;
			cpu_sd.SetTarget(cpu_state);
			
			for (BinderIfaceVideo* b : binders)
				b->Render(cpu_sd);
			
			
			PacketIO::Sink& sink = io.sink[sink_ch];
			PacketIO::Source& src = io.src[src_ch];
			
			ASSERT(sink.p);
			sink.may_remove = true;
			src.from_sink_ch = 0;
			src.p = ReplyPacket(src_ch, sink.p);
			
			InternalPacketData& data = src.p->SetData<InternalPacketData>();
			data.ptr = &cpu_state;
			data.SetText("gfxstate");
		}
	}
	#if HAVE_OPENGL
	else if (src_type == VD(OGL,FBO)) {
		Format fmt = io.src[src_ch].val->GetFormat();
		ASSERT(fmt.IsFbo());
		
		Size sz = fmt.vid.GetSize();
		int stride = fmt.vid.GetPackedCount();
		
		ogl_sd.SetTarget(ogl_state);
		for (BinderIfaceVideo* b : binders)
			b->Render(ogl_sd);
		
		PacketIO::Sink& sink = io.sink[sink_ch];
		PacketIO::Source& src = io.src[src_ch];
		
		ASSERT(sink.p);
		sink.may_remove = true;
		src.from_sink_ch = 0;
		src.p = ReplyPacket(src_ch, sink.p);
		
		InternalPacketData& data = src.p->SetData<InternalPacketData>();
		if (1) {
			data.ptr = &ogl_state;
			data.SetText("gfxstate");
		}
		#if 0
		// deprecated
		else {
			data.ptr = &ogl_pipe;
			data.SetText("gfxpipe");
		}
		#endif
	}
	#endif
	else {
		ASSERT_(0, "TODO");
		return false;
	}
	
	if (src_ch > 0 && io.src[src_ch].p) {
		PacketIO::Sink& prim_sink = io.sink[0];
		PacketIO::Source& prim_src = io.src[0];
		prim_src.from_sink_ch = 0;
		prim_src.p = ReplyPacket(0, prim_sink.p);
	}
	
	return true;
}
*/
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
/*
bool EcsOglBase::ProcessPackets(PacketIO& io) {
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& src = io.src[src_ch];
	src.from_sink_ch = 0;
	src.p = ReplyPacket(src_ch, prim_sink.p);
	
	
	bool succ = true;
	
	
	for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sink[sink_ch];
		Packet& in = sink.p;
		if (!in) {
			ASSERT(!sink.filled);
			continue;
		}
		sink.may_remove = true;
		
		RTLOG("EcsOglBase::ProcessPackets: " << sink_ch << ", " << src_ch << ": " << in->ToString());
		
		
		Format in_fmt = in->GetFormat();
		if (in_fmt.vd == VD(OGL,FBO)) {
			Size3 sz = in_fmt.fbo.GetSize();
			int channels = in_fmt.fbo.GetChannels();
			
			int base = GetSink()->GetSinkCount() > 1 ? 1 : 0;
			if (in->IsData<InternalPacketData>()) {
				succ = buf.LoadOutputLink(sz, sink_ch - base, in->GetData<InternalPacketData>()) && succ;
			}
			else {
				RTLOG("EcsOglBase::ProcessPackets: cannot handle packet: " << in->ToString());
			}
		}
		
		
		if (sink_ch == 0) {
			
			
			//BeginDraw();
			buf.Process(*last_cfg);
			//CommitDraw();
			
			ASSERT(in->GetFormat().IsValid());
			
			
		}
	}
	
	InterfaceSourceRef src_iface = GetSource();
	int src_count = src_iface->GetSourceCount();
	for (int src_ch = 0; src_ch < src_count; src_ch++) {
		PacketIO::Source& src = io.src[src_ch];
		if (!src.val)
			continue;
		Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
		if (src_fmt.vd == VD(OGL,FBO)) {
			Packet& out = src.p;
			if (!out) {
				src.from_sink_ch = 0;
				out = ReplyPacket(src_ch, prim_sink.p);
			}
			PacketValue& val = *out;
			InternalPacketData& data = val.GetData<InternalPacketData>();
			GetBuffer().StoreOutputLink(data);
			RTLOG("EcsOglBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
		}
	}
	
	return succ;
}
*/
void EcsOglBase::AddBinder(BinderIfaceOgl* iface) {
	VectorFindAdd(binders, iface);
}

void EcsOglBase::RemoveBinder(BinderIfaceOgl* iface) {
	VectorRemoveKey(binders, iface);
}
#endif


NAMESPACE_PARALLEL_END
