#ifndef _DesktopSuite_Explorer_h_
#define _DesktopSuite_Explorer_h_

NAMESPACE_TOPSIDE_BEGIN


class ExplorerDirectory : RTTIBase {
	
	
public:
	RTTI_DECL0(ExplorerDirectory)
	ExplorerDirectory();
	
	
};

class Explorer : public TopWindow {
	
	
public:
	typedef Explorer CLASSNAME;
	Explorer();
	
};

NAMESPACE_TOPSIDE_END

#endif
