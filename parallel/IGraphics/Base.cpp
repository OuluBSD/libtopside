#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

template <class Gfx>
bool ShaderBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	
	if (!this->bf.Initialize(*this, ws))
		return false;
	
	int queue_size = 1;
	
	if (this->bf.IsAudio())
		queue_size = DEFAULT_AUDIO_QUEUE_SIZE;
	
	InterfaceSinkRef sink_iface = this->GetSink();
	InterfaceSourceRef src_iface = this->GetSource();
	if (queue_size == 1) {
		int c = sink_iface->GetSinkCount();
		for(int i = 0; i < c; i++)
			sink_iface->GetValue(i).SetMaxQueueSize(queue_size);
		
		c = src_iface->GetSourceCount();
		for(int i = 0; i < c; i++)
			src_iface->GetSourceValue(i).SetMaxQueueSize(queue_size);
	}
	else {
		int c = sink_iface->GetSinkCount();
		for(int i = 0; i < c; i++)
			sink_iface->GetValue(i).SetMinQueueSize(queue_size);
		
		c = src_iface->GetSourceCount();
		for(int i = 0; i < c; i++)
			src_iface->GetSourceValue(i).SetMinQueueSize(queue_size);
	}
	
	if (!this->bf.ImageInitialize(false, Size(0,0)))
		return false;
	
	return true;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::PostInitialize() {
	return true;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::Start() {
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
bool ShaderBaseT<Gfx>::Send(PacketValue& out, int src_ch) {
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

/*bool Send(PacketValue& out, int src_ch) override
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
	if (!buf.IsInitialized()) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		auto& fb = buf.fb;
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
			if (!buf.InitializeCubemap(
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
			if (!buf.InitializeTexture(
				fb.size,
				fb.channels,
				GVar::SAMPLE_U8,
				&*in_data.Begin(),
				in_data.GetCount()))
				return false;
		}
		else {
			if (!buf.InitializeVolume(
				Size3(fb.size.cx, fb.size.cy, fb.depth),
				fb.channels,
				GVar::SAMPLE_U8,
				in_data))
				return false;
		}
	}
	else {
		buf.ReadTexture(
			sz,
			channels,
			GVar::SAMPLE_U8,
			in.GetData());
	}
	
	return true;
}

template <class Gfx>
bool TextureBaseT<Gfx>::Send(PacketValue& out, int src_ch) {
	if (src_ch >= 1) {
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
	if (new_fmt.IsValid() && new_fmt.IsVideo()) {
		ISinkRef sink = this->GetSink();
		Value& val = sink->GetValue(sink_ch);
		val.SetFormat(new_fmt);
		return true;
	}
	return false;
}












GFX3D_EXCPLICIT_INITIALIZE_CLASS(TextureBaseT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
/*X11SW_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)*/


NAMESPACE_PARALLEL_END
