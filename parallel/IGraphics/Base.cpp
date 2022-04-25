#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

template <class Gfx>
bool ShaderBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	auto& buf = this->buf;
	String fragment_path = ws.Get(".fragment");
	String vertex_path = ws.Get(".vertex");
	String library_path = ws.Get(".library");
	String loopback = ws.Get(".loopback");
	
	if (fragment_path.IsEmpty()) fragment_path = ws.Get(".filepath");
	
	if (loopback.GetCount() && !buf.SetLoopback(loopback))
		return false;
	
	if (!vertex_path.IsEmpty() &&
		!buf.LoadShaderFile(GVar::VERTEX_SHADER, vertex_path, library_path))
		return false;
	
	if (!buf.LoadShaderFile(GVar::FRAGMENT_SHADER,fragment_path, library_path))
		return false;
	
	int queue_size = 1;
	
	if (ws.Get(".type") == "audio") {
		queue_size = DEFAULT_AUDIO_QUEUE_SIZE;
		is_audio = true;
	}
	
	buf.AddLink(ws.Get(".link"));
	
	// SDL2ScreenBase duplicate
	for(int i = 0; i < 4; i++) {
		String key = ".buf" + IntStr(i);
		String value = ws.Get(key);
		if (value.IsEmpty())
			;
		else if (value == "volume")
			buf.SetInputVolume(i);
		else if (value == "cubemap")
			buf.SetInputCubemap(i);
		else
			TODO
	}
	
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
	
	return true;
}

template <class Gfx>
bool ShaderBaseT<Gfx>::PostInitialize() {
	auto& buf = this->buf;
	auto& fb = buf.fb;
	fb.is_audio = is_audio;
	fb.is_win_fbo = false;
	if (!is_audio) {
		fb.size = Size(1280,720);
		fb.channels = 4;
		fb.fps = 60;
	}
	else {
		fb.size = Size(1024,1);
		fb.channels = 2;
		fb.fps = 44100.0 / 1024;
	}
	fb.sample = GVar::SAMPLE_FLOAT;
	
	if (!buf.Initialize())
		return false;
	
	return true;
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
	this->buf.Process(*this->last_cfg);
	//CommitDraw();
	ASSERT(in.GetFormat().IsValid());
	
	InternalPacketData& data = out.GetData<InternalPacketData>();
	this->buf.StoreOutputLink(data);
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
			succ = this->buf.LoadOutputLink(sz, sink_ch - base, in->GetData<InternalPacketData>()) && succ;
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


X11SW_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(ShaderBaseT)


NAMESPACE_PARALLEL_END
