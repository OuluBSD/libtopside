#include "LocalVR.h"


NAMESPACE_HMD_BEGIN


float f16_to_float(uint16 f16)
{
	unsigned int sign = f16 >> 15;
	unsigned int exponent = (f16 >> 10) & 0x1f;
	unsigned int mantissa = f16 & 0x3ff;
	union {
		float f32;
		uint32 u32;
	} u;

	if (exponent == 0) {
		if (!mantissa) {
			/* zero */
			u.u32 = sign << 31;
		} else {
			/* subnormal */
			exponent = 127 - 14;
			mantissa <<= 23 - 10;
			/*
			 * convert to normal representation:
			 * shift up mantissa and drop MSB
			 */
			while (!(mantissa & (1 << 23))) {
				mantissa <<= 1;
				exponent--;
			}
			mantissa &= 0x7fffffu;
			u.u32 = (sign << 31) | (exponent << 23) | mantissa;
		}
	} else if (exponent < 31) {
		/* normal */
		exponent += 127 - 15;
		mantissa <<= 23 - 10;
		u.u32 = (sign << 31) | (exponent << 23) | mantissa;
	} else if (mantissa == 0) {
		/* infinite */
		u.u32 = (sign << 31) | (255 << 23);
	} else {
		/* NaN */
		u.u32 = 0x7fffffffu;
	}
	return u.f32;
}

/*
 * Returns the rotation around the normalized vector axis, about the given
 * angle in quaternion q.
 */
void quat_from_axis_angle(quat *q, const vec3 *axis, double angle)
{
	const double half_angle = angle * 0.5;
	const double sin_half_angle = sin(half_angle);

	q->data[3] = cos(half_angle);
	q->data[0] = sin_half_angle * axis->data[0];
	q->data[1] = sin_half_angle * axis->data[1];
	q->data[2] = sin_half_angle * axis->data[2];
}

/*
 * Returns the rotation along the shortest arc from normalized vector a to
 * normalized vector b in quaternion q.
 */
void quat_from_axes(quat *q, const vec3 *a, const vec3 *b)
{
	vec3 w;

	vec3_cross(&w, a, b);

	q->data[3] = 1.0 + vec3_dot(a, b);
	q->data[0] = w[0];
	q->data[1] = w[1];
	q->data[2] = w[2];

	quat_normalize(q);
}

/*
 * Returns the rotation for a gyro reading after timestep dt in quaternion q.
 * This is an approximation of
 *	q->data[3] = cos(x) * cos(y) * cos(z) + sin(x) * sin(y) * sin(z);
 *	q->data[0] = sin(x) * cos(y) * cos(z) - cos(x) * sin(y) * sin(z);
 *	q->data[1] = cos(x) * sin(y) * cos(z) + sin(x) * cos(y) * sin(z);
 *	q->data[2] = cos(x) * cos(y) * sin(z) - sin(x) * sin(y) * cos(z);
 * for small time steps, where the half angles x, y, z are assumed to be small.
 */
void quat_from_gyro(quat *q, const vec3 *gyro, double dt)
{
	const double scale = 0.5 * dt;
	const double x = gyro->data[0] * scale;
	const double y = gyro->data[1] * scale;
	const double z = gyro->data[2] * scale;

	q->data[3] = 1.0 + x * y * z;
	q->data[0] = x - y * z;
	q->data[1] = y + x * z;
	q->data[2] = z - x * y;
}


NAMESPACE_HMD_END

