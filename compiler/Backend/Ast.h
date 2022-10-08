#ifndef _Backend_Ast_h_
#define _Backend_Ast_h_

NAMESPACE_TOPSIDE_BEGIN


class SemanticParser;
class EonStd;


class AstNode : public CompilerNode<AstNode,NodeBase> {
	
public:
	static const int ARG_COUNT = 4;
	
	//AstNode* cur = 0;
	const AstNode* prev = 0;
	//AstNode* next = 0;
	//Object* next_obj = 0;
	AstNode* type = 0;
	AstNode* arg[ARG_COUNT] = {0,0,0,0};
	AstNode* rval = 0;
	AstNode* ctx_next = 0;
	mutable bool locked = false;
	Object obj;
	
	Array<AstNode> sub;
	String name;
	SemanticType src = SEMT_NULL;
	StmtType stmt = STMT_NULL;
	OpType op = OP_NULL;
	ConstType con = CONST_NULL;
	SemanticType filter = SEMT_NULL;
	FileLocation loc;
	PathIdentifier id;
	
	union {
		int64 i64;
		double dbl;
	};
	String str;
	//Vector<String> path;
	
public:
	typedef AstNode CLASSNAME;
	AstNode();
	
	void			Clear() {sub.Clear();}
	void			CopyFrom(EonStd* e, const AstNode& n);
	void			CopyFromObject(const FileLocation& loc, const Object& n);
	void			CopyToObject(Object& n) const;
	//void			CopyPrevNextLinks();
	
	AstNode&		Add(const FileLocation& loc, String name="", int idx=-1);
	AstNode&		GetAdd(const FileLocation& loc, String name="");
	AstNode&		GetAdd(const FileLocation& loc, SemanticType accepts);
	AstNode*		Find(String name, SemanticType accepts=SEMT_NULL);
	const AstNode*	Find(String name, SemanticType accepts=SEMT_NULL) const;
	AstNode*		FindPartial(SemanticType t);
	AstNode*		Find(SemanticType t);
	const AstNode*	Find(SemanticType t) const;
	String			GetConstantString() const;
	AstNode*		FindWithPrevDeep(const AstNode* prev);
	void			FindAll(Vector<AstNode*>& ptrs, SemanticType accepts);
	void			FindAllStmt(Vector<AstNode*>& ptrs, StmtType accepts);
	void			FindAllNonIdEndpoints(Vector<AstNode*>& ptrs, SemanticType accepts=SEMT_NULL);
	void			FindAllNonIdEndpoints0(Vector<AstNode*>& ptrs, SemanticType accepts=SEMT_NULL);
	
	String			GetTreeString(int indent, bool links) const;
	String			GetTreeString(int indent=0) const override;
	String			GetCodeString(const CodeArgs& args) const override;
	String			ToString() const override;
	String			GetName() const override {return name;}
	String			GetPath() const override;
	String			GetPartStringArray() const;
	SemanticType	GetSemanticType() const {return src;}
	bool			IsPartially(SemanticType t) const {return (SemanticTypePrimitive)src & (SemanticTypePrimitive)t;}
	bool			IsStmtPartially(StmtType t) const {return src == SEMT_STATEMENT && ((SemanticTypePrimitive)stmt & (SemanticTypePrimitive)t);}
	
};

struct AstNodeLess {
	bool operator()(const AstNode* a, const AstNode* b) const {
		return a->loc < b->loc;
	}
};

NAMESPACE_TOPSIDE_END

#endif
