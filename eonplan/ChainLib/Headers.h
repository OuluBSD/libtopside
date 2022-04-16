
#define USE_DUMMY 1

HEADER11(			CenterCustomer,		CustomerBase,				customer,	CenterOrder,	CenterReceipt,	CenterOrder)
HEADER_ACTION(		CenterCustomer,		center.customer)
HEADER_LINK(		CenterCustomer,		CUSTOMER, CUSTOMER)
HEADER_ARG(			CenterCustomer,		HINT_PKG,					"AtomDebug")

HEADER11(			TestRealtimeSrc,	RollingValueBase,			pipe,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		TestRealtimeSrc,	center.audio.src.test)
HEADER_LINK(		TestRealtimeSrc,	PIPE, PROCESS)
HEADER_ARG(			TestRealtimeSrc,	HINT_PKG,					"AtomDebug")


HEADER11(			TestRealtimeSink,	VoidSinkBase,				pipe,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		TestRealtimeSink,	center.audio.sink)
HEADER_ACTION(		TestRealtimeSink,	center.audio.sink.test.realtime)
HEADER_LINK(		TestRealtimeSink,	INTERVAL_PIPE, PROCESS)
HEADER_ARG(			TestRealtimeSink,	HINT_PKG,					"AtomDebug")

HEADER11(			TestPollerSink,		VoidPollerSinkBase,			pipe,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		TestPollerSink,		center.audio.sink)
HEADER_ACTION(		TestPollerSink,		center.audio.sink.test.poller)
HEADER_LINK(		TestPollerSink,		PIPE, PROCESS)
HEADER_ARG(			TestPollerSink,		HINT_PKG,					"AtomDebug")

HEADER11(			PortaudioSink,		PortaudioSinkDevice,		pipe,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		PortaudioSink,		center.audio.sink)
HEADER_ACTION(		PortaudioSink,		center.audio.sink.hw)
HEADER_LINK(		PortaudioSink,		EXTERNAL_PIPE, PROCESS)
HEADER_ARG(			PortaudioSink,		HINT_PKG,					"AtomDebug")

HEADER11(			AudioDecoderSrc,	FfmpegSourceDevice,			pipe,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		AudioDecoderSrc,	perma.audio.source.decoder)
HEADER_LINK(		AudioDecoderSrc,	PIPE, PROCESS)
HEADER_ARG(			AudioDecoderSrc,	HINT_PKG,					"AtomDebug")
HEADER_ARG(			AudioDecoderSrc,	reqdef_flagFFMPEG,			1)

HEADER11(			AudioDbgSrc,		AudioGenBase,				pipe,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		AudioDbgSrc,		center.audio.src.dbg_generator)
HEADER_LINK(		AudioDbgSrc,		PIPE, PROCESS)
HEADER_ARG(			AudioDbgSrc,		HINT_PKG,					"AtomDebug")

HEADER12(			AudioSplitter,		VoidBase,					pipe,		CenterAudio,	CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		AudioSplitter,		center.audio.side.src)
HEADER_ACTION(		AudioSplitter,		center.audio.side.src.center)
HEADER_ARG(			AudioSplitter,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		AudioSplitter,		SPLITTER, PROCESS)

HEADER12_U01(		AudioSplitterUser,	VoidBase,					pipe,		CenterAudio,	CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		AudioSplitterUser,	center.audio.side.src)
HEADER_ACTION(		AudioSplitterUser,	center.audio.side.src.center.user)
HEADER_ARG(			AudioSplitterUser,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		AudioSplitterUser,	SPLITTER, PROCESS)

HEADER21(			AudioJoiner,		VoidBase,					pipe,		CenterAudio,	CenterOrder,	CenterAudio,	CenterAudio)
HEADER_ACTION(		AudioJoiner,		center.audio.side.sink)
HEADER_ACTION(		AudioJoiner,		center.audio.side.sink.center)
HEADER_ARG(			AudioJoiner,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		AudioJoiner,		JOINER, PROCESS)

HEADER21_U10(		AudioJoinerUser,	VoidBase,					pipe,		CenterAudio,	CenterOrder,	CenterAudio,	CenterAudio)
HEADER_ACTION(		AudioJoinerUser,	center.audio.side.sink)
HEADER_ACTION(		AudioJoinerUser,	center.audio.side.sink.center.user)
HEADER_ARG(			AudioJoinerUser,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		AudioJoinerUser,	JOINER, PROCESS)

HEADER31_U20(		AudioJoiner2User,	VoidBase,					pipe,		CenterAudio,	CenterOrder,	CenterAudio,	CenterAudio,	CenterAudio)
HEADER_ACTION(		AudioJoiner2User,	center.audio.side.sink)
HEADER_ACTION(		AudioJoiner2User,	center.audio.side.sink2.center.user)
HEADER_ARG(			AudioJoiner2User,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		AudioJoiner2User,	JOINER, PROCESS)

HEADER11(			VideoDbgSrc,		VideoGenBase,				pipe,		CenterVideo,	CenterOrder,	CenterVideo)
HEADER_ACTION(		VideoDbgSrc,		center.video.src.dbg_generator)
HEADER_ARG(			VideoDbgSrc,		reqdef_flagSCREEN,		1)
HEADER_ARG(			VideoDbgSrc,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		VideoDbgSrc,		PIPE, PROCESS)

HEADER11(			WebcamPipe,			OpenCVBase,					pipe,		CenterVideo,	CenterOrder,	CenterVideo)
HEADER_ACTION(		WebcamPipe,			center.video.webcam.pipe)
HEADER_ARG(			WebcamPipe,			reqdef_HAVE_OPENCV,	1)

HEADER12_U01(		WebcamAtom,			OpenCVBase,					pipe,		CenterVideo,	CenterOrder,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		WebcamAtom,			center.video.webcam)
HEADER_ARG(			WebcamAtom,			reqdef_HAVE_OPENCV,	1)

HEADER12_U01(		AudioLoaderAtom,	FfmpegSourceDevice,			pipe,		CenterAudio,	CenterOrder,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		AudioLoaderAtom,	center.audio.loader)
HEADER_ARG(			AudioLoaderAtom,	reqdef_flagSCREEN,	1)
HEADER_ARG(			AudioLoaderAtom,	reqdef_flagFFMPEG,	1)

HEADER13_U02(		VideoLoaderAtom,	FfmpegSourceDevice,			pipe,		CenterVideo,	CenterOrder,	CenterVideo,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		VideoLoaderAtom,	center.video.loader)
HEADER_ARG(			VideoLoaderAtom,	reqdef_flagSCREEN,	1)
HEADER_ARG(			VideoLoaderAtom,	reqdef_flagFFMPEG,	1)

HEADER11(			EventStatePipe,		EventStateBase,			driver_pipe,	CenterEvent,	CenterEvent,	CenterReceipt)
HEADER_ACTION(		EventStatePipe,		state.event.pipe)
HEADER_ARG(			EventStatePipe,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		EventStatePipe,		PIPE, PROCESS)
HEADER_ARG(			EventStatePipe,		reqdef_flagSCREEN,		1)



HEADER11(			EcsEventsAtom,		EcsEventsBase,				pipe,		CenterEvent,	CenterOrder,	CenterReceipt)
HEADER_ACTION(		EcsEventsAtom,		ecs.system.events)
HEADER_ARG(			EcsEventsAtom,		reqdef_flagSCREEN,	1)

//HEADER12_U01(		EcsOglAtom,			EcsOglBase,					pipe,		OglFbo,			OglOrder,		OglFbo,			OglReceipt)
//HEADER_ACTION(		EcsOglAtom,			ecs.system.rendering)
//HEADER_ARG(			EcsOglAtom,			reqdef_flagSCREEN,	1)

HEADER11(			EcsCpuVideoPipe,	EcsVideoBase,				pipe,		CenterVideo,	CenterOrder,	CenterVideo)
HEADER_ACTION(		EcsCpuVideoPipe,	center.video.ecs.pipe)
//HEADER_ARG(			EcsCpuVideoPipe,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		EcsCpuVideoPipe,	PIPE, PROCESS)
HEADER_ARG(			EcsCpuVideoPipe,	reqdef_flagSCREEN,	1)

HEADER11(			EcsProgVideo,		EcsVideoBase,				pipe,		CenterProg,		CenterOrder,	CenterProg)
HEADER_ACTION(		EcsProgVideo,		center.video.prog.ecs)
HEADER_ARG(			EcsProgVideo,		reqdef_flagSCREEN,	1)

HEADER11(			EcsOglFboPipe,		EcsVideoBase,				pipe,		OglFbo,			OglOrder,		OglFbo)
HEADER_ACTION(		EcsOglFboPipe,		ogl.fbo.ecs.pipe)
HEADER_ARG(			EcsOglFboPipe,		reqdef_flagSCREEN,	1)

HEADER55_U44(		EcsCpuVideo,		EcsVideoBase,				pipe,		CenterVideo,	CenterOrder,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		EcsCpuVideo,		center.video.ecs)
HEADER_ARG(			EcsCpuVideo,		reqdef_flagSCREEN,	1)

HEADER55_U44(		EcsOglFbo,			EcsVideoBase,				pipe,		OglFbo,			OglOrder,		OglFbo,		OglReceipt)
HEADER_ACTION(		EcsOglFbo,			ogl.fbo.ecs)
HEADER_ARG(			EcsOglFbo,			reqdef_flagSCREEN,	1)





HEADER11(			X11SwFboPipe,		X11SwFboBase,				pipe,		CenterFbo,		CenterOrder,	CenterFbo)
HEADER_ACTION(		X11SwFboPipe,		x11sw.fbo.pipe)
HEADER_ARG(			X11SwFboPipe,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		X11SwFboPipe,		PIPE, PROCESS)
HEADER_ARG(			X11SwFboPipe,		reqdef_flagSCREEN,			1)





HEADER11(			OglCustomer,		CustomerBase,				customer,	OglOrder,		OglReceipt,		OglOrder)
HEADER_ACTION(		OglCustomer,		ogl.customer)
HEADER_ARG(			OglCustomer,		reqdef_flagSCREEN,		1)
HEADER_LINK(		OglCustomer,		CUSTOMER, CUSTOMER)
HEADER_ARG(			OglCustomer,		HINT_PKG,					"AtomDebug")

HEADER11(			SdlContextAtom,		Sdl2ContextBase,			driver,		CenterReceipt,	CenterReceipt,	CenterReceipt)
HEADER_ACTION(		SdlContextAtom,		sdl.context)
HEADER_LINK(		SdlContextAtom,		DRIVER, DRIVER)
HEADER_ARG(			SdlContextAtom,		HINT_PKG,					"AtomDebug")
HEADER_ARG(			SdlContextAtom,		reqdef_flagSDL2,		1)

HEADER11(			SdlEventAtomPipe,	SDL2EventsBase,				pipe,		CenterEvent,	CenterOrder,	CenterEvent)
HEADER_ACTION(		SdlEventAtomPipe,	sdl.event.pipe)

HEADER12(			SdlEventAtom,		SDL2EventsBase,				pipe,		CenterEvent,	CenterOrder,	CenterEvent,	CenterEvent)
HEADER_ACTION(		SdlEventAtom,		sdl.event)

HEADER21(			EventState,			EventStateBase,			driver_pipe,	CenterEvent,	CenterEvent,	CenterEvent,	CenterReceipt)
HEADER_ACTION(		EventState,			state.event)

HEADER11(			TestEventSrcPipe,	TestEventSrcBase,			pipe,		CenterEvent,	CenterOrder,	CenterEvent)
HEADER_ACTION(		TestEventSrcPipe,	event.src.test.pipe)
HEADER_LINK(		TestEventSrcPipe,	PIPE, PROCESS)
HEADER_ARG(			TestEventSrcPipe,	HINT_PKG,					"AtomDebug")

HEADER12_U01(		SdlImageLoader,		SDL2ImageBase,				pipe,		CenterVideo,	CenterOrder,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		SdlImageLoader,		center.image.loader)
HEADER_ARG(			SdlImageLoader,		reqdef_flagSCREEN,		1)

HEADER12_U01(		VolumeLoaderAtom,	VolumeLoaderBase,			pipe,		CenterVolume,	CenterOrder,	CenterVolume,	CenterReceipt)
HEADER_ACTION(		VolumeLoaderAtom,	center.volume.loader)
HEADER_ARG(			VolumeLoaderAtom,	reqdef_flagSCREEN,		1)




HEADER11(			X11VideoAtomPipe,	X11SinkDevice,				pipe,		CenterVideo,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		X11VideoAtomPipe,	x11.video.pipe)
HEADER_ACTION(		X11VideoAtomPipe,	any.video.pipe)
HEADER_ARG(			X11VideoAtomPipe,	reqdef_flagSCREEN,		1)
HEADER_ARG(			X11VideoAtomPipe,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		X11VideoAtomPipe,	POLLER_PIPE, PROCESS)

HEADER11(			GlxVideoAtomPipe,	X11GlxSinkDevice,			pipe,		CenterVideo,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		GlxVideoAtomPipe,	glx.video.pipe)
HEADER_ARG(			GlxVideoAtomPipe,	reqdef_flagOGL,			1)
HEADER_ARG(			GlxVideoAtomPipe,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		GlxVideoAtomPipe,	POLLER_PIPE, PROCESS)

HEADER11(			GlxFboAtomSA,		X11GlxSinkDevice,			pipe,		OglFbo,			OglOrder,		OglReceipt)
HEADER_ACTION(		GlxFboAtomSA,		glx.fbo.standalone)
HEADER_ARG(			GlxFboAtomSA,		reqdef_flagOGL,			1)
HEADER_ARG(			GlxFboAtomSA,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		GlxFboAtomSA,		POLLER_PIPE, PROCESS)



HEADER11(			X11SwVideoAtomPipe,	X11SwSinkDevice,			pipe,		CenterFbo,		CenterFbo,	CenterReceipt)
HEADER_ACTION(		X11SwVideoAtomPipe,	x11sw.video.pipe)
HEADER_ARG(			X11SwVideoAtomPipe,	reqdef_flagSCREEN,		1)
HEADER_ARG(			X11SwVideoAtomPipe,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		X11SwVideoAtomPipe,	POLLER_PIPE, PROCESS)

HEADER11(			X11SwFboAtomSA,		X11SwSinkDevice,			pipe,		OglFbo,			OglOrder,		OglReceipt)
HEADER_ACTION(		X11SwFboAtomSA,		x11sw.fbo.standalone)
HEADER_ARG(			X11SwFboAtomSA,		reqdef_flagSCREEN,			1)
HEADER_ARG(			X11SwFboAtomSA,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		X11SwFboAtomSA,		POLLER_PIPE, PROCESS)






HEADER11(			SdlFboAtomSA,		Sdl2OglVideoSinkDevice,			pipe,		OglFbo,			OglOrder,		OglReceipt)
HEADER_ACTION(		SdlFboAtomSA,		sdl.fbo.standalone)
HEADER_ARG(			SdlFboAtomSA,		reqdef_flagSDL2,		1)
HEADER_ARG(			SdlFboAtomSA,		reqdef_flagOGL,			1)
HEADER_ARG(			SdlFboAtomSA,		HINT_PKG,					"AtomDebug")
HEADER_LINK(		SdlFboAtomSA,		POLLER_PIPE, PROCESS)

HEADER11(			SdlFboPipe,			Sdl2OglVideoSinkDevice,			pipe,		OglFbo,			OglFbo,			OglReceipt)
HEADER_ACTION(		SdlFboPipe,			sdl.fbo.pipe)
HEADER_ARG(			SdlFboPipe,			reqdef_flagSDL2,		1)
HEADER_ARG(			SdlFboPipe,			reqdef_flagOGL,			1)
HEADER_ARG(			SdlFboPipe,			HINT_PKG,					"AtomDebug")
HEADER_LINK(		SdlFboPipe,			POLLER_PIPE, PROCESS)

HEADER21(			SdlFboPipeSide,		Sdl2OglVideoSinkDevice,			pipe,		OglFbo,			OglOrder,		OglFbo,		OglReceipt)
HEADER_ACTION(		SdlFboPipeSide,		sdl.fbo.pipe.side)
HEADER_ARG(			SdlFboPipeSide,		reqdef_flagSCREEN,		1)

HEADER55_U44(		SdlFboAtom,			Sdl2OglVideoSinkDevice,			pipe,		OglFbo,			OglOrder,		OglFbo,		OglReceipt)
HEADER_ACTION(		SdlFboAtom,			sdl.fbo)
HEADER_ARG(			SdlFboAtom,			reqdef_flagSDL2,		1)
HEADER_ARG(			SdlFboAtom,			reqdef_flagOGL,			1)
HEADER_ARG(			SdlFboAtom,			HINT_PKG,					"AtomDebug")
HEADER_LINK(		SdlFboAtom,			POLLER_PIPE, PROCESS)

HEADER11(			SdlVideoAtomPipe,	Sdl2CenterVideoSinkDevice,		pipe,		CenterVideo,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		SdlVideoAtomPipe,	sdl.video.pipe)
HEADER_ACTION(		SdlVideoAtomPipe,	any.video.pipe)
HEADER_ARG(			SdlVideoAtomPipe,	reqdef_flagSCREEN,		1)
HEADER_ARG(			SdlVideoAtomPipe,	reqdef_flagSDL2,		1)
HEADER_ARG(			SdlVideoAtomPipe,	HINT_PKG,					"AtomDebug")
HEADER_LINK(		SdlVideoAtomPipe,	POLLER_PIPE, PROCESS)

HEADER11(			SdlVideoProgAtom,	Sdl2CenterVideoSinkDevice,		pipe,		CenterVideo,	CenterProg,		CenterReceipt)
HEADER_ACTION(		SdlVideoProgAtom,	sdl.video.prog)
HEADER_ARG(			SdlVideoProgAtom,	reqdef_flagSCREEN,		1)

HEADER11(			SdlVideoAtomSA,		Sdl2CenterVideoSinkDevice,		pipe,		CenterVideo,	CenterOrder,	CenterReceipt)
HEADER_ACTION(		SdlVideoAtomSA,		sdl.video.standalone)
HEADER_ARG(			SdlVideoAtomSA,		reqdef_flagSCREEN,		1)

HEADER55_U44(		SdlVideoAtom,		Sdl2CenterVideoSinkDevice,		pipe,		CenterVideo,	CenterOrder,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		SdlVideoAtom,		sdl.video)
HEADER_ARG(			SdlVideoAtom,		reqdef_flagSCREEN,		1)
HEADER_ARG(			SdlVideoAtom,		reqdef_flagSDL2,		1)
HEADER_ARG(			SdlVideoAtom,		HINT_PKG,				"AtomDebug")
HEADER_LINK(		SdlVideoAtom,		POLLER_PIPE, PROCESS)




HEADER11 (			SdlAudioAtom,		Sdl2AudioSinkDevice,	pipe,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		SdlAudioAtom,		center.audio.sink)
HEADER_ACTION(		SdlAudioAtom,		sdl.audio)
HEADER_ARG(			SdlAudioAtom,		reqdef_flagSDL2,		1)
HEADER_ARG(			SdlAudioAtom,		HINT_PKG,				"AtomDebug")
HEADER_LINK(		SdlAudioAtom,		EXTERNAL_PIPE, PROCESS)

HEADER11(			SdlOglShaderPipe,	SdlOglShaderBase,		pipe,		OglFbo,			OglOrder,		OglFbo)
HEADER_ACTION(		SdlOglShaderPipe,	any.ogl.fbo.source.pipe)
HEADER_ACTION(		SdlOglShaderPipe,	sdl.ogl.fbo.source.pipe)
HEADER_ARG(			SdlOglShaderPipe,	reqdef_flagOGL,			1)
HEADER_ARG(			SdlOglShaderPipe,	HINT_PKG,				"AtomDebug")
HEADER_LINK(		SdlOglShaderPipe,	PIPE, PROCESS)

HEADER55_U44(		SdlOglShaderAtom,	SdlOglShaderBase,		pipe,		OglFbo,			OglOrder,		OglFbo,		OglReceipt)
HEADER_ACTION(		SdlOglShaderAtom,	sdl.ogl.fbo.source)
HEADER_ACTION(		SdlOglShaderAtom,	any.ogl.fbo.source)
HEADER_ARG(			SdlOglShaderAtom,	reqdef_flagOGL,			1)
HEADER_ARG(			SdlOglShaderAtom,	HINT_PKG,				"AtomDebug")
HEADER_LINK(		SdlOglShaderAtom,	PIPE, PROCESS)

HEADER11(			SdlOglShaderAtomSA,	SdlOglShaderBase,			pipe,		OglFbo,			OglOrder,		OglReceipt)
HEADER_ACTION(		SdlOglShaderAtomSA,	ogl.fbo.source.standalone)
HEADER_ARG(			SdlOglShaderAtomSA,	reqdef_flagOGL,			1)
HEADER_ARG(			SdlOglShaderAtomSA,	HINT_PKG,				"AtomDebug")
HEADER_LINK(		SdlOglShaderAtomSA,	PIPE, PROCESS)

HEADER22_U11(		OglTextureSource,	OglTextureBase,				pipe,		OglFbo,			OglOrder,		CenterVideo,	OglFbo,			OglReceipt)
HEADER_ACTION(		OglTextureSource,	ogl.fbo.image)
HEADER_ARG(			OglTextureSource,	reqdef_flagSCREEN,		1)

HEADER22_U11(		OglVolumeSource,	OglTextureBase,				pipe,		OglFbo,			OglOrder,		CenterVolume,	OglFbo,			OglReceipt)
HEADER_ACTION(		OglVolumeSource,	ogl.fbo.volume)
HEADER_ARG(			OglVolumeSource,	reqdef_flagSCREEN,		1)

HEADER22_U11(		OglAudioSink,		OglFboReaderBase,			pipe,		OglFbo,			OglOrder,		OglFbo,			CenterAudio,	OglReceipt)
HEADER_ACTION(		OglAudioSink,		ogl.fbo.center.audio)
HEADER_ARG(			OglAudioSink,		reqdef_flagSCREEN,		1)

HEADER12_U01(		OglKeyboardSource,	OglKeyboardBase,			pipe,		OglFbo,			OglOrder,		OglFbo,			OglReceipt)
HEADER_ACTION(		OglKeyboardSource,	ogl.fbo.keyboard)
HEADER_ARG(			OglKeyboardSource,	reqdef_flagSCREEN,		1)

HEADER22_U11(		OglAudioSource,		OglAudioBase,				pipe,		OglFbo,			OglOrder,		CenterAudio,	OglFbo,			OglReceipt)
HEADER_ACTION(		OglAudioSource,		ogl.fbo.audio)
HEADER_ARG(			OglAudioSource,		reqdef_flagSCREEN,		1)





HEADER12_U01(		CpuKeyboardSource,	CpuKeyboardBase,			pipe,		CenterVideo,	CenterOrder,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		CpuKeyboardSource,	center.video.keyboard)
HEADER_ARG(			CpuKeyboardSource,	reqdef_flagSCREEN,		1)

