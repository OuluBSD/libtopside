#ifndef _Backend_CompilationUnit_h_
#define _Backend_CompilationUnit_h_

NAMESPACE_TOPSIDE_BEGIN


class CompilationUnit : public CompilerNode<CompilationUnit,void> {
	
	
public:
	typedef CompilationUnit CLASSNAME;
	CompilationUnit() {}
	
	
	Namespace&	FindAddNamespace(String name);
	
};


NAMESPACE_TOPSIDE_END

#endif
