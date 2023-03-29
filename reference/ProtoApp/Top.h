#ifndef _ProtoApp_Top_h_
#define _ProtoApp_Top_h_

NAMESPACE_TOPSIDE_BEGIN


class VmCtrl : public Ctrl {
	
	
public:
	typedef VmCtrl CLASSNAME;
	VmCtrl();
	
};

class ProtoApp : public TopWindow {
	TabCtrl tabs;
	VmCtrl vm;
	
public:
	typedef ProtoApp CLASSNAME;
	ProtoApp();
	
};


NAMESPACE_TOPSIDE_END

#endif
