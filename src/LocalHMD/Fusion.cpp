#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


void InitFusion(Fusion* me)
{
	memset(me, 0, sizeof(Fusion));
	me->orient[3] = 1.0f;

	InitFilterQueue(&me->mag_fq, 20);
	InitFilterQueue(&me->accel_fq, 20);
	InitFilterQueue(&me->ang_vel_fq, 20);

	me->flags = FF_USE_GRAVITY;
	me->grav_gain = 0.05f;
}

void UpdateFusion(Fusion* me, float dt, const vec3* ang_vel, const vec3* accel, const vec3* mag)
{
	me->ang_vel = *ang_vel;
	me->accel = *accel;
	me->raw_mag = *mag;
	me->mag = *mag;

	vec3 world_accel;
	oquat_get_rotated(&me->orient, accel, &world_accel);

	me->iterations += 1;
	me->time += dt;

	AddFilterQueue(&me->mag_fq, mag);
	AddFilterQueue(&me->accel_fq, &world_accel);
	AddFilterQueue(&me->ang_vel_fq, ang_vel);

	float ang_vel_length = ang_vel->GetLength();

	if(ang_vel_length > 0.0001f){
		vec3 rot_axis =
			{{ ang_vel->data[0] / ang_vel_length, ang_vel->data[1] / ang_vel_length, ang_vel->data[2] / ang_vel_length }};

		float rot_angle = ang_vel_length * dt;

		quat delta_orient;
		oquat_init_axis(&delta_orient, &rot_axis, rot_angle);

		oquat_mult_me(&me->orient, &delta_orient);
	}

	// gravity correction
	if(me->flags & FF_USE_GRAVITY){
		const float gravity_tolerance = .4f, ang_vel_tolerance = .1f;
		const float min_tilt_error = 0.05f, max_tilt_error = 0.01f;

		// if the device is within tolerance levels, count this as the device is level and add to the counter
		// otherwise reset the counter and start over

		me->device_level_count =
			fabsf(ovec3_get_length(accel) - 9.82f) < gravity_tolerance * 2.0f && ang_vel_length < ang_vel_tolerance
			? me->device_level_count + 1 : 0;

		// device has been level for long enough, grab mean from the accelerometer filter queue (last n values)
		// and use for correction

		if(me->device_level_count > 50){
			me->device_level_count = 0;

			vec3 accel_mean;
			GetMeanFilterQueue(&me->accel_fq, &accel_mean);
			if (ovec3_get_length(&accel_mean) - 9.82f < gravity_tolerance)
			{
				// Calculate a cross product between what the device
				// thinks is up and what gravity indicates is down.
				// The values are optimized of what we would get out
				// from the cross product.
				vec3 tilt = {{accel_mean[2], 0, -accel_mean[0]}};

				ovec3_normalize_me(&tilt);
				ovec3_normalize_me(&accel_mean);

				vec3 up = {{0, 1.0f, 0}};
				float tilt_angle = ovec3_get_angle(&up, &accel_mean);

				if(tilt_angle > max_tilt_error){
					me->grav_error_angle = tilt_angle;
					me->grav_error_axis = tilt;
				}
			}
		}

		// perform gravity tilt correction
		if(me->grav_error_angle > min_tilt_error){
			float use_angle;
			// if less than 2000 iterations have passed, set the up axis to the correction value outright
			if(me->iterations < 2000){
				use_angle = -me->grav_error_angle;
				me->grav_error_angle = 0;
			}

			// otherwise try to correct
			else {
				use_angle = -me->grav_gain * me->grav_error_angle * 0.005f * (5.0f * ang_vel_length + 1.0f);
				me->grav_error_angle += use_angle;
			}

			// perform the correction
			quat corr_quat, old_orient;
			oquat_init_axis(&corr_quat, &me->grav_error_axis, use_angle);
			old_orient = me->orient;

			oquat_mult(&corr_quat, &old_orient, &me->orient);
		}
	}

	// mitigate drift due to floating point
	// inprecision with quat multiplication.
	me->orient.Normalize();
}


NAMESPACE_HMD_END

