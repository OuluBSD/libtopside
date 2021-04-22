#include "EcsCore.h"

NAMESPACE_OULU_BEGIN


AudioSink* VirtualSoundPtr;


void InterfaceBase::RemoveConnection(InterfaceBase* b) {
	int i=0;
	for(auto c: conns) {
		if(c==b) {
			Unlink0(b);
			b->Unlink0(this);
			conns.Remove(i);
			break;
		}
		i++;
	}
}


#define IFACE(x) \
void ComponentBase::Signal##x##Source() {\
	Connector* conn = GetEntity().GetConnector(); \
	if (conn) conn->Signal##x##Source(); \
} \
void ComponentBase::Signal##x##Sink() {\
	Connector* conn = GetEntity().GetConnector(); \
	if (conn) conn->Signal##x##Sink(); \
}
IFACE_LIST
#undef IFACE



String InterfaceBase::GetComponentBaseTypeString(ComponentBase* base) {
	return base->GetType().CleanDemangledName();
}


#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s) {
	if (type != typeid(RouteSource)) {
		LOG(s);
	}
}
#endif


void AudioSource::DefaultEmitAudioSource(float dt, int sink_limit) {
	const auto& sinks = AudioSource::GetSinks();
	if (sink_limit >= 0) {
		//for(int i = 0; i < sinks.GetCount(); i++) {LOG(i << ": " << sinks[i]->AsComponentBase()->GetType().DemangledName());}
		ASSERT_(sinks.GetCount() <= sink_limit,
			"Only the support for single audio sink is implemented currently");
		int i = 0;
		for(const auto& c : sinks) {
			if (i++ >= sink_limit)
				break;
			c.sink->RecvAudioSink(*this, dt);
		}
	}
	else {
		for(const auto& c : sinks)
			c.sink->RecvAudioSink(*this, dt);
	}
}






void AudioSink::DefaultRecvAudioSink(AudioSinkConfig& cfg, AudioSource& src, float dt, Sound& snd) {
	dword cur_sink_frame = snd.GetWriteFrame();
	
	cfg.sync_age += dt;
	
	cfg.dt += dt;
	cfg.sink_frame = cur_sink_frame;
	
	if (cfg.sync_age >= cfg.sync_dt) {
		//DLOG("AudioSink::DefaultRecvAudioSink: sync & play more audio");
		if (cfg.sync_age > 2 * cfg.sync_dt)
			cfg.sync_age = cfg.sync_dt;
		else
			cfg.sync_age = Modulus(cfg.sync_age, cfg.sync_dt);
		
		cfg.last_sync_sink_frame = cur_sink_frame;
		
		cfg.frames_after_sync = 0;
		cfg.sync = true;
		
		src.Play(cfg, snd);
		
		//obj->CommitPlay();
	}
	else if (!snd.IsQueueFull()) {
		//DLOG("AudioSink::DefaultRecvAudioSink: play more audio");
		cfg.sync = false;
		cfg.frames_after_sync = cur_sink_frame > cfg.last_sync_sink_frame ? cur_sink_frame - cfg.last_sync_sink_frame : 0;
		//DUMP(cfg.frames_after_sync);
		src.Play(cfg, snd);
	}
	else {
		//DLOG("AudioSink::DefaultRecvAudioSink: full audio queue");
	}
}


NAMESPACE_OULU_END

