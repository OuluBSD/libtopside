#ifndef _MP3Player_MP3Player_h_
#define _MP3Player_MP3Player_h_

#include <Complete/Complete.h>
#include <FusionCore/FusionCore.h>
using namespace Oulu;

NAMESPACE_OULU_BEGIN


class MP3Player :
	public Component<MP3Player>
{
	//EntityRef mixer, fusion, channel0, track0, output;
	MixerContextComponent* ctx = 0;
	Ref<MultiMediaComponent> file_in;
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
	MultiMediaComponent,
	MP3Player
PREFAB_END


NAMESPACE_OULU_END

#endif
