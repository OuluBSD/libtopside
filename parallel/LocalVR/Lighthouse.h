#ifndef __OpenVR_LIGHTHOUSE_H__
#define __OpenVR_LIGHTHOUSE_H__


NAMESPACE_HMD_BEGIN


struct lighthouse_rotor_calibration {
	float tilt;
	float phase;
	float curve;
	float gibphase;
	float gibmag;
};

struct lighthouse_base_calibration {
	struct lighthouse_rotor_calibration rotor[2];
};

struct lighthouse_frame {
	uint32_t sync_timestamp;
	uint32_t sync_duration;
	uint32_t sync_ids;
	uint32_t sweep_ids;
	uint32_t sweep_offset[32];
	uint16_t sweep_duration[32];
	uint32_t frame_duration;
};

struct lighthouse_base {
	int data_sync;
	int data_word;
	int data_bit;
	uint8_t ootx[40];

	int firmware_version;
	uint32_t serial;
	struct lighthouse_base_calibration calibration;
	vec3 gravity;
	char channel;
	int model_id;
	int reset_count;

	uint32_t last_sync_timestamp;
	int active_rotor;

	struct lighthouse_frame frame[2];
};

struct lighthouse_pulse {
	uint32_t timestamp;
	uint16_t duration;
	uint8_t id;
};

struct lighthouse_sensor {
	struct lighthouse_pulse sync;
	struct lighthouse_pulse sweep;
};

struct lighthouse_watchman {
	unsigned int id;
	const char *name;
	struct tracking_model model;
	bool base_visible;
	struct lighthouse_base base[2];
	struct lighthouse_base *active_base;
	uint32_t seen_by;
	uint32_t last_timestamp;
	struct lighthouse_sensor sensor[32];
	struct lighthouse_pulse last_sync;
	bool sync_lock;
};

void lighthouse_watchman_handle_pulse(struct lighthouse_watchman *watchman,
				      uint8_t id, uint16_t duration,
				      uint32_t timestamp);
void lighthouse_watchman_init(struct lighthouse_watchman *watchman);


NAMESPACE_HMD_END


#endif
