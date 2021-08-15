#ifndef _Backend_Class_h_
#define _Backend_Class_h_


NAMESPACE_TOPSIDE_BEGIN


class Class : public CompilerNode<Class,Namespace> {
public:
	Vector<Class*>	inherited;
	String			name;
	bool			is_template = false;
	
public:
	typedef Class CLASSNAME;
	Class();
	
	
	bool Inherit(Class& cls);
	
	
};


NAMESPACE_TOPSIDE_END


#endif
