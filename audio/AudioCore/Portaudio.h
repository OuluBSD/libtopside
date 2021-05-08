#ifndef _AudioCore_Portaudio_h_
#define _AudioCore_Portaudio_h_

NAMESPACE_OULU_BEGIN

namespace Portaudio {
class BufferedAudioDeviceStream;
}

struct StreamCallbackArgs;


class PortaudioSinkComponent :
	public Component<PortaudioSinkComponent>,
	public AudioSink
{
    RealtimeSourceConfig aconfig;
	String last_error;
	One<Portaudio::BufferedAudioDeviceStream> obj;
	Vector<float> tmp;
	AudioFormat fmt;
	
	
	
public:
	typedef PortaudioSinkComponent CLASSNAME;
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
	
	String GetLastError() const {return last_error;}
	
	AudioFormat		GetAudioFormat() override;
	Audio&			GetAudioSink() override;
	
};


NAMESPACE_OULU_END

#endif
