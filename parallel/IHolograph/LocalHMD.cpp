#include "IHolograph.h"

#if defined flagLOCALHMD
NAMESPACE_PARALLEL_BEGIN

bool HoloLocalHMD::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.sys.require_hmd = !ws.IsTrue(".device.optional.hmd", false);
	dev.sys.require_left = !ws.IsTrue(".device.optional.left", true);
	dev.sys.require_right = !ws.IsTrue(".device.optional.right", true);
	dev.sys.user_hmd_idx = ws.GetInt(".device.hmd.idx", dev.sys.require_hmd ? 0 : -1);
	dev.sys.user_ctrl_idx[0] = ws.GetInt(".device.left.idx", dev.sys.require_left ? 0 : -1);
	dev.sys.user_ctrl_idx[1] = ws.GetInt(".device.right.idx", dev.sys.require_right ? 0 : -1);
	dev.sys.verbose = !ws.IsTrue(".quiet", false);
	
	if (!dev.sys.Initialise())
		return false;
		
	dev.ts.Reset();
	return true;
}

bool HoloLocalHMD::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	
	return true;
}

bool HoloLocalHMD::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	
	return true;
}

void HoloLocalHMD::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void HoloLocalHMD::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	dev.sys.Uninitialise();
}

bool HoloLocalHMD::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.sys.ev_sendable);
	if (!dev.sys.ev_sendable)
		return false;
	
	Format fmt = out.GetFormat();
	RTLOG("HoloLocalHMD::SinkDevice_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		UPP::CtrlEvent& dst = out.SetData<UPP::CtrlEvent>();
		dst = dev.sys.ev;
		out.seq = dev.sys.seq++;
	}
	
	return true;
}

bool HoloLocalHMD::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	return true;
}

void HoloLocalHMD::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool HoloLocalHMD::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase& a, PacketIO& io) {
	dev.sys.UpdateData();
	return true;
}





NAMESPACE_PARALLEL_END
#endif

