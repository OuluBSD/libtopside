#ifndef _Backend_AstBuilder_h_
#define _Backend_AstBuilder_h_

NAMESPACE_TOPSIDE_BEGIN


class AstBuilder : public ErrorSource {
	
	
	
public:
	Vector<Token> tokens[5];
	Index<String> files;
	//CompilationUnit cunit;
	AstNode root;
	
	void LoadLocation(const HiValue& v, FileLocation& loc);
	void LoadPath(const FileLocation& loc, const HiValue& v, PathIdentifier& id, Vector<Token>& tokens);
	
public:
	typedef AstBuilder CLASSNAME;
	AstBuilder();
	
	void InitDefault();
	
	bool PushFunction(const FileLocation& loc, Class& ret_type, const PathIdentifier& name);
	void Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name);
	void PushFunctionDefinition(const FileLocation& loc);
	void PopFunctionDefinition(const FileLocation& loc);
	void PopFunction(const FileLocation& loc);
	void PushStatementList(const FileLocation& loc);
	void PopStatementList(const FileLocation& loc);
	void PushStatement(const FileLocation& loc, StmtType type);
	void PopStatement(const FileLocation& loc);
	void BindStatementParameter(const FileLocation& loc, StmtParamType t);
	void DeclareVariable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id);
	void PopExprScopeToCtor(const FileLocation& loc);
	void PopExpr(const FileLocation& loc);
	void PushRval(const FileLocation& loc, const AstNode& n);
	void PushRvalCall(const FileLocation& loc, const AstNode& n);
	void PushRvalConstruct(const FileLocation& loc, const AstNode& n);
	void PushRvalConstant(const FileLocation& loc, const Token& t);
	void Expr1(const FileLocation& loc, OpType op);
	void Expr2(const FileLocation& loc, OpType op);
	void Expr3(const FileLocation& loc, OpType op);

	void HiAddFile(HiEscape& e);
	void HiPushFunction(HiEscape& e);
	void HiParameter(HiEscape& e);
	void HiPushFunctionDefinition(HiEscape& e);
	void HiPopFunctionDefinition(HiEscape& e);
	void HiPopFunction(HiEscape& e);
	void HiPushStatementList(HiEscape& e);
	void HiPopStatementList(HiEscape& e);
	void HiPushStatement(HiEscape& e);
	void HiPopStatement(HiEscape& e);
	void HiBindStatementParameter(HiEscape& e);
	void HiDeclareVariable(HiEscape& e);
	void HiPopExprScopeToCtor(HiEscape& e);
	void HiPopExpr(HiEscape& e);
	void HiPushRval(HiEscape& e);
	void HiPushRvalCall(HiEscape& e);
	void HiPushRvalConstruct(HiEscape& e);
	void HiPushRvalConstant(HiEscape& e);
	void HiExpr1(HiEscape& e);
	void HiExpr2(HiEscape& e);
	void HiExpr3(HiEscape& e);
	
	
	bool Execute(String high_script_content);
	
};


NAMESPACE_TOPSIDE_END

#endif
