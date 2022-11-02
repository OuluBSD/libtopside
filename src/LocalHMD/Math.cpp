#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


float ovec3_get_length(const vec3* me)
{
	return sqrtf(POW2(me->data[0]) + POW2(me->data[1]) + POW2(me->data[2]));
}

void ovec3_normalize_me(vec3* me)
{
	if(me->data[0] == 0 && me->data[1] == 0 && me->data[2] == 0)
		return;

	float len = ovec3_get_length(me);
	me->data[0] /= len;
	me->data[1] /= len;
	me->data[2] /= len;
}

void ovec3_subtract(const vec3* a, const vec3* b, vec3* out)
{
	for(int i = 0; i < 3; i++)
		out->data[i] = a->data[i] - b->data[i];
}

float ovec3_get_dot(const vec3* me, const vec3* vec)
{
	return me->data[0] * vec->data[0] + me->data[1] * vec->data[1] + me->data[2] * vec->data[2];
}

float ovec3_get_angle(const vec3* me, const vec3* vec)
{
	float dot = ovec3_get_dot(me, vec);
	float lengths = ovec3_get_length(me) * ovec3_get_length(vec);

	if(lengths == 0)
		return 0;

	return acosf(dot / lengths);
}


// quaternion

void oquat_init_axis(quat* me, const vec3* vec, float angle)
{
	vec3 norm = *vec;
	ovec3_normalize_me(&norm);

	me->data[0] = norm[0] * sinf(angle / 2.0f);
	me->data[1] = norm[1] * sinf(angle / 2.0f);
	me->data[2] = norm[2] * sinf(angle / 2.0f);
	me->data[3] = cosf(angle / 2.0f);
}

void oquat_get_rotated(const quat* me, const vec3* vec, vec3* out_vec)
{
	quat q = {vec->data[0] * me->data[3] + vec->data[2] * me->data[1] - vec->data[1] * me->data[2],
	          vec->data[1] * me->data[3] + vec->data[0] * me->data[2] - vec->data[2] * me->data[0],
	          vec->data[2] * me->data[3] + vec->data[1] * me->data[0] - vec->data[0] * me->data[1],
	          vec->data[0] * me->data[0] + vec->data[1] * me->data[1] + vec->data[2] * me->data[2]};

	out_vec->data[0] = me->data[3] * q[0] + me->data[0] * q[3] + me->data[1] * q[2] - me->data[2] * q[1];
	out_vec->data[1] = me->data[3] * q[1] + me->data[1] * q[3] + me->data[2] * q[0] - me->data[0] * q[2];
	out_vec->data[2] = me->data[3] * q[2] + me->data[2] * q[3] + me->data[0] * q[1] - me->data[1] * q[0];
}

void oquat_mult(const quat* me, const quat* q, quat* out_q)
{
	out_q->data[0] = me->data[3] * q->data[0] + me->data[0] * q->data[3] + me->data[1] * q->data[2] - me->data[2] * q->data[1];
	out_q->data[1] = me->data[3] * q->data[1] - me->data[0] * q->data[2] + me->data[1] * q->data[3] + me->data[2] * q->data[0];
	out_q->data[2] = me->data[3] * q->data[2] + me->data[0] * q->data[1] - me->data[1] * q->data[0] + me->data[2] * q->data[3];
	out_q->data[3] = me->data[3] * q->data[3] - me->data[0] * q->data[0] - me->data[1] * q->data[1] - me->data[2] * q->data[2];
}

void oquat_mult_me(quat* me, const quat* q)
{
	quat tmp = *me;
	oquat_mult(&tmp, q, me);
}

void oquat_normalize_me(quat* me)
{
	float len = oquat_get_length(me);
	me->data[0] /= len;
	me->data[1] /= len;
	me->data[2] /= len;
	me->data[3] /= len;
}

float oquat_get_length(const quat* me)
{
	return sqrtf(me->data[0] * me->data[0] + me->data[1] * me->data[1] + me->data[2] * me->data[2] + me->data[3] * me->data[3]);
}

float oquat_get_dot(const quat* me, const quat* q)
{
	return me->data[0] * q->data[0] + me->data[1] * q->data[1] + me->data[2] * q->data[2] + me->data[3] * q->data[3];
}

void oquat_inverse(quat* me)
{
	float dot = oquat_get_dot(me, me);

	// conjugate
	for(int i = 0; i < 3; i++)
		me->data[i] = -me->data[i];
	
	for(int i = 0; i < 4; i++)
		me->data[i] /= dot;
}

void oquat_diff(const quat* me, const quat* q, quat* out_q)
{
	quat inv = *me;
	oquat_inverse(&inv);
	oquat_mult(&inv, q, out_q);
}

void oquat_slerp (float fT, const quat* rkP, const quat* rkQ, bool shortestPath, quat* out_q)
{
	float fCos =  oquat_get_dot(rkP, rkQ);
	quat rkT;

	// Do we need to invert rotation?
	if (fCos < 0.0f && shortestPath)
	{
		fCos = -fCos;
		rkT = *rkQ;
		oquat_inverse(&rkT);
	}
	else
	{
		rkT = *rkQ;
	}

	if (fabsf(fCos) < 1 - 0.001f)
	{
		// Standard case (slerp)
		float fSin = sqrtf(1 - (fCos*fCos));
		float fAngle = atan2f(fSin, fCos); 
		float fInvSin = 1.0f / fSin;
		float fCoeff0 = sin((1.0f - fT) * fAngle) * fInvSin;
		float fCoeff1 = sin(fT * fAngle) * fInvSin;
		
		out_q->data[0] = fCoeff0 * rkP->data[0] + fCoeff1 * rkT[0];
		out_q->data[1] = fCoeff0 * rkP->data[1] + fCoeff1 * rkT[1];
		out_q->data[2] = fCoeff0 * rkP->data[2] + fCoeff1 * rkT[2];
		out_q->data[3] = fCoeff0 * rkP->data[3] + fCoeff1 * rkT[3];
			
		//return fCoeff0 * rkP + fCoeff1 * rkT;
	}
	else
	{
		// There are two situations:
		// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
		//    interpolation safely.
		// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
		//    are an infinite number of possibilities interpolation. but we haven't
		//    have method to fix this case, so just use linear interpolation here.
		//Quaternion t = (1.0f - fT) * rkP + fT * rkT;
		
		out_q->data[0] = (1.0f - fT) * rkP->data[0] + fT * rkT[0];
		out_q->data[1] = (1.0f - fT) * rkP->data[1] + fT * rkT[1];
		out_q->data[2] = (1.0f - fT) * rkP->data[2] + fT * rkT[2];
		out_q->data[3] = (1.0f - fT) * rkP->data[3] + fT * rkT[3];
			
		oquat_normalize_me(out_q);
		
		// taking the complement requires renormalisation
		//t.normalise();
		//return t;
	}
}

void oquat_get_mat4x4(const quat* me, const vec3* point, float mat[4][4])
{
	mat[0][0] = 1 - 2 * me->data[1] * me->data[1] - 2 * me->data[2] * me->data[2];
	mat[0][1] =     2 * me->data[0] * me->data[1] - 2 * me->data[3] * me->data[2];
	mat[0][2] =     2 * me->data[0] * me->data[2] + 2 * me->data[3] * me->data[1];
	mat[0][3] = point->data[0];

	mat[1][0] =     2 * me->data[0] * me->data[1] + 2 * me->data[3] * me->data[2];
	mat[1][1] = 1 - 2 * me->data[0] * me->data[0] - 2 * me->data[2] * me->data[2];
	mat[1][2] =     2 * me->data[1] * me->data[2] - 2 * me->data[3] * me->data[0];
	mat[1][3] = point->data[1];

	mat[2][0] =     2 * me->data[0] * me->data[2] - 2 * me->data[3] * me->data[1];
	mat[2][1] =     2 * me->data[1] * me->data[2] + 2 * me->data[3] * me->data[0];
	mat[2][2] = 1 - 2 * me->data[0] * me->data[0] - 2 * me->data[1] * me->data[1];
	mat[2][3] = point->data[2];

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}


// matrix

void omat4_init_ident(mat4* me)
{
	memset(me, 0, sizeof(*me));
	me->data[0][0] = 1.0f;
	me->data[1][1] = 1.0f;
	me->data[2][2] = 1.0f;
	me->data[3][3] = 1.0f;
}

void omat4_init_perspective(mat4* me, float fovy_rad, float aspect, float znear, float zfar)
{
	float sine, cotangent, delta, half_fov;

	half_fov = fovy_rad / 2.0f;
	delta = zfar - znear;
	sine = sinf(half_fov);

	if ((delta == 0.0f) || (sine == 0.0f) || (aspect == 0.0f)) {
		omat4_init_ident(me);
		return;
	}

	cotangent = cosf(half_fov) / sine;

	me->data[0][0] = cotangent / aspect;
	me->data[0][1] = 0;
	me->data[0][2] = 0;
	me->data[0][3] = 0;

	me->data[1][0] = 0;
	me->data[1][1] = cotangent;
	me->data[1][2] = 0;
	me->data[1][3] = 0;

	me->data[2][0] = 0;
	me->data[2][1] = 0;
	me->data[2][2] = -(zfar + znear) / delta;
	me->data[2][3] = -2.0f * znear * zfar / delta;

	me->data[3][0] = 0;
	me->data[3][1] = 0;
	me->data[3][2] = -1.0f;
	me->data[3][3] = 0;
}

void omat4_init_frustum(mat4* me, float left, float right, float bottom, float top, float znear, float zfar)
{
    omat4_init_ident(me);

    float delta_x = right - left;
    float delta_y = top - bottom;
	float delta_z = zfar - znear;
	if ((delta_x == 0.0f) || (delta_y == 0.0f) || (delta_z == 0.0f)) {
        // can't divide by zero, so just give back identity
		return;
	}

	me->data[0][0] = 2.0f * znear / delta_x;
	me->data[0][1] = 0;
	me->data[0][2] = (right + left) / delta_x;
	me->data[0][3] = 0;

	me->data[1][0] = 0;
	me->data[1][1] = 2.0f * znear / delta_y;
	me->data[1][2] = (top + bottom) / delta_y;
	me->data[1][3] = 0;

	me->data[2][0] = 0;
	me->data[2][1] = 0;
	me->data[2][2] = -(zfar + znear) / delta_z;
	me->data[2][3] = -2.0f * zfar * znear / delta_z;

	me->data[3][0] = 0;
	me->data[3][1] = 0;
	me->data[3][2] = -1.0f;
	me->data[3][3] = 0;
}

void omat4_init_look_at(mat4* me, const quat* rot, const vec3* eye)
{
	quat q;
	vec3 p;

	q[0] = -rot->data[0];
	q[1] = -rot->data[1];
	q[2] = -rot->data[2];
	q[3] =  rot->data[3];

	p[0] = -eye->data[0];
	p[1] = -eye->data[1];
	p[2] = -eye->data[2];

	me->data[0][0] = 1 - 2 * q[1] * q[1] - 2 * q[2] * q[2];
	me->data[0][1] =     2 * q[0] * q[1] - 2 * q[3] * q[2];
	me->data[0][2] =     2 * q[0] * q[2] + 2 * q[3] * q[1];
	me->data[0][3] = p[0] * me->data[0][0] + p[1] * me->data[0][1] + p[2] * me->data[0][2];

	me->data[1][0] =     2 * q[0] * q[1] + 2 * q[3] * q[2];
	me->data[1][1] = 1 - 2 * q[0] * q[0] - 2 * q[2] * q[2];
	me->data[1][2] =     2 * q[1] * q[2] - 2 * q[3] * q[0];
	me->data[1][3] = p[0] * me->data[1][0] + p[1] * me->data[1][1] + p[2] * me->data[1][2];

	me->data[2][0] =     2 * q[0] * q[2] - 2 * q[3] * q[1];
	me->data[2][1] =     2 * q[1] * q[2] + 2 * q[3] * q[0];
	me->data[2][2] = 1 - 2 * q[0] * q[0] - 2 * q[1] * q[1];
	me->data[2][3] = p[0] * me->data[2][0] + p[1] * me->data[2][1] + p[2] * me->data[2][2];

	me->data[3][0] = 0;
	me->data[3][1] = 0;
	me->data[3][2] = 0;
	me->data[3][3] = 1;
}

void omat4_init_Translate(mat4* me, float x, float y, float z)
{
	omat4_init_ident(me);
	me->data[0][3] = x;
	me->data[1][3] = y;
	me->data[2][3] = z;
}

void omat4_transpose(const mat4* m, mat4* o)
{
	o->data[0][0] = m->data[0][0];
	o->data[1][0] = m->data[0][1];
	o->data[2][0] = m->data[0][2];
	o->data[3][0] = m->data[0][3];

	o->data[0][1] = m->data[1][0];
	o->data[1][1] = m->data[1][1];
	o->data[2][1] = m->data[1][2];
	o->data[3][1] = m->data[1][3];

	o->data[0][2] = m->data[2][0];
	o->data[1][2] = m->data[2][1];
	o->data[2][2] = m->data[2][2];
	o->data[3][2] = m->data[2][3];

	o->data[0][3] = m->data[3][0];
	o->data[1][3] = m->data[3][1];
	o->data[2][3] = m->data[3][2];
	o->data[3][3] = m->data[3][3];
}

void omat4_mult(const mat4* l, const mat4* r, mat4 *o)
{
	for(int i = 0; i < 4; i++){
		float a0 = l->data[i][0], a1 = l->data[i][1], a2 = l->data[i][2], a3 = l->data[i][3];
		o->data[i][0] = a0 * r->data[0][0] + a1 * r->data[1][0] + a2 * r->data[2][0] + a3 * r->data[3][0];
		o->data[i][1] = a0 * r->data[0][1] + a1 * r->data[1][1] + a2 * r->data[2][1] + a3 * r->data[3][1];
		o->data[i][2] = a0 * r->data[0][2] + a1 * r->data[1][2] + a2 * r->data[2][2] + a3 * r->data[3][2];
		o->data[i][3] = a0 * r->data[0][3] + a1 * r->data[1][3] + a2 * r->data[2][3] + a3 * r->data[3][3];
	}
}


// filter queue

void InitFilterQueue(FilterQueue* me, int size)
{
	memset(me, 0, sizeof(FilterQueue));
	me->size = size;
}

void AddFilterQueue(FilterQueue* me, const vec3* vec)
{
	me->elems[me->at] = *vec;
	me->at = ((me->at + 1) % me->size);
}

void GetMeanFilterQueue(const FilterQueue* me, vec3* vec)
{
	vec->data[0] = vec->data[1] = vec->data[2] = 0;
	for(int i = 0; i < me->size; i++){
		vec->data[0] += me->elems[i][0];
		vec->data[1] += me->elems[i][1];
		vec->data[2] += me->elems[i][2];
	}

	vec->data[0] /= (float)me->size;
	vec->data[1] /= (float)me->size;
	vec->data[2] /= (float)me->size;
}


NAMESPACE_HMD_END


