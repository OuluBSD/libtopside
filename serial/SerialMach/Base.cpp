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
	LinkBaseRef r = LinkBase::AsRefT();
	ASSERT(r);
	GetMachine().template Get<LinkSystem>()->RemoveCustomer(r);
}

bool CustomerLink::ProcessPackets(PacketIO& io) {
	RTLOG("CustomerLink::ProcessPackets");
	
	PacketIO::Sink& sink = io.sink[0];
	PacketIO::Source& src = io.src[0];
	
	ASSERT(sink.p);
	PacketTracker_StopTracking("CustomerLink::ProcessPackets", __FILE__, __LINE__, *sink.p);
	
	sink.may_remove = true;
	src.from_sink_ch = 0;
	src.p = sink.p;
	src.p->SetFormat(src.val->GetFormat());
	src.p->SetOffset(off_gen.Create());
	
	bool r = atom->ProcessPacket(*src.p);
	
	if (r)
		PacketTracker_Track("CustomerLink::ProcessPackets", __FILE__, __LINE__, *src.p);
	else {
		RTLOG("CustomerLink::ProcessPackets: error: ProcessPacket failed");
	}
	
	return r;
}

LinkTypeCls CustomerLink::GetType() {
	return LINKTYPE(CUSTOMER, CUSTOMER);
}

RTSrcConfig* CustomerLink::GetConfig() {
	return atom->GetConfig();
}

void CustomerLink::Forward(FwdScope& fwd) {
	//RTLOG("CustomerLink::Forward");
	
	while (atom->IsForwardReady()) {
		RTLOG("CustomerLink::Forward: create packet");
		InterfaceSinkRef sink_iface = GetSink();
		
		int sink_count = sink_iface->GetSinkCount();
		ASSERT(sink_count == 1);
		
		Value&			sink_val = sink_iface->GetValue(0);
		PacketBuffer&	sink_buf = sink_val.GetBuffer();
		Format			fmt = sink_val.GetFormat();
		
		off32 init_off(&off_gen, 0);
		Packet p = CreatePacket(init_off);
		p->SetFormat(fmt);
		p->seq = -1;
		
		atom->ForwardPacket(*p);
		
		//PacketTracker::Track(TrackerInfo("CustomerLink::Forward", __FILE__, __LINE__), *p);
		sink_val.GetBuffer().Add(p);
	}
	
}

bool CustomerLink::IsLoopComplete(FwdScope& fwd) {
	return fwd.GetPos() > 0;
}








PipeLink::PipeLink() {
	
}

bool PipeLink::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void PipeLink::Uninitialize() {
	
}

bool PipeLink::ProcessPackets(PacketIO& io) {
	//const auto& internal_fmt = atom->GetInternalFormat();
	
	const int sink_ch = 0;
	const int src_ch = 0;
	
	/*Format internal_fmt = atom->GetSink()->GetValue(sink_ch).GetFormat();
	ASSERT(internal_fmt.IsValid());
	RTLOG("LinkBase::ProcessPackets: fmt=" << internal_fmt.ToString());*/
	
	PacketIO::Sink& sink = io.sink[sink_ch];
	PacketIO::Source& src = io.src[src_ch];
	ASSERT(sink.p);
	sink.may_remove = true;
	src.from_sink_ch = sink_ch;
	src.p = ReplyPacket(sink_ch, sink.p);
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
	
	bool fail = false;
	
	while (flag.IsRunning()) {
		double t = ts.Seconds();
		
		if (t < step_s) {
			Sleep(1);
			continue;
		}
		ts.Reset();
		
		RTLOG("IntervalPipeLink::IntervalSinkProcess: trying to consume " << data.GetCount());
		
		byte* mem = data.Begin();
		int len = data.GetCount();
		if (ForwardAsyncMem(mem, len)) {
			if (atom->Consume(mem, len)) {
				RTLOG("IntervalPipeLink::IntervalSinkProcess: consumed succesfully");
			}
			else {
				LOG("IntervalPipeLink::IntervalSinkProcess: warning: atom failed to consume date");
			}
		}
		else {
			LOG("IntervalPipeLink::IntervalSinkProcess: warning: could not get consumable data");
		}
	}
	
	flag.DecreaseRunning();
}








ExternalPipeLink::ExternalPipeLink() {
	
}

ExternalPipeLink::~ExternalPipeLink() {
	
}

bool ExternalPipeLink::Initialize(const Script::WorldState& ws) {
	GetSink()->GetValue(0).SetMinQueueSize(5);
	
	return true;
}

void ExternalPipeLink::Uninitialize() {
	
}

LinkTypeCls ExternalPipeLink::GetType() {
	return LINKTYPE(EXTERNAL_PIPE, PROCESS);
}







DriverLink::DriverLink() {
	
}

DriverLink::~DriverLink() {
	
}

bool DriverLink::Initialize(const Script::WorldState& ws) {
	DLOG("DriverLink::Initialize");
	return true;
}

void DriverLink::Uninitialize() {
	
}

bool DriverLink::ProcessPackets(PacketIO& io) {
	return true;
}

LinkTypeCls DriverLink::GetType() {
	return LINKTYPE(DRIVER, DRIVER);
}



NAMESPACE_SERIAL_END
