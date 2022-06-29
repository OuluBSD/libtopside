#include "IHolograph.h"

#if defined flagLOCALHMD
NAMESPACE_PARALLEL_BEGIN

void PrintHMD(HoloLocalHMD::NativeSinkDevice& dev, String name, int len, HMD::FloatValue val)
{
	float f[16];
	ASSERT(len <= 16);
	HMD::GetDeviceFloat(dev.hmd, val, f);
	
	String s;
	s << name << ":";
	if (name.GetCount() < 25) s.Cat(' ', 25 - name.GetCount());
	for(int i = 0; i < len; i++) {
		if (i) s << ", ";
		s << DblStr(f[i]);
	}
	LOG("HoloLocalHMD: info: " << s);
}

void PrintHMD(HoloLocalHMD::NativeSinkDevice& dev, String name, int len, HMD::IntValue val)
{
	int v[16];
	ASSERT(len <= 16);
	HMD::GetDeviceInt(dev.hmd, val, v);
	
	String s;
	s << name << ":";
	if (name.GetCount() < 25) s.Cat(' ', 25 - name.GetCount());
	for(int i = 0; i < len; i++) {
		if (i) s << ", ";
		s << IntStr(v[i]);
	}
	LOG("HoloLocalHMD: info: " << s);
}

bool HoloLocalHMD::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	bool require_hmd = !ws.IsTrue(".device.optional.hmd", false);
	bool require_left = !ws.IsTrue(".device.optional.left", true);
	bool require_right = !ws.IsTrue(".device.optional.right", true);
	int user_hmd_idx = ws.GetInt(".device.hmd.idx", require_hmd ? 0 : -1);
	int user_ctrl_idx[2];
	user_ctrl_idx[0] = ws.GetInt(".device.left.idx", require_left ? 0 : -1);
	user_ctrl_idx[1] = ws.GetInt(".device.right.idx", require_right ? 0 : -1);
	bool verbose = !ws.IsTrue(".quiet", false);
	
	
	dev.seq = 0;
	dev.ev.trans = &dev.trans;
	dev.ev.ctrl = &dev.ev3d;
	dev.has_initial_orient = 0;
	dev.initial_orient.SetNull();
	
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
	dev.ctx = HMD::CreateContext();
	
	// Probe for devices
	int num_devices = HMD::ProbeContext(dev.ctx);
	if (num_devices < 0){
		LOG("HoloLocalHMD::SinkDevice_Initialize: error: failed to probe devices: " << HMD::GetContextError(dev.ctx));
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
		HMD::GetListInt(dev.ctx, i, HMD::HMD_DEVICE_CLASS, &device_class);
		HMD::GetListInt(dev.ctx, i, HMD::HMD_DEVICE_FLAGS, &device_flags);
		String path = HMD::GetListString(dev.ctx, i, HMD::HMD_PATH);
		
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
	
			HMD::GetListInt(dev.ctx, i, HMD::HMD_DEVICE_CLASS, &device_class);
			HMD::GetListInt(dev.ctx, i, HMD::HMD_DEVICE_FLAGS, &device_flags);
	
			LOG("device " << i);
			LOG("  vendor:  " << HMD::GetListString(dev.ctx, i, HMD::HMD_VENDOR));
			LOG("  product: " << HMD::GetListString(dev.ctx, i, HMD::HMD_PRODUCT));
			LOG("  path:    " << HMD::GetListString(dev.ctx, i, HMD::HMD_PATH));
			LOG("  class:   " << device_class_s[device_class > HMD::HMD_DEVICE_CLASS_GENERIC_TRACKER ? 4 : device_class]);
			LOG("  flags:   " << HexStr(device_flags));
			LOG("    null device:         " << (device_flags & HMD::HMD_DEVICE_FLAGS_NULL_DEVICE ? "yes" : "no"));
			LOG("    rotational tracking: " << (device_flags & HMD::HMD_DEVICE_FLAGS_ROTATIONAL_TRACKING ? "yes" : "no"));
			LOG("    positional tracking: " << (device_flags & HMD::HMD_DEVICE_FLAGS_POSITIONAL_TRACKING ? "yes" : "no"));
			LOG("    left controller:     " << (device_flags & HMD::HMD_DEVICE_FLAGS_LEFT_CONTROLLER ? "yes" : "no"));
			LOG("    right controller:    " << (device_flags & HMD::HMD_DEVICE_FLAGS_RIGHT_CONTROLLER ? "yes" : "no"));
		}
	}

	dev.settings = HMD::CreateDeviceSettings(dev.ctx);

	// If HMD::HMD_IDS_AUTOMATIC_UPDATE is set to 0, ohmd_ctx_update() must be called at least 10 times per second.
	// It is enabled by default.

	int auto_update = 0;
	HMD::SetDeviceSettingsInt(dev.settings, HMD::HMD_IDS_AUTOMATIC_UPDATE, &auto_update);

	if (hmd_idx >= 0)
		dev.hmd = HMD::OpenListDeviceSettings(dev.ctx, hmd_idx, dev.settings);
	
	for(int i = 0; i < 2; i++)
		dev.ctrl[i] = HMD::OpenListDeviceSettings(dev.ctx, ctrl_idx[i], dev.settings);
	
	if(	(hmd_idx >= 0 && !dev.hmd) ||
		(ctrl_idx[0] >= 0 && !dev.ctrl[0]) ||
		(ctrl_idx[1] >= 0 && !dev.ctrl[1])){
		LOG("HoloLocalHMD::SinkDevice_Initialize: error: failed to open device: " << HMD::GetContextError(dev.ctx));
		return false;
	}
	HMD::GetDeviceInt(dev.hmd, HMD::HMD_SCREEN_HORIZONTAL_RESOLUTION, &dev.screen_sz.cx);
	HMD::GetDeviceInt(dev.hmd, HMD::HMD_SCREEN_VERTICAL_RESOLUTION, &dev.screen_sz.cy);
	if (verbose) {
		LOG("HoloLocalHMD: info: resolution:               " << dev.screen_sz.ToString());
		PrintHMD(dev, "hsize",            1, HMD::HMD_SCREEN_HORIZONTAL_SIZE);
		PrintHMD(dev, "vsize",            1, HMD::HMD_SCREEN_VERTICAL_SIZE);
		PrintHMD(dev, "lens separation",  1, HMD::HMD_LENS_HORIZONTAL_SEPARATION);
		PrintHMD(dev, "lens vcenter",     1, HMD::HMD_LENS_VERTICAL_POSITION);
		PrintHMD(dev, "left eye fov",     1, HMD::HMD_LEFT_EYE_FOV);
		PrintHMD(dev, "right eye fov",    1, HMD::HMD_RIGHT_EYE_FOV);
		PrintHMD(dev, "left eye aspect",  1, HMD::HMD_LEFT_EYE_ASPECT_RATIO);
		PrintHMD(dev, "right eye aspect", 1, HMD::HMD_RIGHT_EYE_ASPECT_RATIO);
		PrintHMD(dev, "distortion k",     6, HMD::HMD_DISTORTION_K);
		PrintHMD(dev, "control count", 1, HMD::HMD_CONTROL_COUNT);
	}
	
	float ipd;
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_EYE_IPD, &ipd);
	
	float viewport_scale[2];
	float distortion_coeffs[4];
	float aberr_scale[3];
	float sep;
	float left_lens_center[2];
	float right_lens_center[2];
	
	// Viewport is half the screen
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_SCREEN_HORIZONTAL_SIZE, &(viewport_scale[0]));
	viewport_scale[0] /= 2.0f;
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_SCREEN_VERTICAL_SIZE, &(viewport_scale[1]));
	
	// Distortion coefficients
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_UNIVERSAL_DISTORTION_K, &(distortion_coeffs[0]));
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_UNIVERSAL_ABERRATION_K, &(aberr_scale[0]));
	
	// Calculate lens centers (assuming the eye separation is the distance between the lens centers)
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_LENS_HORIZONTAL_SEPARATION, &sep);
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_LENS_VERTICAL_POSITION, &(left_lens_center[1]));
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_LENS_VERTICAL_POSITION, &(right_lens_center[1]));
	left_lens_center[0] = viewport_scale[0] - sep/2.0f;
	right_lens_center[0] = sep/2.0f;
	
	// Assume calibration was for lens view to which ever edge of screen is further away from lens center
	float warp_scale = (left_lens_center[0] > right_lens_center[0]) ? left_lens_center[0] : right_lens_center[0];
	float warp_adj = 1.0f;
	
	// Get controller info
	for(int i = 0; i < 2; i++) {
		if (!dev.ctrl[i])
			continue;
		
		HMD::GetDeviceInt(dev.ctrl[i], HMD::HMD_CONTROL_COUNT, &dev.control_count[i]);
		HMD::GetDeviceInt(dev.ctrl[i], HMD::HMD_CONTROLS_HINTS, dev.controls_fn[i]);
		HMD::GetDeviceInt(dev.ctrl[i], HMD::HMD_CONTROLS_TYPES, dev.controls_types[i]);
		
		
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
		
		int c = dev.control_count[i];
		if (c > 0) {
			LOG("HoloLocalHMD: control " << i << ":");
			for(int j = 0; j < c; j++){
				LOG(controls_fn_str[dev.controls_fn[i][j]] << " (" <<
					controls_type_str[dev.controls_types[i][j]] << ")" <<
					(j == c - 1 ? "" : ", "));
			}
		}
	}
	
	HMD::DestroyDeviceSettings(dev.settings);

	HMD::GetString(HMD::HMD_GLSL_DISTORTION_VERT_SRC, &dev.vertex);
	HMD::GetString(HMD::HMD_GLSL_DISTORTION_FRAG_SRC, &dev.fragment);
	
	LOG("LocalHMD vertex shader:\n" << GetLineNumStr(dev.vertex) << "\n");
	LOG("LocalHMD fragment shader:\n" << GetLineNumStr(dev.fragment) << "\n");
	
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
	HMD::DestroyContext(dev.ctx);
}

bool HoloLocalHMD::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.ev_sendable);
	if (!dev.ev_sendable)
		return false;
	
	Format fmt = out.GetFormat();
	RTLOG("HoloLocalHMD::SinkDevice_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		UPP::CtrlEvent& dst = out.SetData<UPP::CtrlEvent>();
		dst = dev.ev;
		out.seq = dev.seq++;
	}
	
	return true;
}

bool HoloLocalHMD::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	return true;
}

void HoloLocalHMD::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
}

bool HoloLocalHMD::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase& a, PacketIO& io) {
	dev.trans.Clear();
	
	const float wait_time = 1.0 / 30;
	if (dev.ts.Seconds() < wait_time)
		return false;
	dev.ts.Reset();
	
	HMD::UpdateContext(dev.ctx);
	
	
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_ROTATION_QUAT, dev.trans.orientation.data.data);
	//StupidHotfix(dev.trans.orientation, dev.has_initial_yaw, dev.initial_yaw);
	if (!dev.has_initial_orient) {
		dev.has_initial_orient = true;
		
		vec3 axes;
		float& yaw = axes[0];
		float& pitch = axes[1];
		float& roll = axes[2];
		QuatAxes(dev.trans.orientation, yaw, pitch, roll);
		pitch = 0;
		roll = 0;
		dev.initial_orient = AxesQuat(yaw, pitch, roll);
	}
	#if 0
	// this should work, but doesn't
	dev.trans.orientation =
		MatQuat(
			QuatMat(dev.trans.orientation)
			* QuatMat(dev.initial_orient).GetInverse());
	#else
	vec3 initial_axes;
	QuatAxes(dev.initial_orient, initial_axes[0], initial_axes[1], initial_axes[2]);
	vec3 axes;
	QuatAxes(dev.trans.orientation, axes[0], axes[1], axes[2]);
	//axes[0] *= -1;
	dev.trans.orientation = AxesQuat(axes[0] - initial_axes[0], axes[1], axes[2]);
	#endif
	
	dev.trans.mode = UPP::TransformMatrix::MODE_AXES;
	dev.trans.is_stereo = true;
	dev.trans.position = vec3(0,0,0);
	dev.trans.FillFromOrientation();
	
	#if 0
	LOG("Head: pos " << dev.trans.position.ToString() << ", " << dev.trans.GetAxesString());
	#endif
	
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_EYE_IPD, &dev.trans.eye_dist);
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_POSITION_VECTOR, dev.trans.position.data);
	
	
	#if 0
	// set hmd rotation, for left eye.
	float proj[4][4];
	float view[4][4];
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_LEFT_EYE_GL_PROJECTION_MATRIX, &proj[0][0]);
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_LEFT_EYE_GL_MODELVIEW_MATRIX, &view[0][0]);
	COPY4x4(dev.trans.proj[0], proj);
	COPY4x4(dev.trans.view[0], view);
	
	// set hmd rotation, for right eye.
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_RIGHT_EYE_GL_PROJECTION_MATRIX, &proj[0][0]);
	HMD::GetDeviceFloat(dev.hmd, HMD::HMD_RIGHT_EYE_GL_MODELVIEW_MATRIX, &view[0][0]);
	COPY4x4(dev.trans.proj[1], proj);
	COPY4x4(dev.trans.view[1], view);
	#endif
	//dev.ev3d.use_lookat = false;
	//dev.ev3d.use_view = false;
	
	
	bool verbose = true;
	if (verbose) {
		/*LOG("HoloLocalHMD::SinkDevice_IsReady:");
		mat4 m;
		m.Set(dev.ev3d.r_proj);
		DUMP(m);*/
	}
	
	for(int i = 0; i < 2; i++) {
		TS::HMD::Device* d = dev.ctrl[i];
		ControllerMatrix::Ctrl& ctrl = dev.ev3d.ctrl[i];
		int c = dev.control_count[i];
		
		ctrl.is_enabled = dev.ctrl[i] != 0;
		
		if (d) {
			ctrl.trans.mode = TransformMatrix::MODE_QUATERNION;
			HMD::GetDeviceFloat(d, HMD::HMD_ROTATION_QUAT, ctrl.trans.orientation.data.data);
			HMD::GetDeviceFloat(d, HMD::HMD_POSITION_VECTOR, ctrl.trans.position.data);
			ctrl.trans.orientation -= dev.initial_orient;
			ctrl.trans.FillFromOrientation();
			
			#if 0
			LOG("Ctrl " << i << ": pos " << ctrl.trans.position.ToString() << ", " << ctrl.trans.GetAxesString());
			#endif
		}
		
		if (d && c) {
			float control_state[256];
			HMD::GetDeviceFloat(d, HMD::HMD_CONTROLS_STATE, control_state);
			
			
			int count[ControllerMatrix::VALUE_COUNT];
			memset(count, 0, sizeof(count));
			
			String s;
			
			for(int j = 0; j < c; j++) {
				ControllerMatrix::Value type = ControllerMatrix::INVALID;
				switch (dev.controls_fn[i][j]) {
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
					
					if (0 && verbose) {
						if (s.GetCount())
							s << ", ";
						s << type << "=" << control_state[j];
					}
				}
			}
			
			if (0 && verbose) {
				LOG("HoloLocalHMD::SinkDevice_IsReady: " << s);
			}
		}
	}
	
	dev.ev_sendable = true;
	dev.ev.type = EVENT_HOLO_STATE;
	
	return true;
}





NAMESPACE_PARALLEL_END
#endif

