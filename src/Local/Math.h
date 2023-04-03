#ifndef _Local_Math_h_
#define _Local_Math_h_

NAMESPACE_TOPSIDE_BEGIN

#ifndef M_2PI
	#define M_2PI (2.0 * M_PI)
#endif

#define DEG2RAD(x)         (((x) / 360.0) * M_2PI)
#define DEG2RADf(x) (float)(((x) / 360.0) * M_2PI)
#define RAD2DEG(x)         (((x) / M_2PI) * 360.0)
#define RAD2DEGf(x) (float)(((x) / M_2PI) * 360.0)


extern const float EPSILONf;
extern const double EPSILON;
extern const double DEG2RAD;


template <class T> T Modulus(T val, T div);
template <> inline float Modulus(float val, float div) {float f = floorf(val / div); return val - f * div;}
template <> inline double Modulus(double val, double div) {double f = floor(val / div); return val - f * div;}

template <class T> T Abs(const T& v) {return (v < 0 ? -1 : +1) * v;}
template <> inline uint8  Abs(const uint8& v) {return v;}
template <> inline uint16 Abs(const uint16& v) {return v;}
template <> inline uint32 Abs(const uint32& v) {return v;}
template <> inline uint64 Abs(const uint64& v) {return v;}


// Fast math
double exp_fast_lb(double a);
double exp_fast_ub(double a);
double exp_fast(double a);
double better_exp_fast(double a);
double exp_fast_schraudolph(double a);
float expf_fast_ub(float a);
float expf_fast(float a);
double better_expf_fast(float a);
float expf_fast_lb(float a);
double log_fast_ankerl(double a);
double log_fast_ub(double a);
double log_fast(double a);
double log_fast_lb(double a);
float logf_fast_ub(float a);
float logf_fast(float a);
float logf_fast_lb(float a);
double pow_fast_ankerl(double a, double b);
float powf_fast(float a, float b);
float powf_fast_lb(float a, float b);
float powf_fast_ub(float a, float b);
double pow_fast_ub(double a, double b);
double pow_fast(double a, double b);
double pow_fast_lb(double a, double b);
double pow_fast_precise_ankerl(double a, double b);
double pow_fast_precise(double a, double b);
double better_pow_fast_precise(double a, double b);
float powf_fast_precise(float a, float b);
float better_powf_fast_precise(float a, float b);


template <class T=double> T FastLn(T a);
template <class T=double> T FastExp(T a);
template <class T=double> T FastPow(T a, T b);
template <class T=double> T FastSqrt(T a);
template<> inline double FastLn(double a) {return log_fast(a);}
template<> inline double FastExp(double a) {return exp_fast(a);}
template<> inline double FastPow(double a, double b) {return better_pow_fast_precise(a, b);}
template<> inline double FastSqrt(double a) {return pow_fast_precise(a, 0.5);}
template<> inline float FastLn(float a) {return logf_fast(a);}
template<> inline float FastExp(float a) {return expf_fast(a);}
template<> inline float FastPow(float a, float b) {return better_powf_fast_precise(a, b);}
template<> inline float FastSqrt(float a) {return powf_fast_precise(a, 0.5f);}

inline double PowOf10(double d) {return FastPow(10.0, d);}
inline double PowTo2(double d) {return d * d;}

template <class T> inline T PowFastT(T v, T e);
template <> inline double PowFastT(double v, double e) {return better_pow_fast_precise(v, e);}
template <> inline float PowFastT(float v, float e) {return better_powf_fast_precise(v, e);}


template <class T> struct FastTrig {
	static const int accuracy = 10000;
	static constexpr double PI2 = 2.0 * M_PI;
	
	Vector<T> sin, cos, tan, asin, acos, atan;
	FastTrig() {
		static_assert(!std::is_same<T, int>(), "T must be floating number");
		
		sin.SetCount(accuracy);
		cos.SetCount(accuracy);
		tan.SetCount(accuracy);
		asin.SetCount(accuracy);
		acos.SetCount(accuracy);
		atan.SetCount(accuracy);
		T *s = sin.Begin(), *c = cos.Begin(), *t = tan.Begin();
		T *as = asin.Begin(), *ac = acos.Begin(), *at = atan.Begin();
		for(int i = 0; i < accuracy; i++) {
			double a = (PI2 * i) / accuracy;
			*s = (T)::sin(a);
			*c = (T)::cos(a);
			*t = (T)::tan(a);
			*as = (T)::asin(a);
			*ac = (T)::acos(a);
			*at = (T)::atan(a);
			//LOG(Format("%d %3n: sin %3n, cos %3n, tan %3n", i, a, *s, *c, *t));
			s++, c++, t++;
			as++, ac++, at++;
		}
	}
	int Pos(T a) const {
		T posf = a / (T)PI2;
		posf -= (T)floor(posf);
		int pos = (int)(posf * (T)accuracy);
		return pos;
	}
	T Sin(T a) const {return sin[Pos(a)];}
	T Cos(T a) const {return cos[Pos(a)];}
	T Tan(T a) const {return tan[Pos(a)];}
	T ASin(T a) const {return asin[Pos(a)];}
	T ACos(T a) const {return acos[Pos(a)];}
	T ATan(T a) const {return atan[Pos(a)];}
};

template <class T> FastTrig<T>& GetFastTrig() {return Single<FastTrig<T>>();}

template <class T> T FastSin(T a) {return GetFastTrig<T>().Sin(a);}
template <class T> T FastCos(T a) {return GetFastTrig<T>().Cos(a);}
template <class T> T FastTan(T a) {return GetFastTrig<T>().Tan(a);}
template <class T> T FastASin(T a) {return GetFastTrig<T>().ASin(a);}
template <class T> T FastACos(T a) {return GetFastTrig<T>().ACos(a);}
template <class T> T FastATan(T a) {return GetFastTrig<T>().ATan(a);}

float FastAtan2(float y, float x);

double nround (double n, unsigned int c);

double StandardNormalCDF(double x);
double NormalPDF(double x, double mean, double dev);
double NormalPDFRelative(double value, double mean, double deviation);
double NormalCDF(double value, double mean, double deviation);

bool IsEpsilonEqual(float a, float b, float epsilon);
bool IsEpsilonEqual(double a, double b, double epsilon);
bool IsEpsilonNotEqual(float a, float b, float epsilon);
bool IsEpsilonNotEqual(double a, double b, double epsilon);

inline double FindPowFrom1(double ratio, double outcome) {
	double a = FastLn(ratio);
	double b = FastLn(outcome);
	double res = b / a;
	return res;
}

inline double FindPowTo1(double begin, double ratio) {
	double a = FastLn(ratio);
	double b = FastLn(begin);
	double res = -(b / a);
	return res;
}

inline int Choose(int n, int k) {
	// A fast way to calculate binomial coefficients by Andrew Dalke (contrib).
	if (0 <= k && k <= n) {
		int64 ntok = 1;
		int64 ktok = 1;
		int count = min(k, n - k) + 1;
		for (int t = 1; t < count; t++) {
			ntok *= n;
			ktok *= t;
			n -= 1;
		}
		ASSERT(ktok != 0);
		return (int)(ntok / ktok);
	}
	else
		return 0;
}

struct OnlineAverage : Moveable<OnlineAverage> {
	double mean;
	int64 count;
	SpinLock lock;
	OnlineAverage() : mean(0), count(0) {}
	
	void Clear() {
		mean = 0.0;
		count = 0;
	}
	
	void Resize(int64 i) {count = i;}
	
	void Add(double a) {
		lock.Enter();
		if (count == 0) {
			mean = a;
		}
		else {
			double delta = a - mean;
			mean += delta / count;
		}
		count++;
		lock.Leave();
	}
	
	double GetMean() const {
		return mean;
	}
	
	void Serialize(Stream& s) {s % mean % count;}
	
	bool operator()(const OnlineAverage& a, const OnlineAverage& b) const {return a.mean < b.mean;}
};

struct OnlineVariance : Moveable<OnlineVariance> {
	double k = 0;
	double count = 0;
	double ex = 0;
	double ex2 = 0;
	
	String ToString() const;
	
	void Clear() {
		k = 0;
		count = 0;
		ex = 0;
		ex2 = 0;
	}
	
	void Resize(double d) {
		if (count > 0.0) {
			ex /= count;
			ex2 /= count;
			count = 1.0;
			ex *= d;
			ex2 *= d;
			count = d;
		}
	}
	
	void Add(double x) {
	    if (count == 0)
	        k = x;
	    count = count + 1;
	    double diff = x - k;
	    ex += diff;
	    ex2 += diff * diff;
	}
	
	void Add(double x, double weight) {
	    if (count == 0)
	        k = x;
	    count += weight;
	    double diff = x - k;
	    ex += diff * weight;
	    ex2 += diff * diff * weight;
	}
	
	void Remove(double x) {
	    count = count - 1;
	    double diff = x - k;
	    ex -= diff;
	    ex2 -= diff * diff;
	}
	
	double GetMean() const {
		if (count == 0.0)
			return 0.0;
		else
			return k + ex / count;
	}
	
	double GetVariance() const {return (ex2 - (ex * ex) / count) / (count - 1);}
	double GetDeviation() const {return sqrt(GetVariance());}
	double GetCDF() const {
		if (count == 0.0) return 0;
		return NormalCDF(0, GetMean(), GetDeviation());
	}
	double GetCDF(double limit, bool rside) const {
		if (count == 0.0) return 0;
		if (rside == 1)
			return 1 - NormalCDF(limit, GetMean(), GetDeviation());
		else
			return     NormalCDF(limit, GetMean(), GetDeviation());
	}
	
	
	void Serialize(Stream& s) {s % k % count % ex % ex2;}
	
};

class MovingOnlineVariance : Moveable<MovingOnlineVariance> {
	Vector<OnlineVariance> vec;
	int period;
	bool skip;
public:
	
	MovingOnlineVariance() {
		skip = false;
		period = 10;
		vec.Add();
	}
	
	OnlineVariance& Get() {return vec[0];}
	
	void SetPeriod(int i) {if (i > 0) {period = i; skip = false;} else {period = 1; skip = true; vec.SetCount(1);}}
	void Add(double d) {for(int i = 0; i < vec.GetCount(); i++) {vec[i].Add(d);}}
	void AddResult(double d) {for(int i = 0; i < vec.GetCount(); i++) {vec[i].Add(d);}}
	void Next() {if (skip) return; while (vec.GetCount() >= period) {vec.Remove(0);} vec.Add();}
	void Clear() {vec.SetCount(1); vec[0].Clear();}
	
	double GetMean() {return Get().GetMean();}
	double GetDeviation() {return Get().GetDeviation();}
	double GetCDF(double cursor, int type) {return Get().GetCDF(cursor, type);}
	
};



struct StdDeviant : Moveable<StdDeviant> {
	double mean = 0, dev = 0;
	
	void Serialize(Stream& s) {s % mean % dev;}
	void Clear() {mean = 0; dev = 0;}
	
	double GetMean() const {return mean;}
	double GetDeviation() const {return dev;}
	double GetVariance() const {return dev * dev;}
	double GetCDF() const {
		return NormalCDF(0, GetMean(), GetDeviation());
	}
	double GetCDF(double limit, bool rside) const {
		if (rside == 1)
			return 1 - NormalCDF(limit, GetMean(), GetDeviation());
		else
			return     NormalCDF(limit, GetMean(), GetDeviation());
	}
	String ToString() const;
	operator double() const {return mean;}
	
	void operator+=(const StdDeviant& s) {mean += s.mean; dev += s.dev;}
	void operator-=(const StdDeviant& s) {mean -= s.mean; dev -= s.dev;}
	void operator*=(double d) {mean *= d; dev *= d;}
	void operator/=(double d) {mean /= d; dev /= d;}
	void operator=(double d) {mean = d; dev = 0;}
	bool operator<=(const StdDeviant& s) const {return mean <= s.GetMean();}
	bool operator>(const StdDeviant& s) const {return mean > s.GetMean();}
};











struct OnlineCovariance : Moveable<OnlineCovariance> {
	double meanx, meany, C;
	dword n;
	
	
	OnlineCovariance() {Clear();}
	OnlineCovariance(const OnlineCovariance& s) {*this = s;}
	void operator=(const OnlineCovariance& s) {meanx = s.meanx; meany = s.meany; C = s.C; n = s.n;}
	void Clear() {meanx = 0; meany = 0; C = 0; n = 0;}
	void Add(double x, double y);
	double Get() const {return C / n;}
	void Serialize(Stream& s) {s % meanx % meany % C % n;}
};

// https://www.statisticshowto.datasciencecentral.com/bivariate-normal-distribution/
struct OnlineBivariate : Moveable<OnlineBivariate> {
	OnlineVariance x, y;
	OnlineCovariance co;
	
	
	OnlineBivariate() {}
	OnlineBivariate(const OnlineBivariate& s) {*this = s;}
	void operator=(const OnlineBivariate& s) {x = s.x; y = s.y; co = s.co;}
	void Add(double x, double y);
	void Serialize(Stream& s) {s % x % y % co;}
	double GetPDF(double x, double y) const;
};









// TODO: optimize for large amount of values
class StepDistribution : Moveable<StepDistribution> {
	Vector<int> values;
	double mean, M2;
	double value_step;
	
public:
	StepDistribution() {
		mean = 0;
		M2 = 0;
		value_step = 0.01;
	}
	
	void Serialize(Stream& s) {s % values % mean % M2 % value_step;}
	
	void AddResult(double value) {
		double delta = value - mean;
        mean += delta / values.GetCount();
        M2 += delta*(value - mean);
		
		int valuei = (int)(value / value_step);
		for(int i = 0; i < values.GetCount(); i++) {
			if (valuei < values[i]) {
				values.Insert(i, valuei);
				return;
			}
		}
		values.Add(valuei);
	}
	
	void Clear() {
		values.SetCount(0);
		mean = 0;
		M2 = 0;
	}
	
	double Get(double prob) {
		ASSERT(prob >= 0.0 && prob <= 1.0);
		ASSERT(values.GetCount());
		int count = values.GetCount() - 1;
		if (count < 0)
			return 0.0;
		double pos_step = 1.0 / (double)count;
		int pos = (int)(prob / pos_step);
		if (pos >= count)
			return values.Top() * value_step;
		if (pos < 0)
			return values[0] * value_step;
		double begin = pos * pos_step;
		double v0 = values[pos] * value_step;
		double v1 = values[pos+1] * value_step;
		double f = (prob - begin) / pos_step;
		double linear_value = v0 * f + v1 * (1.0 - f);
		return linear_value;
	}
	
	int GetCount() const {return values.GetCount();}
	
	double GetMean() {
		return mean;
	}
};


class MovingStepDistribution : Moveable<MovingStepDistribution> {
	Vector<StepDistribution> vec;
	int period;
	bool skip;
public:
	
	MovingStepDistribution() {
		skip = false;
		period = 10;
		vec.Add();
	}
	
	StepDistribution& Get() {return vec[0];}
	
	void SetPeriod(int i) {if (i > 0) {period = i; skip = false;} else {period = 1; skip = true; vec.SetCount(1);}}
	void AddResult(double d) {for(int i = 0; i < vec.GetCount(); i++) {vec[i].AddResult(d);}}
	void Next() {if (skip) return; while (vec.GetCount() >= period) {vec.Remove(0);} vec.Add();}
	void Clear() {vec.SetCount(1); vec[0].Clear();}
	
	double GetMean() {return Get().GetMean();}
	double Get(double prob) {return Get().Get(prob);}
	
	void Serialize(Stream& s) {s % vec % period % skip;}
	
};







class RandomGaussian {
	std::default_random_engine generator;
	std::normal_distribution<double> distribution;
	
public:

	// weight normalization is done to equalize the output
	// variance of every neuron, otherwise neurons with a lot
	// of incoming connections have outputs of larger variance
	RandomGaussian(int length) : distribution(0, sqrt((float)(1.0 / (double)(length)))) {
		generator.seed(Random(1000000000));
	}
	double Get() {return distribution(generator);}
	operator double() {return distribution(generator);}
	
};

template <class T> // Workaround for GCC bug - specialization needed...
T& SingleRandomGaussianLock() {
	static T o;
	return o;
}

inline RandomGaussian& GetRandomGaussian(int length) {
	SpinLock& lock = SingleRandomGaussianLock<SpinLock>(); // workaround
	ArrayMap<int, RandomGaussian>& rands = Single<ArrayMap<int, RandomGaussian> >();
	lock.Enter();
	int i = rands.Find(length);
	RandomGaussian* r;
	if (i == -1) {
		r = &rands.Add(length, new RandomGaussian(length));
	} else {
		r = &rands[i];
	}
	lock.Leave();
	return *r;
}

float smoothstep(float edge0, float edge1, float x);


double GetDistance(Point a, Point b);


template <class T>
T Clamp(T value, T min, T max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}


NAMESPACE_TOPSIDE_END

#endif
