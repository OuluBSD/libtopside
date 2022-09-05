#ifndef _Backend_SemanticParser_h_
#define _Backend_SemanticParser_h_

NAMESPACE_TOPSIDE_BEGIN


struct ParserEmitter {
	
	
	virtual void PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) = 0;
	virtual void PushMetaFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name) = 0;
	virtual void Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) = 0;
	virtual void MetaParameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) = 0;
	//virtual void PushFunctionDefinition(const FileLocation& loc) = 0;
	virtual void PopFunctionDefinition(const FileLocation& loc) = 0;
	virtual void PopFunction(const FileLocation& loc) = 0;
	virtual void PopMetaFunction(const FileLocation& loc) = 0;
	virtual void PushStatementList(const FileLocation& loc) = 0;
	virtual void PopStatementList(const FileLocation& loc) = 0;
	virtual void PushStatement(const FileLocation& loc, StmtType type) = 0;
	virtual void PopStatement(const FileLocation& loc) = 0;
	virtual void PushStatementParameter(const FileLocation& loc, StmtParamType t) = 0;
	virtual void PopStatementParameter(const FileLocation& loc) = 0;
	virtual void DeclareVariable(const FileLocation& loc, AstNode& n, const PathIdentifier& id) = 0;
	virtual void DeclareMetaVariable(const FileLocation& loc, AstNode& n, const PathIdentifier& id) = 0;
	virtual void Variable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id) = 0;
	virtual void PushRvalResolve(const FileLocation& loc, const PathIdentifier& id, SemanticType t) = 0;
	virtual void PushRvalArgumentList(const FileLocation& loc) = 0;
	virtual void Argument(const FileLocation& loc) = 0;
	//virtual void PushExprScope() = 0;
	//virtual void PopExprScopeToCtor(const FileLocation& loc) = 0;
	//virtual void PushCall(const PathIdentifier& id) = 0;
	//virtual void PopCall() = 0;
	//virtual void PushExprScopeRval() = 0;
	//virtual void PushRvalCall(const FileLocation& loc, AstNode& n) = 0;
	virtual void PushRvalConstruct(const FileLocation& loc, AstNode& n) = 0;
	virtual void PopExpr(const FileLocation& loc) = 0;
	virtual void PushRval(const FileLocation& loc, AstNode& n) = 0;
	virtual void PushRvalConstant(const FileLocation& loc, const Token& t) = 0;
	virtual void Expr1(const FileLocation& loc, OpType op) = 0;
	virtual void Expr2(const FileLocation& loc, OpType op) = 0;
	virtual void Expr3(const FileLocation& loc, OpType op) = 0;
	
};


class SemanticParser :
	public CompilerNode<SemanticParser,NodeBase>,
	public EonStd,
	public ParserEmitter,
	public ErrorSource
{
	bool allow_expr_unresolved = false;
	
	struct Iterator {
		const Token* begin;
		const Token* iter;
		const Token* end;
		const TokenNode* node;
		
		const Token* operator->() const {return iter;}
		const Token* operator*() const {return iter;}
		bool IsEnd() const {return iter == end;}
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
	AstNode* ParseAndFindMetaDeclaration();
	bool PassToken(int tk_type);
	bool IsId(const char* s) const;
	bool PassId(const char* s);
	bool IsToken(int tk_type) const;
	bool TryToken(int tk_type);
	bool IsChar(int tk_type) const {return IsToken(tk_type);}
	//bool IsChar2(int a, int b) const;
	//bool Char2(int a, int b);
	bool PassChar(int tk_type) {return PassToken(tk_type);}
	bool Char(int tk_type) {return TryToken(tk_type);}
	bool IsLineEnd() const {return TopIterator().IsEnd();}
	
public:
	typedef SemanticParser CLASSNAME;
	SemanticParser();
	
	AstNode& GetRoot() override {return root;}
	
	bool ProcessEon(const TokenStructure& t);
	bool ParseNamespaceBlock();
	bool ParseMachine();
	bool ParseChain();
	bool ParseLoop();
	bool ParseDeclaration();
	bool ParseClass();
	bool ParseWorld();
	bool ParseSystem();
	bool ParsePool();
	bool ParseEntity();
	bool ParseComponent();
	//bool ParseTypedDeclaration(AstNode& ret_type);
	//bool ParseTypedMetaDeclaration(AstNode& ret_type);
	bool ParseFunction(AstNode& ret_type, const PathIdentifier& name);
	bool ParseMetaFunction(AstNode& ret_type, const PathIdentifier& name);
	bool ParseAtomStatementList();
	bool ParseStatementList();
	bool ParseStatement();
	bool ParseMetaStatement(bool skip_meta_keywords=false);
	bool ParseExpression(bool m);
	bool ParseSwitchBlock();
	bool ParseStatementBlock();
	bool ParseParameter();
	bool ParseMetaParameter();
	bool ParsePathIdentifier(PathIdentifier& id);
	
	bool ParseMachineStatementList();
	bool ParseMachineStatement();
	bool ParseChainStatementList();
	bool ParseChainStatement();
	bool ParseLoopStatementList();
	bool ParseLoopStatement();
	
	bool ParseWorldStatementList();
	bool ParseWorldStatement();
	bool ParseSystemStatementList();
	bool ParseSystemStatement();
	bool ParsePoolStatementList();
	bool ParsePoolStatement();
	bool ParseEntityStatementList();
	bool ParseEntityStatement();
	bool ParseComponentStatementList();
	bool ParseComponentStatement();
	
	bool ParseState();
	bool ParseAtom(PathIdentifier& id);
	bool ParseDeclExpr(bool must_decl);
	bool ParseMetaDeclExpr(bool must_decl);
	bool ParseMeta();
	bool Assign(bool m);
	bool AssignPost(bool m);
	bool Cond(bool m);
	bool Subscript(bool m);
	bool Term(bool m);
	bool Unary(bool m);
	bool Mul(bool m);
	bool Add(bool m);
	bool Shift(bool m);
	bool DoCompare(bool m, const FileLocation& loc, OpType t);
	bool Compare(bool m);
	bool Equal(bool m);
	bool BinAnd(bool m);
	bool BinXor(bool m);
	bool BinOr(bool m);
	bool And(bool m);
	bool Or(bool m);
	//bool IsMetaTypeQualifier() const;
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
