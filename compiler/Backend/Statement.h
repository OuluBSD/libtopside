#ifndef _Backend_Statement_h_
#define _Backend_Statement_h_


NAMESPACE_TOPSIDE_BEGIN


class Statement : public CompilerNode<Statement,Function> {
public:
	Array<Statement>	stmts;
	One<Expression>		expr;
	
public:
	typedef Statement CLASSNAME;
	Statement() {}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END


#endif
