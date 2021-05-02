#ifndef _AudioCore_Portaudio_h_
#define _AudioCore_Portaudio_h_

NAMESPACE_OULU_BEGIN


class BufferedPaSound;
struct StreamCallbackArgs;


class PortaudioSinkComponent :
	public Component<PortaudioSinkComponent>,
	public AudioSink
{
    AudioSinkConfig aconfig;
	String last_error;
	One<BufferedPaSound> obj;
	Vector<float> tmp;
	AudioFormat fmt;
	
	
	
public:
	typedef PortaudioSinkComponent CLASSNAME;
	COPY_PANIC(PortaudioSinkComponent);
	IFACE_CB(AudioSink);
	IFACE_CB(VideoSink);
	IFACE_GENERIC;
	
	PortaudioSinkComponent();
	~PortaudioSinkComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	String GetLastError() const {return last_error;}
	
	void			RecvAudio(AudioSource& src, double dt) override;
	AudioFormat		GetAudioFormat() override;
	
};


NAMESPACE_OULU_END

#endif
