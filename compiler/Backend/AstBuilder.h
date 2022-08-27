#ifndef _Backend_AstBuilder_h_
#define _Backend_AstBuilder_h_

NAMESPACE_TOPSIDE_BEGIN


class AstBuilder :
	public EonStd,
	public ParserEmitter,
	public ErrorSource
{
	
	
	
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
	
	AstNode& GetRoot() override {return root;}
	void Clear();
	
	void PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) override;
	void Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) override;
	void PushFunctionDefinition(const FileLocation& loc) override;
	void PopFunctionDefinition(const FileLocation& loc) override;
	void PopFunction(const FileLocation& loc) override;
	void PushStatementList(const FileLocation& loc) override;
	void PopStatementList(const FileLocation& loc) override;
	void PushStatement(const FileLocation& loc, StmtType type) override;
	void PopStatement(const FileLocation& loc) override;
	void PushStatementParameter(const FileLocation& loc, StmtParamType t) override;
	void PopStatementParameter(const FileLocation& loc) override;
	void DeclareVariable(const FileLocation& loc, AstNode& type, const PathIdentifier& name) override;
	void PopExprScopeToCtor(const FileLocation& loc) override;
	void PopExpr(const FileLocation& loc) override;
	void PushRval(const FileLocation& loc, AstNode& n) override;
	void PushRvalCall(const FileLocation& loc, AstNode& n) override;
	void PushRvalConstruct(const FileLocation& loc, AstNode& n) override;
	void PushRvalConstant(const FileLocation& loc, const Token& t) override;
	void Expr1(const FileLocation& loc, OpType op) override;
	void Expr2(const FileLocation& loc, OpType op) override;
	void Expr3(const FileLocation& loc, OpType op) override;

	void PushRvalConstant(const FileLocation& loc, int32 v);
	void PushRvalConstant(const FileLocation& loc, int64 v);
	void PushRvalConstant(const FileLocation& loc, double v);
	void PushRvalConstant(const FileLocation& loc, String v);
	
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
	void HiPushStatementParameter(HiEscape& e);
	void HiPopStatementParameter(HiEscape& e);
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
