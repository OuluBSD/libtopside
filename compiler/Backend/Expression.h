#ifndef _Backend_Expression_h_
#define _Backend_Expression_h_


NAMESPACE_TOPSIDE_BEGIN


class Expression : public CompilerNode<Expression,Statement> {
public:
	Array<Expression>	exprs;
	
	
public:
	typedef Expression CLASSNAME;
	Expression() {}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END


#endif
