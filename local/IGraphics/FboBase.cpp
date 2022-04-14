#include "IGraphics.h"
#include <SerialMach/SerialMach.h>

NAMESPACE_PARALLEL_BEGIN



template <class Backend>
FboAtomT<Backend>* FboAtomT<Backend>::latest;

template <class Backend>
FboAtomT<Backend>& FboAtomT<Backend>::Latest() {ASSERT(latest); return *latest;}


template <class Backend>
FboAtomT<Backend>::FboAtomT() {
	latest = this;
}

template <class Backend>
bool FboAtomT<Backend>::Initialize(const Script::WorldState& ws) {
	ISourceRef src = this->GetSource();
	int src_count = src->GetSourceCount();
	Value& val = src->GetSourceValue(src_count-1);
	src_type = val.GetFormat().vd;
	
	draw_mem = ws.Get(".drawmem") == "true";
	
	return true;
}

template <class Backend>
bool FboAtomT<Backend>::PostInitialize() {
	// Remove alpha channel
	if (src_type == VD(CENTER, VIDEO)) {
		ISourceRef src = this->GetSource();
		int src_count = src->GetSourceCount();
		int src_ch =
			link->SideSinks().GetCount() == 1 ?
				link->SideSinks().First().local_ch_i :
				src_count-1;
		Value& val = src->GetSourceValue(src_ch);
		Format fmt = val.GetFormat();
		fmt.vid.SetType(LightSampleFD::RGB_U8_LE);
		if (!link->NegotiateSourceFormat(src_ch, fmt))
			return false;
	}
	return true;
}

template <class Backend>
void FboAtomT<Backend>::Uninitialize() {
	
}

template <class Backend>
bool FboAtomT<Backend>::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0 &&
		binders.GetCount() > 0;
	RTLOG("FboAtomT::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

template <class Backend>
bool FboAtomT<Backend>::ProcessPacket(PacketValue& in, PacketValue& out) {
	RTLOG("FboAtomT::ProcessPackets:");
	
	TODO
	
	#if 0
	
	int src_ch = io.src_count > 1 ? 1 : 0;
	int sink_ch = 0; //io.sink_count > 1 ? 1 : 0;
	
	if (src_type == VD(CENTER, PROG)) {
		Size sz(800, 600);
		
		pd.Create(sz);
		for (BinderIfaceVideo* b : binders)
			b->Render(pd);
		pd.Finish();
		
		if (io.sink_count == 1) {
			PacketIO::Sink& sink = io.sink[sink_ch];
			PacketIO::Source& src = io.src[src_ch];
			
			ASSERT(sink.p);
			sink.may_remove = true;
			src.from_sink_ch = 0;
			src.p = this->ReplyPacket(src_ch, sink.p);
			
			InternalPacketData& data = src.p->SetData<InternalPacketData>();
			data.ptr = &pd.cmd_screen_begin;
		}
		else {
			TODO
		}
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
			
			if (io.sink_count == 1) {
				PacketIO::Sink& sink = io.sink[sink_ch];
				PacketIO::Source& src = io.src[src_ch];
				
				ASSERT(sink.p);
				sink.may_remove = true;
				src.from_sink_ch = 0;
				src.p = this->ReplyPacket(src_ch, sink.p);
				
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
			src.p = this->ReplyPacket(src_ch, sink.p);
			
			InternalPacketData& data = src.p->SetData<InternalPacketData>();
			data.ptr = &cpu_state;
			data.SetText("gfxstate");
		}
	}
	/*#if HAVE_OPENGL
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
	#endif*/
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
	
	#endif
	
	return true;
}

template <class Backend>
void FboAtomT<Backend>::AddBinder(BinderIfaceVideo* iface) {
	VectorFindAdd(binders, iface);
}

template <class Backend>
void FboAtomT<Backend>::RemoveBinder(BinderIfaceVideo* iface) {
	VectorRemoveKey(binders, iface);
}

template <class Backend>
void FboAtomT<Backend>::Finalize(RealtimeSourceConfig& cfg) {
	last_cfg = &cfg;
}



X11SW_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)


NAMESPACE_PARALLEL_END
