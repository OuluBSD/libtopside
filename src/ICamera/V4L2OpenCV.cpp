#include "ICamera.h"
#include <SerialMach/SerialMach.h>

#if (defined flagOPENCV) && (defined flagLINUX)


NAMESPACE_PARALLEL_BEGIN


struct CamV4L2OpenCV::NativeCamera {
    Array<VideoSourceFormatT<V4L2Media>> fmts;
    String path;
    Packet last_p;
    Image sw_frame;
    uint32 open_pix_fmt;
    Size open_frame_sz;
    TimeStop cur_time;
    RunningFlag flag;
    double time_step;
    int prev_frame_i;
    Vector<byte> values;
    Format fmt;
    String filepath;
    Size3 sz;
    int stride;
    bool vflip;
    V4L2_DeviceManager devmgr;
    OpenCVCaptureDevice* cap;
};



bool CamV4L2OpenCV::Camera_Create(NativeCamera*& dev) {
	dev = new NativeCamera;
	return true;
}

void CamV4L2OpenCV::Camera_Destroy(NativeCamera*& dev) {
	delete dev;
}

void CamV4L2OpenCV::Camera_Visit(NativeCamera& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool CamV4L2OpenCV::Camera_Initialize(NativeCamera& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.cap = 0;
	dev.time_step = 0;
	dev.prev_frame_i = 0;
	dev.sz = Size3(0,0,0);
	dev.stride = 0;
	dev.vflip = 0;
	
	Size def_cap_sz = Size(1280, 720);
	int def_cap_fps = 25;
	
	dev.devmgr.Refresh();
	
	if (ws.Get(".vflip") == "true")
		dev.vflip = true;
	
	String last_error;
	bool succ = false;
	for(int i = 0; i < dev.devmgr.GetNativeCount(); i++) {
		auto& d = dev.devmgr.GetNative(i);
		
		for(int l = 0; l < d.GetCaptureCount(); l++) {
			OpenCVCaptureDevice& cap = d.GetCapture(l);
			int fmt_i = -1, res_i = -1;
			
			if (cap.FindClosestFormat(def_cap_sz, def_cap_fps, 0.5, 1.5, fmt_i, res_i)) {
				if (cap.Open(fmt_i, res_i, dev.vflip, dev.fmt)) {
					cap.Start();
					succ = true;
					dev.cap = &cap;
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
		
		LOG("CamV4L2OpenCV::Camera_Initialize: error: " << last_error);
	}
	
	return succ;
}

bool CamV4L2OpenCV::Camera_PostInitialize(NativeCamera& dev, AtomBase& a) {
	ISourceRef src = a.GetSource();
	int src_count = src->GetSourceCount();
	for(int i = 0; i < src_count; i++) {
		Value& val = src->GetSourceValue(i);
		Format val_fmt = val.GetFormat();
		if (val_fmt.vd == VD(Center, Video)) {
			if (val_fmt != dev.fmt && !a.GetLink()->NegotiateSourceFormat(i, dev.fmt))
				return false;
		}
	}
	
	return true;
}

bool CamV4L2OpenCV::Camera_Start(NativeCamera& dev, AtomBase& a) {
	// pass
	return true;
}

void CamV4L2OpenCV::Camera_Stop(NativeCamera& dev, AtomBase& a) {
	// pass
}

void CamV4L2OpenCV::Camera_Uninitialize(NativeCamera& dev, AtomBase& a) {
	if (dev.cap) {
		dev.cap->Stop();
		dev.cap = 0;
	}
}

bool CamV4L2OpenCV::Camera_Send(NativeCamera& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	if (!dev.cap) return false;
	
	Format fmt = out.GetFormat();
	if (fmt.IsVideo()) {
		dev.prev_frame_i = dev.cap->GetFrameCount();
		ASSERT(dev.prev_frame_i > 0);
		Packet p = dev.cap->GetPacket();
		ASSERT(p);
		//out = a.ReplyPacket(1, dev.prim_sink.p, p);
		out.Pick(*p);
	}
	
	return true;
}

bool CamV4L2OpenCV::Camera_IsReady(NativeCamera& dev, AtomBase& a, PacketIO& io) {
	bool succ = false;
	if (dev.cap) {
		int frame_i = dev.cap->GetFrameCount();
		if (frame_i > 0 && frame_i > dev.prev_frame_i)
			succ = true;
	}
	
	bool b = succ && io.full_src_mask == 0;
	RTLOG("CamV4L2OpenCV::Camera_IsReady: " << (b ? "true" : "false"));
	return b;
}





NAMESPACE_PARALLEL_END
#endif

