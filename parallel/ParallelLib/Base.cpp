#include "ParallelLib.h"


NAMESPACE_PARALLEL_BEGIN


bool CustomerBase::Initialize(const Script::WorldState& ws) {
	RTLOG("CustomerBase::Initialize");
	
	AtomTypeCls type = GetType();
	
	//if (type.iface.content.val == ValCls::AUDIO)
	//	packet_thrds = 10;
	
	customer.Create();
	
	return true;
}

bool CustomerBase::PostInitialize() {
	packet_thrds = GetSink()->GetValue(0).GetMinPackets();
	
	return true;
}

void CustomerBase::Uninitialize() {
	
}

void CustomerBase::UpdateConfig(double dt) {
	ASSERT(customer);
	DefaultInterfaceSourceRef src = this->GetSource();
	ASSERT(src);
	if (src) {
		int count = src->GetSourceCount();
		bool any_full = false;
		for(int i = 0; i < count; i++) {
			Value& val = src->GetSourceValue(i);
			any_full = any_full || val.IsQueueFull();
		}
		customer->cfg.Update(dt, any_full);
	}
}

bool CustomerBase::ProcessPacket(PacketValue& v) {
	// pass
	return true;
}

bool CustomerBase::IsForwardReady() {
	return packet_count < packet_thrds;
}

void CustomerBase::ForwardPacket(PacketValue& v) {
	InternalPacketData& data = v.template SetData<InternalPacketData>();
	data.pos = 0;
	data.count = 1;
	
	packet_count++;
}












bool RollingValueBase::Initialize(const Script::WorldState& ws) {
	AtomTypeCls type = ((AtomBase*)this)->GetType();
	ValDevCls main_vd = type.iface.src();
	if (main_vd.dev != DevCls::CENTER) {
		RTLOG("RollingValueBase::Initialize: error: invalid device");
		return false;
	}
	if (main_vd.val == ValCls::AUDIO)
		internal_fmt.SetAudio(DevCls::CENTER, SoundSample::U8_LE, 2, 44100, 777);
	else if (main_vd.val == ValCls::VIDEO)
		internal_fmt.SetVideo(DevCls::CENTER, LightSampleFD::U8_LE_ABC, 1280, 720, 60, 1);
	else
		TODO;
	
	int src_ch = FindSourceWithValDev(VD(CENTER,AUDIO));
	if (src_ch < 0)
		return false;
	
	GetSource()->GetSourceValue(src_ch).SetFormat(internal_fmt);
	
	time = 0;
	return true;
}

bool RollingValueBase::ProcessPacket(PacketValue& v) {
	ASSERT(internal_fmt.IsValid());
	
	RTLOG("RollingValueBase::ProcessPacket: time=" << time);
	
	if (internal_fmt.IsAudio()) {
		int sz = internal_fmt.GetFrameSize();
		Vector<byte>& data = v.Data();
		data.SetCount(sz);
		for(byte& dst : data)
			dst = rolling_value++;
		
		time += internal_fmt.GetFrameSeconds();
	}
	else if (internal_fmt.IsVideo()) {
		TODO
	}
	else {
		Panic("invalid internal format");
		return false;
	}
	return true;
}







bool VoidSinkBase::Initialize(const Script::WorldState& ws) {
	//DUMP(ws);
	String dbg_limit_str = ws.Get(".dbg_limit");
	if (!dbg_limit_str.IsEmpty())
		dbg_limit = ScanInt(dbg_limit_str);
	
	return true;
}

bool VoidSinkBase::PostInitialize() {
	InterfaceSinkRef sink = GetSink();
	const int sink_ch_i = sink->GetSinkCount() - 1;
	Value& sink_value = sink->GetValue(sink_ch_i);
	fmt = sink_value.GetFormat();
	
	return true;
}

void VoidSinkBase::Uninitialize() {
	
}

bool VoidSinkBase::ProcessPacket(PacketValue& v) {
	Panic("Not implemented");
	return false;
}

bool VoidSinkBase::Consume(const void* data, int len) {
	
	if (fmt.IsAudio()) {
		AudioFormat& afmt = fmt;
		
		// Verify data
		bool fail = false;
		if (afmt.type == TS::Serial::BinarySample::FLT_LE) {
			float* it = (float*)data;
			float* end = (float*)((byte*)data + len);
			int dbg_i = 0;
			int dbg_count = (int)(end - it);
			for (; it != end; ++it, ++dbg_i) {
				float f0 = *it;
				double f1 = rolling_value++ / 255.0 * 2.0 - 1.0;
				if (!IsClose(f0, f1))
					fail = true;
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
			dbg_iter++;
			
			if (fail || (dbg_limit > 0 && dbg_iter >= dbg_limit)) {
				GetMachine().SetNotRunning();
				LOG("IntervalPipeLink::IntervalSinkProcess: stops. total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
				if (!fail) {LOG("IntervalPipeLink::IntervalSinkProcess: success!");}
				else       {LOG("IntervalPipeLink::IntervalSinkProcess: fail :(");}
			}
			
			RTLOG("IntervalPipeLink::IntervalSinkProcess: successfully verified frame");
		}
		else {
			LOG("IntervalPipeLink::IntervalSinkProcess: error: invalid audio format");
		}
	}
	
	return true;
}


















bool VoidPollerSinkBase::Initialize(const Script::WorldState& ws) {
	RTLOG("VoidPollerSinkBase::Initialize");
	dt = 1.0/60.0;
	GetSink()->GetValue(0).SetMinQueueSize(5);
	AddAtomToUpdateList();
	return true;
}

void VoidPollerSinkBase::Uninitialize() {
	LOG("VoidPollerSinkBase::Uninitialize: " << HexStr(this));
	LOG("VoidPollerSinkBase::Uninitialize: total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
	if (!fail) {LOG("VoidPollerSinkBase::Uninitialize: success!");}
	else       {LOG("VoidPollerSinkBase::Uninitialize: fail :(");}
	RemoveAtomFromUpdateList();
}

bool VoidPollerSinkBase::ProcessPacket(PacketValue& v) {
	TODO
}
/*
void VoidPollerSinkBase::Update(double dt) {
	ts += dt;
	RTLOG("VoidPollerSinkBase::Update: dt=" + DblStr(dt) + ", ts=" << DblStr(ts));
	if (ts >= dt)
		PostContinueForward();
}

bool VoidPollerSinkBase::IsReady(PacketIO& io) {
	bool b = false;
	if (ts >= dt) {
		ts = 0;
		b = true;
	}
	RTLOG("VoidPollerSinkBase::IsReady: " << (b ? "true " : "false ") << BinStr(io.active_sink_mask));
	return b;
}

bool VoidPollerSinkBase::ProcessPackets(PacketIO& io) {
	PacketIO::Sink& prim_sink = io.sink[0];
	Packet& in = prim_sink.p;
	
	uint64 route_desc = in->GetRouteDescriptor();
	
	RTLOG("VoidPollerSinkBase::ProcessPackets: sink #0: " << io.sink[0].p->ToString() << ", descriptor " << HexStr(route_desc));
	
	Parallel::Format fmt = in->GetFormat();
	if (fmt.IsAudio()) {
		Serial::AudioFormat& afmt = fmt;
		
		int i = thrds.Find(route_desc);
		if (i < 0) {
			i = thrds.GetCount();
			thrds.Add(route_desc);
			RTLOG("VoidPollerSinkBase::ProcessPackets: creating new thread for route " + IntStr64(route_desc));
		}
		
		Thread& t = thrds[i];
		const Vector<byte>& data = in->GetData();
		if (data.IsEmpty()) {
			LOG("VoidPollerSinkBase::ProcessPackets: error: thrd #" << i << " empty data");
			fail = true;
		}
		else if (afmt.type == TS::Serial::BinarySample::FLT_LE) {
			float* it = (float*)(void*)data.begin();
			float* end = (float*)(void*)data.end();
			int dbg_i = 0;
			int dbg_count = (int)(end - it);
			for (; it != end; ++it, ++dbg_i) {
				float f0 = *it;
				double f1 = t.rolling_value++ / 255.0 * 2.0 - 1.0;
				ASSERT(IsClose(f0, f1));
				if (!IsClose(f0, f1)) {
					fail = true;
					break;
				}
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
			
			RTLOG("VoidPollerSinkBase::ProcessPackets: thrd #" << i << " successfully verified frame size " << data.GetCount());
		}
		else {
			LOG("VoidPollerSinkBase::ProcessPackets: error: thrd #" << i << " invalid audio format");
			fail = true;
		}
	}
	else {
		RTLOG("VoidPollerSinkBase::ProcessPackets: error: unexpected packet " << in->ToString());
	}
	
	prim_sink.may_remove = true;
	
	PacketIO::Source& prim_src = io.src[0];
	prim_src.from_sink_ch = 0;
	prim_src.p = ReplyPacket(0, in);
	return true;
}
*/


NAMESPACE_PARALLEL_END
