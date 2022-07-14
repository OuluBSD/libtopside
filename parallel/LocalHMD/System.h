#ifndef _LocalHMD_System_h_
#define _LocalHMD_System_h_

NAMESPACE_HMD_BEGIN


struct System {
	RunningFlag flag;
	
	HMD::Context* ctx;
	HMD::DeviceSettings* settings;
	HMD::Device* hmd;
	HMD::Device* ctrl[2];
	
	const char* fragment;
	const char* vertex;
	Size screen_sz;
	CtrlEvent ev;
	ControllerMatrix ev3d;
	TransformMatrix trans;
	bool has_initial_orient;
	quat initial_orient;
	bool ev_sendable;
	int seq;
	int control_count[2];
	int controls_fn[2][64];
	int controls_types[2][64];
	
	bool require_hmd = false;
	bool require_left = true;
	bool require_right = true;
	bool verbose = false;
	bool use_calibration_values = true;
	int user_hmd_idx = -1;
	int user_ctrl_idx[2] = {-1,-1};
	

	void PrintHMD(String name, int len, HMD::FloatValue val);
	void PrintHMD(String name, int len, HMD::IntValue val);
	
	
	typedef System CLASSNAME;
	System();
	bool Initialise();
	void Start();
	void Stop();
	void Uninitialise();
	void BackgroundProcess();
	void UpdateData();
	
	Callback1<CtrlEvent&> WhenSensorEvent;
	
};


NAMESPACE_HMD_END

#endif
