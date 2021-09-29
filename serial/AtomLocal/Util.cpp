#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


bool CustomerBase::AltInitialize(const Script::WorldState& ws) {
	RTLOG("CustomerBase::AltInitialize");
	
	AtomTypeCls type = GetType();
	
	if (type.iface.content.val == ValCls::AUDIO)
		packet_thrds = 5;
	
	return true;
}

void CustomerBase::AltForward(FwdScope& fwd) {
	//RTLOG("CustomerBase::AltForward");
	
	if (!packet_count) {
		RTLOG("CustomerBase::AltForward: create packet");
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
		
		//PacketTracker::Track(TrackerInfo("CustomerBase::AltForward", __FILE__, __LINE__), *p);
		sink_val.GetBuffer().Add(p);
		
		packet_count++;
	}
	
}

void CustomerBase::LoadPacket(int ch_i, const Packet& p) {
	RTLOG("CustomerBase::LoadPacket");
	
	//if (p->seq >= 0) {
	PacketTracker::StopTracking(TrackerInfo("CustomerBase::AltForward", __FILE__, __LINE__), *p);
	//}
}

void CustomerBase::AltStorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("CustomerBase::AltStorePacket");
	
	p->SetOffset(off_gen.Create());
	PacketTracker::Track(TrackerInfo("CustomerBase::AltForward", __FILE__, __LINE__), *p);
	
}



JoinerBase::JoinerBase() {
	
}

bool JoinerBase::AltInitialize(const Script::WorldState& ws) {
	
	return true;
}

void JoinerBase::AltUninitialize() {
	
}

void JoinerBase::AltForward(FwdScope& fwd) {
	
}



SplitterBase::SplitterBase() {
	
}

bool SplitterBase::AltInitialize(const Script::WorldState& ws) {
	
	return true;
}

void SplitterBase::AltUninitialize() {
	
}

void SplitterBase::AltForward(FwdScope& fwd) {
	
}



#ifdef flagGUI

OglShaderBase::OglShaderBase() {
	
}

bool OglShaderBase::AltInitialize(const Script::WorldState& ws) {
	String shader_path = ws.Get(".filepath");
	if (!buf.LoadFragmentShaderFile(shader_path))
		return false;
	
	buf.SetBufferId(ws.Get(".name"));
	
	return true;
}

bool OglShaderBase::AltPostInitialize() {
	buf.is_win_fbo = false;
	buf.fb_size = Size(1280,720);
	//buf.fb_sampletype = OglBuffer::SAMPLE_FLOAT;
	if (!buf.Initialize())
		return false;
	
	
	return true;
}

void OglShaderBase::AltUninitialize() {
	last_packet.Clear();
}

void OglShaderBase::AltForward(FwdScope& fwd) {
	/*const int sink_ch_i = 0;
	const int src_ch_i = 0;
	
	Value& src_val = this->GetSource()->GetSourceValue(src_ch_i);
	Value& sink_val = this->GetSink()->GetValue(sink_ch_i);
	PacketBuffer& sink_buf = sink_val.GetBuffer();
	
	if (src_val.GetQueueSize() == 0 && sink_buf.GetCount()){
		RTLOG("OglShaderBase::AltForward: render");
		
		Packet p = sink_buf.First();
		sink_buf.RemoveFirst();
		PacketConsumed(p);
		last_packet = p;
	}
	else {
		RTLOG("OglShaderBase::AltForward: wait");
	}*/
}

void OglShaderBase::LoadPacket(int ch_i, const Packet& p) {
	if (ch_i == 0)
		last_packet = p;
}

bool OglShaderBase::AltIsReady(ValDevCls vd) {
	const int src_ch_i = 0;
	
	Value& src_val = this->GetSource()->GetSourceValue(src_ch_i);
	return src_val.GetQueueSize() == 0;
}

void OglShaderBase::AltStorePacket(int sink_ch,  int src_ch, Packet& p) {
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

NAMESPACE_SERIAL_END
