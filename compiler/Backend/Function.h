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
	String				name;
	bool				is_static = false;
	TypeExpr			ret;
	ArrayMap<String, TypeExpr>	params;
	
	
public:
	typedef Function CLASSNAME;
	Function() {}
	
	Function&	SetStatic(bool b=true);
	Function&	SetReturn(const TypeExpr& te);
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


class FunctionIdScope :
	public CompilerNode<FunctionIdScope,Class>
{
	Array<Function>		funcs;
	String				name;
	
public:
	typedef FunctionIdScope CLASSNAME;
	FunctionIdScope() {}
	
	String		GetName() const {return name;}
	
	Function&	AddFunction();
	void		SetName(String s) {name = s;}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
	
};


NAMESPACE_TOPSIDE_END


#endif
