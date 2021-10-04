
#define USE_DUMMY 1

HEADER11(			CenterCustomer,		CustomerBase,			customer,	CenterOrder,	CenterReceipt,	CenterOrder)
HEADER_ACTION(		CenterCustomer,		center.customer)

HEADER11(			TestRealtimeSrc,	RollingValueBase,		pipe,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		TestRealtimeSrc,	center.audio.src.test)

HEADER11(			TestRealtimeSink,	VoidSinkBase,				pipe,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		TestRealtimeSink,	center.audio.sink)
HEADER_ACTION(		TestRealtimeSink,	center.audio.sink.test.realtime)

HEADER11(			AudioHardwareSink,	PortaudioSink,				pipe,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		AudioHardwareSink,	center.audio.sink)
HEADER_ACTION(		AudioHardwareSink,	center.audio.sink.hw)

HEADER11(			AudioDecoderSrc,	FfmpegAtomBase,		pipe,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		AudioDecoderSrc,	perma.audio.source.decoder)

HEADER11(			AudioDbgSrc,		AudioGenBase,		pipe,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		AudioDbgSrc,		center.audio.src.dbg_generator)

HEADER12(			AudioSplitter,		SplitterBase,			pipe,	CenterAudio,	CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		AudioSplitter,		center.audio.side.src)
HEADER_ACTION(		AudioSplitter,		center.audio.side.src.center)

HEADER21(			AudioJoiner,		JoinerBase,				pipe,		CenterAudio,	CenterOrder,	CenterAudio,	CenterAudio)
HEADER_ACTION(		AudioJoiner,		center.audio.side.sink)
HEADER_ACTION(		AudioJoiner,		center.audio.side.sink.center)

HEADER11(			VideoDbgSrc,		VideoGenBase,		pipe,		CenterVideo,	CenterOrder,	CenterVideo)
HEADER_ACTION(		VideoDbgSrc,		center.video.src.dbg_generator)
HEADER_ARG(			VideoDbgSrc,		GUI,		1)

HEADER11(			AccelVideoDbgSrc,	AccelVideoGenBase,		pipe,		AccelVideo,		AccelOrder,		AccelVideo)
HEADER_ACTION(		AccelVideoDbgSrc,	accel.video.src.dbg_generator)
HEADER_ARG(			AccelVideoDbgSrc,	GUI,		1)




HEADER11(			AccelCustomer,		CustomerBase,			customer,	AccelOrder,		AccelReceipt,	AccelOrder)
HEADER_ACTION(		AccelCustomer,		accel.customer)
HEADER_ARG(			AccelCustomer,		GUI,		1)

HEADER11(			SdlContextAtom,		SDL2ContextBase,			driver,		CenterReceipt,	CenterReceipt,	CenterReceipt)
HEADER_ACTION(		SdlContextAtom,		sdl.context)

HEADER11(			SdlEventAtomPipe,	SDL2EventsBase,				pipe,		CenterEvent,	CenterOrder,	CenterEvent)
HEADER_ACTION(		SdlEventAtomPipe,	sdl.event.pipe)

HEADER11(			EventStatePipe,		EventStateBase,			driver_pipe,	CenterEvent,	CenterEvent,	CenterReceipt)
HEADER_ACTION(		EventStatePipe,		state.event.pipe)

HEADER12(			SdlEventAtom,		SDL2EventsBase,				pipe,		CenterEvent,	CenterOrder,	CenterEvent,	CenterEvent)
HEADER_ACTION(		SdlEventAtom,		sdl.event)

HEADER21(			EventState,			EventStateBase,			driver_pipe,	CenterEvent,	CenterEvent,	CenterEvent,	CenterReceipt)
HEADER_ACTION(		EventState,			state.event)

HEADER11(			TestEventSrcPipe,	TestEventSrcBase,			pipe,		CenterEvent,	CenterOrder,	CenterEvent)
HEADER_ACTION(		TestEventSrcPipe,	event.src.test.pipe)



HEADER11(			SdlVideoAtomSA,		SDL2ScreenBase,				pipe,		AccelVideo,		AccelOrder,		AccelReceipt)
HEADER_ACTION(		SdlVideoAtomSA,		sdl.video.standalone)
HEADER_ARG(			SdlVideoAtomSA,		GUI,		1)

HEADER11(			SdlVideoAtom,		SDL2ScreenBase,				pipe,		AccelVideo,		AccelVideo,		AccelReceipt)
HEADER_ACTION(		SdlVideoAtom,		sdl.video)
HEADER_ARG(			SdlVideoAtom,		GUI,		1)

HEADER21(			SdlVideoPipe,		SDL2ScreenBase,				pipe,		AccelVideo,		AccelOrder,		AccelVideo,		AccelReceipt)
HEADER_ACTION(		SdlVideoPipe,		sdl.video.pipe)
HEADER_ARG(			SdlVideoPipe,		GUI,		1)

HEADER11(			SdlSwVideoAtom,		SDL2SwScreenBase,			pipe,		CenterVideo,	CenterVideo,	CenterReceipt)
HEADER_ACTION(		SdlSwVideoAtom,		sdl.swvideo)
HEADER_ARG(			SdlSwVideoAtom,		GUI,		1)

HEADER11 (			SdlAudioAtom,		SDL2AudioOutputBase,		pipe,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		SdlAudioAtom,		center.audio.sink)
HEADER_ACTION(		SdlAudioAtom,		sdl.audio)

HEADER11(			OglShaderSource,	OglShaderBase,			pipe,		AccelVideo,		AccelOrder,		AccelVideo)
HEADER_ACTION(		OglShaderSource,	accel.video.source)
HEADER_ARG(			OglShaderSource,	GUI,		1)

HEADER12(			OglShaderPipe,		OglShaderBase,			pipe,		AccelVideo,		AccelOrder,		AccelVideo,		AccelReceipt)
HEADER_ACTION(		OglShaderPipe,		accel.video.source.pipe)
HEADER_ARG(			OglShaderPipe,		GUI,		1)
