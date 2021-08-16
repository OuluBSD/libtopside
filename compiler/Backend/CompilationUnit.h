#ifndef _Backend_CompilationUnit_h_
#define _Backend_CompilationUnit_h_

NAMESPACE_TOPSIDE_BEGIN


class CompilationUnit : public CompilerNode<CompilationUnit,void> {
	
public:
	ArrayMap<String,Namespace>		namespaces;
	
public:
	typedef CompilationUnit CLASSNAME;
	CompilationUnit();
	
	
	Namespace&	GetAddNamespace(String name);
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END

#endif
