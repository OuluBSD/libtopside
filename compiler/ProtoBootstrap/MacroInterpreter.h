#ifndef _Meta_MacroInterpreter_h_
#define _Meta_MacroInterpreter_h_

NAMESPACE_TOPSIDE_BEGIN
using namespace Upp;


class MacroInterpreter : public ErrorSource {
	
protected:
	friend class Make;
	friend class Parser;
	
	
	const Vector<Token>* tk = NULL;
	String file_path;
	int cursor = 0;
	
	Vector<int> cond_stack;
	Vector<const Token*> cond_directive_stack;
	int line_diff = 0;
	String error_file;
	
	bool have_cpp = false;
	
	const Token& Get() {const auto& t = *tk; if (cursor >= t.GetCount()) throw Exc(t_("Unexpected end of file")); return t[cursor];}
	MacroInterpreter& Next() {cursor++; return *this;}
	MacroInterpreter& Previous() {cursor--; return *this;}
	bool IsEnd() {const auto& t = *tk; return cursor >= t.GetCount();}
	void Assert(int tk, String msg) {if (!Get().IsType(tk)) throw Exc(msg);}
	void AssertPathToken(String msg);
	Node& Add(int node_type) {Node& n = root.AddType(node_type); return n;}
	bool GetSubExprValue(Vector<Token>& subexpr);
	void LoadSubExpr(Vector<Token>& subexpr);
	void Push(bool value, const Token& directive);
	void Pop();
	int& Top();
	void SeekElseElifEndif();
	int Line(int orig_line) {return orig_line + line_diff;}
	int Line() {return Line(Get().loc.line);}
	bool ReadMacroArgument(const Vector<Token>& src, int& cursor, Vector<Token>& dst);
	void ReplaceIds(Vector<Token>& replaced, const VectorMap<String, Vector<Token> >& replacing);
	Token ProcessNonMacroId(const Token& tk);
	
	void Error(String msg, int line, int col);
	void Error(String msg) {Error(msg, Get().loc.line, Get().loc.col);}
	void Warning(String msg, int line, int col);
	void Warning(String msg) {Warning(msg, Get().loc.line, Get().loc.col);}
	
public:
	MacroInterpreter();
	
	void SetSource(const Vector<Token>& tokens) {tk = &tokens;}
	
	bool Process();
	Node* GetOutput() {return &root;}
	
	bool ProcessTokenizer();
	
	void Dump() {LOG(NodeTreeStringSimple(root));}
	
	Node root;
};


NAMESPACE_TOPSIDE_END


#endif
