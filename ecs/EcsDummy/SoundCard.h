#ifndef _EcsDummy_SoundCard_h_
#define _EcsDummy_SoundCard_h_

NAMESPACE_TOPSIDE_BEGIN


class DummyAudioSinkComponent :
	public Component<DummyAudioSinkComponent>,
	public AudioSink,
	public ReceiptSource
{
	RunningFlag				flag;
	Mutex					lock;
	RealtimeSourceConfig*	cfg = 0;
	
	void FakeHardwareProcess();
	
protected:
	
	struct StreamCallbackArgs {
		void*			output;
		unsigned long	fpb;
	};
	
	struct LocalSinkValue : public SimpleBufferedAudio {
		DummyAudioSinkComponent& par;
		
		void SinkCallback(StreamCallbackArgs& args);
		LocalSinkValue(DummyAudioSinkComponent* par) : par(*par) {}
	};
	
	struct LocalSourceValue : public SimpleReceipt {
		void StorePacket(ReceiptPacket& p) {}
	};
	
	struct LocalSourceStream : public SimpleReceiptStream {
		DummyAudioSinkComponent& par;
		AudioPacketConsumer consumer;
		
		RTTI_DECL1(LocalSourceStream, SimpleReceiptStream)
		LocalSourceStream(DummyAudioSinkComponent* par) :
			par(*par),
			SimpleReceiptStream(par->src_value) {}
		
	};
	
	
	LinkedList<AudioPacket> consumed_packets;
	
public:
	typedef DummyAudioSinkComponent CLASSNAME;
	RTTI_COMP2(DummyAudioSinkComponent, AudioSink, ReceiptSource)
	VIS_COMP_1_1(Receipt, Audio)
	COPY_PANIC(DummyAudioSinkComponent);
	IFACE_CB(ReceiptSource);
	IFACE_CB(AudioSink);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink.test")
	COMP_MAKE_ACTION_END
	
	
	LocalSinkValue			sink_value;
	LocalSourceValue		src_value;
	LocalSourceStream		src_stream;
	
	DummyAudioSinkComponent() : src_stream(this), sink_value(this) {}
	
	void			Initialize() override;
	void			Uninitialize() override;
	void			Forward(FwdScope& fwd) override;
	void			ForwardExchange(FwdScope& fwd) override;
	void			Process(AudioPacket& p);
	
	// AudioSink
	AudioFormat		GetFormat(AudCtx) override {return AudioFormat();}
	Audio&			GetValue(AudCtx) override {return sink_value;}
	
	// ReceiptSource
	ReceiptStream&	GetStream(RcpCtx) override {return src_stream;}
	void			BeginStream(RcpCtx) override {TODO}
	void			EndStream(RcpCtx) override {TODO}
	bool			ReadFrame() {TODO}
	bool			ProcessFrame() {TODO}
	bool			ProcessDeviceFrame() {TODO}
	
	void SetAudioSyncInterval(double seconds) {}
	
};


NAMESPACE_TOPSIDE_END

#endif
