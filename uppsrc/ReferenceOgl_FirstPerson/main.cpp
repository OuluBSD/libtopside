// From: https://gist.github.com/krzygorz/bd5c7fc5bfa5b50c6cbd
// Copyright: krzygorz

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define ESCAPE 27

void ResizeScene(int Width, int Height);
void RenderScene(void);
void ProcessNormalKeys(unsigned char key, int x, int y);
void ProcessSpecialKeys(int key, int x, int y);
void MouseMove(int x, int y);

// angle of rotation for the camera direction
float angle = 0;
float angle1 = -5000;

// actual vector representing the camera's direction
float lx = 0;
float ly = 0;
float lz = 1;

// XZ position of the camera
float xc = 0;
float yc = 0;
float zc = 10;
float speed = 0.1;
float rotSpeed = 0.0005;
int window;



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	
	window = glutCreateWindow("kasza");
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutReshapeFunc(ResizeScene);
	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(ProcessSpecialKeys);
	glutPassiveMotionFunc(MouseMove);
	
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(100, 100);
	glutMainLoop();
	
	return 0;
}

void ResizeScene(int Width, int Height) {
	if (Height == 0)
		Height = 1;
		
	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(xc, yc, zc,
			  xc + lx, yc + ly, zc + lz,
			  0, 1, 0);
	glutSolidTeapot(1);
	
	glutSwapBuffers();
}

void ProcessNormalKeys(unsigned char key, int x, int y) {
	if (key == ESCAPE) {
		glutDestroyWindow(window);
		exit(0);
	}
}
bool mouseCaptured = true;
void ProcessSpecialKeys(int key, int x, int y) {
	printf("rot: %f, %f\n", lx, lz);
	switch (key) {
	case GLUT_KEY_UP :
		xc += lx * speed;
		yc += ly * speed;
		zc += lz * speed;
		break;
	case GLUT_KEY_DOWN :
		xc -= lx * speed;
		yc -= ly * speed;
		zc -= lz * speed;
		break;
	case GLUT_KEY_LEFT :
		xc += lz * speed;
		zc -= lx * speed;
		break;
	case GLUT_KEY_RIGHT :
		xc -= lz * speed;
		zc += lx * speed;
		break;
	case GLUT_KEY_F1:
		mouseCaptured = !mouseCaptured;
		if (mouseCaptured) {
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else {
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	default:
		break;
	}
	printf("pos: %f, %f\n", xc, zc);
}

bool warping = false;
void MouseMove(int x, int y) {
	if (warping) {
		warping = false;
		return;
	}
	int dx = x - 100;
	int dy = y - 100;
	angle = angle + dx * rotSpeed;
	angle1 = angle1 + dy * rotSpeed;
	lx = sin(angle1) * sin(angle);
	ly = cos(angle1);
	lz = -sin(angle1) * cos(angle);
	printf("x: %d, y: %d, dx: %d, dy: %d, rot: %f, %f,%f angle: %f, angle1: %f\n", x, y, dx, dy, lx, ly, lz, angle, angle1);
	if (mouseCaptured) {
		warping = true;
		glutWarpPointer(100, 100);
	}
}
