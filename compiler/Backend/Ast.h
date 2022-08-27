#ifndef _Backend_Ast_h_
#define _Backend_Ast_h_

NAMESPACE_TOPSIDE_BEGIN


class SemanticParser;

class AstNode : public CompilerNode<AstNode,NodeBase> {
	
public:
	Array<AstNode> sub;
	String name;
	SemanticType src = SEMT_NULL;
	StmtType stmt = STMT_NULL;
	AstNode* type = 0;
	AstNode* link[4] = {0,0,0,0};
	OpType op = OP_NULL;
	bool locked = false;
	
	ConstType con = CONST_NULL;
	union {
		int64 i64;
		double dbl;
	};
	String str;
	
public:
	typedef AstNode CLASSNAME;
	AstNode();
	
	void			Clear() {sub.Clear();}
	
	AstNode&		Add(String name="");
	AstNode&		GetAdd(String name="");
	AstNode*		Find(String name);
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
