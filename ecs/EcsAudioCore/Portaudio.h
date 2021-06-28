#ifndef _AudioCore_Portaudio_h_
#define _AudioCore_Portaudio_h_

NAMESPACE_ECS_BEGIN


Format ConvertPortaudioFormat(Portaudio::AudioFormat fmt);


namespace Portaudio {
using namespace TS::Portaudio;

class BufferedAudioDeviceStream :
	public AudioDeviceStream
{
	
	
public:
	typedef BufferedAudioDeviceStream CLASSNAME;
	BufferedAudioDeviceStream();
	
	void					OpenDefault(void* data, int inchannels=0,int outchannels=2,SampleFormat format=SND_FLOAT32);
	void					OpenDefault(int inchannels=0, int outchannels=2,SampleFormat format=SND_FLOAT32);
	
};

}

struct StreamCallbackArgs;



class PortaudioOutExt :
	public AudioOutputExt
{
	String last_error;
	One<Portaudio::BufferedAudioDeviceStream> obj;
	Vector<float> tmp;
	Format fmt;
	PacketConsumer consumer;
	
public:
	typedef PortaudioOutExt CLASSNAME;
	
	PortaudioOutExt();
	~PortaudioOutExt();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	String GetLastError() const {return last_error;}
	void SinkCallback(TS::Portaudio::StreamCallbackArgs& args);
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink.realtime")
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink.hw")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_PORTAUDIO_AUDIO_OUT;}
	
};



NAMESPACE_ECS_END

#endif
