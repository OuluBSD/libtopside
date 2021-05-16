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









NAMESPACE_TOPSIDE_END
