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


class SemanticParser :
	public CompilerNode<SemanticParser,NodeBase>,
	public ErrorSource
{
	
	
public:
	SemanticNode root;
	Array<const TokenNode*> path;
	
	void AddBuiltinType(String name);
	
	const TokenNode& CurrentNode() {return *path.Top();}
	
	SemanticNode* FindDeclaration(const Token*& iter, const Token* end);
	bool PassToken(const Token*& iter, int tk_type);
	
public:
	typedef SemanticParser CLASSNAME;
	SemanticParser();
	
	void InitDefault();
	bool ProcessEon(const TokenStructure& t);
	bool ParseNamespaceBlock();
	bool ParseDeclaration();
	bool ParseClass();
	bool ParseTypedDeclaration(SemanticNode& ret_type, const Token*& iter);
	bool ParseFunction(SemanticNode& ret_type, const PathIdentifier& name, const Token*& iter);
	bool ParseStatementList();
	bool ParseStatement();
	bool ParseParameter(SemanticNode& ret_type, const Token*& iter);
	bool ParsePathIdentifier(PathIdentifier& id, const Token*& iter, const Token* end);
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
