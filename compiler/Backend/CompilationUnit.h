#ifndef _Backend_CompilationUnit_h_
#define _Backend_CompilationUnit_h_

NAMESPACE_TOPSIDE_BEGIN


class CompilationUnit : public CompilerNode<CompilationUnit,void> {
	ArrayMap<String,Namespace>		namespaces;
	
public:
	typedef CompilationUnit CLASSNAME;
	CompilationUnit();
	
	
	Namespace&	GetAddNamespace(String name);
	
};


NAMESPACE_TOPSIDE_END

#endif
