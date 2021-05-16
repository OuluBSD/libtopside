#ifndef _MP3Player_MP3Player_h_
#define _MP3Player_MP3Player_h_

#include <Complete/Complete.h>
#include <FusionCore/FusionCore.h>
using namespace Topside;

NAMESPACE_TOPSIDE_BEGIN


class DummyGenerator :
	public Component<DummyGenerator>
{
	VIS_COMP_0_0
	
	RefT_Entity<SoundGeneratorComponent> gen;
	RefT_Entity<PortaudioSinkComponent> audio;
	
public:
	typedef DummyGenerator CLASSNAME;
	DummyGenerator() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis & gen & audio;}
	
	COPY_PANIC(DummyGenerator);
	
};

PREFAB_BEGIN(DummyGeneratorPrefab)
	PortaudioSinkComponent,
	SoundGeneratorComponent,
	DummyGenerator
PREFAB_END



class MP3Player :
	public Component<MP3Player>
{
	VIS_COMP_0_0
	
	RefT_Entity<FfmpegComponent> file_in;
	RefT_Entity<PortaudioSinkComponent> audio;
	
public:
	typedef MP3Player CLASSNAME;
	MP3Player() {}
	void OnError();
	void OnStop();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis & file_in & audio;}
	
	COPY_PANIC(MP3Player);
	
};


PREFAB_BEGIN(MP3PlayerPrefab)
	PortaudioSinkComponent,
	FfmpegComponent,
	MP3Player
PREFAB_END


NAMESPACE_TOPSIDE_END

#endif
