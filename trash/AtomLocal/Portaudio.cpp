#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN



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
	
	SetPrimarySinkQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	
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
	Format fmt = in->GetFormat();
	return fmt.vd.val == ValCls::AUDIO;
	
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
