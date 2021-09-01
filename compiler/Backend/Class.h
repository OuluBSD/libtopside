#ifndef _Backend_Class_h_
#define _Backend_Class_h_


NAMESPACE_TOPSIDE_BEGIN


class Class;


class TemplateClass : public CompilerNode<TemplateClass, Class> {
	
public:
	bool					is = false;
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};

class Class : public CompilerNode<Class,Namespace> {
public:
	TemplateClass			tmpl;
	Vector<Class*>			inherited;
	ArrayMap<String, Class>	classes;
	ArrayMap<String,Field>	fields;
	CodeAccess				access = ACC_PUBLIC;
	String					name;
	bool					is_template = false;
	
public:
	typedef Class CLASSNAME;
	Class();
	
	
	bool		Inherit(Class& cls);
	String		GetTypeString() const {return name;}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
	
};


NAMESPACE_TOPSIDE_END


#endif
