#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN




WmrFusionSystem::WmrFusionSystem() {
	
}

void WmrFusionSystem::Process() {
	
	if (in_bright.lock && *in_bright.lock) {
		LOG("WmrFusionSystem::Process: fake bright image process");
		Sleep(2);
		
		*in_bright.lock = false;
	}
	
	if (in_dark.lock && *in_dark.lock) {
		LOG("WmrFusionSystem::Process: fake dark image process");
		Sleep(2);
		
		*in_dark.lock = false;
	}
	
	/*if (in_hmd.new_data) {
		LOG("WmrFusionSystem::Process: new hmd sensor data process");
		Sleep(2);
		
		in_hmd.new_data = false;
	}
	
	for(int i = 0; i < 2; i++) {
		if (in_ctrl[i].new_data) {
			LOG("WmrFusionSystem::Process: new ctrl " << i << " sensor data process");
			Sleep(2);
			
			in_ctrl[i].new_data = false;
		}
	}*/
	
	if (new_ev) {
		LOG("WmrFusionSystem::Process: fake EventCtrl process");
		Sleep(2);
		
		new_ev = false;
	}
}

/*void WmrFusionSystem::PutHmdSensors(const quat& orientation, const vec3& accel) {
	in_hmd.orientation = orientation;
	in_hmd.accel = accel;
	in_hmd.new_data = true;
}

void WmrFusionSystem::PutHmdController(int i, const quat& orientation, const vec3& accel) {
	ASSERT(i >= 0 && i < 2);
	if (i < 0 || i >= 2) return;
	auto& in = in_ctrl[i];
	in.orientation = orientation;
	in.accel = accel;
	in.new_data = true;
}*/

void WmrFusionSystem::PutSensorData(CtrlEvent& ev) {
	new_ev = true;
	if (ev.ctrl)
		in_ctrl = *ev.ctrl;
	if (ev.trans)
		in_trans = *ev.trans;
	in_ev = ev;
	in_ev.ctrl = 0;
	in_ev.trans = 0;
}

void WmrFusionSystem::Attach(SerialServiceServer& server) {
	server.AddTcpSocket(NET_SEND_FUSION_DATA, THISBACK(SendFusionData));
}

void WmrFusionSystem::SendFusionData(TcpSocket& out) {
	
	TODO
	
}

void WmrFusionSystem::PutBrightFrame(bool& lock, Size sz, const Vector<byte>& data) {
	lock = true;
	in_bright.lock = &lock;
	in_bright.sz = sz;
	in_bright.data = &data;
}

void WmrFusionSystem::PutDarkFrame(bool& lock, Size sz, const Vector<byte>& data) {
	lock = true;
	in_dark.lock = &lock;
	in_dark.sz = sz;
	in_dark.data = &data;
}











WmrFusionSystemReceiver::WmrFusionSystemReceiver() {
	
}

bool WmrFusionSystemReceiver::UpdateFrom(SerialServiceClient& client) {
	
	if (!client.CallSocket(NET_LATEST_BRIGHT_FRAME, THISBACK(GetEvent)))
		return false;
	
	TODO
	
	return ev_sendable;
}

void WmrFusionSystemReceiver::GetEvent(TcpSocket& sock) {
	
	TODO
	
	ev.ctrl = &ctrl;
	ev.trans = &trans;
	ev_sendable = true;
}

NAMESPACE_TOPSIDE_END
