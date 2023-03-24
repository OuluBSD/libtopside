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
	//gfxpack = ws.Get(".gfxpack") == "true";
	
	if (program.IsEmpty()) {
		LOG("FboAtomT<Gfx>::Initialize: error: no 'program' attribute was given");
		return false;
	}
	
	
	String bin  = program + "_program";
	auto& bin_map  = GfxProgramLibrary::GetBinders();
	int bin_i  = bin_map.Find(bin);
	
	if (bin_i < 0) {
		LOG("FboAtomT<Gfx>::Initialize: error: program '" << bin << "' not found");
		return false;
	}
	
	Index<String> shader_keys;
	ws.FindKeys(".shader.", shader_keys);
	for (String key : shader_keys) {
		String value = ws.GetString(key);
		int begin = 8;
		int i = key.Find(".", begin);
		if (i <= begin) {
			LOG("FboAtomT<Gfx>::Initialize: error: invalid key '" << key << "'");
			return false;
		}
		PipelineState& pipe = data.GetAddPipeline("default");
		
		String prog_name = key.Mid(begin, i - begin);
		ProgramState& prog = pipe.GetAddProgram(prog_name);
		String shader_key = key.Mid(i+1);
		if (shader_key == "frag.path") {
			if (!prog.LoadShaderFile(GVar::FRAGMENT_SHADER, value, "")) {
				LOG("FboAtomT<Gfx>::Initialize: error: loading shader failed from '" << value << "'");
				return false;
			}
		}
		else if (shader_key == "frag.name") {
			if (!prog.LoadBuiltinShader(GVar::FRAGMENT_SHADER, value + "_fragment")) {
				LOG("FboAtomT<Gfx>::Initialize: error: loading builtin shader failed from '" << value << "'");
				return false;
			}
		}
		else if (shader_key == "vtx.path") {
			if (!prog.LoadShaderFile(GVar::VERTEX_SHADER, value, "")) {
				LOG("FboAtomT<Gfx>::Initialize: error: loading shader failed from '" << value << "'");
				return false;
			}
		}
		else if (shader_key == "vtx.name") {
			if (!prog.LoadBuiltinShader(GVar::VERTEX_SHADER, value + "_vertex")) {
				LOG("FboAtomT<Gfx>::Initialize: error: loading builtin shader failed from '" << value << "'");
				return false;
			}
		}
		else {
			LOG("FboAtomT<Gfx>::Initialize: error: invalid key '" << shader_key << "'");
			return false;
		}
		
		prog.pending_compilation = true;
	}
	
	
	// Create BinderIfaceVideo
	own_binder = bin_map[bin_i]();
	if (!own_binder)
		return false;
	own_binder->Initialize();
	binders.Add(&*own_binder);
	
	
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
	
	String type = ws.GetString(".type");
	if (type == "stereo")
		data.is_stereo = true;
	
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
	if (own_binder) {
		own_binder->Uninitialize();
		own_binder.Clear();
	}
	data.Clear();
}

template <class Gfx>
bool FboAtomT<Gfx>::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		(io.active_sink_mask & 0x1) &&
		io.full_src_mask == 0 &&
		binders.GetCount() > 0;
	RTLOG("FboAtomT::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

template <class Gfx>
bool FboAtomT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("FboAtomT::ProcessPackets:");
	 
	if (src_type == VD(CENTER,FBO) ||
		src_type == VD(OGL,FBO)) {
		accel_sd.SetTarget(data);
		for (BinderIfaceVideo* b : binders)
			if (!b->Render(accel_sd))
				return false;
		
		InternalPacketData& data = out.SetData<InternalPacketData>();
		
		data.ptr = &(GfxDataState&)this->data;
		data.SetText("gfxstate");
		ASSERT(data.ptr);
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
bool FboAtomT<Gfx>::Recv(int sink_ch, const Packet& in) {
	if (sink_ch > 0) {
		const InternalPacketData& data = in->GetData<InternalPacketData>();
		ASSERT(data.ptr);
		GfxDataState* gfx_state = (GfxDataState*)data.ptr;
		DataState* state = CastPtr<DataState>(gfx_state);
		ASSERT(state);
		if (state) {
			VectorFindAdd(this->data.linked, state);
		}
	}
	
	return true;
}

template <class Gfx>
void FboAtomT<Gfx>::Finalize(RealtimeSourceConfig& cfg) {
	last_cfg = &cfg;
}



X11SW_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)
SDLSW_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(FboAtomT)



NAMESPACE_PARALLEL_END
