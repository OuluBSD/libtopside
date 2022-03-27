#include "AtomDebug.h"

namespace TS {

namespace Parallel {

AtomTypeCls CenterCustomer::GetAtomType()
{
	return ATOM11(CENTER_CUSTOMER, CUSTOMER, CENTER, ORDER, CENTER, RECEIPT, CENTER, ORDER);
}

LinkTypeCls CenterCustomer::GetLinkType() {
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

LinkTypeCls TestRealtimeSrc::GetLinkType() {
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

LinkTypeCls TestRealtimeSink::GetLinkType() {
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

LinkTypeCls TestPollerSink::GetLinkType() {
	TODO
}

void TestPollerSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<VoidPollerSinkBase>(this);
}

AtomTypeCls TestPollerSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioDbgSrc::GetAtomType()
{
	return ATOM11(AUDIO_DBG_SRC, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, AUDIO);
}

LinkTypeCls AudioDbgSrc::GetLinkType() {
	TODO
}

void AudioDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AudioGenBase>(this);
}

AtomTypeCls AudioDbgSrc::GetType() const
{
	return GetAtomType();
}

}

}
