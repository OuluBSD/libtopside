#include "Geometry2.h"


Geometry2::Geometry2() {
	
}

Geometry2::~Geometry2() {
	
}

void Geometry2::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Geometry2::Render(Draw& draw) {
	draw.DrawRect(draw.GetPageSize(), Black());
	
	DrawGeometry fb(draw);

	Color white {255, 255, 255};
	Color red {255, 0, 0};
	Color green {0, 255, 0};
	Color blue {0, 0, 255};
	Color orange {255, 128, 0};
	Color yellow {255, 255, 0};
	Color pink {255, 42, 150};
	Color purple {170, 42, 150};
	Color lt_blue {28, 255, 255};
	
	float phase_f = (float)ts.Elapsed() / (float)phase_ms;
	float f = prev_phase_f + phase_f * 1.0;
	float f2 = f * 2.0;
	float f4 = f * 4.0;
	float x = cos(f * M_2PI);
	float y = sin(f * M_2PI);
	float x2 = cos(f2 * M_2PI);
	float y2 = sin(f2 * M_2PI);
	float z = (1 + y) * 0.5;
	float drawscale = 100;
	
	
	// Matrices... (not visual)
	static int times;
	if (times++ == 0) {
		mat3 A, B, C;
		mat23 m23;
		mat32 m32;
		do { for(int r = 0; r < 3; r++) for(int c = 0; c < 3; c++) A[r][c] = 1 + Random(10); } while (A.GetDeterminant() == 0);
		do { for(int r = 0; r < 3; r++) for(int c = 0; c < 3; c++) B[r][c] = 1 + Random(10); } while (B.GetDeterminant() == 0);
		do { for(int r = 0; r < 3; r++) for(int c = 0; c < 3; c++) C[r][c] = 1 + Random(10); } while (C.GetDeterminant() == 0);
		for(int r = 0; r < 2; r++) for(int c = 0; c < 3; c++) m23[r][c] = 1 + Random(10);
		for(int r = 0; r < 3; r++) for(int c = 0; c < 2; c++) m32[r][c] = 1 + Random(10);
		
		
		// Multiplication
		// Identity matrix multiplication creates identity matrix:
		// [[1,0,0],		[[1,0,0],		[[1,0,0],
		//  [0,1,0],	*	 [0,1,0],	=	 [0,1,0],
		//  [0,0,1]]		 [0,0,1]]		 [0,0,1]]
		mat3 ident3;
		ident3.SetIdentity();
		ASSERT(ident3 * ident3 == ident3);
		// Matrix multiplication is not cumulative
		ASSERT(A * B != B * A);
		// ...but it's associative
		ASSERT(A * (B * C) == (A * B) * C);
		// It can create a larger or smaller matrix
		mat2 m2 = m23 * m32;
		mat3 m3 = m32 * m23;
		// Uncomment to see values:
		//    DUMP(m23); DUMP(m32); DUMP(m2); DUMP(m3);
		
		
		// The determinant of a matrix is the same as the determinant of its transpose
		ASSERT(A.GetDeterminant() == A.GetTransposed().GetDeterminant());
		
		// One interesting property of determinants is that the determinant of the inverse of a matrix is
		// the same as the inverse determinant of that matrix
		float a = 1.0 / A.GetDeterminant();
		float b = A.GetInverse().GetDeterminant();
		ASSERT(IsClose(a, b));
		
		// Minor matrix is just the source matrix, but the given row and col are excluded.
		mat2 Aminor = A.GetMinor(1, 1);
		//LOG("A = \n" << A.ToString() << "\nAminor = \n" << Aminor.ToString());
		ASSERT(A[0][0] == Aminor[0][0] && A[2][2] == Aminor[1][1]);
		
		// With inverse matrix, you can restore the original state
		// Multiplying a matrix by it's inverse should yield a identity matrix.
		mat3 B2 = B * B.GetInverse();
		ASSERT(B2.IsClose(Identity<mat3>()));
		mat3 A2 = (B.GetInverse() * (B * A));
		ASSERT(A2.IsClose(A));
		
	}
	
	
	// Matrix transformations
	if (phase < 4) {
		/*
		4x4 matrix is considered to have following components:
		(note: components can overlap)
			X = X rotation axis
			Y = Y rotation axis
			Z = Z rotation axis
			S = Scale vector
			P = Perspective
			T = Translation (moves the position)
			G = Global scale
		
		[[X S		X		X		P],
		 [Y			Y S		Y		P],
		 [Z			Z		Z S		P],
		 [T			T		T		G]]
		*/
		
		// Let's draw unit vector for reference as white. [1,1]
		// 4th column is 1 for positions and 0 for vectors.
		vec4 origo {0, 0, 0, 1};
		vec4 unit {1, 1, 0, 1};
		DrawLine(fb, drawscale, origo, unit, white);
		
		if (phase >= 0) {
			// Let's move the unit vector to position [2,0].
			// Draw it as yellow.
			// The "Project()" call divides the matrix with the global scale (G) value.
			// Matrix must be transposed for multiplying or the vector must be converted
			// to mat41.
			mat4 m = Identity<mat4>();
			m[3][0] = 2 * z;
			m[3][1] = 0;
			m.Transpose();
			vec4 origo2 = m * origo;
			vec4 unit2 = m * unit;
			DrawLine(fb, drawscale, origo2, unit2, yellow);
		}
		if (phase >= 1) {
			// Scale the vector and m to [2,2]
			mat4 m = Identity<mat4>();
			m[3][0] = 2;
			m[3][1] = 0 + 2 * z;
			m[0][0] = 1 + z;
			m[1][1] = 1 + z;
			m[2][2] = 1 + z;
			m.Transpose();
			vec4 origo2 = m * origo;
			vec4 unit2 = m * unit;
			DrawLine(fb, drawscale, origo2, unit2, yellow);
		}
		if (phase >= 2) {
			// Rotate, scale and mov
			// Rotation is around x axis.
			mat4 trans, scale, rot;
			trans.SetTranspose(2, 2 + 2*z, 0);
			scale.SetScale(2 - z);
			rot.SetRotation(0, f * M_2PI);
			mat4 m = (scale * rot * trans).Transpose();
			vec4 origo2 = m * origo;
			vec4 unit2 = m * unit;
			DrawLine(fb, drawscale, origo2, unit2, yellow);
		}
	}
	
	// Draw green grid in perspective
	if (phase >= 4) {
		int w = 800, h = 600;
		float aspect = (float)h / (float)w;
		float vert = 1;
		float horz = vert / aspect;
		
		// Set projection for the Draw function
		mat4 persp;
		persp.SetOrtographic(-horz, +horz, -vert, +vert, 4, -4);
		
		// The default area is between -1 and +1. Project it to 0 and +600.
		mat4 vport = GetViewport(0, 0, w, h, 255); // default
		
		// Use LookAt function to "move the camera"
		vec3 eye {x, 0, y};
		vec3 center {0, 0, 0};
		vec3 up {0, 1, 0};
		mat4 lookat = LookAt(eye, center, up);
		
		// The leftmost matrix is processed first for the line
		mat4 view = vport * persp * lookat;
		
		// Draw a grid of 5 vertical and horizontal lines.
		// The target area is between -1 and +2, so the width is 2.
		// Have extra space; use the divider of 10 instead of 5 (lines).
		int pad = 2;
		float step = 2.0 / 10;
		int grid = 5;
		
		// Horizontal lines
		for(int x = 0; x < grid; x++) {
			float xf = (pad + x) * step - 1;
			vec4 a {xf, (pad) * step - 1, 0, 1};
			vec4 b {xf, (pad + (grid - 1)) * step - 1, 0, 1};
			a = (view * a).Project();
			b = (view * b).Project();
			DrawLine(fb, 1, a, b, green);
		}
		
		// Vertical lines
		for(int y = 0; y < grid; y++) {
			float yf = (pad + y) * step - 1;
			vec4 a {(pad) * step - 1, yf, 0, 1};
			vec4 b {(pad + (grid - 1)) * step - 1, yf, 0, 1};
			a = (view * a).Project();
			b = (view * b).Project();
			DrawLine(fb, 1, a, b, green);
		}
	}
	
	
	if (ts.Elapsed() > phase_ms) {
		ts.Reset();
		phase = (phase + 1) % phases;
		prev_phase_f = f;
	}
}

void Geometry2::DrawLine(DrawGeometry& fb, float scale, vec4 a, vec4 b, Color clr) {
	fb.DrawLine(a.Splice<0,2>() * scale, b.Splice<0,2>() * scale, 1, clr);
}


SIMPLE_ECS_APP_(Geometry2, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")
