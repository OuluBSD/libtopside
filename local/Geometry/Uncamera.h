#ifndef _Geometry_Uncamera_h_
#define _Geometry_Uncamera_h_

NAMESPACE_TOPSIDE_BEGIN


class Uncamera {
	
protected:
	quat orientation;
	
public:
	Uncamera();
	
};


class VirtualStereoUncamera : public Uncamera, public LensPoly {
	
	struct TrackedPoint : Moveable<TrackedPoint> {
		uint32 descriptor[DESCRIPTOR_UINTS];
		OctreeDescriptorPoint* dp;
	};
	
	int distance_limit = 100; // limit for different bits in 32byte desriptor (compared to popcount)
	float eye_dist = 0.068f;
	float error_factor = 0.25; // error_factor is multiplier for the distance, what is searched
	
	
	// temp
	Vector<Vector<const Descriptor*>> l_desc, r_desc;
	Vector<TrackedPoint> tracked_points;
	
	
	
public:
	typedef VirtualStereoUncamera CLASSNAME;
	VirtualStereoUncamera();
	
	void SetEyeDistance(float f) {eye_dist = f;}
	
	void Unrender(const DescriptorImage& l_img, const DescriptorImage& r_img, Octree& o);
	
};




NAMESPACE_TOPSIDE_END

#endif
