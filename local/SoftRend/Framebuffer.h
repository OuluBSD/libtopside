#ifndef _SoftRend_Framebuffer_h_
#define _SoftRend_Framebuffer_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftFramebuffer {
	bool inited = false;
	
public:
	typedef SoftFramebuffer CLASSNAME;
	SoftFramebuffer();
	
	void Clear();
	bool Create();
	void ClearData(GVar::BufferType type);
	
	void SetParam(int type, GVar::Filter filter, GVar::Wrap repeat);
	
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	
};


NAMESPACE_TOPSIDE_END

#endif
