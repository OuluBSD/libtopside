#ifndef _Backend_Namespace_h_
#define _Backend_Namespace_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


class Namespace :
	public CompilerNode<Namespace,CompilationUnit>,
	public ClassPathScope
{
	
public:
	ArrayMap<String, UsingStatement>	using_stmts;
	ArrayMap<String, Namespace>			namespaces;
	ArrayMap<String, Class>				classes;
	ArrayMap<String, MetaStatement>		mstmts;
	String								name;
	
public:
	typedef Namespace CLASSNAME;
	Namespace();
	
	Class&				GetAddClass(String name);
	Class&				GetAddTemplateClass(String name);
	Namespace&			GetAddNamespace(String name);
	UsingStatement&		GetAddUsing(String name);
	MetaStatement&		GetAddMetaStatement(String key);
	String				GetName() const override {return name;}
	String				GetTreeString(int indent=0) const override;
	String				GetCodeString(const CodeArgs& args) const override;
	String				ToString() const override;
	Class*				FindClass(const PathIdentifier& id, int i=0);
	
};


NAMESPACE_TOPSIDE_END


#endif
#endif
