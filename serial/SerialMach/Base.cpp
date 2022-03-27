#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN



CustomerLink::CustomerLink() {
	
}

bool CustomerLink::Initialize(const Script::WorldState& ws) {
	LinkBaseRef r = LinkBase::AsRefT();
	ASSERT(r);
	LinkSystemRef as = GetMachine().template Get<LinkSystem>();
	as->AddCustomer(r);
	
	return true;
}

void CustomerLink::Uninitialize() {
	
}

bool CustomerLink::ProcessPackets(PacketIO& io) {
	TODO
}

LinkTypeCls CustomerLink::GetType() {
	return LINKTYPE(CUSTOMER, CUSTOMER);
}

RTSrcConfig* CustomerLink::GetConfig() {
	return atom->GetConfig();
}





PipeLink::PipeLink() {
	
}

bool PipeLink::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void PipeLink::Uninitialize() {
	
}

bool PipeLink::ProcessPackets(PacketIO& io) {
	const auto& internal_fmt = atom->GetInternalFormat();
	ASSERT(internal_fmt.IsValid());
	
	RTLOG("LinkBase::ProcessPackets: fmt=" << internal_fmt.ToString());
	
	PacketIO::Sink& sink = io.sink[0];
	PacketIO::Source& src = io.src[0];
	ASSERT(sink.p);
	sink.may_remove = true;
	src.from_sink_ch = 0;
	src.p = ReplyPacket(0, sink.p);
	src.p->AddRouteData(src.from_sink_ch);
	
	PacketValue& v = *src.p;
	bool b = atom->ProcessPacket(v);
	
	return b;
}

LinkTypeCls PipeLink::GetType() {
	return LINKTYPE(PIPE, PROCESS);
}








IntervalPipeLink::IntervalPipeLink() {
	
}

IntervalPipeLink::~IntervalPipeLink() {
	ASSERT(!flag.IsRunning());
}

bool IntervalPipeLink::Initialize(const Script::WorldState& ws) {
	flag.Start(1);
	GetSink()->GetValue(0).SetMinQueueSize(5);
	Thread::Start(THISBACK(IntervalSinkProcess));
	
	return true;
}

void IntervalPipeLink::Uninitialize() {
	flag.Stop();
}

LinkTypeCls IntervalPipeLink::GetType() {
	return LINKTYPE(INTERVAL_PIPE, PROCESS);
}

void IntervalPipeLink::IntervalSinkProcess() {
	RTLOG("IntervalPipeLink::IntervalSinkProcess: starts");
	
	const int sink_ch_i = 0;
	
	InterfaceSinkRef sink = GetSink();
	Value& sink_value = sink->GetValue(sink_ch_i);
	Format fmt = sink_value.GetFormat();
	AudioFormat& afmt = fmt;
	
	Vector<byte> data;
	data.SetCount(fmt.GetFrameSize());
	double step_s = fmt.GetFrameSeconds();
	TimeStop ts;
	
	int dbg_total_samples = 0;
	int dbg_total_bytes = 0;
	bool fail = false;
	
	while (flag.IsRunning()) {
		double t = ts.Seconds();
		
		if (t < step_s) {
			Sleep(1);
			continue;
		}
		ts.Reset();
		
		RTLOG("IntervalPipeLink::IntervalSinkProcess: trying to consume " << data.GetCount());
		
		if (!ForwardAsyncMem(data.Begin(), data.GetCount())) {
			LOG("IntervalPipeLink::IntervalSinkProcess: warning: could not get consumable data");
			continue;
		}
	}
	LOG("IntervalPipeLink::IntervalSinkProcess: stops. total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
	if (!fail) {LOG("IntervalPipeLink::IntervalSinkProcess: success!");}
	else       {LOG("IntervalPipeLink::IntervalSinkProcess: fail :(");}
	
	flag.DecreaseRunning();
}



NAMESPACE_SERIAL_END
