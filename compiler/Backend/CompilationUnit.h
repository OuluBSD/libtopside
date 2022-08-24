#ifndef _Backend_CompilationUnit_h_
#define _Backend_CompilationUnit_h_

NAMESPACE_TOPSIDE_BEGIN


class CompilationUnit : public CompilerNode<CompilationUnit,NodeBase> {
	
public:
	ArrayMap<String,Namespace>		namespaces;
	ArrayMap<String,TypeExpr>		gtypes;
	
public:
	typedef CompilationUnit CLASSNAME;
	CompilationUnit();
	
	
	Namespace&	GetAddNamespace(String name);
	bool		Activate(TypeExpr& te);
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	Class*		FindClass(const PathIdentifier& id);
	
};


NAMESPACE_TOPSIDE_END

#endif
