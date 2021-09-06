#ifndef _Backend_Function_h_
#define _Backend_Function_h_


NAMESPACE_TOPSIDE_BEGIN


class FunctionIdScope;

class Function :
	public CompilerNode<Function,FunctionIdScope>,
	public AccessControl
{
public:
	One<Statement>		impl;
	bool				is_static = false;
	bool				is_const = false;
	bool				is_override_anon = false;
	bool				is_ext_impl = false;
	bool				is_alt_impl = false;
	TypeExpr			ret;
	ArrayMap<String, TypeExpr>	params;
	
	
public:
	typedef Function CLASSNAME;
	Function() {}
	
	Function&	SetStatic(bool b=true);
	Function&	SetReturn(const TypeExpr& te);
	Function&	SetOverrideAnonymous();
	Function&	SetConst();
	Function&	SetExternalImpl();
	Function&	SetAltImpl();
	Function&	AddParam(String key, const TypeExpr& te);
	Statement&	RealizeStatement();
	operator Statement&() {return RealizeStatement();}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


class FunctionIdScope :
	public CompilerNode<FunctionIdScope,Class>
{
public:
	Array<Function>		funcs;
	String				name;
	
public:
	typedef FunctionIdScope CLASSNAME;
	FunctionIdScope() {}
	
	String		GetName() const override {return name;}
	
	Function&	AddFunction();
	void		SetName(String s) {name = s;}
	String		GetCodeString(const CodeArgs& args, CodeAccess& acc) const;
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
	
};


NAMESPACE_TOPSIDE_END


#endif
