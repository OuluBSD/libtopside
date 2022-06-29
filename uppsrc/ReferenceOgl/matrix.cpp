//since these fucntions use each other, make sure they're declared before they're defined
#include "matrix.h"

//can't make matrices without using some maths
#include <math.h>


void normalise(float vec[4]) {
	float x = vec[0] / vec[3];
	float y = vec[1] / vec[3];
	float z = vec[2] / vec[3];
	float length = sqrtf(x * x + y * y + z * z);
	
	vec[0] = x / length;
	vec[1] = y / length;
	vec[2] = z / length;
	vec[3] = 1;
}

void crossproduct(float a[4], float b[4], float result[4]) {
	result[0] = (a[1] * b[2]) - (a[2] * b[1]);
	result[1] = (a[2] * b[0]) - (a[0] * b[2]);
	result[2] = (a[0] * b[1]) - (a[1] * b[0]);
	result[3] = 1;
}

void multmatrix(float a[4][4], float b[4][4], float result[4][4]) {
	#if 1
	int r;
	int c2;
	int c;
	float total;
	
	for (r = 0; r < 4; r++) {
		for (c2 = 0; c2 < 4; c2++) {
			total = 0;
			for (c = 0; c < 4; c++) {
				float aa = a[c][c2];
				float bb = b[r][c];
				float mul = aa * bb;
				total += mul;
			}
			result[r][c2] = total;
		}
	}
	#else
	int i;
	int j;
	int k;
	float total;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			total = 0;
			for (k = 0; k < 4; k++)
				total += a[k][i] * b[j][k];
			result[j][i] = total;
		}
	}
	#endif
}

void Translate(float x, float y, float z, float result[4][4]) {
	result[0][0] = 1;
	result[0][1] = 0;
	result[0][2] = 0;
	result[0][3] = 0;
	result[1][0] = 0;
	result[1][1] = 1;
	result[1][2] = 0;
	result[1][3] = 0;
	result[2][0] = 0;
	result[2][1] = 0;
	result[2][2] = 1;
	result[2][3] = 0;
	result[3][0] = x;
	result[3][1] = y;
	result[3][2] = z;
	result[3][3] = 1;
}

void rotate(float angle, float x, float y, float z, float result[4][4]) {
	float vec[4] = {x, y, z, 1};
	float c = cosf(angle * M_PI / 180);
	float s = sinf(angle * M_PI / 180);
	normalise(vec);
	
	result[0][0] = vec[0] * vec[0] * (1 - c) + c;
	result[0][1] = vec[1] * vec[0] * (1 - c) + vec[2] * s;
	result[0][2] = vec[2] * vec[0] * (1 - c) - vec[1] * s;
	result[0][3] = 0;
	result[1][0] = vec[0] * vec[1] * (1 - c) - vec[2] * s;
	result[1][1] = vec[1] * vec[1] * (1 - c) + c;
	result[1][2] = vec[2] * vec[1] * (1 - c) + vec[0] * s;
	result[1][3] = 0;
	result[2][0] = vec[0] * vec[2] * (1 - c) + vec[1] * s;
	result[2][1] = vec[1] * vec[2] * (1 - c) - vec[0] * s;
	result[2][2] = vec[2] * vec[2] * (1 - c) + c;
	result[2][3] = 0;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
}

void lookat(float eyeX, float eyeY, float eyeZ, float centreX, float centreY, float centreZ, float upX, float upY, float upZ, float result[4][4]) {
	float f[4] = {centreX - eyeX, centreY - eyeY, centreZ - eyeZ, 1};
	float u[4] = {upX, upY, upZ, 1};
	float s[4];
	float temp[4][4];
	float temp2[4][4];
	normalise(f);
	normalise(u);
	
	crossproduct(f, u, s);
	normalise(s);
	crossproduct(s, f, u);
	
	temp[0][0] = s[0];
	temp[1][0] = s[1];
	temp[2][0] = s[2];
	temp[3][0] = 0;
	temp[0][1] = u[0];
	temp[1][1] = u[1];
	temp[2][1] = u[2];
	temp[3][1] = 0;
	temp[0][2] = -f[0];
	temp[1][2] = -f[1];
	temp[2][2] = -f[2];
	temp[3][2] = 0;
	temp[0][3] = 0;
	temp[1][3] = 0;
	temp[2][3] = 0;
	temp[3][3] = 1;
	
	Translate(-eyeX, -eyeY, -eyeZ, temp2);
	multmatrix(temp, temp2, result);
	
}

void perspective(float fovy, float aspect, float zNear, float zFar, float result[4][4]) {
	float f = 1 / tanf(fovy/* * M_PI / 360*/);
	
	result[0][0] = f / aspect;
	result[0][1] = 0;
	result[0][2] = 0;
	result[0][3] = 0;
	result[1][0] = 0;
	result[1][1] = f;
	result[1][2] = 0;
	result[1][3] = 0;
	result[2][0] = 0;
	result[2][1] = 0;
	result[2][2] = (zFar + zNear) / (zNear - zFar);
	result[2][3] = -1;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = (2 * zNear * zFar) / (zNear - zFar);
	result[3][3] = 0;
}
