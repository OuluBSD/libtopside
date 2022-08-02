#ifndef _Edit3D_SoftRendCtrl_h_
#define _Edit3D_SoftRendCtrl_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN

struct EditConfiguration;


struct SoftRendCtrl : Ctrl {
	SoftRend rend;
	SoftFramebuffer fb;
	SoftPipeline pipe;
	SoftProgram prog;
	
public:
	typedef SoftRendCtrl CLASSNAME;
	SoftRendCtrl();
	
	void Paint(Draw& d);
	
	void DefaultPreFrame();
	void ProcessStage();
	
	
	EditConfiguration* conf = 0;
};


NAMESPACE_TOPSIDE_END

#endif
#endif
