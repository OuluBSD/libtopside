#ifndef _MP3Player_MP3Player_h_
#define _MP3Player_MP3Player_h_

#include <Complete/Complete.h>
#include <FusionCore/FusionCore.h>
using namespace Oulu;

NAMESPACE_OULU_BEGIN


class DummyGenerator :
	public Component<DummyGenerator>
{
	Ref<SoundGeneratorComponent> gen;
	Ref<PortaudioSinkComponent> audio;
public:
	typedef DummyGenerator CLASSNAME;
	DummyGenerator() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	
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
	Ref<FfmpegComponent> file_in;
	Ref<PortaudioSinkComponent> audio;
public:
	typedef MP3Player CLASSNAME;
	MP3Player() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	
	COPY_PANIC(MP3Player);
	
};


PREFAB_BEGIN(MP3PlayerPrefab)
	PortaudioSinkComponent,
	FfmpegComponent,
	MP3Player
PREFAB_END


NAMESPACE_OULU_END

#endif
