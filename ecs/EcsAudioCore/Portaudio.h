#ifndef _AudioCore_Portaudio_h_
#define _AudioCore_Portaudio_h_

NAMESPACE_TOPSIDE_BEGIN


AudioFormat ConvertPortaudioFormat(Portaudio::AudioFormat fmt);


namespace Portaudio {

class BufferedAudioDeviceStream :
	public AudioDeviceStream,
	public TS::Audio
{
	AudioVolatileBuffer	buf;
	AudioPacketConsumer consumer;
	
	void			SinkCallback(StreamCallbackArgs& args);
	
public:
	typedef BufferedAudioDeviceStream CLASSNAME;
	BufferedAudioDeviceStream();
	
	void					OpenDefault(void* data, int inchannels=0,int outchannels=2,SampleFormat format=SND_FLOAT32);
	void					OpenDefault(int inchannels=0, int outchannels=2,SampleFormat format=SND_FLOAT32);
	
	void					Exchange(AudioEx& e) override {buf.Exchange(e);}
	int						GetQueueSize() const override {return buf.GetQueueSize();}
	TS::AudioFormat	GetFormat() const override {return buf.GetFormat();}
	bool					IsQueueFull() const override {return buf.IsQueueFull();}
	
	AudioVolatileBuffer&	GetBuffer() {return buf;}
	
};

}

struct StreamCallbackArgs;


class PortaudioSinkComponent :
	public DevComponent<CenterSpec, AudioSpec, PortaudioSinkComponent>,
	public AudioSink
{
    RealtimeSourceConfig aconfig;
	String last_error;
	One<Portaudio::BufferedAudioDeviceStream> obj;
	Vector<float> tmp;
	AudioFormat fmt;
	
	
public:
	using Component = DevComponent<CenterSpec, AudioSpec, PortaudioSinkComponent>;
	typedef PortaudioSinkComponent CLASSNAME;
	RTTI_DCOMP1(PortaudioSinkComponent, AudioSink)
	VIS_COMP_0_1(Audio)
	COPY_PANIC(PortaudioSinkComponent);
	IFACE_CB(AudioSink);
	IFACE_CB(VideoSink);
	IFACE_GENERIC;
	
	PortaudioSinkComponent();
	~PortaudioSinkComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void CreatePackets() override {}
	
	String GetLastError() const {return last_error;}
	
	AudioFormat		GetFormat(AudCtx) override;
	Audio&			GetValue(AudCtx) override;
	
};


NAMESPACE_TOPSIDE_END

#endif
