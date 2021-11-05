#include "AtomLocal.h"

#if HAVE_OPENCV

NAMESPACE_SERIAL_BEGIN



OpenCVBase::OpenCVBase() {
	def_cap_sz = Size(1280, 720);
	def_cap_fps = 25;
	
}

bool OpenCVBase::Initialize(const Script::WorldState& ws) {
	devmgr.Refresh();
	
	if (ws.Get(".vflip") == "true")
		vflip = true;
	
	bool succ = false;
	for(int i = 0; i < devmgr.GetNativeCount(); i++) {
		V4L2_Device& dev = devmgr.GetNative(i);
		
		for(int l = 0; l < dev.GetCaptureCount(); l++) {
			OpenCVCaptureDevice& cap = dev.GetCapture(l);
			int fmt_i = -1, res_i = -1;
			
			if (cap.FindClosestFormat(def_cap_sz, def_cap_fps, 0.5, 1.5, fmt_i, res_i)) {
				if (cap.Open(fmt_i, res_i, vflip, fmt)) {
					cap.Start();
					succ = true;
					this->cap = &cap;
					break;
				}
				else {
					last_error = "couldn't open webcam " + cap.GetPath();
				}
			}
			else {
				last_error =
					"couldn't find expected format " + def_cap_sz.ToString() +
					", " + IntStr(def_cap_fps) +
					"fps from webcam "+ cap.GetPath();
			}
		}
	}
		
	if (!succ) {
		if (last_error.IsEmpty())
			last_error = "no available devices";
		
		LOG("OpenCVBase::Initialize: error: " << last_error);
	}
	
	return succ;
}

bool OpenCVBase::PostInitialize() {
	ISourceRef src = GetSource();
	int src_count = src->GetSourceCount();
	for(int i = 0; i < src_count; i++) {
		Value& val = src->GetSourceValue(i);
		Format val_fmt = val.GetFormat();
		if (val_fmt.vd == VD(Center, Video)) {
			if (val_fmt != fmt && !NegotiateSourceFormat(i, fmt))
				return false;
		}
	}
	
	return true;
}

void OpenCVBase::Uninitialize() {
	if (cap) {
		cap->Stop();
		cap = 0;
	}
}

bool OpenCVBase::IsReady(PacketIO& io) {
	bool succ = false;
	if (cap) {
		int frame_i = cap->GetFrameCount();
		if (frame_i > 0 && frame_i > prev_frame_i)
			succ = true;
	}
	
	bool b = succ && io.full_src_mask == 0;
	RTLOG("OpenCVBase::IsReady: " << (b ? "true" : "false"));
	return b;
}

bool OpenCVBase::ProcessPackets(PacketIO& io) {
	if (!cap) return false;
	
	PacketIO::Sink& sink = io.sink[0];
	Packet& in = sink.p;
	ASSERT(in); if (!in) return false;
	sink.may_remove = true;
	
	RTLOG("OpenCVBase::ProcessPackets: sink #0: " << in->ToString());
	
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& prim_src = io.src[0];
	Packet& prim_out = prim_src.p;
	prim_src.from_sink_ch = 0;
	prim_out = ReplyPacket(0, prim_sink.p);
	
	ASSERT(io.src_count >= 2);
	PacketIO::Source& src = io.src[1];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	
	prev_frame_i = cap->GetFrameCount();
	ASSERT(prev_frame_i > 0);
	Packet p = cap->GetPacket();
	ASSERT(p);
	out = ReplyPacket(1, prim_sink.p, p);
	
	return true;
}


NAMESPACE_SERIAL_END

#endif
