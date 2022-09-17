#ifndef _Backend_Ast_h_
#define _Backend_Ast_h_

NAMESPACE_TOPSIDE_BEGIN


class SemanticParser;

class AstNode : public CompilerNode<AstNode,NodeBase> {
	
public:
	static const int LINK_COUNT = 4;
	
	AstNode* prev = 0;
	AstNode* next = 0;
	Object* next_obj = 0;
	AstNode* type = 0;
	AstNode* link[LINK_COUNT] = {0,0,0,0};
	bool locked = false;
	
	Array<AstNode> sub;
	String name;
	SemanticType src = SEMT_NULL;
	StmtType stmt = STMT_NULL;
	OpType op = OP_NULL;
	ConstType con = CONST_NULL;
	SemanticType filter = SEMT_NULL;
	FileLocation loc;
	
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
	void			CopyFrom(const AstNode& n);
	
	AstNode&		Add(const FileLocation& loc, String name="", int idx=-1);
	AstNode&		GetAdd(const FileLocation& loc, String name="");
	AstNode&		GetAdd(const FileLocation& loc, SemanticType accepts);
	AstNode*		Find(String name, SemanticType accepts=SEMT_NULL);
	const AstNode*	Find(String name, SemanticType accepts=SEMT_NULL) const;
	AstNode*		Find(SemanticType t);
	const AstNode*	Find(SemanticType t) const;
	String			GetConstantString() const;
	
	String			GetTreeString(int indent=0) const override;
	String			GetCodeString(const CodeArgs& args) const override;
	String			ToString() const override;
	String			GetName() const override {return name;}
	String			GetPath() const override;
	String			GetPartStringArray() const;
	SemanticType	GetSemanticType() const {return src;}
	bool			IsPartially(SemanticType t) const {return (SemanticTypePrimitive)src & (SemanticTypePrimitive)t;}
	
};


NAMESPACE_TOPSIDE_END

#endif
