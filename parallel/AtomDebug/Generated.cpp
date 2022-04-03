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
AtomTypeCls SdlVideoAtom::GetAtomType()
{
	return ATOM11_U44(SDL_VIDEO_ATOM, PIPE, CENTER, VIDEO, CENTER, ORDER, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, RECEIPT, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO, CENTER, VIDEO);
}

LinkTypeCls SdlVideoAtom::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
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
}

}

