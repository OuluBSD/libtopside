#ifndef _Backend_AstExporter_h_
#define _Backend_AstExporter_h_

NAMESPACE_TOPSIDE_BEGIN


class AstExporter :
	public ErrorSource
{
	struct Scope {
		const AstNode* n = 0;
		bool pop_this = false;
	};
	struct InlineScope {
		int count = 0;
	};
	
	String output;
	Array<Scope> scopes;
	Array<InlineScope> inline_scopes;
	int indent = 0;
	bool inline_mode = false;
	
	void VisitFunction(const AstNode& n);
	void VisitParameter(const AstNode& n);
	void VisitStatement(const AstNode& n);
	void VisitExpression(const AstNode& n, int depth);
	void VisitVariable(const AstNode& n);
	void VisitArgument(const AstNode& n);
	void VisitConstant(const AstNode& n);
	void VisitResolve(const AstNode& n);
	void VisitArgumentList(const AstNode& n);
	void VisitFunctionRval(const AstNode& n);
	void PushScope(const AstNode& n);
	void PopScope();
	void PushInlineScope();
	void PopInlineScope();
	
	String GetIndentString(int offset=0) const;
	String GetCPath() const;
	String GetCPath(const AstNode& n) const;
	
public:
	typedef AstExporter CLASSNAME;
	AstExporter();
	
	bool Process(const AstNode& n);
	
	String GetResult() const {return output;}
	
	
	void Visit(const AstNode& n);
	void Visit(const AstNode& n, SemanticType t);
	void VisitStmt(const AstNode& n, StmtType t);
	
};


NAMESPACE_TOPSIDE_END

#endif
