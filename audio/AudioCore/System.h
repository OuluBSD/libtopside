#ifndef _AudioCore_System_h_
#define _AudioCore_System_h_

#include <EcsLib/EcsLib.h>
#include <FusionCore/FusionCore.h>
#include "AudioCore.h"
#include "Portaudio.h"
#include "Generators.h"

NAMESPACE_OULU_BEGIN


class MixerContextComponent :
	public Component<MixerContextComponent>
{
	String last_error;
	String post_load_file_path;
	
public:
	COPY_PANIC(MixerContextComponent);
	
	MixerContextComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void PostLoadFileAny(String path) {post_load_file_path = path;}
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MixerChannelContextComponent :
	public Component<MixerChannelContextComponent>
{
	String last_error;
	
public:
	COPY_PANIC(MixerChannelContextComponent);
	
	MixerChannelContextComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	String GetLastError() const {return last_error;}
	
};


class MixerChannelInputComponent :
	public Component<MixerChannelInputComponent>,
	public FusionSink,
	public FusionSource
{
	String last_error;
	
public:
	COPY_PANIC(MixerChannelInputComponent);
	IFACE_CB(FusionSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	MixerChannelInputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	const FusionComponentInput& GetHeader() const override;
	
	String GetLastError() const {return last_error;}
	
};

class MixerChannelOutputComponent :
	public Component<MixerChannelOutputComponent>,
	public FusionSink,
	public FusionSource
{
	String last_error;
	
public:
	COPY_PANIC(MixerChannelOutputComponent);
	IFACE_CB(FusionSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	MixerChannelOutputComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	const FusionComponentInput& GetHeader() const override;
	
	String GetLastError() const {return last_error;}
	
};


class MixerAudioSourceComponent :
	public Component<MixerAudioSourceComponent>,
	public FusionSink,
	public AudioSource
{
	String last_error;
	
public:
	COPY_PANIC(MixerAudioSourceComponent);
	IFACE_CB(FusionSink);
	IFACE_CB(AudioSource);
	IFACE_GENERIC;
	
	MixerAudioSourceComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	AudioStream&		GetAudioSource() override;
	void				BeginAudioSource() override;
	void				EndAudioSource(bool any_sink_consumed) override;
	
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
	COPY_PANIC(MidiFileComponent);
	IFACE_CB(MidiSource);
	IFACE_GENERIC;
	
	MidiFileComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EmitMidi(double dt) override;
	bool IsSupported(DevType type) override {return true;}
	void OnLink(Sink sink, Cookie src_c, Cookie sink_c) override;
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
	public MidiSink,
	public FusionSource
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
	COPY_PANIC(FluidsynthComponent);
	IFACE_CB(MidiSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	FluidsynthComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void RecvMidi(const MidiFrame& e) override;
	void Configure(const Midi::File& file) override;
	void OpenTrackListener(int track_i);
	
	String GetLastError() const {return last_error;}
	const FusionComponentInput& GetHeader() const override {return cfg;}
	
	
};



class FluidsynthSystem : public System<FluidsynthSystem> {
	Vector<FluidsynthComponent*> comps;
	Vector<FluidsynthComponent*> track_comps;
	Fluidsynth fs;
	
	
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

NAMESPACE_OULU_END


#endif
