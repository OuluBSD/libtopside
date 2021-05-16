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


mat4 perspective(float fov, float aspect, float near, float far);
mat4 ortho(float left, float right, float bottom, float top, float near, float far);
mat4 ToMat4(const quat& q);

template <class T> T cross(const T& a, const T& b) {return a.GetCrossProduct(b);}
template <class T> T inverse(const T& o) {return o.GetInverse();}
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

template <class T> T min(const T& a, const T& b) {return T::GetMin(a, b);}
template <class T> T max(const T& a, const T& b) {return T::GetMax(a, b);}
#define DEF_MINMAX(T) \
	template <> inline T min(const T& a, const T& b) {return a < b ? a : b;} \
	template <> inline T max(const T& a, const T& b) {return a > b ? a : b;}
DEF_MINMAX(int)
DEF_MINMAX(float)
DEF_MINMAX(double)

mat4 LookAt(const vec3& eye, const vec3& center, const vec3& up);
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
quat make_quat_from_axis_angle(vec3 v, float angle);
mat4 make_mat4_from_quat(const quat& q);
quat make_quat_from_yaw_pitch_roll(float yaw, float pitch, float roll);
mat4 make_mat4_rotation_x(float angle);
mat4 make_mat4_rotation_y(float angle);
mat4 make_mat4_rotation_z(float angle);
mat4 make_mat4_translation(const vec3& position);
quat make_quat_from_rotation_matrix(const mat4& matrix);
inline mat4 rotate(const quat& q) {return make_mat4_from_quat(q);}
inline mat4 make_mat4_from_yaw_pitch_roll(float yaw, float pitch, float roll) {return make_mat4_from_quat(make_quat_from_yaw_pitch_roll(yaw, pitch, roll));}




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
    return ToMat4(rotation) * translate(translation);
}


}


inline float ConvertToRadians(float angle) {return angle / 180.0 * M_PI;}


NAMESPACE_TOPSIDE_END


#endif
	