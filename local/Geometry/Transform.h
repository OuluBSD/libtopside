#ifndef _Math_Transform_h_
#define _Math_Transform_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


inline vec3 right(const mat4& transform) {
	return { + transform[0][0], + transform[0][1], + transform[0][2] };
}

inline vec3 left(const mat4& transform) {
	return { -transform[0][0], -transform[0][1], -transform[0][2] };
}

inline vec3 up(const mat4& transform) {
	return { + transform[1][0], + transform[1][1], + transform[1][2] };
}

inline vec3 down(const mat4& transform) {
	return { -transform[1][0], -transform[1][1], -transform[1][2] };
}

inline vec3 backward(const mat4& transform) {
	return { + transform[2][0], + transform[2][1], + transform[2][2] };
}

inline vec3 forward(const mat4& transform) {
	return { -transform[2][0], -transform[2][1], -transform[2][2] };
}

inline vec3 position(const mat4& transform) {
	return { + transform[3][0], + transform[3][1], + transform[3][2] };
}

inline quat orientation(const mat4& transform) {
	vec3 baller_position, size, skew;
	quat orientation;
	vec4 persp;
	decompose(transform, size, orientation, baller_position, skew, persp);
	return orientation;
}



inline mat4 remove_scale(const mat4& transform) {
	quat rotation;
	vec3 scale, translation, skew;
	vec4 pers;
	decompose(transform, scale, rotation, translation, skew, pers);
	return toMat4(rotation) * translate(translation);
}




inline quat AxisAngleQuat(vec3 v, float angle) {
	return rotate(identity<quat>(), angle, v);
}

inline vec3 transform(vec3 const& position, mat4 const& matrix) {
	return vec3(position[0] * matrix[0][0] + position[1] * matrix[1][0] + position[2] * matrix[2][0] + matrix[3][0],
				position[0] * matrix[0][1] + position[1] * matrix[1][1] + position[2] * matrix[2][1] + matrix[3][1],
				position[0] * matrix[0][2] + position[1] * matrix[1][2] + position[2] * matrix[2][2] + matrix[3][2]);
}

inline float ConvertToRadians(float angle) {
	return angle / 180.0 * M_PI;
}

inline quat make_quaternion_from_yaw_pitch_roll(float yaw, float pitch, float roll) {
	float sr, cr, sp, cp, sy, cy;
	
	float halfRoll = roll * 0.5f;
	sr = sinf(halfRoll);
	cr = cosf(halfRoll);
	
	float halfPitch = pitch * 0.5f;
	sp = sinf(halfPitch);
	cp = cosf(halfPitch);
	
	float halfYaw = yaw * 0.5f;
	sy = sinf(halfYaw);
	cy = cosf(halfYaw);
	
	return quat(cy * sp * cr + sy * cp * sr,
				sy * cp * cr - cy * sp * sr,
				cy * cp * sr - sy * sp * cr,
				cy * cp * cr + sy * sp * sr);
}

inline mat4 make_mat4_from_yaw_pitch_roll(float yaw, float pitch, float roll) {
	quat q = make_quaternion_from_yaw_pitch_roll(yaw, pitch, roll);
	return toMat4(q);
}

inline mat4 make_mat4_rotation_x(float radians) {
	float c = cosf(radians);
	float s = sinf(radians);
	
	return mat4(1,  0, 0, 0,
				0,  c, s, 0,
				0, -s, c, 0,
				0,  0, 0, 1);
}

NAMESPACE_TOPSIDE_END


#endif

#endif
