#include "SoftPhysTests.h"

#include <Graphics/IfaceOgl.h>

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {

#ifndef  M_PI
	#define M_PI 3.14159265358979323846f
#endif

#if 0

void Render(const Mesh& mesh) {
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < mesh.numTriangles; ++i) {
		vec3 normal = Normalized(Cross(mesh.triangles[i].c - mesh.triangles[i].a, mesh.triangles[i].b - mesh.triangles[i].a));
		glNormal3fv(normal.data);

		glVertex3fv(mesh.triangles[i].a.data);
		glVertex3fv(mesh.triangles[i].b.data);
		glVertex3fv(mesh.triangles[i].c.data);
	}

	glEnd();
}

void Render(const Model& model) {
	glPushMatrix();

	mat4 world = GetWorldMatrix(model);
	glMultMatrixf(world.AsArray());
	if (model.GetMesh() != 0) {
		Render(*(model.GetMesh()));
	}

	glPopMatrix();
}

void RenderNormals(const Frustum& frustum) {
	vec3 NTL = Intersection(frustum._near, frustum.top, frustum.left);
	vec3 NTR = Intersection(frustum._near, frustum.top, frustum.right);
	vec3 NBL = Intersection(frustum._near, frustum.bottom, frustum.left);
	vec3 NBR = Intersection(frustum._near, frustum.bottom, frustum.right);

	vec3 FTL = Intersection(frustum._far, frustum.top, frustum.left);
	vec3 FTR = Intersection(frustum._far, frustum.top, frustum.right);
	vec3 FBL = Intersection(frustum._far, frustum.bottom, frustum.left);
	vec3 FBR = Intersection(frustum._far, frustum.bottom, frustum.right);

	vec3 centers[] = {
		(NTR + NTL + FTR + FTL) * 0.25f, // Top
		(NBR + NBL + FBR + FBL) * 0.25f, // Bottom
		(NTL + NBL + FTL + FBL) * 0.25f,// Left
		(NTR + NBR + FTR + FBR) * 0.25f,// Right
		(NTL + NTR + NBL + NBR) * 0.25f,// Near
		(FTL + FTR + FBL + FBR) * 0.25f// Far
	};

	glBegin(GL_LINES);
	for (int i = 0; i < 6; ++i) {
		vec3 p1 = centers[i] + frustum.planes[i].normal * 0.5f;
		glVertex3fv(centers[i].data);
		glVertex3fv(p1.data);
	}
	glEnd();

	for (int i = 0; i < 6; ++i) {
		vec3 p1 = centers[i] + frustum.planes[i].normal * 0.5f;
		vec3 p2 = p1 + frustum.planes[i].normal * 0.25f;

		mat4 orient = FastInverse(LookAt(p1, p2, vec3(0, 1, 0))).GetInverse();
		mat4 rotate = Rotation(90.0f, 0.0f, 0.0f);

		glPushMatrix();
		glMultMatrixf((rotate * orient).AsArray());
		FixedFunctionCone(3, 3.0f, 0.1f);
		glPopMatrix();
	}
}

void Render(const Frustum& frustum) {
	vec3 NTL = Intersection(frustum._near, frustum.top, frustum.left);
	vec3 NTR = Intersection(frustum._near, frustum.top, frustum.right);
	vec3 NBL = Intersection(frustum._near, frustum.bottom, frustum.left);
	vec3 NBR = Intersection(frustum._near, frustum.bottom, frustum.right);

	vec3 FTL = Intersection(frustum._far, frustum.top, frustum.left);
	vec3 FTR = Intersection(frustum._far, frustum.top, frustum.right);
	vec3 FBL = Intersection(frustum._far, frustum.bottom, frustum.left);
	vec3 FBR = Intersection(frustum._far, frustum.bottom, frustum.right);
	
	glBegin(GL_LINES);

	// Near
	glVertex3fv(NTL.data);
	glVertex3fv(NTR.data);
	glVertex3fv(NTR.data);
	glVertex3fv(NBR.data);
	glVertex3fv(NBR.data);
	glVertex3fv(NBL.data);
	glVertex3fv(NBL.data);
	glVertex3fv(NTL.data);

	// Far
	glVertex3fv(FTL.data);
	glVertex3fv(FTR.data);
	glVertex3fv(FTR.data);
	glVertex3fv(FBR.data);
	glVertex3fv(FBR.data);
	glVertex3fv(FBL.data);
	glVertex3fv(FBL.data);
	glVertex3fv(FTL.data);

	// Edges
	glVertex3fv(NTL.data);
	glVertex3fv(FTL.data);
	glVertex3fv(NTR.data);
	glVertex3fv(FTR.data);
	glVertex3fv(NBL.data);
	glVertex3fv(FBL.data);
	glVertex3fv(NBR.data);
	glVertex3fv(FBR.data);


	glEnd();
}

void Render(const Plane& plane, float scale) {
	glPushMatrix();
	glScalef(scale, scale, scale);
	Render(plane);
	glPopMatrix();
}

void Render(const Plane& plane) {
	vec3 forward = plane.normal;
	vec3 up = vec3(0, 1, 0);
	if (CMP(MagnitudeSq(Cross(up, plane.normal)), 0)) {
		up = vec3(1, 0, 0);
		if (CMP(MagnitudeSq(Cross(up, plane.normal)), 0)) {
			up = vec3(0, 0, 1);
		}
	}
	vec3 right = Cross(up, forward);
	up = Cross(forward, right);

	vec3 n = Normalized(plane.normal);
	float d = plane.distance;
	vec3 tx = Normalized(right);
	vec3 ty = Normalized(up);

	glBegin(GL_QUADS);
		glVertex3f((tx[0] + ty[0]) + n[0] * d, (tx[1] + ty[1]) + n[1] * d, (tx[2] + ty[2]) + n[2] * d);
		glVertex3f((tx[0] - ty[0]) + n[0] * d, (tx[1] - ty[1]) + n[1] * d, (tx[2] - ty[2]) + n[2] * d);
		glVertex3f((-tx[0] - ty[0]) + n[0] * d, (-tx[1] - ty[1]) + n[1] * d, (-tx[2] - ty[2]) + n[2] * d);
		glVertex3f((-tx[0] + ty[0]) + n[0] * d, (-tx[1] + ty[1]) + n[1] * d, (-tx[2] + ty[2]) + n[2] * d);

		glVertex3f((tx[0] + ty[0]) + n[0] * d, (tx[1] + ty[1]) + n[1] * d, (tx[2] + ty[2]) + n[2] * d);
		glVertex3f((-tx[0] + ty[0]) + n[0] * d, (-tx[1] + ty[1]) + n[1] * d, (-tx[2] + ty[2]) + n[2] * d);
		glVertex3f((-tx[0] - ty[0]) + n[0] * d, (-tx[1] - ty[1]) + n[1] * d, (-tx[2] - ty[2]) + n[2] * d);
		glVertex3f((tx[0] - ty[0]) + n[0] * d, (tx[1] - ty[1]) + n[1] * d, (tx[2] - ty[2]) + n[2] * d);
	glEnd();

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	vec3 start = n * d;
	vec3 end = start + n;
	glVertex3f(start[0], start[1], start[2]);
	glVertex3f(end[0], end[1], end[2]);
	glEnd();

	glColor4fv(currentColor);
}

void Render(const Triangle& triangle) {
	Render(triangle, false);
}

void Render(const Triangle& triangle, bool oneSided) {
	glBegin(GL_TRIANGLES);

	if (!oneSided) {
		glVertex3f(triangle.a[0], triangle.a[1], triangle.a[2]);
		glVertex3f(triangle.c[0], triangle.c[1], triangle.c[2]);
		glVertex3f(triangle.b[0], triangle.b[1], triangle.b[2]);
	}
	else {
		vec3 ab = triangle.a - triangle.b;
		vec3 ac = triangle.a - triangle.c;
		vec3 norm = Normalized(Cross(ac, ab));
		glNormal3f(norm[0], norm[1], norm[2]);
	}

	glVertex3f(triangle.a[0], triangle.a[1], triangle.a[2]);
	glVertex3f(triangle.b[0], triangle.b[1], triangle.b[2]);
	glVertex3f(triangle.c[0], triangle.c[1], triangle.c[2]);

	glEnd();
}

void Render(const Circle& circle) {
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; ++i) {
		glVertex2f(circle.position[0] + cosf(DEG2RAD(i)) * circle.radius, circle.position[1] + sinf(DEG2RAD(i)) * circle.radius);
	}

	glEnd();
}

void Render(const Line2D& line) {
	glBegin(GL_LINES);
	glVertex3f(line.start[0], line.start[1], 0.0f);
	glVertex3f(line.end[0], line.end[1], 0.0f);
	glEnd();
}

void Render(const Point2D& point) {
	glBegin(GL_POINTS);
	glVertex3f(point[0], point[1], 0.0f);
	glEnd();
}

void Render(const Point& point) {
	glBegin(GL_POINTS);
	glVertex3f(point[0], point[1], point[2]);
	glEnd();
}

void Render(const Ray& ray) {
	// Bit of an ugly hack, just make a really long line
	Line line;
	line.start = ray.origin;
	line.end = ray.origin + ray.direction * 50000.0f;
	// And then render that line :(
	glBegin(GL_LINES);
	glVertex3f(line.start[0], line.start[1], line.start[2]);
	glVertex3f(line.end[0], line.end[1], line.end[2]);
	glEnd();
	// At some point i'm going to fix this
}

void Render(const AABB& aabb) {
	glPushMatrix();

	glTranslatef(aabb.position[0], aabb.position[1], aabb.position[2]);
	FixedFunctionCube(aabb.size[0], aabb.size[1], aabb.size[2]);

	glPopMatrix();
}

void RenderWithQuads(const AABB& aabb) {
	glPushMatrix();

	glTranslatef(aabb.position[0], aabb.position[1], aabb.position[2]);
	FixedFunctionCubeQuads(aabb.size[0], aabb.size[1], aabb.size[2]);

	glPopMatrix();
}

void Render(const Rectangle2D& rect) {
	vec2 min = GetMin(rect);
	vec2 max = GetMax(rect);

	glBegin(GL_LINES); 
	glVertex3f(min[0], min[1], 0.0f);
	glVertex3f(min[0], max[1], 0.0f);
	glVertex3f(min[0], max[1], 0.0f);
	glVertex3f(max[0], max[1], 0.0f);
	glVertex3f(max[0], max[1], 0.0f);
	glVertex3f(max[0], min[1], 0.0f);
	glVertex3f(max[0], min[1], 0.0f);
	glVertex3f(min[0], min[1], 0.0f);
	glEnd();
}

void Render(const BVHNode& bvh) {
	if (bvh.children == 0) {
		RenderWithQuads(bvh.bounds);
	}
	else {
		for (int i = 0; i < 8; ++i) {
			Render(bvh.children[i]);
		}
	}
}

void Render(const OrientedRectangle& rect) {
	glPushMatrix();
	glTranslatef(rect.position[0], rect.position[1], 0.0f);
	glRotatef(rect.rotation, 0.0f, 0.0f, 1.0f);

	vec2 min = vec2(-rect.halfExtents[0], -rect.halfExtents[1]);
	vec2 max = vec2(+rect.halfExtents[0], +rect.halfExtents[1]);
	
	glBegin(GL_LINES);
	glVertex3f(min[0], min[1], 0.0f);
	glVertex3f(min[0], max[1], 0.0f);
	glVertex3f(min[0], max[1], 0.0f);
	glVertex3f(max[0], max[1], 0.0f);
	glVertex3f(max[0], max[1], 0.0f);
	glVertex3f(max[0], min[1], 0.0f);
	glVertex3f(max[0], min[1], 0.0f);
	glVertex3f(min[0], min[1], 0.0f);
	glEnd();

	glPopMatrix();
}

void FixedFunctionSphere() {
	FixedFunctionSphere(2, 1.0f);
}

void FixedFunctionCubeQuads(float extentsX, float extentsY, float extentsZ) {
	float min[] = { -extentsX, -extentsY, -extentsZ };
	float max[] = { +extentsX, +extentsY, +extentsZ };

	glBegin(GL_QUADS);

#if 1
	// Top!
	glNormal3f(0.0f, 1.0f, 0.0f);
	/*0*/glVertex3f(min[0], max[1], min[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*2*/glVertex3f(max[0], max[1], max[2]);
	/*3*/glVertex3f(min[0], max[1], max[2]);
#endif

#if 1
	// Front!
	glNormal3f(0.0f, 0.0f, 1.0f);
	/*0*/glVertex3f(min[0], max[1], max[2]);
	/*1*/glVertex3f(max[0], max[1], max[2]);
	/*2*/glVertex3f(max[0], min[1], max[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
#endif

#if 1
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	/*0*/glVertex3f(min[0], max[1], max[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
	/*2*/glVertex3f(min[0], min[1], min[2]);
	/*1*/glVertex3f(min[0], max[1], min[2]);
#endif

#if 1
	// Bottom!
	glNormal3f(0.0f, -1.0f, 0.0f);
	/*0*/glVertex3f(min[0], min[1], min[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
	/*2*/glVertex3f(max[0], min[1], max[2]);
	/*1*/glVertex3f(max[0], min[1], min[2]);
#endif

#if 1
	// Back!
	glNormal3f(0.0f, 0.0f, -1.0f);
	/*0*/glVertex3f(min[0], max[1], min[2]);
	/*3*/glVertex3f(min[0], min[1], min[2]);
	/*2*/glVertex3f(max[0], min[1], min[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
#endif

#if 1
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	/*0*/glVertex3f(max[0], max[1], max[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*2*/glVertex3f(max[0], min[1], min[2]);
	/*3*/glVertex3f(max[0], min[1], max[2]);
#endif

	glEnd();
}

void FixedFunctionTorus(float outerRaidus, float innerRadius) {
	float diff = (outerRaidus - innerRadius);
	float minorRad = diff * 0.5f;
	float majorRad = outerRaidus - minorRad;
	FixedFunctionTorus(15, 10, majorRad, minorRad);
}

void FixedFunctionTorus() {
	FixedFunctionTorus(1.0f, 0.5f);
}

void FixedFunctionCylinder(float height, float radius) {
	FixedFunctionCylinder(15, height, radius);
}

void FixedFunctionCylinder(float height) {
	FixedFunctionCylinder(15, height, 1.0f);
}

void FixedFunctionCylinder() {
	FixedFunctionCylinder(15, 1.0f, 1.0f);
}

void FixedFunctionCylinder(int slices, float height, float radius) {
	height *= 0.5f;
	float twopi_slices = (2.0f * M_PI) / (float)slices;

	// HULL
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= slices; i++) {
		double angle = twopi_slices * (float)i;  // i 16-ths of a full circle
		double x = cos(angle);
		double z = sin(angle);

		float norm[] = { (float)x, 0.0f, (float)z };
		float d = sqrtf(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
		norm[0] /= d; norm[1] /= d; norm[2] /= d;

		x *= radius;
		z *= radius;

		glNormal3f(norm[0], norm[1], norm[2]); 
		glVertex3f((float)x, (float)height, (float)z);
		glVertex3f((float)x, (float)(-height), (float)z);
	}
	glEnd();

	// TOP CAP
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN); 
	for (int i = 0; i <= slices; i++) {
		double angle = twopi_slices * (float)i;
		double x = cos(angle) * radius;
		double z = sin(angle) * radius;
		glVertex3f((float)x, (float)height, (float)z);
	}
	glEnd();

	// BOTTOM CAP
	glNormal3f(0.0f, -1.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN); 
	for (int i = slices; i >= 0; i--) {
		double angle = twopi_slices * (float)i;
		double x = cos(angle) * radius;
		double z = sin(angle) * radius;
		glVertex3f((float)x, (float)(-height), (float)z);
	}
	glEnd();
}

void FixedFunctionTorus(int TORUS_MAJOR_RES, int TORUS_MINOR_RES, float TORUS_MAJOR, float TORUS_MINOR) {
	int    i, j, k;
	double s, t, x, y, z, nx, ny, nz, scale, twopi;

	twopi = 2.0 * M_PI;
	for (i = 0; i < TORUS_MINOR_RES; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= TORUS_MAJOR_RES; j++)
		{
			for (k = 1; k >= 0; k--)
			{
				s = (i + k) % TORUS_MINOR_RES + 0.5;
				t = j % TORUS_MAJOR_RES;

				// Calculate point on surface
				x = (TORUS_MAJOR + TORUS_MINOR * cos(s * twopi / TORUS_MINOR_RES)) * cos(t * twopi / TORUS_MAJOR_RES);
				y = TORUS_MINOR * sin(s * twopi / TORUS_MINOR_RES);
				z = (TORUS_MAJOR + TORUS_MINOR * cos(s * twopi / TORUS_MINOR_RES)) * sin(t * twopi / TORUS_MAJOR_RES);

				// Calculate surface normal
				nx = x - TORUS_MAJOR * cos(t * twopi / TORUS_MAJOR_RES);
				ny = y;
				nz = z - TORUS_MAJOR * sin(t * twopi / TORUS_MAJOR_RES);
				scale = 1.0 / sqrt(nx*nx + ny*ny + nz*nz);
				nx *= scale;
				ny *= scale;
				nz *= scale;

				glNormal3f((float)nx, (float)ny, (float)nz);
				glVertex3f((float)x, (float)y, (float)z);
			}
		}

		glEnd();
	}
}

void FixedFunctionPlane(float size, int subdivs) {
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.0f);

	float slice = size / (float)subdivs;

	for (int i = 0; i < subdivs; ++i) {
		for (int j = 0; j < subdivs; ++j) {
			float x = ((float)i * slice) - (size * 0.5f);
			float z = ((float)j * slice) - (size * 0.5f);

			glVertex3f(x,         0.0f, z);
			glVertex3f(x + slice, 0.0f, z);
			glVertex3f(x,         0.0f, z + slice);
			glVertex3f(x + slice, 0.0f, z);
			glVertex3f(x + slice, 0.0f, z + slice);
			glVertex3f(x,         0.0f, z + slice);
		}
	}

	glEnd();
}

void FixedFunctionPlane(float size) {
	FixedFunctionPlane(size, 10);
}

void FixedFunctionPlane() {
	FixedFunctionPlane(10, 10);
}


void FixedFunctionSubdivCone(float *v1, float *v2, int subdiv, float height, float radius) {
	float v0[3] = { 0, 0, 0 };

	if (subdiv == 0) {
		// Bottom cover of the cone
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(v0[0] * radius, v0[1] * radius, v0[2] * radius);
		glVertex3f(v2[0] * radius, v2[1] * radius, v2[2] * radius);
		glVertex3f(v1[0] * radius, v1[1] * radius, v1[2] * radius);

		v0[1] = height; // height of the cone, the tip on y axis
		// Side cover of the cone
		float e1[] = { v0[0] - v1[0], v0[1] - v1[1], v0[2] - v1[2] };
		float e2[] = { v0[0] - v2[0], v0[1] - v2[1], v0[2] - v2[2] };
		float n[] = {
			e1[1] * e2[2] - e1[2] * e2[1],
			e1[2] * e2[0] - e1[0] * e2[2],
			e1[0] * e2[1] - e1[1] * e2[0],
		};
		float d = 1.0f / sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
		
		glNormal3f(n[0] * d, n[1] * d, n[2] * d);
		glVertex3f(v0[0] * radius, v0[1] * radius, v0[2] * radius);
		
		glNormal3fv(v1);
		glVertex3f(v1[0] * radius, v1[1] * radius, v1[2] * radius);
		
		glNormal3fv(v2);
		glVertex3f(v2[0] * radius, v2[1] * radius, v2[2] * radius);

		return;
	}

	float v12[3]{
		v1[0] + v2[0],
		v1[1] + v2[1],
		v1[2] + v2[2],
	};

	// Normalize
	float d = 1.0f / sqrtf(v12[0] * v12[0] + v12[1] * v12[1] + v12[2] * v12[2]);
	v12[0] *= d; v12[1] *= d; v12[2] *= d;

	FixedFunctionSubdivCone(v1, v12, subdiv - 1, height, radius);
	FixedFunctionSubdivCone(v12, v2, subdiv - 1, height, radius);
}


void FixedFunctionCone(int subdiv, float height, float radius) {
	static float vdata[4][3] = {
		{  1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f,  1.0f },
		{ -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }
	};

	glBegin(GL_TRIANGLES);
	FixedFunctionSubdivCone(vdata[0], vdata[1], subdiv, height, radius);
	FixedFunctionSubdivCone(vdata[1], vdata[2], subdiv, height, radius);
	FixedFunctionSubdivCone(vdata[2], vdata[3], subdiv, height, radius);
	FixedFunctionSubdivCone(vdata[3], vdata[0], subdiv, height, radius);
	glEnd();
}

void FixedFunctionCone(float height, float radius) {
	FixedFunctionCone(3, height, radius);
}

void FixedFunctionCone() {
	FixedFunctionCone(3, 1.0f, 1.0f);
}

#endif

void FixedFunctionCube(float extentsX, float extentsY, float extentsZ) {
	float min[] = { -extentsX, -extentsY, -extentsZ };
	float max[] = { +extentsX, +extentsY, +extentsZ };

	glBegin(GL_TRIANGLES);

#if 1
	// Top!
	glNormal3f(0.0f, 1.0f, 0.0f);
	/*0*/glVertex3f(min[0], max[1], min[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*3*/glVertex3f(min[0], max[1], max[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*2*/glVertex3f(max[0], max[1], max[2]);
	/*3*/glVertex3f(min[0], max[1], max[2]);
#endif

#if 1
	// Front!
	glNormal3f(0.0f, 0.0f, 1.0f);
	/*0*/glVertex3f(min[0], max[1], max[2]);
	/*1*/glVertex3f(max[0], max[1], max[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
	/*1*/glVertex3f(max[0], max[1], max[2]);
	/*2*/glVertex3f(max[0], min[1], max[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
#endif

#if 1
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	/*0*/glVertex3f(min[0], max[1], max[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
	/*1*/glVertex3f(min[0], max[1], min[2]);
	/*1*/glVertex3f(min[0], max[1], min[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
	/*2*/glVertex3f(min[0], min[1], min[2]);
#endif

#if 1
	// Bottom!
	glNormal3f(0.0f, -1.0f, 0.0f);
	/*0*/glVertex3f(min[0], min[1], min[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
	/*1*/glVertex3f(max[0], min[1], min[2]);
	/*1*/glVertex3f(max[0], min[1], min[2]);
	/*3*/glVertex3f(min[0], min[1], max[2]);
	/*2*/glVertex3f(max[0], min[1], max[2]);
#endif

#if 1
	// Back!
	glNormal3f(0.0f, 0.0f, -1.0f);
	/*0*/glVertex3f(min[0], max[1], min[2]);
	/*3*/glVertex3f(min[0], min[1], min[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*3*/glVertex3f(min[0], min[1], min[2]);
	/*2*/glVertex3f(max[0], min[1], min[2]);
#endif

#if 1
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	/*0*/glVertex3f(max[0], max[1], max[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*3*/glVertex3f(max[0], min[1], max[2]);
	/*1*/glVertex3f(max[0], max[1], min[2]);
	/*2*/glVertex3f(max[0], min[1], min[2]);
	/*3*/glVertex3f(max[0], min[1], max[2]);
#endif

	glEnd();
}

void FixedFunctionSubdivTetrahedron(float* a, float* b, float* c, int div, float r) {
	if (div <= 0) {
		glNormal3fv(a);
		glVertex3f(a[0] * r, a[1] * r, a[2] * r);
		
		glNormal3fv(b);
		glVertex3f(b[0] * r, b[1] * r, b[2] * r);
		
		glNormal3fv(c);
		glVertex3f(c[0] * r, c[1] * r, c[2] * r);
	}
	else {
		float ab[3], ac[3], bc[3];

		ab[0] = (a[0] + b[0]) / 2.0f;
		ac[0] = (a[0] + c[0]) / 2.0f;
		bc[0] = (b[0] + c[0]) / 2.0f;

		ab[1] = (a[1] + b[1]) / 2.0f;
		ac[1] = (a[1] + c[1]) / 2.0f;
		bc[1] = (b[1] + c[1]) / 2.0f;
		
		ab[2] = (a[2] + b[2]) / 2.0f;
		ac[2] = (a[2] + c[2]) / 2.0f;
		bc[2] = (b[2] + c[2]) / 2.0f;

		// Normalize ab
		float d = sqrtf(ab[0] * ab[0] + ab[1] * ab[1] + ab[2] * ab[2]);
		ab[0] /= d; ab[1] /= d; ab[2] /= d;
		// Normalize ac
		d = sqrtf(ac[0] * ac[0] + ac[1] * ac[1] + ac[2] * ac[2]);
		ac[0] /= d; ac[1] /= d; ac[2] /= d;
		// Normalize bc
		d = sqrtf(bc[0] * bc[0] + bc[1] * bc[1] + bc[2] * bc[2]);
		bc[0] /= d; bc[1] /= d; bc[2] /= d;

		FixedFunctionSubdivTetrahedron(a, ab, ac, div - 1, r);
		FixedFunctionSubdivTetrahedron(b, bc, ab, div - 1, r);
		FixedFunctionSubdivTetrahedron(c, ac, bc, div - 1, r);
		FixedFunctionSubdivTetrahedron(ab, bc, ac, div - 1, r); 
	}
}

void FixedFunctionSphere(int numDivisions, float radius) {
	static float X = 0.525731112119133606f;
	static float Y = 0.0f;
	static float Z = 0.850650808352039932f;

	static float vdata[12][3] = {
		{ -X,Y,Z },{ X,Y,Z },{ -X,Y,-Z },{ X,Y,-Z },
		{ Y,Z,X },{ Y,Z,-X },{ Y,-Z,X },{ Y,-Z,-X },
		{ Z,X,Y },{ -Z,X,Y },{ Z,-X,Y },{ -Z,-X,Y } 
	};
	static int tindices[20][3] = { 
		{ 0,4,1 },{ 0,9,4 },{ 9,5,4 },{ 4,5,8 },{ 4,8,1 },
		{ 8,10,1 },{ 8,3,10 },{ 5,3,8 },{ 5,2,3 },{ 2,7,3 },
		{ 7,10,3 },{ 7,6,10 },{ 7,11,6 },{ 11,0,6 },{ 0,1,6 },
		{ 6,1,10 },{ 9,0,11 },{ 9,11,2 },{ 9,2,5 },{ 7,2,11 } 
	};

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 20; ++i) {
		FixedFunctionSubdivTetrahedron(
			vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], numDivisions, radius
		);
	}

	glEnd();
}

void FixedFunctionCube() {
	FixedFunctionCube(1.0f, 1.0f, 1.0f);
}

void FixedFunctionOrigin(bool depthTest, bool twoSided) {
	bool isLit = glIsEnabled(GL_LIGHTING) == GL_TRUE;
	bool depthOn = glIsEnabled(GL_DEPTH_TEST) == GL_TRUE;

	if (isLit) {
		glDisable(GL_LIGHTING);
	}
	if (depthOn && !depthTest) {
		glDisable(GL_DEPTH_TEST);
	} else if (depthTest) {
		glEnable(GL_DEPTH_TEST);
	}

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	if (twoSided) {
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
	}

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	if (twoSided) {
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
	}

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	if (twoSided) {
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -1.0f);
	}
	glEnd();

	if (isLit) {
		glEnable(GL_LIGHTING);
	}
	if (depthOn) {
		glEnable(GL_DEPTH_TEST);
	}
}

void FixedFunctionOrigin(bool depthTest) {
	FixedFunctionOrigin(depthTest, false);
}

void FixedFunctionOrigin() {
	FixedFunctionOrigin(false, false);
}

template<>
void Wrap<Line>::Refresh(GfxDataState& s) {
	glBegin(GL_LINES);
	glVertex3f(start[0], start[1], start[2]);
	glVertex3f(end[0], end[1], end[2]);
	glEnd();
}

template<>
void Wrap<Sphere>::Refresh(GfxDataState& s) {
	glPushMatrix();

	glTranslatef(position[0], position[1], position[2]);
	FixedFunctionSphere(2, radius);

	glPopMatrix();
}

template<>
void Wrap<OBB>::Refresh(GfxDataState& s) {
	glPushMatrix();

	mat4 scale = TS::scale(size);
	mat4 rotation = orientation.Extend();
	mat4 translation = Translation(position);

	// SRT: Scale First, Rotate Second, Translate Last
	// orientation = roll * pitch * yaw;
	mat4 transform = scale * rotation * translation;
	
	// Using GL pipe stuff:
	// glTranslate(obb.position[0], obb.position[1], obb.position[2]);
	// Orientation = yaw * pitch * roll
	// glRotate??? Probably do a matrix multiplication instead
	// glScale(obb.size[0], obb.size[1], obb.size[2]);

	glMultMatrixf(transform.AsArray());
	FixedFunctionCube();
	glPopMatrix();
}


void PhysicsSystem::Refresh(GfxDataState& s) {
	int i = 0;
	for (Space* sp : spaces) for(Geometry* g : sp->geoms) {
		g->Refresh(s);
		i++;
	}

	for (OBB_& obb : constraints)
		obb.Refresh(s);
	
	if (s.dbg_render) {
		for (CollisionManifold& cm : results)
			cm.Refresh(s);
	}

	for (Spring& sp : springs)
		sp.Refresh(s);

	for (Cloth* c : cloths)
		c->Refresh(s);
	
}


void Cloth::Refresh(GfxDataState& s) {
	static const float redDiffuse[]{ 200.0f / 255.0f, 0.0f, 0.0f, 0.0f };
	static const float redAmbient[]{ 200.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f, 0.0f };
	static const float zero[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glColor3f(redDiffuse[0], redDiffuse[1], redDiffuse[2]);
	glLightfv(GL_LIGHT0, GL_AMBIENT, redAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, redDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, zero);

	if (s.dbg_render) {
		for (int i = 0, size = verts.GetCount(); i < size; ++i) {
			verts[i].Refresh(s);
		}

		GLboolean status;
		glGetBooleanv(GL_LIGHTING, &status);
		glDisable(GL_LIGHTING);
		
		glColor3f(1.0f, 0.0f, 1.0f);
		for (Spring& p : structural) {
			if (p.GetP1() == 0 || p.GetP2() == 0)
				continue;
			
			p.Refresh(s);
		}

		glColor3f(1.0f, 1.0f, 0.0f);
		for (Spring& p : shear) {
			if (p.GetP1() == 0 || p.GetP2() == 0)
				continue;
			
			p.Refresh(s);
		}

		glColor3f(0.0f, 1.0f, 1.0f);
		for (Spring& p : bend) {
			if (p.GetP1() == 0 || p.GetP2() == 0)
				continue;
			
			// Visualization
			/*
			vec3 p1 = bend[i].GetP1()->GetPosition();
			vec3 p2 = bend[i].GetP2()->GetPosition();
			p1.y += 0.1f;
			p2.y += 0.1f;
			for (int j = i; j >= 0; --j) {
				p1.y += 0.1f;
				p2.y += 0.1f;
			}*/

			p.Refresh(s);
		}
		
	}
	else {
		#if 0
		for (int x = 0; x < clothSize - 1; ++x) {
			for (int z = 0; z < clothSize - 1; ++z) {
				int tl = z * clothSize + x;
				int bl = (z + 1) * clothSize + x;
				int tr = z * clothSize + (x + 1);
				int br = (z + 1) * clothSize + (x + 1);

				Triangle t1(verts[tl].GetPosition(), verts[br].GetPosition(), verts[bl].GetPosition());
				Triangle t2(verts[tl].GetPosition(), verts[tr].GetPosition(), verts[br].GetPosition());

				::Render(t1, true);
				::Render(t2, true);
			}
		}
		#endif
	}
}

void RigidbodyVolume::Refresh(GfxDataState& s) {
	SynchCollisionVolumes();

	if (type == RIGIDBODY_TYPE_SPHERE) {
		sphere.Refresh(s);
	}
	else if (type == RIGIDBODY_TYPE_BOX) {
		if (s.dbg_render) {
			box.Refresh(s);
		}
		else {
			GetEdges(box, edges);
			RefreshEdges(s);
		}
	}
}

void RigidbodyVolume::RefreshEdges(GfxDataState& s) {
	glBegin(GL_LINES);
	for (int i = 0; i < edges.GetCount(); ++i) {
		vec3 p1 = edges[i].start;
		vec3 p2 = edges[i].end;
		glVertex3f(p1[0], p1[1], p1[2]);
		glVertex3f(p2[0], p2[1], p2[2]);
	}
	glEnd();
}

void Spring::Refresh(GfxDataState& s) {
	if (p1 == 0 || p2 == 0) {
		// if gfxobj, free gfxobj
	}
	else {
		l.Refresh(s);
	}
	
}

void DistanceJoint::Refresh(GfxDataState& s) {
	#if 0
	vec3 pos1 = p1->GetPosition();
	vec3 pos2 = p2->GetPosition();
	Line l(pos1, pos2);
	::Render(l);
	#endif
}

void Particle::Refresh(GfxDataState& s) {
	vis.position = position,
	vis.radius = 0.1f;
	vis.Refresh(s);
}

void CollisionManifold::Refresh(GfxDataState& s) {
	if (!colliding) {
		return;
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (auto& c : contacts) {
		glVertex3f(c[0], c[1], c[2]);
	}
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	vec3 center = vec3();
	for (const vec3& start : contacts) {
		vec3 end = start + normal * depth;
		center = center + start;

		glVertex3fv(start.data);
		glVertex3fv(end.data);
	}
	glEnd();

	if (contacts.GetCount() == 0) {
		return;
	}
	float denom = 1.0f / (float)contacts.GetCount();
	center = center * denom;

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	vec3 start = center;
	vec3 end = center + normal;

	glVertex3fv(start.data);
	glVertex3fv(end.data);
	glEnd();

}

}
NAMESPACE_TOPSIDE_END
