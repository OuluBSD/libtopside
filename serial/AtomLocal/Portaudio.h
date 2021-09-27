#ifndef _AtomLocal_Portaudio_h_
#define _AtomLocal_Portaudio_h_

NAMESPACE_SERIAL_BEGIN


Format ConvertPortaudioFormat(Portaudio::AudioFormat fmt);


namespace Portaudio {

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


class PortaudioSink :
	virtual public AtomBase
{
	One<Portaudio::BufferedAudioDeviceStream> obj;
	String			last_error;
	Vector<float>	tmp;
	Format			fmt;
	PacketConsumer	consumer;
	
public:
	typedef PortaudioSink CLASSNAME;
	
	PortaudioSink();
	~PortaudioSink();
	
	void Visit(RuntimeVisitor& vis) override {}
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void AltStorePacket(int sink_ch,  int src_ch, Packet& p) override;
	void AltIntervalSinkProcess() {}
	bool IsConsumedPartialPacket() override {return consumer.HasLeftover();}
	
	String GetLastError() const {return last_error;}
	void SinkCallback(Portaudio::StreamCallbackArgs& args);
	
	
};


NAMESPACE_SERIAL_END

#endif
