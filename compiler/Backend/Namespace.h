#ifndef _Backend_Namespace_h_
#define _Backend_Namespace_h_


NAMESPACE_TOPSIDE_BEGIN


class Namespace : public CompilerNode<Namespace,CompilationUnit> {
	
public:
	ArrayMap<String, Class>		classes;
	String						name;
	
public:
	typedef Namespace CLASSNAME;
	Namespace();
	
	
	Class&		GetAddClass(String name);
	Class&		GetAddTemplateClass(String name);
	
};


NAMESPACE_TOPSIDE_END


#endif
