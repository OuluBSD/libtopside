#ifndef _Backend_Statement_h_
#define _Backend_Statement_h_


NAMESPACE_TOPSIDE_BEGIN


class Statement : public CompilerNode<Statement,Function> {
	
public:
	typedef enum {
		STMT,
		BLOCK
	} Type;
	
	
public:
	Array<Statement>	stmts;
	One<Expression>		expr;
	Type				type = STMT;
	
public:
	typedef Statement CLASSNAME;
	Statement() {}
	
	Statement&	SetBlock() {type = BLOCK; return *this;}
	
	Expression&	RealizeExpression();
	Statement&	Add();
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	operator Expression&() {return RealizeExpression();}
	
};


class UsingStatement :
	public CompilerNode<UsingStatement,NodeBase>,
	public AccessControl,
	public MetaConditional
{
	
	
public:
	One<Expression>		expr;
	String				name;
	
	
public:
	typedef UsingStatement CLASSNAME;
	UsingStatement();
	
	String		GetName() const override {return name;}
	
	void		SetName(String s) {name = s;}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	operator Expression&() {return *expr;}
	
};


NAMESPACE_TOPSIDE_END


#endif
