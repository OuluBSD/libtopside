#ifndef _Math_Util_h_
#define _Math_Util_h_


NAMESPACE_TOPSIDE_BEGIN


template <class T> T zero() {T o; memset(&o, 0, sizeof(T));return o;}
template <class T> T one() {T o; o.SetConst(1.0); return o;}
template <class T> T identity() {T o; o.SetIdentity(); return o;}

template <class T>
T normalize(const T& a) {
	T o(a);
	o.Normalize();
	return o;
}

template <class T> T mod(const T& a, float f) {return a.Modulus(f);}
template <class T> T mix(const T& a, const T& b, float f) {return a.Mix(b, f);}


mat4 perspective(float half_fov_rad, float aspect, float near, float far);
mat4 ortho(float left, float right, float bottom, float top, float near, float far);
mat4 ToMat4(const quat& q);
void ToMat3_(mat3& m, const quat& q);

template <class T> T cross(const T& a, const T& b) {return a.GetCrossProduct(b);}
template <class T> T inverse(const T& o) {return o.GetInverse();}
template <class T> T transpose(const T& o) {return o.GetTransposed();}
template<class T, class K> T scale(const T& a, const K& b) {return a.Scale(b);}
template<class T, class K> T translate(const T& a, const K& b) {return a.Translate(b);}
template<class T> float dot(const T& a, const T& b) {return a.GetDotProduct(b);}
vec3 combine(const vec3& a, const vec3& b, float ascl, float bscl);

inline mat4 scale(const vec3& b) {mat4 a; a.SetIdentity(); return a.Scale(b);}
inline mat4 translate(const vec3& b) {mat4 a; a.SetIdentity(); return a.Translate(b);}
inline vec3 transform(const vec3& v, const mat4& m) {return (v.Extend(1.0) * m).Splice();}
vec3 transform(const vec3& v, const quat& m);

vec3 lerp(const vec3& pos, const vec3& tgt_pos, float easing_factor);
quat slerp(const quat& orient, const quat& tgt_orient, float easing_factor);

mat4 FastInverse(const mat4& mat);
vec2 Project(const vec2& length, const vec2& direction);
vec3 Project(const vec3& length, const vec3& direction);
vec2 Normalized(const vec2& v);
vec3 Normalized(const vec3& v);
mat4 Translation(const vec3& pos);
mat2 Cut(const mat3& mat, int row, int col);
mat3 Cut(const mat4& mat, int row, int col);
mat2 Minor(const mat2& mat);
mat3 Minor(const mat3& mat);
mat4 Minor(const mat4& mat);
mat2 Cofactor(const mat2& mat);
mat3 Cofactor(const mat3& mat);
mat4 Cofactor(const mat4& mat);
float Determinant(const mat3& mat);
float Determinant(const mat4& mat);
mat2 Adjugate(const mat2& mat);
mat3 Adjugate(const mat3& mat);
mat4 Adjugate(const mat4& mat);
mat2 Inverse(const mat2& mat);
mat3 Inverse(const mat3& mat);
mat4 Inverse(const mat4& m);
bool Multiply(vec2& out, const vec2& v, const mat2& m);
bool Multiply(vec3& out, const vec3& v, const mat3& m);
bool Multiply(vec4& out, const vec4& v, const mat4& m);
float Dot(const vec2& a, const vec2& b);
float Dot(const vec3& a, const vec3& b);
vec3 Cross(const vec3& l, const vec3& r);
float Magnitude(const vec2& v);
float Magnitude(const vec3& v);
float MagnitudeSq(const vec2& v);
float MagnitudeSq(const vec3& v);
float CorrectDegrees(float degrees);
float RadDeg(float radians);
float DegRad(float degrees);
mat2 Transpose(const mat2& matrix);
mat3 Transpose(const mat3& matrix);
mat4 Transpose(const mat4& matrix);
float Determinant(const mat2& matrix);
float Determinant(const mat3& matrix);

vec3 yaw_pitch_to_direction(float yaw, float pitch);
void direction_to_yaw_pitch(vec3 dir, float& yaw, float& pitch);
void camera_object(
	const vec3& eye, const vec3& eye_dir, const vec3& eye_up,
	float obj_yaw_diff, float obj_pitch_diff, float obj_dist,
	vec3& obj_pos, quat& obj_orient);

mat4 Rotation(float pitch, float yaw, float roll);
mat3 Rotation3x3(float pitch, float yaw, float roll);
mat2 Rotation2x2(float angle);
mat4 YawPitchRoll(float yaw, float pitch, float roll);
mat4 XRotation(float angle);
mat3 XRotation3x3(float angle);
mat4 YRotation(float angle);
mat3 YRotation3x3(float angle);
mat4 ZRotation(float angle);
mat3 ZRotation3x3(float angle);

void StoreMatrix(mat4* dst, const mat4& src);
void StoreVec2(vec2* dst, const vec4& src);
void StoreVec3(vec3* dst, const vec4& src);
void StoreVec4(vec4* dst, const vec4& src);
void ScalarSinCos(float* f_sin, float* f_cos, float rad);
mat4 MatrixTranspose(const mat4& m);
vec4 VectorScale(const vec4& v, float f);
RGBA CreateRGBA(const vec4& color);
vec3 MultiplyPoint(const vec3& vec, const mat4& mat);
vec3 MultiplyVector(const vec3& v, const mat3& m);
vec3 MultiplyVector(const vec3& v, const mat4& m);
mat4 MultiplyMatrix(const mat4& m0, const mat4& m1);
mat4 MatrixInverse(const mat4* l, const mat4& r);
vec4 VectorSet(float x, float y, float z, float d);
vec4 VectorCross(const vec4& a, const vec4& b);
mat4 DoubleToMatrix4(const std::vector<double>& v);
vec3 DoubleToVector3(const std::vector<double>& v);
vec3 DoubleToVector4(const std::vector<double>& v);
quat DoubleToQuat(const std::vector<double>& v);
mat4 MatrixTransformation(
    const vec3& scaling_origin,
    const quat& scaling_orientation_quaternion,
    const vec3& scaling,
    const vec3& rotation_origin,
    const quat& rotation_quaternion,
    const vec3& translation
);
mat4 MatrixTranslationFromVector(const vec3& v);
mat4 MatrixRotationQuaternion(quat q);
mat4 MatrixScalingFromVector(const vec3& scale);
mat4 MatrixMultiply(const mat4& m1, const mat4& m2);

extern const vec4 IdentityR0;
extern const vec4 IdentityR1;
extern const vec4 IdentityR2;
extern const vec4 IdentityR3;
extern const vec4 NegIdentityR0;
extern const vec4 NegIdentityR1;
extern const vec4 NegIdentityR2;
extern const vec4 NegIdentityR3;


template <class T> T Min(const T& a, const T& b) {return T::GetMin(a, b);}
template <class T> T Max(const T& a, const T& b) {return T::GetMax(a, b);}
#define DEF_MINMAX(T) \
	template <> inline T Min(const T& a, const T& b) {return a < b ? a : b;} \
	template <> inline T Max(const T& a, const T& b) {return a > b ? a : b;}
DEF_MINMAX(int)
DEF_MINMAX(float)
DEF_MINMAX(double)

struct ViewportParams {
	float x;
	float y;
	float w;
	float h;
	float min_depth;
	float max_depth;
};


mat4 LookAt(const vec3& eye, const vec3& center, const vec3& up);
mat4 GetViewport(const ViewportParams& vp);
mat4 GetViewport(float x, float y, float w, float h, float depth);
bool Decompose(const mat4& model_mat, vec3& scale, quat& orientation, vec3& translation, vec3& skew, vec4& perspective);

template<class T, class K>
Vec<T,3> GetBarycentric(const Vec<T,3>* pts, const Vec<K,2>& P) {
	typedef Vec<T,3> vec3;
	typedef Vec<float,3> fvec3;
	fvec3 u = cross(
		fvec3(	pts[2][0] - pts[0][0],
				pts[1][0] - pts[0][0],
				pts[0][0] - P[0]),
		fvec3(	pts[2][1] - pts[0][1],
				pts[1][1] - pts[0][1],
				pts[0][1] - P[1]));
	/* `pts` and `P` has integer value as coordinates
	   so `abs(u[2])` < 1 means `u[2]` is 0, that means
	   triangle is degenerate, in this case return something with negative coordinates */
	if (std::abs(u[2]) < 1)
		return vec3(-1, 1, 1);
	return vec3(
		1.0 - (u[0] + u[1]) / u[2],
		              u[1]  / u[2],
		              u[0]  / u[2]);
}


void ColorCopy(const RGBA& src, vec3& dst);
void ColorCopy(const RGBA& src, vec4& dst);


Size ToSize(const vec2& v);
Point ToPoint(const vec2& v);
vec3 MakeVec3(float v[4]);
vec3 MakeVec3(double v[4]);
vec4 MakeVec4(const vec3& v, float v4);


double GetRadians(double degrees);
double GetDegrees(double radians);



template<class T>
T safe_normalize(T v) {
    float l = v.GetLength();
    if (l < EPSILON)
        return T(1);
    return v * (1 / l);
}

mat4 GetEulerAngleYXZ(const vec3& roll);
mat4 GetEulerAngleYX(const vec3& roll);
mat4 rotate(mat4 const& m, float angle, vec3 const& v);
quat make_quat_from_axis_angle(const vec3& v, float angle);
mat4 make_mat4_from_quat(const quat& q);
quat make_quat_from_yaw_pitch_roll(float yaw, float pitch, float roll);
mat4 make_mat4_rotation_x(float angle);
mat4 make_mat4_rotation_y(float angle);
mat4 make_mat4_rotation_z(float angle);
mat4 make_mat4_translation(const vec3& position);
quat make_quat_from_rotation_matrix(const mat4& matrix);
inline mat4 rotate(const quat& q) {return make_mat4_from_quat(q);}
inline mat4 make_mat4_from_yaw_pitch_roll(float yaw, float pitch, float roll) {return make_mat4_from_quat(make_quat_from_yaw_pitch_roll(yaw, pitch, roll));}

quat make_rotation_direction(const vec3& dir, const vec3& up);



namespace MatrixUtils {


inline vec3 right(const mat4& transform)
{
    return { +transform[0][0], +transform[0][1], +transform[0][2] };
}

inline vec3 left(const mat4& transform)
{
    return { -transform[0][0], -transform[0][1], -transform[0][2] };
}

inline vec3 up(const mat4& transform)
{
    return { +transform[1][0], +transform[1][1], +transform[1][2] };
}

inline vec3 down(const mat4& transform)
{
    return { -transform[1][0], -transform[1][1], -transform[1][2] };
}

inline vec3 backward(const mat4& transform)
{
    return { +transform[2][0], +transform[2][1], +transform[2][2] };
}

inline vec3 forward(const mat4& transform)
{
    return { -transform[2][0], -transform[2][1], -transform[2][2] };
}

inline vec3 position(const mat4& transform)
{
    return { +transform[3][0], +transform[3][1], +transform[3][2] };
}

inline quat orientation(const mat4& transform)
{
    vec3 baller_position, size, skew;
	quat orientation;
	vec4 persp;
	Decompose(transform, size, orientation, baller_position, skew, persp);
	return orientation;
}



inline mat4 RemoveScale(const mat4& transform)
{
    quat rotation;
    vec3 scale, translation, skew;
    vec4 pers;
    Decompose(transform, scale, rotation, translation, skew, pers);
    return translate(translation) * ToMat4(rotation);
}


}

inline float ConvertToRadians(float angle) {return (float)(angle / 180.0 * M_PI);}

void Multiply(mat3& res, const mat3& a, const mat3& b);
void SetCrossMatrixPlus(mat3& res, const vec3& a);
bool FactorCholesky(const mat3& A, vec3& out);
bool IsPositiveDefinite(const mat3& m);


vec2 Intersect(const vec2& a, const vec2& b, const vec2& c, const vec2& d);

NAMESPACE_TOPSIDE_END


#endif
	