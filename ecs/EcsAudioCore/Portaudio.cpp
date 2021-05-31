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
		consumer.SetSource(buf);
	
	if (args.output) {
		Topside::AudioFormat fmt = ConvertPortaudioFormat(this->fmt);
		
		int size = fmt.GetFrameSize();
		if (buf.GetQueueSize() > 0 || consumer.HasLeftover()) {
			ASSERT(args.fpb == fmt.sample_rate);
			
			off32 begin_offset = buf.GetOffset();
			if (0) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: trying to consume " << begin_offset.ToString());
				RTLOG("BufferedAudioDeviceStream::SinkCallback: dumping");
				buf.Dump();
			}
			
			consumer.TestSetOffset(begin_offset);
			
			consumer.SetDestination(fmt, args.output, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			if (consumer.GetLastMemoryBytes() != size) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: error: consumed " << consumer.GetLastMemoryBytes() << " (expected " << size << ")");
			}
			
			off32 end_offset = consumer.GetOffset();
			off32 diff = off32::GetDifference(begin_offset, end_offset);
			if (diff) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed count=" << diff.ToString());
				buf.RemoveFirst(diff.value);
			}
			else if (consumer.HasLeftover()) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed packet partially");
			}
			else if (!consumer.HasLeftover()) {
				RTLOG("error: BufferedAudioDeviceStream::SinkCallback: device error");
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
	
	Topside::AudioFormat fmt = ConvertPortaudioFormat(this->fmt);
	buf.SetSampleSize(fmt, 4*MIN_AUDIO_BUFFER_SAMPLES);
}

void BufferedAudioDeviceStream::OpenDefault(int inchannels, int outchannels, SampleFormat format){
	AudioDeviceStream::OpenDefault(inchannels, outchannels, format);
	
	Topside::AudioFormat fmt = ConvertPortaudioFormat(this->fmt);
	buf.SetSampleSize(fmt, 4*MIN_AUDIO_BUFFER_SAMPLES);
}



}



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
	THROW(Exc("PortaudioSinkComponent: obj is null"));
}




NAMESPACE_TOPSIDE_END