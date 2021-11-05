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
		
		off32 init_off(&off_gen, 0);
		Packet p = CreatePacket(init_off);
		p->SetFormat(fmt);
		p->seq = -1;
		
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		//PacketTracker::Track(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *p);
		sink_val.GetBuffer().Add(p);
		
		packet_count++;
	}
	
}

bool CustomerBase::ProcessPackets(PacketIO& io) {
	RTLOG("CustomerBase::ProcessPackets");
	
	PacketIO::Sink& sink = io.sink[0];
	PacketIO::Source& src = io.src[0];
	
	ASSERT(sink.p);
	PacketTracker::StopTracking(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *sink.p);
	
	sink.may_remove = true;
	src.from_sink_ch = 0;
	src.p = sink.p;
	src.p->SetFormat(src.val->GetFormat());
	src.p->SetOffset(off_gen.Create());
	
	
	PacketTracker::Track(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *src.p);
	
	return true;
}




JoinerBase::JoinerBase() {
	
}

bool JoinerBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void JoinerBase::Uninitialize() {
	
}

bool JoinerBase::IsReady(PacketIO& io) {
	RTLOG("JoinerBase::IsReady: " << BinStr(io.active_sink_mask));
	// require primary and single side channel
	int src_ch_count = GetSink()->GetSinkCount();
	if (!(io.active_sink_mask & 1))
		return false;
	for(int i = 1; i < src_ch_count; i++)
		if (io.active_sink_mask & (1 << i))
			return true;
	return false;
}

bool JoinerBase::ProcessPackets(PacketIO& io) {
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
	
	RTLOG("JoinerBase::ProcessPackets: forward packet from sink #" << side_sink_ch << " to src #0: " << sink.p->ToString());
	prim_sink.may_remove = true;
	sink.may_remove = true;
	PacketIO::Source& src = io.src[0];
	
	src.from_sink_ch = side_sink_ch;
	src.p = sink.p;
	
	src.p->SetOffset(prim_sink.p->GetOffset());
	
	return true;
}




SplitterBase::SplitterBase() {
	
}

bool SplitterBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void SplitterBase::Uninitialize() {
	
}

bool SplitterBase::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0;
	
	RTLOG("JoinerBase::IsReady: " << (b ? "true " : "false ") << BinStr(io.full_src_mask));
	
	return b;
}

bool SplitterBase::ProcessPackets(PacketIO& io) {
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
				RTLOG("SplitterBase::ProcessPackets: converted packet: " << src.p->ToString());
			}
			else {
				RTLOG("SplitterBase::ProcessPackets: packet conversion failed from " << sink.p->ToString());
				src.p.Clear();
				return false;
			}
		}
	}
	
	return true;
}

#if 0
void SplitterBase::StorePacket(int sink_ch,  int src_ch, const Packet& in, Packet& out) {
	if (src_ch > 0) {
		Format in_fmt = in->GetFormat();
		Format src_fmt = GetSource()->GetSourceValue(src_ch).GetFormat();
		if (in_fmt.IsCopyCompatible(src_fmt)) {
			out = in;
			RTLOG("SplitterBase::StorePacket: active copy-compatible packet: " << out->ToString());
		}
		else {
			out = CreatePacket(in->GetOffset());
			out->SetFormat(src_fmt);
			if (Convert(in, out)) {
				RTLOG("SplitterBase::StorePacket: active converted packet: " << out->ToString());
				out->CopyRouteData(*in);
				out->AddRouteData(sink_ch);
			}
			else {
				RTLOG("SplitterBase::StorePacket: packet conversion failed from " << in->ToString());
				out.Clear();
			}
		}
	}
	else {
		RTLOG("SplitterBase::StorePacket: default reply");
		out = ReplyPacket(src_ch, in);
	}
}

#endif



#ifdef flagGUI

OglShaderBase::OglShaderBase() {
	
}

bool OglShaderBase::Initialize(const Script::WorldState& ws) {
	String shader_path = ws.Get(".filepath");
	if (!buf.LoadFragmentShaderFile(shader_path))
		return false;
	
	// SDL2ScreenBase duplicate
	for(int i = 0; i < 4; i++) {
		String key = ".buf" + IntStr(i);
		String value = ws.Get(key);
		if (value.IsEmpty())
			;
		else if (value == "volume")
			buf.SetInputVolume(i);
		else if (value == "cubemap")
			buf.SetInputCubemap(i);
		else
			TODO
	}
	
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
	
}

bool OglShaderBase::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0;
	RTLOG("OglShaderBase::IsReady: " << (b ? "true" : "false"));
	return b;
}

bool OglShaderBase::ProcessPackets(PacketIO& io) {
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& src = io.src[src_ch];
	src.from_sink_ch = 0;
	src.p = ReplyPacket(src_ch, prim_sink.p);
	
	
	bool succ = true;
	
	
	for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sink[sink_ch];
		Packet& in = sink.p;
		if (!in) {
			ASSERT(!sink.filled);
			continue;
		}
		sink.may_remove = true;
		
		RTLOG("OglShaderBase::ProcessPackets: " << sink_ch << ", " << src_ch << ": " << in->ToString());
		
		
		Format in_fmt = in->GetFormat();
		if (in_fmt.vd == VD(OGL,FBO)) {
			Size3 sz = in_fmt.fbo.GetSize();
			int channels = in_fmt.fbo.GetChannels();
			
			int base = GetSink()->GetSinkCount() > 1 ? 1 : 0;
			if (in->IsData<InternalPacketData>()) {
				succ = buf.LoadOutputLink(sz, sink_ch - base, in->GetData<InternalPacketData>()) && succ;
			}
			else {
				RTLOG("OglShaderBase::ProcessPackets: cannot handle packet: " << in->ToString());
			}
		}
		
		
		if (sink_ch == 0) {
			
			
			//BeginDraw();
			buf.ProcessStage(*last_cfg);
			//CommitDraw();
			
			ASSERT(in->GetFormat().IsValid());
			
			
		}
	}
	
	InterfaceSourceRef src_iface = GetSource();
	int src_count = src_iface->GetSourceCount();
	for (int src_ch = 0; src_ch < src_count; src_ch++) {
		PacketIO::Source& src = io.src[src_ch];
		if (!src.val)
			continue;
		Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
		if (src_fmt.vd == VD(OGL,FBO)) {
			Packet& out = src.p;
			if (!out) {
				src.from_sink_ch = 0;
				out = ReplyPacket(src_ch, prim_sink.p);
			}
			PacketValue& val = *out;
			InternalPacketData& data = val.GetData<InternalPacketData>();
			GetBuffer().StoreOutputLink(data);
			RTLOG("OglShaderBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
		}
	}
	
	return succ;
}















OglTextureBase::OglTextureBase() {
	
}

bool OglTextureBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

bool OglTextureBase::PostInitialize() {
	
	return true;
}

void OglTextureBase::Uninitialize() {
	
}

bool OglTextureBase::NegotiateSinkFormat(int sink_ch, const Format& new_fmt) {
	// accept all valid video formats for now
	if (new_fmt.IsValid() && new_fmt.IsVideo()) {
		ISinkRef sink = GetSink();
		Value& val = sink->GetValue(sink_ch);
		val.SetFormat(new_fmt);
		return true;
	}
	return false;
}

bool OglTextureBase::IsReady(PacketIO& io) {
	return io.full_src_mask == 0 && io.active_sink_mask == 0b11;
}

bool OglTextureBase::ProcessPackets(PacketIO& io) {
	ASSERT(io.src_count == 2 && io.sink_count == 2);
	
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& prim_src = io.src[0];
	PacketIO::Sink& sink = io.sink[1];
	
	ASSERT(prim_sink.p && sink.p);
	prim_sink.may_remove = true;
	sink.may_remove = true;
	prim_src.from_sink_ch = 0;
	prim_src.p = ReplyPacket(0, prim_sink.p);
	
	PacketValue& from = *sink.p;
	
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
		channels	= from_fmt.vid.GetChannels();
	}
	else
		TODO
	
	if (!buf.IsInitialized()) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		buf.is_win_fbo = false;
		buf.fb_size = sz;
		buf.fb_channels = channels;
		buf.fb_sampletype = OglBuffer::SAMPLE_BYTE;
		buf.fb_accel_sampletype = OglBuffer::SAMPLE_FLOAT;
		
		if (loading_cubemap) {
			ASSERT(cubemap.GetCount() == 6);
			if (!buf.InitializeCubemapRGBA(
					Size(sz.cx, sz.cy), channels,
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
			if (!buf.InitializeTextureRGBA(Size(sz.cx, sz.cy), channels, from.GetData()))
				return false;
		}
		else {
			if (!buf.InitializeVolume(sz, channels, from.GetData()))
				return false;
		}
	}
	else {
		buf.ReadTexture(sz, channels, from.GetData());
	}
	
	
	InterfaceSourceRef src_iface = GetSource();
	int src_count = src_iface->GetSourceCount();
	for (int src_ch = 1; src_ch < src_count; src_ch++) {
		PacketIO::Source& src = io.src[src_ch];
		if (!src.val)
			continue;
		Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
		if (src_fmt.vd == VD(OGL,FBO)) {
			Packet& out = src.p;
			if (!out) {
				src.from_sink_ch = 1;
				out = ReplyPacket(src_ch, prim_sink.p);
			}
			PacketValue& val = *out;
			InternalPacketData& data = val.GetData<InternalPacketData>();
			GetBuffer().StoreOutputLink(data);
			RTLOG("OglTextureBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
		}
	}
	
	return true;
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

bool TestEventSrcBase::IsReady(PacketIO& io) {
	return true;
}

bool TestEventSrcBase::ProcessPackets(PacketIO& io) {
	TODO
	#if 0
	RTLOG("TestEventSrcBase::ProcessPackets");
	return true;
	#endif
}

#if 0
void TestEventSrcBase::StorePacket(int sink_ch,  int src_ch, const Packet& in, Packet& out) {
	RTLOG("TestEventSrcBase::StorePacket");
	
	TODO
	
	Format fmt = in->GetFormat();
	ASSERT(fmt.vd.val == ValCls::EVENT);
	if (fmt.vd.val == ValCls::EVENT) {
		CtrlEvent& ev = out->SetData<CtrlEvent>();
		RandomizeEvent(ev);
	}
	
}
#endif










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

bool EventStateBase::IsReady(PacketIO& io) {
	return true;
}

bool EventStateBase::ProcessPackets(PacketIO& io) {
	TODO
	#if 0
	RTLOG("EventStateBase::LoadPacket: sink #" << sink_ch << ": " << in->ToString());
	
	TODO
	#endif
	return true;
}

#if 0
void EventStateBase::ProcessPackets(PacketIO& io) {
	RTLOG("EventStateBase::StorePacket: sink #" << sink_ch << ", src #" << src_ch << ": " << out->ToString());
	
	TODO
	
}
#endif



NAMESPACE_SERIAL_END
