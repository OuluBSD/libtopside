#ifndef _Backend_AstExporter_h_
#define _Backend_AstExporter_h_

NAMESPACE_TOPSIDE_BEGIN


struct AstExporterLanguage {
	
	
};


void InitHighExporter(AstExporterLanguage& l);
void InitCppExporter(AstExporterLanguage& l);

class AstExporter :
	public ErrorSource
{
	struct Scope {
		const AstNode* n = 0;
		bool pop_this = false;
		bool skip_indent = false;
	};
	struct InlineScope {
		int count = 0;
	};
	
	String output;
	Array<Scope> scopes;
	Array<InlineScope> inline_scopes;
	int indent = 0;
	bool inline_mode = false;
	
	void VisitLoop(const AstNode& n);
	void VisitFunction(const AstNode& n);
	void VisitParameter(const AstNode& n);
	void VisitStatement(const AstNode& n);
	void VisitExpression(const AstNode& n, int depth);
	void VisitVariable(const AstNode& n, bool declare=false);
	void VisitArgument(const AstNode& n);
	void VisitConstant(const AstNode& n);
	void VisitResolve(const AstNode& n, bool rval=false);
	void VisitRval(const AstNode& n);
	void VisitArgumentList(const AstNode& n);
	void VisitFunctionRval(const AstNode& n);
	void VisitConstructor(const AstNode& n);
	void VisitArraySize(const AstNode& n);
	void PushScope(const AstNode& n, bool skip_indent=false);
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
	
	
	void Visit(const AstNode& n, bool force=false, bool declare=false);
	void Visit(const AstNode& n, SemanticType t);
	void VisitStmt(const AstNode& n, StmtType t);
	void VisitBuiltin(const AstNode& n);
	void VisitCtorExpr(const AstNode& n);
	
	
	
	AstExporterLanguage lang;
	
};


NAMESPACE_TOPSIDE_END

#endif
