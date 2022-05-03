#include "AtomDebug.h"

namespace TS {

namespace Parallel {

AtomTypeCls CenterCustomer::GetAtomType()
{
	return ATOM11(CENTER_CUSTOMER, CUSTOMER, CENTER, ORDER, CENTER, RECEIPT, CENTER, ORDER);
}

LinkTypeCls CenterCustomer::GetLinkType()
{
	return LINKTYPE(CUSTOMER, CUSTOMER);
}

void CenterCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CustomerBase>(this);
}

AtomTypeCls CenterCustomer::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestRealtimeSrc::GetAtomType()
{
	return ATOM11(TEST_REALTIME_SRC, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO);
}

LinkTypeCls TestRealtimeSrc::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void TestRealtimeSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<RollingValueBase>(this);
}

AtomTypeCls TestRealtimeSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestRealtimeSink::GetAtomType()
{
	return ATOM11(TEST_REALTIME_SINK, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

LinkTypeCls TestRealtimeSink::GetLinkType()
{
	return LINKTYPE(INTERVAL_PIPE, PROCESS);
}

void TestRealtimeSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidSinkBase>(this);
}

AtomTypeCls TestRealtimeSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestPollerSink::GetAtomType()
{
	return ATOM11(TEST_POLLER_SINK, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

LinkTypeCls TestPollerSink::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void TestPollerSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidPollerSinkBase>(this);
}

AtomTypeCls TestPollerSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls PortaudioSink::GetAtomType()
{
	return ATOM11(PORTAUDIO_SINK, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

LinkTypeCls PortaudioSink::GetLinkType()
{
	return LINKTYPE(EXTERNAL_PIPE, PROCESS);
}

void PortaudioSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<PortaudioSinkDevice>(this);
}

AtomTypeCls PortaudioSink::GetType() const
{
	return GetAtomType();
}

#if defined flagFFMPEG
AtomTypeCls AudioDecoderSrc::GetAtomType()
{
	return ATOM11(AUDIO_DECODER_SRC, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO);
}

LinkTypeCls AudioDecoderSrc::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void AudioDecoderSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<FfmpegSourceDevice>(this);
}

AtomTypeCls AudioDecoderSrc::GetType() const
{
	return GetAtomType();
}

#endif
AtomTypeCls AudioDbgSrc::GetAtomType()
{
	return ATOM11(AUDIO_DBG_SRC, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO);
}

LinkTypeCls AudioDbgSrc::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void AudioDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AudioGenBase>(this);
}

AtomTypeCls AudioDbgSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioSplitter::GetAtomType()
{
	return ATOM12(AUDIO_SPLITTER, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT, CENTER, AUDIO);
}

LinkTypeCls AudioSplitter::GetLinkType()
{
	return LINKTYPE(SPLITTER, PROCESS);
}

void AudioSplitter::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidBase>(this);
}

AtomTypeCls AudioSplitter::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioSplitterUser::GetAtomType()
{
	return ATOM11_U01(AUDIO_SPLITTER_USER, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT, CENTER, AUDIO);
}

LinkTypeCls AudioSplitterUser::GetLinkType()
{
	return LINKTYPE(SPLITTER, PROCESS);
}

void AudioSplitterUser::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidBase>(this);
}

AtomTypeCls AudioSplitterUser::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioJoiner::GetAtomType()
{
	return ATOM21(AUDIO_JOINER, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO, CENTER, AUDIO);
}

LinkTypeCls AudioJoiner::GetLinkType()
{
	return LINKTYPE(JOINER, PROCESS);
}

void AudioJoiner::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidBase>(this);
}

AtomTypeCls AudioJoiner::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioJoinerUser::GetAtomType()
{
	return ATOM11_U10(AUDIO_JOINER_USER, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO, CENTER, AUDIO);
}

LinkTypeCls AudioJoinerUser::GetLinkType()
{
	return LINKTYPE(JOINER, PROCESS);
}

void AudioJoinerUser::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidBase>(this);
}

AtomTypeCls AudioJoinerUser::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioJoiner2User::GetAtomType()
{
	return ATOM11_U20(AUDIO_JOINER2_USER, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO, CENTER, AUDIO, CENTER, AUDIO);
}

LinkTypeCls AudioJoiner2User::GetLinkType()
{
	return LINKTYPE(JOINER, PROCESS);
}

void AudioJoiner2User::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidBase>(this);
}

AtomTypeCls AudioJoiner2User::GetType() const
{
	return GetAtomType();
}

#if defined flagSCREEN
AtomTypeCls VideoDbgSrc::GetAtomType()
{
	return ATOM11(VIDEO_DBG_SRC, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO);
}

LinkTypeCls VideoDbgSrc::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void VideoDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VideoGenBase>(this);
}

AtomTypeCls VideoDbgSrc::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls EventStatePipe::GetAtomType()
{
	return ATOM11(EVENT_STATE_PIPE, DRIVER_PIPE, CENTER, EVENT, CENTER, EVENT, CENTER, RECEIPT);
}

LinkTypeCls EventStatePipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void EventStatePipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EventStateBase>(this);
}

AtomTypeCls EventStatePipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls X11SwFboProg::GetAtomType()
{
	return ATOM11(X11_SW_FBO_PROG, PIPE, CENTER, FBO, CENTER, ORDER, CENTER, FBO);
}

LinkTypeCls X11SwFboProg::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void X11SwFboProg::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11SwFboBase>(this);
}

AtomTypeCls X11SwFboProg::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagOGL
AtomTypeCls X11OglFboProg::GetAtomType()
{
	return ATOM11(X11_OGL_FBO_PROG, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

LinkTypeCls X11OglFboProg::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void X11OglFboProg::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11OglFboBase>(this);
}

AtomTypeCls X11OglFboProg::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagOGL && defined flagSDL2
AtomTypeCls SdlOglShaderProg::GetAtomType()
{
	return ATOM11(SDL_OGL_SHADER_PROG, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

LinkTypeCls SdlOglShaderProg::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void SdlOglShaderProg::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SdlOglFboBase>(this);
}

AtomTypeCls SdlOglShaderProg::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls X11SwShaderPipe::GetAtomType()
{
	return ATOM11(X11_SW_SHADER_PIPE, PIPE, CENTER, FBO, CENTER, ORDER, CENTER, FBO);
}

LinkTypeCls X11SwShaderPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void X11SwShaderPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11SwShaderBase>(this);
}

AtomTypeCls X11SwShaderPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagOGL
AtomTypeCls X11OglShaderPipe::GetAtomType()
{
	return ATOM11(X11_OGL_SHADER_PIPE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

LinkTypeCls X11OglShaderPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void X11OglShaderPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11OglShaderBase>(this);
}

AtomTypeCls X11OglShaderPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagOGL && defined flagSDL2
AtomTypeCls SdlOglShaderPipe::GetAtomType()
{
	return ATOM11(SDL_OGL_SHADER_PIPE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

LinkTypeCls SdlOglShaderPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void SdlOglShaderPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SdlOglShaderBase>(this);
}

AtomTypeCls SdlOglShaderPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls X11SwFboAtomPipe::GetAtomType()
{
	return ATOM11(X11_SW_FBO_ATOM_PIPE, PIPE, CENTER, FBO, CENTER, FBO, CENTER, RECEIPT);
}

LinkTypeCls X11SwFboAtomPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void X11SwFboAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11SwSinkDevice>(this);
}

AtomTypeCls X11SwFboAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagOGL
AtomTypeCls X11OglFboAtomPipe::GetAtomType()
{
	return ATOM11(X11_OGL_FBO_ATOM_PIPE, PIPE, OGL, FBO, OGL, FBO, OGL, RECEIPT);
}

LinkTypeCls X11OglFboAtomPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void X11OglFboAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11OglSinkDevice>(this);
}

AtomTypeCls X11OglFboAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagOGL && defined flagSDL2
AtomTypeCls SdlOglFboAtomPipe::GetAtomType()
{
	return ATOM11(SDL_OGL_FBO_ATOM_PIPE, PIPE, OGL, FBO, OGL, FBO, OGL, RECEIPT);
}

LinkTypeCls SdlOglFboAtomPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void SdlOglFboAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2OglVideoSinkDevice>(this);
}

AtomTypeCls SdlOglFboAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglCustomer::GetAtomType()
{
	return ATOM11(OGL_CUSTOMER, CUSTOMER, OGL, ORDER, OGL, RECEIPT, OGL, ORDER);
}

LinkTypeCls OglCustomer::GetLinkType()
{
	return LINKTYPE(CUSTOMER, CUSTOMER);
}

void OglCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CustomerBase>(this);
}

AtomTypeCls OglCustomer::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSDL2
AtomTypeCls SdlContextAtom::GetAtomType()
{
	return ATOM11(SDL_CONTEXT_ATOM, DRIVER, CENTER, RECEIPT, CENTER, RECEIPT, CENTER, RECEIPT);
}

LinkTypeCls SdlContextAtom::GetLinkType()
{
	return LINKTYPE(DRIVER, DRIVER);
}

void SdlContextAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2ContextBase>(this);
}

AtomTypeCls SdlContextAtom::GetType() const
{
	return GetAtomType();
}

#endif
AtomTypeCls TestEventSrcPipe::GetAtomType()
{
	return ATOM11(TEST_EVENT_SRC_PIPE, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT);
}

LinkTypeCls TestEventSrcPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void TestEventSrcPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<TestEventSrcBase>(this);
}

AtomTypeCls TestEventSrcPipe::GetType() const
{
	return GetAtomType();
}

#if defined flagSCREEN
AtomTypeCls X11VideoAtomPipe::GetAtomType()
{
	return ATOM11(X11_VIDEO_ATOM_PIPE, PIPE, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT);
}

LinkTypeCls X11VideoAtomPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void X11VideoAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11SinkDevice>(this);
}

AtomTypeCls X11VideoAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagOGL
AtomTypeCls X11OglVideoAtomPipe::GetAtomType()
{
	return ATOM11(X11_OGL_VIDEO_ATOM_PIPE, PIPE, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT);
}

LinkTypeCls X11OglVideoAtomPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void X11OglVideoAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11OglSinkDevice>(this);
}

AtomTypeCls X11OglVideoAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagOGL
AtomTypeCls X11OglFboAtomSA::GetAtomType()
{
	return ATOM11(X11_OGL_FBO_ATOM_S_A, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT);
}

LinkTypeCls X11OglFboAtomSA::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void X11OglFboAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11OglSinkDevice>(this);
}

AtomTypeCls X11OglFboAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls X11SwVideoAtomPipe::GetAtomType()
{
	return ATOM11(X11_SW_VIDEO_ATOM_PIPE, PIPE, CENTER, FBO, CENTER, FBO, CENTER, RECEIPT);
}

LinkTypeCls X11SwVideoAtomPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void X11SwVideoAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11SwSinkDevice>(this);
}

AtomTypeCls X11SwVideoAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls X11SwFboAtomSA::GetAtomType()
{
	return ATOM11(X11_SW_FBO_ATOM_S_A, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT);
}

LinkTypeCls X11SwFboAtomSA::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void X11SwFboAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11SwSinkDevice>(this);
}

AtomTypeCls X11SwFboAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSDL2 && defined flagOGL
AtomTypeCls SdlFboAtomSA::GetAtomType()
{
	return ATOM11(SDL_FBO_ATOM_S_A, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT);
}

LinkTypeCls SdlFboAtomSA::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void SdlFboAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2OglVideoSinkDevice>(this);
}

AtomTypeCls SdlFboAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSDL2 && defined flagOGL
AtomTypeCls SdlFboPipe::GetAtomType()
{
	return ATOM11(SDL_FBO_PIPE, PIPE, OGL, FBO, OGL, FBO, OGL, RECEIPT);
}

LinkTypeCls SdlFboPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void SdlFboPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2OglVideoSinkDevice>(this);
}

AtomTypeCls SdlFboPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSDL2 && defined flagOGL
AtomTypeCls SdlFboAtom::GetAtomType()
{
	return ATOM11_U44(SDL_FBO_ATOM, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO, OGL, RECEIPT, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO);
}

LinkTypeCls SdlFboAtom::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void SdlFboAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2OglVideoSinkDevice>(this);
}

AtomTypeCls SdlFboAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagSDL2
AtomTypeCls SdlVideoAtomPipe::GetAtomType()
{
	return ATOM11(SDL_VIDEO_ATOM_PIPE, PIPE, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT);
}

LinkTypeCls SdlVideoAtomPipe::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void SdlVideoAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2CenterVideoSinkDevice>(this);
}

AtomTypeCls SdlVideoAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN && defined flagSDL2
AtomTypeCls SdlVideoAtom::GetAtomType()
{
	return ATOM11_U44(SDL_VIDEO_ATOM, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO);
}

LinkTypeCls SdlVideoAtom::GetLinkType()
{
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void SdlVideoAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2CenterVideoSinkDevice>(this);
}

AtomTypeCls SdlVideoAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSDL2
AtomTypeCls SdlAudioAtom::GetAtomType()
{
	return ATOM11(SDL_AUDIO_ATOM, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

LinkTypeCls SdlAudioAtom::GetLinkType()
{
	return LINKTYPE(EXTERNAL_PIPE, PROCESS);
}

void SdlAudioAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2AudioSinkDevice>(this);
}

AtomTypeCls SdlAudioAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagOGL && defined flagSDL2
AtomTypeCls SdlOglShaderAtom::GetAtomType()
{
	return ATOM11_U44(SDL_OGL_SHADER_ATOM, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO, OGL, RECEIPT, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO);
}

LinkTypeCls SdlOglShaderAtom::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void SdlOglShaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SdlOglShaderBase>(this);
}

AtomTypeCls SdlOglShaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagOGL && defined flagSDL2
AtomTypeCls SdlOglShaderAtomSA::GetAtomType()
{
	return ATOM11(SDL_OGL_SHADER_ATOM_S_A, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT);
}

LinkTypeCls SdlOglShaderAtomSA::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void SdlOglShaderAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SdlOglShaderBase>(this);
}

AtomTypeCls SdlOglShaderAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
}

}

