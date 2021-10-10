#ifndef _AtomLocal_Portaudio_h_
#define _AtomLocal_Portaudio_h_

NAMESPACE_SERIAL_BEGIN


Format ConvertPortaudioFormat(Portaudio::AudioFormat fmt);


namespace Portaudio {
using namespace ::TS::Portaudio;


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
	virtual public AtomBase,
	public AsyncMemForwarderBase
{
	One<Portaudio::BufferedAudioDeviceStream> obj;
	String			last_error;
	Vector<float>	tmp;
	Format			fmt;
	
public:
	typedef PortaudioSink CLASSNAME;
	
	PortaudioSink();
	~PortaudioSink();
	
	void Visit(RuntimeVisitor& vis) override {}
	
	bool	Initialize(const Script::WorldState& ws) override;
	void	Uninitialize() override;
	bool	PassProcessPackets(PacketIO& io) override;
	
	String GetLastError() const {return last_error;}
	void SinkCallback(Portaudio::StreamCallbackArgs& args);
	
	
};


NAMESPACE_SERIAL_END

#endif
