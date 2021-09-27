#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


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


NAMESPACE_SERIAL_END
