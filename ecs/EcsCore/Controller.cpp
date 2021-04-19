#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


bool ControllerSystem::Initialize() {
	return true;
}

void ControllerSystem::Uninitialize() {

}

void ControllerSystem::Start() {

#ifdef flagOPENVR
	vr = machine.Get<OpenVR>();
	
	ctrl_states.SetCount(vr::k_unMaxTrackedDeviceCount);
	
	for (int device_id = 0; device_id < vr::k_unMaxTrackedDeviceCount; ++device_id) {
		ControllerState& state = ctrl_states[device_id];
		ControllerSourceDevice& src = state.src;
		ControllerSourceLocation& loc = state.loc;
		ControllerProperties& prop = state.prop;
		ControllerSourceHead& head = loc.head;
		ControllerPointerPose& pointer = loc.pointer;
		
		
		src.id = device_id;
		
		switch (vr->m_pHMD->GetTrackedDeviceClass(device_id)) {
		case vr::TrackedDeviceClass_Controller:
			src.kind = Controller;
			src.handedness = vr->m_pHMD->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_LeftHand) == device_id ? Left : Right;
			if (src.handedness)
				left_id = device_id;
			else
				right_id = device_id;
			break;
		case vr::TrackedDeviceClass_HMD:
			src.kind = HMD;
			break;
		case vr::TrackedDeviceClass_TrackingReference:
			src.kind = TrackingReference;
			break;
		case vr::TrackedDeviceClass_Invalid:
		default:
			src.kind = Invalid;
			break;
		}
		
		loc.angular_veolcity = zero<vec3>();
		loc.pose = identity<mat4>();
		loc.velocity = zero<vec3>();
		
		prop.is_touch_press = 0;
		prop.is_touch_touch = 0;
		prop.thumb_x = 0;
		prop.thumb_y = 0;
		prop.touch_x = 0;
		prop.touch_y = 0;
		
		head.pose = identity<mat4>();
		
		pointer.pose = identity<mat4>();
	}
#endif

}

void ControllerSystem::HandleSourceDetected(const ControllerEventArgs& args) {
	for (auto& listener : m_ctrl_Listeners.PurgeAndGetListeners()) {
		listener->OnSourceDetected(args);
	}
}

void ControllerSystem::HandleSourceLost(const ControllerEventArgs& args) {
	for (auto& listener : m_ctrl_Listeners.PurgeAndGetListeners()) {
		listener->OnSourceLost(args);
	}
}

void ControllerSystem::HandleSourcePressed(const ControllerEventArgs& args) {
	for (auto& listener : m_ctrl_Listeners.PurgeAndGetListeners()) {
		listener->OnSourcePressed(args);
	}
}

void ControllerSystem::HandleSourceUpdated(const ControllerEventArgs& args) {
	for (auto& listener : m_ctrl_Listeners.PurgeAndGetListeners()) {
		listener->OnSourceUpdated(args);
	}
}

void ControllerSystem::HandleSourceReleased(const ControllerEventArgs& args) {
	for (auto& listener : m_ctrl_Listeners.PurgeAndGetListeners()) {
		listener->OnSourceReleased(args);
	}
}


Vector<ControllerState> ControllerSystem::GetDetectedSourcesAtTimestamp(PerceptionTimestamp ts) {
	Vector<ControllerState> v;
	for (int i = 0; i < ctrl_states.GetCount(); i++) {
		if (ctrl_states[i])
			v.Add(ctrl_states[i]);
	}
	return v;
}

#ifdef flagOPENVR

void ControllerSystem::UpdateHMDMatrixPose() {

	for (int device_id = 0; device_id < vr::k_unMaxTrackedDeviceCount; ++device_id) {
		ControllerState& state = ctrl_states[device_id];
		ControllerSourceDevice& src = state.src;
		ControllerSourceLocation& loc = state.loc;
		ControllerProperties& prop = state.prop;
		ControllerSourceHead& head = loc.head;
		ControllerPointerPose& pointer = loc.pointer;
		
		if (vr->m_rTrackedDevicePose[device_id].bPoseIsValid) {
			state.SetValid(true);
			
			loc.angular_veolcity = ConvertSteamVRMatrixToVec3(vr->m_rTrackedDevicePose[device_id].vAngularVelocity);
			loc.pose = ConvertSteamVRMatrixToMat4(vr->m_rTrackedDevicePose[device_id].mDeviceToAbsoluteTracking);
			loc.velocity = ConvertSteamVRMatrixToVec3(vr->m_rTrackedDevicePose[device_id].vVelocity);
			/*
			prop.is_touch_press = 0;
			prop.is_touch_touch = 0;
			prop.thumb_x = 0;
			prop.thumb_y = 0;
			prop.touch_x = 0;
			prop.touch_y = 0;
			*/
			head.pose = loc.pose;
			
			pointer.pose = loc.pose;
		}
		else {
			state.SetValid(false);
		}
		
	}
	
}

void ControllerSystem::ProcessEvent(const vr::VREvent_t& event) {
	if (event.trackedDeviceIndex < 0 || event.trackedDeviceIndex >= ctrl_states.GetCount())
		return;
		
	ControllerState& ctrl_state = ctrl_states[event.trackedDeviceIndex];
	ControllerSourceDevice& src = ctrl_state.src;
	ControllerSourceLocation& loc = ctrl_state.loc;
	ControllerProperties& prop = ctrl_state.prop;
	ControllerSourceHead& head = loc.head;
	ControllerPointerPose& pointer = loc.pointer;
	
	const int left_controller = vr->m_pHMD->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_LeftHand);
	const int right_controller = vr->m_pHMD->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_RightHand);
	
	
	const vr::VREvent_Controller_t controller = event.data.controller;
	
	if (controller.button == vr::k_EButton_SteamVR_Trigger) {
		if (event.eventType == vr::VREvent_ButtonPress) {
			ControllerEventArgs args;
			args.state = ctrl_states[event.trackedDeviceIndex];
			args.kind = Trigger;
			HandleSourcePressed(args);
		}
		else if (event.eventType == vr::VREvent_ButtonUnpress) {
			ControllerEventArgs args;
			args.state = ctrl_states[event.trackedDeviceIndex];
			args.kind = Trigger;
			HandleSourceReleased(args);
		}
	}
	else if (controller.button == vr::k_EButton_Axis0) {
		vr::VRControllerState_t state;
		if (vr->m_pHMD->GetControllerState(left_controller, &state, 0)) {
		
			prop.touch_x = state.rAxis[0].x;
			prop.touch_y = state.rAxis[0].y;
			
			if (event.eventType == vr::VREvent_ButtonTouch) {
				prop.is_touch_touch = true;
			}
			else if (event.eventType == vr::VREvent_ButtonUntouch) {
				prop.is_touch_touch = false;
			}
			else if (event.eventType == vr::VREvent_ButtonPress) {
				prop.is_touch_press = true;
				ControllerEventArgs args;
				args.state = ctrl_states[event.trackedDeviceIndex];
				args.kind = Touchpad;
				HandleSourcePressed(args);
			}
			else if (event.eventType == vr::VREvent_ButtonUnpress) {
				prop.is_touch_press = false;
				ControllerEventArgs args;
				args.state = ctrl_states[event.trackedDeviceIndex];
				args.kind = Touchpad;
				HandleSourceReleased(args);
			}
		}
	}
	else if (controller.button == vr::k_EButton_ApplicationMenu) {
		if (event.eventType == vr::VREvent_ButtonPress) {
			ControllerEventArgs args;
			args.state = ctrl_states[event.trackedDeviceIndex];
			args.kind = Menu;
			HandleSourcePressed(args);
		}
		else if (event.eventType == vr::VREvent_ButtonUnpress) {
			ControllerEventArgs args;
			args.state = ctrl_states[event.trackedDeviceIndex];
			args.kind = Menu;
			HandleSourceReleased(args);
		}
	}
}

void ControllerSystem::ProcessController(vr::TrackedDeviceIndex_t device, vr::VRControllerState_t* state, mat4& M) {
	ControllerState& ctrl_state = ctrl_states[device];
	ControllerSourceDevice& src = ctrl_state.src;
	ControllerSourceLocation& loc = ctrl_state.loc;
	ControllerProperties& prop = ctrl_state.prop;
	ControllerSourceHead& head = loc.head;
	ControllerPointerPose& pointer = loc.pointer;
	
	loc.pose = M;
	
	if (state->ulButtonTouched & ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad)) {
		prop.is_touch_touch = true;
		prop.touch_x = state->rAxis[0].x;
		prop.touch_y = state->rAxis[0].y;
	}
	else {
		prop.is_touch_touch = false;
	}
}



#endif

NAMESPACE_OULU_END
