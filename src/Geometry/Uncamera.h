#ifndef _Geometry_Uncamera_h_
#define _Geometry_Uncamera_h_

NAMESPACE_TOPSIDE_BEGIN


class Uncamera : public MeshTracker {
	
	
public:
	Uncamera();
	
};

struct HorizontalMatch : Moveable<HorizontalMatch> {
	const Descriptor* l;
	const Descriptor* r;
	axes2s eyes;
	vec3 local_tgt;
	vec3 global_tgt;
	TrackedPoint* tp = 0;
};

struct UncameraFrame : MeshTrackerFrame {
	Octree otree;
	Image l_img, r_img;
	DescriptorImage l_dimg, r_dimg;
	//Vector<vec2> l_keypoints, r_keypoints;
	//Vector<vec3> points;
	
	// temp
	Vector<Vector<const Descriptor*>> l_desc, r_desc;
	Vector<HorizontalMatch> horz_match;
};


class VirtualStereoUncamera : public Uncamera, public LensPoly {
	float eye_dist = 0.068f;
	float error_factor = 0.25; // error_factor is multiplier for the distance, what is searched
	int iter = 0;
	int y_levels = 0;
	int y_level_h = 10;
	
	
public:
	UncameraFrame incremental;
	
	
public:
	typedef VirtualStereoUncamera CLASSNAME;
	VirtualStereoUncamera();
	
	void SetEyeDistance(float f) {eye_dist = f;}
	void SetYLevelHeight(int h) {y_level_h = h;}
	
	void Unrender(const UncameraFrame& from, UncameraFrame& to);
	void StageStereoKeypoints(const UncameraFrame& from, UncameraFrame& to);
	void StageProcessTransform(const UncameraFrame& from, UncameraFrame& to);
	
	void InitializeLensPoly(UncameraFrame& to);
	void ResetTempVariables(UncameraFrame& to);
	void FindPreviousFrameMatches(const UncameraFrame& from, UncameraFrame& to);
	void UpdateStereoTargets(const UncameraFrame& from);
	void FindHorizontalMatches(UncameraFrame& to);
	void AddHorizontalMatches(const UncameraFrame& from, UncameraFrame& to);
	void ProcessHorizontalMatches(UncameraFrame& to);
	void GetAddTrackedPoint(UncameraFrame& to, TrackedPoint& tp);
	
};

struct StagedVirtualStereoUncamera : VirtualStereoUncamera {
	Array<UncameraFrame> frames;
	
	
};




NAMESPACE_TOPSIDE_END

#endif
