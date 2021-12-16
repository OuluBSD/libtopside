#include "AtomSDL2.h"
#ifdef flagSCREEN


NAMESPACE_SERIAL_BEGIN


template <class Gfx>
bool SDL2ScreenBaseT<Gfx>::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	
	String env_name = ws.Get(".env");
	if (!env_name.IsEmpty()) {
		LoopRef l = GetLoop();
		env = l->FindNearestState(env_name);
		if (!env) {
			LOG("SDL2ScreenBase::Initialize: error: environment state with name '" << env_name << "' not found");
			return false;
		}
	}
	
	close_machine = ws.Get(".close_machine") == "true";
		
	
	OBJ_CREATE
	
	Buffer& buf = this->GetBuffer();
	buf.SetEnvState(env);
	buf.AddLink(ws.Get(".link"));
	
	String loopback = ws.Get(".loopback");
	if (loopback.GetCount() && !buf.SetLoopback(loopback))
		return false;
	
	String fragment_path = ws.Get(".fragment");
	String vertex_path = ws.Get(".vertex");
	String library_path = ws.Get(".library");
	if (fragment_path.IsEmpty()) fragment_path = ws.Get(".filepath");
	
	obj->SetShaderFile(fragment_path, vertex_path, library_path);
	obj->SetFragmentShader(ws.Get(".fragshader"));
	obj->SetVertexShader(ws.Get(".vtxshader"));
	obj->SetBuffer(buf);
	obj->Sizeable(ws.Get(".sizeable") == "true");
	obj->Maximize(ws.Get(".maximize") == "true");
	obj->Fullscreen(ws.Get(".fullscreen") == "true");
	
	// ShaderBase duplicate
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
	
	AddAtomToUpdateList();
	//AtomBase::GetMachine().template Get<AtomSystem>()->AddPolling(AtomBase::AsRefT());
	GetSink()->GetValue(0).SetMaxQueueSize(1);
	
	return true;
}

template <class Gfx>
void SDL2ScreenBaseT<Gfx>::Uninitialize() {
	ev = 0;
	obj.Clear();
	RemoveAtomFromUpdateList();
	//AtomBase::GetMachine().template Get<AtomSystem>()->RemovePolling(AtomBase::AsRefT());
}

template <class Gfx>
bool SDL2ScreenBaseT<Gfx>::ProcessPackets(PacketIO& io) {
	for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sink[sink_ch];
		Packet& in = sink.p;
		if (!in)
			continue;
		sink.may_remove = true;
		
		RTLOG("SDL2ScreenBase::ProcessPackets: sink #" << sink_ch << ": " << in->ToString());
		
		if (!obj->Recv(sink_ch, in))
			return false;
		
		if (sink_ch == 0)
			obj->Render(*last_cfg);
	}
	
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& src = io.src[src_ch];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	out = ReplyPacket(src_ch, prim_sink.p);
	
	
	#if 0
	Format fmt = p->GetFormat();
	if (fmt.vd == VD(OGL,FBO)) {
		PacketValue& val = *p;
		InternalPacketData& data = val.GetData<InternalPacketData>();
		GetBuffer().StoreOutputLink(data);
	}
	#endif
	
	return true;
}

template <class Gfx>
bool SDL2ScreenBaseT<Gfx>::IsReady(PacketIO& io) {
	//dword iface_sink_mask = iface.GetSinkMask();
	//bool b = io.active_sink_mask == iface_sink_mask; // wrong here: only primary is required
	bool b = FramePollerBase::IsReady(io) && io.sink[0].filled;
	RTLOG("SDL2ScreenBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ")");
	return b;
}

template <class Gfx>
void SDL2ScreenBaseT<Gfx>::Update(double dt) {
	BufferBase::Update(dt);
	FramePollerBase::Update(dt);
	
	if (env) {
		Size& video_size = env->Set<Size>(SCREEN0_SIZE);
		const bool& close_window = env->Set<bool>(SCREEN0_CLOSE);
		Buffer& buf = this->GetBuffer();
		
		if (close_window) {
			if (close_machine)
				GetMachine().SetNotRunning();
			else
				Destroy();
		}
		else if (video_size != buf.fb.size) {
			if (video_size.cx == 0 || video_size.cy == 0)
				video_size = buf.fb.size;
			else
				buf.SetFramebufferSize(video_size);
		}
		
	}
}

template <class Gfx>
bool SDL2ScreenBaseT<Gfx>::NegotiateSinkFormat(int sink_ch, const Format& new_fmt) {
	// accept all valid video formats for now
	if (new_fmt.IsValid() && IsDefaultGfxVal<Gfx>(new_fmt.vd.val)) {
		ISinkRef sink = GetSink();
		Value& val = sink->GetValue(sink_ch);
		val.SetFormat(new_fmt);
		return true;
	}
	return false;
}


GFX_EXCPLICIT_INITIALIZE_CLASS(SDL2ScreenBaseT)


NAMESPACE_SERIAL_END

#endif
