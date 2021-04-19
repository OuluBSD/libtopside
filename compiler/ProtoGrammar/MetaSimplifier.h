#ifndef _ProtoGrammar_MetaSimplifier_h_
#define _ProtoGrammar_MetaSimplifier_h_


#ifndef flagBOOTSTRAP

NAMESPACE_OULU_BEGIN


class MetaSimplifier : public ErrorSource {
	#include "Generated_MetaSimplifier.inl"
	
	typedef Array<Ast::Node> NodeVec;
	
	AstResolver& ar;
	const Node* src = NULL;
	RecyclerPool<NodeVec> pool;
	Array<Node> tmp;
	
	
	
	void PushError(String msg);
	bool Visit(const Node& in, NodeVec& out, int* pos, int* type, int count);
	
	Ast::Node* AstCompilationUnit(NodeVec& cont);
	Ast::Node* AstCall(NodeVec& cont);
	Ast::Node* AstCall(NodeVec& id, NodeVec& cont);
	Ast::Node* AstCallArg(NodeVec& pre, NodeVec& pos, NodeVec& cont);
	Ast::Node* AstIdentifier(NodeVec& cont);
	Ast::Node* AstExpressionStatement(NodeVec& cont);
	Ast::Node* AstToken(const Node& n);
	Ast::Node* AstLiteral(const Node& n);
	void       AstBeginStmt();
	
	
	void OnError(String msg);
	
public:
	MetaSimplifier(AstResolver& ar);
	
	bool Process();
	String NodeTreeString(const Node& n, int depth=0, String tab="\t");
	
	void SetSource(const Node& n) {src = &n;}
	const Node& GetOutput() {ASSERT(root); return *root;}
	
	void Dump();
	
	
	One<Node> root;
};

}

#endif

#endif
