#include "EcsLib.h"


NAMESPACE_ECS_BEGIN



ExtComponent::ExtComponent()
{
	//DumpRuntimeDiagnostics(this);
	ValDevCls vd(DevCls::CENTER, ValCls::ORDER);
	SetSinkType(vd);
	SetSourceType(vd);
}

ExtComponent::~ExtComponent() {ASSERT(ext.IsEmpty());}

void ExtComponent::Initialize() {
	// unlinked
	if (this == (void*)0x802160900) {
		LOG("");
	}
	// linked
	if (this == (void*)0x802059300) {
		LOG("");
	}
	
	ASSERT(type.IsValid());
	if (type.sub == SubCompCls::CUSTOMER) {
		customer.Create();
		cfg = &customer->cfg;
		
		ExtSystemRef sys = GetMachine().TryGet<ExtSystem>();
		if (sys)
			sys->Add(AsRef<ExtComponent>());
	}
	
	Format sink_fmt = GetDefaultFormat(type.sink);
	Format src_fmt = GetDefaultFormat(type.src);
	ASSERT(sink_fmt.IsValid() && src_fmt.IsValid());
	
	if (type.sink.val == ValCls::AUDIO)
		sink_buf.Create(this);
	else
		sink.Create(this);
	
	if (type.src.val == ValCls::AUDIO)
		src_buf.Create(this);
	else
		src.Create(this);
	
	/*if (type.sub == SubCompCls::SIDE_OUTPUT) {
		if (type.side.vd.val == ValCls::AUDIO)
			side_src_buf.Create(this);
		else
			side_src.Create(this);
		Format side_src_fmt = GetDefaultFormat(type.side.vd);
		GetSideSourceValue().SetFormat(side_src_fmt);
	}*/
	
	if (type.sub == SubCompCls::SIDE_INPUT) {
		if (type.side.vd.val == ValCls::AUDIO)
			side_sink_buf.Create(this);
		else
			side_sink.Create(this);
		Format side_sink_fmt = GetDefaultFormat(type.side.vd);
		GetSideSinkValue().SetFormat(side_sink_fmt);
	}
	
	GetSinkValue().SetFormat(sink_fmt);
	GetSourceValue().SetFormat(src_fmt);
	
}

void ExtComponent::OnLink(ExchangeSourceProviderRef src, CookieRef src_c, CookieRef ) {
	if (!customer) {
		ExchangeSourceProviderRef src = GetSinkLink();
		ExtComponentRef src_ext = src;
		ASSERT(src_ext);
		cfg = &src_ext->GetConfig();
		ASSERT(cfg);
	}
}

void ExtComponent::Uninitialize() {
	/*sink.Clear();
	sink_buf.Clear();
	src.Clear();
	src_buf.Clear();*/
	side_in_conn.Clear();
	side_out_conn.Clear();
	side_sink.Clear();
	side_sink_buf.Clear();
	
	if (customer) {
		ExtSystemRef sys = GetMachine().TryGet<ExtSystem>();
		if (sys)
			sys->Remove(AsRef<ExtComponent>());
		
		customer.Clear();
	}
	if (ext) {
		ext->Uninitialize();
	}
}

void ExtComponent::SetType(const TypeCompCls& cls) {
	type = cls;
	ValSink::iface = cls.sink;
	ValSource::iface = cls.src;
}

void ExtComponent::UpdateConfig(double dt) {
	ASSERT(customer);
	customer->cfg.Update(dt, GetSourceValue().IsQueueFull());
}

void ExtComponent::AddPlan(Eon::Plan& ep) {
	customer->plans.Add(ep);
}

void ExtComponent::Forward(FwdScope& fwd) {
	packets_forwarded = 0;
	
	if (ext)
		ext->Forward(fwd);
	
	if (type.sub == SubCompCls::CUSTOMER)
		ForwardCustomer(fwd);
	else if (type.sub == SubCompCls::INPUT)
		ForwardInput(fwd);
	else if (type.sub == SubCompCls::OUTPUT)
		ForwardOutput(fwd);
	else if (type.sub == SubCompCls::SIDE_INPUT)
		ForwardSideInput(fwd);
	else if (type.sub == SubCompCls::SIDE_OUTPUT)
		ForwardSideOutput(fwd);
	else
		TODO
}

void ExtComponent::ForwardCustomer(FwdScope& fwd) {
	ASSERT(this->customer);
	CustomerData& c = *this->customer;
	
	int read_i = fwd.GetPos();
	if (read_i == 0) {
		Value& src_value = GetSourceValue();
		
		if (src_value.IsQueueFull()) {
			RTLOG("ExtComponent::ForwardCustomer: customer: skipping order, because queue is full");
			return;
		}
		
		off32 off = c.gen.Create();
		Packet p = CreatePacket(off);
		
		c.unfulfilled_offsets.Add(off.value);
		
		Format fmt = GetSourceValue().GetFormat();
		ASSERT(fmt.IsValid());
		RTLOG("ExtComponent::ForwardCustomer: customer: sending order " << off.ToString() << " in format: " << fmt.ToString());
		p->SetFormat(fmt);
		
		//DUMP(c.plans.GetCount());
		ASSERT(c.plans.GetCount() == 1);
		Eon::Plan& ep = c.plans[0];
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = ep.plan.GetCount()-1;
		
		WhenEnterCreatedEmptyPacket(p);
		WhenLeaveCreatedEmptyPacket();
		
		PacketTracker::Track(TrackerInfo("ExtComponent::ForwardCustomer", __FILE__, __LINE__), *p);
		src_value.GetBuffer().Add(p);
		packets_forwarded++;
	}
	else {
		Value& sink_value = GetValue();
		
		PacketBuffer& buf = sink_value.GetBuffer();
		for (Packet& p : buf) {
			off32 off = p->GetOffset();
			c.unfulfilled_offsets.RemoveKey(off.value);
			RTLOG("ExtComponent::ForwardCustomer: customer: removing fulfilled packet " << off.ToString());
		}
		buf.Clear();
		
		
		/*if (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled) {
			LOG("ExtComponent::Forward: customer: error: too many unfulfilled packets");
			DUMPC(c.unfulfilled_offsets);
			while (c.unfulfilled_offsets.GetCount() > c.max_unfulfilled)
				c.unfulfilled_offsets.Remove(0);
		}*/
	}
}

void ExtComponent::ForwardInput(FwdScope& fwd) {
	
	// From source
	ValSink& iface_sink = *this;
	Value& sink_val = iface_sink.GetValue();
	SimpleBufferedValue* sink_buf_val;
	SimpleValue* sink_sval;
	PacketBuffer* sink_buf;
	if ((sink_buf_val = CastPtr<SimpleBufferedValue>(&sink_val))) {
		sink_buf = &sink_buf_val->GetBuffer();
	}
	else if ((sink_sval = CastPtr<SimpleValue>(&sink_val))) {
		sink_buf = &sink_sval->GetBuffer();
	}
	else TODO
	
	ForwardInputBuffer(fwd, *sink_buf);
}


void ExtComponent::ForwardInputBuffer(FwdScope& fwd, PacketBuffer& sink_buf) {
	
	// To sink
	ValSource& iface_src = *this;
	Value& val = iface_src.GetStream().Get();
	SimpleValue* sval;
	SimpleBufferedValue* sbcal;
	PacketBuffer* pbuf;
	if ((sval = CastPtr<SimpleValue>(&val))) {
		pbuf = &sval->GetBuffer();
	}
	else if ((sbcal = CastPtr<SimpleBufferedValue>(&val))) {
		pbuf = &sbcal->GetBuffer();
	}
	else TODO
	
	RTLOG("ExtComponent::ForwardInput: pre sink=" << sink_buf.GetCount() << ", src=" << val.GetBuffer().GetCount());
	Format fmt = GetSourceValue().GetFormat();
	
	while (sink_buf.GetCount() && !val.IsQueueFull()) {
		if (ext && !ext->IsReady(fmt.vd))
			break;
		Packet in = sink_buf.First();
		sink_buf.RemoveFirst();
		
		//int c = sink_buf.IsEmpty() ? 100 : 1;
		
		//for(int i = 0; i < c && !val.IsQueueFull(); i++) {
		off32 off = in->GetOffset();
		RTLOG("ExtComponent::ForwardInput: play packet " << off.ToString());
		
		Packet to = CreatePacket(off);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		if (ext) {
			WhenEnterStorePacket(*ext, to);
			
			ext->StorePacket(to);
			
			WhenLeaveStorePacket(to);
		}
		else {
			WhenEnterCreatedEmptyPacket(to);
			
			RTLOG("ExtComponent::ForwardInput: sending packet in format: " << fmt.ToString());
			to->SetFormat(fmt);
			
			WhenLeaveCreatedEmptyPacket();
		}
		
		PacketTracker::Track(TrackerInfo("ExtComponent::ForwardInput", __FILE__, __LINE__), *to);
		pbuf->Add(to);
		packets_forwarded++;
		//}
	}
	
	
	/* BREAKS OFFSET CHECKING!
	if (InterfaceSink::iface.val.type == ValCls::ORDER) {
		sink_buf->Clear();
		RTLOG("ExtComponent::ForwardInput: cleared order-sink buffer");
	}*/
	
	{
		int src_total = 0;
		int src_ch_samples = 0;
		for (Packet& p : *pbuf) {
			src_total += p->GetSizeBytes();
			src_ch_samples += p->GetSizeChannelSamples();
		}
		RTLOG("ExtComponent::ForwardInput: post sink=" << sink_buf.GetCount() << ", src=" << val.GetBuffer().GetCount() << " (total " << src_total << " bytes, " << src_ch_samples << " ch-samples)");
	}
	
}

void ExtComponent::ForwardOutput(FwdScope& fwd) {
	POPO(Pol::Ecs::ExtComp::ConsumerFirst);
	POPO(Pol::Ecs::ExtComp::SkipDulicateExtFwd);
	if (fwd.GetPos() > 0) {
		if (this->ext)
			this->ext->Forward(fwd);
	}
	else {
		RTLOG("ExtComponent::ForwardOutput: skip duplicate extension forward");
	}
	
	
	ForwardConsumed(fwd);
}

void ExtComponent::ForwardConsumed(FwdScope& fwd) {
	Value& sink_value = GetSinkValue();
	Value& src_value = GetSourceValue();
	auto& sink_buf = sink_value.GetBuffer();
	auto& src_buf = src_value.GetBuffer();
	Format src_fmt = src_value.GetFormat();
	
	cfg = &fwd.Cfg();
	
	lock.Enter();
	LinkedList<Packet> consumed_packets;
	MemSwap(this->consumed_packets, consumed_packets);
	lock.Leave();
	
	Index<dword> offs;
	for (auto& in : consumed_packets) {
		off32 o = in->GetOffset();
		if (offs.Find(o.value) >= 0) {
			// receipt is already sent
			continue;
		}
		offs.Add(o.value);
		
		RTLOG("ExtComponent::ForwardOutput: sending receipt for packet(" << o.ToString() << ")");
		Packet to = CreatePacket(o);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		if (ext && type.sub != SubCompCls::SIDE_OUTPUT) {
			WhenEnterStorePacket(*ext, to);
			
			ext->StorePacket(to);
			
			if (!to->GetFormat().IsValid()) {DUMP(src_fmt); DUMP(to->GetFormat());}
			ASSERT(to->GetFormat().IsValid());
			
			WhenLeaveStorePacket(to);
		}
		else {
			WhenEnterCreatedEmptyPacket(to);
			
			RTLOG("ExtComponent::ForwardOutput: sending packet in format: " << src_fmt.ToString());
			to->SetFormat(src_fmt);
			
			WhenLeaveCreatedEmptyPacket();
		}
		
		PacketTracker::Track(TrackerInfo("ExtComponent::ForwardOutput", __FILE__, __LINE__), *to);
		src_buf.Add(to);
		packets_forwarded++;
	}
	
}

void ExtComponent::ForwardSideInput(FwdScope& fwd) {
	POPO(Pol::Ecs::ExtComp::ConsumerFirst);
	POPO(Pol::Ecs::ExtComp::SkipDulicateExtFwd);
	if (fwd.GetPos() > 0) {
		if (this->ext)
			this->ext->Forward(fwd);
	}
	else {
		RTLOG("ExtComponent::ForwardSideInput: skip duplicate extension forward");
	}
	
	Value& sink_value = GetSinkValue();
	auto& sink_buf = sink_value.GetBuffer();
	Format sink_fmt = sink_value.GetFormat();
	
	Value& side_sink_value = GetSideSinkValue();
	auto& side_sink_buf = side_sink_value.GetBuffer();
	Format side_sink_fmt = side_sink_value.GetFormat();
	
	Value& src_value = GetSourceValue();
	auto& src_buf = src_value.GetBuffer();
	Format src_fmt = src_value.GetFormat();
	
	while (sink_buf.GetCount() && side_sink_buf.GetCount() && !src_value.IsQueueFull()) {
		Packet side_p = side_sink_buf.First();
		Packet sink_p = sink_buf.First();
		side_sink_buf.RemoveFirst();
		sink_buf.RemoveFirst();
		
		PacketTracker::StopTracking(TrackerInfo("ExtComponent::ForwardSideInput", __FILE__, __LINE__), sink_p);
		off32 off = sink_p->GetOffset();
		sink_p.Clear();
		
		RTLOG("ExtComponent::ForwardSideInput: forwarding side packet in format: " << side_p->GetFormat().ToString());
		
		if (side_p->GetFormat() == src_fmt) {
			side_p->SetOffset(off);
			src_buf.Add(side_p);
		}
		else {
			Packet dst = CreatePacket(off);
			if (Convert(side_p, dst))
				src_buf.Add(dst);
			else {
				RTLOG("ExtComponent::ForwardSideInput: error: packet conversion failed");
			}
		}
	}
}

void ExtComponent::ForwardSideOutput(FwdScope& fwd) {
	POPO(Pol::Ecs::ExtComp::ConsumerFirst);
	POPO(Pol::Ecs::ExtComp::SkipDulicateExtFwd);
	if (fwd.GetPos() > 0) {
		if (this->ext)
			this->ext->Forward(fwd);
	}
	else {
		RTLOG("ExtComponent::ForwardOutput: skip duplicate extension forward");
	}
	
	Value& sink_value = GetSinkValue();
	auto& sink_buf = sink_value.GetBuffer();
	
	
	//LOG(HexStr((void*)this) << " side_in_conn = " << HexStr(side_in_conn.Get()));
	ASSERT(side_in_conn);
	Value& side_sink_value = side_in_conn->GetSideSinkValue();
	auto& side_sink_buf = side_sink_value.GetBuffer();
	Format side_sink_fmt = side_sink_value.GetFormat();
	
	while (sink_buf.GetCount() && !side_sink_value.IsQueueFull()) {
		Packet in = sink_buf.First();
		sink_buf.RemoveFirst();
		
		off32 o = in->GetOffset();
		
		RTLOG("ExtComponent::ForwardSideOutput: sending side-out packet(" << o.ToString() << ")");
		
		consumed_packets.Add(in);
		
		if (in->GetFormat() != side_sink_fmt) {
			Packet dst = CreatePacket(o);
			dst->SetFormat(side_sink_fmt);
			Convert(in, dst);
			in = dst;
		}
		
		side_sink_buf.Add(in);
	}
	
	
	ForwardConsumed(fwd);
}

void ExtComponent::ForwardExchange(FwdScope& fwd) {
	if (!packets_forwarded && GetSourceValue().GetBuffer().IsEmpty()) {
		RTLOG("ExtComponent::ForwardExchange: no packets to forward, exiting FwdScope");
		return;
	}
	int read_i = fwd.GetPos();
	ValSource& src = *this;
	
	ExchangePointRef expt = src.GetExPt();
	ASSERT(expt);
	if (expt) {
		fwd.AddNext(*expt);
	}
	else {
		RTLOG("ExtComponent::ForwardExchange: source has no next exchange point");
	}
}

bool ExtComponent::SetExtension(ComponentExtBase* c) {
	ext.Clear();
	ext = c;
	c->SetParent(this);
	// c->Initialize(); // not here, requires world-state
	return true;
}

void ExtComponent::ClearExtension() {
	if (ext) {
		ext->Uninitialize();
		ext.Clear();
	}
}

ComponentExtBaseRef ExtComponent::GetExtension() {
	return ext ? ext->template AsRef<ComponentExtBase>() : ComponentExtBaseRef();
}


InterfaceSourceRef ExtComponent::GetSource() {
	return InterfaceSourceRef(GetParentUnsafe(), (InterfaceSource*)this);
}

InterfaceSinkRef ExtComponent::GetSink() {
	return InterfaceSinkRef(GetParentUnsafe(), (InterfaceSink*)this);
}

bool ExtComponent::ForwardMem(void* mem, size_t mem_size) {
	Value& sink_value = GetSinkValue();
	Value& src_value = GetSourceValue();
	
	if (consumer.IsEmptySource())
		consumer.SetSource(sink_value.GetBuffer());
	
	if (mem) {
		Format fmt = sink_value.GetFormat();
		
		int size = fmt.GetFrameSize();
		if (size != mem_size) {
			RTLOG("OutputComponent::ForwardMem: error: memsize mismatch (" << size << " != " << mem_size << ")");
			return false;
		}
		
		int qsize = sink_value.GetQueueSize();
		if (qsize > 0 || consumer.HasLeftover()) {
			
			/*off32 begin_offset = buf.GetOffset();
			if (0) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: trying to consume " << begin_offset.ToString());
				RTLOG("BufferedAudioDeviceStream::SinkCallback: dumping");
				buf.Dump();
			}*/
			
			consumer.SetDestination(fmt, mem, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			int csize = consumer.GetLastMemoryBytes();
			int consumed_count = consumer.GetCount();
			if (csize != size) {
				RTLOG("OutputComponent::ForwardMem: error: consumed " << csize << " (expected " << size << "), packets=" << consumed_count);
			}
			else {
				RTLOG("OutputComponent::ForwardMem:  consumed " << csize << ", packets=" << consumed_count);
			}
			
			lock.Enter();
			consumed_packets.Append(consumer.consumed_packets);
			lock.Leave();
			
			
			if (cust_sys && cfg)
				cust_sys->AddOnce(*this, *cfg);
			
			/*off32 end_offset = consumer.GetOffset();
			off32 diff = off32::GetDifference(begin_offset, end_offset);
			if (diff) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed count=" << diff.ToString());
				buf.RemoveFirst(diff.value);
			}
			else if (consumer.HasLeftover()) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed packet partially");
			}
			else if (!consumer.HasLeftover()) {
				RTLOG("error: BufferedAudioDeviceStream::SinkCallback: device error");
			}*/
			return true;
		}
		else {
			#if DEBUG_RT_PIPE
			RTLOG("error: OutputComponent::ForwardMem: got empty data");
			#endif
			
			memset(mem, 0, size);
		}
	}
	return false;
}

bool ExtComponent::LinkSideIn(ComponentBaseRef in) {
	ExtComponentRef ein = in;
	ASSERT(ein);
	ASSERT(!side_in_conn);
	if (!ein)
		return false;
	
	ASSERT(ein->type.sub == SubCompCls::SIDE_INPUT);
	if (ext && ein->ext) {
		if (ext->LinkSideIn(*ein->ext)) {
			side_in_conn = ein;
			LOG(HexStr((void*)this) << " side_in_conn = " << HexStr(&*side_in_conn));
			return true;
		}
		return false;
	}
	
	return true;
}

bool ExtComponent::LinkSideOut(ComponentBaseRef out) {
	ExtComponentRef eout = out;
	ASSERT(eout);
	if (!eout)
		return false;
	
	ASSERT(eout->type.sub == SubCompCls::SIDE_OUTPUT);
	if (ext && eout->ext) {
		if (ext->LinkSideOut(*eout->ext)) {
			side_out_conn = eout;
			LOG(HexStr((void*)this) << " side_out_conn = " << HexStr(&*side_out_conn));
			return true;
		}
		return false;
	}
	
	return true;
}




















bool ExtSystem::Initialize() {
	
	return true;
}

void ExtSystem::Start() {
	
}

void ExtSystem::Update(double dt) {
	LinkedList<Once> cbs;
	lock.Enter();
	MemSwap(cbs, once_cbs);
	lock.Leave();
	
	for (Once& o : cbs) {
		WhenEnterOnceForward(o.fwd);
		
		for (FwdScope scope(o.fwd, *o.cfg); scope; scope++) {
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveOnceForward();
	}
	
	int dbg_i = 0;
	for (ExtComponentRef& c : customers) {
		RTLOG("ExtSystem::Update: customer #" << dbg_i);
		c->UpdateConfig(dt);
		WhenEnterExtComponentForward(&*c);
		
		int dbg_j = 0;
		for (FwdScope scope(*c, c->GetConfig()); scope; scope++) {
			RTLOG("ExtSystem::Update: customer #" << dbg_i << " fwd #" << dbg_j++);
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveExtComponentForward();
		dbg_i++;
	}
	
}

void ExtSystem::Stop() {
	
}

void ExtSystem::Uninitialize() {
	once_cbs.Clear();
	customers.Clear();
	
	WhenUninit()();
}

void ExtSystem::Add(ExtComponentRef p) {
	customers.FindAdd(p);
}

void ExtSystem::Remove(ExtComponentRef p) {
	customers.RemoveKey(p);
}

void ExtSystem::AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg) {
	lock.Enter();
	Once& o = once_cbs.Add();
	o.fwd = &fwd;
	o.cfg = &cfg;
	lock.Leave();
}












TypeCompCls AsTypeCompCls(TypeExtCls e) {
	TypeCompCls c;
	c.sub = e.sub;
	c.side.vd = e.side;
	c.side.type = ExtComponent::GetEcsType();
	c.sink = e.sink;
	c.src  = e.src;
	return c;
}

NAMESPACE_ECS_END
