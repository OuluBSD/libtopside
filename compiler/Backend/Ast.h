#ifndef _Backend_Ast_h_
#define _Backend_Ast_h_

NAMESPACE_TOPSIDE_BEGIN


class SemanticParser;

class AstNode : public CompilerNode<AstNode,NodeBase> {
	
public:
	Array<AstNode> sub;
	String name;
	SemanticType src = SEMT_NULL;
	AstNode* type = 0;
	AstNode* link[4] = {0,0,0,0};
	bool locked = false;
	
	StmtType stmt = STMT_NULL;
	OpType op = OP_NULL;
	ConstType con = CONST_NULL;
	SemanticType filter = SEMT_NULL;
	
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
	
	AstNode&		Add(String name="", int idx=-1);
	AstNode&		GetAdd(String name="");
	AstNode&		GetAdd(SemanticType accepts);
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
