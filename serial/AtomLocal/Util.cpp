#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


bool CustomerBase::Initialize(const Script::WorldState& ws) {
	RTLOG("CustomerBase::Initialize");
	
	AtomTypeCls type = GetType();
	
	//if (type.iface.content.val == ValCls::AUDIO)
	//	packet_thrds = 10;
	
	AtomBase::packets_forwarded = 0;
	customer.Create();
	AtomBaseRef r = AtomBase::AsRefT();
	ASSERT(r);
	AtomSystemRef as = AtomBase::GetMachine().template Get<AtomSystem>();
	as->AddCustomer(r);
	
	return true;
}

bool CustomerBase::PostInitialize() {
	packet_thrds = GetSink()->GetValue(0).GetMinPackets();
	
	return true;
}

void CustomerBase::Uninitialize() {
	AtomBaseRef r = AtomBase::AsRefT();
	ASSERT(r);
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveCustomer(r);
}

void CustomerBase::UpdateConfig(double dt) {
	ASSERT(customer);
	DefaultInterfaceSourceRef src = this->GetSource();
	ASSERT(src);
	if (src) {
		int count = src->GetSourceCount();
		for(int i = 0; i < count; i++) {
			Value& val = src->GetSourceValue(i);
			customer->cfg.Update(dt, val.IsQueueFull());
		}
	}
}

void CustomerBase::Forward(FwdScope& fwd) {
	//RTLOG("CustomerBase::Forward");
	
	while (packet_count < packet_thrds) {
		RTLOG("CustomerBase::Forward: create packet");
		InterfaceSinkRef sink_iface = GetSink();
		
		int sink_count = sink_iface->GetSinkCount();
		ASSERT(sink_count == 1);
		
		Value&			sink_val = sink_iface->GetValue(0);
		PacketBuffer&	sink_buf = sink_val.GetBuffer();
		Format			fmt = sink_val.GetFormat();
		
		Packet p = CreatePacket(off_gen);
		p->SetFormat(fmt);
		p->seq = -1;
		
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		WhenEnterCreatedEmptyPacket(p);
		WhenLeaveCreatedEmptyPacket();
		
		//PacketTracker::Track(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *p);
		sink_val.GetBuffer().Add(p);
		
		packet_count++;
	}
	
}

bool CustomerBase::LoadPacket(int ch_i, const Packet& p) {
	RTLOG("CustomerBase::LoadPacket");
	
	//if (p->seq >= 0) {
	PacketTracker::StopTracking(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *p);
	//}
	return ch_i == 0;
}

void CustomerBase::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("CustomerBase::StorePacket");
	
	p->SetOffset(off_gen.Create());
	PacketTracker::Track(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *p);
	
}



JoinerBase::JoinerBase() {
	
}

bool JoinerBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void JoinerBase::Uninitialize() {
	
}

void JoinerBase::Forward(FwdScope& fwd) {
	RTLOG("JoinerBase::Forward");
	cur_side.Clear();
}

bool JoinerBase::LoadPacket(int ch_i, const Packet& p) {
	if (ch_i == 1) {
		RTLOG("JoinerBase::LoadPacket: active ch-1 packet" << p->ToString());
		cur_side = p;
	}
	else {
		RTLOG("JoinerBase::LoadPacket: skipping ch-" << ch_i << " packet");
	}
	return true;
}

void JoinerBase::StorePacket(int sink_ch, int src_ch, Packet& p) {
	if (sink_ch == 0) {
		RTLOG("JoinerBase::StorePacket: (" << sink_ch << "," << src_ch << "): " << p->ToString());
		p = cur_side;
	}
	else {
		RTLOG("JoinerBase::StorePacket: (" << sink_ch << "," << src_ch << "): skipping packet");
		p.Clear();
	}
}



SplitterBase::SplitterBase() {
	
}

bool SplitterBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void SplitterBase::Uninitialize() {
	
}

void SplitterBase::Forward(FwdScope& fwd) {
	cur_side.Clear();
}

bool SplitterBase::LoadPacket(int ch_i, const Packet& p) {
	cur_side.Clear();
	
	Format p_fmt = p->GetFormat();
	Format sink_fmt = GetSink()->GetValue(0).GetFormat();
	if (p_fmt.IsCopyCompatible(sink_fmt)) {
		cur_side = p;
		RTLOG("SplitterBase::LoadPacket: active copy-compatible packet: " << cur_side->ToString());
	}
	else {
		cur_side = CreatePacket(p->GetOffset());
		cur_side->SetFormat(sink_fmt);
		if (Convert(p, cur_side)) {
			RTLOG("SplitterBase::LoadPacket: active converted packet: " << cur_side->ToString());
		}
		else {
			RTLOG("SplitterBase::LoadPacket: packet conversion failed from " << p->ToString());
			cur_side.Clear();
		}
			
	}
	
	return true;
}

void SplitterBase::StorePacket(int sink_ch, int src_ch, Packet& p) {
	if (src_ch > 0) {
		if (cur_side) {
			p = cur_side;
			RTLOG("SplitterBase::StorePacket: forwarded packet (" << sink_ch << ", " << src_ch << "): " << p->ToString());
		}
		else {
			RTLOG("SplitterBase::StorePacket: store packet failed");
		}
	}
	else {
		RTLOG("SplitterBase::StorePacket: skipping src 0");
	}
}


#ifdef flagGUI

OglShaderBase::OglShaderBase() {
	
}

bool OglShaderBase::Initialize(const Script::WorldState& ws) {
	String shader_path = ws.Get(".filepath");
	if (!buf.LoadFragmentShaderFile(shader_path))
		return false;
	
	buf.SetBufferId(ws.Get(".name"));
	
	InterfaceSinkRef sink_iface = GetSink();
	int c = sink_iface->GetSinkCount();
	for(int i = 0; i < c; i++)
		sink_iface->GetValue(i).SetMaxQueueSize(1);
	
	InterfaceSourceRef src_iface = GetSource();
	c = src_iface->GetSourceCount();
	for(int i = 0; i < c; i++)
		src_iface->GetSourceValue(i).SetMaxQueueSize(1);
	
	return true;
}

bool OglShaderBase::PostInitialize() {
	buf.is_win_fbo = false;
	buf.fb_size = Size(1280,720);
	//buf.fb_sampletype = OglBuffer::SAMPLE_FLOAT;
	if (!buf.Initialize())
		return false;
	
	return true;
}

void OglShaderBase::Uninitialize() {
	last_packet.Clear();
}

bool OglShaderBase::LoadPacket(int ch_i, const Packet& p) {
	bool succ = true;
	Format fmt = p->GetFormat();
	if (fmt.IsVideo()) {
		if (p->IsData<InternalPacketData>()) {
			succ = buf.LoadOutputLink(p->GetData<InternalPacketData>());
		}
		else {
			RTLOG("OglShaderBase::LoadPacket: cannot handle packet: " << p->ToString());
		}
	}
	
	if (ch_i == 0)
		last_packet = p;
	
	return succ;
}

bool OglShaderBase::IsReady(ValDevCls vd) {
	return true;
}

void OglShaderBase::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("OglShaderBase::StorePacket: " << sink_ch << ", " << src_ch << ": " << p->ToString());
	
	if (sink_ch == 0 && src_ch == 0) {
		ASSERT(last_packet);
		
		//BeginDraw();
		buf.ProcessStage(*last_cfg);
		//CommitDraw();
		
		last_packet.Clear();
		ASSERT(p->GetFormat().IsValid());
	}
	
	Format fmt = p->GetFormat();
	if (fmt.vd == VD(ACCEL,VIDEO)) {
		PacketValue& val = *p;
		InternalPacketData& data = val.GetData<InternalPacketData>();
		GetBuffer().StoreOutputLink(data);
	}
}

#endif













TestEventSrcBase::TestEventSrcBase() {
	
}

bool TestEventSrcBase::Initialize(const Script::WorldState& ws) {
	RTLOG("TestEventSrcBase::Initialize");
	return true;
}

void TestEventSrcBase::Uninitialize() {
	RTLOG("TestEventSrcBase::Uninitialize");
	
}

bool TestEventSrcBase::IsReady(ValDevCls vd) {
	return true;
}

bool TestEventSrcBase::LoadPacket(int ch_i, const Packet& p) {
	RTLOG("TestEventSrcBase::LoadPacket");
	return true;
}

void TestEventSrcBase::StorePacket(int sink_ch, int src_ch, Packet& p) {
	RTLOG("TestEventSrcBase::StorePacket");
	
	Format fmt = p->GetFormat();
	ASSERT(fmt.vd.val == ValCls::EVENT);
	if (fmt.vd.val == ValCls::EVENT) {
		CtrlEvent& ev = p->SetData<CtrlEvent>();
		RandomizeEvent(ev);
	}
	
}











EventStateBase::EventStateBase() {
	
}

bool EventStateBase::Initialize(const Script::WorldState& ws) {
	RTLOG("EventStateBase::Initialize");
	
	return true;
}

bool EventStateBase::PostInitialize() {
	RTLOG("EventStateBase::PostInitialize");
	
	return true;
}

void EventStateBase::Uninitialize() {
	RTLOG("EventStateBase::Uninitialize");
	
}

bool EventStateBase::IsReady(ValDevCls vd) {
	return true;
}

bool EventStateBase::LoadPacket(int ch_i, const Packet& p) {
	RTLOG("EventStateBase::LoadPacket: sink #" << ch_i << ": " << p->ToString());
	
	TODO
	
	return true;
}

void EventStateBase::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("EventStateBase::StorePacket: sink #" << sink_ch << ", src #" << src_ch << ": " << p->ToString());
	
	TODO
	
}




NAMESPACE_SERIAL_END
