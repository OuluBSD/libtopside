#ifndef _Geometry_Vr_h_
#define _Geometry_Vr_h_

NAMESPACE_TOPSIDE_BEGIN


class VrSystemTestGenerator {
	
	
	
};


class WmrFusionSystem {
	
	struct FrameQueueItem {
		bool* lock = 0;
		Size sz;
		const Vector<byte>* data = 0;
	};
	FrameQueueItem in_dark, in_bright;
	
	/*struct SensorData {
		bool new_data = false;
		quat orientation;
		vec3 accel;
		
	};
	SensorData in_hmd, in_ctrl[2];*/
	
	ControllerMatrix in_ctrl;
	TransformMatrix in_trans;
	CtrlEvent in_ev;
	bool new_ev = false;
	
public:
	typedef WmrFusionSystem CLASSNAME;
	
	WmrFusionSystem();
	
	void Process();
	void Attach(SerialServiceServer& srv);
	void SendFusionData(TcpSocket& out);
	void PutBrightFrame(bool& lock, Size sz, const Vector<byte>& data);
	void PutDarkFrame(bool& lock, Size sz, const Vector<byte>& data);
	/*void PutHmdSensors(const quat& orientation, const vec3& accel);
	void PutHmdController(int i, const quat& orientation, const vec3& accel);*/
	void PutSensorData(CtrlEvent& ev);
	
};


struct WmrFusionSystemReceiver {
	CtrlEvent ev;
	ControllerMatrix ctrl;
	TransformMatrix trans;
	bool ev_sendable = false;
	dword seq = 0;
	
	
	typedef WmrFusionSystemReceiver CLASSNAME;
	WmrFusionSystemReceiver();
	bool UpdateFrom(SerialServiceClient& c);
	void GetEvent(TcpSocket& sock);
	
};


NAMESPACE_TOPSIDE_END

#endif
