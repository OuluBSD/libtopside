#ifndef _Backend_MetaEmitter_h_
#define _Backend_MetaEmitter_h_

NAMESPACE_TOPSIDE_BEGIN


class HighScriptEmitter : public ParserEmitter {
	String code, main;
	int indent = 0;
	bool dbg_indent = 0;
	Index<String> files;
	
	void Log(String s);
	void Enter();
	void Leave();
	
	String LocArg(const FileLocation& loc);
public:
	typedef HighScriptEmitter CLASSNAME;
	HighScriptEmitter();
	
	static String GetPartStringArray(const PathIdentifier& name);
	
	void Finish();
	void SetDebugIndent(bool b=true) {dbg_indent = b;}
	String GetResult() const {return code;}
	String GetTabString() const;
	
	void PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) override;
	void Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) override;
	void PushFunctionDefinition(const FileLocation& loc) override;
	void PopFunctionDefinition(const FileLocation& loc) override;
	void PopFunction(const FileLocation& loc) override;
	void PushStatementList(const FileLocation& loc) override;
	void PopStatementList(const FileLocation& loc) override;
	void PushStatement(const FileLocation& loc, StmtType type) override;
	void PopStatement(const FileLocation& loc) override;
	void BindStatementParameter(const FileLocation& loc, StmtParamType t) override;
	void DeclareVariable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id) override;
	//void PushExprScope() override;
	void PopExprScopeToCtor(const FileLocation& loc) override;
	//void PushCall(const PathIdentifier& id) override;
	//void PopCall() override;
	//void PushExprScopeRval() override;
	void PopExpr(const FileLocation& loc) override;
	void PushRval(const FileLocation& loc, const AstNode& n) override;
	void PushRvalCall(const FileLocation& loc, const AstNode& n) override;
	void PushRvalConstruct(const FileLocation& loc, const AstNode& n) override;
	void PushRvalConstant(const FileLocation& loc, const Token& t) override;
	void Expr1(const FileLocation& loc, OpType op) override;
	void Expr2(const FileLocation& loc, OpType op) override;
	void Expr3(const FileLocation& loc, OpType op) override;
	
};

NAMESPACE_TOPSIDE_END

#endif
