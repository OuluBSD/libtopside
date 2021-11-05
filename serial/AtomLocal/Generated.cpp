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

AtomTypeCls TestPollerSink::GetAtomType()
{
	return ATOM11(TEST_POLLER_SINK, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

void TestPollerSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<TestPollerSink>>(this);
	vis.VisitThis<VoidPollerSinkBase>(this);
}

AtomTypeCls TestPollerSink::GetType() const
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

AtomTypeCls AudioSplitterUser::GetAtomType()
{
	return ATOM11_U01(AUDIO_SPLITTER_USER, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT, CENTER, AUDIO);
}

void AudioSplitterUser::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioSplitterUser>>(this);
	vis.VisitThis<SplitterBase>(this);
}

AtomTypeCls AudioSplitterUser::GetType() const
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

AtomTypeCls AudioJoinerUser::GetAtomType()
{
	return ATOM11_U10(AUDIO_JOINER_USER, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO, CENTER, AUDIO);
}

void AudioJoinerUser::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioJoinerUser>>(this);
	vis.VisitThis<JoinerBase>(this);
}

AtomTypeCls AudioJoinerUser::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioJoiner2User::GetAtomType()
{
	return ATOM11_U20(AUDIO_JOINER2_USER, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO, CENTER, AUDIO, CENTER, AUDIO);
}

void AudioJoiner2User::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<AudioJoiner2User>>(this);
	vis.VisitThis<JoinerBase>(this);
}

AtomTypeCls AudioJoiner2User::GetType() const
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
#if defined HAVE_OPENCV
AtomTypeCls WebcamPipe::GetAtomType()
{
	return ATOM11(WEBCAM_PIPE, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO);
}

void WebcamPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<WebcamPipe>>(this);
	vis.VisitThis<OpenCVBase>(this);
}

AtomTypeCls WebcamPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined HAVE_OPENCV
AtomTypeCls WebcamAtom::GetAtomType()
{
	return ATOM11_U01(WEBCAM_ATOM, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, RECEIPT, CENTER, VIDEO);
}

void WebcamAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<WebcamAtom>>(this);
	vis.VisitThis<OpenCVBase>(this);
}

AtomTypeCls WebcamAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls VideoLoaderAtom::GetAtomType()
{
	return ATOM11_U02(VIDEO_LOADER_ATOM, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, RECEIPT, CENTER, VIDEO, CENTER, AUDIO);
}

void VideoLoaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<VideoLoaderAtom>>(this);
	vis.VisitThis<FfmpegAtomBase>(this);
}

AtomTypeCls VideoLoaderAtom::GetType() const
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
AtomTypeCls SdlImageLoader::GetAtomType()
{
	return ATOM11_U01(SDL_IMAGE_LOADER, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, RECEIPT, CENTER, VIDEO);
}

void SdlImageLoader::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlImageLoader>>(this);
	vis.VisitThis<SDL2ImageBase>(this);
}

AtomTypeCls SdlImageLoader::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls VolumeLoaderAtom::GetAtomType()
{
	return ATOM11_U01(VOLUME_LOADER_ATOM, PIPE, CENTER, VOLUME, CENTER, ORDER, CENTER, RECEIPT, CENTER, VOLUME);
}

void VolumeLoaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<VolumeLoaderAtom>>(this);
	vis.VisitThis<VolumeLoaderBase>(this);
}

AtomTypeCls VolumeLoaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
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
AtomTypeCls SdlFboPipe::GetAtomType()
{
	return ATOM11(SDL_FBO_PIPE, PIPE, OGL, FBO, OGL, FBO, OGL, RECEIPT);
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
AtomTypeCls SdlFboPipeSide::GetAtomType()
{
	return ATOM21(SDL_FBO_PIPE_SIDE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT);
}

void SdlFboPipeSide::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<SdlFboPipeSide>>(this);
	vis.VisitThis<SDL2ScreenBase>(this);
}

AtomTypeCls SdlFboPipeSide::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls SdlFboAtom::GetAtomType()
{
	return ATOM11_U44(SDL_FBO_ATOM, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO, OGL, RECEIPT, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO);
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
AtomTypeCls OglShaderPipe::GetAtomType()
{
	return ATOM11(OGL_SHADER_PIPE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
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
#if defined flagGUI
AtomTypeCls OglShaderAtom::GetAtomType()
{
	return ATOM11_U44(OGL_SHADER_ATOM, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO, OGL, RECEIPT, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO);
}

void OglShaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<OglShaderAtom>>(this);
	vis.VisitThis<OglShaderBase>(this);
}

AtomTypeCls OglShaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls OglTextureSource::GetAtomType()
{
	return ATOM11_U11(OGL_TEXTURE_SOURCE, PIPE, OGL, FBO, OGL, ORDER, CENTER, VIDEO, OGL, RECEIPT, OGL, FBO);
}

void OglTextureSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<OglTextureSource>>(this);
	vis.VisitThis<OglTextureBase>(this);
}

AtomTypeCls OglTextureSource::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls OglVolumeSource::GetAtomType()
{
	return ATOM11_U11(OGL_VOLUME_SOURCE, PIPE, OGL, FBO, OGL, ORDER, CENTER, VOLUME, OGL, RECEIPT, OGL, FBO);
}

void OglVolumeSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<OglVolumeSource>>(this);
	vis.VisitThis<OglTextureBase>(this);
}

AtomTypeCls OglVolumeSource::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagGUI
AtomTypeCls OglAudioSink::GetAtomType()
{
	return ATOM11_U11(OGL_AUDIO_SINK, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT, CENTER, AUDIO);
}

void OglAudioSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Atom<OglAudioSink>>(this);
	vis.VisitThis<OglFboReaderBase>(this);
}

AtomTypeCls OglAudioSink::GetType() const
{
	return GetAtomType();
}

#endif
}

}

