#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


vec3 lerp(const vec3& pos, const vec3& tgt_pos, float easing_factor) {
	TODO
}

quat slerp(const quat& orient, const quat& tgt_orient, float easing_factor) {
	TODO
}



mat4 LookAt(const vec3& eye, const vec3& center, const vec3& up) {
    vec3 z = normalize(eye - center);
    vec3 x = normalize(cross(up, z));
    vec3 y = normalize(cross(z,x));
    mat4 minv = identity<mat4>();
    mat4 tr   = identity<mat4>();
    for (int i=0; i<3; i++) {
        minv[0][i] = x[i];
        minv[1][i] = y[i];
        minv[2][i] = z[i];
        tr[i][3] = -center[i];
    }
    minv *= tr;
    return minv;
}

mat4 GetViewport(float x, float y, float w, float h, float depth) {
	mat4 m = identity<mat4>();
	m[0][3] = x + w / 2.f;
	m[1][3] = y + h / 2.f;
	m[2][3] = depth / 2.f;
	
	m[0][0] = w / 2.f;
	m[1][1] = h / 2.f;
	m[2][2] = depth / 2.f;
	return m;
}

void ColorCopy(const RGBA& src, vec3& dst) {
	dst[0] = src.r / 255.0;
	dst[1] = src.g / 255.0;
	dst[2] = src.b / 255.0;
}

void ColorCopy(const RGBA& src, vec4& dst) {
	dst[0] = src.r / 255.0;
	dst[1] = src.g / 255.0;
	dst[2] = src.b / 255.0;
	dst[3] = src.a / 255.0;
}


Size ToSize(const vec2& v) {return Size((int)v[0], (int)v[1]);}
Point ToPoint(const vec2& v) {return Point((int)v[0], (int)v[1]);}
vec3 MakeVec3(float v[4]) {vec3 o; for(int i = 0; i < 3; i++) o[i] = v[i]; return o;}
vec3 MakeVec3(double v[4]) {vec3 o; for(int i = 0; i < 3; i++) o[i] = v[i]; return o;}
vec4 MakeVec4(const vec3& v, float v4) {vec4 o; for(int i = 0; i < 3; i++) o[i] = v[i]; o[3] = v4; return o;}

double GetRadians(double degrees) {return degrees / 360.0 * M_2PI;}
double GetDegrees(double radians) {return radians / M_2PI * 360.0;}


mat4 perspective(float fov, float aspect, float near, float far) {
	mat4 m;
	m.SetProjection(fov, aspect, near, far);
	return m;
}

mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 m;
	m.SetOrtographic(left, right, bottom, top, near, far);
	return m;
}

mat4 ToMat4(const quat& q) {
	mat4 result;
	result.SetIdentity();
	
	double qxx = q[0] * q[0];
	double qyy = q[1] * q[1];
	double qzz = q[2] * q[2];
	double qxz = q[0] * q[2];
	double qxy = q[0] * q[1];
	double qyz = q[1] * q[2];
	double qwx = q[3] * q[0];
	double qwy = q[3] * q[1];
	double qwz = q[3] * q[2];

	result[0][0] = 1.0 - 2.0 * (qyy +  qzz);
	result[0][1] = 2.0       * (qxy + qwz);
	result[0][2] = 2.0       * (qxz - qwy);

	result[1][0] = 2.0       * (qxy - qwz);
	result[1][1] = 1.0 - 2.0 * (qxx +  qzz);
	result[1][2] = 2.0       * (qyz + qwx);

	result[2][0] = 2.0       * (qxz + qwy);
	result[2][1] = 2.0       * (qyz - qwx);
	result[2][2] = 1.0 - 2.0 * (qxx +  qyy);
	
	for(int i = 0; i < 3; i++) {
		result[3][i] = 0;
		result[i][3] = 0;
	}
	result[3][3] = 1;
	
	return result;
}



bool Decompose(const mat4& model_mat, vec3& scale_, quat& orientation, vec3& translation, vec3& skew, vec4& perspective) {
	mat4 local_mat(model_mat);

	if(IsEpsilonEqual(local_mat[3][3], 0.0f, EPSILONf))
		return false;

	for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            local_mat[i][j] /= local_mat[3][3];

	mat4 persp_mat(local_mat);

	for(int i = 0; i < 3; i++)
		persp_mat[i][3] = 0.0f;
	persp_mat[3][3] = 1.0f;

	if(IsEpsilonEqual(persp_mat.GetDeterminant(), 0.0f, EPSILONf))
		return false;

	if( IsEpsilonNotEqual(local_mat[0][3], 0.0f, EPSILONf) ||
		IsEpsilonNotEqual(local_mat[1][3], 0.0f, EPSILONf) ||
		IsEpsilonNotEqual(local_mat[2][3], 0.0f, EPSILONf)) {
		vec4 right_hand_side;
		right_hand_side[0] = local_mat[0][3];
		right_hand_side[1] = local_mat[1][3];
		right_hand_side[2] = local_mat[2][3];
		right_hand_side[3] = local_mat[3][3];

		mat4 inv_persp_mat = persp_mat.GetInverse();
		mat4 trans_inv_persp_mat = inv_persp_mat.GetTransposed();

		perspective = trans_inv_persp_mat * right_hand_side;

		local_mat[0][3] = local_mat[1][3] = local_mat[2][3] = 0.0f;
		local_mat[3][3] = 1.0f;
	}
	else {
		perspective = vec4(0, 0, 0, 1);
	}

	translation = local_mat[3].Splice();
	local_mat[3] = vec4(0, 0, 0, local_mat[3][3]);

	vec3 row[3], p_dum3;

	for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            row[i][j] = local_mat[i][j];

	scale_[0] = row[0].GetLength();

	row[0] = scale(row[0], 1.0f);

	skew[2] = dot(row[0], row[1]);
	row[1] = combine(row[1], row[0], 1.0f, -skew[2]);

	scale_[1] = row[1].GetLength();
	row[1] = scale(row[1], 1.0f);
	skew[2] /= scale_[1];

	skew[1] = dot(row[0], row[2]);
	row[2] = combine(row[2], row[0], 1.0f, -skew[1]);
	skew[0] = dot(row[1], row[2]);
	row[2] = combine(row[2], row[1], 1.0f, -skew[0]);

	scale_[2] = row[2].GetLength();
	row[2] = scale(row[2], 1.0f);
	skew[1] /= scale_[2];
	skew[0] /= scale_[2];

	p_dum3 = cross(row[1], row[2]);
	if (dot(row[0], p_dum3) < 0) {
		for(int i = 0; i < 3; i++)
		{
			scale_[i] *= -1.0f;
			row[i] *= -1.0f;
		}
	}

	int i, j, k = 0;
	float root, trace = row[0][0] + row[1][1] + row[2][2];
	if(trace > 0.0f)
	{
		root = sqrt(trace + 1.0f);
		orientation[3] = 0.5f * root;
		root = 0.5f / root;
		orientation[0] = root * (row[1][2] - row[2][1]);
		orientation[1] = root * (row[2][0] - row[0][2]);
		orientation[2] = root * (row[0][1] - row[1][0]);
	}
	else {
		static int Next[3] = {1, 2, 0};
		i = 0;
		if(row[1][1] > row[0][0]) i = 1;
		if(row[2][2] > row[i][i]) i = 2;
		j = Next[i];
		k = Next[j];

		root = sqrt(row[i][i] - row[j][j] - row[k][k] + 1.0f);

		orientation[i] = 0.5f * root;
		root = 0.5f / root;
		orientation[j] = root * (row[i][j] + row[j][i]);
		orientation[k] = root * (row[i][k] + row[k][i]);
		orientation[3] = root * (row[j][k] - row[k][j]);
	}

	return true;
}

vec3 combine(const vec3& a, const vec3& b, float ascl, float bscl) {
	return (a * ascl) + (b * bscl);
}

mat4 GetEulerAngleYXZ(const vec3& in) {
	float yaw = in[2];
	float pitch = in[1];
	float roll = in[0];
	float ch = cos(yaw);
	float sh = sin(yaw);
	float cp = cos(pitch);
	float sp = sin(pitch);
	float cb = cos(roll);
	float sb = sin(roll);

	mat4 r;
	r[0][0] = ch * cb + sh * sp * sb;
	r[0][1] = sb * cp;
	r[0][2] = -sh * cb + ch * sp * sb;
	r[0][3] = 0;
	r[1][0] = -ch * sb + sh * sp * cb;
	r[1][1] = cb * cp;
	r[1][2] = sb * sh + ch * sp * cb;
	r[1][3] = 0;
	r[2][0] = sh * cp;
	r[2][1] = -sp;
	r[2][2] = ch * cp;
	r[2][3] = 0;
	r[3][0] = 0;
	r[3][1] = 0;
	r[3][2] = 0;
	r[3][3] = 1;
	return r;
}

mat4 GetEulerAngleYX(const vec3& in) {
	float angle_y = in[2];
	float angle_x = in[1];
	
	float cos_x = cos(angle_x);
	float sin_x = sin(angle_x);
	float cos_y = cos(angle_y);
	float sin_y = sin(angle_y);

	return mat4 {
		{cos_y,          0,            -sin_y,    0},
		{sin_y * sin_x,  cos_x, cos_y * sin_x,    0},
		{sin_y * cos_x, -sin_x, cos_y * cos_x,    0},
		{0,              0,             0,        1}};
	
}

mat4 rotate(mat4 const& m, float angle, vec3 const& v) {
	const float a = angle;
	const float c = cos(a);
	const float s = sin(a);
	
	vec3 axis(normalize(v));
	vec3 temp(axis * (1.0f - c));
	
	mat4 rot;
	rot[0][0] = c + temp[0] * axis[0];
	rot[0][1] = temp[0] * axis[1] + s * axis[2];
	rot[0][2] = temp[0] * axis[2] - s * axis[1];
	
	rot[1][0] = temp[1] * axis[0] - s * axis[2];
	rot[1][1] = c + temp[1] * axis[1];
	rot[1][2] = temp[1] * axis[2] + s * axis[0];
	
	rot[2][0] = temp[2] * axis[0] + s * axis[1];
	rot[2][1] = temp[2] * axis[1] - s * axis[0];
	rot[2][2] = c + temp[2] * axis[2];
	
	mat4 res;
	res[0] = m[0] * rot[0][0] + m[1] * rot[0][1] + m[2] * rot[0][2];
	res[1] = m[0] * rot[1][0] + m[1] * rot[1][1] + m[2] * rot[1][2];
	res[2] = m[0] * rot[2][0] + m[1] * rot[2][1] + m[2] * rot[2][2];
	res[3] = m[3];
	return res;
}

quat make_quat_from_axis_angle(vec3 v, float angle) {
	double s = sinf(angle * 0.5);
	quat r;
	r[0] = v[0] * s;
	r[1] = v[1] * s;
	r[2] = v[2] * s;
	r[3] = cosf(angle * 0.5);
	return r;
}

vec3 transform(const vec3& v, const quat& q) {
	// https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
	
	// Extract the vector part of the quaternion
    vec3 u = q.data.Splice();

    // Extract the scalar part of the quaternion
    float s = q.data[3];

    // Do the math
    vec3 vprime = u * (2.0f * dot(u, v))
          + v * ((s*s - dot(u, u)))
          + cross(u, v) * (2.0f * s);
    return vprime;
}

mat4 make_mat4_from_quat(const quat& q) {
	mat4 m1{
		{q[3], q[2], -q[1], q[0]},
		{-q[2], q[3], q[0], q[1]},
		{q[1], -q[0], q[3], q[2]},
		{-q[0], -q[1], -q[2], q[3]}
	};
	
	mat4 m2{
		{q[3], q[2], -q[1], -q[0]},
		{-q[2], q[3], q[0], -q[1]},
		{q[1], -q[0], q[3], -q[2]},
		{q[0], q[1], q[2], q[3]}
	};
	
	return m1 * m2;
}

quat make_quat_from_yaw_pitch_roll(float yaw, float pitch, float roll)
{
    float sr, cr, sp, cp, sy, cy;

    float half_roll = roll * 0.5f;
    sr = sinf(half_roll);
    cr = cosf(half_roll);

    float half_pitch = pitch * 0.5f;
    sp = sinf(half_pitch);
    cp = cosf(half_pitch);

    float half_yaw = yaw * 0.5f;
    sy = sinf(half_yaw);
    cy = cosf(half_yaw);

    return quat(
		cy * sp * cr + sy * cp * sr,
		sy * cp * cr - cy * sp * sr,
		cy * cp * sr - sy * sp * cr,
		cy * cp * cr + sy * sp * sr
	);
}

mat4 make_mat4_rotation_x(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);
	
	return mat4{
		{1,  0, 0, 0},
		{0,  c, s, 0},
		{0, -s, c, 0},
		{0,  0, 0, 1}
	};
}

mat4 make_mat4_rotation_y(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);
	return mat4{
		{c, 0, -s, 0},
		{0, 1,  0, 0},
		{s, 0,  c, 0},
		{0, 0,  0, 1}
	};
}

mat4 make_mat4_rotation_z(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);
	return mat4{
		{c, s, 0, 0},
		{-s, c, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
}

mat4 make_mat4_translation(const vec3& position) {
    return mat4{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{position[0], position[1], position[2], 1}
	};
}

quat make_quat_from_rotation_matrix(const mat4& m) {
    if (m[1][1] + m[2][2] + m[3][3] > 0.0f)
    {
        float s = sqrtf(1.0f + m[1][1] + m[2][2] + m[3][3]);
        float inv_s = 0.5f / s;

        return quat((m[2][3] - m[3][2]) * inv_s,
                   (m[3][1] - m[1][3]) * inv_s,
                   (m[1][2] - m[2][1]) * inv_s,
                   s * 0.5f);
    }
    else if (m[1][1] >= m[2][2] && m[1][1] >= m[3][3])
    {
        float s = sqrtf(1.0f + m[1][1] - m[2][2] - m[3][3]);
        float inv_s = 0.5f / s;

        return quat(0.5f * s,
                    (m[1][2] + m[2][1]) * inv_s,
                    (m[1][3] + m[3][1]) * inv_s,
                    (m[2][3] - m[3][2]) * inv_s);
    }
    else if (m[2][2] > m[3][3])
    {
        float s = sqrtf(1.0f + m[2][2] - m[1][1] - m[3][3]);
        float inv_s = 0.5f / s;

        return quat((m[2][1] + m[1][2]) * inv_s,
                    0.5f * s,
                    (m[3][2] + m[2][3]) * inv_s,
                    (m[3][1] - m[1][3]) * inv_s);
    }
    else
    {
        float s = sqrtf(1.0f + m[3][3] - m[1][1] - m[2][2]);
        float inv_s = 0.5f / s;

        return quat((m[3][1] + m[1][3]) * inv_s,
                    (m[3][2] + m[2][3]) * inv_s,
                    0.5f * s,
                    (m[1][2] - m[2][1]) * inv_s);
    }
}


NAMESPACE_TOPSIDE_END
