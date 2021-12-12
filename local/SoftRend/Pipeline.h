#ifndef _SoftRend_Pipeline_h_
#define _SoftRend_Pipeline_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftPipeline {
	bool inited = false;
	
	
public:
	typedef SoftPipeline CLASSNAME;
	SoftPipeline();
	
	bool Create();
	void Clear();
	void Use(SoftProgram& prog, uint32 bmask);
	
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	
};


NAMESPACE_TOPSIDE_END

#endif
