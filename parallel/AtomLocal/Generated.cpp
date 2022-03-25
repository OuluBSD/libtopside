#include "AtomLocal.h"

namespace TS {

namespace Parallel {

AtomTypeCls TestRealtimeSrc::GetAtomType()
{
	return ATOM11(TEST_REALTIME_SRC, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO);
}

void TestRealtimeSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<RollingValueBase>(this);
}

AtomTypeCls TestRealtimeSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioHardwareSink::GetAtomType()
{
	return ATOM11(AUDIO_HARDWARE_SINK, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

void AudioHardwareSink::Visit(RuntimeVisitor& vis)
{
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
	vis.VisitThis<FfmpegAtomBase>(this);
}

AtomTypeCls AudioDecoderSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioSplitter::GetAtomType()
{
	return ATOM12(AUDIO_SPLITTER, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT, CENTER, AUDIO);
}

void AudioSplitter::Visit(RuntimeVisitor& vis)
{
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
	vis.VisitThis<JoinerBase>(this);
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

void VideoDbgSrc::Visit(RuntimeVisitor& vis)
{
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
	vis.VisitThis<OpenCVBase>(this);
}

AtomTypeCls WebcamAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls AudioLoaderAtom::GetAtomType()
{
	return ATOM11_U01(AUDIO_LOADER_ATOM, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, RECEIPT, CENTER, AUDIO);
}

void AudioLoaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<FfmpegAtomBase>(this);
}

AtomTypeCls AudioLoaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls VideoLoaderAtom::GetAtomType()
{
	return ATOM11_U02(VIDEO_LOADER_ATOM, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, RECEIPT, CENTER, VIDEO, CENTER, AUDIO);
}

void VideoLoaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<FfmpegAtomBase>(this);
}

AtomTypeCls VideoLoaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
AtomTypeCls EventStatePipe::GetAtomType()
{
	return ATOM11(EVENT_STATE_PIPE, DRIVER_PIPE, CENTER, EVENT, CENTER, EVENT, CENTER, RECEIPT);
}

void EventStatePipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EventStateBase>(this);
}

AtomTypeCls EventStatePipe::GetType() const
{
	return GetAtomType();
}

#if defined flagSCREEN
AtomTypeCls EcsEventsAtom::GetAtomType()
{
	return ATOM11(ECS_EVENTS_ATOM, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, RECEIPT);
}

void EcsEventsAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EcsEventsBase>(this);
}

AtomTypeCls EcsEventsAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls EcsCpuVideoPipe::GetAtomType()
{
	return ATOM11(ECS_CPU_VIDEO_PIPE, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO);
}

void EcsCpuVideoPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EcsVideoBase>(this);
}

AtomTypeCls EcsCpuVideoPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls EcsProgVideo::GetAtomType()
{
	return ATOM11(ECS_PROG_VIDEO, PIPE, CENTER, PROG, CENTER, ORDER, CENTER, PROG);
}

void EcsProgVideo::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EcsVideoBase>(this);
}

AtomTypeCls EcsProgVideo::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls EcsOglFboPipe::GetAtomType()
{
	return ATOM11(ECS_OGL_FBO_PIPE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

void EcsOglFboPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EcsVideoBase>(this);
}

AtomTypeCls EcsOglFboPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls EcsCpuVideo::GetAtomType()
{
	return ATOM11_U44(ECS_CPU_VIDEO, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO);
}

void EcsCpuVideo::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EcsVideoBase>(this);
}

AtomTypeCls EcsCpuVideo::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls EcsOglFbo::GetAtomType()
{
	return ATOM11_U44(ECS_OGL_FBO, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO, OGL, RECEIPT, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO);
}

void EcsOglFbo::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EcsVideoBase>(this);
}

AtomTypeCls EcsOglFbo::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglCustomer::GetAtomType()
{
	return ATOM11(OGL_CUSTOMER, CUSTOMER, OGL, ORDER, OGL, RECEIPT, OGL, ORDER);
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
AtomTypeCls SdlContextAtom::GetAtomType()
{
	return ATOM11(SDL_CONTEXT_ATOM, DRIVER, CENTER, RECEIPT, CENTER, RECEIPT, CENTER, RECEIPT);
}

void SdlContextAtom::Visit(RuntimeVisitor& vis)
{
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
	vis.VisitThis<SDL2EventsBase>(this);
}

AtomTypeCls SdlEventAtomPipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlEventAtom::GetAtomType()
{
	return ATOM12(SDL_EVENT_ATOM, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT, CENTER, EVENT);
}

void SdlEventAtom::Visit(RuntimeVisitor& vis)
{
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
	vis.VisitThis<TestEventSrcBase>(this);
}

AtomTypeCls TestEventSrcPipe::GetType() const
{
	return GetAtomType();
}

#if defined flagSCREEN
AtomTypeCls SdlImageLoader::GetAtomType()
{
	return ATOM11_U01(SDL_IMAGE_LOADER, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, RECEIPT, CENTER, VIDEO);
}

void SdlImageLoader::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2ImageBase>(this);
}

AtomTypeCls SdlImageLoader::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls VolumeLoaderAtom::GetAtomType()
{
	return ATOM11_U01(VOLUME_LOADER_ATOM, PIPE, CENTER, VOLUME, CENTER, ORDER, CENTER, RECEIPT, CENTER, VOLUME);
}

void VolumeLoaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VolumeLoaderBase>(this);
}

AtomTypeCls VolumeLoaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlFboAtomSA::GetAtomType()
{
	return ATOM11(SDL_FBO_ATOM_S_A, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT);
}

void SdlFboAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2OglScreenBase>(this);
}

AtomTypeCls SdlFboAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlFboPipe::GetAtomType()
{
	return ATOM11(SDL_FBO_PIPE, PIPE, OGL, FBO, OGL, FBO, OGL, RECEIPT);
}

void SdlFboPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2OglScreenBase>(this);
}

AtomTypeCls SdlFboPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlFboPipeSide::GetAtomType()
{
	return ATOM21(SDL_FBO_PIPE_SIDE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT);
}

void SdlFboPipeSide::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2OglScreenBase>(this);
}

AtomTypeCls SdlFboPipeSide::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlFboAtom::GetAtomType()
{
	return ATOM11_U44(SDL_FBO_ATOM, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO, OGL, RECEIPT, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO);
}

void SdlFboAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2OglScreenBase>(this);
}

AtomTypeCls SdlFboAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlVideoAtomPipe::GetAtomType()
{
	return ATOM11(SDL_VIDEO_ATOM_PIPE, PIPE, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT);
}

void SdlVideoAtomPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2CpuScreenBase>(this);
}

AtomTypeCls SdlVideoAtomPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlVideoProgAtom::GetAtomType()
{
	return ATOM11(SDL_VIDEO_PROG_ATOM, PIPE, CENTER, VIDEO, CENTER, PROG, CENTER, RECEIPT);
}

void SdlVideoProgAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2CpuScreenBase>(this);
}

AtomTypeCls SdlVideoProgAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlVideoAtomSA::GetAtomType()
{
	return ATOM11(SDL_VIDEO_ATOM_S_A, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, RECEIPT);
}

void SdlVideoAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2CpuScreenBase>(this);
}

AtomTypeCls SdlVideoAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlVideoAtom::GetAtomType()
{
	return ATOM11_U44(SDL_VIDEO_ATOM, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO);
}

void SdlVideoAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SDL2CpuScreenBase>(this);
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
	vis.VisitThis<SDL2AudioOutputBase>(this);
}

AtomTypeCls SdlAudioAtom::GetType() const
{
	return GetAtomType();
}

#if defined flagSCREEN
AtomTypeCls OglShaderPipe::GetAtomType()
{
	return ATOM11(OGL_SHADER_PIPE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

void OglShaderPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglShaderBase>(this);
}

AtomTypeCls OglShaderPipe::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglShaderAtom::GetAtomType()
{
	return ATOM11_U44(OGL_SHADER_ATOM, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO, OGL, RECEIPT, OGL, FBO, OGL, FBO, OGL, FBO, OGL, FBO);
}

void OglShaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglShaderBase>(this);
}

AtomTypeCls OglShaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglShaderAtomSA::GetAtomType()
{
	return ATOM11(OGL_SHADER_ATOM_S_A, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT);
}

void OglShaderAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglShaderBase>(this);
}

AtomTypeCls OglShaderAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglTextureSource::GetAtomType()
{
	return ATOM11_U11(OGL_TEXTURE_SOURCE, PIPE, OGL, FBO, OGL, ORDER, CENTER, VIDEO, OGL, RECEIPT, OGL, FBO);
}

void OglTextureSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglTextureBase>(this);
}

AtomTypeCls OglTextureSource::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglVolumeSource::GetAtomType()
{
	return ATOM11_U11(OGL_VOLUME_SOURCE, PIPE, OGL, FBO, OGL, ORDER, CENTER, VOLUME, OGL, RECEIPT, OGL, FBO);
}

void OglVolumeSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglTextureBase>(this);
}

AtomTypeCls OglVolumeSource::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglAudioSink::GetAtomType()
{
	return ATOM11_U11(OGL_AUDIO_SINK, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT, CENTER, AUDIO);
}

void OglAudioSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglFboReaderBase>(this);
}

AtomTypeCls OglAudioSink::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglKeyboardSource::GetAtomType()
{
	return ATOM11_U01(OGL_KEYBOARD_SOURCE, PIPE, OGL, FBO, OGL, ORDER, OGL, RECEIPT, OGL, FBO);
}

void OglKeyboardSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglKeyboardBase>(this);
}

AtomTypeCls OglKeyboardSource::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglAudioSource::GetAtomType()
{
	return ATOM11_U11(OGL_AUDIO_SOURCE, PIPE, OGL, FBO, OGL, ORDER, CENTER, AUDIO, OGL, RECEIPT, OGL, FBO);
}

void OglAudioSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OglAudioBase>(this);
}

AtomTypeCls OglAudioSource::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls CpuKeyboardSource::GetAtomType()
{
	return ATOM11_U01(CPU_KEYBOARD_SOURCE, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, RECEIPT, CENTER, VIDEO);
}

void CpuKeyboardSource::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CpuKeyboardBase>(this);
}

AtomTypeCls CpuKeyboardSource::GetType() const
{
	return GetAtomType();
}

#endif
}

}

