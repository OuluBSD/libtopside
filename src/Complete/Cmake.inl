#ifdef flagCMAKE

NAMESPACE_UPP_BEGIN


#undef INITBLOCK_
#define INITBLOCK_(x) void COMBINE(Init,x)();
#define INITLIST \
	INITBLOCK_(EcsCore) \
	INITBLOCK_(EcsLib) \
	INITBLOCK_(EcsLocal) \
	/*INITBLOCK_(EcsVirtualGui)*/ \
	INITBLOCK_(EcsAudioCore) \
	INITBLOCK_(AtomAudio) \
	INITBLOCK_(AtomEcs) \
	INITBLOCK_(AtomMinimal) \
	INITBLOCK_(AudioHost) \
	INITBLOCK_(Local) \
	INITBLOCK_(SerialLib) \
	INITBLOCK_(SerialMach) \
	INITBLOCK_(ShaderToy) \
	INITBLOCK_(SoftRendShaders) \
	INITBLOCK_(StaticInterface) \
	INITBLOCK_(AppInitStartup) \
	INITBLOCK_(IGraphics) \

INITLIST

#ifdef flagVR
#ifdef flagLOCALHMD
INITBLOCK_(LocalHMD)
#endif
INITBLOCK_(AtomVR)
#endif
#if HAVE_WINDOWSYSTEM
INITBLOCK_(EcsVirtualGui)
INITBLOCK_(VirtualGui)
#endif

void RunInitBlocksManually() {
	#undef INITBLOCK_
	#define INITBLOCK_(x) COMBINE(Init,x)();
	INITLIST
	
	#ifdef flagVR
	#ifdef flagLOCALHMD
	INITBLOCK_(LocalHMD)
	#endif
	INITBLOCK_(AtomVR)
	#endif
	#if HAVE_WINDOWSYSTEM
	INITBLOCK_(EcsVirtualGui)
	INITBLOCK_(VirtualGui)
	#endif
}

void RunExitBlocksManually() {
	
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
INITBLOCK_(Portaudio)
INITBLOCK_(EcsAudioCore)
INITBLOCK_(PortaudioSystem)*/

NAMESPACE_UPP_END

#endif
