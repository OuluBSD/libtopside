#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


#ifdef flagSCREEN


bool SDL2SwScreenBase::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	
	String env_name = ws.Get(".env");
	if (!env_name.IsEmpty()) {
		LoopRef l = GetLoop();
		env = l->FindNearestState(env_name);
		if (!env) {
			LOG("SDL2SwScreenBase::Initialize: error: environment state with name '" << env_name << "' not found");
			return false;
		}
	}
	
	close_machine = ws.Get(".close_machine") == "true";
	
	OBJ_CREATE
	
	AddAtomToUpdateList();
	GetSink()->GetValue(0).SetMaxQueueSize(1);
	return true;
}

void SDL2SwScreenBase::Uninitialize() {
	ev = 0;
	obj.Clear();
	RemoveAtomFromUpdateList();
}

bool SDL2SwScreenBase::NegotiateSinkFormat(int sink_ch, const Format& new_fmt) {
	// accept all valid video formats for now
	if (new_fmt.IsValid() && new_fmt.IsVideo()) {
		ISinkRef sink = GetSink();
		Value& val = sink->GetValue(sink_ch);
		val.SetFormat(new_fmt);
		return true;
	}
	return false;
}

void SDL2SwScreenBase::Update(double dt) {
	FramePollerBase::Update(dt);
	
	if (env) {
		Size& video_size = env->Set<Size>(SCREEN0_SIZE);
		const bool& close_window = env->Set<bool>(SCREEN0_CLOSE);
		//OglBuffer& buf = GetBuffer();
		
		if (close_window) {
			if (close_machine)
				GetMachine().SetNotRunning();
			else
				Destroy();
		}
		/*else if (video_size != buf.state.size) {
			if (video_size.IsEmpty())
				video_size = buf.state.size;
			else
				buf.SetFramebufferSize(video_size);
		}*/
	}
}

bool SDL2SwScreenBase::ProcessPackets(PacketIO& io) {
	PacketIO::Sink& sink = io.sink[0];
	PacketIO::Source& src = io.src[0];
	Packet& in = sink.p;
	Packet& out = src.p;
	sink.may_remove = true;
	src.from_sink_ch = 0;
	out = ReplyPacket(0, sink.p);
	
	RTLOG("SDL2SwScreenBase::ProcessPackets: sink #0 " << in->ToString());
	
	if (!obj->Recv(0, in))
		return false;
	
	obj->Render();
	
	return true;
}


#endif


NAMESPACE_SERIAL_END
