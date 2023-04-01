#include "LocalHMD.h"

NAMESPACE_HMD_BEGIN


System::System() {
	//verbose = true;
	
}

bool System::Initialise() {
	seq = 0;
	ev.trans = &trans;
	ev.ctrl = &ev3d;
	has_initial_orient = 0;
	initial_orient.SetNull();
	
	// Get & check openhmd version
	int major, minor, patch;
	HMD::GetVersion(&major, &minor, &patch);
	LOG("LocalHMD version: " << major << "." << minor << "." << patch);
	int code = major * 100 + minor;
	if (code < 3) {
		LOG("HoloLocalHMD::SinkDevice_Initialize: error: too old openhmd version (" << major << "." << minor << ")");
		return false;
	}
	
	// Create openhmd context
	ctx = HMD::CreateContext();
	
	// Probe for devices
	int num_devices = HMD::ProbeContext(ctx);
	if (num_devices < 0){
		LOG("HoloLocalHMD::SinkDevice_Initialize: error: failed to probe devices: " << HMD::GetContextError(ctx));
		return false;
	}
	if (num_devices == 0){
		LOG("HoloLocalHMD::SinkDevice_Initialize: error: no connected devices");
		return false;
	}
	
	// Find device indices;
	int hmd_idx = -1, hmd_count = 0;
	int ctrl_idx[2] = {-1,-1}, ctrl_count[2] = {0,0};
	for (int i = 0; i < num_devices; i++) {
		int device_class = 0, device_flags = 0;
		HMD::GetListInt(ctx, i, HMD::HMD_DEVICE_CLASS, &device_class);
		HMD::GetListInt(ctx, i, HMD::HMD_DEVICE_FLAGS, &device_flags);
		String path = HMD::GetListString(ctx, i, HMD::HMD_PATH);
		
		// Skip null devices
		if (device_flags & HMD::HMD_DEVICE_FLAGS_NULL_DEVICE)
			continue;
		
		if (device_class == HMD::HMD_DEVICE_CLASS_HMD && path != "(none)") {
			if (hmd_count == user_hmd_idx || hmd_idx < 0)
				hmd_idx = i;
			hmd_count++;
		}
		else if (device_class == HMD::HMD_DEVICE_CLASS_CONTROLLER) {
			int j = (device_flags & HMD::HMD_DEVICE_FLAGS_LEFT_CONTROLLER ? 0 : 1);
			if (ctrl_count[j] == user_ctrl_idx[j] || ctrl_idx[j] < 0)
				ctrl_idx[j] = i;
			ctrl_count[j]++;
		}
		
	}
	if (hmd_idx < 0) {
		LOG("HoloLocalHMD::SinkDevice_Initialize: error: could not find any hmd device");
		return false;
	}
	
	// Dump device info
	if (verbose) {
		LOG("HoloLocalHMD::SinkDevice_Initialize: dumping openhmd device info");
		for(int i = 0; i < num_devices; i++){
			int device_class = 0, device_flags = 0;
			const char* device_class_s[] = {"HMD", "Controller", "Generic Tracker", "Unknown"};
	
			HMD::GetListInt(ctx, i, HMD::HMD_DEVICE_CLASS, &device_class);
			HMD::GetListInt(ctx, i, HMD::HMD_DEVICE_FLAGS, &device_flags);
	
			LOG("device " << i);
			LOG("  vendor:  " << HMD::GetListString(ctx, i, HMD::HMD_VENDOR));
			LOG("  product: " << HMD::GetListString(ctx, i, HMD::HMD_PRODUCT));
			LOG("  path:    " << HMD::GetListString(ctx, i, HMD::HMD_PATH));
			LOG("  class:   " << device_class_s[device_class > HMD::HMD_DEVICE_CLASS_GENERIC_TRACKER ? 4 : device_class]);
			LOG("  flags:   " << HexStr(device_flags));
			LOG("    null device:         " << (device_flags & HMD::HMD_DEVICE_FLAGS_NULL_DEVICE ? "yes" : "no"));
			LOG("    rotational tracking: " << (device_flags & HMD::HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING ? "yes" : "no"));
			LOG("    positional tracking: " << (device_flags & HMD::HMD_DEVICE_FLAGS_POSITIONAL_TRACKING ? "yes" : "no"));
			LOG("    left controller:     " << (device_flags & HMD::HMD_DEVICE_FLAGS_LEFT_CONTROLLER ? "yes" : "no"));
			LOG("    right controller:    " << (device_flags & HMD::HMD_DEVICE_FLAGS_RIGHT_CONTROLLER ? "yes" : "no"));
		}
	}

	settings = HMD::CreateDeviceSettings(ctx);

	// If HMD::HMD_IDS_AUTOMATIC_UPDATE is set to 0, ohmd_ctx_update() must be called at least 10 times per second.
	// It is enabled by default.
	int auto_update = 0;
	HMD::SetDeviceSettingsInt(settings, HMD::HMD_IDS_AUTOMATIC_UPDATE, &auto_update);

	if (hmd_idx >= 0)
		hmd = HMD::OpenListDeviceSettings(ctx, hmd_idx, settings);
	
	for(int i = 0; i < 2; i++)
		this->ctrl[i] = HMD::OpenListDeviceSettings(ctx, ctrl_idx[i], settings);
	
	if(	(hmd_idx >= 0 && !hmd) ||
		(ctrl_idx[0] >= 0 && !this->ctrl[0]) ||
		(ctrl_idx[1] >= 0 && !this->ctrl[1])){
		LOG("HoloLocalHMD::SinkDevice_Initialize: error: failed to open device: " << HMD::GetContextError(ctx));
		return false;
	}
	HMD::GetDeviceInt(hmd, HMD::HMD_SCREEN_HORIZONTAL_RESOLUTION, &screen_sz.cx);
	HMD::GetDeviceInt(hmd, HMD::HMD_SCREEN_VERTICAL_RESOLUTION, &screen_sz.cy);
	if (verbose) {
		LOG("HoloLocalHMD: info: resolution:               " << screen_sz.ToString());
		PrintHMD("hsize",            1, HMD::HMD_SCREEN_HORIZONTAL_SIZE);
		PrintHMD("vsize",            1, HMD::HMD_SCREEN_VERTICAL_SIZE);
		PrintHMD("lens separation",  1, HMD::HMD_LENS_HORIZONTAL_SEPARATION);
		PrintHMD("lens vcenter",     1, HMD::HMD_LENS_VERTICAL_POSITION);
		PrintHMD("left eye fov",     1, HMD::HMD_LEFT_EYE_FOV);
		PrintHMD("right eye fov",    1, HMD::HMD_RIGHT_EYE_FOV);
		PrintHMD("left eye aspect",  1, HMD::HMD_LEFT_EYE_ASPECT_RATIO);
		PrintHMD("right eye aspect", 1, HMD::HMD_RIGHT_EYE_ASPECT_RATIO);
		PrintHMD("distortion k",     6, HMD::HMD_DISTORTION_K);
		PrintHMD("control count", 1, HMD::HMD_CONTROL_COUNT);
	}
	
	float ipd;
	HMD::GetDeviceFloat(hmd, HMD::HMD_EYE_IPD, &ipd);
	
	float viewport_scale[2];
	float distortion_coeffs[4];
	float aberr_scale[3];
	float sep;
	float left_lens_center[2];
	float right_lens_center[2];
	
	// Viewport is half the screen
	HMD::GetDeviceFloat(hmd, HMD::HMD_SCREEN_HORIZONTAL_SIZE, &(viewport_scale[0]));
	viewport_scale[0] /= 2.0f;
	HMD::GetDeviceFloat(hmd, HMD::HMD_SCREEN_VERTICAL_SIZE, &(viewport_scale[1]));
	
	// Distortion coefficients
	HMD::GetDeviceFloat(hmd, HMD::HMD_UNIVERSAL_DISTORTION_K, &(distortion_coeffs[0]));
	HMD::GetDeviceFloat(hmd, HMD::HMD_UNIVERSAL_ABERRATION_K, &(aberr_scale[0]));
	
	// Calculate lens centers (assuming the eye separation is the distance between the lens centers)
	HMD::GetDeviceFloat(hmd, HMD::HMD_LENS_HORIZONTAL_SEPARATION, &sep);
	HMD::GetDeviceFloat(hmd, HMD::HMD_LENS_VERTICAL_POSITION, &(left_lens_center[1]));
	HMD::GetDeviceFloat(hmd, HMD::HMD_LENS_VERTICAL_POSITION, &(right_lens_center[1]));
	left_lens_center[0] = viewport_scale[0] - sep/2.0f;
	right_lens_center[0] = sep/2.0f;
	
	// Assume calibration was for lens view to which ever edge of screen is further away from lens center
	//float warp_scale = (left_lens_center[0] > right_lens_center[0]) ? left_lens_center[0] : right_lens_center[0];
	float warp_adj = 1.0f;
	
	// Get controller info
	for(int i = 0; i < 2; i++) {
		if (!this->ctrl[i])
			continue;
		
		HMD::GetDeviceInt(this->ctrl[i], HMD::HMD_CONTROL_COUNT, &control_count[i]);
		HMD::GetDeviceInt(this->ctrl[i], HMD::HMD_CONTROLS_HINTS, controls_fn[i]);
		HMD::GetDeviceInt(this->ctrl[i], HMD::HMD_CONTROLS_TYPES, controls_types[i]);
		
		
		const char* controls_fn_str[] = {
			"generic",
			"trigger",
			"trigger_click",
			"squeeze",
			"menu",
			"home",
			"analog-x",
			"analog-y",
			"anlog_press",
			"button-a",
			"button-b",
			"button-x",
			"button-y",
			"volume-up",
			"volume-down",
			"mic-mute"
		};
		
		const char* controls_type_str[] = {"digital", "analog"};
		
		int c = control_count[i];
		if (c > 0) {
			LOG("HoloLocalHMD: control " << i << ":");
			for(int j = 0; j < c; j++){
				LOG(controls_fn_str[controls_fn[i][j]] << " (" <<
					controls_type_str[controls_types[i][j]] << ")" <<
					(j == c - 1 ? "" : ", "));
			}
		}
	}
	
	HMD::DestroyDeviceSettings(settings);

	HMD::GetString(HMD::HMD_GLSL_DISTORTION_VERT_SRC, &vertex);
	HMD::GetString(HMD::HMD_GLSL_DISTORTION_FRAG_SRC, &fragment);
	
	LOG("LocalHMD vertex shader:\n" << GetLineNumStr(vertex) << "\n");
	LOG("LocalHMD fragment shader:\n" << GetLineNumStr(fragment) << "\n");
	
	
	return true;
}

void System::Start() {
	flag.Start(1);
	UPP::Thread::Start(THISBACK(BackgroundProcess));
}

void System::Stop() {
	flag.Stop();
}

void System::Uninitialise() {
	if (ctx) {
		HMD::DestroyContext(ctx);
		ctx = 0;
	}
}

void System::BackgroundProcess() {
	
	while (flag.IsRunning()) {
		UpdateData();
		Sleep(1000/60);
	}
	
	flag.DecreaseRunning();
}

void System::UpdateData() {
	trans.Clear();
	
	HMD::UpdateContext(ctx);
	
	HMD::GetDeviceFloat(hmd, HMD::HMD_ROTATION_QUAT, trans.orientation.data.data);
	
	if (!has_initial_orient) {
		has_initial_orient = true;
		
		vec3 axes;
		float& yaw = axes[0];
		float& pitch = axes[1];
		float& roll = axes[2];
		QuatAxes(trans.orientation, yaw, pitch, roll);
		pitch = 0;
		roll = 0;
		initial_orient = AxesQuat(yaw, pitch, roll);
	}
	
	trans.orientation = MatQuat(QuatMat(trans.orientation) * QuatMat(initial_orient));
	
	trans.mode = UPP::TransformMatrix::MODE_AXES;
	trans.is_stereo = true;
	trans.position = vec3(0,0,0);
	trans.FillFromOrientation();
	
	if (verbose) {
		LOG("Head: pos " << trans.position.ToString() << ", " << trans.GetAxesString());
	}
	
	HMD::GetDeviceFloat(hmd, HMD::HMD_EYE_IPD, &trans.eye_dist);
	HMD::GetDeviceFloat(hmd, HMD::HMD_POSITION_VECTOR, trans.position.data);
	HMD::GetDeviceFloat(hmd, HMD::HMD_LEFT_EYE_FOV, &trans.fov);
	
	// Local calibration values (currently fixed placeholder) (use test 07h to calibrate these)
	if (use_calibration_values) {
		trans.fov += 0.261799-0.665658;
		trans.eye_dist += -0.0452138;
	}
	
	#if 0
	// set hmd rotation, for left eye.
	float proj[4][4];
	float view[4][4];
	HMD::GetDeviceFloat(hmd, HMD::HMD_LEFT_EYE_GL_PROJECTION_MATRIX, &proj[0][0]);
	HMD::GetDeviceFloat(hmd, HMD::HMD_LEFT_EYE_GL_MODELVIEW_MATRIX, &view[0][0]);
	COPY4x4(trans.proj[0], proj);
	COPY4x4(trans.view[0], view);
	
	// set hmd rotation, for right eye.
	HMD::GetDeviceFloat(hmd, HMD::HMD_RIGHT_EYE_GL_PROJECTION_MATRIX, &proj[0][0]);
	HMD::GetDeviceFloat(hmd, HMD::HMD_RIGHT_EYE_GL_MODELVIEW_MATRIX, &view[0][0]);
	COPY4x4(trans.proj[1], proj);
	COPY4x4(trans.view[1], view);
	#endif
	
	
	for(int i = 0; i < 2; i++) {
		TS::HMD::Device* d = ctrl[i];
		ControllerMatrix::Ctrl& ctrl = ev3d.ctrl[i];
		int c = control_count[i];
		
		ctrl.is_enabled = this->ctrl[i] != 0;
		
		if (d) {
			ctrl.trans.mode = TransformMatrix::MODE_QUATERNION;
			HMD::GetDeviceFloat(d, HMD::HMD_ROTATION_QUAT, ctrl.trans.orientation.data.data);
			HMD::GetDeviceFloat(d, HMD::HMD_POSITION_VECTOR, ctrl.trans.position.data);
			
			ctrl.trans.orientation = MatQuat(QuatMat(initial_orient) * QuatMat(ctrl.trans.orientation));
			//ctrl.trans.orientation = ctrl.trans.orientation;
			
			ctrl.trans.FillFromOrientation();
			if (ctrl.trans.position == vec3(0.5,0,0) ||
				ctrl.trans.position == vec3(-0.5,0,0)) {
				ctrl.trans.position *= 0.5;
				ctrl.trans.position += VEC_FWD * 1.0;
			}
			if (verbose) {
				LOG("\tCtrl " << i << ": pos " << ctrl.trans.position.ToString() << ", " << ctrl.trans.GetAxesString());
			}
		}
		
		if (d && c) {
			float control_state[256];
			HMD::GetDeviceFloat(d, HMD::HMD_CONTROLS_STATE, control_state);
			
			
			int count[ControllerMatrix::VALUE_COUNT];
			memset(count, 0, sizeof(count));
			
			String s;
			
			for(int j = 0; j < c; j++) {
				ControllerMatrix::Value type = ControllerMatrix::INVALID;
				switch (controls_fn[i][j]) {
					#undef CTRL
					#define CTRL(x) case HMD::HMD_##x: type = ControllerMatrix::Value::x; break;
					CTRL(GENERIC)
					CTRL(TRIGGER)
					CTRL(TRIGGER_CLICK)
					CTRL(SQUEEZE)
					CTRL(MENU)
					CTRL(HOME)
					CTRL(ANALOG_X)
					CTRL(ANALOG_Y)
					CTRL(ANALOG_PRESS)
					CTRL(BUTTON_A)
					CTRL(BUTTON_B)
					CTRL(BUTTON_X)
					CTRL(BUTTON_Y)
					CTRL(VOLUME_PLUS)
					CTRL(VOLUME_MINUS)
					CTRL(MIC_MUTE)
					#undef CTRL
					default: break;
				}
				if (type != ControllerMatrix::INVALID) {
					count[type]++;
					if (type == ControllerMatrix::ANALOG_PRESS ||
						type == ControllerMatrix::ANALOG_X ||
						type == ControllerMatrix::ANALOG_Y
					) {
						ASSERT(count[type] <= 4);
						type = (ControllerMatrix::Value)((int)type + count[type] - 1);
					}
					else {
						ASSERT(count[type] == 1);
					}
					
					ctrl.is_value[type] = true;
					ctrl.value[type] = control_state[j];
				}
				/*if (type == HMD::HMD_MENU && control_state[j] > 0) {
					LOG("");
				}*/
			}
		}
	}
	
	ev_sendable = true;
	ev.type = EVENT_HOLO_STATE;
	
	WhenSensorEvent(ev);
}

void System::PrintHMD(String name, int len, HMD::FloatValue val)
{
	float f[16];
	ASSERT(len <= 16);
	HMD::GetDeviceFloat(hmd, val, f);
	
	String s;
	s << name << ":";
	if (name.GetCount() < 25) s.Cat(' ', 25 - name.GetCount());
	for(int i = 0; i < len; i++) {
		if (i) s << ", ";
		s << DblStr(f[i]);
	}
	LOG("HoloLocalHMD: info: " << s);
}

void System::PrintHMD(String name, int len, HMD::IntValue val)
{
	int v[16];
	ASSERT(len <= 16);
	HMD::GetDeviceInt(hmd, val, v);
	
	String s;
	s << name << ":";
	if (name.GetCount() < 25) s.Cat(' ', 25 - name.GetCount());
	for(int i = 0; i < len; i++) {
		if (i) s << ", ";
		s << IntStr(v[i]);
	}
	LOG("HoloLocalHMD: info: " << s);
}


NAMESPACE_HMD_END
