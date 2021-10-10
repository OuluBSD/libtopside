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

bool PortaudioSink::Initialize(const Script::WorldState& ws) {
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
	
	GetSink()->GetValue(0).SetMinQueueSize(10);
	
	//AddToContext<CenterSpec>(AsRef<CenterSink>());
	return true;
}

void PortaudioSink::Uninitialize() {
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSink>());
	
	//dev.Clear();
	//sys.Clear();
	obj->Stop();
	obj.Clear();
}

bool PortaudioSink::PassConsumePacket(int sink_ch, const Packet& in) {
	TODO
	#if 0
	return in->GetFormat().IsCopyCompatible(fmt);
	#endif
}

void PortaudioSink::SinkCallback(Portaudio::StreamCallbackArgs& args) {
	if (!args.output) return;
	
	#ifdef flagDEBUG
	this->dbg_async_race = true;
	#endif
	
	Serial::AudioFormat& afmt = fmt;
	int size = fmt.GetFrameSize();
	if (!this->ForwardAsyncMem((byte*)args.output, size)) {
		RTLOG("PortaudioSink::SinkCallback: reading memory failed");
		memset(args.output, 0, size);
	}
	
	
	#ifdef flagDEBUG
	this->dbg_async_race = false;
	#endif
}


NAMESPACE_SERIAL_END


NAMESPACE_TOPSIDE_BEGIN


namespace Portaudio {bool IsPortaudioUninitialized() {return Serial::__is_portaudio_uninit;}}


NAMESPACE_TOPSIDE_END
