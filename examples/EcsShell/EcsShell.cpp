#include "EcsShell.h"



// Just call default macro in AtomComplete
DEFAULT_ECS_SHELL


NAMESPACE_UPP_BEGIN


#ifdef flagCMAKE
#undef INITBLOCK_
#define INITBLOCK_(x) void COMBINE(Init,x)();
#define INITLIST \
	INITBLOCK_(EcsCore) \
	INITBLOCK_(EcsLib) \
	INITBLOCK_(EcsLocal) \
	/*INITBLOCK_(EcsVirtualGui)*/ \
	INITBLOCK_(AtomAudio) \
	INITBLOCK_(AtomEcs) \
	INITBLOCK_(AtomMinimal) \
	INITBLOCK_(AtomVR) \
	INITBLOCK_(AudioHost) \
	INITBLOCK_(Local) \
	INITBLOCK_(LocalHMD) \
	INITBLOCK_(SerialLib) \
	INITBLOCK_(SerialMach) \
	INITBLOCK_(ShaderToy) \
	INITBLOCK_(SoftRendShaders) \
	INITBLOCK_(StaticInterface) \
	INITBLOCK_(AppInitStartup) \

INITLIST

void RunInitBlocksManually() {
	#undef INITBLOCK_
	#define INITBLOCK_(x) COMBINE(Init,x)();
	INITLIST
}

/*INITBLOCK_(Local_Network)
INITBLOCK_(OdeSystem)
INITBLOCK_(EcsDummy)
INITBLOCK_(EcsMultimedia)
INITBLOCK_(AppInitStartup)
INITBLOCK_(AppDefaultGfx)
INITBLOCK_(EscInitStartup)
INITBLOCK_(EcsShaders)
INITBLOCK_(Sequencer)
INITBLOCK_(OdeSystem)
INITBLOCK_(Editor)
INITBLOCK_(LocalVR)
INITBLOCK_(IGraphicsShaders)
INITBLOCK_(Portaudio)
INITBLOCK_(EcsAudioCore)
INITBLOCK_(PortaudioSystem)*/
#endif

NAMESPACE_UPP_END
