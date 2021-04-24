#include "Oulu.h"


NAMESPACE_OULU_BEGIN


const float EPSILONf = 0.0000000001f;
const double EPSILON = 0.0000000001;
const double DEG2RAD = M_PI / 180;







bool IsEpsilonEqual(float a, float b, float epsilon) {
	float diff = fabsf(a - b);
	return diff < epsilon;
}

bool IsEpsilonEqual(double a, double b, double epsilon) {
	float diff = fabs(a - b);
	return diff < epsilon;
}

bool IsEpsilonNotEqual(float a, float b, float epsilon) {
	float diff = fabs(a - b);
	return diff >= epsilon;
}

bool IsEpsilonNotEqual(double a, double b, double epsilon) {
	float diff = fabs(a - b);
	return diff >= epsilon;
}

float FastAtan2(float y, float x) {
    const float n1 = 0.97239411f;
    const float n2 = -0.19194795f;
    float result = 0.0f;
    
    if (x != 0.0f) {
        const union { float flVal; uint32 nVal; } tYSign = { y };
        const union { float flVal; uint32 nVal; } tXSign = { x };
        if (fabsf(x) >= fabsf(y)) {
            union { float flVal; uint32 nVal; } tOffset = { (float)M_PI };
            // Add or subtract PI based on y's sign.
            tOffset.nVal |= tYSign.nVal & 0x80000000u;
            // No offset if x is positive, so multiply by 0 or based on x's sign.
            tOffset.nVal *= tXSign.nVal >> 31;
            result = tOffset.flVal;
            const float z = y / x;
            result += (n1 + n2 * z * z) * z;
        }
        // Use atan(y/x) = pi/2 - atan(x/y) if |y/x| > 1.
        else {
            union { float flVal; uint32 nVal; } tOffset = { (float)M_PI_2 };
            // Add or subtract PI/2 based on y's sign.
            tOffset.nVal |= tYSign.nVal & 0x80000000u;
            result = tOffset.flVal;
            const float z = x / y;
            result -= (n1 + n2 * z * z) * z;
        }
    }
    else if (y > 0.0f) {
        result = (float)M_PI_2;
    }
    else if (y < 0.0f) {
        result = (float)-M_PI_2;
    }
    return result;
}

double nround (double n, unsigned int c)
{
    double marge = pow (10, c);
    double up    = n * marge;
    double ret   = round (up) / marge;

    return ret;
}

double StandardNormalCDF(double x) {
	double sum = x;
	double value = x;
	for (int i = 1; i < 100; i++) {
		value = (value * x * x / (2 * i + 1));
		sum += value;
	}
	return 0.5 + (sum / sqrt(2*M_PI)) * pow(M_E, -1* x*x / 2);
}

#if 1
double NormalPDF(double x, double mean, double dev) {
	double a = dev * sqrt(2 * M_PI);
	double b = 1.0 / a;
	double c = x  - mean;
	double d = -(c * c) / (2 * dev * dev);
	double e = exp(d);
	return b * e;
}
#else
double NormalPDF(double value, double mean, double deviation) {
	if (deviation == 0)
		return 0;
	
	double low = mean - 4 * deviation;
	double high = mean + 4 * deviation;
	if (mean < low || high < mean)
		return 0;
	
	struct PDF_Constant {
		double value;
		PDF_Constant() {value = sqrt(2 * M_PI);}
	};
	static PDF_Constant pdf_const;
	
	double a = (value - mean) / deviation;
	double b = -0.5 * a * a;
	if (b < -10)
		return 0;
	double c = FastExp(b);
	double d = 1.0 / (deviation * pdf_const.value);
	double e = d * c;
	return e;
}
#endif






double NormalPDFRelative(double value, double mean, double deviation) {
	if (deviation == 0)
		return 0;
	
	double low = mean - 4 * deviation;
	double high = mean + 4 * deviation;
	if (mean < low || high < mean)
		return 0;
	
	double a = (value - mean) / deviation;
	double b = -0.5 * a * a;
	if (b < -10)
		return 0;
	double c = FastExp(b);
	return c;
}

double NormalCDF(double value, double mean, double deviation) {
	if (deviation == 0) {
		if (value < mean) return 0;
		else return 1;
	}
	double d = (value - mean) / deviation;
	d = StandardNormalCDF(d);
	if (!IsFin(d)) {
		if (value < mean) return 0;
		else return 1;
	}
	return d;
}











void OnlineCovariance::Add(double x, double y) {
	n++;
	double dx = x - meanx;
	meanx += dx / n;
	meany += (y - meany) / n;
	C += dx * (y - meany);
}

void OnlineBivariate::Add(double x, double y) {
	this->x.Add(x);
	this->y.Add(y);
	co.Add(x,y);
}

double OnlineBivariate::GetPDF(double x, double y) const {
	double mux = this->x.GetMean();
	double devx = this->x.GetDeviation();
	double xdiff = x - mux;
	
	double muy = this->y.GetMean();
	double devy = this->y.GetDeviation();
	double ydiff = y - muy;
	
	if (devx <= 0.0 || devy <= 0.0 || this->y.count == 0 || this->x.count == 0)
		return 0.0;
	
	double p = co.Get() / (devx * devy);
	double pd = 1.0 - p * p;
	double pdr = FastPow(pd, 0.5);
	
	double a = (xdiff * xdiff) / (devx * devx);
	double b = (2.0 * p * xdiff * ydiff) / (devx * devy);
	double c = (ydiff * ydiff) / (devy * devy);
	
	double z = a - b + c;
	
	double d = 2.0 * M_PI * devx * devy * pdr;
	double e = 1.0 / d;
	double f = -(z / (2.0 * pd));
	double g = FastExp(f);
	
	double pdf = e * g;
	return pdf;
}








String OnlineVariance::ToString() const {return Format("k=%v count=%v ex=%v ex2=%v mean=%v", k, count, ex, ex2, GetMean());}
String StdDeviant::ToString() const {return Format("mean=%v, dev=%v", mean, dev);}

NAMESPACE_OULU_END
