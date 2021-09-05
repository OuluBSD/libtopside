#ifndef _Backend_Expression_h_
#define _Backend_Expression_h_


NAMESPACE_TOPSIDE_BEGIN


class Expression : public CompilerNode<Expression,NodeBase> {
	
public:
	typedef enum {
		EMPTY,
		PARENT,
		ID,
		ID_TMPL,
		RETURN,
		META_CALL,
		CALL,
		OBJ_METHOD,
		OBJ_METHOD_TMPL,
		OBJ_FIELD,
		
	} Type;
	
	
public:
	Array<Expression>	exprs;
	Type				type = EMPTY;
	String				str;
	union {
		int64			i64;
		uint64			u64;
		double			dbl;
	};
	
public:
	typedef Expression CLASSNAME;
	Expression() {}
	
	Expression&	SetParentExpr() {type = PARENT; return *this;}
	Expression&	SetReturn() {type = RETURN; return *this;}
	Expression&	SetId(String key) {type = ID; str = key; return *this;}
	Expression&	SetIdTemplate(String key) {type = ID_TMPL; str = key; return *this;}
	Expression&	SetCall(String key) {type = CALL; str = key; return *this;}
	Expression&	SetMetaCall(String key) {type = META_CALL; str = key; return *this;}
	Expression&	SetObjMethodTemplate(String key) {type = OBJ_METHOD_TMPL; str = key; return *this;}
	
	Expression&	First() {if (exprs.GetCount() < 1) exprs.SetCount(1); return exprs[0];}
	Expression&	Second() {if (exprs.GetCount() < 2) exprs.SetCount(2); return exprs[1];}
	Expression&	Add() {return exprs.Add();}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END


#endif
