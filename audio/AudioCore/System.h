#ifndef _AudioCore_System_h_
#define _AudioCore_System_h_

#include <EcsLib/EcsLib.h>
#include <FusionCore/FusionCore.h>
#include "AudioCore.h"
#include "Portaudio.h"
#include "Generators.h"

NAMESPACE_TOPSIDE_BEGIN


class MixerContextComponent :
	public Component<MixerContextComponent>
{
	String last_error;
	String post_load_file_path;
	
public:
	RTTI_COMP0(MixerContextComponent)
	VIS_COMP_0_0
	COPY_PANIC(MixerContextComponent);
	
	MixerContextComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void PostLoadFileAny(String path) {post_load_file_path = path;}
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MixerChannelContextComponent :
	public Component<MixerChannelContextComponent>
{
	String last_error;
	
public:
	RTTI_COMP0(MixerChannelContextComponent)
	VIS_COMP_0_0
	COPY_PANIC(MixerChannelContextComponent);
	
	MixerChannelContextComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	String GetLastError() const {return last_error;}
	
};


class MixerChannelInputComponent :
	public Component<MixerChannelInputComponent>,
	public AcceleratorSource,
	public AcceleratorSink
{
	String last_error;
	
public:
	RTTI_COMP2(MixerChannelInputComponent, AcceleratorSource, AcceleratorSink)
	VIS_COMP_1_1(Accelerator, Accelerator)
	COPY_PANIC(MixerChannelInputComponent);
	IFACE_CB(AcceleratorSink);
	IFACE_CB(AcceleratorSource);
	IFACE_GENERIC;
	
	MixerChannelInputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//const AcceleratorHeader& GetHeader() const override;
	
	// AcceleratorSource
	AcceleratorStream&	GetStream(AccCtx) override {TODO}
	void				BeginStream(AccCtx) override {TODO}
	void				EndStream(AccCtx) override {TODO}
	
	// AcceleratorSink
	AcceleratorFormat	GetFormat(AccCtx) override {TODO}
	Accelerator&		GetValue(AccCtx) override {TODO}
	
	String GetLastError() const {return last_error;}
	
};

class MixerChannelOutputComponent :
	public Component<MixerChannelOutputComponent>,
	public AcceleratorSource,
	public AcceleratorSink
{
	String last_error;
	
public:
	RTTI_COMP2(MixerChannelOutputComponent, AcceleratorSource, AcceleratorSink)
	VIS_COMP_1_1(Accelerator, Accelerator)
	COPY_PANIC(MixerChannelOutputComponent);
	IFACE_CB(AcceleratorSink);
	IFACE_CB(AcceleratorSource);
	IFACE_GENERIC;
	
	MixerChannelOutputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	//const AcceleratorHeader& GetHeader() const override;
	
	// AcceleratorSource
	AcceleratorStream&	GetStream(AccCtx) override;
	void				BeginStream(AccCtx) override;
	void				EndStream(AccCtx) override;
	
	// AcceleratorSink
	AcceleratorFormat	GetFormat(AccCtx) override;
	Accelerator&		GetValue(AccCtx) override;
	
	String GetLastError() const {return last_error;}
	
};


class MixerAudioSourceComponent :
	public Component<MixerAudioSourceComponent>,
	public AudioSource,
	public AcceleratorSink
{
	String last_error;
	
public:
	RTTI_COMP2(MixerAudioSourceComponent, AudioSource, AcceleratorSink)
	VIS_COMP_1_1(Audio, Accelerator)
	COPY_PANIC(MixerAudioSourceComponent);
	IFACE_CB(AcceleratorSink);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	
	MixerAudioSourceComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	// AudioSource
	AudioStream&		GetStream(AudCtx) override;
	void				BeginStream(AudCtx) override;
	void				EndStream(AudCtx) override;
	
	// AcceleratorSink
	AcceleratorFormat	GetFormat(AccCtx) override;
	Accelerator&		GetValue(AccCtx) override;
	
	String GetLastError() const {return last_error;}
	
};




class MidiFileComponent :
	public Component<MidiFileComponent>,
	public DeviceSource
{
	String last_error;
	Midi::File file;
	Vector<int> track_i;
	double song_dt = 0;
	MidiFrame tmp;
	
public:
	RTTI_COMP1(MidiFileComponent, DeviceSource)
	VIS_COMP_1_0(Device)
	COPY_PANIC(MidiFileComponent);
	IFACE_CB(DeviceSource);
	IFACE_GENERIC;
	
	MidiFileComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	//void EmitMidi(double dt) override;
	//bool IsSupported(DevType type) override {return true;}
	void OnLink(SinkProv sink, Cookie src_c, Cookie sink_c) override {TODO}
	void Visit(RuntimeVisitor& vis) override {}
	bool OpenFilePath(String path);
	void Clear();
	void CollectTrackEvents(int i);
	void EmitTrack(int i);
	void DumpMidiFile();
	
	// DeviceSource
	DeviceStream&		GetStream(DevCtx) override {TODO}
	void				BeginStream(DevCtx) override {TODO}
	void				EndStream(DevCtx) override {TODO}
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};



#if HAVE_FLUIDSYNTH

class FluidsynthComponent :
	public Component<FluidsynthComponent>,
	public AcceleratorSource,
	public MidiSink
{
	String last_error;
	FusionComponentInput cfg;
	int mode = 0;
	int track_i = -1;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
public:
	RTTI_COMP2(FluidsynthComponent, AcceleratorSource, MidiSink)
	VIS_COMP_1_1(Accelerator, Midi)
	COPY_PANIC(FluidsynthComponent);
	IFACE_CB(MidiSink);
	IFACE_CB(AcceleratorSource);
	IFACE_GENERIC;
	
	FluidsynthComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void RecvMidi(const MidiFrame& e) override;
	void Configure(const Midi::File& file) override;
	void Visit(RuntimeVisitor& vis) override {}
	void OpenTrackListener(int track_i);
	
	// AcceleratorSource
	AcceleratorStream&	GetStream(AccCtx) override;
	void				BeginStream(AccCtx) override;
	void				EndStream(AccCtx) override;
	
	String GetLastError() const {return last_error;}
	const AcceleratorHeader& GetHeader() const override {return cfg;}
	
	
};



class FluidsynthSystem :
	public System<FluidsynthSystem>
{
	LinkedList<FluidsynthComponentRef> comps;
	LinkedList<FluidsynthComponentRef> track_comps;
	
	Fluidsynth fs;
	
	
	SYS_RTTI(FluidsynthSystem)
	void Visit(RuntimeVisitor& vis) override {
		vis && comps
			&& track_comps;
	}
	
public:
	FluidsynthSystem(Machine& m);
	
	const Vector<FluidsynthComponent*>& GetContext() const {return comps;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
    
protected:
	friend class FluidsynthComponent;
	void AddContext(FluidsynthComponent& comp);
	void RemoveContext(FluidsynthComponent& comp);
	void Assign(const Midi::File& file, int track_i, FluidsynthComponent* comp);
	
};


PREFAB_BEGIN(CompleteFluidsynth)
		MixerChannelContextComponent,
		FluidsynthComponent,
		MixerChannelOutputComponent
PREFAB_END;

#endif


PREFAB_BEGIN(CompleteMixer)
		MixerContextComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMixerChannel)
		MixerChannelContextComponent,
		MixerChannelInputComponent,
		MixerChannelOutputComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMixerOutput)
		MixerChannelContextComponent,
		MixerChannelInputComponent,
		MixerAudioSourceComponent
PREFAB_END;

PREFAB_BEGIN(MidiFileController)
		MidiFileComponent
PREFAB_END;

NAMESPACE_TOPSIDE_END


#endif
