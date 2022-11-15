#ifndef _Math_Matrix_h_
#define _Math_Matrix_h_

NAMESPACE_TOPSIDE_BEGIN

#define STRICT_MTX_CHECK(x) ASSERT(x)

#if IS_NEGATIVE_Z
	#define VEC_FWD vec3(0,0,-1)
	#define VEC_FWD4 vec4(0,0,-1,1)
	#define VEC_BWD vec3(0,0,1)
	#define VEC_BWD4 vec4(0,0,1,1)
	#define SCALAR_FWD_Z -1
	#define VEC_POS_ROT vec3(1,1,-1)
	#define VEC_POS_ROT4 vec3(1,1,-1,1)
#else
	#define VEC_FWD vec3(0,0,1)
	#define VEC_FWD4 vec4(0,0,1,1)
	#define VEC_BWD vec3(0,0,-1)
	#define VEC_BWD4 vec4(0,0,-1,1)
	#define SCALAR_FWD_Z 1
	#define VEC_POS_ROT vec3(1,1,1)
	#define VEC_POS_ROT4 vec3(1,1,1,1)
#endif
#define VEC_LEFT vec3(-1,0,0)
#define VEC_LEFT4 vec4(-1,0,0,1)
#define VEC_RIGHT vec3(1,0,0)
#define VEC_RIGHT4 vec4(1,0,0,1)
#define VEC_UP vec3(0,1,0)
#define VEC_UP4 vec4(0,1,0,1)
#define VEC_DOWN vec3(0,-1,0)
#define VEC_DOWN4 vec4(0,-1,0,1)
#define VEC_X vec3(1,0,0)
#define VEC_Y vec3(0,1,0)
#define VEC_Z vec3(0,0,1)

#if IS_CW_ANGLE
	#define A_PI (-M_PI)
	#define VEC_ROT_LEFT axes3(-1,0,0)
	#define VEC_ROT_RIGHT axes3(+1,0,0)
	#define VEC_ROT_UP axes3(0,-1,0)
	#define VEC_ROT_DOWN axes3(0,+1,0)
#else
	#define A_PI M_PI
	#define VEC_ROT_LEFT axes3(+1,0,0)
	#define VEC_ROT_RIGHT axes3(-1,0,0)
	#define VEC_ROT_UP axes3(0,+1,0)
	#define VEC_ROT_DOWN axes3(0,-1,0)
#endif

template <class T, int I> struct PartVec {};
template <class T, int R, int C, class Precise=double> struct Matrix;

template <class T> struct PartVec<T, 2> {
	static inline T GetCrossProduct(const T& a, const T& b);
};

template <class T> struct PartVec<T, 3> {
	static inline T GetCrossProduct(const T& a, const T& b);
};

template <class T> struct PartVec<T, 4> {
	static inline T GetCrossProduct(const T& a, const T& b);
};

template <class T, int I>
struct Vec : Moveable<Vec<T, I> > {
	static const int size = I;
	using Unit = T;
	
	T data[I];
	
	
	Vec() {for(int i = 0; i < I; i++) data[i] = 0;}
	Vec(Vec&& v) {memcpy(this, &v, sizeof(Vec));}
	Vec(const Vec& v) {memcpy(this, &v, sizeof(Vec));}
	Vec(T value) {SetConst(value);}
	Vec(T x, T y) {Set(x,y); ClearFrom(2);}
	Vec(T x, T y, T z) {Set(x,y,z); ClearFrom(3);}
	Vec(T x, T y, T z, T w) {Set(x,y,z,w); ClearFrom(4);}
	Vec(std::initializer_list<T> list) {
		if (list.size() == 1) {
			for(auto& v : list) {
				for(int i = 0; i < I; i++) data[i] = v;
			}
		}
		else {
			int i = 0;
			for(auto& v : list) {data[i++] = v; if (i >= I) break;}
			while (i < I) data[i++] = 0;
		}
	}
	Vec(Nuller) {SetNull();}
	//Vec(const byte* b, T mul, T offset) {Set(b, mul, offset);}
	
	void SetNull() {for(int i = 0; i < I; i++) data[i] = std::numeric_limits<T>::max();}
	bool IsNull() const {for(int i = 0; i < I; i++) if (data[i] != std::numeric_limits<T>::max()) return false; return true;}
	//operator bool() const {return !IsNull();}
	
	void Clear() {memset(this, 0, sizeof(Vec));}
	void ClearFrom(int i) {for(; i < I; i++) data[i] = 0;}
	
	hash_t GetHashValue() const {
		CombineHash c;
		for(int i = 0; i < I; i++) c.Put(UPP::GetHashValue((double)data[i]));
		return c;
	}
	T& operator[](int i) {STRICT_MTX_CHECK(i >= 0 && i < I); return data[i];}
	const T& operator[](int i) const {STRICT_MTX_CHECK(i >= 0 && i < I); return data[i];}
	
	Vec& operator=(const Vec& v) {for(int i = 0; i < I; i++) data[i] = v.data[i]; return *this;}
	Vec& operator*=(T v) {for(int i = 0; i < I; i++) data[i] *= v; return *this;}
	Vec& operator/=(T v) {for(int i = 0; i < I; i++) data[i] /= v; return *this;}
	template<int J> Vec& operator+=(const Vec<T,J>& v) {for(int i = 0; i < std::min(I,J); i++) data[i] += v.data[i]; return *this;}
	
	Vec operator-()             const {Vec r; for(int i = 0; i < I; i++) r.data[i] = -data[i]; return r;}
	Vec operator-(const Vec& v) const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] - v.data[i]; return r;}
	Vec operator+(const Vec& v) const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] + v.data[i]; return r;}
	Vec operator*(T v)          const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] * v; return r;}
	Vec operator/(T v)          const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] / v; return r;}
	Vec operator^(const Vec& v) const {return GetCrossProduct(v);}
	//T   operator*(const Vec& v) const {return GetDotProduct(v);}
	Vec operator*(const Vec& v) const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] * v.data[i]; return r;}
	Vec operator/(const Vec& v) const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] / v.data[i]; return r;}
	
	Vec Multiply(const Vec& v)  const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] * v.data[i]; return r;}
	Vec Multiply(T v)           const {Vec r; for(int i = 0; i < I; i++) r.data[i] = data[i] * v; return r;}
	Vec Modulus(T v)            const {Vec r; for(int i = 0; i < I; i++) r.data[i] = fmod(data[i], v); return r;}
	Vec Mix(const Vec& v, T f)  const {Vec r; for(int i = 0; i < I; i++) r.data[i] = (1.0 - f) * data[i] + f * v.data[i]; return r;}
	
	Vec operator*(const Matrix<T,I,I>& m) const;
	
	bool operator==(const Vec& v) const {for(int i = 0; i < I; i++) if (data[i] != v.data[i]) return false; return true;}
	bool operator!=(const Vec& v) const {return !(*this == v);}
	bool operator<=(const Vec& v) const {for(int i = 0; i < I; i++) if (data[i] > v.data[i]) return false; return true;}
	bool operator>=(const Vec& v) const {for(int i = 0; i < I; i++) if (data[i] < v.data[i]) return false; return true;}
	
	T GetMagnitude() const {return FastSqrt(Dot(*this));}
	T GetMagnitudeSq() const {return Dot(*this);}
	
	Vec& Normalize(bool unsafe=false) {
		T mag = 0;
		for(int i = 0; i < I; i++) mag += data[i] * data[i];
		if (unsafe && mag == 0) return *this;
		ASSERT_(mag != 0, "zero magnitude vector");
		mag = 1 / std::sqrt(mag);
		for(int i = 0; i < I; i++) data[i] *= mag;
		return *this;
	}
	Vec& Set(T x) {static_assert(I >= 1, "Invalid ctor"); data[0] = x; return *this;}
	Vec& Set(T x, T y) {static_assert(I >= 2, "Invalid ctor"); data[1] = y; return Set(x);}
	Vec& Set(T x, T y, T z) {static_assert(I >= 3, "Invalid ctor"); data[2] = z; return Set(x,y);}
	Vec& Set(T x, T y, T z, T w) {static_assert(I >= 4, "Invalid ctor"); data[3] = w; return Set(x,y,z);}
	Vec& SetData(const byte* b, T mul, T offset) {for(int i = 0; i < I; i++) data[i] = ((T)b[i] / (T)255) * mul + offset; return *this;}
	
	Vec& SetConst(const T& value) {for(int i = 0; i < I; i++) data[i] = value; return *this;}
	Vec& SetIdentity() {for(int i = 0; i < I; i++) data[i] = (T)(i == 0 ? 1 : 0); return *this;}
	template <int begin=0, int end=I-1> Vec& SetFromSplice(const Vec<T, end - begin>& src) {
		static_assert(begin < end, "Splicing area must be positive");
		static_assert(end - begin <= I, "Splicing area must be less or equal to source area");
		for(int i = begin, j = 0; i < end; i++, j++) data[i] = src.data[j];
		return *this;
	}
	template <int from_i=I-1> Vec& Project() {ASSERT(data[from_i] != 0.0); static_assert(from_i >= 0 && from_i < I, "Invalid project pos");for(int i = 0; i < I; i++) if (i != from_i) data[i] /= data[from_i]; data[from_i] = 1.0; return *this;}
	
	Vec<T, I-1> Cut(int c) {
		Vec<T, I-1> v;
		for(int i = 0, j = 0; i < I && j < I; i++)
			if (i != c) v.data[j++] = data[i];
		return v;
	}
	template <int begin=0, int end=I-1> Vec<T, end - begin> Splice() const {
		static_assert(begin < end, "Splicing area must be positive");
		static_assert(end - begin <= I, "Splicing area must be less or equal to source area");
		Vec<T, end - begin> ret;
		for(int i = begin, j = 0; i < end; i++, j++) ret.data[j] = data[i];
		return ret;
	}
	template <int J=I+1> Vec<T,J> Embed() const {return Extend<J>(1.0f);}
	template <int J=I+1> Vec<T,J> Extend(float value=0.0) const {
		Vec<T,J> ret;
		for(int i = 0; i < I; i++) ret[i] = data[i];
		for(int j = I; j < J; j++) ret[j] = value;
		return ret;
	}
	
	T GetLengthSquared() const {T r = 0; for(int i = 0; i < I; i++) r += data[i] * data[i]; return r;}
	T GetLength() const {return std::sqrt(GetLengthSquared());}
	T GetAngle(const Vec& v) const {
		T m = std::sqrt(GetLengthSquared() + v.GetLengthSquared());
		return FastACos((*this * v) / m);
		//T m = pow(GetLengthSquared() + v.GetLengthSquared(), 0.5); return acos((*this * v) / m);
	}
	
	Vec GetNormalized() const {Vec v(*this); v.Normalize(); return v;}
	T   GetDotProduct(const Vec& v) const {T r = 0; for(int i = 0; i < I; i++) r += data[i] * v.data[i]; return r;}
	Vec GetCrossProduct(const Vec& b) const {return PartVec<Vec,I>::GetCrossProduct(*this, b);}
	Vec GetProjection(const Vec& v) const {return *this * (v.Dot(*this) / GetLengthSquared());}
	Vec GetReflection(const Vec& surf_normal) const {return *this - surf_normal * ((*this * surf_normal) * (T)2);}
	Vec	GetAbsolute() const {Vec v(*this); for(int i = 0; i < I; i++) if (v.data[i] < 0) v.data[i] *= -1; return v;}
	T   Dot(const Vec& v) const {return GetDotProduct(v);}
	Vec Scale(T target_len) const {
		Vec v;
		T mul = target_len / GetLength();
		for(int i = 0; i < I; i++)
			v.data[i] = data[i] * mul;
		return v;
	}
	
	static Vec GetMin(const Vec& a, const Vec& b) {Vec r; for(int i = 0; i < I; i++) r.data[i] = std::min(a.data[i], b.data[i]); return r;}
	static Vec GetMax(const Vec& a, const Vec& b) {Vec r; for(int i = 0; i < I; i++) r.data[i] = std::max(a.data[i], b.data[i]); return r;}
	
	String ToString() const {
		StringStream s;
		s.Reserve(256);
		s << "[";
		for(int i = 0; i < I; i++) {
			if (i) s << ", ";
			s << ::UPP::AsString(data[i]);
		}
		s << "]";
		return s.GetResult();
	}
	
	
	operator Point_<T>() const {
		static_assert(I == 2, "Losing information when converting to Point_<T>");
		return Point_<T>(data[0], data[1]);
	}
};


typedef Vec<float, 1> vec1;
typedef Vec<float, 2> vec2;
typedef Vec<float, 3> vec3;
typedef Vec<float, 4> vec4;
typedef Vec<double, 1> dvec1;
typedef Vec<double, 2> dvec2;
typedef Vec<double, 3> dvec3;
typedef Vec<double, 4> dvec4;
typedef Vec<float, 2> axes2;
typedef Vec<float, 3> axes3;
typedef Vec<float, 3> axes2s; // stereo angle [left yaw, right yaw, pitch]
typedef Vec<float, 4> axes3s; // stereo angle [left yaw, right yaw, pitch, roll]

typedef Vec<int, 2> ivec2;
typedef Vec<int, 3> ivec3;
typedef Vec<int, 4> ivec4;


struct quat {
	vec4 data;
	
	quat() {}
	quat(const quat& q) {*this = q;}
	quat(float x, float y, float z, float w) : data(x,y,z,w) {}
	
	void operator=(const quat& q) {data = q.data;}
	
	void Clear() {data.Clear();}
	void SetNull() {data.SetNull();}
	bool IsNull() const {return data.IsNull();}
	
	quat& SetIdentity() {data = vec4{0,0,0,1}; return *this;}
	quat& Normalize() {data.Normalize(); return *this;}
	
	const float& operator[](int i) const {return data[i];}
	float& operator[](int i) {return data[i];}
	quat GetConjugate() const;
	quat GetInverse() const {return GetConjugate();}
	
	quat operator-() const;
	quat operator+(const quat& q) const;
	quat operator-(const quat& q) const;
	quat operator*(const quat& q) const;
	quat operator*(float f) const;
	quat operator/(float f) const;
	void operator+=(const quat& q) {for(int i = 0; i < 4; i++) data.data[i] += q.data.data[i];}
	void operator-=(const quat& q) {for(int i = 0; i < 4; i++) data.data[i] -= q.data.data[i];}
	void operator*=(const quat& q) {quat n = *this * q; data = n.data;}
	
	float GetDotProduct(const quat& q) const;
	quat Mix(const quat& q, float f) const;
	
	String ToString() const {return data.ToString();}
	
	hash_t GetHashValue() const {return data.GetHashValue();}
	
};

template <class Unit, class M> inline void DeterminantNonSingle(Unit& det, const M& m) {
	det = 0;
	for(int c = 0; c < m.cols; c++)
		det += m[0][c] * m.GetCofactor(0, c);
}

template <class T, int R, int C> struct PartMatrix {
	typedef typename T::Unit Unit;
	
	static inline void Determinant(Unit& det, const T& m) {DeterminantNonSingle(det, m);}
	
};

template <class T> struct PartMatrix<T, 1, 1> {
	typedef typename T::Unit Unit;
	
	static inline void Determinant(Unit& det, const T& m) {det = m[0][0];}
	
};

template <class T> struct PartMatrix<T, 3, 3> {
	enum {X, Y, Z};
	
	typedef typename T::Unit Unit;
	
	static inline void Determinant(Unit& det, const T& m) {DeterminantNonSingle(det, m);}
	static inline void Adjoint(T& a, const T& m);
};

template <class T> struct PartMatrix<T, 4, 4> {
	enum {X, Y, Z, W};
	
	typedef typename T::Unit Unit;
	
	static inline void Determinant(Unit& det, const T& m);
	static inline void Adjoint(T& a, const T& m);
};



template <class T, int R, int C, class Precise>
struct Matrix : Moveable<Matrix<T,R,C,Precise> > {
	Vec<T, C> data[R];
	
	typedef T Unit;
	typedef Vec<T, C> vec;
	typedef Vec<T, R> vecR;
	typedef Matrix<T, R, C> mat;
	typedef Matrix<T, R-1, C-1> MinorMatrix;
	typedef Vec<T, C-1> MinorVec;
	typedef Matrix<Precise, R, C, Precise> PreciseMatrix;
	
	static const int rows = R;
	static const int cols = C;
	
	
	Matrix() {}
	Matrix(const Matrix& m) {*this = m;}
	Matrix(std::initializer_list<vec> list) {
		if (list.size() != R)
			Panic("invalid initializer_list size to matrix");
		int i = 0; for(auto& v : list) {data[i] = v; i++;}
	}
	Matrix(std::initializer_list<float> list) {
		if (list.size() != R*C)
			Panic("invalid initializer_list size to matrix");
		int i = 0; for(auto& v : list) {data[i / C].data[i % C] = v; i++;}
	}
	
	void SetNull() {for(int i = 0; i < R; i++) data[i].SetNull();}
	bool IsNull() const {for(int i = 0; i < R; i++) if (!data[i].IsNull()) return false; return true;}
	
	void Set(T* v) {for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) data[i].data[j] = *v++;}
	
	void operator=(const Matrix& m) {for(int i = 0; i < R; i++) data[i] = m.data[i];}
	vec& operator[](int i) {STRICT_MTX_CHECK(i >= 0 && i < R); return data[i];}
	const vec& operator[](int i) const {STRICT_MTX_CHECK(i >= 0 && i < R); return data[i];}
	
	vecR GetColumn(int c) const {ASSERT(c >= 0 && c < C); vecR v; for(int i = 0; i < R; i++) v[i] = data[i][c]; return v;}
	
	T* AsArray() {
		thread_local static T t[C*R];
		int k = 0;
		for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) t[k++] = data[i].data[j];
		return t;
	}
	Matrix<T,C-1,R-1> Cut(int r, int c) const {
		Matrix<T,C-1,R-1> m;
		for(int a = 0, b = 0; a < R && b < R; a++) {
			if (a != r) {
				const auto& src = data[a];
				auto& dst = m.data[b++];
				for(int i = 0, j = 0; i < C && j < C; i++)
					if (i != c) dst[j++] = src[i];
			}
		}
		return m;
	}
	Matrix<T,C+1,R+1> Extend(T value=0) const {
		Matrix<T,C+1,R+1> m;
		for(int i = 0; i < R; i++)
			for(int j = 0; j < C; j++)
				m.data[i].data[j] = data[i].data[j];
		for(int i = 0; i < R+1; i++)
			m.data[i].data[C] = value;
		for(int i = 0; i < C; i++)
			m.data[R].data[i] = value;
		return m;
	}
	Matrix<T,C,R> GetTransposed() const {
		Matrix<T,C,R> ret;
		for(int c = 0; c < C; c++)
			for(int r = 0; r < R; r++)
				ret.data[c][r] = data[r][c];
		return ret;
	}
	MinorMatrix GetMinor(int row, int col) const {
		MinorMatrix ret;
		for(int r = 0; r < R-1; r++)
			for(int c = 0; c < C-1; c++)
				ret[r][c] = data[r < row ? r : r+1][c < col ? c : c+1];
		return ret;
	}
	T GetCofactor(int row, int col) const {
		return GetMinor(row, col).GetDeterminant() *
			((row + col) % 2 ? (T)-1 : (T)1);
	}
	Matrix GetAdjugated() const {
		Matrix ret;
		for(int r = 0; r < R; r++)
			for(int c = 0; c < C; c++)
				ret[r][c] = GetCofactor(r, c);
		return ret;
	}
	Matrix GetInverseTransposed() const {
		Matrix ret = GetAdjugated();
		T d = Dot(ret[0], data[0]);
		ret /= d;
		return ret;
	}
	Matrix GetInverse() const {
		PreciseMatrix pm;
		CopyTo(pm);
		Matrix result;
		pm.GetInverseTransposed().GetTransposed().CopyTo(result);
		return result;
	}
	Matrix GetAdjoint() const {Matrix dst; PartMatrix<Matrix,R,C>::Adjoint(dst, *this); return dst;}
	T GetDeterminant() const {T ret; PartMatrix<Matrix,R,C>::Determinant(ret, *this); return ret;}
	String ToString() const {
		String s;
		for(int r = 0; r < R; r++) {
			s << (r == 0 ? "[[\t" : " [\t");
			for(int c = 0; c < C; c++) {
				if (c) s << ",\t";
				s << AsString(data[r][c]);
			}
			s << (r == R-1 ? "\t]]" : "\t],\n");
		}
		return s;
	}
	
	void Clear() {for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) data[i].data[j] = 0;}
	void Zero()  {for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) data[i].data[j] = 0;}
	
	template <class M> void CopyTo(M& o) const {
		for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) o.data[i].data[j] = data[i].data[j];
	}
	
	Matrix& Transpose() {
		for(int c = 0; c < C; c++)
			for(int r = 0; r < R; r++)
				if (c != r)
					data[c][r] = data[r][c];
		return *this;
	}
	
	Matrix& SetColumn(int col, const vecR& v) {
		ASSERT(col >= 0 && col < C);
		for(int r = 0; r < R; r++)
			data[r][col] = v[r];
		return *this;
	}
	
	Matrix& SetConst(const T& value) {
		for(int r = 0; r < R; r++)
			data[r].SetConst(value);
		return *this;
	}
	
	Matrix& SetIdentity() {
		for(int r = 0; r < R; r++)
			for(int c = 0; c < C; c++)
				data[r].data[c] = (T)(r == c ? 1 : 0);
		return *this;
	}
	
	Matrix& SetComponentTranslate(T x, T y, T z) {
		data[3][0] = x;
		data[3][1] = y;
		data[3][2] = z;
		return *this;
	}
	
	Matrix& SetComponentScale(T x, T y, T z) {
		data[0][0] = x;
		data[1][1] = y;
		data[2][2] = z;
		return *this;
	}
	
	Matrix& SetTranslate(T x, T y, T z) {SetIdentity().SetComponentTranslate(x, y, z); return *this;}
	Matrix& SetScale(T scale) {SetIdentity().SetComponentScale(scale, scale, scale); return *this;}
	
	vec3 GetTranslation() const {
		return vec3(	data[3][0],
						data[3][1],
						data[3][2]);
	}
	
	Matrix& SetRotation(int axis, float angle_rad) {
		static_assert(R == C && R >= 3, "Expecting square matrix of at least size 3");
		SetIdentity();
		T s = FastSin(angle_rad);
		T c = FastCos(angle_rad);
		if (axis == 0) {
			data[1][1] = c;
			data[1][2] = s;
			data[2][1] = -s;
			data[2][2] = c;
		}
		else if (axis == 1) {
			data[0][0] = c;
			data[0][2] = -s;
			data[2][0] = s;
			data[2][2] = c;
		}
		else if (axis == 2) {
			data[0][0] = c;
			data[0][1] = s;
			data[1][0] = -s;
			data[1][1] = c;
		}
		return *this;
	}
	Matrix& SetRotation(const vec3& axis, float angle_rad) {*this = GetRotation(axis, angle_rad); return *this;}
	Matrix& SetPerspectiveRH_ZO(T fov_rad, T aspect, T near, T far) {
		ASSERT(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
		T const tan_half_fovy = tan(fov_rad / static_cast<T>(2));
		data[0][0] = static_cast<T>(1) / (aspect * tan_half_fovy);
		data[1][1] = static_cast<T>(1) / (tan_half_fovy);
		data[2][2] = far / (near - far);
		data[2][3] = - static_cast<T>(1);
		data[3][2] = -(far * near) / (far - near);
		return *this;
	}
	Matrix& SetPerspectiveRH_PZO(T fov_rad, T aspect, T near, T far) {
		ASSERT(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
		T const tan_half_fovy = tan(fov_rad / static_cast<T>(2));
		data[0][0] = -static_cast<T>(1) / (aspect * tan_half_fovy);
		data[1][1] = static_cast<T>(1) / (tan_half_fovy);
		data[2][2] = (far + near) / (far - near);
		data[2][3] = static_cast<T>(1);
		data[3][2] = - (static_cast<T>(2) * far * near) / (far - near);
		return *this;
	}
	Matrix& SetPerspectiveRH_NO(T fov_rad, T aspect, T near, T far) {
		ASSERT(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
		T const tan_half_fovy = tan(fov_rad / static_cast<T>(2));
		data[0][0] = static_cast<T>(1) / (aspect * tan_half_fovy);
		data[1][1] = static_cast<T>(1) / (tan_half_fovy);
		data[2][2] = - (far + near) / (far - near);
		data[2][3] = - static_cast<T>(1);
		data[3][2] = - (static_cast<T>(2) * far * near) / (far - near);
		return *this;
	}
	Matrix& SetPerspectiveLH_ZO(T fov_rad, T aspect, T near, T far) {
		ASSERT(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
		T const tan_half_fovy = tan(fov_rad / static_cast<T>(2));
		data[0][0] = static_cast<T>(1) / (aspect * tan_half_fovy);
		data[1][1] = static_cast<T>(1) / (tan_half_fovy);
		data[2][2] = far / (far - near);
		data[2][3] = static_cast<T>(1);
		data[3][2] = -(far * near) / (far - near);
		return *this;
	}
	Matrix& SetPerspectiveLH_NO(T fov_rad, T aspect, T near, T far) {
		ASSERT(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
		T const tan_half_fovy = tan(fov_rad / static_cast<T>(2));
		data[0][0] = static_cast<T>(1) / (aspect * tan_half_fovy);
		data[1][1] = static_cast<T>(1) / (tan_half_fovy);
		data[2][2] = (far + near) / (far - near);
		data[2][3] = static_cast<T>(1);
		data[3][2] = - (static_cast<T>(2) * far * near) / (far - near);
		return *this;
	}
	Matrix& SetPerspective(T fov_rad, T aspect, T near, T far) {
		#if IS_NEGATIVE_Z
		return SetPerspectiveRH_ZO(fov_rad, aspect, near, far);
		#elif 0
		return SetPerspectiveRH_PZO(fov_rad, aspect, near, far);
		#elif 0
		return SetPerspectiveRH_NO(fov_rad, aspect, near, far);
		#elif !IS_NEGATIVE_Z
		return SetPerspectiveLH_ZO(fov_rad, aspect, near, far);
		#elif 0
		return SetPerspectiveLH_NO(fov_rad, aspect, near, far);
		#endif
	}
	Matrix& SetOrtographic(T left, T right, T bottom, T top, T near, T far) {
		Clear();
		SetComponentScale(		2.0f / (right - left),
								2.0f / (top - bottom),
								1.0f / (far - near));
		SetComponentTranslate(	(left + right) / (left - right),
								(top + bottom) / (bottom - top),
								(near) / (near - far));
		data[3][3] = 1;
		return *this;
	}
	
	static Matrix GetRotation(const vec3& axis, float angle_rad) {
		T s = FastSin(angle_rad);
		T c = FastCos(angle_rad);
		T t = (T)1.0 - c;
		T x = axis[0], y = axis[1], z = axis[2];
		if (axis.GetLengthSquared() != (T)1.0) {
			T mul = (T)1 / axis.GetLength();
			x *= mul;
			y *= mul;
			z *= mul;
		}
		return Matrix {	vec{t*(x*x) + c, t*x*y + s*z, t*x*z - s*y, 0.0f},
						vec{t*x*y - s*z, t*(y*y) + c, t*y*z + s*x, 0.0f},
						vec{t*x*z + s*y, t*y*z - s*x, t*(z*z) + c, 0.0f},
						vec{0.0f,        0.0f,        0.0f,        1.0f}};
	}
	
	#if 0
	vecR operator*(const vec& src) const {
		vecR ret;
		for(int r = 0; r < R; r++) {
			const vec& row = data[r];
			T& v = ret[r];
			v = 0;
			for(int c = 0; c < C; c++)
				v += row[c] * src[c];
		}
		return ret;
	}
	#else
	vecR operator*(const vec& src) const {
		vecR ret;
		for(int r = 0; r < R; r++) {
			T& v = ret[r];
			v = 0;
			for(int c = 0; c < C; c++)
				v += data[c][r] * src[c];
		}
		return ret;
	}
	#endif
	
	bool operator==(const Matrix& m) const {
		for(int r = 0; r < R; r++)
			if (!(data[r] == m.data[r]))
				return false;
		return true;
	}
	bool operator!=(const Matrix& m) const {return !(*this == m);}
	bool IsClose(const Matrix& m) const {
		for(int r = 0; r < R; r++)
			for(int c = 0; c < C; c++)
				if (!TS::IsClose(data[r][c], m.data[r][c]))
					return false;
		return true;
	}
		
	
	Matrix& operator*=(const Matrix<T,R,C>& src) {*this = Multiply(src); return *this;}
	Matrix& operator*=(T v) {for(int i = 0; i < R; i++) data[i] *= v; return *this;}
	Matrix& operator/=(T v) {for(int i = 0; i < R; i++) data[i] /= v; return *this;}
	
	Matrix operator*(T m) const {return Multiply(m);}
	template<int R2> Matrix<T,R2,C> operator*(const Matrix<T,R2,R>& src) const {return Multiply(src);}
	
	Matrix Multiply(T f) const {
		Matrix m;
		for(int r = 0; r < R; r++)
			for(int c = 0; c < C; c++)
				m.data[r].data[c] = data[r].data[c] * f;
		return m;
	}
	template<int R2> Matrix<T,R2,C> Multiply(const Matrix<T,R2,R>& src) const {
		Matrix<T,R2,C> m;
		for(int c = 0; c < C; c++) {
			for(int r2 = 0; r2 < R2; r2++) {
				T o = 0;
				for(int r = 0; r < R; r++) {
					T aa = src.data[r2][r];
					T bb = data[r][c];
					T mul = aa * bb;
					o += mul;
				}
				m[r2][c] = o;
			}
		}
		return m;
	}
	Matrix Translate(const MinorVec& v) const {
		static_assert(R == C, "must be square matrix");
		Matrix m;
		m.SetIdentity();
		for(int i = 0; i < C-1; i++)
			m.data[R-1][i] = v.data[i];
		return m.Multiply(*this);
	}
	Matrix Scale(const MinorVec& v) const {
		static_assert(R == C, "must be square matrix");
		Matrix m;
		m.Clear();
		for(int i = 0; i < R-1; i++)
			m.data[i][i] = v[i];
		m.data[R-1][R-1] = 1;
		return m.Multiply(*this);
	}
	
	
	operator const vec2& () {static_assert(R == 1 && C == 2, "Expecting Matrix<1,2>"); return data[0];}
	operator const vec3& () {static_assert(R == 1 && C == 3, "Expecting Matrix<1,3>"); return data[0];}
	operator const vec4& () {static_assert(R == 1 && C == 4, "Expecting Matrix<1,4>"); return data[0];}
	
	hash_t GetHashValue() const {
		CombineHash c;
		for(int i = 0; i < R; i++) c.Put(data[i].GetHashValue());
		return c;
	}
	
	template <int begin=0, int end0=R-1, int end1=C-1> Matrix<T, end0 - begin, end1-begin> Splice() const {
		static_assert(begin < end0 && begin < end1, "Splicing area must be positive");
		static_assert(end0 - begin <= C && end1 - begin <= R, "Splicing area must be less or equal to source area");
		Matrix<T, end0 - begin, end1-begin> ret;
		for(int i = begin, k = 0; i < end0; i++, k++)
			for(int j = begin, l = 0; j < end1; j++, l++)
				ret.data[k].data[l] = data[i].data[j];
		return ret;
	}
	template <int R0=R+1,int C0=C+1> Matrix<T,R0,C0> Embed() const {
		Matrix<T,R0,C0> ret;
		ret.Zero();
		for (int r = 0; r < R && r < R0; r++)
			for (int c = 0; c < C && c < C0; c++)
				ret.data[r].data[c] = data[r].data[c];
		int r = R, c = C;
		while (r < R0 && c < C0)
			ret.data[r++].data[c++] = 1;
		return ret;
	}
};


typedef Matrix<float, 1, 1> mat1;
typedef Matrix<float, 1, 2> mat12;
typedef Matrix<float, 1, 3> mat13;
typedef Matrix<float, 2, 1> mat21;
typedef Matrix<float, 2, 2> mat2;
typedef Matrix<float, 2, 3> mat23;
typedef Matrix<float, 3, 1> mat31;
typedef Matrix<float, 3, 2> mat32;
typedef Matrix<float, 3, 3> mat3;
typedef Matrix<float, 4, 4> mat4;
typedef Matrix<float, 4, 3> mat43;


inline mat12 AsMatrix(const vec2& v) {return mat12 {v};}
inline mat13 AsMatrix(const vec3& v) {return mat13 {v};}
inline mat21 AsMatrixTrans(const vec2& v) {return mat21 { vec1{v[0]}, vec1{v[1]} };}
inline mat31 AsMatrixTrans(const vec3& v) {return mat31 { vec1{v[0]}, vec1{v[1]}, vec1{v[2]} };}


template <class T> inline T PartVec<T,2>::GetCrossProduct(const T& a, const T& b) {
	if (a == b)
		return a * -1;
	typename T::Unit z = 1;
	T r;
    r[0] =  ( a[1] * z    ) - ( z    * b[1] );
    r[1] =  ( z    * b[0] ) - ( a[0] * z    );
    return r;
}

template <class T> inline T PartVec<T,3>::GetCrossProduct(const T& a, const T& b) {
	T r;
    r[0] =  ( a[1] * b[2] ) - ( a[2] * b[1] );
    r[1] =  ( a[2] * b[0] ) - ( a[0] * b[2] );
    r[2] =  ( a[0] * b[1] ) - ( a[1] * b[0] );
    return r;
}

template <class T> inline T PartVec<T,4>::GetCrossProduct(const T& a, const T& b) {
	T r;
    r[0] =  ( a[1] * b[2] ) - ( a[2] * b[1] );
    r[1] =  ( a[2] * b[0] ) - ( a[0] * b[2] );
    r[2] =  ( a[0] * b[1] ) - ( a[1] * b[0] );
    r[3] =  0;
    return r;
}

template<class T> inline void PartMatrix<T,4,4>::Determinant(Unit& det, const T& m) {
	det =	+ m[X][X] * Determinant3 ( m[Y][Y], m[Z][Y], m[W][Y], m[Y][Z], m[Z][Z], m[W][Z], m[Y][W], m[Z][W], m[W][W] )
			- m[X][Y] * Determinant3 ( m[Y][X], m[Z][X], m[W][X], m[Y][Z], m[Z][Z], m[W][Z], m[Y][W], m[Z][W], m[W][W] )
			+ m[X][Z] * Determinant3 ( m[Y][X], m[Z][X], m[W][X], m[Y][Y], m[Z][Y], m[W][Y], m[Y][W], m[Z][W], m[W][W] )
			- m[X][W] * Determinant3 ( m[Y][X], m[Z][X], m[W][X], m[Y][Y], m[Z][Y], m[W][Y], m[Y][Z], m[Z][Z], m[W][Z] );
}

template<class T> inline void PartMatrix<T,4,4>::Adjoint(T& a, const T& m) {
	a[X][X]  =  Determinant3 ( m[Y][Y], m[Z][Y], m[W][Y], m[Y][Z], m[Z][Z], m[W][Z], m[Y][W], m[Z][W], m[W][W] );
    a[Y][X]  = -Determinant3 ( m[Y][X], m[Z][X], m[W][X], m[Y][Z], m[Z][Z], m[W][Z], m[Y][W], m[Z][W], m[W][W] );
    a[Z][X]  =  Determinant3 ( m[Y][X], m[Z][X], m[W][X], m[Y][Y], m[Z][Y], m[W][Y], m[Y][W], m[Z][W], m[W][W] );
    a[W][X]  = -Determinant3 ( m[Y][X], m[Z][X], m[W][X], m[Y][Y], m[Z][Y], m[W][Y], m[Y][Z], m[Z][Z], m[W][Z] );

    a[X][Y]  = -Determinant3 ( m[X][Y], m[Z][Y], m[W][Y], m[X][Z], m[Z][Z], m[W][Z], m[X][W], m[Z][W], m[W][W] );
    a[Y][Y]  =  Determinant3 ( m[X][X], m[Z][X], m[W][X], m[X][Z], m[Z][Z], m[W][Z], m[X][W], m[Z][W], m[W][W] );
    a[Z][Y]  = -Determinant3 ( m[X][X], m[Z][X], m[W][X], m[X][Y], m[Z][Y], m[W][Y], m[X][W], m[Z][W], m[W][W] );
    a[W][Y]  =  Determinant3 ( m[X][X], m[Z][X], m[W][X], m[X][Y], m[Z][Y], m[W][Y], m[X][Z], m[Z][Z], m[W][Z] );

    a[X][Z]  =  Determinant3 ( m[X][Y], m[Y][Y], m[W][Y], m[X][Z], m[Y][Z], m[W][Z], m[X][W], m[Y][W], m[W][W] );
    a[Y][Z]  = -Determinant3 ( m[X][X], m[Y][X], m[W][X], m[X][Z], m[Y][Z], m[W][Z], m[X][W], m[Y][W], m[W][W] );
    a[Z][Z]  =  Determinant3 ( m[X][X], m[Y][X], m[W][X], m[X][Y], m[Y][Y], m[W][Y], m[X][W], m[Y][W], m[W][W] );
    a[W][Z]  = -Determinant3 ( m[X][X], m[Y][X], m[W][X], m[X][Y], m[Y][Y], m[W][Y], m[X][Z], m[Y][Z], m[W][Z] );

    a[X][W]  = -Determinant3 ( m[X][Y], m[Y][Y], m[Z][Y], m[X][Z], m[Y][Z], m[Z][Z], m[X][W], m[Y][W], m[Z][W] );
    a[Y][W]  =  Determinant3 ( m[X][X], m[Y][X], m[Z][X], m[X][Z], m[Y][Z], m[Z][Z], m[X][W], m[Y][W], m[Z][W] );
    a[Z][W]  = -Determinant3 ( m[X][X], m[Y][X], m[Z][X], m[X][Y], m[Y][Y], m[Z][Y], m[X][W], m[Y][W], m[Z][W] );
    a[W][W]  =  Determinant3 ( m[X][X], m[Y][X], m[Z][X], m[X][Y], m[Y][Y], m[Z][Y], m[X][Z], m[Y][Z], m[Z][Z] );
}






template <class T>
class DMatrix : Moveable<DMatrix<T>> {
	
public:
	using type = T;
	Vector<T> data;
	int cols;
	int rows;
	int channels;
	
    DMatrix() : cols(0), rows(0), channels(0) {}
    
    DMatrix(int c, int r, int ch) {
        ASSERT(c > 0 && r > 0 && ch > 0);
        this->cols = c;
        this->rows = r;
        this->channels = ch;
        allocate();
    }
    DMatrix(int c, int r, int ch, const Vector<T>& data) {
        ASSERT(c > 0 && r > 0 && ch > 0);
        this->cols = c;
        this->rows = r;
        this->channels = ch;
        this->data <<= data;
    }
    
    DMatrix(const DMatrix& s) {*this = s;}
    
    void operator=(const DMatrix& s) {
        cols = s.cols;
        rows = s.rows;
        channels = s.channels;
		data <<= s.data;
    }
    void allocate() {
        data.SetCount(cols * rows * channels, 0);
    }
    
    void copy_to(DMatrix& other) const {
        ASSERT(other.cols == cols);
        ASSERT(other.rows == rows);
        ASSERT(other.channels == channels);
        other.data <<= data;
    }
    
    void SetSize(int c, int r, int ch) {
        this->cols = c;
        this->rows = r;
        this->channels = ch;
        allocate();
    }
	
	bool IsEmpty() const {
		return cols == 0 || rows == 0 || channels == 0;
	}
	
};

using ByteMat = DMatrix<byte>;
using FloatMat = DMatrix<float>;



template <class T>
struct Pyramid : Moveable<Pyramid<T>> {
	using Mat = DMatrix<T>;
	
	Vector<Mat> data;
	
	Pyramid() {}
	Pyramid(int w, int h, int levels) {SetSize(w, h, levels);}
	Pyramid(const Pyramid& p) {*this = p;}
	
	
	int GetLevels() const {return data.GetCount();}
	bool IsEmpty() const {return data.IsEmpty();}
	
	Mat& operator[](int i) {return data[i];}
	
	void SetLevels(int i) {data.SetCount(i);}
	
	void SetSize(int w, int h, int channels, int levels) {
		data.SetCount(levels);
		int i = levels;
        while(--i >= 0) {
            data[i].SetSize(w >> i, h >> i, channels);
        }
	}
	
	void Build(const Mat& input, bool skip_first_level=false) {
		ASSERT(data.GetCount());
		if (data.IsEmpty())
			return;
		int i = 2;
		const Mat* a = &input;
		Mat* b = &data[0];
        if (!skip_first_level) {
            *b = *a;
        }
        b = &data[1];
        DownsamplePyramid(*a, *b);
        for(; i < data.GetCount(); ++i) {
            a = b;
            b = &data[i];
            DownsamplePyramid(*a, *b);
        }
	}
	
	
};

typedef Pyramid<uint8> pyra8;
typedef Pyramid<float> pyraf;


template <class T>
void DownsamplePyramid(const DMatrix<T>& src, DMatrix<T>& dst, int sx=0, int sy=0) {
	int w = src.cols;
	int h = src.rows;
	int w2 = w >> 1;
	int h2 = h >> 1;
	int _w2 = w2 - (sx << 1);
	int _h2 = h2 - (sy << 1);
	int sptr = sx + sy * w;
	int dptr = 0;
	
	dst.SetSize(w2, h2, src.channels);
	
	const auto& src_d = src.data;
	auto& dst_d = dst.data;
	
	for (int y = 0; y < _h2; ++y) {
		int sline = sptr;
		int dline = dptr;
		int x;
		for (x = 0; x <= _w2 - 2; x += 2, dline += 2, sline += 4) {
			dst_d[dline] = (src_d[sline] + src_d[sline+1] +
							src_d[sline+w] + src_d[sline+w+1] + 2) >> 2;
			dst_d[dline+1] = (src_d[sline+2] + src_d[sline+3] +
							  src_d[sline+w+2] + src_d[sline+w+3] + 2) >> 2;
		}
		for (; x < _w2; ++x, ++dline, sline += 2) {
			dst_d[dline] = (src_d[sline] + src_d[sline+1] +
							src_d[sline+w] + src_d[sline+w+1] + 2) >> 2;
		}
		sptr += w << 1;
		dptr += w2;
	}
}






template <class T>
struct VectorAverage {
	T mean;
	uint32 count = 0;
	
	VectorAverage() {mean.Clear();}
	void Resize(int64 i) {count = i;}
	void Add(const T& a) {
		if (count == 0) {
			mean = a;
		}
		else {
			T delta = a - mean;
			mean += delta / count;
		}
		count++;
	}
	
	T GetMean() const {
		return mean;
	}
	
	
};

typedef VectorAverage<quat> quatav;
typedef VectorAverage<vec4> vec4av;
typedef VectorAverage<vec3> vec3av;
typedef VectorAverage<vec2> vec2av;


template <class Vec=vec3, class Quat=quat, class Count=uint32>
struct PositionOrientationAverageT {
	Vec position;
	Quat orientation;
	Count count = 0;
	
	PositionOrientationAverageT() {position.Clear(); orientation.Clear();}
	void Resize(int64 i) {count = i;}
	void Add(const Vec& pos, const Quat& q) {
		if (count == 0) {
			position = pos;
			orientation = q;
		}
		else {
			vec3 delta_pos = pos - position;
			position += delta_pos / count;
			vec4 delta_q = q.data - orientation.data;
			orientation.data += delta_q / count;
		}
		count++;
	}
	
	Count GetCount() const {return count;}
	Vec GetMeanPosition() const {return position;}
	Quat GetMeanOrientation() const {return orientation;}
	
	
};

using PositionOrientationAverage = PositionOrientationAverageT<>;


struct Square : Moveable<Square> {
	vec3 tl, tr, br, bl;
	
};




// Classes for RTTI requirements
struct Quaternion : RTTIBase {
	RTTI_DECL0(Quaternion);
	
	quat data;
	
	String ToString() const {return data.ToString();}
	int ToInt() const {return 0;}
	double ToDouble() const {return 0;}
	hash_t GetHashValue() const {return data.GetHashValue();}
	
};

struct Vector3 : RTTIBase {
	RTTI_DECL0(Vector3);
	
	vec3 data;
	
	String ToString() const {return data.ToString();}
	int ToInt() const {return 0;}
	double ToDouble() const {return 0;}
	hash_t GetHashValue() const {return data.GetHashValue();}
	
};

struct Matrix4 : RTTIBase {
	RTTI_DECL0(Matrix4);
	
	mat4 data;
	
	String ToString() const {return data.ToString();}
	int ToInt() const {return 0;}
	double ToDouble() const {return 0;}
	hash_t GetHashValue() const {return data.GetHashValue();}
	
};



NAMESPACE_TOPSIDE_END

NAMESPACE_UPP
using namespace TS;
#undef TransformMatrix
struct TransformMatrix : RTTIBase {
	RTTI_DECL0(TransformMatrix);
	
	typedef enum {
		MODE_POSITION,
		MODE_LOOKAT,
		MODE_AXES, // yaw, pitch, roll
		MODE_QUATERNION,
		//MODE_VIEW,
	} Mode;
	
	Mode mode = MODE_POSITION;
	bool is_stereo = false;
	
	vec3 position;
	vec3 direction;
	vec3 up = VEC_UP;
	vec3 axes;
	quat orientation;
	//mat4 proj[2], view[2];
	float eye_dist = 0;
	float fov = 0;
	
	
	TransformMatrix() {}
	TransformMatrix(const TransformMatrix& m) {*this = m;}
	void operator=(const TransformMatrix& m);
	
	void Clear();
	void FillFromOrientation();
	void FillFromLookAt();
	
	vec3 GetForwardDirection() const;
	String GetAxesString() const;
	
	String ToString() const {return "TransformMatrix";}
	int ToInt() const {return 0;}
	double ToDouble() const {return 0;}
	hash_t GetHashValue() const {return 0;}
	
};

struct ControllerMatrix : RTTIBase {
	RTTI_DECL0(ControllerMatrix);
	
	typedef enum {
		INVALID = -1,
		
		GENERIC,
		TRIGGER,
		TRIGGER_CLICK,
		SQUEEZE,
		MENU,
		
		HOME,
		ANALOG_X0,
		ANALOG_X1,
		ANALOG_X2,
		ANALOG_X3,
		
		ANALOG_Y0,
		ANALOG_Y1,
		ANALOG_Y2,
		ANALOG_Y3,
		ANALOG_PRESS0,
		
		ANALOG_PRESS1,
		ANALOG_PRESS2,
		ANALOG_PRESS3,
		BUTTON_A,
		BUTTON_B,
		
		BUTTON_X,
		BUTTON_Y,
		VOLUME_PLUS,
		VOLUME_MINUS,
		MIC_MUTE,
		
		VALUE_COUNT,
		
		ANALOG_X = ANALOG_X0,
		ANALOG_Y = ANALOG_Y0,
		ANALOG_PRESS = ANALOG_PRESS0,
	} Value;

	static const int CTRL_COUNT = 2;
	struct Ctrl {
		bool is_enabled = false;
		bool is_value[VALUE_COUNT];
		float value[VALUE_COUNT];
		TransformMatrix trans;
		
		void operator=(const Ctrl& c) {
			is_enabled = c.is_enabled;
			for(int i = 0; i < VALUE_COUNT; i++) {
				is_value[i] = c.is_value[i];
				value[i] = c.value[i];
			}
			trans = c.trans;
		}
		
		float GetTouchpadX(int i=0) const {return value[ANALOG_X0 + i];}
		float GetTouchpadY(int i=0) const {return value[ANALOG_Y0 + i];}
		float GetThumbstickX(int i=0) const {return value[ANALOG_X1 + i];}
		float GetThumbstickY(int i=0) const {return value[ANALOG_Y1 + i];}
		bool IsGrasped() const {return is_value[SQUEEZE] && value[SQUEEZE] > 0.0f;}
		bool IsTouchpadTouched(int i=0) const {return value[ANALOG_PRESS0] > 0.0f;}
		bool IsTouchpadPressed(int i=0) const {return value[ANALOG_PRESS0] > 0.0f;}
		bool IsSelectPressed(int i=0) const {return value[TRIGGER] > 0.0f;}
	};
	Ctrl ctrl[CTRL_COUNT];
	
	
	
	ControllerMatrix() {}
	ControllerMatrix(const ControllerMatrix& m) {*this = m;}
	
	String ToString() const {return "ControllerMatrix";}
	int ToInt() const {return 0;}
	double ToDouble() const {return 0;}
	hash_t GetHashValue() const {return 0;}
	
	void operator=(const ControllerMatrix& m) {
		for(int i = 0; i < CTRL_COUNT; i++)
			ctrl[i] = m.ctrl[i];
	}
	
	
};

struct ControllerState {
	ControllerSource* source = 0;
	ControllerMatrix props;
	
	const ControllerSource& GetSource() const {ASSERT(source); return *source;}
	const ControllerMatrix& GetControllerProperties() const {return props;}
	
};


struct CalibrationData {
	bool is_enabled = false;
	vec3 axes = vec3(0,0,0);
	vec3 position = vec3(0,0,0);
	float fov = 0;
	float scale = 0;
	float eye_dist = 0;
	
	
	String ToString() const;
	void Dump();
	
};


struct OnlineAverageVector {
	OnlineAverage av[3];
	
	
	OnlineAverageVector() {}
	
	void SetSize(int i) {
		for(int j = 0; j < 3; j++)
			av[j].Resize(i);
	}
	
	void Add(const vec3& v) {
		for(int i = 0; i < 3; i++)
			av[i].Add(v[i]);
	}
	
	vec3 GetMean() const {
		vec3 v;
		for(int i = 0; i < 3; i++)
			v.data[i] = (float)av[i].GetMean();
		return v;
	}
};

END_UPP_NAMESPACE

#include "Matrix.inl"


#endif
