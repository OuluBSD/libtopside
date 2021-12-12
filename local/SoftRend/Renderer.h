#ifndef _SoftRend_Renderer_h_
#define _SoftRend_Renderer_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftRend {
	bool verbose = false;
	
	
public:
	typedef SoftRend CLASSNAME;
	SoftRend();
	
	void SetDebugOutput(bool b) {verbose = b;}
	void ClearBuffers();
	void SetSmoothShading(bool b=true);
	void SetDepthTest(bool b=true);
	void SetDepthOrderLess(bool b=true);
	void SetClearValue(RGBA clr, byte depth);
	void SetFastPerspectiveCorrection(bool b=true);
	void SetTriangleBacksideCulling(bool b=true);
	void SetTriangleFrontsideCCW(bool b=true);
	void SetViewport(Size sz);
	
	
};


NAMESPACE_TOPSIDE_END

#endif
