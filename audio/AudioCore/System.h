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
	public FusionSource,
	public FusionSink
{
	String last_error;
	
public:
	VIS_COMP_1_1(Fusion, Fusion)
	COPY_PANIC(MixerChannelInputComponent);
	IFACE_CB(FusionSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	MixerChannelInputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	const FusionComponentInput& GetHeader() const override;
	
	String GetLastError() const {return last_error;}
	
};

class MixerChannelOutputComponent :
	public Component<MixerChannelOutputComponent>,
	public FusionSource,
	public FusionSink
{
	String last_error;
	
public:
	VIS_COMP_1_1(Fusion, Fusion)
	COPY_PANIC(MixerChannelOutputComponent);
	IFACE_CB(FusionSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	MixerChannelOutputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	const FusionComponentInput& GetHeader() const override;
	
	String GetLastError() const {return last_error;}
	
};


class MixerAudioSourceComponent :
	public Component<MixerAudioSourceComponent>,
	public AudioSource,
	public FusionSink
{
	String last_error;
	
public:
	VIS_COMP_1_1(Audio, Fusion)
	COPY_PANIC(MixerAudioSourceComponent);
	IFACE_CB(FusionSink);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	
	MixerAudioSourceComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	AudioStream&		GetAudioSource() override;
	void				BeginAudioSource() override;
	void				EndAudioSource() override;
	
	String GetLastError() const {return last_error;}
	
};




class MidiFileComponent :
	public Component<MidiFileComponent>,
	public MidiSource
{
	String last_error;
	Midi::File file;
	Vector<int> track_i;
	double song_dt = 0;
	MidiFrame tmp;
	
public:
	VIS_COMP_1_0(Midi)
	COPY_PANIC(MidiFileComponent);
	IFACE_CB(MidiSource);
	IFACE_GENERIC;
	
	MidiFileComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitMidi(double dt) override;
	bool IsSupported(DevType type) override {return true;}
	void OnLink(Sink sink, Cookie src_c, Cookie sink_c) override;
	void Visit(RuntimeVisitor& vis) override {}
	bool OpenFilePath(String path);
	void Clear();
	void CollectTrackEvents(int i);
	void EmitTrack(int i);
	void DumpMidiFile();
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};



#if HAVE_FLUIDSYNTH

class FluidsynthComponent :
	public Component<FluidsynthComponent>,
	public FusionSource,
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
	VIS_COMP_1_1(Fusion, Midi)
	COPY_PANIC(FluidsynthComponent);
	IFACE_CB(MidiSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	FluidsynthComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void RecvMidi(const MidiFrame& e) override;
	void Configure(const Midi::File& file) override;
	void Visit(RuntimeVisitor& vis) override {}
	void OpenTrackListener(int track_i);
	
	String GetLastError() const {return last_error;}
	const FusionComponentInput& GetHeader() const override {return cfg;}
	
	
};



class FluidsynthSystem : public System<FluidsynthSystem> {
	LinkedList<FluidsynthComponentRef> comps;
	LinkedList<FluidsynthComponentRef> track_comps;
	
	Fluidsynth fs;
	
	
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
