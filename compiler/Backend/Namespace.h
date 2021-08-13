#ifndef _Backend_Namespace_h_
#define _Backend_Namespace_h_


NAMESPACE_TOPSIDE_BEGIN


class Namespace : public CompilerNode<Namespace,CompilationUnit> {
	
	
public:
	typedef Namespace CLASSNAME;
	Namespace() {}
	
	
	Class&		FindAddClass(String name);
	Class&		FindAddTemplateClass(String name);
	
};


NAMESPACE_TOPSIDE_END


#endif
