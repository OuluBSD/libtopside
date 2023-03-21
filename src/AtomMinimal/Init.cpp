#include "AtomMinimal.h"

// This file is generated. Do not modify this file.

INITBLOCK_(AtomMinimal) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	Factory::RegisterAtom<CenterCustomer>();
	Factory::RegisterAtom<TestRealtimeSrc>();
	Factory::RegisterAtom<TestRealtimeSink>();
	Factory::RegisterAtom<TestPollerSink>();
	#if (defined flagBUILTIN_PORTAUDIO) || (defined flagPORTAUDIO)
	Factory::RegisterAtom<PortaudioSink>();
	#endif
	#if defined flagFFMPEG
	Factory::RegisterAtom<AudioDecoderSrc>();
	#endif
	Factory::RegisterAtom<AudioDbgSrc>();
	Factory::RegisterAtom<AudioSplitter>();
	Factory::RegisterAtom<AudioSplitterUser>();
	Factory::RegisterAtom<AudioJoiner>();
	Factory::RegisterAtom<AudioJoinerUser>();
	Factory::RegisterAtom<AudioJoiner2User>();
	Factory::RegisterAtom<AudioMixer16>();
	#if defined flagSCREEN
	Factory::RegisterAtom<VideoDbgSrc>();
	#endif
	#if (defined flagOPENCV && defined flagLINUX)
	Factory::RegisterAtom<WebcamPipe>();
	#endif
	#if (defined flagOPENCV && defined flagLINUX)
	Factory::RegisterAtom<WebcamAtom>();
	#endif
	#if defined flagFFMPEG
	Factory::RegisterAtom<AudioLoaderAtom>();
	#endif
	#if defined flagFFMPEG
	Factory::RegisterAtom<VideoLoaderAtom>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<EventStatePipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11SwFboProg>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglFboProg>();
	#endif
	#if defined flagSDL2
	Factory::RegisterAtom<SdlSwFboProg>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglFboProg>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11SwShaderPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglShaderPipe>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglShaderPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11SwFboAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglFboAtomPipe>();
	#endif
	#if defined flagSDL2
	Factory::RegisterAtom<SdlSwFboAtomPipe>();
	#endif
	#if (defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglFboAtomPipe>();
	#endif
	#if (defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglProgAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11ContextAtom>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11SwContextAtom>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglContextAtom>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11EventAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11SwEventAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglEventAtomPipe>();
	#endif
	Factory::RegisterAtom<OglCustomer>();
	#if defined flagSDL2
	Factory::RegisterAtom<SdlContextAtom>();
	#endif
	#if defined flagSDL2
	Factory::RegisterAtom<SdlEventAtomPipe>();
	#endif
	Factory::RegisterAtom<TestEventSrcPipe>();
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglImageLoader>();
	#endif
	Factory::RegisterAtom<VolumeLoaderAtom>();
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11VideoAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglVideoAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglFboAtomSA>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11SwVideoAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11SwFboAtomSA>();
	#endif
	#if (defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglFboAtomSA>();
	#endif
	#if (defined flagSDL2 && defined flagOGL && defined flagUPPCORE)
	Factory::RegisterAtom<SdlUppOglDeviceSA>();
	#endif
	#if (defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglFboPipe>();
	#endif
	#if (defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglFboAtom>();
	#endif
	#if (defined flagSDL2 && defined flagUPPCORE)
	Factory::RegisterAtom<SdlUppEventsBasePipe>();
	#endif
	#if defined flagSDL2
	Factory::RegisterAtom<SdlVideoAtomPipe>();
	#endif
	#if defined flagSDL2
	Factory::RegisterAtom<SdlProgAtomPipe>();
	#endif
	#if (defined flagPOSIX && defined flagSCREEN)
	Factory::RegisterAtom<X11ProgAtomPipe>();
	#endif
	#if defined flagSCREEN
	Factory::RegisterAtom<X11SwFboGuiProg>();
	#endif
	#if (defined flagSCREEN && defined flagOGL)
	Factory::RegisterAtom<X11OglFboGuiProg>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglFboGuiProg>();
	#endif
	#if defined flagSDL2
	Factory::RegisterAtom<SdlVideoAtom>();
	#endif
	#if defined flagSDL2
	Factory::RegisterAtom<SdlAudioAtom>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglShaderAtom>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglShaderAtomSA>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglTextureSource>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglVolumeSource>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglAudioSink>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglKeyboardSource>();
	#endif
	#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
	Factory::RegisterAtom<SdlOglAudioSource>();
	#endif
}

