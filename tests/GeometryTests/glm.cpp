#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <assert.h>
#include <iostream>
using namespace glm;
using namespace std;

#define DUMP(x) Dump(x)
#define ASSERT(x) assert(x)

#define VEC_FWD vec3(0,0,-1)
#define VEC_FWD4 vec4(0,0,-1,1)
#define VEC_BWD vec3(0,0,1)
#define VEC_BWD4 vec4(0,0,1,1)
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


void Dump(const vec3& v) {
	cout << "[";
	for(int i = 0; i < 3; i++) {
		if (i) cout << ", ";
		cout << v[i];
	}
	cout << "]";
	cout << endl;
}

void Dump(const vec4& v) {
	cout << "[";
	for(int i = 0; i < 4; i++) {
		if (i) cout << ", ";
		cout << v[i];
	}
	cout << "]";
	cout << endl;
}

void Dump(const mat4& m) {
	cout << "[";
	for(int i = 0; i < 4; i++) {
		if (i) cout << " ";
		cout << "[";
		for(int j = 0; j < 4; j++) {
			if (j) cout << ", ";
			cout << m[i][j];
		}
		if (i < 3)
			cout << "],\n";
		else
			cout << "]]\n";
	}
	cout << endl;
}
bool IsClose(const quat& a, const quat& b) {
	float sum = 0;
	for(int i = 0; i < 4; i++)
		sum += fabsf(a[i] - b[i]);
	return sum < 0.001;
}

bool IsClose(const vec3& a, const vec3& b) {
	float dist = distance(a, b);
	return fabsf(dist) < 0.001;
}

bool IsClose(const vec4& a, const vec4& b) {
	float dist = distance(a, b);
	return fabsf(dist) < 0.001;
}

bool IsClose(const mat4& a, const mat4& b) {
	double sum = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			sum += fabsf(a[i][j] - b[i][j]);
		}
	}
	return fabs(sum) < 0.001;
}


void glm_test() {
	
	{
		vec3 fwd_vec(0,0,1);
		mat4 fwd_mat = translate(identity<mat4>(), fwd_vec);
		Dump(fwd_mat);
	}
	
	{
		vec3 l0 = rotateY(VEC_FWD, (float)(+M_PI / 2.0));
		vec3 l1 = VEC_LEFT;
		DUMP(l0);
		DUMP(l1);
		ASSERT(IsClose(l0, l1));
		vec3 u0 = rotateX(VEC_FWD, (float)(+M_PI / 2.0));
		vec3 u1 = VEC_UP;
		DUMP(u0);
		DUMP(u1);
		ASSERT(IsClose(u0, u1));
		vec3 l2 = rotateZ(VEC_UP, (float)(+M_PI / 2.0));
		DUMP(l2);
		ASSERT(IsClose(l0, l2));
	}
	
	{
		quat q;
		q[0] = -0.173780918;
		q[1] = -0.00384500739;
		q[2] = -0.0217834469;
		q[3] = 0.984535873;
		
		mat4 m = toMat4(q);
		DUMP(m);
		
		/*
		data = {0.999021411, -0.0415567942, 0.0151421903, 0}
      data = {0.0442295484, 0.938651383, -0.342019588, 0}
      data = {-9.31322575e-10, 0.342354625, 0.939570844, 0}
      data = {0, 0, 0, 1}*/
      
		
		int i = 0;
	}
	
}
