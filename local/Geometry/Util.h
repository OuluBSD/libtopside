#ifndef _Math_Util_h_
#define _Math_Util_h_


NAMESPACE_OULU_BEGIN


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
template<class T, class K> T scale(const T& a, const K& b) {return a.Scale(b);}
template<class T, class K> T translate(const T& a, const K& b) {return a.Translate(b);}
template<class T> float dot(const T& a, const T& b) {return a.GetDotProduct(b);}
vec3 combine(const vec3& a, const vec3& b, float ascl, float bscl);

inline mat4 scale(const vec3& b) {mat4 a; a.SetIdentity(); return a.Scale(b);}
inline mat4 translate(const vec3& b) {mat4 a; a.SetIdentity(); return a.Translate(b);}

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


quat MakeQuaternionFromAxisAngle(vec3 v, double s);


NAMESPACE_OULU_END


#endif
	