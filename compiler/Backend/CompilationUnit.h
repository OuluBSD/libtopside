#ifndef _Backend_CompilationUnit_h_
#define _Backend_CompilationUnit_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


class CompilationUnit : public CompilerNode<CompilationUnit,NodeBase> {
	
public:
	Namespace						root;
	ArrayMap<String,TypeExpr>		gtypes;
	
public:
	typedef CompilationUnit CLASSNAME;
	CompilationUnit();
	
	void InitDefault();
	
	Namespace&	GetAddNamespace(String name);
	bool		Activate(TypeExpr& te);
	void		AddBuiltinType(String name);
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	Class*		FindClass(const PathIdentifier& id, int i=0);
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif
