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
bool ShaderBaseT<Gfx>::ProcessPacket(PacketValue& in, PacketValue& out) {
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
	
	this->bf.GetBuffer().Process(*this->last_cfg);
	//CommitDraw();
	ASSERT(in.GetFormat().IsValid());
	
	InternalPacketData& data = out.GetData<InternalPacketData>();
	this->bf.GetBuffer().StoreOutputLink(data);
	RTLOG("ShaderBaseT::ProcessPacket: 0, " << out.ToString());
	return true;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::Recv(int sink_ch, const Packet& in) {
	RTLOG("ShaderBaseT::Recv: " << sink_ch << ": " << in->ToString());
	bool succ = true;
	
	Format in_fmt = in->GetFormat();
	if (in_fmt.vd == VD(OGL,FBO)) {
		Size3 sz = in_fmt.fbo.GetSize();
		int channels = in_fmt.fbo.GetChannels();
		
		int base = this->GetSink()->GetSinkCount() > 1 ? 1 : 0;
		if (in->IsData<InternalPacketData>()) {
			succ = this->bf.GetBuffer().LoadInputLink(sz, sink_ch - base, in->GetData<InternalPacketData>()) && succ;
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

/*bool ProcessPacket(PacketValue& in, PacketValue& out) override
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



X11SW_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)


NAMESPACE_PARALLEL_END
