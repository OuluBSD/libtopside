#ifndef _ComputerVision_BrightnessBinaryFeature_h_
#define _ComputerVision_BrightnessBinaryFeature_h_

NAMESPACE_TOPSIDE_BEGIN


class BrightnessBinaryFeature {
	int interval = 4;
	double scale = 1.1486;
	int next = 5;
	double scale_to = 1;
	
	
public:
	
	BrightnessBinaryFeature();
	
	void PrepareCascade(Cascade& cascade);
	const pyra8& BuildPyramid(pyra8& img_pyr, const pyra8::Mat& src, int min_width, int min_height, int interval = 4);
	void Detect(Vector<BBox>& rects, const pyra8& pyramid, Cascade& cascade);
	
	
};


NAMESPACE_TOPSIDE_END

#endif
