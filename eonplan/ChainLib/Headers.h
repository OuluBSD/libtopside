
#define USE_DUMMY 1

HEADER11(			CenterCustomer,		CustomerBaseT,			customer,	CenterOrder,	CenterReceipt,	CenterOrder)
HEADER_ACTION(		CenterCustomer,		center.customer)
//HEADER_INHERITS(	CenterCustomer,		CustomerBase)

HEADER11(			TestRealtimeSrc,	CenterSourceAsync,		source,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		TestRealtimeSrc,	center.audio.src.test)
HEADER_INHERITS(	TestRealtimeSrc,	RollingValueBase)

HEADER11(			TestRealtimeSink,	CenterSinkPolling,		sink,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_INHERITS(	TestRealtimeSink,	VoidSinkBase)
HEADER_ACTION(		TestRealtimeSink,	center.audio.sink)
HEADER_ACTION(		TestRealtimeSink,	center.audio.sink.test.realtime)

HEADER11(			AudioHardwareSink,	CenterSinkPolling,		sink,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_ACTION(		AudioHardwareSink,	center.audio.sink)
HEADER_ACTION(		AudioHardwareSink,	center.audio.sink.hw)
HEADER_INHERITS(	AudioHardwareSink,	PortaudioSink)
HEADER_ARG(			AudioHardwareSink,	ALT_LINK,	1)

HEADER11(			AudioDecoderSrc,	CenterSourceAsync,		source,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		AudioDecoderSrc,	perma.audio.source.decoder)
HEADER_INHERITS(	AudioDecoderSrc,	FfmpegAtomBase)
HEADER_ARG(			AudioDecoderSrc,	ALT_LINK,	1)
HEADER_ARG(			AudioDecoderSrc,	ALT_FWD,	1)

HEADER11(			AudioDbgSrc,		CenterSourceAsync,		source,		CenterAudio,	CenterOrder,	CenterAudio)
HEADER_ACTION(		AudioDbgSrc,		center.audio.src.dbg_generator)
HEADER_INHERITS(	AudioDbgSrc,		AudioGenBase)
HEADER_ARG(			AudioDbgSrc,		ALT_LINK,	1)
HEADER_ARG(			AudioDbgSrc,		ALT_FWD,	1)

HEADER12(			AudioSplitter,		CenterSourcePolling,		side_source,	CenterAudio,	CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_INHERITS(	AudioSplitter,		SplitterBase)
HEADER_ACTION(		AudioSplitter,		center.audio.side.src)
HEADER_ACTION(		AudioSplitter,		center.audio.side.src.center)

HEADER21(			AudioJoiner,		CenterSinkPolling,		side_sink,		CenterAudio,	CenterOrder,	CenterAudio,	CenterAudio)
HEADER_INHERITS(	AudioJoiner,		JoinerBase)
HEADER_ACTION(		AudioJoiner,		center.audio.side.sink)
HEADER_ACTION(		AudioJoiner,		center.audio.side.sink.center)

HEADER11(			VideoDbgSrc,		CenterSourceAsync,		source,		CenterVideo,	CenterOrder,	CenterVideo)
HEADER_ACTION(		VideoDbgSrc,		center.video.src.dbg_generator)
HEADER_INHERITS(	VideoDbgSrc,		VideoGenBase)
HEADER_ARG(			VideoDbgSrc,		ALT_LINK,	1)
HEADER_ARG(			VideoDbgSrc,		ALT_FWD,	1)

HEADER11(			AccelVideoDbgSrc,	AccelSourceAsync,		source,		AccelVideo,		AccelOrder,		AccelVideo)
HEADER_ACTION(		AccelVideoDbgSrc,	accel.video.src.dbg_generator)
HEADER_INHERITS(	AccelVideoDbgSrc,	AccelVideoGenBase)
HEADER_ARG(			AccelVideoDbgSrc,	ALT_LINK,	1)
HEADER_ARG(			AccelVideoDbgSrc,	ALT_FWD,	1)




HEADER11(			AccelCustomer,		CustomerBaseT,			customer,	AccelOrder,		AccelReceipt,	AccelOrder)
HEADER_ACTION(		AccelCustomer,		accel.customer)
//HEADER_INHERITS(	AccelCustomer,		CustomerBase)

/*HEADER11(			VideoHardwareSink,	AccelSinkPolling,				sink,		AccelVideo,		AccelReceipt)
HEADER_ACTION(		VideoHardwareSink,	accel.video.sink.hw)
HEADER_ARG(			VideoHardwareSink,	ALT_LINK,	1)*/

/*HEADER11(			VideoShaderSrc,		AccelAsync,				source,		AccelOrder,		AccelVideo)
HEADER_ACTION(		VideoShaderSrc,		accel.video.src)
HEADER_ARG(			VideoShaderSrc,		ALT_LINK,	1)
HEADER_ARG(			VideoShaderSrc,		ALT_FWD,	1)

HEADER11(			VideoShaderBuffer,	AccelAsync,				side_pipe,	AccelOrder,		AccelReceipt)
HEADER_ACTION(		VideoShaderBuffer,	accel.video.buffer)
HEADER_ARG(			VideoShaderBuffer,	ALT_LINK,	1)

#if USE_DUMMY
HEADER_INHERITS(	VideoHardwareSink,	DummyAlt)
HEADER_INHERITS(	VideoShaderSrc,		DummyAlt)
HEADER_INHERITS(	VideoShaderBuffer,	DummyAlt)
#else
HEADER_INHERITS(	VideoHardwareSink,	SystemVideoSink)
HEADER_INHERITS(	VideoShaderSrc,		SystemVideoSink)
HEADER_INHERITS(	VideoShaderBuffer,	SystemVideoSink)
#endif
*/

HEADER11(			SdlContextAtom,		CenterDriver,			driver,		CenterReceipt,	CenterReceipt,	CenterReceipt)
HEADER_INHERITS(	SdlContextAtom,		SDL2ContextBase)
HEADER_ACTION(		SdlContextAtom,		sdl.context)
HEADER_ARG(			SdlContextAtom,		ALT_LINK,	1)
HEADER_ARG(			SdlContextAtom,		ALT_FWD,	1)

/*HEADER11(			SdlEventAtom,		CenterSourceAsync,		source,		CenterOrder,	CenterEvent)
HEADER_INHERITS(	SdlEventAtom,		SDL2EventsBase)
HEADER_ACTION(		SdlEventAtom,		sdl.event)*/

HEADER11(			SdlVideoAtomSA,		AccelSinkPolling,		sink,		AccelVideo,		AccelOrder,		AccelReceipt)
HEADER_INHERITS(	SdlVideoAtomSA,		SDL2ScreenBase)
HEADER_ACTION(		SdlVideoAtomSA,		sdl.video.standalone)

HEADER11(			SdlVideoAtom,		AccelSinkPolling,		sink,		AccelVideo,		AccelVideo,		AccelReceipt)
HEADER_INHERITS(	SdlVideoAtom,		SDL2ScreenBase)
HEADER_ACTION(		SdlVideoAtom,		sdl.video)

HEADER21(			SdlVideoPipe,		AccelSinkPolling,		pipe,		AccelVideo,		AccelOrder,		AccelVideo,		AccelReceipt)
HEADER_INHERITS(	SdlVideoPipe,		SDL2ScreenBase)
HEADER_ACTION(		SdlVideoPipe,		sdl.video.pipe)

/*HEADER11(			SideSdlVideoAtom,	AccelSinkPolling,		sink,		AccelVideo,		AccelVideo,		AccelReceipt)
HEADER_INHERITS(	SideSdlVideoAtom,	SDL2ScreenBase)
HEADER_ACTION(		SideSdlVideoAtom,	sdl.video.with.buf0)*/

HEADER11(			SdlSwVideoAtom,		CenterSinkPolling,		sink,		CenterVideo,	CenterVideo,	CenterReceipt)
HEADER_INHERITS(	SdlSwVideoAtom,		SDL2SwScreenBase)
HEADER_ACTION(		SdlSwVideoAtom,		sdl.swvideo)

HEADER11 (			SdlAudioAtom,		CenterSinkAsync,		sink,		CenterAudio,	CenterAudio,	CenterReceipt)
HEADER_INHERITS(	SdlAudioAtom,		SDL2AudioOutputBase)
HEADER_ACTION(		SdlAudioAtom,		center.audio.sink)
HEADER_ACTION(		SdlAudioAtom,		sdl.audio)

HEADER11(			OglShaderSource,	AccelSourcePolling,		source,		AccelVideo,		AccelOrder,		AccelVideo)
HEADER_INHERITS(	OglShaderSource,	OglShaderBase)
HEADER_ACTION(		OglShaderSource,	accel.video.source)
HEADER_ARG(			OglShaderSource,	ALT_LINK,	1)

HEADER12(			OglShaderPipe,		AccelSourcePolling,		pipe,		AccelVideo,		AccelOrder,		AccelVideo,		AccelReceipt)
HEADER_INHERITS(	OglShaderPipe,		OglShaderBase)
HEADER_ACTION(		OglShaderPipe,		accel.video.source.pipe)
HEADER_ARG(			OglShaderPipe,		ALT_LINK,	1)

/*HEADER12(			OglShaderBuffer,	AccelSourcePolling,		side_source,	AccelVideo,		AccelOrder,		AccelVideo,		AccelReceipt)
HEADER_INHERITS(	OglShaderBuffer,	OglShaderBase)
HEADER_ACTION(		OglShaderBuffer,	accel.video.buffer)
HEADER_ARG(			OglShaderBuffer,	ALT_LINK,	1)*/


//HEADER(AccelCustomer,		AccelReceiptOrder)s
//HEADER(NetCustomer,		NetReceiptOrder)