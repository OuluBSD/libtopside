#include "EcsAudioCore.h"


NAMESPACE_TOPSIDE_BEGIN


AudioFormat ConvertPortaudioFormat(Portaudio::AudioFormat fmt) {
	AudioFormat r;
	r.channels = fmt.channels;
	r.freq = fmt.freq;
	r.sample_rate = fmt.sample_rate;
	switch (fmt.fmt) {
		#if CPU_BIG_ENDIAN
		#error TODO
		#endif
		
		case Portaudio::SND_FLOAT32:
			r.SetType(SoundSample::FLT_LE);
			break;
		case Portaudio::SND_INT32:
			r.SetType(SoundSample::S32_LE);
			break;
		case Portaudio::SND_INT24:
			r.SetType(SoundSample::S24_LE);
			break;
		case Portaudio::SND_INT16:
			r.SetType(SoundSample::S16_LE);
			break;
		case Portaudio::SND_INT8:
			r.SetType(SoundSample::S8_LE);
			break;
		case Portaudio::SND_UINT8:
			r.SetType(SoundSample::U8_LE);
			break;
		default:
			THROW(Exc("invalid portaudio sound sample format"));
	}
	return r;
}


namespace Portaudio {
	
	
BufferedAudioDeviceStream::BufferedAudioDeviceStream() {
	WhenAction << THISBACK(SinkCallback);
}

void BufferedAudioDeviceStream::SinkCallback(StreamCallbackArgs& args) {
	if (consumer.IsEmptySource())
		consumer.SetSource(buf.GetBuffer());
	
	if (args.output) {
		TS::AudioFormat fmt = ConvertPortaudioFormat(AudioBase::fmt);
		
		int size = fmt.GetFrameSize();
		if (buf.GetQueueSize() > 0 || consumer.HasLeftover()) {
			ASSERT(args.fpb == fmt.sample_rate);
			
			consumer.SetDestination(fmt, args.output, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			if (consumer.GetLastMemoryBytes() != size) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: error: consumed " << consumer.GetLastMemoryBytes() << " (expected " << size << ")");
			}
			
			int consumed_count = consumer.GetCount();
			if (consumed_count) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed count=" << consumed_count);
			}
			
		}
		else {
			#if DEBUG_RT_PIPE
			RTLOG("error: BufferedAudioDeviceStream::SinkCallback: got empty data");
			#endif
			
			memset(args.output, 0, size);
		}
	}
}

void BufferedAudioDeviceStream::OpenDefault(void* data, int inchannels,int outchannels, SampleFormat format){
	AudioDeviceStream::OpenDefault(data, inchannels, outchannels, format);
	
	TS::AudioFormat fmt = ConvertPortaudioFormat(AudioBase::fmt);
	buf.SetFormat(fmt);
}

void BufferedAudioDeviceStream::OpenDefault(int inchannels, int outchannels, SampleFormat format){
	AudioDeviceStream::OpenDefault(inchannels, outchannels, format);
	
	TS::AudioFormat fmt = ConvertPortaudioFormat(AudioBase::fmt);
	buf.SetFormat(fmt);
}



}



bool __is_portaudio_uninit;
namespace Portaudio {bool IsPortaudioUninitialized() {return __is_portaudio_uninit;}}

void CloseAudioSys() {
	Portaudio::AudioSys().Close();
	__is_portaudio_uninit = true;
}

INITBLOCK {
	CenterSystem::WhenUninit() << callback(CloseAudioSys);
}











PortaudioSinkComponent::PortaudioSinkComponent() : src_stream(this) {
	
}

PortaudioSinkComponent::~PortaudioSinkComponent() {
	obj.Clear();
}

void PortaudioSinkComponent::Initialize() {
	Component::Initialize();
	
	obj.Create();
	obj->OpenDefault();
	
	obj->Start();
	
}

void PortaudioSinkComponent::Uninitialize() {
	Component::Uninitialize();
	
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
		return *obj;
	THROW(Exc("PortaudioSinkComponent: obj is null"));
}




NAMESPACE_TOPSIDE_END
