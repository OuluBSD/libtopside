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
	
	PacketIO::Sink& sink = io.sinks[0];
	PacketIO::Source& src = io.srcs[0];
	
	ASSERT(sink.p);
	PacketTracker_StopTracking("CustomerLink::ProcessPackets", __FILE__, __LINE__, *sink.p);
	
	sink.may_remove = true;
	src.from_sink_ch = 0;
	src.p = sink.p;
	src.p->SetFormat(src.val->GetFormat());
	src.p->SetOffset(off_gen.Create());
	
	bool r = atom->Recv(0, sink.p) && atom->Send(*last_cfg, *src.p, 0);
	
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
		
		PacketValue null_in(init_off);
		PacketValue& out = *p;
		atom->ForwardPacket(null_in, out);
		
		PacketBuffer& buf = sink_val.GetBuffer();
		buf.EnterWrite();
		buf.Add(p);
		buf.LeaveWrite();
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

bool DefaultProcessPackets(Link& link, AtomBase& atom, PacketIO& io) {
	const int sink_ch = 0;
	const int src_ch = 0;
	
	PacketIO::Sink& sink = io.sinks[sink_ch];
	PacketIO::Source& src = io.srcs[src_ch];
	ASSERT(sink.p);
	sink.may_remove = true;
	src.from_sink_ch = sink_ch;
	src.p = link.ReplyPacket(sink_ch, sink.p);
	#if HAVE_PACKETTRACKER
	src.p->AddRouteData(src.from_sink_ch);
	#endif
	
	auto& cfg = *link.GetConfig();
	atom.Finalize(cfg);
	
	bool b = atom.Recv(0, sink.p) && atom.Send(cfg, *src.p, 0);
	
	return b;
}

bool PipeLink::ProcessPackets(PacketIO& io) {
	return DefaultProcessPackets(*this, *atom, io);
}

LinkTypeCls PipeLink::GetType() {
	return LINKTYPE(PIPE, PROCESS);
}











PipeOptSideLink::PipeOptSideLink() {
	
}

bool PipeOptSideLink::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void PipeOptSideLink::Uninitialize() {
	
}

bool PipeOptSideLink::ProcessPackets(PacketIO& io) {
	bool do_finalize = false;
	bool b = true;
	
	for(int sink_ch = io.sinks.GetCount()-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sinks[sink_ch];
		Packet& in = sink.p;
		if (!in)
			continue;
		sink.may_remove = true;
		
		RTLOG("PipeOptSideLink::ProcessPackets: sink #" << sink_ch << ": " << in->ToString());
		
		b = atom->Recv(sink_ch, in) && b;
		
		if  ((finalize_on_side && sink_ch > 0) ||
			(!finalize_on_side && sink_ch == 0))
			do_finalize = true;
	}
	
	if (do_finalize)
		atom->Finalize(*last_cfg);
	
	PacketIO::Sink& prim_sink = io.sinks[0];
	
	InterfaceSourceRef src_iface = this->GetSource();
	int src_count = src_iface->GetSourceCount();
	for (int src_ch = 1; src_ch < src_count; src_ch++) {
		PacketIO::Source& src = io.srcs[src_ch];
		if (!src.val)
			continue;
		Packet& out = src.p;
		if (!out) {
			src.from_sink_ch = 0;
			out = this->ReplyPacket(src_ch, prim_sink.p);
		}
		if (!atom->Send(*last_cfg, *out, src_ch)) {
			// don't update "b" because non-primary channels are allowed to fail sending
			src.p.Clear();
		}
	}
	
	{
		int src_ch = 0;
		PacketIO::Source& src = io.srcs[src_ch];
		Packet& out = src.p;
		src.from_sink_ch = 0;
		out = ReplyPacket(src_ch, prim_sink.p);
		
		b = atom->Send(*last_cfg, *out, 0) && b;
	}
	
	return b;
}

LinkTypeCls PipeOptSideLink::GetType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}











IntervalPipeLink::IntervalPipeLink() {
	
}

IntervalPipeLink::~IntervalPipeLink() {
	ASSERT(!flag.IsRunning());
}

bool IntervalPipeLink::Initialize(const Script::WorldState& ws) {
	flag.Start(1);
	//GetSink()->GetValue(0).SetMinQueueSize(5);
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
	LOG("IntervalPipeLink::IntervalSinkProcess: starts");
	
	const int sink_ch_i = 0;
	
	InterfaceSinkRef sink = GetSink();
	Value& sink_value = sink->GetValue(sink_ch_i);
	Format fmt = sink_value.GetFormat();
	
	bool raw_data = fmt.IsAudio();
	
	Vector<byte> data;
	if (raw_data)
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
		
		if (raw_data) {
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
		else {
			ForwardAsync();
		}
	}
	
	flag.DecreaseRunning();
}









PollerLink::PollerLink() {
	
}

PollerLink::~PollerLink() {
	
}

bool PollerLink::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	
	AddLinkToUpdateList();
	
	return true;
}

void PollerLink::Uninitialize() {
	RemoveLinkFromUpdateList();
}

LinkTypeCls PollerLink::GetType() {
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

bool PollerLink::IsReady(PacketIO& io) {
	return atom->IsReady(io);
}

bool PollerLink::ProcessPackets(PacketIO& io) {
	bool do_finalize = false;
	bool b = true;
	
	for(int sink_ch = io.sinks.GetCount()-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sinks[sink_ch];
		Packet& in = sink.p;
		if (!in)
			continue;
		sink.may_remove = true;
		
		RTLOG("PollerLink::ProcessPackets: sink #" << sink_ch << ": " << in->ToString());
		
		b = atom->Recv(sink_ch, in) && b;
		
		if  ((finalize_on_side && sink_ch > 0) ||
			(!finalize_on_side && sink_ch == 0))
			do_finalize = true;
	}
	
	if (do_finalize)
		atom->Finalize(*last_cfg);
	
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sinks[0];
	PacketIO::Source& src = io.srcs[src_ch];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	out = ReplyPacket(src_ch, prim_sink.p);
	
	b = atom->Send(*last_cfg, *out, 0) && b;
	
	return true;
}










ExternalPipeLink::ExternalPipeLink() {
	
}

ExternalPipeLink::~ExternalPipeLink() {
	
}

bool ExternalPipeLink::Initialize(const Script::WorldState& ws) {
	//GetSink()->GetValue(0).SetMinQueueSize(5);
	
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







MergerLink::MergerLink() {
	
}

bool MergerLink::Initialize(const Script::WorldState& ws) {
	Format fmt = GetSink()->GetValue(1).GetFormat();
	if (fmt.IsAudio()) {
		//GetAtom()->SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	}
	
	return true;
}

bool MergerLink::PostInitialize() {
	return true;
}

void MergerLink::Uninitialize() {
	
}

bool MergerLink::IsReady(PacketIO& io) {
	RTLOG("MergerLink::IsReady: " << BinStr(io.active_sink_mask));
	
	// require primary and single side channel
	//int src_ch_count = GetSink()->GetSinkCount();
	if (!(io.active_sink_mask & 1))
		return false;
	for (Exchange& e : side_src_conn)
		if (!(io.active_sink_mask & (1 << e.local_ch_i)))
			return false;
	return true;
}

bool MergerLink::ProcessPackets(PacketIO& io) {
	bool do_finalize = false;
	bool b = true;
	
	for (Exchange& e : side_src_conn) {
		int sink_ch = e.local_ch_i;
		
		PacketIO::Sink& sink = io.sinks[sink_ch];
		Packet& in = sink.p;
		ASSERT(in);
		sink.may_remove = true;
		
		RTLOG("PipeOptSideLink::ProcessPackets: sink #" << sink_ch << ": " << in->ToString());
		
		b = atom->Recv(sink_ch, in) && b;
	}
	
	ASSERT(io.sinks[0].p);
	b = atom->Recv(0, io.sinks[0].p) && b;
	io.sinks[0].may_remove = true;
	
	atom->Finalize(*last_cfg);
	
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sinks[0];
	PacketIO::Source& src = io.srcs[src_ch];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	out = ReplyPacket(src_ch, prim_sink.p);
	
	InterfaceSourceRef src_iface = this->GetSource();
	int src_count = src_iface->GetSourceCount();
	for (int src_ch = 1; src_ch < src_count; src_ch++) {
		PacketIO::Source& src = io.srcs[src_ch];
		if (!src.val)
			continue;
		Packet& out = src.p;
		if (!out) {
			src.from_sink_ch = 1;
			out = this->ReplyPacket(src_ch, prim_sink.p);
		}
		if (!atom->Send(*last_cfg, *out, src_ch)) {
			// don't update "b" because non-primary channels are allowed to fail sending
			src.p.Clear();
		}
	}
	
	b = atom->Send(*last_cfg, *out, 0) && b;
	
	
	return b;
}

LinkTypeCls MergerLink::GetType() {
	return LINKTYPE(MERGER, PROCESS);
}







JoinerLink::JoinerLink() {
	
}

bool JoinerLink::Initialize(const Script::WorldState& ws) {
	Format fmt = GetSink()->GetValue(1).GetFormat();
	/*if (fmt.IsAudio()) {
		GetAtom()->SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	}*/
	
	return true;
}

bool JoinerLink::PostInitialize() {
	return true;
}

void JoinerLink::Uninitialize() {
	
}

bool JoinerLink::IsReady(PacketIO& io) {
	RTLOG("JoinerLink::IsReady: " << BinStr(io.active_sink_mask));
	
	// require primary and single side channel
	int src_ch_count = GetSink()->GetSinkCount();
	if (src_ch_count == 3) {
		LOG("");
	}
	if (!(io.active_sink_mask & 1))
		return false;
	
	int sink_ch = scheduler_iter;
	for(int i = 1; i < src_ch_count; i++) {
		if (io.active_sink_mask & (1 << sink_ch))
			return true;
		sink_ch = (sink_ch + 1) % src_ch_count;
		if (!sink_ch) sink_ch = 1;
	}
	
	return false;
}

bool JoinerLink::ProcessPackets(PacketIO& io) {
	ASSERT(io.active_sink_mask & 0x0001);
	ASSERT(io.nonempty_sinks >= 2);
	ASSERT(io.srcs.GetCount() == 1);
	PacketIO::Sink& prim_sink = io.sinks[0];
	
	int side_sink_ch = -1;
	for (int tries = 0; tries < 3; tries++) {
		int sink_ch = scheduler_iter;
		
		if (io.sinks[sink_ch].p) {
			side_sink_ch = sink_ch;
			break;
		}
	}
	
	scheduler_iter++;
	if (scheduler_iter >= io.sinks.GetCount())
		scheduler_iter = 1;
	
	ASSERT(side_sink_ch >= 0);
	if (side_sink_ch < 0)
		return false;
	
	PacketIO::Sink& sink = io.sinks[side_sink_ch];
	
	RTLOG("JoinerLink::ProcessPackets: forward packet from sink #" << side_sink_ch << " to src #0: " << sink.p->ToString());
	prim_sink.may_remove = true;
	sink.may_remove = true;
	PacketIO::Source& src = io.srcs[0];
	
	src.from_sink_ch = side_sink_ch;
	src.p = sink.p;
	
	src.p->SetOffset(prim_sink.p->GetOffset());
	
	return true;
}

LinkTypeCls JoinerLink::GetType() {
	return LINKTYPE(JOINER, PROCESS);
}







SplitterLink::SplitterLink() {
	
}

bool SplitterLink::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void SplitterLink::Uninitialize() {
	
}

bool SplitterLink::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0 && (io.active_sink_mask & 0x1);
	
	RTLOG("SplitterLink::IsReady: " << (b ? "true " : "false ") << BinStr(io.full_src_mask));
	
	return b;
}

bool SplitterLink::ProcessPackets(PacketIO& io) {
	ASSERT(io.srcs.GetCount() > 1 && io.sinks.GetCount() == 1);
	ASSERT(io.active_sink_mask == 0x0001);
	int sink_ch = 0;
	PacketIO::Sink& sink = io.sinks[sink_ch];
	sink.may_remove = true;
	
	PacketIO::Source& prim_src = io.srcs[0];
	prim_src.from_sink_ch = sink_ch;
	prim_src.p = ReplyPacket(0, sink.p);
	
	Format in_fmt = sink.p->GetFormat();
	
	InterfaceSourceRef src_iface = GetSource();
	for(int i = 1; i < io.srcs.GetCount(); i++) {
		PacketIO::Source& src = io.srcs[i];
		if (!src.val)
			continue;
		Format src_fmt = src_iface->GetSourceValue(i).GetFormat();
		src.from_sink_ch = sink_ch;
		if (src_fmt.IsCopyCompatible(in_fmt)) {
			src.p = sink.p;
		}
		else {
			src.p = CreatePacket(sink.p->GetOffset());
			src.p->SetFormat(src_fmt);
			#if HAVE_PACKETTRACKER
			src.p->CopyRouteData(*sink.p);
			#endif
			#if HAVE_PACKETTIMING
			src.p->CopyTiming(*sink.p);
			#endif
			if (Convert(sink.p, src.p)) {
				RTLOG("SplitterLink::ProcessPackets: converted packet: " << src.p->ToString());
			}
			else {
				RTLOG("SplitterLink::ProcessPackets: packet conversion failed from " << sink.p->ToString());
				src.p.Clear();
				return false;
			}
		}
		//ASSERT(!src_fmt.IsAudio() || sink.p->GetBeginTime());
		//ASSERT(!src_fmt.IsAudio() || src.p->GetBeginTime());
	}
	
	return true;
}

LinkTypeCls SplitterLink::GetType() {
	return LINKTYPE(SPLITTER, PROCESS);
}


NAMESPACE_SERIAL_END
