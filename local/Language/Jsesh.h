#ifndef _Language_Jsesh_h_
#define _Language_Jsesh_h_

NAMESPACE_LANGUAGE_BEGIN

enum {
	JSESH_UNKNOWN,
	JSESH_NEWLINE,
	JSESH_SETTING,
	JSESH_ENDTAG,
	JSESH_LATIN,
	JSESH_LATINBOLD,
	JSESH_LATINITALIC,
	JSESH_TRANSLITERATION,
	JSESH_SEPARATOR,
	JSESH_VERTGROUP,
	JSESH_HORZGROUP,
	JSESH_PARENTHESIS_BEGIN,
	JSESH_PARENTHESIS_END,
	JSESH_LINE_END,
	JSESH_TEXT,
	JSESH_CARTOUCHE_BEGIN,
	JSESH_CARTOUCHE_END,
	JSESH_FULL_SPACE,
	JSESH_HALF_SPACE,
};

class JseshLexer : public Lexer {
	int line = 0, col = 0;
	
	void Add(int token) {Token& t = tokens.Add(); t.type = token; t.l = line; t.c = col;}
	void AppendText(int chr) {if (tokens.GetCount() && tokens.Top().IsType(JSESH_TEXT)) tokens.Top().Cat(chr); else tokens.Add().SetType(JSESH_TEXT).Cat(chr);}
	
	
public:
	JseshLexer();
	
	virtual bool Tokenize(WString txt);
	virtual String GetTypeString(int type);
	
};

class JseshParser : public Parser {
	JseshLexer l;
	
	int cursor = 0;
	Node root;
	Vector<Node*> scope;
	
	
	
	void ParseStatement();
	
	bool IsEnd() const {return cursor >= l.GetCount();}
	const Token& Get() const {return l.Get(cursor);}
	void Type(int tk);
	bool PassEmpty();
	bool PassType(int tk);
	bool IsType(int tk) {if (IsEnd()) return false; return l.Get(cursor).type == tk;}
	Node& Top() {return *scope.Top();}
	Node& PushScope(Node* n) {return *scope.Add(n);}
	Node& PushScope(int node_type);
	void PopScope();
	void AppendText();
	
	Node* LsideStatement();
	Node* Parenthesis();
	Node* VertGroup();
	Node* HorzGroup();
	Node* Id();
	
	void SolveSigns(Node& n);
	void SolveWords(Node& n, int depth);
	bool GetSignList(Node& n, int begin, Vector<Node*>& sign_list, int depth);
	bool CheckReplaceWord(Node& n, int begin);
	
public:
	JseshParser();
	
	virtual bool Parse(WString txt);
	
	void DumpRoot();
	void DumpTokens();
};


NAMESPACE_LANGUAGE_END

#endif
