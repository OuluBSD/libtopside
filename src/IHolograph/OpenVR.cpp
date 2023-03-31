#include "IHolograph.h"

#if defined flagOPENVR

#include <openvr.h>


NAMESPACE_PARALLEL_BEGIN



struct HoloOpenVR::NativeSinkDevice {
	vr::IVRSystem* hmd = 0;
	vr::TrackedDevicePose_t tracked_dev[ vr::k_unMaxTrackedDeviceCount ];
	String driver;
	String display;
	mat4 dev_pose[ vr::k_unMaxTrackedDeviceCount ];
};


bool HoloOpenVR::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void HoloOpenVR::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
}

void HoloOpenVR::SinkDevice_Visit(NativeSinkDevice&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HoloOpenVR::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.sys.verbose = ws.IsTrue(".verbose", false);
	
	if (!dev.sys.Initialise())
		return false;
		
	dev.ts.Reset();
	return true;
}

bool HoloOpenVR::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	
	return true;
}

bool HoloOpenVR::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	
	return true;
}

void HoloOpenVR::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void HoloOpenVR::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	dev.sys.Uninitialise();
}

bool HoloOpenVR::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.sys.ev_sendable);
	if (!dev.sys.ev_sendable)
		return false;
	
	Format fmt = out.GetFormat();
	RTLOG("HoloOpenVR::SinkDevice_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		UPP::CtrlEvent& dst = out.SetData<UPP::CtrlEvent>();
		dst = dev.sys.ev;
		out.seq = dev.sys.seq++;
	}
	
	return true;
}

bool HoloOpenVR::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	return true;
}

void HoloOpenVR::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool HoloOpenVR::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase& a, PacketIO& io) {
	dev.sys.UpdateData();
	return true;
}





NAMESPACE_PARALLEL_END
#endif

