#ifndef _Backend_Class_h_
#define _Backend_Class_h_


NAMESPACE_TOPSIDE_BEGIN


class Class;

class ClassPathScope;

class ClassDecl : public CompilerNode<ClassDecl, ClassPathScope> {
	Class*		cls = 0;
	String		name;
	
	
public:
	typedef ClassDecl CLASSNAME;
	ClassDecl();
	
	void		SetName(String name) {this->name = name;}
	
	Class*		GetClass() const {return cls;}
	String		GetName() const override {return name;}
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};

class ClassPathScope {
	ArrayMap<String, ClassDecl>		cdecls;
	
public:
	typedef ClassPathScope CLASSNAME;
	ClassPathScope();
	
	
	ClassDecl&		GetAddClassDecl(String key);
	
};

class TemplateClass : public CompilerNode<TemplateClass, Class> {
	
public:
	bool					is = false;
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};

class Class :
	public CompilerNode<Class,Namespace>,
	public MetaScope,
	public AccessControl
{
public:
	TemplateClass			tmpl;
	Vector<Class*>			inherited;
	ArrayMap<String, Class>	classes;
	ArrayMap<String,Field>	fields;
	ArrayMap<String,FunctionIdScope>	funcids;
	ArrayMap<String, MetaStatement>		mstmts;
	String					name;
	bool					is_template = false;
	
public:
	typedef Class CLASSNAME;
	Class();
	
	
	bool				Inherit(Class& cls);
	String				GetTypeString() const {return name;}
	Field&				GetAddField(String name);
	MStmt&				GetAddMetaStatement(String name);
	FunctionIdScope&	GetAddFunctionIdScope(String name);
	String				GetName() const override {return name;}
	String				GetClassKey() const {return "class";}
	
	String				GetTreeString(int indent=0) const override;
	String				GetCodeString(const CodeArgs& args) const override;
	String				ToString() const override;
	String				GetClassPath() const override;
	
};


NAMESPACE_TOPSIDE_END


#endif
