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
	
	
};


NAMESPACE_TOPSIDE_END


#endif
