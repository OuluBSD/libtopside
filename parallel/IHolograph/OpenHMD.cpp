#include "IHolograph.h"

#if defined flagOPENHMD && ((defined flagLINUX) || (defined flagFREEBSD))


NAMESPACE_PARALLEL_BEGIN

bool HoloOpenHMD::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.ctx = ohmd_ctx_create();
	int num_devices = ohmd_ctx_probe(dev.ctx);
	if(num_devices < 0){
		LOG("HoloOpenHMD::SinkDevice_Initialize: error: failed to probe devices: " << ohmd_ctx_get_error(dev.ctx));
		return false;
	}

	dev.settings = ohmd_device_settings_create(dev.ctx);

	// If OHMD_IDS_AUTOMATIC_UPDATE is set to 0, ohmd_ctx_update() must be called at least 10 times per second.
	// It is enabled by default.

	int auto_update = 1;
	ohmd_device_settings_seti(dev.settings, OHMD_IDS_AUTOMATIC_UPDATE, &auto_update);

	dev.hmd = ohmd_list_open_device_s(dev.ctx, 0, dev.settings);
	if(!dev.hmd){
		LOG("HoloOpenHMD::SinkDevice_Initialize: error: failed to open device: " << ohmd_ctx_get_error(dev.ctx));
		return false;
	}
	ohmd_device_geti(dev.hmd, OHMD_SCREEN_HORIZONTAL_RESOLUTION, &dev.screen_sz.cx);
	ohmd_device_geti(dev.hmd, OHMD_SCREEN_VERTICAL_RESOLUTION, &dev.screen_sz.cy);
	float ipd;
	ohmd_device_getf(dev.hmd, OHMD_EYE_IPD, &ipd);
	float viewport_scale[2];
	float distortion_coeffs[4];
	float aberr_scale[3];
	float sep;
	float left_lens_center[2];
	float right_lens_center[2];
	
	//viewport is half the screen
	ohmd_device_getf(dev.hmd, OHMD_SCREEN_HORIZONTAL_SIZE, &(viewport_scale[0]));
	viewport_scale[0] /= 2.0f;
	ohmd_device_getf(dev.hmd, OHMD_SCREEN_VERTICAL_SIZE, &(viewport_scale[1]));
	
	//distortion coefficients
	ohmd_device_getf(dev.hmd, OHMD_UNIVERSAL_DISTORTION_K, &(distortion_coeffs[0]));
	ohmd_device_getf(dev.hmd, OHMD_UNIVERSAL_ABERRATION_K, &(aberr_scale[0]));
	
	//calculate lens centers (assuming the eye separation is the distance between the lens centers)
	ohmd_device_getf(dev.hmd, OHMD_LENS_HORIZONTAL_SEPARATION, &sep);
	ohmd_device_getf(dev.hmd, OHMD_LENS_VERTICAL_POSITION, &(left_lens_center[1]));
	ohmd_device_getf(dev.hmd, OHMD_LENS_VERTICAL_POSITION, &(right_lens_center[1]));
	left_lens_center[0] = viewport_scale[0] - sep/2.0f;
	right_lens_center[0] = sep/2.0f;
	
	//assume calibration was for lens view to which ever edge of screen is further away from lens center
	float warp_scale = (left_lens_center[0] > right_lens_center[0]) ? left_lens_center[0] : right_lens_center[0];
	float warp_adj = 1.0f;

	ohmd_device_settings_destroy(dev.settings);

	ohmd_gets(OHMD_GLSL_DISTORTION_VERT_SRC, &dev.vertex);
	ohmd_gets(OHMD_GLSL_DISTORTION_FRAG_SRC, &dev.fragment);
	
	LOG("OpenHMD vertex shader:\n" << GetLineNumStr(dev.vertex) << "\n");
	LOG("OpenHMD fragment shader:\n" << GetLineNumStr(dev.fragment) << "\n");
	
	return true;
}

bool HoloOpenHMD::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	
	return true;
}

bool HoloOpenHMD::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	
	return true;
}

void HoloOpenHMD::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void HoloOpenHMD::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	ohmd_ctx_destroy(dev.ctx);
}

bool HoloOpenHMD::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

bool HoloOpenHMD::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	TODO
}

void HoloOpenHMD::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	ohmd_ctx_update(dev.ctx);
	
	// set hmd rotation, for left eye.
	float l_proj[16];
	float l_view[16];
	ohmd_device_getf(dev.hmd, OHMD_LEFT_EYE_GL_PROJECTION_MATRIX, l_proj);
	ohmd_device_getf(dev.hmd, OHMD_LEFT_EYE_GL_MODELVIEW_MATRIX, l_view);
	
	// set hmd rotation, for right eye.
	float r_proj[16];
	float r_view[16];
	ohmd_device_getf(dev.hmd, OHMD_RIGHT_EYE_GL_PROJECTION_MATRIX, r_proj);
	ohmd_device_getf(dev.hmd, OHMD_RIGHT_EYE_GL_MODELVIEW_MATRIX, r_view);
	
	dev.l_proj.Set(l_proj);
	dev.l_view.Set(l_view);
	dev.r_proj.Set(r_proj);
	dev.r_view.Set(r_view);
	
}

bool HoloOpenHMD::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

