#include "AtomLocal.h"

namespace TS {

namespace Parallel {

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
AtomTypeCls SdlOglFboPipeSide::GetAtomType()
{
	return ATOM21(SDL_OGL_FBO_PIPE_SIDE, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO, OGL, RECEIPT);
}

LinkTypeCls SdlOglFboPipeSide::GetLinkType()
{
	return LINKTYPE(, );
}

void SdlOglFboPipeSide::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SdlOglVideoSinkDevice>(this);
}

AtomTypeCls SdlOglFboPipeSide::GetType() const
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

