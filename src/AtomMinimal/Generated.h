#ifndef _AtomMinimal_Generated_h_
#define _AtomMinimal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

class CenterCustomer : public CustomerBase {

public:
	RTTI_DECL1(CenterCustomer, CustomerBase)
	COPY_PANIC(CenterCustomer)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class TestRealtimeSrc : public RollingValueBase {

public:
	RTTI_DECL1(TestRealtimeSrc, RollingValueBase)
	COPY_PANIC(TestRealtimeSrc)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class TestRealtimeSink : public VoidSinkBase {

public:
	RTTI_DECL1(TestRealtimeSink, VoidSinkBase)
	COPY_PANIC(TestRealtimeSink)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class TestPollerSink : public VoidPollerSinkBase {

public:
	RTTI_DECL1(TestPollerSink, VoidPollerSinkBase)
	COPY_PANIC(TestPollerSink)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if (defined flagBUILTIN_PORTAUDIO) || (defined flagPORTAUDIO)
class PortaudioSink : public PortaudioSinkDevice {

public:
	RTTI_DECL1(PortaudioSink, PortaudioSinkDevice)
	COPY_PANIC(PortaudioSink)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagFFMPEG
class AudioDecoderSrc : public FfmpegSourceDevice {

public:
	RTTI_DECL1(AudioDecoderSrc, FfmpegSourceDevice)
	COPY_PANIC(AudioDecoderSrc)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

class AudioDbgSrc : public AudioGenBase {

public:
	RTTI_DECL1(AudioDbgSrc, AudioGenBase)
	COPY_PANIC(AudioDbgSrc)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class AudioSplitter : public VoidBase {

public:
	RTTI_DECL1(AudioSplitter, VoidBase)
	COPY_PANIC(AudioSplitter)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class AudioSplitterUser : public VoidBase {

public:
	RTTI_DECL1(AudioSplitterUser, VoidBase)
	COPY_PANIC(AudioSplitterUser)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class AudioJoiner : public VoidBase {

public:
	RTTI_DECL1(AudioJoiner, VoidBase)
	COPY_PANIC(AudioJoiner)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class AudioJoinerUser : public VoidBase {

public:
	RTTI_DECL1(AudioJoinerUser, VoidBase)
	COPY_PANIC(AudioJoinerUser)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class AudioJoiner2User : public VoidBase {

public:
	RTTI_DECL1(AudioJoiner2User, VoidBase)
	COPY_PANIC(AudioJoiner2User)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

class AudioMixer16 : public AudioMixerBase {

public:
	RTTI_DECL1(AudioMixer16, AudioMixerBase)
	COPY_PANIC(AudioMixer16)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if defined flagSCREEN
class VideoDbgSrc : public VideoGenBase {

public:
	RTTI_DECL1(VideoDbgSrc, VideoGenBase)
	COPY_PANIC(VideoDbgSrc)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagOPENCV && defined flagLINUX)
class WebcamPipe : public V4L2OpenCVCamera {

public:
	RTTI_DECL1(WebcamPipe, V4L2OpenCVCamera)
	COPY_PANIC(WebcamPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagOPENCV && defined flagLINUX)
class WebcamAtom : public V4L2OpenCVCamera {

public:
	RTTI_DECL1(WebcamAtom, V4L2OpenCVCamera)
	COPY_PANIC(WebcamAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagFFMPEG
class AudioLoaderAtom : public FfmpegSourceDevice {

public:
	RTTI_DECL1(AudioLoaderAtom, FfmpegSourceDevice)
	COPY_PANIC(AudioLoaderAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagFFMPEG
class VideoLoaderAtom : public FfmpegSourceDevice {

public:
	RTTI_DECL1(VideoLoaderAtom, FfmpegSourceDevice)
	COPY_PANIC(VideoLoaderAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSCREEN
class EventStatePipe : public EventStateBase {

public:
	RTTI_DECL1(EventStatePipe, EventStateBase)
	COPY_PANIC(EventStatePipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11SwFboProg : public X11SwFboBase {

public:
	RTTI_DECL1(X11SwFboProg, X11SwFboBase)
	COPY_PANIC(X11SwFboProg)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
class X11OglFboProg : public X11OglFboBase {

public:
	RTTI_DECL1(X11OglFboProg, X11OglFboBase)
	COPY_PANIC(X11OglFboProg)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSDL2
class SdlSwFboProg : public SdlCenterFboSinkDevice {

public:
	RTTI_DECL1(SdlSwFboProg, SdlCenterFboSinkDevice)
	COPY_PANIC(SdlSwFboProg)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglFboProg : public SdlOglFboBase {

public:
	RTTI_DECL1(SdlOglFboProg, SdlOglFboBase)
	COPY_PANIC(SdlOglFboProg)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11SwShaderPipe : public X11SwShaderBase {

public:
	RTTI_DECL1(X11SwShaderPipe, X11SwShaderBase)
	COPY_PANIC(X11SwShaderPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
class X11OglShaderPipe : public X11OglShaderBase {

public:
	RTTI_DECL1(X11OglShaderPipe, X11OglShaderBase)
	COPY_PANIC(X11OglShaderPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglShaderPipe : public SdlOglShaderBase {

public:
	RTTI_DECL1(SdlOglShaderPipe, SdlOglShaderBase)
	COPY_PANIC(SdlOglShaderPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11SwFboAtomPipe : public X11SwSinkDevice {

public:
	RTTI_DECL1(X11SwFboAtomPipe, X11SwSinkDevice)
	COPY_PANIC(X11SwFboAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
class X11OglFboAtomPipe : public X11OglSinkDevice {

public:
	RTTI_DECL1(X11OglFboAtomPipe, X11OglSinkDevice)
	COPY_PANIC(X11OglFboAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSDL2
class SdlSwFboAtomPipe : public SdlCenterFboSinkDevice {

public:
	RTTI_DECL1(SdlSwFboAtomPipe, SdlCenterFboSinkDevice)
	COPY_PANIC(SdlSwFboAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSDL2 && defined flagOGL)
class SdlOglFboAtomPipe : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtomPipe, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11ContextAtom : public X11Context {

public:
	RTTI_DECL1(X11ContextAtom, X11Context)
	COPY_PANIC(X11ContextAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11SwContextAtom : public X11SwContext {

public:
	RTTI_DECL1(X11SwContextAtom, X11SwContext)
	COPY_PANIC(X11SwContextAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
class X11OglContextAtom : public X11OglContext {

public:
	RTTI_DECL1(X11OglContextAtom, X11OglContext)
	COPY_PANIC(X11OglContextAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11EventAtomPipe : public X11EventsBase {

public:
	RTTI_DECL1(X11EventAtomPipe, X11EventsBase)
	COPY_PANIC(X11EventAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11SwEventAtomPipe : public X11SwEventsBase {

public:
	RTTI_DECL1(X11SwEventAtomPipe, X11SwEventsBase)
	COPY_PANIC(X11SwEventAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

class OglCustomer : public CustomerBase {

public:
	RTTI_DECL1(OglCustomer, CustomerBase)
	COPY_PANIC(OglCustomer)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if defined flagSDL2
class SdlContextAtom : public SdlContextBase {

public:
	RTTI_DECL1(SdlContextAtom, SdlContextBase)
	COPY_PANIC(SdlContextAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSDL2
class SdlEventAtomPipe : public SdlEventsBase {

public:
	RTTI_DECL1(SdlEventAtomPipe, SdlEventsBase)
	COPY_PANIC(SdlEventAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

class TestEventSrcPipe : public TestEventSrcBase {

public:
	RTTI_DECL1(TestEventSrcPipe, TestEventSrcBase)
	COPY_PANIC(TestEventSrcPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglImageLoader : public SdlOglImageBase {

public:
	RTTI_DECL1(SdlOglImageLoader, SdlOglImageBase)
	COPY_PANIC(SdlOglImageLoader)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

class VolumeLoaderAtom : public RawByteStaticSource {

public:
	RTTI_DECL1(VolumeLoaderAtom, RawByteStaticSource)
	COPY_PANIC(VolumeLoaderAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};

#if (defined flagPOSIX && defined flagSCREEN)
class X11VideoAtomPipe : public X11SinkDevice {

public:
	RTTI_DECL1(X11VideoAtomPipe, X11SinkDevice)
	COPY_PANIC(X11VideoAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
class X11OglVideoAtomPipe : public X11OglSinkDevice {

public:
	RTTI_DECL1(X11OglVideoAtomPipe, X11OglSinkDevice)
	COPY_PANIC(X11OglVideoAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
class X11OglFboAtomSA : public X11OglSinkDevice {

public:
	RTTI_DECL1(X11OglFboAtomSA, X11OglSinkDevice)
	COPY_PANIC(X11OglFboAtomSA)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11SwVideoAtomPipe : public X11SwSinkDevice {

public:
	RTTI_DECL1(X11SwVideoAtomPipe, X11SwSinkDevice)
	COPY_PANIC(X11SwVideoAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagPOSIX && defined flagSCREEN)
class X11SwFboAtomSA : public X11SwSinkDevice {

public:
	RTTI_DECL1(X11SwFboAtomSA, X11SwSinkDevice)
	COPY_PANIC(X11SwFboAtomSA)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSDL2 && defined flagOGL)
class SdlOglFboAtomSA : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtomSA, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboAtomSA)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSDL2 && defined flagOGL)
class SdlOglFboPipe : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboPipe, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSDL2 && defined flagOGL)
class SdlOglFboAtom : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtom, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSDL2
class SdlVideoAtomPipe : public SdlCenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoAtomPipe, SdlCenterVideoSinkDevice)
	COPY_PANIC(SdlVideoAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSDL2
class SdlProgAtomPipe : public SdlCenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlProgAtomPipe, SdlCenterVideoSinkDevice)
	COPY_PANIC(SdlProgAtomPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSDL2
class SdlVideoAtom : public SdlCenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoAtom, SdlCenterVideoSinkDevice)
	COPY_PANIC(SdlVideoAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSDL2
class SdlAudioAtom : public SdlAudioSinkDevice {

public:
	RTTI_DECL1(SdlAudioAtom, SdlAudioSinkDevice)
	COPY_PANIC(SdlAudioAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglShaderAtom : public SdlOglShaderBase {

public:
	RTTI_DECL1(SdlOglShaderAtom, SdlOglShaderBase)
	COPY_PANIC(SdlOglShaderAtom)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglShaderAtomSA : public SdlOglShaderBase {

public:
	RTTI_DECL1(SdlOglShaderAtomSA, SdlOglShaderBase)
	COPY_PANIC(SdlOglShaderAtomSA)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglTextureSource : public SdlOglTextureBase {

public:
	RTTI_DECL1(SdlOglTextureSource, SdlOglTextureBase)
	COPY_PANIC(SdlOglTextureSource)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglVolumeSource : public SdlOglTextureBase {

public:
	RTTI_DECL1(SdlOglVolumeSource, SdlOglTextureBase)
	COPY_PANIC(SdlOglVolumeSource)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglAudioSink : public SdlOglFboReaderBase {

public:
	RTTI_DECL1(SdlOglAudioSink, SdlOglFboReaderBase)
	COPY_PANIC(SdlOglAudioSink)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglKeyboardSource : public SdlOglKeyboardBase {

public:
	RTTI_DECL1(SdlOglKeyboardSource, SdlOglKeyboardBase)
	COPY_PANIC(SdlOglKeyboardSource)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagSCREEN && defined flagSDL2 && defined flagOGL)
class SdlOglAudioSource : public SdlOglAudioBase {

public:
	RTTI_DECL1(SdlOglAudioSource, SdlOglAudioBase)
	COPY_PANIC(SdlOglAudioSource)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

}

}
#endif
