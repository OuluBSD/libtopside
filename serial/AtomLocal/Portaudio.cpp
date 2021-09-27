#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


Format ConvertPortaudioFormat(Portaudio::AudioFormat pa_fmt) {
	Format fmt;
	fmt.vd = VD(CENTER,AUDIO);
	AudioFormat& r = fmt;
	r.res[0] = pa_fmt.channels;
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
	AtomSystem::WhenUninit() << callback(CloseAudioSys);
}










PortaudioSink::PortaudioSink() {
	
}

PortaudioSink::~PortaudioSink() {
	obj.Clear();
}

bool PortaudioSink::AltInitialize(const Script::WorldState& ws) {
	const int sink_ch_i = 0;
	
	//sys = GetMachine().TryGet<PortaudioSystem>();
	//if (sys)
	//	dev.Create(sys->GetDefaultOutput());
	
	obj.Create();
	obj->WhenAction << THISBACK(SinkCallback);
	obj->OpenDefault();
	
	Value& sink_val = GetSink()->GetValue(sink_ch_i);
	fmt = ConvertPortaudioFormat(obj->GetFormat());
	ASSERT(fmt.IsValid());
	sink_val.SetFormat(fmt);
	
	obj->Start();
	
	//AddToContext<CenterSpec>(AsRef<CenterSink>());
	return true;
}

void PortaudioSink::AltUninitialize() {
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSink>());
	
	//dev.Clear();
	//sys.Clear();
	obj->Stop();
	obj.Clear();
}

void PortaudioSink::AltForward(FwdScope& fwd) {
	// pass
}

void PortaudioSink::AltStorePacket(int sink_ch,  int src_ch, Packet& p) {
	// pass
}

void PortaudioSink::SinkCallback(Portaudio::StreamCallbackArgs& args) {
	const int sink_ch_i = 0;
	
	Value& sink_val = GetSink()->GetValue(sink_ch_i);
	PacketBuffer& sink_buf = sink_val.GetBuffer();
	
	if (consumer.IsEmptySource())
		consumer.SetSource(sink_buf);
	
	#ifdef flagDEBUG
	this->dbg_async_race = true;
	#endif
	
	if (args.output) {
		Serial::AudioFormat& afmt = fmt;
		
		int size = fmt.GetFrameSize();
		if (sink_buf.GetCount() > 0 || consumer.HasLeftover()) {
			int sample_rate = afmt.GetSampleRate();
			ASSERT(args.fpb == afmt.sample_rate);
			
			consumer.SetDestination(fmt, args.output, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			if (consumer.GetLastMemoryBytes() != size) {
				RTLOG("PortaudioSink::SinkCallback: error: consumed " << consumer.GetLastMemoryBytes() << " (expected " << size << ")");
			}
			
			int consumed_count = consumer.GetCount();
			if (consumed_count) {
				RTLOG("PortaudioSink::SinkCallback: device consumed count=" << consumed_count);
			}
			
			PacketsConsumed(consumer.consumed_packets);
			//PostContinueForward();
		}
		else {
			#if DEBUG_RT_PIPE
			RTLOG("error: PortaudioSink::SinkCallback: got empty data");
			#endif
			
			memset(args.output, 0, size);
		}
	}
	
	
	#ifdef flagDEBUG
	this->dbg_async_race = false;
	#endif
}

namespace Portaudio {bool IsPortaudioUninitialized() {return Serial::__is_portaudio_uninit;}}

NAMESPACE_SERIAL_END
