#include <Geometry/Geometry.h>
using namespace TS;


bool MatCompareTest(const mat4& m0, const mat4& m1, bool succ_result=true) {
	bool succ = true;
	for(int i = 0; i < 6; i++) {
		vec3 v;
		switch(i) {
			case 0: v = vec3(0,0,+1); break;
			case 1: v = vec3(0,0,-1); break;
			case 2: v = vec3(0,+1,0); break;
			case 3: v = vec3(0,-1,0); break;
			case 4: v = vec3(+1,0,0); break;
			case 5: v = vec3(-1,0,0); break;
		}
		
		vec4 v0 = v.Embed() * m0;
		vec4 v1 = v.Embed() * m1;
		if (!IsClose(v0,v1)) {
			succ = false;
			if (succ != succ_result) {
				DUMP(v);
				DUMP(v0);
				DUMP(v1);
				DUMP(m0);
				DUMP(m1);
			}
			break;
		}
	}
	return succ;
}


void glm_test();



CONSOLE_APP_MAIN {
	SetCoutLog();
	
	glm_test();
	
	// quat -> mat4: QuatMat
	if (1) {
		mat4 rot0 = QuatMat(AxisAngleQuat(VEC_Y, +A_PI / 2));
		vec3 l0 = (VEC_FWD4 * rot0).Splice();
		vec3 l1 = VEC_LEFT;
		DUMP(l0);
		DUMP(l1);
		ASSERT(IsClose(l0, l1));
		mat4 rot1 = QuatMat(AxisAngleQuat(VEC_X, +A_PI / 2));
		vec3 u0 = (VEC_FWD4 * rot1).Splice();
		vec3 u1 = VEC_UP;
		DUMP(u0);
		DUMP(u1);
		ASSERT(IsClose(u0, u1));
		mat4 rot2 = QuatMat(AxisAngleQuat(VEC_Z, +A_PI / 2));
		vec3 l2 = (VEC_UP4 * rot2).Splice();
		DUMP(l2);
		ASSERT(IsClose(l0, l2));
	}
	
	{
		vec3 v0 = VEC_FWD;
		mat4 fwd_mat = Translate(v0);
		
		vec3 v1 = Position(fwd_mat);
		DUMP(v1);
		ASSERT(v0 == v1);
		
		float yaw = 0;
		float pitch = 0;
		vec3 v2 = AxesDir(yaw, pitch);
		DUMP(v2);
		ASSERT(IsClose(v2, v0));
		
		yaw = -A_PI/2;
		vec3 v3 = VEC_RIGHT;
		vec3 v4 = AxesDir(yaw, pitch);
		DUMP(v3);
		DUMP(v4);
		ASSERT(IsClose(v3, v4));
	}
	
	{
		{
			vec3 left_vec(-1,0,0);
			DUMP(left_vec);
			float left_yaw = +A_PI / 2;
			float left_pitch = 0;
			vec3 left_vec2 = AxesDir(left_yaw, left_pitch);
			DUMP(left_vec2);
			ASSERT(IsClose(left_vec2, left_vec));
			float left_yaw2, left_pitch2;
			DirAxes(left_vec, left_yaw2, left_pitch2);
			DUMP(left_yaw2);
			//ASSERT(IsClose(left_yaw, left_yaw2));
			//ASSERT(IsClose(left_pitch, left_pitch2));
		}
		
		{
			vec3 right_vec(+1,0,0);
			DUMP(right_vec);
			float right_yaw = -A_PI / 2;
			float right_pitch = 0;
			vec3 right_vec2 = AxesDir(right_yaw, right_pitch);
			DUMP(right_vec2);
			ASSERT(IsClose(right_vec2, right_vec));
			float right_yaw2, right_pitch2;
			DirAxes(right_vec, right_yaw2, right_pitch2);
			DUMP(right_yaw2);
			//ASSERT(IsClose(right_yaw, right_yaw2));
			//ASSERT(IsClose(right_pitch, right_pitch2));
		}
		
		// forward
		{
			vec3 v0 = AxesDir(0, 0);
			float yaw, pitch;
			DirAxes(v0, yaw, pitch);
			DUMP(yaw);
			ASSERT(IsClose(yaw, 0));
		}
		
		
		// backward
		{
			vec3 v0 = AxesDir(A_PI, 0);
			float yaw, pitch;
			DirAxes(v0, yaw, pitch);
			DUMP(yaw);
			ASSERT(IsClose(fmodf(A_PI*2 + yaw, A_PI*2), A_PI));
		}
		
		{
			vec3 fwdup_vec = AxesDir(0, +M_PI / 4);
			ASSERT(fwdup_vec[1] > 0);
			float fwdup_yaw, fwdup_pitch;
			DirAxes(fwdup_vec, fwdup_yaw, fwdup_pitch);
			ASSERT(fwdup_pitch > 0);
			ASSERT(IsClose(fwdup_yaw, 0));
			ASSERT(AxesDir(0, -M_PI / 4)[1] < 0);
		}
	}
	
	
	// Decompose
	#if 2
	{
		// Decompose is probably too broken still, even though this passes
		vec3 scale0(1,2,3), scale1;
		quat orient0 = AxesQuat(A_PI/4,A_PI/4,A_PI/4), orient1;
		vec3 trans0(2,3,4), trans1;
		vec3 skew1;
		vec4 persp;
		{
			mat4 m = Scale(scale0);
			Decompose(m, scale1, orient1, trans1, skew1, persp);
			ASSERT(IsClose(scale0, scale1));
		}
		{
			mat4 m = QuatMat(orient0);
			Decompose(m, scale1, orient1, trans1, skew1, persp);
			DUMP(orient0);
			DUMP(orient1);
			ASSERT(IsClose(orient0, orient1));
		}
		{
			mat4 m = Translate(trans0);
			Decompose(m, scale1, orient1, trans1, skew1, persp);
			ASSERT(IsClose(trans0, trans1));
		}
	}
	#endif
	
	
	// AxisAngleQuat
	{
		float y, p, r;
		quat l = AxisAngleQuat(VEC_Y, A_PI / 2);
		QuatAxes(l, y, p, r);
		ASSERT(IsClose(y, A_PI / 2) && p == 0 && r == 0);
		l = AxisAngleQuat(VEC_X, A_PI / 4);
		QuatAxes(l, y, p, r);
		ASSERT(IsClose(p, A_PI / 4) && y == 0 && r == 0);
		l = AxisAngleQuat(VEC_Z, A_PI / 4);
		QuatAxes(l, y, p, r);
		ASSERT(IsClose(r, A_PI / 4) && y == 0 && p == 0);
	}
	
	// transform
	if (1) {
		vec3 l0 = VectorTransform(VEC_FWD, AxisAngleQuat(vec3(0,1,0), A_PI / 2));
		vec3 l1 = VEC_LEFT;
		ASSERT(IsClose(l0, l1));
	}
	
	// axes -> quat: AxesQuat
	{
		mat4 rot0 = QuatMat(AxesQuat(A_PI/2,0,0));
		vec3 l0 = (VEC_FWD4 * rot0).Splice();
		vec3 l1 = VEC_LEFT;
		ASSERT(IsClose(l0, l1));
		mat4 rot1 = QuatMat(AxesQuat(0,A_PI/2,0));
		vec3 u0 = (VEC_FWD4 * rot1).Splice();
		vec3 u1 = VEC_UP;
		ASSERT(IsClose(u0, u1));
		mat4 rot2 = QuatMat(AxesQuat(0,0,A_PI/2));
		vec3 l2 = (VEC_UP4 * rot2).Splice();
		DUMP(l0);
		DUMP(l2);
		ASSERT(IsClose(l0, l2));
	}
	
	// Rotations
	{
		mat4 m0 = XRotation(+A_PI / 2);
		mat4 m1 = QuatMat(AxisAngleQuat(VEC_X, +A_PI / 2));
		ASSERT(IsClose(m0, m1));
		m0 = YRotation(+A_PI / 2);
		m1 = QuatMat(AxisAngleQuat(VEC_Y, +A_PI / 2));
		ASSERT(IsClose(m0, m1));
		m0 = ZRotation(+A_PI / 2);
		m1 = QuatMat(AxisAngleQuat(VEC_Z, +A_PI / 2));
		ASSERT(IsClose(m0, m1));
	}
	
	// Identity matrix
	{
		mat4 m0 {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
		ASSERT(m0.data[0].data[0] == 1);
		ASSERT(m0.data[3].data[3] == 1);
		mat4 m1 = Identity<mat4>();
		ASSERT(m0 == m1);
		mat4 m2 = Scale(vec3(1,1,1));
		ASSERT(m2 == m0);
		mat4 m3 = Translate(vec3(0,0,0));
		ASSERT(m3 == m0);
	}
	
	// ypr -> mat4
	{
		// pass (proxy functino)
	}
	
	// quat -> ypr
	{
		quat q0 = AxesQuat(A_PI/2,0,0); // already checked
		float yaw, pitch, roll;
		QuatAxes(q0, yaw, pitch, roll);
		ASSERT(IsClose(yaw, A_PI/2) && pitch == 0 && roll == 0);
		q0 = AxesQuat(0,A_PI/2,0); // already checked
		QuatAxes(q0, yaw, pitch, roll);
		ASSERT(IsClose(pitch, A_PI/2));
		q0 = AxesQuat(0,0,A_PI/2); // already checked
		QuatAxes(q0, yaw, pitch, roll);
		ASSERT(IsClose(roll, A_PI/2));
	}
	
	// CameraObject
	{
		vec3 eye(0,0,0);
		vec3 eye_dir = VEC_FWD;
		vec3 up = VEC_UP;
		vec3 v0;
		CameraObject(
			eye, eye_dir, up,
			A_PI/2, 0, 1,
			v0);
		vec3 v1 = VEC_LEFT;
		ASSERT(IsClose(v0, v1));
		CameraObject(
			eye, eye_dir, up,
			0, M_PI/4, 1,
			v0);
		float per_axis = sqrt(2)/2;
		v1 = (VEC_UP + VEC_FWD) * per_axis;
		DUMP(v0);
		DUMP(v1);
		ASSERT(IsClose(v0, v1));
	}
	
	// Inverse, FastInverse (very basic)
	{
		// from https://www.mathsisfun.com/algebra/matrix-inverse.html
		// A group took a trip on a bus, at $3 per child and $3,20 per adult for a total of $118,40.
		// They took the train back at $3,50 per child and $3,60 per adult for a total of $135,20.
		// How many children, and how many adults?
		mat4 fare = Identity<mat4>();
		fare[0][0] = 3.0;
		fare[1][0] = 3.2;
		fare[0][1] = 3.5;
		fare[1][1] = 3.6;
		vec4 total{118.4f, 135.2f, 0.f, 0.f};
		mat4 fare_inv0 = Identity<mat4>();
		fare_inv0[0][0] = -9;
		fare_inv0[0][1] = 8.75;
		fare_inv0[1][0] = 8;
		fare_inv0[1][1] = -7.5;
		mat4 fare_inv1 = fare.GetInverse();
		mat4 fare_inv2 = FastInverse(fare);
		DUMP(fare_inv1);
		DUMP(fare_inv2);
		mat3 fare1 = fare.Splice();
		mat2 fare2 = fare.Splice<0,2,2>();
		DUMP(fare1);
		DUMP(fare2);
		mat4 fare_inv3 = FastInverse(fare1).Embed();
		mat4 fare_inv4 = FastInverse(fare2).Embed().Embed();
		DUMP(fare_inv3);
		DUMP(fare_inv4);
		ASSERT(IsClose(fare_inv0, fare_inv1));
		ASSERT(IsClose(fare_inv0, fare_inv2));
		ASSERT(IsClose(fare_inv0, fare_inv3));
		ASSERT(IsClose(fare_inv0, fare_inv4));
	}
	
	// Inverse, FastInverse
	{
		mat4 m0{
			{1,3,5,9},
			{1,3,1,7},
			{4,3,9,7},
			{5,2,0,9}};
		float det = m0.GetDeterminant();
		ASSERT(IsClose(det, -376));
		mat4 m1 = m0.GetInverse();
		mat4 m2 = FastInverse(m0);
		DUMP(m0);
		DUMP(m1);
		DUMP(m2);
		ASSERT(IsClose(m1, m2));
	}
		
	// mat4 -> quat
	#if 0
	{
		// Passes, but probably very wrong with other angles
		quat q0 = AxisAngleQuat(vec3(0,1,0), +A_PI / 2);
		mat4 rot0 = QuatMat(q0);
		quat q1 = MatQuat(rot0);
		DUMP(q0);
		DUMP(q1);
		ASSERT(IsClose(q0, q1));
	}
	#endif
	
	// GetEulerAngleYXZ
	// NOTE the inverse axis order
	{
		float yaw = A_PI/2, pitch = A_PI/4, roll = A_PI/2;
		vec3 axes0(yaw, pitch, roll);
		vec3 yxz(roll, pitch, yaw);
		mat4 m0 = AxesMat(yaw, pitch, roll);
		mat4 m1 = GetEulerAngleYXZ(yxz);
		ASSERT(IsClose(m0, m1));
		vec3 yx(0, pitch, yaw);
		mat4 m2 = AxesMat(yaw, pitch, 0);
		mat4 m3 = GetEulerAngleYXZ(yx);
		ASSERT(IsClose(m2, m3));
	}
	
	// LookAt
	{
		{
			vec3 eye(0,0,0);
			vec3 tgt = VEC_FWD;
			vec3 up = VEC_UP;
			mat4 m0 = AxesMat(0,0,0);
			mat4 m1 = LookAt(eye, tgt, up);
			ASSERT(MatCompareTest(m0, m1));
		}
		{
			vec3 eye(0,0,0);
			vec3 tgt = VEC_BWD;
			vec3 up = VEC_UP;
			mat4 m0 = AxesMat(A_PI,0,0);
			mat4 m1 = LookAt(eye, tgt, up);
			ASSERT(MatCompareTest(m0, m1));
		}
		{
			vec3 eye(0,0,0);
			vec3 tgt = VEC_RIGHT;
			vec3 up = VEC_UP;
			mat4 m0 = AxesMat(-A_PI/2,0,0);
			mat4 m1 = LookAt(eye, tgt, up);
			ASSERT(!MatCompareTest(m0, m1, false)); // should fail
		}
		{
			vec3 eye(0,0,0);
			vec3 tgt = VEC_FWD + VEC_UP;
			vec3 up = VEC_UP;
			tgt.Normalize();
			mat4 m0 = AxesMat(0,A_PI/4,0);
			mat4 m1 = LookAt(eye, tgt, up);
			ASSERT(!MatCompareTest(m0, m1, false)); // should fail
		}
		{
			vec3 eye(0,0,0);
			vec3 tgt = VEC_FWD;
			vec3 up = VEC_DOWN;
			mat4 m0 = AxesMat(0,0,A_PI);
			mat4 m1 = LookAt(eye, tgt, up);
			ASSERT(MatCompareTest(m0, m1));
		}
	}
	
	if (0) {
		mat4 m0 = GetViewport(-640, -480, 640, 480, 2);
		mat4 im0 = m0.GetInverse();
		DUMP(vec4(0,0,0,1) * im0);
		DUMP(im0 * vec4(640,0,0,1));
		DUMP(im0 * vec4(640,480,0,1));
		DUMP(im0 * vec4(0,480,0,1));
	}
	
	#if 0
	{
		vec3 scale0(1,2,3), scale1;
		quat orient0 = AxesQuat(A_PI/4,A_PI/4,A_PI/4), orient1;
		vec3 trans0(2,3,4), trans1;
		vec3 skew1;
		vec4 persp;
		{
			//mat4 m0 = Translate(trans0) * Scale(scale0) * QuatMat(orient0) * Perspective(DEG2RAD(45), 1.33, 0.1, 1.0);
			mat4 m0{
			{1,3,5,9},
			{1,3,1,7},
			{4,3,9,7},
			{5,2,0,9}};
			Decompose(m0, scale1, orient1, trans1, skew1, persp);
			mat4 m1 = Recompose(scale1, orient1, trans1, skew1, persp);
			DUMP(m0);
			DUMP(m1);
			Decompose(m1, scale1, orient1, trans1, skew1, persp);
			mat4 m2 = Recompose(scale1, orient1, trans1, skew1, persp);
			DUMP(m2);
			ASSERT(IsClose(m1, m2));
		}
	}
	#endif
	
	LOG("Tests passed!");
}
