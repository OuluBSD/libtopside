#include "System.h"
#include "Internal.h"
#include "Sound.h"

NAMESPACE_OULU_BEGIN

void CloseSoundSys() {
	SoundSys().Close();
}

INITBLOCK {
	AudioSystem::WhenUninit << callback(CloseSoundSys);
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
	
	AddToSystem<AudioSystem>(this);
}

void PortaudioSinkComponent::Uninitialize() {
	RemoveFromSystem<AudioSystem>(this);
	
	//dev.Clear();
	//sys.Clear();
	obj->Stop();
	obj.Clear();
}

void PortaudioSinkComponent::RecvAudio(AudioSource& src, double dt) {
	DefaultRecvAudio(aconfig, src, dt, *obj);
}

#if 0
void PortaudioSinkComponent::RecvMedia(Media& media) {
	if (obj /*&& obj->WriteAvailable()*/) {
		Sound& snd = media.GetSound();
		int frames = snd.GetQueueSize();
		AudioFormat src_fmt = snd.GetFormat();
		AudioFormat dst_fmt = obj->GetFormat();
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
	TODO
}
#endif

AudioFormat PortaudioSinkComponent::GetAudioFormat() {
	TODO
}



NAMESPACE_OULU_END
