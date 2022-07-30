#ifndef _Geometry_Pointcloud_h_
#define _Geometry_Pointcloud_h_

NAMESPACE_TOPSIDE_BEGIN


class OctreePointModel {
	
	
public:
	typedef OctreePointModel CLASSNAME;
	OctreePointModel();
	
	
	
	Octree octree;
	
};





class WmrMotionControllerModel : public OctreePointModel {
	float outer_rad;
	float inner_rad;
	float outer_inner_edge_distance;
	float z_axis_dist;
	float angle;
	Vector<vec3> outer_pts;
	Vector<vec3> inner_pts;
	
	void AddPoint(const Point& pt, float x_sum, float roll_mul, float& roll, float rad_diff, float& hypo_sum, Vector<vec3>& vec);
	
public:
	typedef WmrMotionControllerModel CLASSNAME;
	WmrMotionControllerModel();
	
	void InitDefault();
	
};


NAMESPACE_TOPSIDE_END

#endif
