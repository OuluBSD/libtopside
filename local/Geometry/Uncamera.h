#ifndef _Geometry_Uncamera_h_
#define _Geometry_Uncamera_h_

NAMESPACE_TOPSIDE_BEGIN


class Uncamera {
	
	
};


class VirtualStereoUncamera : public Uncamera, public LensPoly {
	float eye_dist = 0.068f;
	
	// temp
	Vector<Vector<const Descriptor*>> l_desc, r_desc;
	
	
	
	
public:
	typedef VirtualStereoUncamera CLASSNAME;
	VirtualStereoUncamera();
	
	void SetEyeDistance(float f) {eye_dist = f;}
	
	void Unrender(const DescriptorImage& l_img, const DescriptorImage& r_img, Octree& o);
	
};




NAMESPACE_TOPSIDE_END

#endif
