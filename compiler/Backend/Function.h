#ifndef _Backend_Function_h_
#define _Backend_Function_h_


NAMESPACE_TOPSIDE_BEGIN


class Function : public CompilerNode<Function,Class> {
public:
	One<Statement>		impl;
	String				name;
	
public:
	typedef Function CLASSNAME;
	Function() {}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END


#endif
