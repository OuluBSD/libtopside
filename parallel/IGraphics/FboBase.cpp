#include "IGraphics.h"
#include <SerialMach/SerialMach.h>

NAMESPACE_PARALLEL_BEGIN



template <class Gfx>
FboAtomT<Gfx>* FboAtomT<Gfx>::latest;

template <class Gfx>
FboAtomT<Gfx>& FboAtomT<Gfx>::Latest() {ASSERT(latest); return *latest;}


template <class Gfx>
FboAtomT<Gfx>::FboAtomT() {
	latest = this;
}

template <class Gfx>
bool FboAtomT<Gfx>::Initialize(const Script::WorldState& ws) {
	ISourceRef src = this->GetSource();
	int src_count = src->GetSourceCount();
	Value& val = src->GetSourceValue(src_count-1);
	src_type = val.GetFormat().vd;
	
	draw_mem = ws.Get(".drawmem") == "true"; // Dumb "local render" (forward raw data)
	//gfxbuf = ws.Get(".gfxbuf") == "true"; // SoftRender rending locally (not just data-forwarding)
	program = ws.Get(".program");
	gfxpack = ws.Get(".gfxpack") == "true";
	
	if (program.IsEmpty()) {
		LOG("FboAtomT<Gfx>::Initialize: error: no 'program' attribute was given");
		return false;
	}
	
	
	String bin  = program + "_program";
	auto& bin_map  = ShaderLibrary::GetBinders();
	int bin_i  = bin_map.Find(bin);
	
	if (bin_i < 0) {
		LOG("FboAtomT<Gfx>::Initialize: error: program '" << bin << "' not found");
		return false;
	}
	
	data.prog = bin_map[bin_i]();
	binders.Add(&*data.prog);
	
	Index<String> keys;
	ws.FindKeys(".program.arg.", keys);
	for (String key : keys) {
		String arg_key = key.Mid(13);
		String value = ws.Get(key);
		for (BinderIfaceVideo* b : binders) {
			if (!b->Arg(arg_key, value)) {
				LOG("FboAtomT<Gfx>::Initialize: error: program '" << bin << "' did not accept argument: " << arg_key << " = " << value);
				return false;
			}
		}
	}
	
	if (gfxpack) {
		String frag = program + "_fragment";
		String vtx  = program + "_vertex";
		auto& frag_map = SoftShaderLibrary::GetMap(GVar::FRAGMENT_SHADER);
		auto& vtx_map  = SoftShaderLibrary::GetMap(GVar::VERTEX_SHADER);
		int frag_i = frag_map.Find(frag);
		int vtx_i  = vtx_map.Find(vtx);
		
		if (frag_i < 0) {
			LOG("FboAtomT<Gfx>::Initialize: error: fragment program '" << frag << "' not found");
			return false;
		}
		
		if (vtx_i < 0) {
			LOG("FboAtomT<Gfx>::Initialize: error: vertex program '" << vtx << "' not found");
			return false;
		}
		
		data.frag_prog = frag_map[frag_i]();
		data.vtx_prog = vtx_map[vtx_i]();
	}
	
	
	return true;
}

template <class Gfx>
bool FboAtomT<Gfx>::PostInitialize() {
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

template <class Gfx>
void FboAtomT<Gfx>::Uninitialize() {
	
}

template <class Gfx>
bool FboAtomT<Gfx>::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0 &&
		binders.GetCount() > 0;
	RTLOG("FboAtomT::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

template <class Gfx>
bool FboAtomT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("FboAtomT::ProcessPackets:");
	
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
	else
	#endif
	 
	if (src_type == VD(CENTER,FBO) ||
		src_type == VD(OGL,FBO)) {
		/*Format fmt = io.src[src_ch].val->GetFormat();
		ASSERT(fmt.IsFbo());
		
		Size sz = fmt.vid.GetSize();
		int stride = fmt.vid.GetPackedCount();
		*/
		accel_sd.SetTarget(data.accel_state);
		for (BinderIfaceVideo* b : binders)
			if (!b->Render(accel_sd))
				return false;
		
		/*
		PacketIO::Sink& sink = io.sink[sink_ch];
		PacketIO::Source& src = io.src[src_ch];
		
		ASSERT(sink.p);
		sink.may_remove = true;
		src.from_sink_ch = 0;
		src.p = ReplyPacket(src_ch, sink.p);*/
		
		InternalPacketData& data = out.SetData<InternalPacketData>();
		if (gfxpack) {
			data.ptr = &this->data;
			data.SetText("gfxpack");
		}
		else {
			data.ptr = &(GfxDataState&)this->data.accel_state;
			data.SetText("gfxstate");
		}
	}
	else {
		ASSERT_(0, "TODO");
		return false;
	}
	
	#if 0
	if (src_ch > 0 && io.src[src_ch].p) {
		PacketIO::Sink& prim_sink = io.sink[0];
		PacketIO::Source& prim_src = io.src[0];
		prim_src.from_sink_ch = 0;
		prim_src.p = ReplyPacket(0, prim_sink.p);
	}
	#endif
	
	return true;
}

template <class Gfx>
void FboAtomT<Gfx>::AddBinder(BinderIfaceVideo* iface) {
	VectorFindAdd(binders, iface);
}

template <class Gfx>
void FboAtomT<Gfx>::RemoveBinder(BinderIfaceVideo* iface) {
	VectorRemoveKey(binders, iface);
}

template <class Gfx>
void FboAtomT<Gfx>::Finalize(RealtimeSourceConfig& cfg) {
	last_cfg = &cfg;
}



X11SW_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)
SDLSW_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)






template <class Gfx>
	VectorMap<String, typename SoftShaderLibraryT<Gfx>::ShaderFactory>&
		SoftShaderLibraryT<Gfx>::GetMap(int i) {
	static VectorMap<String, typename SoftShaderLibraryT<Gfx>::ShaderFactory> shader_classes[GVar::SHADERTYPE_COUNT];
	ASSERT(i >= 0 && i < GVar::SHADERTYPE_COUNT);
	return shader_classes[i];
}

/*template <class Gfx>
	VectorMap<String, typename ShaderLibraryT<Gfx>::VideoBinderFactory>&
		SoftShaderLibraryT<Gfx>::GetBinders() {
	static VectorMap<String, SoftShaderLibraryT<Gfx>::VideoBinderFactory> m;
	return m;
}*/


SDLSW_EXCPLICIT_INITIALIZE_CLASS(SoftShaderLibraryT)
X11SW_EXCPLICIT_INITIALIZE_CLASS(SoftShaderLibraryT)
//X11OGL_EXCPLICIT_INITIALIZE_CLASS(SoftShaderLibraryT)


NAMESPACE_PARALLEL_END
