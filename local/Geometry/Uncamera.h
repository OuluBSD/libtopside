#ifndef _Geometry_Uncamera_h_
#define _Geometry_Uncamera_h_

NAMESPACE_TOPSIDE_BEGIN


class Uncamera : public MeshTracker {
	
	
public:
	Uncamera();
	
};


class VirtualStereoUncamera : public Uncamera, public LensPoly {
	float eye_dist = 0.068f;
	float error_factor = 0.25; // error_factor is multiplier for the distance, what is searched
	int iter = 0;
	int y_levels = 0;
	int y_level_h = 10;
	
	// temp
	struct HorizontalMatch : Moveable<HorizontalMatch> {
		const Descriptor* l;
		const Descriptor* r;
		axes2s eyes;
		vec3 local_tgt;
		vec3 global_tgt;
	};
	Vector<Vector<const Descriptor*>> l_desc, r_desc;
	Vector<HorizontalMatch> horz_match;
	
	
	
	
	void InitializeLensPoly(const DescriptorImage& l_img, const DescriptorImage& r_img);
	void ResetTempVariables();
	void FindPreviousFrameMatches(const DescriptorImage& l_img, const DescriptorImage& r_img);
	void UpdateStereoTargets();
	void FindHorizontalMatches();
	void ProcessHorizontalMatches(Octree& o);
	
public:
	typedef VirtualStereoUncamera CLASSNAME;
	VirtualStereoUncamera();
	
	void SetEyeDistance(float f) {eye_dist = f;}
	void SetYLevelHeight(int h) {y_level_h = h;}
	
	void Unrender(const DescriptorImage& l_img, const DescriptorImage& r_img, Octree& o);
	
};




NAMESPACE_TOPSIDE_END

#endif
