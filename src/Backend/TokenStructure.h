#ifndef _Backend_TokenStructure_h_
#define _Backend_TokenStructure_h_

NAMESPACE_TOPSIDE_BEGIN

class TokenStructure;

class TokenNode : public CompilerNode<TokenNode,TokenStructure> {
	
public:
	Array<TokenNode> sub;
	const Token* begin = 0;
	const Token* end = 0;
	
public:
	typedef TokenNode CLASSNAME;
	TokenNode();
	
	void		Clear() {sub.Clear();}
	
	TokenNode&	Add();
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};

class TokenStructure :
	public CompilerNode<TokenNode,NodeBase>,
	public ErrorSource {
	
	
public:
	TokenNode root;
	
	// Temp
	const Token *iter, *end;
	bool IsEnd() const {ASSERT(iter <= end); return iter == end;}
	
public:
	typedef TokenStructure CLASSNAME;
	TokenStructure();
	
	bool ProcessEon(const Tokenizer& t);
	bool ParseBlock(TokenNode& n);
	bool ParseStatement(TokenNode& n, bool break_comma);
	
	bool PassType(int tk);
	const Token& Current() {ASSERT(iter <= end); return *iter;}
	bool Next() {return ++iter != end;}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END

#endif
