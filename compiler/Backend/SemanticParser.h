#ifndef _Backend_SemanticParser_h_
#define _Backend_SemanticParser_h_

NAMESPACE_TOPSIDE_BEGIN


class SemanticParser;

class SemanticNode : public CompilerNode<SemanticNode,TokenStructure> {
	
public:
	Array<SemanticNode> sub;
	String name;
	ClassSource src = CLSRC_NULL;
	
public:
	typedef SemanticNode CLASSNAME;
	SemanticNode();
	
	void			Clear() {sub.Clear();}
	
	SemanticNode&	Add(String name="");
	SemanticNode*	Find(String name);
	
	String			GetTreeString(int indent=0) const override;
	String			GetCodeString(const CodeArgs& args) const override;
	String			ToString() const override;
	String			GetName() const override {return name;}
	
};


struct ParserEmitter {
	
	
	virtual void PushFunction(SemanticNode& ret_type, const PathIdentifier& name) {}
	virtual void Parameter(const PathIdentifier& type, const PathIdentifier& name) {}
	virtual void PushFunctionDefinition() {}
	virtual void PopFunctionDefinition() {}
	virtual void PopFunction() {}
	virtual void PushStatementList() {}
	virtual void PopStatementList() {}
	virtual void PushStatement(StmtType type) {}
	virtual void PopStatement() {}
	
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
		bool Check(const TokenNode& n) const {return node == &n && begin <= iter && iter <= end && n.begin == begin && n.end == end;}
		void operator++(int i) {iter++; ASSERT(iter <= end);}
		void operator++() {++iter; ASSERT(iter <= end);}
	};
	Array<Iterator> iters;
	ParserEmitter* emitter = 0;
	
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
	bool PassToken(int tk_type);
	bool PassId(const char* s);
	bool IsToken(int tk_type) const;
	bool TryToken(int tk_type);
	bool IsChar(int tk_type) const {return IsToken(tk_type);}
	bool IsChar2(int a, int b) const;
	bool Char2(int a, int b);
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
	bool DoCompare(const char *op);
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
