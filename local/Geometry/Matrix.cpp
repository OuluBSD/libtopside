#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN

quat quat::GetConjugate() const {
	// https://mathworld.wolfram.com/QuaternionConjugate.html
	quat q;
	q.data[0] = q.data[0];
	q.data[1] = -q.data[1];
	q.data[2] = -q.data[2];
	q.data[3] = -q.data[3];
	return q;
}

quat quat::operator-() const {
	quat q = *this;
	for (int i = 0; i < 4; i++)
		q.data.data[i] *= -1;
	return q;
}

quat quat::operator+(const quat& q) const {
	quat r = *this;
	for (int i = 0; i < 4; i++)
		r.data.data[i] += q.data.data[i];
	return r;
}

quat quat::operator*(const quat& b) const {
	// https://stackoverflow.com/questions/19956555/how-to-multiply-two-quaternions
	const quat& a = *this;
	return quat (
		a[3] * b[3] - a[0] * b[0] - a[1] * b[1] - a[2] * b[2],
	    a[3] * b[0] + a[0] * b[3] + a[1] * b[2] - a[2] * b[1],
	    a[3] * b[1] - a[0] * b[2] + a[1] * b[3] + a[2] * b[0],
	    a[3] * b[2] + a[0] * b[1] - a[1] * b[0] + a[2] * b[3]
	);
}

quat quat::operator*(float f) const {
	quat q = *this;
	for (int i = 0; i < 4; i++)
		q.data.data[i] *= f;
	return q;
}

quat quat::operator/(float f) const {
	quat q = *this;
	for (int i = 0; i < 4; i++)
		q.data.data[i] /= f;
	return q;
}

float quat::GetDotProduct(const quat& q) const {
	return data.GetDotProduct(q.data);
}

quat quat::Mix(const quat& q, float f) const {
	quat r;
	r.data = data.Mix(q.data, f);
	return r;
}







NAMESPACE_TOPSIDE_END
