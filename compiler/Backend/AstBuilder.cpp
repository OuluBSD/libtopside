#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstBuilder::AstBuilder() :
	ErrorSource("AstBuilder")
{
	
}

bool AstBuilder::Execute(String high_script_content) {
    ArrayMap<String, HiValue> global;
    
	try {
		HighCall(global, "AddFile(file)", THISBACK(HiAddFile));
		HighCall(global, "PushFunction(loc, ret_type, name)", THISBACK(HiPushFunction));
		HighCall(global, "Parameter(loc, type, name)", THISBACK(HiParameter));
		HighCall(global, "PushFunctionDefinition(loc)", THISBACK(HiPushFunctionDefinition));
		HighCall(global, "PopFunctionDefinition(loc)", THISBACK(HiPopFunctionDefinition));
		HighCall(global, "PopFunction(loc)", THISBACK(HiPopFunction));
		HighCall(global, "PushStatementList(loc)", THISBACK(HiPushStatementList));
		HighCall(global, "PopStatementList(loc)", THISBACK(HiPopStatementList));
		HighCall(global, "PushStatement(loc, type)", THISBACK(HiPushStatement));
		HighCall(global, "PopStatement(loc)", THISBACK(HiPopStatement));
		HighCall(global, "BindStatementParameter(loc, param_type)", THISBACK(HiBindStatementParameter));
		HighCall(global, "DeclareVariable(loc, n, id)", THISBACK(HiDeclareVariable));
		HighCall(global, "PopExprScopeToCtor(loc)", THISBACK(HiPopExprScopeToCtor));
		HighCall(global, "PopExpr(loc)", THISBACK(HiPopExpr));
		HighCall(global, "PushRval(loc, n)", THISBACK(HiPushRval));
		HighCall(global, "PushRvalCall(loc, n)", THISBACK(HiPushRvalCall));
		HighCall(global, "PushRvalConstruct(loc, n)", THISBACK(HiPushRvalConstruct));
		HighCall(global, "PushRvalConstant(loc, t)", THISBACK(HiPushRvalConstant));
		HighCall(global, "Expr1(loc, op)", THISBACK(HiExpr1));
		HighCall(global, "Expr2(loc, op)", THISBACK(HiExpr2));
		HighCall(global, "Expr3(loc, op)", THISBACK(HiExpr3));
	    StdLib(global);
	
        Scan(global, high_script_content, "parser");
        HiValue ret = TS::Execute(global, "main", INT_MAX);
        DUMP(ret);
    }
    catch(Exc e) {
        LOG("ERROR: " << e << "\n");
        return false;
    }
    return true;
}

void AstBuilder::PushFunction(const FileLocation& loc, Class& ret_type, const PathIdentifier& name) {
	TODO
}

void AstBuilder::Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {
	TODO
}

void AstBuilder::PushFunctionDefinition(const FileLocation& loc) {
	TODO
}

void AstBuilder::PopFunctionDefinition(const FileLocation& loc) {
	TODO
}

void AstBuilder::PopFunction(const FileLocation& loc) {
	TODO
}

void AstBuilder::PushStatementList(const FileLocation& loc) {
	TODO
}

void AstBuilder::PopStatementList(const FileLocation& loc) {
	TODO
}

void AstBuilder::PushStatement(const FileLocation& loc, StmtType type) {
	TODO
}

void AstBuilder::PopStatement(const FileLocation& loc) {
	TODO
}

void AstBuilder::BindStatementParameter(const FileLocation& loc, StmtParamType t) {
	TODO
}

void AstBuilder::DeclareVariable(const FileLocation& loc, const SemanticNode& n, const PathIdentifier& id) {
	TODO
}

void AstBuilder::PopExprScopeToCtor(const FileLocation& loc) {
	TODO
}

void AstBuilder::PopExpr(const FileLocation& loc) {
	TODO
}

void AstBuilder::PushRval(const FileLocation& loc, const SemanticNode& n) {
	TODO
}

void AstBuilder::PushRvalCall(const FileLocation& loc, const SemanticNode& n) {
	TODO
}

void AstBuilder::PushRvalConstruct(const FileLocation& loc, const SemanticNode& n) {
	TODO
}

void AstBuilder::PushRvalConstant(const FileLocation& loc, const Token& t) {
	TODO
}

void AstBuilder::Expr1(const FileLocation& loc, OpType op) {
	TODO
}

void AstBuilder::Expr2(const FileLocation& loc, OpType op) {
	TODO
}

void AstBuilder::Expr3(const FileLocation& loc, OpType op) {
	TODO
}





void AstBuilder::LoadLocation(const HiValue& v, FileLocation& loc) {
	int f = v[0];
	loc.line = v[1];
	loc.col = v[2];
	loc.file = f >= 0 && f < files.GetCount() ? files[f] : String();
}

void AstBuilder::LoadPath(const FileLocation& loc, const HiValue& v, PathIdentifier& id, Vector<Token>& tokens) {
	id.part_count = v.GetCount();
	int c = id.part_count * 2 - 1;
	tokens.SetCount(c);
	for(int i = 0, j = 0; i < c; i++) {
		Token& t = tokens[i];
		t.loc = loc;
		if (i % 2 == 0) {
			const HiValue& v0 = v.ArrayGet(j);
			id.parts[j] = &t;
			t.type = TK_ID;
			t.str_value = (String)v0;
			j++;
		}
		else {
			t.type = '.';
		}
	}
	id.begin = tokens.Begin();
	id.end = tokens.End();
}

void AstBuilder::HiAddFile(HiEscape& e) {
	String file = e[0];
	files.Add(file);
}

void AstBuilder::HiPushFunction(HiEscape& e) {
	FileLocation loc;
	LoadLocation(e[0], loc);
	
	PathIdentifier name, type;
	LoadPath(loc, e[1], type, tokens[0]);
	LoadPath(loc, e[2], name, tokens[1]);
	
	//DUMP(loc); DUMP(name); DUMP(type);
	
	Class* ret_cls = cunit.FindClass(type);
	if (!ret_cls) {
		TODO // internal error
		// e.Throw
	}
	
	PushFunction(loc, *ret_cls, name);
}

void AstBuilder::HiParameter(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushFunctionDefinition(HiEscape& e) {
	TODO
}

void AstBuilder::HiPopFunctionDefinition(HiEscape& e) {
	TODO
}

void AstBuilder::HiPopFunction(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushStatementList(HiEscape& e) {
	TODO
}

void AstBuilder::HiPopStatementList(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushStatement(HiEscape& e) {
	TODO
}

void AstBuilder::HiPopStatement(HiEscape& e) {
	TODO
}

void AstBuilder::HiBindStatementParameter(HiEscape& e) {
	TODO
}

void AstBuilder::HiDeclareVariable(HiEscape& e) {
	TODO
}

void AstBuilder::HiPopExprScopeToCtor(HiEscape& e) {
	TODO
}

void AstBuilder::HiPopExpr(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushRval(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushRvalCall(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushRvalConstruct(HiEscape& e) {
	TODO
}

void AstBuilder::HiPushRvalConstant(HiEscape& e) {
	TODO
}

void AstBuilder::HiExpr1(HiEscape& e) {
	TODO
}

void AstBuilder::HiExpr2(HiEscape& e) {
	TODO
}

void AstBuilder::HiExpr3(HiEscape& e) {
	TODO
}




NAMESPACE_TOPSIDE_END
