#ifndef _Backend_SemanticParser_h_
#define _Backend_SemanticParser_h_

NAMESPACE_TOPSIDE_BEGIN


struct ParserEmitter {
	
	
	virtual void PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) {}
	virtual void Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {}
	virtual void PushFunctionDefinition(const FileLocation& loc) {}
	virtual void PopFunctionDefinition(const FileLocation& loc) {}
	virtual void PopFunction(const FileLocation& loc) {}
	virtual void PushStatementList(const FileLocation& loc) {}
	virtual void PopStatementList(const FileLocation& loc) {}
	virtual void PushStatement(const FileLocation& loc, StmtType type) {}
	virtual void PopStatement(const FileLocation& loc) {}
	virtual void PushStatementParameter(const FileLocation& loc, StmtParamType t) {}
	virtual void PopStatementParameter(const FileLocation& loc) {}
	virtual void DeclareVariable(const FileLocation& loc, AstNode& n, const PathIdentifier& id) {}
	virtual void Variable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id) {}
	//virtual void PushExprScope() {}
	virtual void PopExprScopeToCtor(const FileLocation& loc) {}
	//virtual void PushCall(const PathIdentifier& id) {}
	//virtual void PopCall() {}
	//virtual void PushExprScopeRval() {}
	virtual void PushRvalCall(const FileLocation& loc, AstNode& n) {}
	virtual void PushRvalConstruct(const FileLocation& loc, AstNode& n) {}
	virtual void PopExpr(const FileLocation& loc) {}
	virtual void PushRval(const FileLocation& loc, AstNode& n) {}
	virtual void PushRvalConstant(const FileLocation& loc, const Token& t) {}
	virtual void Expr1(const FileLocation& loc, OpType op) {}
	virtual void Expr2(const FileLocation& loc, OpType op) {}
	virtual void Expr3(const FileLocation& loc, OpType op) {}
	
};


class SemanticParser :
	public CompilerNode<SemanticParser,NodeBase>,
	public EonStd,
	public ParserEmitter,
	public ErrorSource
{
	
	struct Iterator {
		const Token* begin;
		const Token* iter;
		const Token* end;
		const TokenNode* node;
		
		const Token* operator->() const {return iter;}
		const Token* operator*() const {return iter;}
		operator bool() const {return iter < end;}
		operator const Token*() const {return iter;}
		operator const Token&() const {return *iter;}
		bool Check(const TokenNode& n) const {return node == &n && begin <= iter && iter <= end && n.begin == begin && n.end == end;}
		void operator++(int i) {iter++; ASSERT(iter <= end);}
		void operator++() {++iter; ASSERT(iter <= end);}
	};
	Array<Iterator> iters;
	
	
	
	String GetPath(const AstNode& n) const;
	
public:
	AstNode root;
	Array<const TokenNode*> path;
	
	const TokenNode& CurrentNode() {return *path.Top();}
	bool Id(const char* s);
	Iterator& AddIterator(const TokenNode& n);
	Iterator& TopIterator();
	const Iterator& TopIterator() const;
	void PopIterator();
	AstNode* ParseAndFindDeclaration();
	bool PassToken(int tk_type);
	bool PassId(const char* s);
	bool IsToken(int tk_type) const;
	bool TryToken(int tk_type);
	bool IsChar(int tk_type) const {return IsToken(tk_type);}
	//bool IsChar2(int a, int b) const;
	//bool Char2(int a, int b);
	bool PassChar(int tk_type) {return PassToken(tk_type);}
	bool Char(int tk_type) {return TryToken(tk_type);}
	
	
public:
	typedef SemanticParser CLASSNAME;
	SemanticParser();
	
	AstNode& GetRoot() override {return root;}
	
	bool ProcessEon(const TokenStructure& t);
	bool ParseNamespaceBlock();
	bool ParseDeclaration();
	bool ParseClass();
	bool ParseTypedDeclaration(AstNode& ret_type);
	bool ParseFunction(AstNode& ret_type, const PathIdentifier& name);
	bool ParseStatementList();
	bool ParseStatement();
	bool ParseConditional();
	bool ParseExpression();
	bool ParseSwitchBlock();
	bool ParseStatementBlock();
	bool ParseParameter();
	bool ParsePathIdentifier(PathIdentifier& id);
	bool ParseDeclExpr();
	bool Assign();
	bool Cond();
	bool Subscript();
	bool Term();
	bool Unary();
	bool Mul();
	bool Add();
	bool Shift();
	bool DoCompare(const FileLocation& loc, OpType t);
	bool Compare();
	bool Equal();
	bool BinAnd();
	bool BinXor();
	bool BinOr();
	bool And();
	bool Or();
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
