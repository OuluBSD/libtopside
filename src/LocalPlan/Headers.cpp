#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


void InterfaceBuilder::Headers() {
	AddCustomBase("CustomerBase");
	AddCustomBase("RollingValueBase");
	AddCustomBase("VoidSinkBase");
	AddCustomBase("VoidPollerSinkBase");
	AddCustomBase("AudioGenBase");
	AddCustomBase("VoidBase");
	AddCustomBase("VideoGenBase", "SCREEN");
	AddCustomBase("FfmpegSourceDevice", "FFMPEG");
	AddCustomBase("EventStateBase", "SCREEN");
	AddCustomBase("HandleEventsBase", "SCREEN");
	AddCustomBase("HandleVideoBase", "SCREEN");
	AddCustomBase("X11SwFboBase", "POSIXDESKTOP&SCREEN");
	AddCustomBase("X11SwShaderBase", "POSIXDESKTOP&SCREEN");
	AddCustomBase("X11OglFboBase", "POSIXDESKTOP&SCREEN&OGL");
	AddCustomBase("X11OglShaderBase", "POSIXDESKTOP&SCREEN&OGL");
	AddCustomBase("TestEventSrcBase");
	AddCustomBase("SdlOglFboBase", "SCREEN&SDL2&OGL");
	AddCustomBase("SdlOglShaderBase", "SCREEN&SDL2&OGL");
	AddCustomBase("SdlOglImageBase", "SCREEN&SDL2&OGL");
	AddCustomBase("SdlOglTextureBase", "SCREEN&SDL2&OGL");
	AddCustomBase("SdlOglFboReaderBase", "SCREEN&SDL2&OGL");
	AddCustomBase("SdlOglKeyboardBase", "SCREEN&SDL2&OGL");
	AddCustomBase("SdlOglAudioBase", "SCREEN&SDL2&OGL");
	AddCustomBase("X11SwFboProgBase", "POSIXDESKTOP&SCREEN");
	AddCustomBase("X11OglFboProgBase", "POSIXDESKTOP&SCREEN&OGL");
	AddCustomBase("SdlOglFboProgBase", "SCREEN&SDL2&OGL");
	AddCustomBase("WinDxFboBase", "SCREEN&WIN32&DX");
	AddCustomBase("MidiFileReaderAtom");
	AddCustomBase("MidiNullAtom");
	AddCustomBase("AudioMixerBase");
	
	AddHeader("CenterCustomer", "CustomerBase", "customer")
		.In("CenterReceipt").Out("CenterOrder")
		.Action("center.customer")
		.Link("CUSTOMER", "CUSTOMER")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("TestRealtimeSrc", "RollingValueBase", "pipe")
		.In("CenterOrder").Out("CenterAudio")
		.Action("center.audio.src.test")
		.Link("PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("TestRealtimeSink", "VoidSinkBase", "pipe")
		.In("CenterAudio").Out("CenterReceipt")
		.Action("center.audio.sink.test.realtime")
		.Link("INTERVAL_PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("TestPollerSink", "VoidPollerSinkBase", "pipe")
		.In("CenterAudio").Out("CenterReceipt")
		.Action("center.audio.sink.test.poller")
		.Link("PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("PortaudioSink", "PortaudioSinkDevice", "pipe")
		.In("CenterAudio").Out("CenterReceipt")
		.Action("center.audio.sink.hw")
		.Link("EXTERNAL_PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("AudioDecoderSrc", "FfmpegSourceDevice", "pipe")
		.In("CenterOrder").Out("CenterAudio")
		.Action("perma.audio.source.decoder")
		.Link("PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagFFMPEG", "1")
	;
	
	AddHeader("AudioDbgSrc", "AudioGenBase", "pipe")
		.In("CenterOrder").Out("CenterAudio")
		.Action("center.audio.src.dbg_generator")
		.Link("PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("AudioSplitter", "VoidBase", "pipe")
		.In("CenterAudio").Out("CenterReceipt").Out("CenterAudio")
		.Action("center.audio.side.src.center")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("SPLITTER", "PROCESS")
	;
	
	AddHeader("AudioSplitterUser", "VoidBase", "pipe")
		.In("CenterAudio").Out("CenterReceipt").OutOpt(8, "CenterAudio")
		.Action("center.audio.side.src.center.user")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("SPLITTER", "PROCESS")
	;
	
	AddHeader("AudioJoiner", "VoidBase", "pipe")
		.In("CenterOrder").In("CenterAudio").Out("CenterAudio")
		.Action("center.audio.side.sink.center")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("JOINER", "PROCESS")
	;
	
	AddHeader("AudioJoinerUser", "VoidBase", "pipe")
		.In("CenterOrder").InOpt("CenterAudio").Out("CenterAudio")
		.Action("center.audio.side.sink.center.user")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("JOINER", "PROCESS")
	;
	
	AddHeader("AudioJoiner2User", "VoidBase", "pipe")
		.In("CenterOrder").InOpt("CenterAudio").InOpt("CenterAudio").Out("CenterAudio")
		.Action("center.audio.side.sink2.center.user")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("JOINER", "PROCESS")
	;
	
	AddHeader("AudioMixer16", "AudioMixerBase", "pipe")
		.In("CenterOrder").InOpt(16,"CenterAudio")
		.Out("CenterAudio")
		.Action("center.audio.mixer16")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("MERGER", "PROCESS")
	;
	
	AddHeader("VideoDbgSrc", "VideoGenBase", "pipe")
		.In("CenterOrder").Out("CenterVideo")
		.Action("center.video.src.dbg_generator")
		//.Arg("reqdef_flagSCREEN", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("WebcamPipe", "V4L2OpenCVCamera", "pipe")
		.In("CenterOrder").Out("CenterVideo")
		.Action("center.video.webcam.pipe")
		//.Arg("reqdef_flagOPENCV", "1")
		//.Arg("reqdef_flagLINUX", "1")
		.Link("PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("WebcamAtom", "V4L2OpenCVCamera", "pipe")
		.In("CenterOrder").Out("CenterReceipt").OutOpt("CenterVideo")
		.Action("center.video.webcam")
		//.Arg("reqdef_flagOPENCV", "1")
		//.Arg("reqdef_flagLINUX", "1")
		.Link("PIPE_OPTSIDE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("AudioLoaderAtom", "FfmpegSourceDevice", "pipe")
		.In("CenterOrder").Out("CenterReceipt").OutOpt("CenterAudio")
		.Action("center.audio.loader")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagFFMPEG", "1")
		.Link("PIPE_OPTSIDE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("VideoLoaderAtom", "FfmpegSourceDevice", "pipe")
		.In("CenterOrder").Out("CenterReceipt").OutOpt("CenterVideo").OutOpt("CenterAudio")
		.Action("center.video.loader")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagFFMPEG", "1")
		.Link("PIPE_OPTSIDE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("EventStatePipe", "EventStateBase", "driver_pipe")
		.In("CenterEvent").Out("CenterReceipt")
		.Action("state.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("HandleProgEvents", "HandleEventsBase", "pipe")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("center.events.prog.ecs")
		.Arg("HINT_PKG", "AtomHandle")
		.Link("PIPE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("CenterProgPipe", "HandleVideoBase", "pipe")
		.In("CenterOrder")
		.Out("CenterProg")
		.Action("center.video.prog.pipe")
		.Arg("HINT_PKG", "AtomHandle")
		.Link("PIPE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("OglProgPipe", "HandleVideoBase", "pipe")
		.In("OglOrder")
		.Out("OglProg")
		.Action("ogl.prog.pipe")
		.Arg("HINT_PKG", "AtomHandle")
		.Link("PIPE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("HandleProgVideo", "HandleVideoBase", "pipe")
		.In("CenterOrder")
		.Out("CenterReceipt")
		.Action("center.video.prog.ecs")
		.Arg("HINT_PKG", "AtomHandle")
		.Link("PIPE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("X11SwFboProg", "X11SwFboBase", "pipe")
		.In("CenterOrder")
		.InOpt("CenterFbo")
		.Out("CenterFbo")
		.Action("x11.sw.fbo.program")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("X11OglFboProg", "X11OglFboBase", "pipe")
		.In("OglOrder")
		.InOpt("OglFbo")
		.Out("OglFbo")
		.Action("x11.ogl.fbo.program")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
	;
	
	AddHeader("SdlSwFboProg", "SdlCenterFboSinkDevice", "pipe")
		.In("CenterOrder")
		.InOpt("CenterFbo")
		.Out("CenterFbo")
		.Action("sdl.sw.fbo.program")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglFboProg", "SdlOglFboBase", "pipe")
		.In("OglOrder")
		.InOpt("OglFbo")
		.Out("OglFbo")
		.Action("sdl.ogl.fbo.program")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("OpenHMDPipe", "OpenHMDSinkDevice", "pipe")
		.In("CenterOrder")
		.Out("CenterEvent")
		.Action("x11.ogl.ohmd.events")
		.Arg("HINT_PKG", "AtomVR")
		.Link("PIPE", "PROCESS")
		//.Arg("reqdef_flagOPENHMD", "1")
	;
	
	AddHeader("LocalHMDPipe", "LocalHMDSinkDevice", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("x11.ogl.holo.events")
		.Arg("HINT_PKG", "AtomVR")
		.Link("PIPE", "PROCESS")
		//.Arg("reqdef_flagLOCALHMD", "1")
	;
	
	AddHeader("RemoteVRServerPipe", "RemoteVRServerSinkDevice", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("tcp.ogl.holo.events")
		.Arg("HINT_PKG", "AtomVR")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("BluetoothHoloPipe", "DevBluetoothSinkDevice", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("bluetooth.holo.events")
		.Arg("HINT_PKG", "AtomVR")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("X11SwShaderPipe", "X11SwShaderBase", "pipe")
		.In("CenterOrder").Out("CenterFbo")
		.Action("x11.sw.fbo.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("X11OglShaderPipe", "X11OglShaderBase", "pipe")
		.In("OglOrder").Out("OglFbo")
		.Action("x11.ogl.fbo.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglShaderPipe", "SdlOglShaderBase", "pipe")
		.In("OglOrder").Out("OglFbo")
		.Action("sdl.ogl.fbo.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("X11SwFboAtomPipe", "X11SwSinkDevice", "pipe")
		.In("CenterFbo").Out("CenterReceipt")
		.Action("x11.sw.fbo.sink")
		//.Arg("reqdef_flagSCREEN", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11OglFboAtomPipe", "X11OglSinkDevice", "pipe")
		.In("OglFbo").Out("OglReceipt")
		.Action("x11.ogl.fbo.sink")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlSwFboAtomPipe", "SdlCenterFboSinkDevice", "pipe")
		.In("CenterFbo").Out("CenterReceipt")
		.Action("sdl.sw.fbo.sink")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglFboAtomPipe", "SdlOglVideoSinkDevice", "pipe")
		.In("OglFbo").Out("OglReceipt")
		.Action("sdl.ogl.fbo.sink")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglProgAtomPipe", "SdlOglVideoSinkDevice", "pipe")
		.In("OglProg").Out("OglReceipt")
		.Action("sdl.ogl.prog.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11ContextAtom", "X11Context", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("x11.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("X11SwContextAtom", "X11SwContext", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("x11.sw.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("X11OglContextAtom", "X11OglContext", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("x11.ogl.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("X11EventAtomPipe", "X11EventsBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("x11.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11SwEventAtomPipe", "X11SwEventsBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("x11.sw.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11OglEventAtomPipe", "X11OglEventsBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("x11.ogl.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("WinContextAtom", "WinContext", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("win.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("WinVideoAtomPipe", "WinSinkDevice", "pipe")
		.In("CenterVideo").Out("CenterReceipt")
		.Action("win.video.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("DxCustomer", "CustomerBase", "customer")
		.In("DxReceipt").Out("DxOrder")
		.Action("dx.customer")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("CUSTOMER", "CUSTOMER")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("WinDxContextAtom", "WinDxContext", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("win.dx.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("WinDxFboProg", "WinDxFboBase", "pipe")
		.In("DxOrder")
		.InOpt("DxFbo")
		.Out("DxFbo")
		.Action("win.dx.fbo.program")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
	;
	
	AddHeader("WinDxFboAtomPipe", "WinDxSinkDevice", "pipe")
		.In("DxFbo").Out("DxReceipt")
		.Action("win.dx.fbo.sink")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("WinDxFboAtomSA", "WinDxSinkDevice", "pipe")
		.In("DxOrder").Out("DxReceipt")
		.Action("win.dx.fbo.standalone")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	/*
	AddHeader("X11SwContextAtom", "X11SwContext", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("x11.sw.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("X11OglContextAtom", "X11OglContext", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("x11.ogl.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
	;
	
	AddHeader("X11EventAtomPipe", "X11EventsBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("x11.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11SwEventAtomPipe", "X11SwEventsBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("x11.sw.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11OglEventAtomPipe", "X11OglEventsBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("x11.ogl.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("POLLER_PIPE", "PROCESS")
	;
	*/
	AddHeader("OglCustomer", "CustomerBase", "customer")
		.In("OglReceipt").Out("OglOrder")
		.Action("ogl.customer")
		//.Arg("reqdef_flagSCREEN", "1")
		.Link("CUSTOMER", "CUSTOMER")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("SdlContextAtom", "SdlContextBase", "driver")
		.In("CenterReceipt").Out("CenterReceipt")
		.Action("sdl.context")
		.Link("DRIVER", "DRIVER")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSDL2", "1")
	;
	
	AddHeader("SdlEventAtomPipe", "SdlEventsBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("sdl.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		//.Arg("reqdef_flagSDL2", "1")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("TestEventSrcPipe", "TestEventSrcBase", "pipe")
		.In("CenterOrder").Out("CenterEvent")
		.Action("event.src.test.pipe")
		.Link("PIPE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("SdlOglImageLoader", "SdlOglImageBase", "pipe")
		.In("CenterOrder").Out("CenterReceipt").OutOpt("CenterVideo")
		.Action("center.image.loader")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Link("PIPE_OPTSIDE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("VolumeLoaderAtom", "RawByteStaticSource", "pipe")
		.In("CenterOrder").Out("CenterReceipt").OutOpt("CenterVolume")
		.Action("center.volume.loader")
		.Link("PIPE_OPTSIDE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("X11VideoAtomPipe", "X11SinkDevice", "pipe")
		.In("CenterVideo").Out("CenterReceipt")
		.Action("x11.video.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11OglVideoAtomPipe", "X11OglSinkDevice", "pipe")
		.In("CenterVideo").Out("CenterReceipt")
		.Action("glx.video.pipe")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11OglFboAtomSA", "X11OglSinkDevice", "pipe")
		.In("OglOrder").Out("OglReceipt")
		.Action("x11.ogl.fbo.standalone")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11SwVideoAtomPipe", "X11SwSinkDevice", "pipe")
		.In("CenterFbo").Out("CenterReceipt")
		.Action("x11.sw.video.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11SwFboAtomSA", "X11SwSinkDevice", "pipe")
		.In("CenterOrder").Out("CenterReceipt")
		.Action("x11.sw.fbo.standalone")
		//.Arg("reqdef_flagSCREEN", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglFboAtomSA", "SdlOglVideoSinkDevice", "pipe")
		.In("OglOrder").Out("OglReceipt")
		.Action("sdl.fbo.standalone")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlUppOglDeviceSA", "SdlUppOglDevice", "pipe")
		.In("OglOrder").Out("OglReceipt")
		.Action("uppsdl.ogl.standalone")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglFboPipe", "SdlOglVideoSinkDevice", "pipe")
		.In("OglFbo").Out("OglReceipt")
		.Action("sdl.fbo.sink")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglFboAtom", "SdlOglVideoSinkDevice", "pipe")
		.In("OglOrder").InOpt("OglFbo").InOpt("OglFbo").InOpt("OglFbo").InOpt("OglFbo")
		.Out("OglReceipt").OutOpt("OglFbo").OutOpt("OglFbo").OutOpt("OglFbo").OutOpt("OglFbo")
		.Action("sdl.fbo")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlUppEventsBasePipe", "SdlUppEventsBase", "pipe")
		.In("CenterOrder").Out("CenterReceipt")
		.Action("uppsdl.event.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlVideoAtomPipe", "SdlCenterVideoSinkDevice", "pipe")
		.In("CenterVideo").Out("CenterReceipt")
		.Action("sdl.video.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlProgAtomPipe", "SdlCenterVideoSinkDevice", "pipe")
		.In("CenterProg")
		.Out("CenterReceipt")
		.Action("sdl.prog.pipe")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11ProgAtomPipe", "X11SinkDevice", "pipe")
		.In("CenterProg")
		.Out("CenterReceipt")
		.Action("x11.prog.pipe")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("X11SwFboGuiProg", "X11SwFboProgBase", "pipe")
		.In("CenterProg")
		.Out("CenterReceipt")
		.OutOpt("CenterFbo")
		.Action("x11.sw.prog")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("X11OglFboGuiProg", "X11OglFboProgBase", "pipe")
		.In("CenterProg")
		.Out("CenterReceipt")
		.OutOpt("OglFbo")
		.Action("x11.ogl.prog")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SdlOglFboGuiProg", "SdlOglFboProgBase", "pipe")
		.In("CenterProg")
		.Out("CenterReceipt")
		.OutOpt("OglFbo")
		.Action("sdl.ogl.prog")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SdlVideoAtom", "SdlCenterVideoSinkDevice", "pipe")
		.In("CenterOrder").InOpt("CenterVideo").InOpt("CenterVideo").InOpt("CenterVideo").InOpt("CenterVideo")
		.Out("CenterReceipt").OutOpt("CenterVideo").OutOpt("CenterVideo").OutOpt("CenterVideo").OutOpt("CenterVideo")
		.Action("sdl.video")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("POLLER_PIPE", "PROCESS")
	;
	
	AddHeader("SdlAudioAtom", "SdlAudioSinkDevice", "pipe")
		.In("CenterAudio").Out("CenterReceipt")
		.Action("sdl.audio")
		//.Arg("reqdef_flagSDL2", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("EXTERNAL_PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglShaderAtom", "SdlOglShaderBase", "pipe")
		.In("OglOrder").InOpt("OglFbo").InOpt("OglFbo").InOpt("OglFbo").InOpt("OglFbo")
		.Out("OglReceipt").OutOpt("OglFbo").OutOpt("OglFbo").OutOpt("OglFbo").OutOpt("OglFbo")
		.Action("sdl.ogl.fbo.side")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SdlOglShaderAtomSA", "SdlOglShaderBase", "pipe")
		.In("OglOrder").Out("OglReceipt")
		.Action("ogl.fbo.source.standalone")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("SdlOglTextureSource", "SdlOglTextureBase", "pipe")
		.In("OglOrder").InOpt("CenterVideo").Out("OglReceipt").OutOpt("OglFbo")
		.Action("sdl.ogl.fbo.image")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SdlOglVolumeSource", "SdlOglTextureBase", "pipe")
		.In("OglOrder").InOpt("CenterVolume").Out("OglReceipt").OutOpt("OglFbo")
		.Action("sdl.ogl.fbo.volume")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SdlOglAudioSink", "SdlOglFboReaderBase", "pipe")
		.In("OglOrder").InOpt("OglFbo").Out("OglReceipt").OutOpt("CenterAudio")
		.Action("sdl.ogl.fbo.center.audio")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SdlOglKeyboardSource", "SdlOglKeyboardBase", "pipe")
		.In("OglOrder").InOpt("OglFbo").InOpt("OglFbo").InOpt("OglFbo").InOpt("OglFbo")
		.Out("OglReceipt").OutOpt("OglFbo").OutOpt("OglFbo").OutOpt("OglFbo").OutOpt("OglFbo")
		.Action("sdl.ogl.fbo.keyboard")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Arg("HINT_PKG", "AtomMinimal")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SdlOglAudioSource", "SdlOglAudioBase", "pipe")
		.In("OglOrder").InOpt("CenterAudio").Out("OglReceipt").OutOpt("OglFbo")
		.Action("sdl.ogl.center.fbo.audio")
		//.Arg("reqdef_flagSCREEN", "1")
		//.Arg("reqdef_flagSDL2", "1")
		//.Arg("reqdef_flagOGL", "1")
		.Link("PIPE_OPTSIDE", "PROCESS")
		.Arg("HINT_PKG", "AtomMinimal")
	;
	
	AddHeader("MidiFileReaderPipe", "MidiFileReaderAtom", "pipe")
		.In("CenterOrder").Out("CenterMidi")
		.Action("midi.file.reader.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("MidiFileReader", "MidiFileReaderAtom", "pipe")
		.In("CenterOrder")
		.Out("CenterReceipt").OutOpt("CenterMidi")
		.Action("midi.file.reader")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("MidiFileReader16", "MidiFileReaderAtom", "pipe")
		.In("CenterOrder")
		.Out("CenterReceipt").OutOpt(16, "CenterMidi")
		.Action("midi.file.reader16")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("MidiNullSink", "MidiNullAtom", "pipe")
		.In("CenterMidi").Out("CenterReceipt")
		.Action("midi.null.sink")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("FluidsynthPipe", "FluidsynthInstrument", "pipe")
		.In("CenterOrder").InOpt("CenterMidi").Out("CenterAudio")
		.Action("fluidsynth.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("SoftInstrumentPipe", "SoftInstrument", "pipe")
		.In("CenterOrder").InOpt("CenterMidi").Out("CenterAudio")
		.Action("softinstru.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("FmSynthPipe", "FmSynthInstrument", "pipe")
		.In("CenterOrder").InOpt("CenterMidi").Out("CenterAudio")
		.Action("fmsynth.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("LV2InstrumentPipe", "LV2Instrument", "pipe")
		.In("CenterOrder").InOpt("CenterMidi").Out("CenterAudio")
		.Action("lv2.instrument.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("CoreSynthPipe", "CoreSynthInstrument", "pipe")
		.In("CenterOrder").InOpt("CenterMidi").Out("CenterAudio")
		.Action("coresynth.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("CoreDrummerPipe", "CoreDrummerInstrument", "pipe")
		.In("CenterOrder").InOpt("CenterMidi")
		.Out("CenterReceipt").OutOpt(4, "CenterAudio")
		.Action("coredrummer.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("CoreEffectPipe", "AudioCoreEffect", "pipe")
		.In("CenterAudio").InOpt(8, "CenterAudio")
		.Out("CenterAudio")
		.Action("corefx.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("CoreEffectAtom", "AudioCoreEffect", "pipe")
		.In("CenterOrder").InOpt(8, "CenterAudio")
		.Out("CenterAudio")
		.Action("corefx.atom")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("LV2EffectPipe", "LV2Effect", "pipe")
		.In("CenterAudio").Out("CenterAudio")
		.Action("lv2.effect.pipe")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("PortmidiPipe", "PortmidiSource", "pipe")
		.In("CenterOrder").Out("CenterMidi")
		.Action("midi.src.portmidi")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE", "PROCESS")
	;
	
	AddHeader("PortmidiSend", "PortmidiSource", "pipe")
		.In("CenterOrder")
		.Out("CenterReceipt").OutOpt(4, "CenterMidi")
		.Action("midi.src.side.portmidi")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
	AddHeader("CoreAudioFileOut", "CoreAudioSink", "pipe")
		.In("CenterAudio")
		.Out("CenterReceipt")
		.Action("audio.file.writer")
		.Arg("HINT_PKG", "AtomAudio")
		.Link("PIPE_OPTSIDE", "PROCESS")
	;
	
}


NAMESPACE_TOPSIDE_END
