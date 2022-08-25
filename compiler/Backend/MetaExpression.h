#ifndef _Backend_MetaExpression_h_
#define _Backend_MetaExpression_h_

#if 0

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
		ID,
		STRING,
		DEFINE,
		
	} Type;
	
protected:
	friend class AssemblyExporter;
	
	Array<MetaExpression>	mexprs;
	Type		type = INVALID;
	String		str;
	union {
		int64	i64;
		uint64	u64;
		double	dbl;
	};
	
public:
	
	MetaExpression&	SetType(Type t) {type = t; return *this;}
	MetaExpression&	SetId(String s) {ASSERT(s.GetCount()); type = ID; str = s; return *this;}
	MetaExpression&	SetString(String s) {ASSERT(s.GetCount()); type = STRING; str = s; return *this;}
	MetaExpression&	SetCall(String s) {ASSERT(s.GetCount()); type = CALL; str = s; return *this;}
	MetaExpression&	SetDefine(String s) {ASSERT(s.GetCount()); type = DEFINE; str = s; return *this;}
	MetaExpression&	AddSub();
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};

using MExpr = MetaExpression;



class MetaStatement :
	public CompilerNode<MetaStatement,NodeBase>,
	public AccessControl
{
public:
	One<MetaExpression>		mexpr;
	bool					is_inline = false;
	bool					hide_stmt = false;
	
public:
	
	MetaStatement();
	
	MetaStatement&		SetInline(bool b=true) {is_inline = b; return *this;}
	MetaStatement&		HideStatement(bool b=true) {hide_stmt = b; return *this;}
	
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
#endif
