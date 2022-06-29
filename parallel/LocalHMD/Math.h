#ifndef _LocalHMD_OMATH_H
#define _LocalHMD_OMATH_H


NAMESPACE_HMD_BEGIN



#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define POW2(_x) ((_x) * (_x))
#define RAD_TO_DEG(_r) ((_r) * 360.0f / (2.0f * (float)M_PI))
#define DEG_TO_RAD(_d) ((_d) * (2.0f * (float)M_PI) / 360.0f)


// vector

/*typedef union {
	struct {
		float x, y, z;
	};
	float data[3];
} vec3;*/

void ovec3_normalize_me(vec3* me);
float ovec3_get_length(const vec3* me);
float ovec3_get_angle(const vec3* me, const vec3* vec);
float ovec3_get_dot(const vec3* me, const vec3* vec);
void ovec3_subtract(const vec3* a, const vec3* b, vec3* out);


// quaternion

/*typedef union {
	struct {
		float x, y, z, w;
	};
	float data[4];
} quat;*/

void oquat_init_axis(quat* me, const vec3* vec, float angle);

void oquat_get_rotated(const quat* me, const vec3* vec, vec3* out_vec);
void oquat_mult_me(quat* me, const quat* q);
void oquat_mult(const quat* me, const quat* q, quat* out_q);
void oquat_diff(const quat* me, const quat* q, quat* out_q);
void oquat_normalize_me(quat* me);
float oquat_get_length(const quat* me);
float oquat_get_dot(const quat* me, const quat* q);
void oquat_inverse(quat* me);

void oquat_get_mat4x4(const quat* me, const vec3* point, float mat[4][4]);

// matrix

/*typedef union {
	float m[4][4];
	float data[16];
} mat4;*/

void omat4_init_ident(mat4* me);
void omat4_init_perspective(mat4* me, float fov_rad, float aspect, float znear, float zfar);
void omat4_init_frustum(mat4* me, float left, float right, float bottom, float top, float znear, float zfar);
void omat4_init_look_at(mat4* me, const quat* ret, const vec3* eye);
void omat4_init_Translate(mat4* me, float x, float y, float z);
void omat4_mult(const mat4* left, const mat4* right, mat4* out_mat);
void omat4_transpose(const mat4* me, mat4* out_mat);




// filter queue
#define FILTER_QUEUE_MAX_SIZE 256

typedef struct {
	int at, size;
	vec3 elems[FILTER_QUEUE_MAX_SIZE];
} FilterQueue;

void InitFilterQueue(FilterQueue* me, int size);
void AddFilterQueue(FilterQueue* me, const vec3* vec);
void GetMeanFilterQueue(const FilterQueue* me, vec3* vec);


NAMESPACE_HMD_END


#endif
