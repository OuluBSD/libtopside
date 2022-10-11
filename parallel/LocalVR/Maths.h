#ifndef __LocalVR_MATHS_H__
#define __LocalVR_MATHS_H__


NAMESPACE_HMD_BEGIN


float f16_to_float(uint16 f16);

static inline double vec3_dot(const vec3 *a, const vec3 *b)
{
	return a->data[0] * b->data[0] + a->data[1] * b->data[1] + a->data[2] * b->data[2];
}

static inline double vec3_norm(const vec3 *v)
{
	return sqrt(vec3_dot(v, v));
}

static inline void vec3_normalize(vec3 *v)
{
	const float inv_norm = 1.0f / vec3_norm(v);

	v->data[0] *= inv_norm;
	v->data[1] *= inv_norm;
	v->data[2] *= inv_norm;
}

static inline void vec3_cross(vec3 *c, const vec3 *a, const vec3 *b)
{
	c->data[0] = a->data[1] * b->data[2] - b->data[1] * a->data[2];
	c->data[1] = a->data[2] * b->data[0] - b->data[2] * a->data[0];
	c->data[2] = a->data[0] * b->data[1] - b->data[0] * a->data[1];
}

static inline double quat_dot(const quat *q, const quat *p)
{
	return q->data[3] * p->data[3] + q->data[0] * p->data[0] + q->data[1] * p->data[1] + q->data[2] * p->data[2];
}

static inline double quat_norm(const quat *q)
{
	return sqrt(quat_dot(q, q));
}

static inline void quat_normalize(quat *q)
{
	const double inv_norm = 1.0 / quat_norm(q);

	q->data[3] *= inv_norm;
	q->data[0] *= inv_norm;
	q->data[1] *= inv_norm;
	q->data[2] *= inv_norm;
}

static inline void quat_mult(quat *r, quat *p, const quat *q)
{
	r->data[3] = p->data[3] * q->data[3] - p->data[0] * q->data[0] - p->data[1] * q->data[1] - p->data[2] * q->data[2];
	r->data[0] = p->data[3] * q->data[0] + p->data[0] * q->data[3] + p->data[1] * q->data[2] - p->data[2] * q->data[1];
	r->data[1] = p->data[3] * q->data[1] + p->data[1] * q->data[3] + p->data[2] * q->data[0] - p->data[0] * q->data[2];
	r->data[2] = p->data[3] * q->data[2] + p->data[2] * q->data[3] + p->data[0] * q->data[1] - p->data[1] * q->data[0];
}

void quat_from_axis_angle(quat *quat, const vec3 *axis, double angle);
void quat_from_axes(quat *q, const vec3 *a, const vec3 *b);
void quat_from_gyro(quat *q, const vec3 *gyro, double dt);


NAMESPACE_HMD_END


#endif
