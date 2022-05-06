#include "AtomLocal.h"

namespace TS {

namespace Parallel {

#if defined HAVE_OPENCV
AtomTypeCls WebcamPipe::GetAtomType()
{
	return ATOM11(WEBCAM_PIPE, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO);
}

LinkTypeCls WebcamPipe::GetLinkType()
{
	return LINKTYPE(, );
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

LinkTypeCls WebcamAtom::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
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
#if defined flagSCREEN && defined flagFFMPEG
AtomTypeCls AudioLoaderAtom::GetAtomType()
{
	return ATOM11_U01(AUDIO_LOADER_ATOM, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, RECEIPT, CENTER, AUDIO);
}

LinkTypeCls AudioLoaderAtom::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void AudioLoaderAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<FfmpegSourceDevice>(this);
}

AtomTypeCls AudioLoaderAtom::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls EcsEventsAtom::GetAtomType()
{
	return ATOM11(ECS_EVENTS_ATOM, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, RECEIPT);
}

LinkTypeCls EcsEventsAtom::GetLinkType()
{
	return LINKTYPE(, );
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

LinkTypeCls EcsCpuVideoPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
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

LinkTypeCls EcsProgVideo::GetLinkType()
{
	return LINKTYPE(, );
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

LinkTypeCls EcsOglFboPipe::GetLinkType()
{
	return LINKTYPE(, );
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

LinkTypeCls EcsCpuVideo::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
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

LinkTypeCls EcsOglFbo::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
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
AtomTypeCls SdlEventAtom::GetAtomType()
{
	return ATOM12(SDL_EVENT_ATOM, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT, CENTER, EVENT);
}

LinkTypeCls SdlEventAtom::GetLinkType()
{
	return LINKTYPE(, );
}

void SdlEventAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2EventsBase>(this);
}

AtomTypeCls SdlEventAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls EventState::GetAtomType()
{
	return ATOM21(EVENT_STATE, DRIVER_PIPE, CENTER, EVENT, CENTER, EVENT, CENTER, EVENT, CENTER, RECEIPT);
}

LinkTypeCls EventState::GetLinkType()
{
	return LINKTYPE(, );
}

void EventState::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EventStateBase>(this);
}

AtomTypeCls EventState::GetType() const
{
	return GetAtomType();
}

#if defined flagSCREEN
AtomTypeCls SdlFboPipeSide::GetAtomType()
{
	return ATOM21(SDL_FBO_PIPE_SIDE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT);
}

LinkTypeCls SdlFboPipeSide::GetLinkType()
{
	return LINKTYPE(, );
}

void SdlFboPipeSide::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2OglVideoSinkDevice>(this);
}

AtomTypeCls SdlFboPipeSide::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls SdlVideoProgAtom::GetAtomType()
{
	return ATOM11(SDL_VIDEO_PROG_ATOM, PIPE, CENTER, VIDEO, CENTER, PROG, CENTER, RECEIPT);
}

LinkTypeCls SdlVideoProgAtom::GetLinkType()
{
	return LINKTYPE(, );
}

void SdlVideoProgAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2CenterVideoSinkDevice>(this);
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

LinkTypeCls SdlVideoAtomSA::GetLinkType()
{
	return LINKTYPE(, );
}

void SdlVideoAtomSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<Sdl2CenterVideoSinkDevice>(this);
}

AtomTypeCls SdlVideoAtomSA::GetType() const
{
	return GetAtomType();
}

#endif
#if defined flagSCREEN
AtomTypeCls OglAudioSink::GetAtomType()
{
	return ATOM11_U11(OGL_AUDIO_SINK, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT, CENTER, AUDIO);
}

LinkTypeCls OglAudioSink::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
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

LinkTypeCls OglKeyboardSource::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
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

LinkTypeCls OglAudioSource::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
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

LinkTypeCls CpuKeyboardSource::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
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

