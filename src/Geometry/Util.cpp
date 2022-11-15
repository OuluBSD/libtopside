#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


vec3 Lerp(const vec3& pos, const vec3& tgt_pos, float easing_factor) {
	ASSERT(easing_factor >= 0.f && easing_factor <= 1.f);
	return pos * (1.0f - easing_factor) + (tgt_pos * easing_factor);
}

quat Slerp(const quat& orient, const quat& tgt_orient, float easing_factor) {
	quat z = tgt_orient;
	float cos_theta = Dot(orient, tgt_orient);
	
	if (cos_theta < 0.0f) {
		z = -tgt_orient;
		cos_theta = -cos_theta;
	}

	if (cos_theta > 1.0f - std::numeric_limits<float>::epsilon()) {
		return Mix(orient, z, easing_factor);
	}
	else {
		float angle = acos(cos_theta);
		return (
			orient * sin((1.0f - easing_factor) * angle) +
			z * sin(easing_factor * angle)) / sin(angle);
	}
}



mat4 LookAt(const vec3& eye_, const vec3& center_, const vec3& up_) {
    mat4 m = zero<mat4>();
    
    vec3 eye = eye_;
    vec3 center = center_;
    vec3 up = up_;
    
    #if IS_NEGATIVE_Z
    vec3 z = Normalize(eye - center);
    vec3 x = Normalize(Cross(up, z));
    vec3 y = Cross(z,x);
    #else
    vec3 z = -Normalize(eye - center);
    vec3 x = -Normalize(Cross(up, -z));
    vec3 y = Cross(-z,-x);
    #endif
    
    
    for (int i=0; i<3; i++) {
        m[i][0] = x[i];
        m[i][1] = y[i];
        m[i][2] = z[i];
    }
    
    m[3][0] = -Dot(x, eye_);
    m[3][1] = -Dot(y, eye_);
    m[3][2] = -Dot(z, eye_);
    
    m[3][3] = 1.0f;
    
    return m;
}

mat4 GetViewport(const ViewportParams& vp) {
	return GetViewport(vp.x, vp.y, vp.w, vp.h, vp.max_depth);
}

mat4 GetViewport(float x, float y, float w, float h, float depth) {
	mat4 m = zero<mat4>();
	m[0][3] = x + w / 2.f;
	m[1][3] = y + h / 2.f;
	m[2][3] = depth / 2.f;

	m[0][0] = w / 2.f;
	m[1][1] = h / 2.f;
	m[2][2] = depth / 2.f;
	m[3][3] = 1.0f;
	return m;
}

void ColorCopy(const RGBA& src, vec3& dst) {
	dst[0] = src.r / 255.0f;
	dst[1] = src.g / 255.0f;
	dst[2] = src.b / 255.0f;
}

void ColorCopy(const RGBA& src, vec4& dst) {
	dst[0] = src.r / 255.0f;
	dst[1] = src.g / 255.0f;
	dst[2] = src.b / 255.0f;
	dst[3] = src.a / 255.0f;
}


Size ToSize(const vec2& v) {return Size((int)v[0], (int)v[1]);}
Point ToPoint(const vec2& v) {return Point((int)v[0], (int)v[1]);}
vec3 MakeVec3(float v[4]) {vec3 o; for(int i = 0; i < 3; i++) o[i] = v[i]; return o;}
vec3 MakeVec3(double v[4]) {vec3 o; for(int i = 0; i < 3; i++) o[i] = (float)v[i]; return o;}
vec4 MakeVec4(const vec3& v, float v4) {vec4 o; for(int i = 0; i < 3; i++) o[i] = v[i]; o[3] = v4; return o;}

double GetRadians(double degrees) {return degrees / 360.0 * M_2PI;}
double GetDegrees(double radians) {return radians / M_2PI * 360.0;}


mat4 Perspective(float half_fov_rad, float aspect, float near, float far) {
	mat4 m;
	m.SetPerspective(half_fov_rad, aspect, near, far);
	return m;
}

mat4 Ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 m;
	m.SetOrtographic(left, right, bottom, top, near, far);
	return m;
}


bool Decompose(const mat4& model_mat, vec3& scale_, quat& orientation, vec3& translation, vec3& skew, vec4& perspective) {
	mat4 local_mat(model_mat);

	#if !IS_NEGATIVE_Z && !IS_CW_ANGLE
	ChangeZConvention(local_mat);
	#endif

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

	row[0] = Scale(row[0], 1.0f);

	skew[2] = Dot(row[0], row[1]);
	row[1] = Combine(row[1], row[0], 1.0f, -skew[2]);

	scale_[1] = row[1].GetLength();
	row[1] = Scale(row[1], 1.0f);
	skew[2] /= scale_[1];

	skew[1] = Dot(row[0], row[2]);
	row[2] = Combine(row[2], row[0], 1.0f, -skew[1]);
	skew[0] = Dot(row[1], row[2]);
	row[2] = Combine(row[2], row[1], 1.0f, -skew[0]);

	scale_[2] = row[2].GetLength();
	row[2] = Scale(row[2], 1.0f);
	skew[1] /= scale_[2];
	skew[0] /= scale_[2];

	p_dum3 = Cross(row[1], row[2]);
	if (Dot(row[0], p_dum3) < 0) {
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

	#if !IS_NEGATIVE_Z && !IS_CW_ANGLE
	orientation[2] = -orientation[2];
	#endif
	
	return true;
}


mat4 Recompose(const vec3& scale, const quat& orientation, const vec3& translation, const vec3& skew, const vec4& perspective) {
	mat4 m = QuatMat(orientation);
    
    m[0][3] = perspective[0];
    m[1][3] = perspective[1];
    m[2][3] = perspective[2];
    m[3][3] = perspective[3];
    
	m[3][0] = translation[0];
	m[3][1] = translation[1];
	m[3][2] = translation[2];
	
    
    mat4 tmp;
    tmp.SetIdentity();
    if (skew[0]) {
        tmp[2][1] = skew[0];
		m = m * tmp;
		tmp[2][1] = 0;
    }
    
    if (skew[1]) {
        tmp[2][0] = skew[1];
		m = m * tmp;
        tmp[2][0] = 0;
    }
    
    if (skew[2]) {
        tmp[1][0] = skew[2];
		m = m * tmp;
        tmp[1][0] = 0;
    }
    
    m = m * Scale(scale);

	return m;
}

vec3 Combine(const vec3& a, const vec3& b, float ascl, float bscl) {
	return (a * ascl) + (b * bscl);
}

mat4 GetEulerAngleYXZ(const vec3& in) {
	float yaw = in[2];
	float pitch = in[1];
	float roll = in[0];
	
	#if IS_NEGATIVE_Z
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
	
	#else
	
	return AxesMat(yaw, pitch, roll);
	
	#endif
}

mat4 GetEulerAngleYX(const vec3& in) {
	#if IS_NEGATIVE_Z
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
	#else
	
	float yaw = in[2];
	float pitch = in[1];
	return AxesMat(yaw, pitch, 0);
	
	#endif
}

mat4 Rotate(mat4 const& m, float angle, vec3 const& v) {
	const float a = angle;
	const float c = cos(a);
	const float s = sin(a);
	
	vec3 axis(Normalize(v));
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

quat AxisAngleQuat(const vec3& v, float angle) {
	double s = sinf(angle * 0.5);
	quat r;
	r[0] = v[0] * s;
	r[1] = v[1] * s;
	r[2] = v[2] * s;
	r[3] = cosf(angle * 0.5);
	#if IS_CW_ANGLE
	r[2] = -r[2];
	#endif
	return r;
}

vec3 VectorTransform(const vec3& v, const quat& q) {
	#if IS_NEGATIVE_Z
	// https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
	
	// Extract the vector part of the quaternion
    vec3 u = q.data.Splice();

    // Extract the scalar part of the quaternion
    float s = q.data[3];

    // Do the math
    vec3 vprime = u * (2.0f * Dot(u, v))
          + v * ((s*s - Dot(u, u)))
          + Cross(u, v) * (2.0f * s);
    return vprime;
    #else
    mat4 m = QuatMat(q);
    return (v.Embed() * m).Splice();
    #endif
}
quat AxesQuat(float yaw, float pitch, float roll)
{
	//return MatrixUtils::orientation(YawPitchRoll(yaw, pitch, roll));
    float sr, cr, sp, cp, sy, cy;
	
	#if IS_CW_ANGLE
	roll = -roll;
	#endif
	
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


quat AxesQuat(const vec3& axes) {
	return AxesQuat(axes.data[0], axes.data[1], axes.data[2]);
}

mat4 XRotation(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);
	
	#if IS_NEGATIVE_Z || IS_CW_ANGLE
	return mat4{
		{1,  0, 0, 0},
		{0,  c, s, 0},
		{0, -s, c, 0},
		{0,  0, 0, 1}
	};
	#else
	return mat4{
		{1,  0, 0, 0},
		{0,  c, -s, 0},
		{0,  s, c, 0},
		{0,  0, 0, 1}
	};
	#endif
}

mat4 YRotation(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);
	#if IS_NEGATIVE_Z || IS_CW_ANGLE
	return mat4{
		{c, 0, -s, 0},
		{0, 1,  0, 0},
		{s, 0,  c, 0},
		{0, 0,  0, 1}
	};
	#else
	return mat4{
		{ c, 0,  s, 0},
		{ 0, 1,  0, 0},
		{-s, 0,  c, 0},
		{ 0, 0,  0, 1}
	};
	#endif
}

mat4 ZRotation(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);
	#if IS_NEGATIVE_Z
	return mat4{
		{c, s, 0, 0},
		{-s, c, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	#elif IS_CW_ANGLE
	return mat4{
		{c, -s, 0, 0},
		{s, c, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	#else
	return mat4{
		{-c, s, 0, 0},
		{-s, -c, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	#endif
}

mat4 Translate(const vec3& position) {
    return mat4{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{position.data[0], position.data[1], position.data[2], 1}
	};
}

mat4 Scale(const vec3& scale) {
    return mat4{
		{scale.data[0],	0,				0,				0},
		{0,				scale.data[1],	0,				0},
		{0,				0,				scale.data[2],	0},
		{0,				0,				0,				1}
	};
}

mat4 AxesMat(float yaw, float pitch, float roll) {
	return QuatMat(AxesQuat(yaw, pitch, roll));
}

mat4 AxesMat(const vec3& axes) {
	return QuatMat(AxesQuat(axes));
}

vec3 AxesDir(float yaw, float pitch) {
	#if IS_NEGATIVE_Z
	float len = cos(pitch);
	return vec3(
		len * -sin(yaw),
		sin(pitch),
		len * -cos(yaw));
	#elif IS_CW_ANGLE
	float len = cos(pitch);
	return vec3(
		len * -sin(-yaw),
		sin(pitch),
		len * cos(-yaw));
	#else
	float len = cos(pitch);
	return vec3(
		len * -sin(yaw),
		sin(pitch),
		len * cos(yaw));
	#endif
}

vec3 AxesDirRoll(float pitch, float roll) {
	mat4 pitch_m = XRotation(pitch);
	mat4 roll_m = ZRotation(roll);
	mat4 m = roll_m * pitch_m;
	vec3 dir = (m * VEC_FWD4).Splice();
	return dir;
}

void DirAxes(vec3 dir, float& yaw, float& pitch) {
	dir.Normalize();
	pitch = asin(dir.data[1]);
	#if IS_NEGATIVE_Z
	yaw = -atan2(dir.data[2], dir.data[0]);
	yaw -= M_PI_2;
	#else
	yaw = atan2(dir.data[2], dir.data[0]);
	yaw -= M_PI_2;
	#endif
	yaw = yaw < -M_PI ? yaw + M_2PI : yaw;
}

void DirAxes(vec3 dir, vec3& axes) {
	DirAxes(dir, axes.data[0], axes.data[1]);
	axes[2] = 0;
}

vec3 GetDirAxes(const vec3& dir) {
	vec3 axes;
	DirAxes(dir, axes.data[0], axes.data[1]);
	return axes;
}


axes2 GetDirAxesRoll(vec3 dir) {
	if (dir.data[0] == 0 && dir.data[1] == 0)
		return axes2(0,0);
	dir.Normalize();
	float roll = -atan2(dir.data[0], dir.data[1]);
	vec3 fwd_dir = (dir.Embed() * ZRotation(-roll)).Splice();
	float pitch = asin(fwd_dir.data[1]);
	return axes2(pitch, roll);
}

vec3 GetAxesDir(const axes2& ax) {
	return AxesDir(ax.data[0], ax.data[1]);
}

void CameraObject(
	const vec3& eye, const vec3& eye_dir, const vec3& eye_up,
	float obj_yaw_diff, float obj_pitch_diff, float obj_dist,
	vec3& position) {
	
	// get z-vector from eye direction
	vec3 zv = eye_dir;
	zv.Normalize();
	
	// get x-vector with cross product of z-vector and up-vector
	#if IS_NEGATIVE_Z
	vec3 xv = Cross(zv, eye_up);
	#else
	vec3 xv = -Cross(zv, eye_up);
	#endif
	xv.Normalize();
	
	// get y-vector with x-vector and z-vector
	#if IS_NEGATIVE_Z
	vec3 yv = -Cross(zv, xv);
	#else
	vec3 yv = Cross(zv, xv);
	#endif
	yv.Normalize(); // unnecessary
	
	// calculate relative direction vector for object in local space
	vec3 local_obj_dir = AxesDir(obj_yaw_diff, obj_pitch_diff);
	vec3 local_eye_dir = AxesDir(0, 0);
	local_obj_dir.Normalize();
	local_eye_dir.Normalize();
	float local_obj_dir_mag = local_obj_dir.GetMagnitude();
	float local_eye_dir_mag = local_eye_dir.GetMagnitude();
	ASSERT(local_obj_dir_mag == 1.0f);
	ASSERT(local_eye_dir_mag == 1.0f);
	
	// get angle between relative direction vector and eye direction
	float local_obj_eye_dot = Dot(local_obj_dir, local_eye_dir);
	float local_obj_eye_angle = acos(local_obj_eye_dot / (local_obj_dir_mag * local_eye_dir_mag));
	float local_obj_eye_angle_deg = RAD2DEG(local_obj_eye_angle);
	
	// calculate plane's z-distance from angle
	float local_plane_z = cos(local_obj_eye_angle) * obj_dist;
	
	// calculate xy point in plane using plane's distance and angles
	float local_plane_x = local_obj_dir[0] * obj_dist;
	float local_plane_y = local_obj_dir[1] * obj_dist;
	
	// calculate relative point in global space using local plane-xyz and global forward-unit-vector
	vec3 obj_xv = xv * local_plane_x;
	vec3 obj_yv = yv * local_plane_y;
	vec3 obj_zv = zv * local_plane_z;
	vec3 obj_rel_pos = obj_xv + obj_yv + obj_zv;
	
	// calculate global position
	position = eye + obj_rel_pos;
	
}



vec2 Project(const vec2& length, const vec2& direction) {
	float dot = Dot(length, direction);
	float magSq = MagnitudeSq(direction);
	return direction * (dot / magSq);
}

vec3 Project(const vec3& length, const vec3& direction) {
	float dot = Dot(length, direction);
	float magSq = MagnitudeSq(direction);
	return direction * (dot / magSq);
}

vec2 Normalized(const vec2& v) {
	return v * (1.0f / Magnitude(v));
}
vec3 Normalized(const vec3& v) {
	return v * (1.0f / Magnitude(v));
}

mat4 Translation(const vec3& pos) {
	return mat4 {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		pos[0],pos[1],pos[2],1.0f
	};
}

mat2 Cut(const mat3& mat, int row, int col) {
	return mat.Cut(row, col);
}

mat3 Cut(const mat4& mat, int row, int col) {
	return mat.Cut(row, col);
}

mat2 Minor(const mat2& mat) {
	return mat2 {
		mat[1][1], mat[1][0],
		mat[0][1], mat[0][0]
	};
}

mat3 Minor(const mat3& mat) {
	mat3 result;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result[i][j] = Determinant(Cut(mat, i, j));
		}
	}
	
	return result;
}

mat4 Minor(const mat4& mat) {
	mat4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i][j] = Determinant(Cut(mat, i, j));
		}
	}

	return result;
}

void Cofactor(mat2& out, const mat2& minor) {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			out[j][i] = minor[j][i] * powf(-1.0f, i + j);
}

void Cofactor(mat3& out, const mat3& minor) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			out[j][i] = minor[j][i] * powf(-1.0f, i + j);
}

void Cofactor(mat4& out, const mat4& minor) {
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			out[j][i] = minor[j][i] * powf(-1.0f, i + j);
}

mat2 Cofactor(const mat2& mat) {
	mat2 result;
	Cofactor(result, Minor(mat));
	return result;
}

mat3 Cofactor(const mat3& mat) {
	mat3 result;
	Cofactor(result, Minor(mat));
	return result;
}

mat4 Cofactor(const mat4& mat) {
	mat4 result;
	Cofactor(result, Minor(mat));
	return result;
}

float Determinant(const mat2& mat) {
	float result = 0.0f;

	mat2 cofactor = Cofactor(mat);
	for (int j = 0; j < 2; ++j) {
		result += mat[0][j] * cofactor[0][j];
	}

	return result;
}

float Determinant(const mat3& mat) {
	float result = 0.0f;

	mat3 cofactor = Cofactor(mat);
	for (int j = 0; j < 3; ++j) {
		result += mat[0][j] * cofactor[0][j];
	}

	return result;
}

float Determinant(const mat4& mat) {
	float result = 0.0f;

	mat4 cofactor = Cofactor(mat);
	for (int j = 0; j < 4; ++j) {
		result += mat[0][j] * cofactor[0][j];
	}

	return result;
}

mat2 Transpose(const mat2& matrix) {return matrix.GetTransposed();}
mat3 Transpose(const mat3& matrix) {return matrix.GetTransposed();}
mat4 Transpose(const mat4& matrix) {return matrix.GetTransposed();}

mat2 Adjugate(const mat2& mat) {return Transpose(Cofactor(mat));}
mat3 Adjugate(const mat3& mat) {return Transpose(Cofactor(mat));}
mat4 Adjugate(const mat4& mat) {return Transpose(Cofactor(mat));}

mat2 FastInverse(const mat2& mat) {
	float det = Determinant(mat);
	if (CMP(det, 0.0f)) { return mat2(); }
	mat2 a = Adjugate(mat);
	return a * (1.0f / det);
}

mat3 FastInverse(const mat3& mat) {
	float det = Determinant(mat);
	if (CMP(det, 0.0f)) { return mat3(); }
	mat3 a = Adjugate(mat);
	return a * (1.0f / det);
}

mat4 FastInverse(const mat4& m) {

	float det
		= m.data[0].data[0] * m.data[1].data[1] * m.data[2].data[2] * m.data[3].data[3] + m.data[0].data[0] * m.data[1].data[2] * m.data[2].data[3] * m.data[3].data[1] + m.data[0].data[0] * m.data[1].data[3] * m.data[2].data[1] * m.data[3].data[2]
		+ m.data[0].data[1] * m.data[1].data[0] * m.data[2].data[3] * m.data[3].data[2] + m.data[0].data[1] * m.data[1].data[2] * m.data[2].data[0] * m.data[3].data[3] + m.data[0].data[1] * m.data[1].data[3] * m.data[2].data[2] * m.data[3].data[0]
		+ m.data[0].data[2] * m.data[1].data[0] * m.data[2].data[1] * m.data[3].data[3] + m.data[0].data[2] * m.data[1].data[1] * m.data[2].data[3] * m.data[3].data[0] + m.data[0].data[2] * m.data[1].data[3] * m.data[2].data[0] * m.data[3].data[1]
		+ m.data[0].data[3] * m.data[1].data[0] * m.data[2].data[2] * m.data[3].data[1] + m.data[0].data[3] * m.data[1].data[1] * m.data[2].data[0] * m.data[3].data[2] + m.data[0].data[3] * m.data[1].data[2] * m.data[2].data[1] * m.data[3].data[0]
		- m.data[0].data[0] * m.data[1].data[1] * m.data[2].data[3] * m.data[3].data[2] - m.data[0].data[0] * m.data[1].data[2] * m.data[2].data[1] * m.data[3].data[3] - m.data[0].data[0] * m.data[1].data[3] * m.data[2].data[2] * m.data[3].data[1]
		- m.data[0].data[1] * m.data[1].data[0] * m.data[2].data[2] * m.data[3].data[3] - m.data[0].data[1] * m.data[1].data[2] * m.data[2].data[3] * m.data[3].data[0] - m.data[0].data[1] * m.data[1].data[3] * m.data[2].data[0] * m.data[3].data[2]
		- m.data[0].data[2] * m.data[1].data[0] * m.data[2].data[3] * m.data[3].data[1] - m.data[0].data[2] * m.data[1].data[1] * m.data[2].data[0] * m.data[3].data[3] - m.data[0].data[2] * m.data[1].data[3] * m.data[2].data[1] * m.data[3].data[0]
		- m.data[0].data[3] * m.data[1].data[0] * m.data[2].data[1] * m.data[3].data[2] - m.data[0].data[3] * m.data[1].data[1] * m.data[2].data[2] * m.data[3].data[0] - m.data[0].data[3] * m.data[1].data[2] * m.data[2].data[0] * m.data[3].data[1];

	if (CMP(det, 0.0f)) {
		return mat4();
	}
	float i_det = 1.0f / det;

	mat4 result;
	result[0].data[0] = (m.data[1].data[1] * m.data[2].data[2] * m.data[3].data[3] + m.data[1].data[2] * m.data[2].data[3] * m.data[3].data[1] + m.data[1].data[3] * m.data[2].data[1] * m.data[3].data[2] - m.data[1].data[1] * m.data[2].data[3] * m.data[3].data[2] - m.data[1].data[2] * m.data[2].data[1] * m.data[3].data[3] - m.data[1].data[3] * m.data[2].data[2] * m.data[3].data[1]) * i_det;
	result[0].data[1] = (m.data[0].data[1] * m.data[2].data[3] * m.data[3].data[2] + m.data[0].data[2] * m.data[2].data[1] * m.data[3].data[3] + m.data[0].data[3] * m.data[2].data[2] * m.data[3].data[1] - m.data[0].data[1] * m.data[2].data[2] * m.data[3].data[3] - m.data[0].data[2] * m.data[2].data[3] * m.data[3].data[1] - m.data[0].data[3] * m.data[2].data[1] * m.data[3].data[2]) * i_det;
	result[0].data[2] = (m.data[0].data[1] * m.data[1].data[2] * m.data[3].data[3] + m.data[0].data[2] * m.data[1].data[3] * m.data[3].data[1] + m.data[0].data[3] * m.data[1].data[1] * m.data[3].data[2] - m.data[0].data[1] * m.data[1].data[3] * m.data[3].data[2] - m.data[0].data[2] * m.data[1].data[1] * m.data[3].data[3] - m.data[0].data[3] * m.data[1].data[2] * m.data[3].data[1]) * i_det;
	result[0].data[3] = (m.data[0].data[1] * m.data[1].data[3] * m.data[2].data[2] + m.data[0].data[2] * m.data[1].data[1] * m.data[2].data[3] + m.data[0].data[3] * m.data[1].data[2] * m.data[2].data[1] - m.data[0].data[1] * m.data[1].data[2] * m.data[2].data[3] - m.data[0].data[2] * m.data[1].data[3] * m.data[2].data[1] - m.data[0].data[3] * m.data[1].data[1] * m.data[2].data[2]) * i_det;
	result[1].data[0] = (m.data[1].data[0] * m.data[2].data[3] * m.data[3].data[2] + m.data[1].data[2] * m.data[2].data[0] * m.data[3].data[3] + m.data[1].data[3] * m.data[2].data[2] * m.data[3].data[0] - m.data[1].data[0] * m.data[2].data[2] * m.data[3].data[3] - m.data[1].data[2] * m.data[2].data[3] * m.data[3].data[0] - m.data[1].data[3] * m.data[2].data[0] * m.data[3].data[2]) * i_det;
	result[1].data[1] = (m.data[0].data[0] * m.data[2].data[2] * m.data[3].data[3] + m.data[0].data[2] * m.data[2].data[3] * m.data[3].data[0] + m.data[0].data[3] * m.data[2].data[0] * m.data[3].data[2] - m.data[0].data[0] * m.data[2].data[3] * m.data[3].data[2] - m.data[0].data[2] * m.data[2].data[0] * m.data[3].data[3] - m.data[0].data[3] * m.data[2].data[2] * m.data[3].data[0]) * i_det;
	result[1].data[2] = (m.data[0].data[0] * m.data[1].data[3] * m.data[3].data[2] + m.data[0].data[2] * m.data[1].data[0] * m.data[3].data[3] + m.data[0].data[3] * m.data[1].data[2] * m.data[3].data[0] - m.data[0].data[0] * m.data[1].data[2] * m.data[3].data[3] - m.data[0].data[2] * m.data[1].data[3] * m.data[3].data[0] - m.data[0].data[3] * m.data[1].data[0] * m.data[3].data[2]) * i_det;
	result[1].data[3] = (m.data[0].data[0] * m.data[1].data[2] * m.data[2].data[3] + m.data[0].data[2] * m.data[1].data[3] * m.data[2].data[0] + m.data[0].data[3] * m.data[1].data[0] * m.data[2].data[2] - m.data[0].data[0] * m.data[1].data[3] * m.data[2].data[2] - m.data[0].data[2] * m.data[1].data[0] * m.data[2].data[3] - m.data[0].data[3] * m.data[1].data[2] * m.data[2].data[0]) * i_det;
	result[2].data[0] = (m.data[1].data[0] * m.data[2].data[1] * m.data[3].data[3] + m.data[1].data[1] * m.data[2].data[3] * m.data[3].data[0] + m.data[1].data[3] * m.data[2].data[0] * m.data[3].data[1] - m.data[1].data[0] * m.data[2].data[3] * m.data[3].data[1] - m.data[1].data[1] * m.data[2].data[0] * m.data[3].data[3] - m.data[1].data[3] * m.data[2].data[1] * m.data[3].data[0]) * i_det;
	result[2].data[1] = (m.data[0].data[0] * m.data[2].data[3] * m.data[3].data[1] + m.data[0].data[1] * m.data[2].data[0] * m.data[3].data[3] + m.data[0].data[3] * m.data[2].data[1] * m.data[3].data[0] - m.data[0].data[0] * m.data[2].data[1] * m.data[3].data[3] - m.data[0].data[1] * m.data[2].data[3] * m.data[3].data[0] - m.data[0].data[3] * m.data[2].data[0] * m.data[3].data[1]) * i_det;
	result[2].data[2] = (m.data[0].data[0] * m.data[1].data[1] * m.data[3].data[3] + m.data[0].data[1] * m.data[1].data[3] * m.data[3].data[0] + m.data[0].data[3] * m.data[1].data[0] * m.data[3].data[1] - m.data[0].data[0] * m.data[1].data[3] * m.data[3].data[1] - m.data[0].data[1] * m.data[1].data[0] * m.data[3].data[3] - m.data[0].data[3] * m.data[1].data[1] * m.data[3].data[0]) * i_det;
	result[2].data[3] = (m.data[0].data[0] * m.data[1].data[3] * m.data[2].data[1] + m.data[0].data[1] * m.data[1].data[0] * m.data[2].data[3] + m.data[0].data[3] * m.data[1].data[1] * m.data[2].data[0] - m.data[0].data[0] * m.data[1].data[1] * m.data[2].data[3] - m.data[0].data[1] * m.data[1].data[3] * m.data[2].data[0] - m.data[0].data[3] * m.data[1].data[0] * m.data[2].data[1]) * i_det;
	result[3].data[0] = (m.data[1].data[0] * m.data[2].data[2] * m.data[3].data[1] + m.data[1].data[1] * m.data[2].data[0] * m.data[3].data[2] + m.data[1].data[2] * m.data[2].data[1] * m.data[3].data[0] - m.data[1].data[0] * m.data[2].data[1] * m.data[3].data[2] - m.data[1].data[1] * m.data[2].data[2] * m.data[3].data[0] - m.data[1].data[2] * m.data[2].data[0] * m.data[3].data[1]) * i_det;
	result[3].data[1] = (m.data[0].data[0] * m.data[2].data[1] * m.data[3].data[2] + m.data[0].data[1] * m.data[2].data[2] * m.data[3].data[0] + m.data[0].data[2] * m.data[2].data[0] * m.data[3].data[1] - m.data[0].data[0] * m.data[2].data[2] * m.data[3].data[1] - m.data[0].data[1] * m.data[2].data[0] * m.data[3].data[2] - m.data[0].data[2] * m.data[2].data[1] * m.data[3].data[0]) * i_det;
	result[3].data[2] = (m.data[0].data[0] * m.data[1].data[2] * m.data[3].data[1] + m.data[0].data[1] * m.data[1].data[0] * m.data[3].data[2] + m.data[0].data[2] * m.data[1].data[1] * m.data[3].data[0] - m.data[0].data[0] * m.data[1].data[1] * m.data[3].data[2] - m.data[0].data[1] * m.data[1].data[2] * m.data[3].data[0] - m.data[0].data[2] * m.data[1].data[0] * m.data[3].data[1]) * i_det;
	result[3].data[3] = (m.data[0].data[0] * m.data[1].data[1] * m.data[2].data[2] + m.data[0].data[1] * m.data[1].data[2] * m.data[2].data[0] + m.data[0].data[2] * m.data[1].data[0] * m.data[2].data[1] - m.data[0].data[0] * m.data[1].data[2] * m.data[2].data[1] - m.data[0].data[1] * m.data[1].data[0] * m.data[2].data[2] - m.data[0].data[2] * m.data[1].data[1] * m.data[2].data[0]) * i_det;
	
	return result;
}

bool Multiply(vec2& out, const vec2& v, const mat2& m) {
	out = v * m;
	return true;
}

bool Multiply(vec3& out, const vec3& v, const mat3& m) {
	out = v * m;
	return true;
}

bool Multiply(vec4& out, const vec4& v, const mat4& m) {
	out = v * m;
	return true;
}

float Dot(const vec2& a, const vec2& b) {
	return a.Dot(b);
}

float Dot(const vec3& a, const vec3& b) {
	return a.Dot(b);
}

//vec3 Cross(const vec3& l, const vec3& r) {return Cross(l,r);}
float Magnitude(const vec2& v) {return v.GetMagnitude();}
float Magnitude(const vec3& v) {return v.GetMagnitude();}
float MagnitudeSq(const vec2& v) {return v.GetMagnitudeSq();}
float MagnitudeSq(const vec3& v) {return v.GetMagnitudeSq();}

float CorrectDegrees(float degrees) {
	while (degrees > 360.0f) {
		degrees -= 360.0f;
	}
	while (degrees < -360.0f) {
		degrees += 360.0f;
	}
	return degrees;
}

float RadDeg(float radians) {
	float degrees = radians * 57.295754f;
	degrees = CorrectDegrees(degrees);
	return degrees;
}

float DegRad(float degrees) {
	degrees = CorrectDegrees(degrees);
	float radians = degrees * 0.0174533f;
	return radians;
}

void SetCrossMatrixPlus(mat3& res, const vec3& a)
{
	const float a_0 = a[0];
	const float a_1 = a[1];
	const float a_2 = a[2];
	res[0][1] = -a_2;
	res[0][2] = +a_1;
	res[1][0] = +a_2;
	res[1][2] = -a_0;
	res[2][0] = -a_1;
	res[2][1] = +a_0;
}



float CalcVectorDot(const mat3& a, int a_col, const vec3& b) {
	return	a[0][a_col] * b[0] +
			a[1][a_col] * b[1] +
			a[2][a_col] * b[2];
}

void Multiply0_333_Helper(vec3& res, const mat3& a, const vec3& b) {
  float res_0 = CalcVectorDot(a, 0, b);
  float res_1 = CalcVectorDot(a, 1, b);
  float res_2 = CalcVectorDot(a, 2, b);
  res[0] = res_0;
  res[1] = res_1;
  res[2] = res_2;
}

void Multiply(mat3& res, const mat3& a, const mat3& b) {
	Multiply0_333_Helper(res[0], b, a[0]);
	Multiply0_333_Helper(res[1], b, a[1]);
	Multiply0_333_Helper(res[2], b, a[2]);
}


bool FactorCholesky(mat3& A, vec3& out) {
    bool failure = false;
    const unsigned n = 3;
    
    for (unsigned i = 0; i < n; ++i) {
        vec3& cc = A[i];
        {
            for (unsigned j = 0; j < i; ++j) {
                vec3& bb = A[j];
                
                float sum = cc[j];
				for(int k = 0; k < j; k++) {
					sum -= cc[k] * bb[k];
				}
				cc[j] = sum * out[j];
            }
        }
        {
            float sum = cc[i];
            for (unsigned j = 0; j < i; ++j) {
                float f = cc[j];
                sum -= f * f;
            }
            if (sum <= 0.0f) {
                failure = true;
                break;
            }
            float sumsqrt = FastSqrt(sum);
            cc[i] = sumsqrt;
            out[i] = 1.0f / sumsqrt;
        }
    }
    
    return failure ? 0 : 1;
}

bool IsPositiveDefinite(const mat3& m) {
	vec3 tmp{0,0,0};
	mat3 tmp_m = m;
	return FactorCholesky(tmp_m, tmp);
}

void StoreMatrix(mat4* dst, const mat4& src) {
	*dst = src;
}

void StoreVec2(vec2* dst, const vec4& src) {
	*dst = src.Splice<0,2>();
}

void StoreVec3(vec3* dst, const vec4& src) {
	*dst = src.Splice<0,3>();
}

void StoreVec4(vec4* dst, const vec4& src) {
	*dst = src;
}

void ScalarSinCos(float* f_sin, float* f_cos, float rad) {
	ASSERT(f_sin && f_cos);
	if (f_sin) *f_sin = FastSin(rad);
	if (f_cos) *f_cos = FastCos(rad);
}

vec4 VectorScale(const vec4& v, float f) {
	return v * f;
}

RGBA CreateRGBA(const vec4& color) {
    vec4 colorf = color * 255.f;
    RGBA r;
    r.r = (byte)colorf[0];
    r.g = (byte)colorf[1];
    r.b = (byte)colorf[2];
    r.a = (byte)colorf[3];
    return r;
}

vec3 MultiplyPoint(const vec3& vec, const mat4& mat) {
	return (vec.Embed() * mat).Splice(); // notice Embed = Extend(1)
}

vec3 MultiplyVector(const vec3& vec, const mat3& mat) {
	return vec * mat;
}

vec3 MultiplyVector(const vec3& vec, const mat4& mat) {
	return (vec.Extend() * mat).Splice();
}

mat4 MultiplyMatrix(const mat4& m0, const mat4& m1) {
	mat4 r;
    
    float x = m0.data[0].data[0];
    float y = m0.data[0].data[1];
    float z = m0.data[0].data[2];
    float w = m0.data[0].data[3];
    
    r.data[0].data[0] = (m1.data[0].data[0] * x) + (m1.data[1].data[0] * y) + (m1.data[2].data[0] * z) + (m1.data[3].data[0] * w);
    r.data[0].data[1] = (m1.data[0].data[1] * x) + (m1.data[1].data[1] * y) + (m1.data[2].data[1] * z) + (m1.data[3].data[1] * w);
    r.data[0].data[2] = (m1.data[0].data[2] * x) + (m1.data[1].data[2] * y) + (m1.data[2].data[2] * z) + (m1.data[3].data[2] * w);
    r.data[0].data[3] = (m1.data[0].data[3] * x) + (m1.data[1].data[3] * y) + (m1.data[2].data[3] * z) + (m1.data[3].data[3] * w);
    
    x = m0.data[1].data[0];
    y = m0.data[1].data[1];
    z = m0.data[1].data[2];
    w = m0.data[1].data[3];
    r.data[1].data[0] = (m1.data[0].data[0] * x) + (m1.data[1].data[0] * y) + (m1.data[2].data[0] * z) + (m1.data[3].data[0] * w);
    r.data[1].data[1] = (m1.data[0].data[1] * x) + (m1.data[1].data[1] * y) + (m1.data[2].data[1] * z) + (m1.data[3].data[1] * w);
    r.data[1].data[2] = (m1.data[0].data[2] * x) + (m1.data[1].data[2] * y) + (m1.data[2].data[2] * z) + (m1.data[3].data[2] * w);
    r.data[1].data[3] = (m1.data[0].data[3] * x) + (m1.data[1].data[3] * y) + (m1.data[2].data[3] * z) + (m1.data[3].data[3] * w);
    
    x = m0.data[2].data[0];
    y = m0.data[2].data[1];
    z = m0.data[2].data[2];
    w = m0.data[2].data[3];
    r.data[2].data[0] = (m1.data[0].data[0] * x) + (m1.data[1].data[0] * y) + (m1.data[2].data[0] * z) + (m1.data[3].data[0] * w);
    r.data[2].data[1] = (m1.data[0].data[1] * x) + (m1.data[1].data[1] * y) + (m1.data[2].data[1] * z) + (m1.data[3].data[1] * w);
    r.data[2].data[2] = (m1.data[0].data[2] * x) + (m1.data[1].data[2] * y) + (m1.data[2].data[2] * z) + (m1.data[3].data[2] * w);
    r.data[2].data[3] = (m1.data[0].data[3] * x) + (m1.data[1].data[3] * y) + (m1.data[2].data[3] * z) + (m1.data[3].data[3] * w);
    
    x = m0.data[3].data[0];
    y = m0.data[3].data[1];
    z = m0.data[3].data[2];
    w = m0.data[3].data[3];
    r.data[3].data[0] = (m1.data[0].data[0] * x) + (m1.data[1].data[0] * y) + (m1.data[2].data[0] * z) + (m1.data[3].data[0] * w);
    r.data[3].data[1] = (m1.data[0].data[1] * x) + (m1.data[1].data[1] * y) + (m1.data[2].data[1] * z) + (m1.data[3].data[1] * w);
    r.data[3].data[2] = (m1.data[0].data[2] * x) + (m1.data[1].data[2] * y) + (m1.data[2].data[2] * z) + (m1.data[3].data[2] * w);
    r.data[3].data[3] = (m1.data[0].data[3] * x) + (m1.data[1].data[3] * y) + (m1.data[2].data[3] * z) + (m1.data[3].data[3] * w);
    
    return r;
}

vec4 VectorSet(float x, float y, float z, float d) {
	return vec4 {x, y, z, d};
}

vec4 VectorCross(const vec4& a, const vec4& b) {
	return Cross(a, b);
}

mat4 MatrixTranspose(const mat4& m) {
	return m.GetTransposed();
}

mat4 DoubleToMatrix4(const std::vector<double>& v) {
	ASSERT(v.size() == 16);
	mat4 m;
	int k = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			m[i][j] = k < v.size() ? v[k] : 0;
			k++;
		}
	}
	return m;
}

vec3 DoubleToVector3(const std::vector<double>& v) {
	ASSERT(v.size() == 3);
	vec3 r;
	for(int i = 0; i < 3; i++)
		r[i] = v[i];
	return r;
}

vec3 DoubleToVector4(const std::vector<double>& v) {
	ASSERT(v.size() == 4);
	vec3 r;
	for(int i = 0; i < 4; i++)
		r[i] = v[i];
	return r;
}

quat DoubleToQuat(const std::vector<double>& v) {
	ASSERT(v.size() == 4);
	quat r;
	for(int i = 0; i < 4; i++)
		r[i] = v[i];
	return r;
}

mat4 MatrixTransformation(
    const vec3& scaling_origin,
    const quat& scaling_orientation_quaternion,
    const vec3& scaling,
    const vec3& rotation_origin,
    const quat& rotation_quaternion,
    const vec3& translation
)
{
    vec4 v_scaling_origin			= scaling_origin.Extend();
    vec3 neg_scaling_origin			= -scaling_origin;

    mat4 m_scaling_origin_i			= MatrixTranslationFromVector(neg_scaling_origin);
    mat4 m_scaling_orientation		= QuatMat(scaling_orientation_quaternion);
    mat4 m_scaling_orientation_t	= MatrixTranspose(m_scaling_orientation);
    mat4 m_scaling					= MatrixScalingFromVector(scaling);
    vec4 v_rotation_origin			= rotation_origin.Extend();
    mat4 m_rotation					= QuatMat(rotation_quaternion);
    vec4 v_translation				= translation.Extend();

    mat4 m;
    m		= MatrixMultiply(m_scaling_origin_i, m_scaling_orientation_t);
    m		= MatrixMultiply(m, m_scaling);
    m		= MatrixMultiply(m, m_scaling_orientation);
    m[3]	= m[3] + v_scaling_origin;
    m[3]	= m[3] - v_rotation_origin;
    m		= MatrixMultiply(m, m_rotation);
    m[3]	= m[3] + v_rotation_origin + v_translation;
    return m;
}

mat4 MatrixTranslationFromVector(const vec3& v) {
	mat4 m;
	m.SetIdentity();
	m.SetComponentTranslate(v[0], v[1], v[2]);
	return m;
}

void ChangeZConvention(mat4& m) {
	
    //m[0][0] = -m[0][0];
    //3m[2][2] = -m[2][2];
    
    m[0][1] = -m[0][1];
    m[0][2] = -m[0][2];
    
    m[1][0] = -m[1][0];
    m[1][2] = -m[1][2];
    
    m[2][0] = -m[2][0];
    m[2][1] = -m[2][1];
	
}

mat4 QuatMat(quat q) {
    float qx = q[0];
    float qxx = qx * qx;

    float qy = q[1];
    float qyy = qy * qy;

    float qz = q[2];
    float qzz = (qz * qz);

    float qw = q[3];
	
	#if IS_NEGATIVE_Z || IS_CW_ANGLE
    mat4 m;
    m[0][0] = 1.f - 2.f * qyy - 2.f * qzz;
    m[0][1] = 2.f * qx * qy + 2.f * qz * qw;
    m[0][2] = 2.f * qx * qz - 2.f * qy * qw;
    m[0][3] = 0.f;

    m[1][0] = 2.f * qx * qy - 2.f * qz * qw;
    m[1][1] = 1.f - 2.f * qxx - 2.f * qzz;
    m[1][2] = 2.f * qy * qz + 2.f * qx * qw;
    m[1][3] = 0.f;

    m[2][0] = 2.f * qx * qz + 2.f * qy * qw;
    m[2][1] = 2.f * qy * qz - 2.f * qx * qw;
    m[2][2] = 1.f - 2.f * qxx - 2.f * qyy;
    m[2][3] = 0.f;

    m[3][0] = 0.f;
    m[3][1] = 0.f;
    m[3][2] = 0.f;
    m[3][3] = 1.0f;
    
    #else
    
    qz = -qz;
    
    mat4 m;
    m[0][0] = 1.f - 2.f * qyy - 2.f * qzz;
    m[0][1] = -(2.f * qx * qy + 2.f * qz * qw);
    m[0][2] = -(2.f * qx * qz - 2.f * qy * qw);
    m[0][3] = 0.f;

    m[1][0] = -(2.f * qx * qy - 2.f * qz * qw);
    m[1][1] = 1.f - 2.f * qxx - 2.f * qzz;
    m[1][2] = -(2.f * qy * qz + 2.f * qx * qw);
    m[1][3] = 0.f;

    m[2][0] = -(2.f * qx * qz + 2.f * qy * qw);
    m[2][1] = -(2.f * qy * qz - 2.f * qx * qw);
    m[2][2] = 1.f - 2.f * qxx - 2.f * qyy;
    m[2][3] = 0.f;

    m[3][0] = 0.f;
    m[3][1] = 0.f;
    m[3][2] = 0.f;
    m[3][3] = 1.0f;
    
    #endif
    
    return m;
}

mat4 MatrixScalingFromVector(const vec3& scale)
{
    mat4 m;
    
    m[0][0] = scale[0];
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = scale[1];
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = scale[2];
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    return m;
}

mat4 MatrixMultiply(const mat4& m1, const mat4& m2) {
    mat4 r;
    
    // Cache the invariants in registers
    float x = m1[0][0];
    float y = m1[0][1];
    float z = m1[0][2];
    float w = m1[0][3];
    
    // Perform the operation on the first row
    r[0][0] = (m2[0][0] * x) + (m2[1][0] * y) + (m2[2][0] * z) + (m2[3][0] * w);
    r[0][1] = (m2[0][1] * x) + (m2[1][1] * y) + (m2[2][1] * z) + (m2[3][1] * w);
    r[0][2] = (m2[0][2] * x) + (m2[1][2] * y) + (m2[2][2] * z) + (m2[3][2] * w);
    r[0][3] = (m2[0][3] * x) + (m2[1][3] * y) + (m2[2][3] * z) + (m2[3][3] * w);
    
    // Repeat for all the other rows
    x = m1[1][0];
    y = m1[1][1];
    z = m1[1][2];
    w = m1[1][3];
    r[1][0] = (m2[0][0] * x) + (m2[1][0] * y) + (m2[2][0] * z) + (m2[3][0] * w);
    r[1][1] = (m2[0][1] * x) + (m2[1][1] * y) + (m2[2][1] * z) + (m2[3][1] * w);
    r[1][2] = (m2[0][2] * x) + (m2[1][2] * y) + (m2[2][2] * z) + (m2[3][2] * w);
    r[1][3] = (m2[0][3] * x) + (m2[1][3] * y) + (m2[2][3] * z) + (m2[3][3] * w);
    
    x = m1[2][0];
    y = m1[2][1];
    z = m1[2][2];
    w = m1[2][3];
    r[2][0] = (m2[0][0] * x) + (m2[1][0] * y) + (m2[2][0] * z) + (m2[3][0] * w);
    r[2][1] = (m2[0][1] * x) + (m2[1][1] * y) + (m2[2][1] * z) + (m2[3][1] * w);
    r[2][2] = (m2[0][2] * x) + (m2[1][2] * y) + (m2[2][2] * z) + (m2[3][2] * w);
    r[2][3] = (m2[0][3] * x) + (m2[1][3] * y) + (m2[2][3] * z) + (m2[3][3] * w);
    
    x = m1[3][0];
    y = m1[3][1];
    z = m1[3][2];
    w = m1[3][3];
    r[3][0] = (m2[0][0] * x) + (m2[1][0] * y) + (m2[2][0] * z) + (m2[3][0] * w);
    r[3][1] = (m2[0][1] * x) + (m2[1][1] * y) + (m2[2][1] * z) + (m2[3][1] * w);
    r[3][2] = (m2[0][2] * x) + (m2[1][2] * y) + (m2[2][2] * z) + (m2[3][2] * w);
    r[3][3] = (m2[0][3] * x) + (m2[1][3] * y) + (m2[2][3] * z) + (m2[3][3] * w);
    
    return r;
}

const vec4 IdentityR0            = vec4{ 1.0f, 0.0f, 0.0f, 0.0f };
const vec4 IdentityR1            = vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
const vec4 IdentityR2            = vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
const vec4 IdentityR3            = vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
const vec4 NegIdentityR0         = vec4{ -1.0f, 0.0f, 0.0f, 0.0f };
const vec4 NegIdentityR1         = vec4{ 0.0f, -1.0f, 0.0f, 0.0f };
const vec4 NegIdentityR2         = vec4{ 0.0f, 0.0f, -1.0f, 0.0f };
const vec4 NegIdentityR3         = vec4{ 0.0f, 0.0f, 0.0f, -1.0f };



void QuatAxes(const quat& q, float& yaw, float& pitch, float& roll) {
	float x = q[0];
	float y = q[1];
	float z = q[2];
	float w = q[3];
	yaw   = atan2(2*y*w - 2*x*z, 1 - 2*y*y - 2*z*z);
	pitch = atan2(2*x*w - 2*y*z, 1 - 2*x*x - 2*z*z);
	roll  = asin(2*x*y + 2*z*w);
	#if IS_CW_ANGLE
	roll = -roll;
	#endif
}

void QuatAxes(const quat& q, vec3& axes) {
	QuatAxes(q, axes[0], axes[1], axes[2]);
}

vec3 GetQuatAxes(const quat& q) {
	vec3 v;
	QuatAxes(q,v);
	return v;
}


vec3 Right(const mat4& transform)
{
    return { +transform[0][0], +transform[0][1], +transform[0][2] };
}

vec3 Left(const mat4& transform)
{
    return { -transform[0][0], -transform[0][1], -transform[0][2] };
}

vec3 Up(const mat4& transform)
{
    return { +transform[1][0], +transform[1][1], +transform[1][2] };
}

vec3 Down(const mat4& transform)
{
    return { -transform[1][0], -transform[1][1], -transform[1][2] };
}


vec3 Forward(const mat4& transform)
{
	#if IS_NEGATIVE_Z
    return { -transform[2][0], -transform[2][1], -transform[2][2] };
	#else
    return { +transform[2][0], +transform[2][1], +transform[2][2] };
    #endif
}

vec3 Backward(const mat4& transform)
{
	#if IS_NEGATIVE_Z
    return { +transform[2][0], +transform[2][1], +transform[2][2] };
	#else
    return { -transform[2][0], -transform[2][1], -transform[2][2] };
    #endif
}

vec3 Position(const mat4& transform)
{
    return { +transform[3][0], +transform[3][1], +transform[3][2] };
}



mat4 RemoveScale(const mat4& transform)
{
    quat rotation;
    vec3 scale, translation, skew;
    vec4 pers;
    Decompose(transform, scale, rotation, translation, skew, pers);
    rotation.Normalize();
    return Translate(translation) * QuatMat(rotation);
}


quat MatQuat(const mat4& transform)
{
    vec3 baller_position, size, skew;
	quat orientation;
	vec4 persp;
	Decompose(transform, size, orientation, baller_position, skew, persp);
	return orientation;
}

mat4 SkewMat(const vec3& v, float ident_value) {
	/*S =
	[0   -c   b   0
     c    0  -a   0
    -b    a   0   0
     0    0   0   0];*/
	mat4 m;
	m[0][0] = ident_value;
	m[1][1] = ident_value;
	m[2][2] = ident_value;
	m[3][3] = ident_value;
	m[0][1] = -v.data[2];
	m[0][2] =  v.data[1];
	m[1][0] =  v.data[2];
	m[1][2] = -v.data[0];
	m[2][0] = -v.data[1];
	m[2][1] =  v.data[0];
	
    return m;
}

mat4 SkewMat(const vec4& v, float ident_value) {
	/*S =
	[0   -a   d   -c
     a    0   c    b
    -d   -c   0   -a
     c   -b   a    0];*/
	mat4 m;
	m[0][0] = ident_value;
	m[1][1] = ident_value;
	m[2][2] = ident_value;
	m[3][3] = ident_value;
	m[0][1] = -v.data[0];
	m[0][2] =  v.data[3];
	m[0][3] = -v.data[2];
	m[1][0] =  v.data[0];
	m[1][2] =  v.data[2];
	m[1][3] =  v.data[1];
	m[2][0] = -v.data[3];
	m[2][1] = -v.data[2];
	m[2][3] = -v.data[0];
	m[3][0] =  v.data[2];
	m[3][1] = -v.data[1];
	m[3][2] =  v.data[0];
	
    return m;
}





vec3 GetVelocityNearSourceLocation(
	    const vec3& grasp_position,
	    const vec3& grasp_velocity,
	    const vec3& angular_velocity,
	    const vec3& position_near_source_location)
{
    // Compute the tangential velocity at position_near_source_location due to angular velocity.
    vec3 position_near_source_location_offset = position_near_source_location - grasp_position;
    vec3 angular_tangential_velocity = Cross(angular_velocity, position_near_source_location_offset);

    // Combine the tangential velocity with the velocity to get the combined velocity.
    vec3 ret = grasp_velocity + angular_tangential_velocity;
    return ret;
}

mat2 Rotation2x2(float angle) {
	return mat2{
		cosf(angle), sinf(angle),
		-sinf(angle), cosf(angle)
		};
}

quat TurnLeft(float angle) {
	#if IS_NEGATIVE_Z
	return AxisAngleQuat(vec3(0,1,0), -angle);
	#else
	return AxisAngleQuat(vec3(0,1,0), +angle);
	#endif
}

quat TurnRight(float angle) {
	#if IS_NEGATIVE_Z
	return AxisAngleQuat(vec3(0,1,0), +angle);
	#else
	return AxisAngleQuat(vec3(0,1,0), -angle);
	#endif
}

quat TurnUp(float angle) {
	#if IS_NEGATIVE_Z
	return AxisAngleQuat(vec3(1,0,0), +angle);
	#else
	return AxisAngleQuat(vec3(1,0,0), -angle);
	#endif
}

quat TurnDown(float angle) {
	#if IS_NEGATIVE_Z
	return AxisAngleQuat(vec3(1,0,0), -angle);
	#else
	return AxisAngleQuat(vec3(1,0,0), +angle);
	#endif
}

quat SwapHandedness(const quat& input) {
    return quat(
         input.data[1],   // -(  right = -left  )
        -input.data[2],   // -(     up =  up     )
        -input.data[0],   // -(forward =  forward)
         input.data[3]
    );
}

String Plot(const vec3& a, const vec3& b) {
	float dot = Dot(a, b) / b.GetLength();
	dot = max(-1.0f, min(+1.0f, dot));
	int chars = 20;

	String s;
	if (dot < 0) {
		int spaces = (1.0 + dot) * chars;
		int fills = chars - spaces;
		s.Cat(' ', spaces);
		s.Cat('#', fills);
		s.Cat(' ', chars);
	}
	else {
		int fills = dot * chars;
		int spaces = (1.0 - dot) * chars;
		s.Cat(' ', chars);
		s.Cat('#', fills);
		s.Cat(' ', spaces);
	}
	return s;
}

float VectorAngle(const vec3& a, const vec3& b) {
	float dot = a.Dot(b);
	float len = a.GetLength() * b.GetLength();
	float ratio = dot / len;
	float angle = acos(ratio);
	return angle;
}

float VectorAngle(const vec2& a, const vec2& b) {
	float dot = a.Dot(b);
	float len = a.GetLength() * b.GetLength();
	float ratio = dot / len;
	float angle = acos(ratio);
	return angle;
}





bool IsClose(const quat& a, const quat& b) {
	float sum = 0;
	for(int i = 0; i < 4; i++)
		sum += fabsf(a[i] - b[i]);
	return sum < 0.001;
}

bool IsClose(const axes2& a, const axes2& b, float dist_limit) {
	double sum = 0;
	for(int i = 0; i < 2; i++) {
		sum += fabsf(a[i] - b[i]);
	}
	return fabs(sum) < dist_limit;
}

bool IsClose(const axes3s& a, const axes3s& b, float dist_limit) {
	double sum = 0;
	for(int i = 0; i < 4; i++) {
		sum += fabsf(a[i] - b[i]);
	}
	return fabs(sum) < dist_limit;
}

bool IsClose(const vec3& a, const vec3& b, float dist_limit) {
	double sum = 0;
	for(int i = 0; i < 3; i++) {
		sum += fabsf(a[i] - b[i]);
	}
	return fabs(sum) < dist_limit;
}

bool IsClose(const vec4& a, const vec4& b) {
	float dist = (a - b).GetLength();
	return fabsf(dist) < 0.001;
}

bool IsClose(const mat4& a, const mat4& b) {
	double sum = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			sum += fabsf(a[i][j] - b[i][j]);
		}
	}
	return fabs(sum) < 0.001;
}








axes2s LookAtStereoAngles(float eye_dist, const vec3& pt) {
	vec3 l(-eye_dist*0.5,0,0);
	vec3 r(+eye_dist*0.5,0,0);
	vec3 pt_l = pt - l;
	vec3 pt_r = pt - r;
	vec3 axes_l = GetDirAxes(pt_l);
	vec3 axes_r = GetDirAxes(pt_r);
	axes2s a;
	a.data[0] = axes_l.data[0];
	a.data[1] = axes_r.data[0];
	a.data[2] = axes_l.data[1];
	return a;
}

axes2s LookAtStereoAngles(float eye_dist, const vec3& pt, axes2& l, axes2& r) {
	axes2s a = LookAtStereoAngles(eye_dist, pt);
	AxesStereoMono(a, l, r);
	return a;
}

void AxesStereoMono(const axes2s& axes, axes2& l, axes2& r) {
	l.data[0] = axes.data[0];
	l.data[1] = axes.data[2];
	r.data[0] = axes.data[1];
	r.data[1] = axes.data[2];
}

axes2s AxesMonoStereo(const axes2& l, const axes2& r) {
	float pitch = (l.data[1] + r.data[1]) * 0.5;
	return axes2s(
		l.data[0],
		r.data[0],
		pitch
	);
}

vec2 CalculateThirdPoint(const vec2& a, const vec2& b, float alp1, float alp2) {
	ASSERT(alp1 > 0 && alp1 < M_PI);
	ASSERT(alp2 > 0 && alp2 < M_PI);
	// initial data
	float x1 = a[0];
	float y1 = a[1];
	float x2 = b[0];
	float y2 = b[1];
	float u = x2 - x1;
	float v = y2 - y1;
	float a3 = sqrt(u * u + v * v);
	float alp3 = M_PI - alp1 - alp2;
	ASSERT(alp3 > 0 && alp3 < M_PI);
	float a2 = a3 * sin(alp2) / sin(alp3);
	float RHS1 = x1 * u + y1 * v + a2 * a3 * cos(alp1);
	float RHS2 = y2 * u - x2 * v - a2 * a3 * sin(alp1);
	float x3 = (1 / (a3 * a3)) * (u * RHS1 - v * RHS2);
	float y3 = (1 / (a3 * a3)) * (v * RHS1 + u * RHS2);
	return vec2(x3, y3);
}

vec2 CalculateStereoThirdPoint(float eye_dist, float a0, float a1) {
	float d = eye_dist;
	float deg0 = a0 / M_PI * 180;
	float deg1 = a1 / M_PI * 180;
	
	
	if (a0 < M_PI/2 && a1 < M_PI/2) {
		// Isosceles
		
		// x0
		// x1 = d - x0
		// tan(a0) = y / x0
		// tan(a1) = y / x1
		// y = tan(a0) * x0
		// y = tan(a1) * x1
		// y = tan(a1) * (d - x0)
		// tan(a0) * x0 = tan(a1) * (d - x0)
		// x0 = d*tan(a1)/(tan(a0)+tan(a1))
		float ta1 = tan(a1);
		float x0 = d*ta1/(tan(a0)+ta1);
		float y = tan(a0) * x0;
		float x = -d*0.5 + x0;
		return vec2(x,y);
	}
	else if (a0 > M_PI/2 && a1 < M_PI/2) {
		// x0
		// x1 = d + x0
		// tan(M_PI-a0) = y / x0
		// x0 * tan(M_PI-a0) = y
		// tan(a1) = y / x1
		// tan(a1) = y / (d + x0)
		// (d + x0) * tan(a1) = y
		// x0 * tan(M_PI-a0) = (d + x0) * tan(a1)
		// x0 = d*tan(a1)/(tan(M_PI-a0)-tan(a1))
		float ta0 = tan(M_PI-a0);
		float ta1 = tan(a1);
		float x0 = d*ta1/(ta0-ta1);
		float y = x0 * ta0;
		float x = -d*0.5 - x0;
		return vec2(x,y);
	}
	else if (a0 < M_PI/2 && a1 > M_PI/2) {
		// x0 = d + x1
		// x1
		// tan(a0) = y / x0
		// tan(a0) = y / (d + x1)
		// (d + x1) * tan(a0) = y
		// tan(M_PI-a1) = y / x1
		// x1 * tan(M_PI-a1) = y
		// (d + x1) * tan(a0) = x1 * tan(M_PI-a1)
		// x1 = -d*tan(a0)/(tan(a0)-tan(M_PI-a1));
		float ta0 = tan(a0);
		float ta1 = tan(M_PI-a1);
		float x1 = -d*ta0/(ta0-ta1);
		float y = x1 * ta1;
		float x = +d*0.5 + x1;
		return vec2(x,y);
	}
	else {
		vec2 v = CalculateThirdPoint(vec2(-eye_dist/2,0), vec2(+eye_dist/2,0), a0, a1);
		TODO // inv z?
		return v;
	}
	
}

bool CalculateStereoTarget(const axes2s& stereo_axes, float eye_dist, vec3& dir_c) {
	// Flat directions
	vec3 flat_a = AxesDir(stereo_axes[0], 0);
	vec3 flat_b = AxesDir(stereo_axes[1], 0);
	
	// Rotate triangle to y=0 level
	#if 0
	float yaw_a, pitch_a;
	float yaw_b, pitch_b;
	DirAxes(dir_a, yaw_a, pitch_a);
	DirAxes(dir_b, yaw_b, pitch_b);
	float pitch = (pitch_a + pitch_b) * 0.5;
	mat4 x_rot = XRotation(-pitch);
	vec3 flat_a = (x_rot * dir_a.Embed()).Splice();
	vec3 flat_b = (x_rot * dir_b.Embed()).Splice();
	#endif
	
	// Calculate third point of the leveled triangle
	vec2 dir_a2(flat_a[0], flat_a[2]);
	vec2 dir_b2(flat_b[0], flat_b[2]);
	vec2 l_eye(-eye_dist*0.5,0);
	vec2 r_eye(+eye_dist*0.5,0);
	//DUMP(dir_a); DUMP(dir_b);
	//DUMP(dir_a2); DUMP(dir_b2);
	float alp1 = VectorAngle(dir_a2, vec2(+1,0));
	float alp2 = VectorAngle(dir_b2, vec2(-1,0));
	float deg1 = alp1 / M_PI * 180;
	float deg2 = alp2 / M_PI * 180;
	if (alp1 + alp2 >= M_PI)
		return false;
	vec2 tgt = CalculateStereoThirdPoint(eye_dist, alp1, alp2);
	
	//vec2 tgt = CalculateThirdPoint(l_eye, r_eye, alp1, alp2);
	//tgt.data[2] *= -1;
	//DUMP(tgt);
	
	#if !IS_NEGATIVE_Z
	TODO
	#endif
	
	vec3 flat_c(tgt[0], 0, -tgt[1]);
	if (stereo_axes[2] != 0) {
		mat4 x_rot = XRotation(stereo_axes[2]);
		dir_c = (x_rot * flat_c.Embed()).Splice();
	}
	else {
		dir_c = flat_c;
	}
	
	
	//DUMP(dir_c);
	
	return true;
}

bool CalculateTriangleChange(const vec3& a0, const vec3& a1, const vec3& a2, const vec3& b0, const vec3& b1, const vec3& b2, mat4& out) {
	
	if (a0 == a1 || a0 == a2 ||
		a1 == a2 ||
		b0 == b1 || b0 == b2 ||
		b1 == b2)
		return false;
	
	vec3 a10 = a1 - a0;
	vec3 a20 = a2 - a0;
	vec3 b10 = b1 - b0;
	vec3 b20 = b2 - b0;
	
	float a_scale = (a10.GetLength() + a20.GetLength()) * 0.5;
	float b_scale = (b10.GetLength() + b20.GetLength()) * 0.5;
	float scale_factor = b_scale / a_scale;
	
	vec3 scale(scale_factor);
	
	mat4 a_rot_inv = GetPrincipalAxesMat(a10, a20);
	mat4 b_rot_inv = GetPrincipalAxesMat(b10, b20);
	mat4 a_rot = a_rot_inv.GetInverse();
	mat4 b_rot = b_rot_inv.GetInverse();
	mat4 rot = a_rot_inv * b_rot;
	mat4 rot_inv = rot.GetInverse();
	quat orient = MatQuat(rot);
	
	vec3 pos_diff = b0 - a0;
	vec3 pos_diff_orient = VecMul(rot_inv, pos_diff);
	
	vec3 skew(0);
	vec4 proj(0,0,0,1);
	mat4 m = Recompose(scale, orient, pos_diff_orient, skew, proj);
	
	// NOTE: brute force fix, no theory behind... makes tests pass
	vec3 c0 = VecMul(m, a0);
	vec3 b_diff = VecMul(rot_inv, b0 - c0);
	out = m * Translate(b_diff);
	
	return true;
}

bool TriangleToStereoEyes(const vec3& v0, const vec3& v1, vec3& v_eye0, vec3& v_eye1, vec3& v_tgt, mat4& mat, mat4& inv_mat, bool have_common_scale, float& common_scale) {
	float dist = (v1 - v0).GetLength();
	vec3 v_ct = (v0 + v1) * 0.5;
	
	bool upwards = Cross(v1 - v0, -v0)[1] > 0;
	float x_mult = upwards ? +1.0f : -1.0f;
	
	vec3 v_rot_z = -v_ct.GetNormalized();
	vec3 v_rot_x = (v1 - v_ct).GetNormalized() * x_mult;
	vec3 v_rot_y = Cross(v_rot_x, v_rot_z);
	
	if (!have_common_scale) {
		common_scale = 1.0 / dist;
	}
	float scale_mul = dist * common_scale;
	mat = mat * Scale(vec3(scale_mul));
	
	// Translate previous 2 points to be "eyes"
	inv_mat = mat.GetInverse();
	v_eye0 = (inv_mat * v0.Embed()).Splice();
	v_eye1 = (inv_mat * v1.Embed()).Splice();
	v_tgt = (inv_mat * vec4(0,0,0,1)).Splice();
	
	return true;
}

// This is dumb function. You probably shouldn't use it.
bool CalculateTriangleChange(vec3 local, vec3 prev0, vec3 prev1, vec3 cur0, vec3 cur1, mat4& out) {
	if (prev0 == local || prev1 == local ||
		cur0 == local || cur1 == local)
		return false;
	
	prev0 = prev0 - local;
	prev1 = prev1 - local;
	cur0 = cur0 - local;
	cur1 = cur1 - local;
	
	vec3 prev_ct, prev_eye0, prev_eye1, prev_tgt;
	mat4 prev_mat, prev_inv_mat;
	float common_scale = 1;
	if (!TriangleToStereoEyes(prev0, prev1, prev_eye0, prev_eye1, prev_tgt, prev_mat, prev_inv_mat, false, common_scale))
		return false;
	
	vec3 cur_ct, cur_eye0, cur_eye1, cur_tgt;
	mat4 cur_mat, cur_inv_mat;
	if (!TriangleToStereoEyes(cur0, cur1, cur_eye0, cur_eye1, cur_tgt, cur_mat, cur_inv_mat, true, common_scale))
		return false;
	
	ASSERT(IsClose(prev_eye0, cur_eye0));
	ASSERT(IsClose(prev_eye1, cur_eye1));
	
	out = prev_inv_mat * cur_mat;
	
	return true;
}

vec3 VecMul(const mat4& m, const vec3& v) {
	vec4 p = m * v.Embed();
	p.data[0] /= p.data[3];
	p.data[1] /= p.data[3];
	p.data[2] /= p.data[3];
	return p.Splice();
}

void GetPrincipalAxes(const vec3& a, const vec3& b, vec3& x, vec3& y, vec3& z) {
	z = a.GetNormalized();
	y = -Cross(a, b);
	x = Cross(z, y);
	y.Normalize();
	x.Normalize();
}

mat4 GetPrincipalAxesMat(const vec3& a, const vec3& b) {
	vec3 x, y, z;
	GetPrincipalAxes(a, b, x, y, z);
	return mat4 {
		x.data[0], x.data[1], x.data[2] * SCALAR_FWD_Z, 0,
		y.data[0], y.data[1], y.data[2] * SCALAR_FWD_Z, 0,
		z.data[0], z.data[1], z.data[2] * SCALAR_FWD_Z, 0,
		0,0,0,1
	};
}











#if 1


const uint32 NumSamples = 256;
const float InvNumSamples = 1.0 / float(NumSamples);

float radicalInverse_VdC(uint32 bits)
{
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	return float(bits) * 2.3283064365386963e-10;
}

vec2 sampleHammersley(uint32 i)
{
	return vec2(i * InvNumSamples, radicalInverse_VdC(i));
}

vec3 sampleGGX(float u1, float u2, float roughness)
{
	float alpha = roughness * roughness;

	float cosTheta = sqrt((1.0 - u2) / (1.0 + (alpha*alpha - 1.0) * u2));
	float sinTheta = sqrt(1.0 - cosTheta*cosTheta);
	float phi = M_2PI * u1;

	return vec3(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta);
}

float gaSchlickG1(float cosTheta, float k)
{
	return cosTheta / (cosTheta * (1.0 - k) + k);
}

float gaSchlickGGX_IBL(float cosLi, float cosLo, float roughness)
{
	float r = roughness;
	float k = (r * r) / 2.0;
	return gaSchlickG1(cosLi, k) * gaSchlickG1(cosLo, k);
}

void MakeSpecBRDF(FloatImage& img, int side_len) {
	Size sz(side_len, side_len);
	img.Set(sz, 3);
	
	const float Epsilon = 0.001;
	
	float* begin = img.Begin();
	
	for (int x = 0; x < sz.cx; ++x) {
	
	    for (int y = 0; y < sz.cy; ++y)
	    {
			float cosLo = x / float(sz.cx);
			float roughness = y / float(sz.cy);
		
			cosLo = max(cosLo, Epsilon);
		
			vec3 Lo = vec3(sqrt(1.0 - cosLo*cosLo), 0.0, cosLo);
		
			float DFG1 = 0;
			float DFG2 = 0;
		
			for(uint32 i=0; i<NumSamples; ++i) {
				vec2 u  = sampleHammersley(i);
				vec3 Lh = sampleGGX(u[0], u[1], roughness);
				vec3 Li = Lh * (2.0f * Dot(Lo, Lh)) - Lo;
		
				float cosLi   = Li[2];
				float cosLh   = Lh[2];
				float cosLoLh = max(Dot(Lo, Lh), 0.0f);
		
				if(cosLi > 0.0f) {
					float G  = gaSchlickGGX_IBL(cosLi, cosLo, roughness);
					float Gv = G * cosLoLh / (cosLh * cosLo);
					float Fc = pow(1.0f - cosLoLh, 5);
		
					DFG1 += (1 - Fc) * Gv;
					DFG2 += Fc * Gv;
				}
			}
			
	        float* pix = begin + y * img.pitch + x * img.channels;
	        pix[0] = DFG1 * InvNumSamples;
	        pix[1] = DFG2 * InvNumSamples;
	        pix[2] = 0;
	    }
	}
}

#else

void MakeSpecBRDF(FloatImage& img, int side_len) {
	Size sz(side_len, side_len);
	img.Set(sz, 3);
	
	float* begin = img.Begin();
	
	for (int x = 0; x < sz.cx; ++x) {
	    float xNorm = (float) x / (sz.cx - 1);
	    float roughness = xNorm;
	    float alpha = roughness * roughness;
	    float alphaSqr = alpha * alpha;
	    float k = roughness + 1;
	    k = k * k * 0.125f;
	
	    float LdotH5 = pow(1 - xNorm, 5);
	
	    // R -> F -> LdotH x Spec
	    // G -> G -> Roughness x NdotL
	    // G -> G -> Roughness x NdotV
	    // B -> D -> Roughness x NdotH
	
	    for (int y = 0; y < sz.cy; ++y)
	    {
	        float yNorm = (float)y / (sz.cy - 1);
	
	        float F = yNorm + (1 - yNorm) * LdotH5;
	
	        float denom = yNorm * yNorm * (alphaSqr - 1) + 1;
	
	        denom = max(M_PI * denom * denom, 0.0000001);
	        float D = alphaSqr / denom;
	        
	        float G = yNorm / max(yNorm * (1 - k) + k, 0.0000001f);
	
	        float* pix = begin + y * img.pitch + x * img.channels;
	        pix[0] = F;
	        pix[1] = G;
	        pix[2] = D;
	    }
	}
}
#endif


vec3 CrossArea3(vec3 a, vec3 b) {
	return vec3(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}

float CrossArea2(vec2 a, vec2 b) {
	return (a[0] * b[1]) - (a[1] * b[0]);
}

float Area3(const vec3& a, const vec3& b, const vec3& c) {
	vec3 v = CrossArea3(b-a, c-b);
	return v[2] > 0? v.GetLength() : -v.GetLength();
}

float Area2(const vec2& a, const vec2& b, const vec2& c) {
	return CrossArea2(b-a, c-b);
}


NAMESPACE_TOPSIDE_END
