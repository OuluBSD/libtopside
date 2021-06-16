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
			
			/*off32 begin_offset = buf.GetOffset();
			if (0) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: trying to consume " << begin_offset.ToString());
				RTLOG("BufferedAudioDeviceStream::SinkCallback: dumping");
				buf.Dump();
			}*/
			
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
			
			/*off32 end_offset = consumer.GetOffset();
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
			}*/
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
	
	//sys = GetMachine().TryGet<PortaudioSystem>();
	//if (sys)
	//	dev.Create(sys->GetDefaultOutput());
	
	obj.Create();
	obj->OpenDefault();
	
	obj->Start();
	
	//AddToContext<CenterSpec>(AsRef<CenterSink>());
}

void PortaudioSinkComponent::Uninitialize() {
	Component::Uninitialize();
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSink>());
	
	//dev.Clear();
	//sys.Clear();
	obj->Stop();
	obj.Clear();
}

AudioFormat PortaudioSinkComponent::GetFormat(AudCtx) {
	TODO
}

Audio& PortaudioSinkComponent::GetValue(AudCtx) {
	if (obj)
		return *obj;
	THROW(Exc("PortaudioSinkComponent: obj is null"));
}




NAMESPACE_TOPSIDE_END
