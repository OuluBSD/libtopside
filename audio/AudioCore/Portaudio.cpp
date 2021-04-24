#include "System.h"
#include "Internal.h"
#include "Sound.h"

NAMESPACE_OULU_BEGIN



PortaudioSystem::PortaudioSystem(Machine& m) : System<PortaudioSystem>(m) {
	
}

bool PortaudioSystem::Initialize() {
	// SoundSys
	
	return true;
}

void PortaudioSystem::Start() {
	
	
}

void PortaudioSystem::Update(float dt) {
	
	
}

void PortaudioSystem::Stop() {
	
	
}

void PortaudioSystem::Uninitialize() {
	
}










PortaudioSinkComponent::PortaudioSinkComponent() {
	
}

PortaudioSinkComponent::~PortaudioSinkComponent() {
	obj.Clear();
}

void PortaudioSinkComponent::Initialize() {
	//sys = GetMachine().TryGet<PortaudioSystem>();
	//if (sys)
	//	dev.Create(sys->GetDefaultOutput());
	aconfig.frames_after_sync = 0;
	aconfig.sync_dt = 1.5;
	
	obj.Create();
	obj->OpenDefault();
	
	obj->Start();
}

void PortaudioSinkComponent::Uninitialize() {
	//dev.Clear();
	//sys.Clear();
	obj->Stop();
	obj.Clear();
}

void PortaudioSinkComponent::RecvAudioSink(AudioSource& src, float dt) {
	DefaultRecvAudioSink(aconfig, src, dt, *obj);
}

void PortaudioSinkComponent::RecvMedia(Media& media) {
	#if 0
	if (obj /*&& obj->WriteAvailable()*/) {
		Sound& snd = media.GetSound();
		int frames = snd.GetQueueSize();
		SoundFormat src_fmt = snd.GetFormat();
		SoundFormat dst_fmt = obj->GetFormat();
		if (src_fmt == dst_fmt) {
			int size = src_fmt.sample_rate * src_fmt.channels;
			tmp.SetCount(size);
			for(int i = 0; i < frames; i++) {
				float* f = tmp.Begin();
				snd.Get(f, size * src_fmt.var_size);
				obj->Put(f, src_fmt.sample_rate, true);
			}
		}
		else Panic("Invalid sample type");
	}
	#endif
	TODO
}

SystemSound& PortaudioSinkComponent::BeginPlay() {
	TODO
}

void PortaudioSinkComponent::CommitPlay() {
	TODO
}

void PortaudioSinkComponent::UndoPlay() {
	TODO
}

SoundFormat PortaudioSinkComponent::GetFormat() {
	TODO
}



NAMESPACE_OULU_END
