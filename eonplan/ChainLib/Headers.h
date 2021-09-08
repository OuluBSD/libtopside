
#define USE_DUMMY 1

HEADER2(CustomerAtom,			AtomReceiptSink,	customer,	CenterReceipt,	CenterOrder)
HEADER_ACTION(CustomerAtom,		customer.test.single)

HEADER2(TestRealtimeSrc,		CenterSourceAsync,	source,		CenterOrder,	CenterAudio)
HEADER2(TestRealtimeSink,		CenterSinkSync,		sink,		CenterAudio,	CenterReceipt)
HEADER_ACTION(TestRealtimeSrc,	center.audio.src.test)
HEADER_ACTION(TestRealtimeSink,	center.audio.sink.test.realtime)

HEADER2(			AudioHardwareSink,	CenterSinkPolling,		sink,		CenterAudio,	CenterReceipt)
HEADER_ACTION(		AudioHardwareSink,	center.audio.sink.hw)
HEADER_INHERITS(	AudioHardwareSink,	PortaudioSink)
HEADER_ARG(			AudioHardwareSink,	ALT_LINK,	1)

HEADER2(			AudioDecoderSrc,	CenterSourceAsync,		source,		CenterOrder,	CenterAudio)
HEADER_ACTION(		AudioDecoderSrc,	perma.audio.source.decoder)
HEADER_INHERITS(	AudioDecoderSrc,	FfmpegAtomBase)
HEADER_ARG(			AudioDecoderSrc,	ALT_LINK,	1)
HEADER_ARG(			AudioDecoderSrc,	ALT_FWD,	1)

#if USE_DUMMY
HEADER2(			VideoHardwareSink,	DummySideAsync,		sink,		AccelVideo,		AccelReceipt)
HEADER2(			VideoShaderSrc,		DummySideAsync,		source,		AccelOrder,		AccelVideo)
HEADER2(			VideoShaderBuffer,	DummySideAsync,		side_pipe,	AccelOrder,		AccelReceipt)
#else
HEADER2(			VideoHardwareSink,	AccelSideAsync,		sink,		AccelVideo,		AccelReceipt)
HEADER2(			VideoShaderSrc,		AccelSideAsync,		source,		AccelOrder,		AccelVideo)
HEADER2(			VideoShaderBuffer,	AccelSideAsync,		side_pipe,	AccelOrder,		AccelReceipt)
#endif

//HEADER(AccelCustomer,		AccelReceiptOrder)s
//HEADER(NetCustomer,		NetReceiptOrder)