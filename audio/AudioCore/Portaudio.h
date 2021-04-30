#ifndef _AudioCore_Portaudio_h_
#define _AudioCore_Portaudio_h_

NAMESPACE_OULU_BEGIN


class BufferedPaSound;
struct StreamCallbackArgs;


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
	
	void			RecvAudioSink(AudioSource& src, double dt) override;
	void			RecvMedia(Media& media) override;
	
	SystemSound&	BeginPlay() override;
	void			CommitPlay() override;
	void			UndoPlay() override;
	SoundFormat		GetFormat() override;
};

class PortaudioSystem : public System<PortaudioSystem> {
	Vector<AudioSink*> sinks;
	
public:
	PortaudioSystem(Machine& m);
	
	void Add(AudioSink* sink);
	void Remove(AudioSink* sink);
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
	
};


NAMESPACE_OULU_END

#endif
