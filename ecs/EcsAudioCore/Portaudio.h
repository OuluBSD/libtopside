#ifndef _AudioCore_Portaudio_h_
#define _AudioCore_Portaudio_h_

NAMESPACE_TOPSIDE_BEGIN


AudioFormat ConvertPortaudioFormat(Portaudio::AudioFormat fmt);


namespace Portaudio {

class BufferedAudioDeviceStream :
	public AudioDeviceStream,
	public SimpleBufferedAudio
{
	SimpleBufferedAudio	buf;
	AudioPacketConsumer consumer;
	
	void			SinkCallback(StreamCallbackArgs& args);
	
public:
	typedef BufferedAudioDeviceStream CLASSNAME;
	BufferedAudioDeviceStream();
	
	void					OpenDefault(void* data, int inchannels=0,int outchannels=2,SampleFormat format=SND_FLOAT32);
	void					OpenDefault(int inchannels=0, int outchannels=2,SampleFormat format=SND_FLOAT32);
	
};

}

struct StreamCallbackArgs;


class PortaudioSinkComponent :
	public DevComponent<CenterSpec, AudioSpec, PortaudioSinkComponent>,
	public AudioSink,
	public ReceiptSource
{
	String last_error;
	One<Portaudio::BufferedAudioDeviceStream> obj;
	Vector<float> tmp;
	AudioFormat fmt;
	
protected:
	
	struct LocalSourceValue : public SimpleReceipt {
		
	};
	
	struct LocalSourceStream : public SimpleReceiptStream {
		RTTI_DECL1(LocalSourceStream, SimpleReceiptStream)
		PortaudioSinkComponent& par;
		LocalSourceStream(PortaudioSinkComponent* par) :
			par(*par),
			SimpleReceiptStream(par->src_value) {}
	};
	
	LocalSourceValue		src_value;
	LocalSourceStream		src_stream;
	
public:
	using Component = DevComponent<CenterSpec, AudioSpec, PortaudioSinkComponent>;
	typedef PortaudioSinkComponent CLASSNAME;
	RTTI_DCOMP2(PortaudioSinkComponent, AudioSink, ReceiptSource)
	VIS_COMP_1_1(Receipt, Audio)
	COPY_PANIC(PortaudioSinkComponent);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink")
	COMP_MAKE_ACTION_END
	
	PortaudioSinkComponent();
	~PortaudioSinkComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void ForwardPackets(double dt) override {}
	void Forward(FwdScope& fwd) override {}
	void ForwardExchange(FwdScope& fwd) override {}
	
	String GetLastError() const {return last_error;}
	
	// AudioSink
	AudioFormat		GetFormat(AudCtx) override;
	Audio&			GetValue(AudCtx) override;
	
	// ReceiptSource
	ReceiptStream&	GetStream(RcpCtx) override {return src_stream;}
	void			BeginStream(RcpCtx) override {TODO}
	void			EndStream(RcpCtx) override {TODO}
	bool			ReadFrame() {TODO}
	bool			ProcessFrame() {TODO}
	bool			ProcessDeviceFrame() {TODO}
};

PREFAB_BEGIN(CompletePortaudio)
	PortaudioSinkComponent
PREFAB_END

NAMESPACE_TOPSIDE_END

#endif
