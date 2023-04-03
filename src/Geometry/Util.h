#ifndef _Math_Util_h_
#define _Math_Util_h_


NAMESPACE_TOPSIDE_BEGIN


template <class T> T zero() {T o; memset(&o, 0, sizeof(T));return o;}
template <class T> T one() {T o; o.SetConst(1.0); return o;}
template <class T> T Identity() {T o; o.SetIdentity(); return o;}

template <class T>
T Normalize(const T& a) {
	T o(a);
	o.Normalize();
	return o;
}

template <class T> T Mod(const T& a, float f) {return a.Modulus(f);}
template <class T> T Mix(const T& a, const T& b, float f) {return a.Mix(b, f);}


vec3 Lerp(const vec3& pos, const vec3& tgt_pos, float easing_factor);
quat Slerp(const quat& orient, const quat& tgt_orient, float easing_factor);

mat4 Perspective(float half_fov_rad, float aspect, float near, float far);
mat4 Ortho(float left, float right, float bottom, float top, float near, float far);

template <class T> T Cross(const T& a, const T& b) {return a.GetCrossProduct(b);}
template <class T> T Inverse(const T& o) {return o.GetInverse();}
template <class T> T Transpose(const T& o) {return o.GetTransposed();}
template<class T, class K> T Scale(const T& a, const K& b) {return a.Scale(b);}
template<class T, class K> T Translate(const T& a, const K& b) {return a.Translate(b);}
template<class T> float Dot(const T& a, const T& b) {return (float)a.GetDotProduct(b);}
vec3 Combine(const vec3& a, const vec3& b, float ascl, float bscl);

void ChangeZConvention(mat4& m);

inline vec3 VectorTransform(const vec3& v, const mat4& m) {return (v.Extend(1.0) * m).Splice();}
vec3 VectorTransform(const vec3& v, const quat& m);

vec3 Lerp(const vec3& pos, const vec3& tgt_pos, float easing_factor);
quat Slerp(const quat& orient, const quat& tgt_orient, float easing_factor);

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
mat2 FastInverse(const mat2& mat);
mat3 FastInverse(const mat3& mat);
mat4 FastInverse(const mat4& m);
bool Multiply(vec2& out, const vec2& v, const mat2& m);
bool Multiply(vec3& out, const vec3& v, const mat3& m);
bool Multiply(vec4& out, const vec4& v, const mat4& m);
float Dot(const vec2& a, const vec2& b);
float Dot(const vec3& a, const vec3& b);
//vec3 Cross(const vec3& l, const vec3& r);
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

mat2 Rotation2x2(float angle);

vec3 AxesDir(float yaw, float pitch);
vec3 AxesDirRoll(float pitch, float roll);
void DirAxes(vec3 dir, float& yaw, float& pitch);
void DirAxes(vec3 dir, vec3& axes);
vec3 GetDirAxes(const vec3& dir);
axes2 GetDirAxesRoll(vec3 dir);
vec3 GetAxesDir(const axes2& ax);
void CameraObject(
	const vec3& eye, const vec3& eye_dir, const vec3& eye_up,
	float obj_yaw_diff, float obj_pitch_diff, float obj_dist,
	vec3& position);


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
mat4 QuatMat(quat q);
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
mat4 Recompose(const vec3& scale, const quat& orientation, const vec3& translation, const vec3& skew, const vec4& perspective);
float Area3(const vec3& a, const vec3& b, const vec3& c);
float Area2(const vec2& a, const vec2& b, const vec2& c);
vec3 CrossArea3(vec3 a, vec3 b);
float CrossArea2(vec2 a, vec2 b);

template <class T> T Sign(T v) {
	if (v < 0)
		return -1;
	else
		return +1;
}


template<class T, class K>
Vec<T,3> GetBarycentricTriangle(const Vec<T,3>* pts, const Vec<K,2>& P) {
	typedef Vec<T,3> vec3;
	typedef Vec<float,3> fvec3;
	fvec3 u = Cross(
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
		1.0f - (u[0] + u[1]) / u[2],
		               u[1]  / u[2],
		               u[0]  / u[2]);
}

template<class T, class K>
Vec<T, 4> GetBarycentricQuad(const Vec<T, 4>* pts, const Vec<K, 2>& p) {
	typedef Vec<T,2> vec2;
	typedef Vec<T,3> vec3;
	typedef Vec<T,4> vec4;
	
	//https://jcgt.org/published/0011/03/04/paper.pdf
	
	// From pseudocode in [Hormann and Tarini 2004]
	T w[4] = {
		pts[0][3],
		pts[1][3],
		pts[2][3],
		pts[3][3]
	};
	T r[4], t[4], u[4];
	vec2 v[4] = {
		pts[0].template Splice<0,2>() / w[0],
		pts[1].template Splice<0,2>() / w[1],
		pts[2].template Splice<0,2>() / w[2],
		pts[3].template Splice<0,2>() / w[3]
	};
	vec2 s[4];
	
	for (int i = 0; i < 4; i++) {
		s[i] = v[i] - p;
		r[i] = s[i].GetLength() * Sign(w[i]);
	}
	
	for (int i = 0; i < 4; i++) {
		T A = CrossArea2(s[i], s[(i+1)%4]);
		T D = Dot(s[i], s[(i+1)%4]);
		t[i] = (r[i] * r[(i+1)%4] - D) / A;
	}
	
	for (int i = 0; i < 4; i++)
		u[i] = (t[(i+3)%4] + t[i]) / r[i];
		
	return
		vec4((float)u[0], (float)u[1], (float)u[2], (float)u[3]) / (u[0] + u[1] + u[2] + u[3]);
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

float VectorAngle(const vec2& a, const vec2& b);
float VectorAngle(const vec3& a, const vec3& b);


template<class T>
T safe_normalize(T v) {
    float l = v.GetLength();
    if (l < EPSILON)
        return T(1);
    return v * (1 / l);
}

mat4 GetEulerAngleYXZ(const vec3& roll);
mat4 GetEulerAngleYX(const vec3& roll);
mat4 Rotate(mat4 const& m, float angle, vec3 const& v);
quat AxisAngleQuat(const vec3& v, float angle);
//mat4 QuatMat(const quat& q);
quat AxesQuat(float yaw, float pitch, float roll);
quat AxesQuat(const vec3& axes);
mat4 XRotation(float angle);
mat4 YRotation(float angle);
mat4 ZRotation(float angle);
mat4 Translate(const vec3& position);
mat4 Scale(const vec3& scale);
//mat4 Rotate(const quat& q);
mat4 AxesMat(float yaw, float pitch, float roll);
mat4 AxesMat(const vec3& axes);

//quat make_rotation_direction(const vec3& dir, const vec3& up);

void QuatAxes(const quat& q, float& yaw, float& pitch, float& roll);
void QuatAxes(const quat& q, vec3& axes);
vec3 GetQuatAxes(const quat& q);
//void MatAxes(const mat4& m, vec3& axes);

quat MatQuat(const mat4& transform);

mat4 SkewMat(const vec3& v, float ident_value=1.0f);
mat4 SkewMat(const vec4& v, float ident_value=1.0f);



vec3 Right(const mat4& transform);
vec3 Left(const mat4& transform);
vec3 Up(const mat4& transform);
vec3 Down(const mat4& transform);
vec3 Backward(const mat4& transform);
vec3 Forward(const mat4& transform);
vec3 Position(const mat4& transform);




mat4 RemoveScale(const mat4& transform);

inline float ConvertToRadians(float angle) {return (float)(angle / 180.0 * M_PI);}

void Multiply(mat3& res, const mat3& a, const mat3& b);
void SetCrossMatrixPlus(mat3& res, const vec3& a);
bool FactorCholesky(const mat3& A, vec3& out);
bool IsPositiveDefinite(const mat3& m);


vec2 Intersect(const vec2& a, const vec2& b, const vec2& c, const vec2& d);


vec3 GetVelocityNearSourceLocation(
	    const vec3& grasp_position,
	    const vec3& grasp_velocity,
	    const vec3& angular_velocity,
	    const vec3& position_near_source_location);


quat TurnLeft(float angle);
quat TurnRight(float angle);
quat TurnUp(float angle);
quat TurnDown(float angle);

quat SwapHandedness(const quat& input);
String Plot(const vec3& a, const vec3& b);




bool IsClose(const quat& a, const quat& b);
bool IsClose(const vec3& a, const vec3& b, float dist_limit=0.001);
bool IsClose(const vec4& a, const vec4& b);
bool IsClose(const mat4& a, const mat4& b);
bool IsClose(const axes2& a, const axes2& b, float dist_limit=0.001);
bool IsClose(const axes3s& a, const axes3s& b, float dist_limit=0.001);

axes2s LookAtStereoAngles(float eye_dist, const vec3& pt);
axes2s LookAtStereoAngles(float eye_dist, const vec3& pt, axes2& l, axes2& r);
void AxesStereoMono(const axes2s& axes, axes2& l, axes2& r);
axes2s AxesMonoStereo(const axes2& l, const axes2& r);
vec2 CalculateThirdPoint(const vec2& a, const vec2& b, float alp1, float alp2);
vec2 CalculateStereoThirdPoint(float eye_dist, float a1, float a2);
bool CalculateStereoTarget(const axes2s& stereo_axes, float eye_dist, vec3& dir_c);
bool CalculateTriangleChange(const vec3& a0, const vec3& a1, const vec3& a2, const vec3& b0, const vec3& b1, const vec3& b2, mat4& out);
bool CalculateTriangleChange(vec3 local, vec3 prev0, vec3 prev1, vec3 cur0, vec3 cur1, mat4& out);


vec3 VecMul(const mat4& m, const vec3& v);
void GetPrincipalAxes(const vec3& a, const vec3& b, vec3& x, vec3& y, vec3& z);
mat4 GetPrincipalAxesMat(const vec3& a, const vec3& b);


void MakeSpecBRDF(FloatImage& img, int sz);



NAMESPACE_TOPSIDE_END


#endif
	