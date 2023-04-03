#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


OctreePointModel::OctreePointModel() {
	
}




WmrMotionControllerModel::WmrMotionControllerModel() {
	InitDefault();
}

void WmrMotionControllerModel::InitDefault() {
	
	// Measured by hand (might be errors)
	outer_rad = 0.118f * 0.5f; // diameter 11.8cm
	inner_rad = 0.097f * 0.5f; // diameter 9.7cm
	outer_inner_edge_distance = 0.028f; // distance from edge of the circle to another circle
	
	// Distance between circles (x = ?)
	float y = outer_rad - inner_rad;
	float hypo = outer_inner_edge_distance;
	float x = sqrt(hypo * hypo - y * y);
	z_axis_dist = x;
	angle = atan2f(y, x);
	
	
	// x should probably be 2.6cm, but let's use calculated anyway
	
	
	
	// Outer side points (positive is top-left, CCW, from user's center point of view)
	Vector<Point> outer;
	outer	<< Point(0,20)
			<< Point(16,4)
			<< Point(22,10)
			<< Point(25,14)
			<< Point(25,3)
			<< Point(16,20)
			<< Point(17,3)
			<< Point(17,20)
			<< Point(20,8)
			<< Point(24,12)
			<< Point(22,3)
			<< Point(18,18)
			<< Point(20,3)
			<< Point(17,20)
			<< Point(16,3)
			<< Point(16,20)
			<< Point(25,9)
			<< Point(23,3)
			<< Point(16,20);
	
	float outer_x_sum = 0;
	for (Point& pt : outer) {outer_x_sum += pt.x;}
	outer_pts.SetCount(0);
	float outer_roll = 0, outer_hypo_sum = 0;
	for(int i = 0; i < outer.GetCount()-1; i++)
		AddPoint(outer[i], outer_x_sum, +1, outer_roll, 0, outer_hypo_sum, outer_pts);
	
	
	
	// Inner side points (positive is top-left, CCW, from user's center point of view)
	Vector<Point> inner;
	inner	<< Point(0,7)
			<< Point(25,8)
			<< Point(24,7)
			<< Point(24,20)
			<< Point(19,7)
			<< Point(23,6)
			<< Point(21,17)
			<< Point(24,14)
			<< Point(22,6)
			<< Point(18,22)
			<< Point(20,8)
			<< Point(22,18)
			<< Point(21,5)
			<< Point(20,19)
			<< Point(20,7);
	
	float inner_x_sum = 0;
	for (Point& pt : inner) {inner_x_sum += pt.x;}
	inner_pts.SetCount(0);
	float inner_roll = 0, inner_hypo_sum = 0;
	for(int i = 0; i < inner.GetCount()-1; i++)
		AddPoint(inner[i], inner_x_sum, -1, inner_roll, -0.004f, inner_hypo_sum, inner_pts);
	
	
	
	DUMPC(outer_pts);
	DUMPC(inner_pts);
}

void WmrMotionControllerModel::AddPoint(const Point& pt, float x_sum, float roll_mul, float& roll, float rad_diff, float& hypo_sum, Vector<vec3>& vec) {
	float roll_ratio = pt.x / x_sum;
	float roll_change = M_PIf*2 * roll_ratio * roll_mul;
	roll += roll_change;
	ASSERT(roll < M_PI*2 || IsClose(roll, M_PI*2));
	
	float hypo = outer_inner_edge_distance - pt.y * 0.001f;
	float y = sin(angle) * hypo;
	float x = cos(angle) * hypo;
	float rad = inner_rad + y + rad_diff;
	ASSERT(x < z_axis_dist && x >= 0);
	
	// origo is the "writing point" of the controller, and points are inwards from that
	vec3 ctrl_pt;
	ctrl_pt[0] = 0;
	ctrl_pt[1] = rad;
	ctrl_pt[2] = (z_axis_dist - x) * -SCALAR_FWD_Zf;
	
	ctrl_pt = VecMul(ZRotation(roll), ctrl_pt);
	
	vec.Add(ctrl_pt);
}



NAMESPACE_TOPSIDE_END
