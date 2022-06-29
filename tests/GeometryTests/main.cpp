#include <Geometry/Geometry.h>
using namespace TS;


bool IsClose(const quat& a, const quat& b) {
	float sum = 0;
	for(int i = 0; i < 4; i++)
		sum += fabsf(a[i] - b[i]);
	return sum < 0.001;
}

bool IsClose(const vec3& a, const vec3& b) {
	float dist = (a - b).GetLength();
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

CONSOLE_APP_MAIN {
	SetCoutLog();
	
	
	// This is +z == forward matrix math.
	// Most other solutions use -z (probably because of compass angles)
	// +z math is more consistent and intuitive outside of geographical compass angles topics.
	// It's really matter of choice, and I couldn't find mathematical reasons, when I searched.
	// I prefer to built everything around forward==vec3(0,0,1) vector, because it's a lot
	// faster and intuitive for me to think.
	// I will change to -z, if there's any compelling mathematical reason for it.
	
	// Historical reason for -z math might be that +x is towards right and people want to think that
	// turning right is positive angle too (which affects compass clockwise direction, and
	// which forces -z math).
	
	// Another positive feature in +z math is that both top-down (xz) angles
	// and forward (xy) angles are counter-clockwise.
	// Only negative thing in +z math is that positive horizontal angle is left and not right.
	// I think that pros outweight cons easily.
	
	{
		vec3 fwd_vec(0,0,1);
		mat4 fwd_mat = Translate(fwd_vec);
		
		vec3 fwd_vec2 = Position(fwd_mat);
		DUMP(fwd_vec2);
		ASSERT(fwd_vec == fwd_vec2);
		
		float fwd_yaw = 0;
		float fwd_pitch = 0;
		vec3 fwd_vec3 = AxesDir(fwd_yaw, fwd_pitch);
		DUMP(fwd_vec3);
		ASSERT(IsClose(fwd_vec3, fwd_vec));
	}
	
	{
		vec3 left_vec(-1,0,0);
		DUMP(left_vec);
		float left_yaw = +M_PI / 2;
		float left_pitch = 0;
		vec3 left_vec2 = AxesDir(left_yaw, left_pitch);
		DUMP(left_vec2);
		ASSERT(IsClose(left_vec2, left_vec));
		float left_yaw2, left_pitch2;
		DirAxes(left_vec, left_yaw2, left_pitch2);
		ASSERT(IsClose(left_yaw, left_yaw2));
		ASSERT(IsClose(left_pitch, left_pitch2));
	}
	
	{
		vec3 right_vec(+1,0,0);
		DUMP(right_vec);
		float right_yaw = -M_PI / 2;
		float right_pitch = 0;
		vec3 right_vec2 = AxesDir(right_yaw, right_pitch);
		DUMP(right_vec2);
		ASSERT(IsClose(right_vec2, right_vec));
		float right_yaw2, right_pitch2;
		DirAxes(right_vec, right_yaw2, right_pitch2);
		ASSERT(IsClose(right_yaw, right_yaw2));
		ASSERT(IsClose(right_pitch, right_pitch2));
	}
	
	{
		vec3 fwdup_vec = AxesDir(0, +M_PI / 4);
		ASSERT(fwdup_vec[1] > 0);
		float fwdup_yaw, fwdup_pitch;
		DirAxes(fwdup_vec, fwdup_yaw, fwdup_pitch);
		ASSERT(fwdup_pitch > 0);
		ASSERT(IsClose(fwdup_yaw, 0));
		ASSERT(AxesDir(0, -M_PI / 4)[1] < 0);
		ASSERT(AxesDir(0, 0)[2] > 0);
		ASSERT(AxesDir(M_PI, 0)[2] < 0);
	}
	
	
	// quat -> mat4: QuatMat
	if (1) {
		mat4 rot0 = QuatMat(AxisAngleQuat(vec3(0,1,0), +M_PI / 2));
		vec3 l0 = (vec4(0,0,1,1) * rot0).Splice();
		vec3 l1(-1,0,0);
		DUMP(l0);
		DUMP(l1);
		ASSERT(IsClose(l0, l1));
		mat4 rot1 = QuatMat(AxisAngleQuat(vec3(1,0,0), +M_PI / 2));
		vec3 u0 = (vec4(0,0,1,1) * rot1).Splice();
		vec3 u1(0,1,0);
		ASSERT(IsClose(u0, u1));
		mat4 rot2 = QuatMat(AxisAngleQuat(vec3(0,0,1), +M_PI / 2));
		/*DUMP(rot2);
		mat4 rot3 = QuatMat(AxisAngleQuat(vec3(0,0,1), -M_PI / 2));
		DUMP(rot3);*/
		vec3 l2 = (vec4(0,1,0,1) * rot2).Splice();
		DUMP(l2);
		ASSERT(IsClose(l0, l2));
	}
	
	// Decompose
	if (1) {
		vec3 scale0(1,2,3), scale1;
		quat orient0 = AxesQuat(M_PI/4,M_PI/4,M_PI/4), orient1;
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
			ASSERT(IsClose(orient0, orient1));
		}
		{
			mat4 m = Translate(trans0);
			Decompose(m, scale1, orient1, trans1, skew1, persp);
			ASSERT(IsClose(trans0, trans1));
		}
	}
	
	
	// AxisAngleQuat
	{
		float y, p, r;
		quat l = AxisAngleQuat(vec3(0,1,0), M_PI / 2);
		QuatAxes(l, y, p, r);
		ASSERT(IsClose(y, M_PI / 2) && p == 0 && r == 0);
		l = AxisAngleQuat(vec3(1,0,0), M_PI / 4);
		QuatAxes(l, y, p, r);
		ASSERT(IsClose(p, M_PI / 4) && y == 0 && r == 0);
		l = AxisAngleQuat(vec3(0,0,1), M_PI / 4);
		QuatAxes(l, y, p, r);
		ASSERT(IsClose(r, M_PI / 4) && y == 0 && p == 0);
	}
	
	// transform
	if (1) {
		vec3 l0 = Transform(vec3(0,0,1), AxisAngleQuat(vec3(0,1,0), M_PI / 2));
		vec3 l1(-1,0,0);
		ASSERT(IsClose(l0, l1));
	}
	
	// axes -> quat: AxesQuat
	{
		mat4 rot0 = QuatMat(AxesQuat(M_PI/2,0,0));
		vec3 l0 = (vec4(0,0,1,1) * rot0).Splice();
		vec3 l1(-1,0,0);
		ASSERT(IsClose(l0, l1));
		mat4 rot1 = QuatMat(AxesQuat(0,M_PI/2,0));
		vec3 u0 = (vec4(0,0,1,1) * rot1).Splice();
		vec3 u1(0,1,0);
		ASSERT(IsClose(u0, u1));
		mat4 rot2 = QuatMat(AxesQuat(0,0,M_PI/2));
		vec3 l2 = (vec4(0,1,0,1) * rot2).Splice();
		ASSERT(IsClose(l0, l2));
	}
	
	// Rotations
	{
		mat4 m0 = XRotation(+M_PI / 2);
		mat4 m1 = QuatMat(AxisAngleQuat(vec3(1,0,0), +M_PI / 2));
		ASSERT(IsClose(m0, m1));
		m0 = YRotation(+M_PI / 2);
		m1 = QuatMat(AxisAngleQuat(vec3(0,1,0), +M_PI / 2));
		ASSERT(IsClose(m0, m1));
		m0 = ZRotation(+M_PI / 2);
		m1 = QuatMat(AxisAngleQuat(vec3(0,0,1), +M_PI / 2));
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
		quat q0 = AxesQuat(M_PI/2,0,0); // already checked
		float yaw, pitch, roll;
		QuatAxes(q0, yaw, pitch, roll);
		ASSERT(IsClose(yaw, M_PI/2) && pitch == 0 && roll == 0);
		q0 = AxesQuat(0,M_PI/2,0); // already checked
		QuatAxes(q0, yaw, pitch, roll);
		ASSERT(IsClose(pitch, M_PI/2));
		q0 = AxesQuat(0,0,M_PI/2); // already checked
		QuatAxes(q0, yaw, pitch, roll);
		ASSERT(IsClose(roll, M_PI/2));
	}
	
	// CameraObject
	{
		vec3 eye(0,0,0);
		vec3 eye_dir(0,0,1);
		vec3 up(0,1,0);
		vec3 v0;
		CameraObject(
			eye, eye_dir, up,
			M_PI/2, 0, 1,
			v0);
		vec3 v1(-1,0,0);
		ASSERT(IsClose(v0, v1));
		CameraObject(
			eye, eye_dir, up,
			0, M_PI/4, 1,
			v0);
		float per_axis = sqrt(2)/2;
		v1 = vec3(0,per_axis,per_axis);
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
	{
		quat q0 = AxisAngleQuat(vec3(0,1,0), +M_PI / 2);
		mat4 rot0 = QuatMat(q0);
		quat q1 = MatQuat(rot0);
		DUMP(q0);
		DUMP(q1);
		ASSERT(IsClose(q0, q1));
	}
	
	// GetEulerAngleYXZ
	// NOTE the inverse axis order
	{
		float yaw = M_PI/2, pitch = M_PI/4, roll = M_PI/2;
		vec3 axes0(yaw, pitch, roll);
		vec3 yxz(roll, pitch, yaw);
		mat4 m0 = AxesMat(yaw, pitch, roll);
		mat4 m1 = GetEulerAngleYXZ(yxz);
		vec3 axes1;
		MatAxes(m1, axes1);
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
			vec3 tgt(0,0,1);
			vec3 up(0,1,0);
			mat4 m0 = Identity<mat4>();
			mat4 m1 = LookAt(eye, tgt, up);
			DUMP(m1);
			ASSERT(IsClose(m0, m1));
		}
		{
			vec3 eye(0,0,0);
			vec3 tgt(1,0,0);
			vec3 up(0,1,0);
			mat4 m0 = AxesMat(-M_PI/2,0,0);
			mat4 m1 = LookAt(eye, tgt, up);
			DUMP(m0);
			DUMP(m1);
			ASSERT(IsClose(m0, m1));
		}
		{
			vec3 eye(0,0,0);
			vec3 tgt(0,1,1);
			vec3 up(0,1,0);
			tgt.Normalize();
			mat4 m0 = AxesMat(0,M_PI/4,0);
			mat4 m1 = LookAt(eye, tgt, up);
			DUMP(m0);
			DUMP(m1);
			ASSERT(IsClose(m0, m1));
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
	
	LOG("Tests passed!");
}
