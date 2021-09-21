#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


bool RollingValueBase::AltInitialize(const Script::WorldState& ws) {
	AtomTypeCls type = ((AtomBase*)this)->GetType();
	if (type.iface.src().val == ValCls::AUDIO)
		internal_fmt.SetAudio(DevCls::ACCEL, SoundSample::U8_LE, 2, 44100, 777);
	else if (type.iface.src().val == ValCls::VIDEO)
		internal_fmt.SetVideo(DevCls::ACCEL, LightSampleFD::U8_LE_ABC, 1280, 720, 60, 1);
	else
		TODO;
	
	time = 0;
	return true;
}

void RollingValueBase::AltStorePacket(Packet& p) {
	ASSERT(internal_fmt.IsValid());
	
	RTLOG("RollingValueBase::AltStorePacket: time=" << time << ", fmt=" << internal_fmt.ToString());
	ASSERT_(!p->GetFormat().IsValid(), "Packed shouldn't be initialized before this");
	PacketValue& pv = *p;
	pv.SetFormat(internal_fmt);
	
	Vector<byte>& data = pv.Data();
	data.SetCount(internal_fmt.GetFrameSize());
	for(byte& dst : data)
		dst = rolling_value++;
	
	time += internal_fmt.GetFrameSeconds();
}



bool VoidSinkBase::AltInitialize(const Script::WorldState& ws) {
	flag.Start(1);
	Thread::Start(THISBACK(IntervalSinkProcess0));
	return true;
}

void VoidSinkBase::IntervalSinkProcess() {
	RTLOG("VoidSinkBase::IntervalSinkProcess: starts");
	
	InterfaceSinkRef sink = GetSink();
	Value& sink_value = sink->GetValue();
	Serial::Format fmt = sink_value.GetFormat();
	Serial::AudioFormat& afmt = fmt;
	Vector<byte> data;
	data.SetCount(fmt.GetFrameSize());
	double step_s = fmt.GetFrameSeconds();
	TimeStop ts;
	bool do_log = false;
	#ifdef DEBUG_RT_PIPE
	do_log = true;
	#endif
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
		
		if (do_log) {
			Serial::PacketBuffer& sink_buf = sink_value.GetBuffer();
			int total_bytes = 0;
			int total_ch_samples = 0;
			for(Packet& p : sink_buf) {
				total_bytes += p->GetSizeBytes();
				total_ch_samples += p->GetSizeChannelSamples();
			}
			String s;
			s   << "VoidSinkBase::IntervalSinkProcess: sink has "
				<< sink_buf.GetCount() << " packets, "
				<< total_bytes << " total bytes, "
				<< total_ch_samples << " total ch samples";
			RTLOG(s);
		}
		
		if (!ForwardMem(data.Begin(), data.GetCount())) {
			RTLOG("VoidSinkBase::IntervalSinkProcess: error: could not get consumable data");
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
		}
	}
	RTLOG("VoidSinkBase::IntervalSinkProcess: stops. total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
	if (!fail) {LOG("VoidSinkBase::IntervalSinkProcess: success!");}
	else       {LOG("VoidSinkBase::IntervalSinkProcess: fail :(");}
	
	flag.DecreaseRunning();
}


NAMESPACE_SERIAL_END
