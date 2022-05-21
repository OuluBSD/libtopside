#ifndef MATRIX_H
#define MATRIX_H

//define M_PI to something sensible since we're using c99 which doens't define it for whatever reason
#define M_PI 3.14159265358979323846264338327

void normalise ( float vec[4] );
void crossproduct ( float a[4], float b[4], float result[4] );
void multmatrix ( float a[4][4], float b[4][4], float result[4][4] );
void rotate ( float angle, float x, float y, float z, float result[4][4] );
void translate ( float x, float y, float z, float result[4][4] );
void lookat ( float eyeX, float eyeY, float eyeZ, float centreX, float centreY, float centreZ, float upX, float upY, float upZ, float result[4][4] );
void perspective ( float fovy, float aspect, float zNear, float zFar, float result[4][4] );

#endif