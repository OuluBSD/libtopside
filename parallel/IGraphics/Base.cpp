#include "IGraphics.h"
#include <SerialMach/SerialMach.h>


NAMESPACE_PARALLEL_BEGIN

template <class Gfx>
bool ShaderBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	
	if (!this->bf.Initialize(*this, ws))
		return false;
	
	int queue_size = 1;
	
	if (this->bf.IsAudio())
		queue_size = DEFAULT_AUDIO_QUEUE_SIZE;
	
	this->SetQueueSize(queue_size);
	
	return true;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::PostInitialize() {
	return true;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::Start() {
	if (!this->bf.ImageInitialize(false, Size(0,0)))
		return false;
	
	return this->bf.PostInitialize();
}

template <class Gfx>
void ShaderBaseT<Gfx>::Uninitialize() {
	
}

template <class Gfx>
bool ShaderBaseT<Gfx>::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0;
	RTLOG("OglShaderBase::IsReady: " << (b ? "true" : "false"));
	return b;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	//BeginDraw();
	
	/*Gfx::SetClearValue(RGBA(0,0,0,255), 255);
	//TODO: useless? Gfx::ClearBuffers();
	Gfx::SetSmoothShading();
	Gfx::SetDepthTest();
	Gfx::SetDepthOrderLess(true);
	Gfx::SetFastPerspectiveCorrection();
	Gfx::SetTriangleBacksideCulling();
	Gfx::SetTriangleFrontsideCCW();
	Gfx::SetViewport(this->bf.GetBuffer().fb.GetSize());*/
	
	Format fmt = out.GetFormat();
	
	if (fmt.vd.val == ValCls::RECEIPT) {
		// pass
	}
	else if (fmt.vd.val == ValCls::FBO) {
		this->bf.GetBuffer().Process(*this->last_cfg);
		//CommitDraw();
		ASSERT(fmt.IsValid());
		
		InternalPacketData& data = out.GetData<InternalPacketData>();
		this->bf.GetBuffer().StoreOutputLink(data);
		RTLOG("ShaderBaseT::Send: 0, " << out.ToString());
		
		/*Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
		if (src_fmt.vd == VD(OGL,FBO)) {
			Packet& out = src.p;
			if (!out) {
				src.from_sink_ch = 1;
				out = this->ReplyPacket(src_ch, prim_sink.p);
			}
			PacketValue& val = *out;
			InternalPacketData& data = val.GetData<InternalPacketData>();
			this->GetBuffer().StoreOutputLink(data);
			RTLOG("PipeOptSideLink::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
		}*/
	}
	else {
		TODO
	}
	
	return true;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::Recv(int sink_ch, const Packet& in) {
	RTLOG("ShaderBaseT::Recv: " << sink_ch << ": " << in->ToString());
	bool succ = true;
	
	Format in_fmt = in->GetFormat();
	if (in_fmt.vd == VD(OGL,FBO)) {
		//Size3 sz = in_fmt.fbo.GetSize();
		int channels = in_fmt.fbo.GetChannels();
		
		int base = this->GetSink()->GetSinkCount() > 1 ? 1 : 0;
		if (in->IsData<InternalPacketData>()) {
			succ = this->bf.GetBuffer().LoadInputLink(sink_ch - base, in->GetData<InternalPacketData>()) && succ;
		}
		else {
			RTLOG("OglShaderBase::ProcessPackets: cannot handle packet: " << in->ToString());
		}
	}
	
	return succ;
}

template <class Gfx>
void ShaderBaseT<Gfx>::Finalize(RealtimeSourceConfig& cfg) {
	this->last_cfg = &cfg;
}

/*bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override
bool ProcessPackets(PacketIO& io) override {
	auto& buf = this->buf;
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& src = io.src[src_ch];
	src.from_sink_ch = 0;
	src.p = this->ReplyPacket(src_ch, prim_sink.p);
	
	
	bool succ = true;
	
	
	for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sink[sink_ch];
		Packet& in = sink.p;
		if (!in) {
			ASSERT(!sink.filled);
			continue;
		}
		sink.may_remove = true;
		
		RTLOG("OglShaderBase::ProcessPackets: " << sink_ch << ", " << src_ch << ": " << in->ToString());
		
		
		Format in_fmt = in->GetFormat();
		if (in_fmt.vd == VD(OGL,FBO)) {
			Size3 sz = in_fmt.fbo.GetSize();
			int channels = in_fmt.fbo.GetChannels();
			
			int base = this->GetSink()->GetSinkCount() > 1 ? 1 : 0;
			if (in->IsData<InternalPacketData>()) {
				succ = buf.LoadInputLink(sz, sink_ch - base, in->GetData<InternalPacketData>()) && succ;
			}
			else {
				RTLOG("OglShaderBase::ProcessPackets: cannot handle packet: " << in->ToString());
			}
		}
		
		
		if (sink_ch == 0) {
			
			
			//BeginDraw();
			buf.Process(*this->last_cfg);
			//CommitDraw();
			
			ASSERT(in->GetFormat().IsValid());
			
			
		}
	}
	
	InterfaceSourceRef src_iface = this->GetSource();
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
				out = this->ReplyPacket(src_ch, prim_sink.p);
			}
			PacketValue& val = *out;
			InternalPacketData& data = val.GetData<InternalPacketData>();
			this->GetBuffer().StoreOutputLink(data);
			RTLOG("OglShaderBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
		}
	}
	
	return succ;
}*/




template <class Gfx>
bool TextureBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	
	String f = ws.Get(".filter");
	if (!f.IsEmpty()) {
		if (f == "nearest")
			filter = GVar::FILTER_NEAREST;
		else if (f == "linear")
			filter = GVar::FILTER_LINEAR;
		else if (f == "mipmap")
			filter = GVar::FILTER_MIPMAP;
		else {
			LOG("OglTextureBase::Initialize: error: invalid filter string '" << f << "'");
			return false;
		}
	}
	
	String w = ws.Get(".wrap");
	if (!w.IsEmpty()) {
		if (w == "clamp")
			wrap = GVar::WRAP_CLAMP;
		else if (w == "repeat")
			wrap = GVar::WRAP_REPEAT;
		else {
			LOG("OglTextureBase::Initialize: error: invalid wrap string '" << w << "'");
			return false;
		}
	}
	
	return true;
}

template <class Gfx>
bool TextureBaseT<Gfx>::PostInitialize() {
	
	return true;
}

template <class Gfx>
void TextureBaseT<Gfx>::Uninitialize() {
	
}

template <class Gfx>
bool TextureBaseT<Gfx>::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0 && io.active_sink_mask == 0b11;
	RTLOG("OglTextureBase::IsReady: " << (b ? "true" : "false"));
	return b;
}

template <class Gfx>
bool TextureBaseT<Gfx>::Recv(int sink_ch, const Packet& p) {
	PacketValue& in = *p;
	const Vector<byte> in_data = in.GetData();
	
	Format in_fmt = in.GetFormat();
	if (in_fmt.IsOrder())
		return true;
	
	ASSERT(in_fmt.IsVideo() || in_fmt.IsVolume());
	Size3 sz;
	int channels;
	if (in_fmt.IsVideo()) {
		sz			= in_fmt.vid.GetSize();
		channels	= in_fmt.vid.GetChannels();
		
		if (in_fmt.vid.IsCubemap()) {
			if (in.seq == 0) {
				loading_cubemap = true;
				cubemap.Clear();
			}
			
			if (loading_cubemap) {
				if (in.seq == cubemap.GetCount())
					cubemap.Add(p);
				
				if (cubemap.GetCount() < 6)
					return true;
				
				RTLOG("TextureBaseT<Gfx>::Recv: cubemap receiving succeeded");
			}
		}
	}
	else if (in_fmt.IsVolume()) {
		sz			= in_fmt.vol.GetSize();
		channels	= in_fmt.vol.GetChannels();
	}
	else
		TODO
	
	
	auto& buf = this->bf.GetBuffer();
	auto& stage = buf.InitSingle();
	if (!stage.IsInitialized()) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		auto& fb = stage.fb;
		fb.is_win_fbo = false;
		fb.size = sz;
		fb.depth = sz.cz;
		fb.channels = channels;
		fb.sample = GVar::SAMPLE_FLOAT;
		fb.filter = this->filter;
		fb.wrap = this->wrap;
		fb.fps = 0;
		
		if (loading_cubemap) {
			ASSERT(cubemap.GetCount() == 6);
			if (!stage.InitializeCubemap(
					fb.size,
					fb.channels,
					GVar::SAMPLE_U8,
					cubemap[0]->GetData(),
					cubemap[1]->GetData(),
					cubemap[2]->GetData(),
					cubemap[3]->GetData(),
					cubemap[4]->GetData(),
					cubemap[5]->GetData()
				))
				return false;
		}
		else if (sz.cz == 0) {
			if (!stage.InitializeTexture(
				fb.size,
				fb.channels,
				GVar::SAMPLE_U8,
				&*in_data.Begin(),
				in_data.GetCount()))
				return false;
		}
		else {
			if (!stage.InitializeVolume(
				Size3(fb.size.cx, fb.size.cy, fb.depth),
				fb.channels,
				GVar::SAMPLE_U8,
				in_data))
				return false;
		}
	}
	else {
		if (sz.cz == 0) {
			const Vector<byte>& data = in.GetData();
			stage.ReadTexture(
				(Size)sz,
				channels,
				GVar::SAMPLE_U8,
				data.Begin(), data.GetCount());
		}
		else {
			stage.ReadTexture(
				sz,
				channels,
				GVar::SAMPLE_U8,
				in.GetData());
		}
	}
	
	return true;
}

template <class Gfx>
bool TextureBaseT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	if (src_ch >= 1) {
		// non-primary channel (src_ch>0) is allowed to not send packets
		if (!this->bf.GetBuffer().IsSingleInitialized())
			return false;
		
		Format fmt = out.GetFormat();
		
		if (fmt.vd == VD(OGL,FBO)) {
			InternalPacketData& data = out.GetData<InternalPacketData>();
			this->GetBuffer().StoreOutputLink(data);
			RTLOG("OglTextureBase::ProcessPackets: 0, " << src_ch << ": " << out.ToString());
		}
	}
	
	return true;
}

template <class Gfx>
void TextureBaseT<Gfx>::Visit(RuntimeVisitor& vis) {vis.VisitThis<BufferBase>(this);}

template <class Gfx>
bool TextureBaseT<Gfx>::NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) {
	// accept all valid video formats for now
	if (new_fmt.IsValid() && (new_fmt.IsVideo() || new_fmt.IsVolume())) {
		ISinkRef sink = this->GetSink();
		Value& val = sink->GetValue(sink_ch);
		val.SetFormat(new_fmt);
		return true;
	}
	return false;
}












template <class Gfx>
bool FboReaderBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	ISourceRef src = this->GetSource();
	Format out_fmt = src->GetSourceValue(src->GetSourceCount()-1).GetFormat();
	if (out_fmt.IsAudio()) {
		this->SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	}
	return true;
}

template <class Gfx>
bool FboReaderBaseT<Gfx>::PostInitialize() {
	return true;
}

template <class Gfx>
void FboReaderBaseT<Gfx>::Uninitialize() {
	
}

template <class Gfx>
bool FboReaderBaseT<Gfx>::IsReady(PacketIO& io) {
	dword iface_sink_mask = this->iface.GetSinkMask();
	bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
	RTLOG("OglFboReaderBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

template <class Gfx>
bool FboReaderBaseT<Gfx>::Recv(int sink_ch, const Packet& in) {
	Format fmt = in->GetFormat();
		
	if (fmt.IsFbo()) {
		/*int src_queue = src.val->GetMinPackets();
		int sink_queue = sink.val->GetMinPackets();
		ASSERT(src_queue > 1);
		ASSERT(sink_queue > 1);*/
		
		//DUMP(fmt);
		InternalPacketData& v = in->GetData<InternalPacketData>();
		if (v.IsText("gfxbuf")) {
			src_buf = CastPtr<BufferStage>(static_cast<GfxBufferStage*>(v.ptr));
			ASSERT(src_buf);
		}
		else {
			TODO
			return false;
		}
	}
	
	return true;
}

template <class Gfx>
bool FboReaderBaseT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	if (fmt.IsReceipt()) {
		//out.AddRouteData(src.from_sink_ch);
	}
	else if (fmt.IsAudio()) {
		if (!src_buf)
			return false;
		
		//out.AddRouteData(src.from_sink_ch);
		AudioFormat& afmt = fmt;
		
		//ASSERT(afmt.IsSampleFloat());
		/*int src_queue = src.val->GetMinPackets();
		int sink_queue = sink.val->GetMinPackets();
		ASSERT(src_queue > 1);
		ASSERT(sink_queue > 1);*/
		
		//DUMP(fmt);
		auto& fb = src_buf->GetFramebuffer();
		int afmt_size = afmt.GetSize();
		/*if (fb.size.cx != afmt.sample_rate && fb.size.cy != 1) {
			afmt.res[0] = afmt.sample_rate;
			afmt.res[1] = 1;
			out.SetFormat(fmt);
			afmt_size = afmt.GetSize();
		}*/
		ASSERT(fb.size.cx == afmt.sample_rate && fb.size.cy == 1 && fb.channels == afmt_size);
		int len = afmt.sample_rate * fb.channels * GVar::GetSampleSize(fb.sample);
		ASSERT(len > 0);
		Vector<byte>& out_data = out.Data();
		out_data.SetCount(len);
		
		NativeFrameBufferConstRef frame_buf = fb.GetReadFramebuffer();
		ASSERT(frame_buf);
		Gfx::BindFramebufferRO(frame_buf);
		Gfx::ReadPixels(0, 0, afmt.sample_rate, 1, fb.sample, fb.channels, out_data.Begin());
		Gfx::UnbindFramebuffer();
		
		src_buf = 0;
	}
	else TODO
	
	return true;
}

template <class Gfx>
bool FboReaderBaseT<Gfx>::NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) {
	
	TODO
	
}

template <class Gfx>
void FboReaderBaseT<Gfx>::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<BufferBase>(this);
}















template <class Gfx>
bool KeyboardBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	
	target = ws.Get(".target");
	if (target.IsEmpty()) {
		LOG("EventStateBase::Initialize: error: target state argument is required");
		return false;
	}
	
	Space& space = this->GetParent();
	state = space.FindNearestState(target);
	if (!state) {
		LOG("EventStateBase::Initialize: error: state '" << target << "' not found in parent space: " << space.GetDeepName());
		return false;
	}
	
	FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
	data.SetAll(false);
	
	return true;
}

template <class Gfx>
bool KeyboardBaseT<Gfx>::PostInitialize() {
	
	return true;
}

template <class Gfx>
void KeyboardBaseT<Gfx>::Uninitialize() {
	
}

template <class Gfx>
bool KeyboardBaseT<Gfx>::IsReady(PacketIO& io) {
	if (!state) return false;
	ASSERT(io.srcs.GetCount() >= 2);
	if (io.srcs.GetCount() < 2) return false;
	
	dword iface_sink_mask = this->iface.GetSinkMask();
	bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
	RTLOG("KeyboardBaseT<Gfx>::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

template <class Gfx>
bool KeyboardBaseT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("KeyboardBaseT<Gfx>::Send");
	auto& buf = this->bf.GetBuffer();
	auto& stage = buf.InitSingle();
	
	Format fmt = out.GetFormat();
	if (fmt.IsFbo()) {
		Size sz(FboKbd::key_tex_w, FboKbd::key_tex_h);
		int channels = 1;
		FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
		
		//LOG("KeyboardBaseT<Gfx>::Send: " << HexStr(data.GetHashValue()));
		
		if (!stage.IsInitialized()) {
			ASSERT(sz.cx > 0 && sz.cy > 0);
			auto& fb = stage.fb;
			fb.is_win_fbo = false;
			fb.size = sz;
			fb.channels = channels;
			fb.sample = GVar::SAMPLE_FLOAT;
			fb.fps = 0;
			
			if (!stage.InitializeTexture(
				Size(sz.cx, sz.cy),
				channels,
				GVar::SAMPLE_U8,
				data.Get(),
				data.GetCount() * sizeof(byte)))
				return false;
		}
		else {
			stage.ReadTexture(
				sz,
				channels,
				GVar::SAMPLE_U8,
				data.Get(),
				data.GetCount() * sizeof(byte));
		}
		
		
		InternalPacketData& d = out.GetData<InternalPacketData>();
		this->GetBuffer().StoreOutputLink(d);
		RTLOG("KeyboardBaseT<Gfx>::Send: 0, " << src_ch << ": " << out.ToString());
		
	}
	
	return true;
}












template <class Gfx>
bool AudioBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	
	return true;
}

template <class Gfx>
bool AudioBaseT<Gfx>::PostInitialize() {
	
	// e.g. opengl doesn't support 2-channel float input always, so request 16-bit uint
	ISinkRef sink = this->GetSink();
	for(int i = 0; i < sink->GetSinkCount(); i++) {
		Value& v = sink->GetValue(i);
		Format fmt = v.GetFormat();
		if (fmt.IsAudio()) {
			AudioFormat& afmt = fmt;
			afmt.SetType(SoundSample::U16_LE);
			if (!this->GetLink()->NegotiateSinkFormat(i, fmt))
				return false;
		}
	}
	
	return true;
}

template <class Gfx>
void AudioBaseT<Gfx>::Uninitialize() {
	
}

template <class Gfx>
bool AudioBaseT<Gfx>::IsReady(PacketIO& io) {
	dword iface_sink_mask = this->iface.GetSinkMask();
	bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
	RTLOG("AudioBaseT<Gfx>::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

template <class Gfx>
bool AudioBaseT<Gfx>::Recv(int sink_ch, const Packet& p) {
	RTLOG("AudioBaseT<Gfx>::Recv");
	
	const PacketValue& in = *p;
	Format fmt = in.GetFormat();
	if (fmt.IsAudio()) {
		auto& buf = this->bf.GetBuffer();
		auto& stage = buf.InitSingle();
		AudioFormat& afmt = fmt;
		
		Format sink_fmt = this->GetSink()->GetValue(sink_ch).GetFormat();
		AudioFormat& sink_afmt = sink_fmt;
		ASSERT_(sink_afmt.type == afmt.type, "packet conversion did not happen");
		
		Size sz(afmt.sample_rate, 1);
		int channels = afmt.GetSize();
		const Vector<byte>& data = in.GetData();
		
		//ASSERT(afmt.type == SoundSample::FLT_LE || afmt.type == SoundSample::U8_LE);
		GVar::Sample sample = GetGVarType(afmt.type);
		int sample_size = GVar::GetSampleSize(sample);
		
		if (!stage.IsInitialized()) {
			ASSERT(sz.cx > 0 && sz.cy > 0);
			auto& fb = stage.fb;
			fb.is_win_fbo = false;
			fb.is_audio = true;
			fb.size = sz;
			fb.channels = channels;
			fb.sample = sample;
			fb.fps = 0;
			
			// opengl fails with 2 channel internal format, so force it to 3
			//if (fb.channels == 2)
			//	fb.channels = 4;
			
			if (!stage.InitializeTexture(
				Size(sz.cx, sz.cy),
				channels,
				sample,
				&*data.Begin(),
				data.GetCount()))
				return false;
		}
		else {
			stage.ReadTexture(
				sz,
				channels,
				sample,
				&*data.Begin(),
				data.GetCount());
		}
	}
	
	return true;
}

template <class Gfx>
bool AudioBaseT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("AudioBaseT<Gfx>::Send");
	Format fmt = out.GetFormat();
	if (fmt.IsFbo()) {
		InternalPacketData& data = out.GetData<InternalPacketData>();
		this->GetBuffer().StoreOutputLink(data);
		RTLOG("AudioBaseT<Gfx>::Send: 0, " << src_ch << ": " << out.ToString());
	}
	return true;
}

/*bool ProcessPackets(PacketIO& io) {
	RTLOG("OglAudioBase::ProcessPackets");
	ASSERT(io.src.GetCount() == 2 && io.sink.GetCount() == 2);
	auto& buf = this->buf;
	
	PacketIO::Sink&		prim_sink	= io.sink[0];
	PacketIO::Source&	prim_src	= io.src[0];
	PacketIO::Sink&		sink		= io.sink[1];
	PacketIO::Source&	src			= io.src[1];
	
	ASSERT(prim_sink.p);
	prim_sink.may_remove = true;
	prim_src.from_sink_ch = 0;
	prim_src.p = this->ReplyPacket(0, prim_sink.p);
	
	ASSERT(sink.p);
	sink.may_remove = true;
	src.from_sink_ch = 0;
	src.p = this->ReplyPacket(1, sink.p);
	
	Packet& from = sink.p;
	Format from_fmt = from->GetFormat();
	ASSERT(from_fmt.IsAudio());
	AudioFormat& afmt = from_fmt;
	Size sz(afmt.sample_rate, 1);
	int channels = afmt.GetSize();
	const Vector<byte>& data = from->GetData();
	
	if (!buf.IsInitialized()) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		auto& fb = buf.fb;
		fb.is_win_fbo = false;
		fb.size = sz;
		fb.channels = channels;
		ASSERT(afmt.IsSampleFloat());
		fb.sample = GVar::SAMPLE_FLOAT;
		fb.fps = 0;
		
		if (!buf.InitializeTexture(
			Size(sz.cx, sz.cy),
			channels,
			GVar::SAMPLE_U8,
			&*data.Begin(),
			data.GetCount() * sizeof(byte)))
			return false;
	}
	else {
		buf.ReadTexture(
			sz,
			channels,
			GVar::SAMPL
template <class Gfx>
void AudioBaseT<Gfx>::E_U8,
			&*data.Begin(),
			data.GetCount() * sizeof(byte));
	}
	
	
	InterfaceSourceRef src_iface = this->GetSource();
	int src_count = src_iface->GetSourceCount();
	for (int src_ch = 1; src_ch < src_count; src_ch++) {
		PacketIO::Source& src = io.src[src_ch];
		if (!src.val)
			continue;
		Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
		if (src_fmt.vd == VD(OGL,FBO)) {
			Packet& out = src.p;
			if (!out) {
				src.from_sink_ch = 1;
				out = this->ReplyPacket(src_ch, prim_sink.p);
			}
			PacketValue& val = *out;
			InternalPacketData& data = val.GetData<InternalPacketData>();
			this->GetBuffer().StoreOutputLink(data);
			RTLOG("OglKeyboardBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
		}
	}
	
	return true;
}*/

template <class Gfx>
bool AudioBaseT<Gfx>::NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) {
	// accept all valid video formats for now
	if (new_fmt.IsValid() && new_fmt.IsAudio()) {
		ISinkRef sink = this->GetSink();
		Value& val = sink->GetValue(sink_ch);
		val.SetFormat(new_fmt);
		return true;
	}
	return false;
}










GFX3D_EXCPLICIT_INITIALIZE_CLASS(TextureBaseT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(FboReaderBaseT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(KeyboardBaseT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(AudioBaseT)
//GFX3D_EXCPLICIT_INITIALIZE_CLASS(VolumeBaseT)
/*X11SW_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)*/


NAMESPACE_PARALLEL_END
