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
	
public:
	typedef AstNode CLASSNAME;
	AstNode();
	
	void			Clear() {sub.Clear();}
	
	AstNode&		Add(String name="");
	AstNode&		GetAdd(String name="");
	AstNode*		Find(String name);
	
	String			GetTreeString(int indent=0) const override;
	String			GetCodeString(const CodeArgs& args) const override;
	String			ToString() const override;
	String			GetName() const override {return name;}
	String			GetPath() const override;
	String			GetPartStringArray() const;
	
};


NAMESPACE_TOPSIDE_END

#endif
