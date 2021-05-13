#ifndef _EcsCore_TransformUtil_h_
#define _EcsCore_TransformUtil_h_

NAMESPACE_OULU_BEGIN



#if 0



inline vec3 transform(vec3 const& position, mat4 const& matrix) {
    return vec3  (position.x * matrix[0][0] + position.y * matrix[1][0] + position.z * matrix[2][0] + matrix[3][0],
                  position.x * matrix[0][1] + position.y * matrix[1][1] + position.z * matrix[2][1] + matrix[3][1],
                  position.x * matrix[0][2] + position.y * matrix[1][2] + position.z * matrix[2][2] + matrix[3][2]);
}

inline quat make_quaternion_from_yaw_pitch_roll(float yaw, float pitch, float roll) {
    float sr, cr, sp, cp, sy, cy;

    float halfRoll = roll * 0.5f;
    sr = sinf(halfRoll); cr = cosf(halfRoll);

    float halfPitch = pitch * 0.5f;
    sp = sinf(halfPitch); cp = cosf(halfPitch);

    float halfYaw = yaw * 0.5f;
    sy = sinf(halfYaw); cy = cosf(halfYaw);

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

#endif


NAMESPACE_OULU_END

#endif
