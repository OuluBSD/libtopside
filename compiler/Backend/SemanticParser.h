#ifndef _Backend_SemanticParser_h_
#define _Backend_SemanticParser_h_

NAMESPACE_TOPSIDE_BEGIN


class SemanticParser;

class SemanticNode : public CompilerNode<SemanticNode,TokenStructure> {
	
public:
	Array<SemanticNode> sub;
	String name;
	SemanticType src = SEMT_NULL;
	SemanticNode* type = 0;
	
public:
	typedef SemanticNode CLASSNAME;
	SemanticNode();
	
	void			Clear() {sub.Clear();}
	
	SemanticNode&	Add(String name="");
	SemanticNode&	GetAdd(String name="");
	SemanticNode*	Find(String name);
	
	String			GetTreeString(int indent=0) const override;
	String			GetCodeString(const CodeArgs& args) const override;
	String			ToString() const override;
	String			GetName() const override {return name;}
	String			GetPath() const override;
	String			GetPartStringArray() const;
	
};


struct ParserEmitter {
	
	
	virtual void PushFunction(const FileLocation& loc, SemanticNode& ret_type, const PathIdentifier& name) {}
	virtual void Parameter(const FileLocation& loc, const PathIdentifier& type, const PathIdentifier& name) {}
	virtual void PushFunctionDefinition(const FileLocation& loc) {}
	virtual void PopFunctionDefinition(const FileLocation& loc) {}
	virtual void PopFunction(const FileLocation& loc) {}
	virtual void PushStatementList(const FileLocation& loc) {}
	virtual void PopStatementList(const FileLocation& loc) {}
	virtual void PushStatement(const FileLocation& loc, StmtType type) {}
	virtual void PopStatement(const FileLocation& loc) {}
	virtual void BindStatementParameter(const FileLocation& loc, StmtParamType t) {}
	virtual void DeclareVariable(const FileLocation& loc, const SemanticNode& n, const PathIdentifier& id) {}
	virtual void Variable(const FileLocation& loc, const SemanticNode& n, const PathIdentifier& id) {}
	//virtual void PushExprScope() {}
	virtual void PopExprScopeToCtor(const FileLocation& loc) {}
	//virtual void PushCall(const PathIdentifier& id) {}
	//virtual void PopCall() {}
	//virtual void PushExprScopeRval() {}
	virtual void PushRvalCall(const FileLocation& loc, const SemanticNode& n) {}
	virtual void PushRvalConstruct(const FileLocation& loc, const SemanticNode& n) {}
	virtual void PopExpr(const FileLocation& loc) {}
	virtual void PushRval(const FileLocation& loc, const SemanticNode& n) {}
	virtual void PushRvalConstant(const FileLocation& loc, const Token& t) {}
	virtual void Expr1(const FileLocation& loc, OpType op) {}
	virtual void Expr2(const FileLocation& loc, OpType op) {}
	virtual void Expr3(const FileLocation& loc, OpType op) {}
	
};


class SemanticParser :
	public CompilerNode<SemanticParser,NodeBase>,
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
	ParserEmitter* emitter = 0;
	
	
	struct Scope : Moveable<Scope> {
		SemanticNode* n;
		bool pop_this;
		
		void Set(SemanticNode* sn, bool b) {n = sn; pop_this = b;}
	};
	Vector<Scope> spath;
	
	
	void PushScope(SemanticNode& n);
	void PopScope();
	
	String GetPath(const SemanticNode& n) const;
	
public:
	SemanticNode root;
	Array<const TokenNode*> path;
	
	void SetEmitter(ParserEmitter& e) {emitter = &e;}
	void AddBuiltinType(String name);
	
	const TokenNode& CurrentNode() {return *path.Top();}
	bool Id(const char* s);
	Iterator& AddIterator(const TokenNode& n);
	Iterator& TopIterator();
	const Iterator& TopIterator() const;
	void PopIterator();
	SemanticNode* FindDeclaration();
	SemanticNode* FindDeclaration(const PathIdentifier& id);
	SemanticNode& DeclareRelative(const PathIdentifier& id);
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
	
	void InitDefault();
	bool ProcessEon(const TokenStructure& t);
	bool ParseNamespaceBlock();
	bool ParseDeclaration();
	bool ParseClass();
	bool ParseTypedDeclaration(SemanticNode& ret_type);
	bool ParseFunction(SemanticNode& ret_type, const PathIdentifier& name);
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
