#ifndef _EcsLib_Dummy_h_
#define _EcsLib_Dummy_h_

NAMESPACE_TOPSIDE_BEGIN



class DummyAudioSinkComponent :
	public Component<DummyAudioSinkComponent>,
	public AudioSink
{
	
public:
	RTTI_COMP1(DummyAudioSinkComponent, AudioSink)
	VIS_COMP_0_1(Audio)
	COPY_PANIC(DummyAudioSinkComponent);
	IFACE_CB(AudioSink);
	IFACE_GENERIC;
	
	SimpleBufferedAudio value;
	
	DummyAudioSinkComponent() = default;
	
	void			Initialize() override {}
	void			Uninitialize() override {}
	void			Visit(RuntimeVisitor& vis) override {}
	
	AudioFormat		GetFormat(AudCtx) override {return AudioFormat();}
	Audio&			GetValue(AudCtx) override {return value;}
	
	void SetAudioSyncInterval(double seconds) {}
	
};



NAMESPACE_TOPSIDE_END

#endif
