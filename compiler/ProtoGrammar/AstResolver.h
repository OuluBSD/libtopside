#ifndef _ProtoGrammar_AstResolver_h_
#define _ProtoGrammar_AstResolver_h_
#ifndef flagBOOTSTRAP

NAMESPACE_OULU_BEGIN


class AstResolver;


class ExprResolver {
	Array<Ast::Expression> exprs;
	Ast::Scope* scope = 0;
	AstResolver& res;
	
	
public:
	ExprResolver(AstResolver& res) : res(res) {}
	
	
	Ast::Node* NewId(String id);
	
};


class AstResolver : public ErrorSource {
	Array<ExprResolver> res_scopes;
	
protected:
	friend class ExprResolver;
	void PushError(String msg);
	
public:
	typedef AstResolver CLASSNAME;
	AstResolver();
	
	void Init();
	
	void BeginStmt();
	Ast::Node* NewExprId(String id);
	
};


NAMESPACE_OULU_END

#endif
#endif
