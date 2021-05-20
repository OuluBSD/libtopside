#include "System.h"
#include "Internal.h"
#include "PortaudioCore.h"

NAMESPACE_TOPSIDE_BEGIN


bool __is_portaudio_uninit;
namespace Portaudio {bool IsPortaudioUninitialized() {return __is_portaudio_uninit;}}

void CloseAudioSys() {
	Portaudio::AudioSys().Close();
	__is_portaudio_uninit = true;
}

INITBLOCK {
	AudioSystem::WhenUninit() << callback(CloseAudioSys);
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
	
	AddToSystem<AudioSystem>(AsRef<AudioSink>());
}

void PortaudioSinkComponent::Uninitialize() {
	RemoveFromSystem<AudioSystem>(AsRef<AudioSink>());
	
	//dev.Clear();
	//sys.Clear();
	obj->Stop();
	obj.Clear();
}

#if 0
void PortaudioSinkComponent::RecvMedia(Media& media) {
	if (obj /*&& obj->WriteAvailable()*/) {
		Audio& aud = media.GetAudio();
		int frames = aud.GetQueueSize();
		AudioFormat src_fmt = aud.GetFormat();
		AudioFormat dst_fmt = obj->GetFormat();
		if (src_fmt == dst_fmt) {
			int size = src_fmt.sample_rate * src_fmt.channels;
			tmp.SetCount(size);
			for(int i = 0; i < frames; i++) {
				float* f = tmp.Begin();
				aud.Get(f, size * src_fmt.var_size);
				obj->Put(f, src_fmt.sample_rate, true);
			}
		}
		else Panic("Invalid sample type");
	}
	TODO
}
#endif

AudioFormat PortaudioSinkComponent::GetFormat(AudCtx) {
	TODO
}

Audio& PortaudioSinkComponent::GetValue(AudCtx) {
	if (obj)
		return obj->GetBuffer();
	throw Exc("PortaudioSinkComponent: obj is null");
}




NAMESPACE_TOPSIDE_END
