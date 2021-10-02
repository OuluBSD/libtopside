#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


bool RollingValueBase::AltInitialize(const Script::WorldState& ws) {
	AtomTypeCls type = ((AtomBase*)this)->GetType();
	ValDevCls main_vd = type.iface.src();
	if (main_vd.dev != DevCls::CENTER) {
		RTLOG("RollingValueBase::AltInitialize: error: invalid device");
		return false;
	}
	if (main_vd.val == ValCls::AUDIO)
		internal_fmt.SetAudio(DevCls::CENTER, SoundSample::U8_LE, 2, 44100, 777);
	else if (main_vd.val == ValCls::VIDEO)
		internal_fmt.SetVideo(DevCls::CENTER, LightSampleFD::U8_LE_ABC, 1280, 720, 60, 1);
	else
		TODO;
	
	time = 0;
	return true;
}

void RollingValueBase::AltStorePacket(int sink_ch,  int src_ch, Packet& p) {
	ASSERT(internal_fmt.IsValid());
	
	RTLOG("RollingValueBase::AltStorePacket: time=" << time << ", fmt=" << internal_fmt.ToString());
	PacketValue& pv = *p;
	pv.SetFormat(internal_fmt);
	
	if (internal_fmt.IsAudio()) {
		int sz = internal_fmt.GetFrameSize();
		Vector<byte>& data = pv.Data();
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
	}
}



bool VoidSinkBase::AltInitialize(const Script::WorldState& ws) {
	flag.Start(1);
	GetSink()->GetValue(0).SetMinQueueSize(5);
	Thread::Start(THISBACK(IntervalSinkProcess));
	return true;
}

void VoidSinkBase::AltUninitialize() {
	flag.Stop();
}

void VoidSinkBase::IntervalSinkProcess() {
	RTLOG("VoidSinkBase::IntervalSinkProcess: starts");
	
	const int sink_ch_i = 0;
	
	InterfaceSinkRef sink = GetSink();
	Value& sink_value = sink->GetValue(sink_ch_i);
	Serial::Format fmt = sink_value.GetFormat();
	Serial::AudioFormat& afmt = fmt;
	
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
		
		RTLOG("VoidSinkBase::IntervalSinkProcess: trying to consume " << data.GetCount());
		
		if (!ForwardAsyncMem(data.Begin(), data.GetCount())) {
			LOG("VoidSinkBase::IntervalSinkProcess: error: could not get consumable data");
			fail = true;
			break;
		}
		
		// Verify data
		if (afmt.type == TS::Serial::BinarySample::FLT_LE) {
			float* it = (float*)(void*)data.begin();
			float* end = (float*)(void*)data.end();
			int dbg_i = 0;
			int dbg_count = end - it;
			for (; it != end; ++it, ++dbg_i) {
				float f0 = *it;
				float f1 = rolling_value++ / 255.0 * 2.0 - 1.0;
				ASSERT(IsClose(f0, f1));
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
			
			LOG("VoidSinkBase::IntervalSinkProcess: successfully verified frame");
		}
		else {
			LOG("VoidSinkBase::IntervalSinkProcess: error: invalid audio format");
		}
	}
	RTLOG("VoidSinkBase::IntervalSinkProcess: stops. total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
	if (!fail) {LOG("VoidSinkBase::IntervalSinkProcess: success!");}
	else       {LOG("VoidSinkBase::IntervalSinkProcess: fail :(");}
	
	flag.DecreaseRunning();
}


NAMESPACE_SERIAL_END
