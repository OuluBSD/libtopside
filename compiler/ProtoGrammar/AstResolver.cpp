#include "Grammar.h"


#ifndef flagBOOTSTRAP


NAMESPACE_TOPSIDE_BEGIN


#define REF_EXPR_SCOPE \
	if (res_scopes.IsEmpty()) {PushError("No expression-resolve scopes"); return 0;} \
	ExprResolver& e = res_scopes.Top();



AstResolver::AstResolver() : ErrorSource("AstResolver") {
	
}

void AstResolver::Init() {
	
}

void AstResolver::BeginStmt() {
	res_scopes.Add(new ExprResolver(*this));
}

Ast::Node* AstResolver::NewExprId(String id) {
	REF_EXPR_SCOPE
	return e.NewId(id);
}

void AstResolver::PushError(String msg) {
	FileLocation loc;
	AddError(loc, msg);
}




Ast::Node* ExprResolver::NewId(String id) {
	Ast::Node* n = scope->FindInVisible(id);
	
	if (!n) {
		res.PushError(Format("Identifier '%s' not found in any scope", id));
		return 0;
	}
	
	TODO
	
	return n;
}


NAMESPACE_TOPSIDE_END


#endif
