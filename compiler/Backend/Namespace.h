#ifndef _Backend_Namespace_h_
#define _Backend_Namespace_h_


NAMESPACE_TOPSIDE_BEGIN


class Namespace : public CompilerNode<Namespace,CompilationUnit> {
	
public:
	ArrayMap<String, Namespace>	namespaces;
	ArrayMap<String, Class>		classes;
	String						name;
	
public:
	typedef Namespace CLASSNAME;
	Namespace();
	
	Class&		GetAddClass(String name);
	Class&		GetAddTemplateClass(String name);
	Namespace&	GetAddNamespace(String name);
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END


#endif
