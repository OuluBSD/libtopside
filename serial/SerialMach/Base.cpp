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
	
	bool r = atom->Recv(0, sink.p) && atom->Send(*src.p, 0);
	
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
		
		PacketValue null_in(init_off);
		PacketValue& out = *p;
		atom->ForwardPacket(null_in, out);
		
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

bool DefaultProcessPackets(Link& link, AtomBase& atom, PacketIO& io) {
	const int sink_ch = 0;
	const int src_ch = 0;
	
	PacketIO::Sink& sink = io.sink[sink_ch];
	PacketIO::Source& src = io.src[src_ch];
	ASSERT(sink.p);
	sink.may_remove = true;
	src.from_sink_ch = sink_ch;
	src.p = link.ReplyPacket(sink_ch, sink.p);
	src.p->AddRouteData(src.from_sink_ch);
	
	atom.Finalize(*link.GetConfig());
	
	bool b = atom.Recv(0, sink.p) && atom.Send(*src.p, 0);
	
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
	
	for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sink[sink_ch];
		Packet& in = sink.p;
		if (!in)
			continue;
		sink.may_remove = true;
		
		RTLOG("PipeOptSideLink::ProcessPackets: sink #" << sink_ch << ": " << in->ToString());
		
		b = atom->Recv(sink_ch, in) && b;
		
		if  ((finalize_on_side && sink_ch > 0/*IsDefaultGfxVal<Gfx>(sink.val->GetFormat().vd.val)*/) ||
			(!finalize_on_side && sink_ch == 0))
			do_finalize = true;
	}
	
	if (do_finalize)
		atom->Finalize(*last_cfg);
	
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& src = io.src[src_ch];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	out = ReplyPacket(src_ch, prim_sink.p);
	
	b = atom->Send(*out, 0) && b;
	
	
	InterfaceSourceRef src_iface = this->GetSource();
	int src_count = src_iface->GetSourceCount();
	for (int src_ch = 1; src_ch < src_count; src_ch++) {
		PacketIO::Source& src = io.src[src_ch];
		if (!src.val)
			continue;
		Packet& out = src.p;
		if (!out) {
			src.from_sink_ch = 1;
			out = this->ReplyPacket(src_ch, prim_sink.p);
		}
		b = atom->Send(*out, src_ch) && b;
	}
	
	
	return b;
	/*
	auto& buf = this->buf;
	ASSERT(io.src_count == 2 && io.sink_count == 2);
	
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& prim_src = io.src[0];
	PacketIO::Sink& sink = io.sink[1];
	
	ASSERT(prim_sink.p && sink.p);
	prim_sink.may_remove = true;
	sink.may_remove = true;
	prim_src.from_sink_ch = 0;
	prim_src.p = this->ReplyPacket(0, prim_sink.p);
	
	PacketValue& from = *sink.p;
	const Vector<byte> from_data = from.GetData();
	
	Format from_fmt = from.GetFormat();
	ASSERT(from_fmt.IsVideo() || from_fmt.IsVolume());
	Size3 sz;
	int channels;
	if (from_fmt.IsVideo()) {
		sz			= from_fmt.vid.GetSize();
		channels	= from_fmt.vid.GetChannels();
		
		if (from_fmt.vid.IsCubemap()) {
			if (from.seq == 0) {
				loading_cubemap = true;
				cubemap.Clear();
			}
			
			if (loading_cubemap) {
				if (from.seq == cubemap.GetCount())
					cubemap.Add(sink.p);
				
				if (cubemap.GetCount() < 6)
					return true;
			}
		}
	}
	else if (from_fmt.IsVolume()) {
		sz			= from_fmt.vol.GetSize();
		channels	= from_fmt.vol.GetChannels();
	}
	else
		TODO
	
	if (!buf.IsInitialized()) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		auto& fb = buf.fb;
		fb.is_win_fbo = false;
		fb.size = sz;
		fb.channels = channels;
		fb.sample = GVar::SAMPLE_FLOAT;
		fb.filter = this->filter;
		fb.wrap = this->wrap;
		fb.fps = 0;
		
		if (loading_cubemap) {
			ASSERT(cubemap.GetCount() == 6);
			if (!buf.InitializeCubemap(
					fb.size,
					fb.channels,
					GVar::SAMPLE_U8,
					cubemap[0]->GetData(),
					cubemap[1]->GetData(),
					cubemap[2]->GetData(),
					cubemap[3]->GetData(),
					cubemap[4]->GetData(),
					cubemap[5]->GetData()
				))
				return false;
		}
		else if (sz.cz == 0) {
			if (!buf.InitializeTexture(
				fb.size,
				fb.channels,
				GVar::SAMPLE_U8,
				&*from_data.Begin(),
				from_data.GetCount()))
				return false;
		}
		else {
			if (!buf.InitializeVolume(
				fb.size,
				fb.channels,
				GVar::SAMPLE_U8,
				from_data))
				return false;
		}
	}
	else {
		buf.ReadTexture(
			sz,
			channels,
			GVar::SAMPLE_U8,
			from.GetData());
	}
	
	
	return true;
	*/
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
	
	for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sink[sink_ch];
		Packet& in = sink.p;
		if (!in)
			continue;
		sink.may_remove = true;
		
		RTLOG("PollerLink::ProcessPackets: sink #" << sink_ch << ": " << in->ToString());
		
		b = atom->Recv(sink_ch, in) && b;
		
		if  ((finalize_on_side && sink_ch > 0/*IsDefaultGfxVal<Gfx>(sink.val->GetFormat().vd.val)*/) ||
			(!finalize_on_side && sink_ch == 0))
			do_finalize = true;
	}
	
	if (do_finalize)
		atom->Finalize(*last_cfg);
	
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& src = io.src[src_ch];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	out = ReplyPacket(src_ch, prim_sink.p);
	
	b = atom->Send(*out, 0) && b;
	
	return true;
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







JoinerLink::JoinerLink() {
	
}

bool JoinerLink::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void JoinerLink::Uninitialize() {
	
}

bool JoinerLink::IsReady(PacketIO& io) {
	RTLOG("JoinerLink::IsReady: " << BinStr(io.active_sink_mask));
	
	// require primary and single side channel
	int src_ch_count = GetSink()->GetSinkCount();
	if (!(io.active_sink_mask & 1))
		return false;
	for(int i = 1; i < src_ch_count; i++)
		if (io.active_sink_mask & (1 << i))
			return true;
	return false;
}

bool JoinerLink::ProcessPackets(PacketIO& io) {
	ASSERT(io.active_sink_mask & 0x0001);
	ASSERT(io.nonempty_sinks >= 2);
	ASSERT(io.src_count == 1);
	PacketIO::Sink& prim_sink = io.sink[0];
	
	int side_sink_ch = -1;
	for (int tries = 0; tries < 3; tries++) {
		int sink_ch = scheduler_iter;
		
		scheduler_iter++;
		if (scheduler_iter >= io.sink_count)
			scheduler_iter = 1;
		
		if (io.sink[sink_ch].p) {
			side_sink_ch = sink_ch;
			break;
		}
	}
	
	ASSERT(side_sink_ch >= 0);
	if (side_sink_ch < 0) return false;
	
	PacketIO::Sink& sink = io.sink[side_sink_ch];
	
	RTLOG("JoinerLink::ProcessPackets: forward packet from sink #" << side_sink_ch << " to src #0: " << sink.p->ToString());
	prim_sink.may_remove = true;
	sink.may_remove = true;
	PacketIO::Source& src = io.src[0];
	
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
	bool b = io.full_src_mask == 0;
	
	RTLOG("SplitterLink::IsReady: " << (b ? "true " : "false ") << BinStr(io.full_src_mask));
	
	return b;
}

bool SplitterLink::ProcessPackets(PacketIO& io) {
	ASSERT(io.src_count > 1 && io.sink_count == 1);
	ASSERT(io.active_sink_mask == 0x0001);
	PacketIO::Sink& sink = io.sink[0];
	sink.may_remove = true;
	
	PacketIO::Source& prim_src = io.src[0];
	prim_src.from_sink_ch = 0;
	prim_src.p = ReplyPacket(0, sink.p);
	
	Format in_fmt = sink.p->GetFormat();
	
	InterfaceSourceRef src_iface = GetSource();
	for(int i = 1; i < io.src_count; i++) {
		PacketIO::Source& src = io.src[i];
		Format src_fmt = src_iface->GetSourceValue(i).GetFormat();
		if (src_fmt.IsCopyCompatible(in_fmt)) {
			src.from_sink_ch = 0;
			src.p = sink.p;
		}
		else {
			src.p = CreatePacket(sink.p->GetOffset());
			src.p->SetFormat(src_fmt);
			src.p->CopyRouteData(*sink.p);
			if (Convert(sink.p, src.p)) {
				RTLOG("SplitterLink::ProcessPackets: converted packet: " << src.p->ToString());
			}
			else {
				RTLOG("SplitterLink::ProcessPackets: packet conversion failed from " << sink.p->ToString());
				src.p.Clear();
				return false;
			}
		}
	}
	
	return true;
}

#if 0
void SplitterLink::StorePacket(int sink_ch,  int src_ch, const Packet& in, Packet& out) {
	if (src_ch > 0) {
		Format in_fmt = in->GetFormat();
		Format src_fmt = GetSource()->GetSourceValue(src_ch).GetFormat();
		if (in_fmt.IsCopyCompatible(src_fmt)) {
			out = in;
			RTLOG("SplitterLink::StorePacket: active copy-compatible packet: " << out->ToString());
		}
		else {
			out = CreatePacket(in->GetOffset());
			out->SetFormat(src_fmt);
			if (Convert(in, out)) {
				RTLOG("SplitterLink::StorePacket: active converted packet: " << out->ToString());
				out->CopyRouteData(*in);
				out->AddRouteData(sink_ch);
			}
			else {
				RTLOG("SplitterLink::StorePacket: packet conversion failed from " << in->ToString());
				out.Clear();
			}
		}
	}
	else {
		RTLOG("SplitterLink::StorePacket: default reply");
		out = ReplyPacket(src_ch, in);
	}
}

#endif

LinkTypeCls SplitterLink::GetType() {
	return LINKTYPE(SPLITTER, PROCESS);
}


NAMESPACE_SERIAL_END
