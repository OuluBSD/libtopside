#ifndef _MP3Player_MP3Player_h_
#define _MP3Player_MP3Player_h_

#include <Complete/Complete.h>
using namespace TS;

NAMESPACE_TOPSIDE_BEGIN

#if 0
using AudioSinkComponent = PortaudioSinkComponent;
#else
using AudioSinkComponent = DummyAudioSinkComponent;
#endif


class DummyGenerator :
	public Component<DummyGenerator>
{
	VIS_COMP_0_0
	
	RefT_Entity<DummySoundGeneratorComponent> gen;
	RefT_Entity<AudioSinkComponent> audio;
	
public:
	typedef DummyGenerator CLASSNAME;
	DummyGenerator() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {COMP_DEF_VISIT_; vis & gen & audio;}
	
	COPY_PANIC(DummyGenerator);
	
};

PREFAB_BEGIN(DummyGeneratorPrefab)
	AudioSinkComponent,
	DummySoundGeneratorComponent,
	DummyGenerator
PREFAB_END



class MP3Player :
	public Component<MP3Player>
{
	VIS_COMP_0_0
	
	RefT_Entity<FfmpegComponent> file_in;
	RefT_Entity<AudioSinkComponent> audio;
	
public:
	typedef MP3Player CLASSNAME;
	MP3Player() {}
	void OnError();
	void OnStop();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {COMP_DEF_VISIT_; vis & file_in & audio;}
	
	COPY_PANIC(MP3Player);
	
};


PREFAB_BEGIN(MP3PlayerPrefab)
	AudioSinkComponent,
	FfmpegComponent,
	MP3Player
PREFAB_END


NAMESPACE_TOPSIDE_END

#endif
