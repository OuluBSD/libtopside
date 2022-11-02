#ifndef _Backend_SemanticParser_h_
#define _Backend_SemanticParser_h_

NAMESPACE_TOPSIDE_BEGIN



class SemanticParser :
	public CompilerNode<SemanticParser,NodeBase>,
	public EonStd,
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
	bool Id2(const char* a, const char* b);
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
	bool PassChar(int tk_type) {return PassToken(tk_type);}
	bool Char(int tk_type) {return TryToken(tk_type);}
	bool IsLineEnd() const {return TopIterator().IsEnd();}
	
public:
	typedef SemanticParser CLASSNAME;
	SemanticParser();
	
	AstNode& GetRoot() override {return root;}
	
	bool ProcessEon(const TokenStructure& t);
	bool ParseNamespaceBlock();
	bool ParseDeclaration();
	bool ParseClass();
	bool ParseFunction(AstNode& ret_type, const PathIdentifier& name);
	bool ParseMetaFunction(AstNode& ret_type, const PathIdentifier& name);
	bool ParseStatementList();
	bool ParseStatement();
	bool ParseExpressionStatement();
	bool ParseMetaStatement(int& cookie, bool skip_meta_keywords=false);
	AstNode* ParseExpression(bool m);
	bool ParseSwitchBlock();
	bool ParseStatementBlock();
	bool ParseType(PathIdentifier& type, AstNode*& tn);
	bool ParseParameter();
	bool ParseMetaParameter();
	bool ParsePathIdentifier(PathIdentifier& id, bool declare, bool resolve);
	bool ParseCallArguments();
	
	bool ParseMachine();
	bool ParseChain();
	bool ParseLoop();
	bool ParsePool();
	bool ParseMachineStatementList();
	bool ParseMachineStatement(int& cookie);
	bool ParseChainStatementList();
	bool ParseChainStatement(int& cookie);
	bool ParseLoopStatementList();
	bool ParseLoopStatement(int& cookie);
	bool ParseAtomStatementList();
	bool ParseAtom(PathIdentifier& id);
	bool ParseAtomExpressionStatement();
	
	bool ParseWorld();
	bool ParseSystem();
	bool ParseEntity();
	bool ParseComponent();
	bool ParseWorldStatementList();
	bool ParseWorldStatement(int& cookie);
	bool ParseSystemStatementList();
	bool ParseSystemStatement(int& cookie);
	bool ParsePoolStatementList();
	bool ParsePoolStatement(int& cookie);
	bool ParseEntityStatementList();
	bool ParseEntityStatement(int& cookie);
	bool ParseComponentStatementList();
	bool ParseComponentStatement(int& cookie);
	bool ParseExpressionList();
	
	bool ParseState();
	bool ParseDeclExpr(bool meta, const PathIdentifier& type_id, AstNode& tn);
	bool ParseMeta(int& cookie);
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
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
	
public:
	void PushRvalConstant(const FileLocation& loc, bool v);
	void PushRvalConstant(const FileLocation& loc, int32 v);
	void PushRvalConstant(const FileLocation& loc, int64 v);
	void PushRvalConstant(const FileLocation& loc, double v);
	void PushRvalConstant(const FileLocation& loc, String v);
	
	void PushWorld(const FileLocation& loc, const PathIdentifier& name);
	void PopWorld(const FileLocation& loc);
	AstNode* PushClass(const FileLocation& loc, const PathIdentifier& name);
	void PopClass(const FileLocation& loc);
	AstNode* PushFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name);
	AstNode* PushMetaFunction(const FileLocation& loc, AstNode& ret_type, const PathIdentifier& name);
	void Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name);
	void MetaParameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name);
	void PopFunctionDefinition(const FileLocation& loc);
	void PopFunction(const FileLocation& loc);
	void PopMetaFunction(const FileLocation& loc);
	void PushStatementList(const FileLocation& loc);
	void PopStatementList(const FileLocation& loc);
	AstNode* PushStatement(const FileLocation& loc, StmtType type);
	void PopStatement(const FileLocation& loc, AstNode* rval);
	AstNode* PushConstructor(const FileLocation& loc, bool meta, AstNode& type, AstNode* var);
	void PopConstructor(const FileLocation& loc);
	void PushStatementParameter(const FileLocation& loc, StmtParamType t);
	void PopStatementParameter(const FileLocation& loc);
	AstNode* DeclareVariable(const FileLocation& loc, AstNode& type, const PathIdentifier& name);
	void DeclareMetaVariable(const FileLocation& loc, AstNode& type, const PathIdentifier& name);
	void Variable(const FileLocation& loc, const AstNode& n, const PathIdentifier& id);
	void PushRvalResolve(const FileLocation& loc, const PathIdentifier& id, SemanticType t);
	void PushRvalUnresolved(const FileLocation& loc, const PathIdentifier& id, SemanticType t);
	AstNode* PushRvalArgumentList(const FileLocation& loc);
	void Argument(const FileLocation& loc);
	AstNode* ArraySize(const FileLocation& loc);
	AstNode* PopExpr(const FileLocation& loc);
	void PushRval(const FileLocation& loc, AstNode& n);
	void PushRvalConstruct(const FileLocation& loc, AstNode& n);
	void PushRvalConstant(const FileLocation& loc, const Token& t);
	void Expr1(const FileLocation& loc, OpType op);
	void Expr2(const FileLocation& loc, OpType op);
	void Expr3(const FileLocation& loc, OpType op);
	void PushSystem(const FileLocation& loc, const PathIdentifier& id);
	void PopSystem(const FileLocation& loc);
	void PushPool(const FileLocation& loc, const PathIdentifier& id);
	void PopPool(const FileLocation& loc);
	void PushEntity(const FileLocation& loc, const PathIdentifier& id);
	void PopEntity(const FileLocation& loc);
	void PushComponent(const FileLocation& loc, const PathIdentifier& id);
	void PopComponent(const FileLocation& loc);
	void PushMachine(const FileLocation& loc, const PathIdentifier& id);
	void PopMachine(const FileLocation& loc);
	void PushChain(const FileLocation& loc, const PathIdentifier& id);
	void PopChain(const FileLocation& loc);
	AstNode* PushLoop(const FileLocation& loc, const PathIdentifier& id);
	void PopLoop(const FileLocation& loc);
	AstNode* PushAtom(const FileLocation& loc, const PathIdentifier& id);
	void PopAtom(const FileLocation& loc);
	AstNode* AddEmptyAtomConnector(const FileLocation& loc, int part);
	AstNode* PushAtomConnector(const FileLocation& loc, int part);
	void PopAtomConnector(const FileLocation& loc);
	void PushState(const FileLocation& loc, const PathIdentifier& id);
	void PopState(const FileLocation& loc);
	void PushCall(const FileLocation& loc);
	void PopCall(const FileLocation& loc);
	void PopExprCallArgument(const FileLocation& loc, int arg_i);
	void PopRvalLink(const FileLocation& loc);
	AstNode* PartialMetaResolve(const FileLocation& loc, const PathIdentifier& id, SemanticType t);
	
};


NAMESPACE_TOPSIDE_END

#endif
