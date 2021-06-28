#include "EcsAudioCore.h"


NAMESPACE_ECS_BEGIN


Format ConvertPortaudioFormat(Portaudio::AudioFormat pa_fmt) {
	Format fmt;
	fmt.vd = VD(CENTER,AUDIO);
	AudioFormat& r = fmt;
	r.channels = pa_fmt.channels;
	r.freq = pa_fmt.freq;
	r.sample_rate = pa_fmt.sample_rate;
	switch (pa_fmt.fmt) {
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
	return fmt;
}


namespace Portaudio {
	
	
BufferedAudioDeviceStream::BufferedAudioDeviceStream() {
	
}

void BufferedAudioDeviceStream::OpenDefault(void* data, int inchannels,int outchannels, SampleFormat format){
	AudioDeviceStream::OpenDefault(data, inchannels, outchannels, format);
	
}

void BufferedAudioDeviceStream::OpenDefault(int inchannels, int outchannels, SampleFormat format){
	AudioDeviceStream::OpenDefault(inchannels, outchannels, format);
	
}



}



bool __is_portaudio_uninit;

void CloseAudioSys() {
	Portaudio::AudioSys().Close();
	__is_portaudio_uninit = true;
}

INITBLOCK {
	ExtSystem::WhenUninit() << callback(CloseAudioSys);
}










PortaudioOutExt::PortaudioOutExt() {
	
}

PortaudioOutExt::~PortaudioOutExt() {
	obj.Clear();
}

bool PortaudioOutExt::Initialize(const Eon::WorldState& ws) {
	
	//sys = GetMachine().TryGet<PortaudioSystem>();
	//if (sys)
	//	dev.Create(sys->GetDefaultOutput());
	
	obj.Create();
	obj->WhenAction << THISBACK(SinkCallback);
	obj->OpenDefault();
	
	ExtComponent& ext = GetParent();
	Value& sink_val = ext.GetSinkValue();
	fmt = ConvertPortaudioFormat(obj->GetFormat());
	ASSERT(fmt.IsValid());
	sink_val.SetFormat(fmt);
	
	obj->Start();
	
	//AddToContext<CenterSpec>(AsRef<CenterSink>());
	return true;
}

void PortaudioOutExt::Uninitialize() {
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSink>());
	
	//dev.Clear();
	//sys.Clear();
	obj->Stop();
	obj.Clear();
}

void PortaudioOutExt::Forward(FwdScope& fwd) {
	
}

void PortaudioOutExt::StorePacket(Packet& p) {
	TODO
}

void PortaudioOutExt::SinkCallback(TS::Portaudio::StreamCallbackArgs& args) {
	ExtComponent& ext = GetParent();
	Value& sink_val = ext.GetSinkValue();
	PacketBuffer& sink_buf = sink_val.GetBuffer();
	
	if (consumer.IsEmptySource())
		consumer.SetSource(sink_buf);
	
	if (args.output) {
		Ecs::AudioFormat& afmt = fmt;
		
		int size = fmt.GetFrameSize();
		if (sink_buf.GetCount() > 0 || consumer.HasLeftover()) {
			int sample_rate = afmt.GetSampleRate();
			ASSERT(args.fpb == afmt.sample_rate);
			
			/*off32 begin_offset = sink_buf.GetOffset();
			if (0) {
				RTLOG("PortaudioOutExt::SinkCallback: trying to consume " << begin_offset.ToString());
				RTLOG("PortaudioOutExt::SinkCallback: dumping");
				sink_buf.Dump();
			}*/
			
			consumer.SetDestination(fmt, args.output, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			if (consumer.GetLastMemoryBytes() != size) {
				RTLOG("PortaudioOutExt::SinkCallback: error: consumed " << consumer.GetLastMemoryBytes() << " (expected " << size << ")");
			}
			
			int consumed_count = consumer.GetCount();
			if (consumed_count) {
				RTLOG("PortaudioOutExt::SinkCallback: device consumed count=" << consumed_count);
			}
			
			/*off32 end_offset = consumer.GetOffset();
			off32 diff = off32::GetDifference(begin_offset, end_offset);
			if (diff) {
				RTLOG("PortaudioOutExt::SinkCallback: device consumed count=" << diff.ToString());
				sink_buf.RemoveFirst(diff.value);
			}
			else if (consumer.HasLeftover()) {
				RTLOG("PortaudioOutExt::SinkCallback: device consumed packet partially");
			}
			else if (!consumer.HasLeftover()) {
				RTLOG("error: PortaudioOutExt::SinkCallback: device error");
			}*/
		}
		else {
			#if DEBUG_RT_PIPE
			RTLOG("error: PortaudioOutExt::SinkCallback: got empty data");
			#endif
			
			memset(args.output, 0, size);
		}
	}
}





NAMESPACE_ECS_END


NAMESPACE_TOPSIDE_BEGIN

namespace Portaudio {bool IsPortaudioUninitialized() {return Ecs::__is_portaudio_uninit;}}

NAMESPACE_TOPSIDE_END

