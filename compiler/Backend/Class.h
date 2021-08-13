#ifndef _Backend_Class_h_
#define _Backend_Class_h_


NAMESPACE_TOPSIDE_BEGIN


class Class : public CompilerNode<Class,Namespace> {
	
	
public:
	typedef Class CLASSNAME;
	Class() {}
	
	
	bool Inherit(Class& cls);
	
	
};


NAMESPACE_TOPSIDE_END


#endif
