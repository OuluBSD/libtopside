#ifndef _Backend_MetaExpression_h_
#define _Backend_MetaExpression_h_

NAMESPACE_TOPSIDE_BEGIN


class MetaScope;
class MetaStatement;
class MetaExpression;


class MetaExpression : public CompilerNode<MetaExpression,MetaStatement> {
	
public:
	typedef enum {
		INVALID,
		CALL,
		REFERENCE,
		STRING,
		
	} Type;
	
protected:
	Array<MetaExpression>	mexprs;
	Type		type = INVALID;
	String		str;
	union {
		int64	i64;
		uint64	u64;
		double	dbl;
	};
	
public:
	
	void			SetType(Type t) {type = t;}
	void			SetId(String s) {ASSERT(s.GetCount()); type = STRING; str = s;}
	void			SetCall(String s) {ASSERT(s.GetCount()); type = CALL; str = s;}
	MetaExpression&	AddSub();
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};

using MExpr = MetaExpression;



class MetaStatement :
	public CompilerNode<MetaStatement,MetaScope>,
	public AccessControl
{
	
	One<MetaExpression>		mexpr;
	
public:
	
	MetaStatement();
	
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
	operator MetaExpression&() {return *mexpr;}
	
};

using MStmt = MetaStatement;



class MetaScope {
	
	
};


NAMESPACE_TOPSIDE_END

#endif
