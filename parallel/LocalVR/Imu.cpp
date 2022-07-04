#include "LocalVR.h"


NAMESPACE_HMD_BEGIN


enum pose_mode {
	ACCEL_ONLY,
	GYRO_ONLY,
};

enum pose_mode mode = GYRO_ONLY;

/*
 * Find the quaternion that rotates the local up vector back to where the
 * accelerometer points.
 */
void quat_from_accel(quat *q, vec3 *accel)
{
	vec3 a = *accel;
	vec3 up = { 0.0, 1.0, 0.0 };

	vec3_normalize(&a);
	quat_from_axes(q, &a, &up);
}

/*
 * Updates the rotational part of the pose, given a time interval and angular
 * velocity measurement.
 */
void pose_update(double dt, struct dpose *pose, struct imu_sample *sample)
{
	quat q, dq;

	switch (mode) {
	case ACCEL_ONLY:
		quat_from_accel(&q, &sample->acceleration);
		break;
	case GYRO_ONLY:
		quat_from_gyro(&dq, &sample->angular_velocity, dt);
		quat_mult(&q, &pose->rotation, &dq);
		quat_normalize(&q);
		break;
	}

	pose->rotation = q;
}


NAMESPACE_HMD_END

