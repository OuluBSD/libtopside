#ifndef _LocalHMD_FUSION_H
#define _LocalHMD_FUSION_H


NAMESPACE_HMD_BEGIN


#define FF_USE_GRAVITY 1

typedef struct {
	int state;
	
	quat orient;   // orientation
	vec3 accel;    // acceleration
	vec3 ang_vel;  // angular velocity
	vec3 mag;      // magnetometer
	vec3 raw_mag;  // raw magnetometer values
	
	int iterations;
	float time;
	
	int flags;
	
	// filter queues for magnetometer, accelerometers and angular velocity
	FilterQueue mag_fq, accel_fq, ang_vel_fq;
	
	// gravity correction
	int device_level_count;
	float grav_error_angle;
	vec3 grav_error_axis;
	float grav_gain; // amount of correction
} Fusion;

void InitFusion(Fusion* me);
void UpdateFusion(Fusion* me, float dt, const vec3* ang_vel, const vec3* accel, const vec3* mag_field);


NAMESPACE_HMD_END


#endif
