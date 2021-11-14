#ifndef _ComputerVision_BrightnessBinaryFeature_h_
#define _ComputerVision_BrightnessBinaryFeature_h_

NAMESPACE_TOPSIDE_BEGIN


class BrightnessBinaryFeature {
	pyra8 img_pyr;
	int interval = 4;
	double scale = 1.1486;
	int next = 5;
	double scale_to = 1;
	
	
public:
	
	BrightnessBinaryFeature();
	
	void prepare_cascade(Cascade& cascade);const pyra8& build_pyramid(const pyra8::DTen& src, int min_width, int min_height, int interval = 4);
	Vector<BBox> detect(const pyra8& pyramid, Cascade& cascade);
	
	
};


NAMESPACE_TOPSIDE_END

#endif
