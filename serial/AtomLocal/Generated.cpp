#include "AtomLocal.h"

namespace TS {

namespace Serial {

AtomTypeCls CenterCustomer::GetAtomType()
{
	return ATOM11(CENTER_CUSTOMER, CUSTOMER, CENTER, ORDER, CENTER, RECEIPT, CENTER, ORDER);
}

void CenterCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<CenterCustomer>>(this);
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

void TestRealtimeSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<TestRealtimeSrc>>(this);
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

void TestRealtimeSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<TestRealtimeSink>>(this);
	vis.VisitThis<VoidSinkBase>(this);
}

AtomTypeCls TestRealtimeSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioHardwareSink::GetAtomType()
{
	return ATOM11(AUDIO_HARDWARE_SINK, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

void AudioHardwareSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioHardwareSink>>(this);
	vis.VisitThis<PortaudioSink>(this);
}

AtomTypeCls AudioHardwareSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioDecoderSrc::GetAtomType()
{
	return ATOM11(AUDIO_DECODER_SRC, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO);
}

void AudioDecoderSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioDecoderSrc>>(this);
	vis.VisitThis<FfmpegAtomBase>(this);
}

AtomTypeCls AudioDecoderSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioDbgSrc::GetAtomType()
{
	return ATOM11(AUDIO_DBG_SRC, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO);
}

void AudioDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioDbgSrc>>(this);
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

void AudioSplitter::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioSplitter>>(this);
	vis.VisitThis<SplitterBase>(this);
}

AtomTypeCls AudioSplitter::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioJoiner::GetAtomType()
{
	return ATOM21(AUDIO_JOINER, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO, CENTER, AUDIO);
}

void AudioJoiner::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioJoiner>>(this);
	vis.VisitThis<JoinerBase>(this);
}

AtomTypeCls AudioJoiner::GetType() const
{
	return GetAtomType();
}

#if defined flagGUI
AtomTypeCls VideoDbgSrc::GetAtomType()
{
	return ATOM11(VIDEO_DBG_SRC, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO);
}

void VideoDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<VideoDbgSrc>>(this);
	vis.VisitThis<VideoGenBase>(this);
}

AtomTypeCls VideoDbgSrc::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls OglCustomer::GetAtomType()
{
	return ATOM11(OGL_CUSTOMER, CUSTOMER, OGL, ORDER, OGL, RECEIPT, OGL, ORDER);
}

void OglCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<OglCustomer>>(this);
	vis.VisitThis<CustomerBase>(this);
}

AtomTypeCls OglCustomer::GetType() const
{
	return GetAtomType();
}

#endif
AtomTypeCls SdlContextAtom::GetAtomType()
{
	return ATOM11(SDL_CONTEXT_ATOM, DRIVER, CENTER, RECEIPT, CENTER, RECEIPT, CENTER, RECEIPT);
}

void SdlContextAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlContextAtom>>(this);
	vis.VisitThis<SDL2ContextBase>(this);
}

AtomTypeCls SdlContextAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlEventAtomPipe::GetAtomType()
{
	return ATOM11(SDL_EVENT_ATOM_PIPE, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT);
}

void SdlEventAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlEventAtomPipe>>(this);
	vis.VisitThis<SDL2EventsBase>(this);
}

AtomTypeCls SdlEventAtomPipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls EventStatePipe::GetAtomType()
{
	return ATOM11(EVENT_STATE_PIPE, DRIVER_PIPE, CENTER, EVENT, CENTER, EVENT, CENTER, RECEIPT);
}

void EventStatePipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<EventStatePipe>>(this);
	vis.VisitThis<EventStateBase>(this);
}

AtomTypeCls EventStatePipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlEventAtom::GetAtomType()
{
	return ATOM12(SDL_EVENT_ATOM, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT, CENTER, EVENT);
}

void SdlEventAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlEventAtom>>(this);
	vis.VisitThis<SDL2EventsBase>(this);
}

AtomTypeCls SdlEventAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls EventState::GetAtomType()
{
	return ATOM21(EVENT_STATE, DRIVER_PIPE, CENTER, EVENT, CENTER, EVENT, CENTER, EVENT, CENTER, RECEIPT);
}

void EventState::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<EventState>>(this);
	vis.VisitThis<EventStateBase>(this);
}

AtomTypeCls EventState::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestEventSrcPipe::GetAtomType()
{
	return ATOM11(TEST_EVENT_SRC_PIPE, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT);
}

void TestEventSrcPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<TestEventSrcPipe>>(this);
	vis.VisitThis<TestEventSrcBase>(this);
}

AtomTypeCls TestEventSrcPipe::GetType() const
{
	return GetAtomType();
}

#if defined flagGUI
AtomTypeCls SdlFboAtomSA::GetAtomType()
{
	return ATOM11(SDL_FBO_ATOM_S_A, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT);
}

void SdlFboAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlFboAtomSA>>(this);
	vis.VisitThis<SDL2ScreenBase>(this);
}

AtomTypeCls SdlFboAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls SdlFboAtom::GetAtomType()
{
	return ATOM11(SDL_FBO_ATOM, PIPE, OGL, FBO, OGL, FBO, OGL, RECEIPT);
}

void SdlFboAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlFboAtom>>(this);
	vis.VisitThis<SDL2ScreenBase>(this);
}

AtomTypeCls SdlFboAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls SdlFboPipe::GetAtomType()
{
	return ATOM21(SDL_FBO_PIPE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT);
}

void SdlFboPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlFboPipe>>(this);
	vis.VisitThis<SDL2ScreenBase>(this);
}

AtomTypeCls SdlFboPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls SdlVideoAtom::GetAtomType()
{
	return ATOM11(SDL_VIDEO_ATOM, PIPE, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT);
}

void SdlVideoAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlVideoAtom>>(this);
	vis.VisitThis<SDL2SwScreenBase>(this);
}

AtomTypeCls SdlVideoAtom::GetType() const
{
	return GetAtomType();
}

#endif
AtomTypeCls SdlAudioAtom::GetAtomType()
{
	return ATOM11(SDL_AUDIO_ATOM, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

void SdlAudioAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlAudioAtom>>(this);
	vis.VisitThis<SDL2AudioOutputBase>(this);
}

AtomTypeCls SdlAudioAtom::GetType() const
{
	return GetAtomType();
}

#if defined flagGUI
AtomTypeCls OglShaderSource::GetAtomType()
{
	return ATOM11(OGL_SHADER_SOURCE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

void OglShaderSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<OglShaderSource>>(this);
	vis.VisitThis<OglShaderBase>(this);
}

AtomTypeCls OglShaderSource::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls OglShaderPipe::GetAtomType()
{
	return ATOM55(OGL_SHADER_PIPE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT, OGL, FBO);
}

void OglShaderPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<OglShaderPipe>>(this);
	vis.VisitThis<OglShaderBase>(this);
}

AtomTypeCls OglShaderPipe::GetType() const
{
	return GetAtomType();
}

#endif
}

}

