#include "AtomLocal.h"


NAMESPACE_SERIAL_BEGIN



Callback1<EcsEventsBase*> EcsEventsBase::WhenInitialize;


EcsEventsBase::EcsEventsBase() {
	
}

bool EcsEventsBase::Initialize(const Script::WorldState& ws) {
	
	target = ws.Get(".target");
	if (target.IsEmpty()) {
		LOG("EcsEventsBase::Initialize: error: target state argument is required");
		return false;
	}
	
	Loop& loop = GetParent();
	state = loop.FindNearestState(target);
	if (!state) {
		LOG("EcsEventsBase::Initialize: error: state '" << target << "' not found in parent loop: " << loop.GetDeepName());
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
	RTLOG("EcsEventsBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EcsEventsBase::ProcessPackets(PacketIO& io) {
	
	RTLOG("EcsEventsBase::ProcessPackets: TODO");
	
	prev_iter = state->GetInt(KEYBOARD_STATE_ITER);
	
	if (io.sink_count == 1) {
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

void EcsEventsBase::AddBinder(BinderIfaceEvents* iface) {
	VectorFindAdd(binders, iface);
}

void EcsEventsBase::RemoveBinder(BinderIfaceEvents* iface) {
	VectorRemoveKey(binders, iface);
}







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
	
	return true;
}

bool EcsVideoBase::PostInitialize() {
	// Remove alpha channel
	if (src_type == VD(CENTER, VIDEO)) {
		ISourceRef src = this->GetSource();
		int src_count = src->GetSourceCount();
		Value& val = src->GetSourceValue(src_count-1);
		Format fmt = val.GetFormat();
		fmt.vid.SetType(LightSampleFD::RGB_U8_LE);
		if (!NegotiateSourceFormat(src_count-1, fmt))
			return false;
	}
	return true;
}

void EcsVideoBase::Uninitialize() {
	
}

bool EcsVideoBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0 &&
		binders.GetCount() > 0;
	RTLOG("EcsVideoBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EcsVideoBase::ProcessPackets(PacketIO& io) {
	RTLOG("EcsVideoBase::ProcessPackets:");
	
	
	if (src_type == VD(CENTER, PROG)) {
		Size sz(800, 600);
		
		pd.Create(sz);
		for (BinderIfaceVideo* b : binders)
			b->Render(pd);
		pd.Finish();
		
		if (io.sink_count == 1) {
			PacketIO::Sink& sink = io.sink[0];
			PacketIO::Source& src = io.src[0];
			
			ASSERT(sink.p);
			sink.may_remove = true;
			src.from_sink_ch = 0;
			src.p = ReplyPacket(0, sink.p);
			
			InternalPacketData& data = src.p->SetData<InternalPacketData>();
			data.ptr = &pd.cmd_screen_begin;
		}
		else {
			TODO
		}
	}
	else if (src_type == VD(CENTER, VIDEO)) {
		Format fmt = io.src[0].val->GetFormat();
		ASSERT(fmt.IsVideo());
		
		Size sz = fmt.vid.GetSize();
		int stride = fmt.vid.GetPackedCount();
		
		// render to memory
		if (0) {
			id.Create(sz, stride);
			for (BinderIfaceVideo* b : binders)
				b->Render(id);
			id.Finish();
			
			if (io.sink_count == 1) {
				PacketIO::Sink& sink = io.sink[0];
				PacketIO::Source& src = io.src[0];
				
				ASSERT(sink.p);
				sink.may_remove = true;
				src.from_sink_ch = 0;
				src.p = ReplyPacket(0, sink.p);
				
				#if 0
				Swap(src.p->Data(), id.Data());
				#else
				InternalPacketData& data = src.p->SetData<InternalPacketData>();
				data.ptr = (byte*)id.Data().Begin();
				data.count = id.Data().GetCount();
				#endif
			}
			else {
				TODO
			}
		}
		// render to state
		else {
			TODO
			#if 0
			cpu_state.size = sz;
			cpu_state.channels = stride;
			cpu_state.sample = ShaderVar::SAMPLE_U8;
			sd.SetTarget(cpu_state);
			
			for (BinderIfaceVideo* b : binders)
				b->Render(sd);
			
			if (io.sink_count == 1) {
				PacketIO::Sink& sink = io.sink[0];
				PacketIO::Source& src = io.src[0];
				
				ASSERT(sink.p);
				sink.may_remove = true;
				src.from_sink_ch = 0;
				src.p = ReplyPacket(0, sink.p);
				
				InternalPacketData& data = src.p->SetData<InternalPacketData>();
				data.ptr = &cpu_state;
				data.SetText("cpustate");
			}
			else {
				TODO
			}
			#endif
		}
	}
	#if HAVE_OPENGL
	else if (src_type == VD(OGL,FBO)) {
		TODO
		#if 0
		Format fmt = io.src[0].val->GetFormat();
		ASSERT(fmt.IsFbo());
		
		Size sz = fmt.vid.GetSize();
		int stride = fmt.vid.GetPackedCount();
		
		sd.SetTarget(ogl_state);
		for (BinderIfaceVideo* b : binders)
			b->Render(sd);
		
		if (io.sink_count == 1) {
			PacketIO::Sink& sink = io.sink[0];
			PacketIO::Source& src = io.src[0];
			
			ASSERT(sink.p);
			sink.may_remove = true;
			src.from_sink_ch = 0;
			src.p = ReplyPacket(0, sink.p);
			
			InternalPacketData& data = src.p->SetData<InternalPacketData>();
			if (0) {
				data.ptr = &ogl_state;
				data.SetText("oglstate");
			}
			else {
				data.ptr = &ogl_pipe;
				data.SetText("oglpipe");
			}
		}
		else {
			TODO
		}
		#endif
	}
	#endif
	else {
		ASSERT_(0, "TODO");
		return false;
	}
	
	
	return true;
}

void EcsVideoBase::AddBinder(BinderIfaceVideo* iface) {
	VectorFindAdd(binders, iface);
}

void EcsVideoBase::RemoveBinder(BinderIfaceVideo* iface) {
	VectorRemoveKey(binders, iface);
}



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
	RTLOG("EcsOglBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

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

void EcsOglBase::AddBinder(BinderIfaceOgl* iface) {
	VectorFindAdd(binders, iface);
}

void EcsOglBase::RemoveBinder(BinderIfaceOgl* iface) {
	VectorRemoveKey(binders, iface);
}
#endif


NAMESPACE_SERIAL_END
