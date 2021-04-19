#ifndef _AudioCore_Portaudio_h_
#define _AudioCore_Portaudio_h_

NAMESPACE_OULU_BEGIN


class BufferedPaSound;
struct StreamCallbackArgs;


class PortaudioSystem : public System<PortaudioSystem> {
	
public:
	PortaudioSystem(Machine& m);
	
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(float dt) override;
    void Stop() override;
    void Uninitialize() override;
    
};

class PortaudioSinkComponent :
	public Component<PortaudioSinkComponent>,
	public AudioSink,
	public MediaSink
{
    AudioSinkConfig aconfig;
	String last_error;
	One<BufferedPaSound> obj;
	Vector<float> tmp;
	SoundFormat fmt;
	
	
	
public:
	typedef PortaudioSinkComponent CLASSNAME;
	COPY_PANIC(PortaudioSinkComponent);
	IFACE_CB(AudioSink);
	IFACE_CB(MediaSink);
	IFACE_GENERIC;
	
	PortaudioSinkComponent();
	~PortaudioSinkComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	String GetLastError() const {return last_error;}
	
	void			RecvAudioSink(AudioSource& src, float dt) override;
	void			RecvMedia(Media& media) override;
	
	SystemSound&	BeginPlay() override;
	void			CommitPlay() override;
	void			UndoPlay() override;
	SoundFormat		GetFormat() override;
};


NAMESPACE_OULU_END

#endif
