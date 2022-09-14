#ifndef _Local_Tokenizer_h_
#define _Local_Tokenizer_h_

NAMESPACE_TOPSIDE_BEGIN


enum {
	TK_UNKNOWN,
	
	TK_EXCLAMATION = '!',
	TK_NUMBERSIGN = '#',
	TK_PERCENT = '%',
	TK_AMPERSAND = '&',
	TK_DIV = '/',
	TK_BRACKET_BEGIN = '{',
	TK_BRACKET_END = '}',
	TK_PARENTHESIS_BEGIN = '(',
	TK_PARENTHESIS_END = ')',
	TK_SQUARE_BEGIN = '[',
	TK_SQUARE_END = ']',
	TK_ASS = '=',
	TK_QUESTION = '?',
	TK_PLUS = '+',
	TK_SOLIDUS = '\\',
	TK_ACCENT = '^',
	TK_TILDE = '~',
	TK_MUL = '*',
	TK_AT = '@',
	TK_OR = '|',
	TK_MINUS = '-',
	TK_SEMICOLON = ';',
	TK_COMMA = ',',
	TK_PUNCT = '.',
	TK_COLON = ':',
	TK_LESS = '<',
	TK_GREATER = '>',
	TK_NEWLINE = '\n',
	TK_DOLLARSIGN = '$',
	
	TK_NONCHAR_BEGIN	= 1000,
	TK_ID				= 1000,
	TK_INTEGER,
	TK_HEX,
	TK_OCT,
	TK_FLOAT,
	TK_DOUBLE,
	TK_STRING,
	TK_CHAR,
	TK_BLOCK_COMMENT,
	TK_COMMENT,
	TK_INDENT,
	TK_DEDENT,
	TK_INVALID,
	TK_END_STMT,
	
	// Combined tokens (not enabled by default)
	TK_INC,
	TK_DEC,
	TK_LSHIFT,
	TK_RSHIFT,
	TK_EQ,
	TK_LSEQ,
	TK_GREQ,
	TK_INEQ,
	TK_LOGAND,
	TK_LOGOR,
	TK_MULASS,
	TK_DIVASS,
	TK_MODASS,
	TK_ADDASS,
	TK_SUBASS,
	TK_ANDASS,
	TK_XORASS,
	TK_ORASS,
	TK_LSHIFTASS,
	TK_RSHIFTASS,
	
	TK_EOF = 100000,
	TK_COMBINED2_BEGIN = TK_INC,
	TK_COMBINED3_BEGIN = TK_LSHIFTASS,
};

struct Token : Moveable<Token> {
	FileLocation loc, end;
	int type = 0;
	String str_value;
	int spaces = 0;
	
	Token() {}
	Token(const Token& t) {*this = t;}
	void Clear() {loc.Clear(); end.Clear(); type = 0; str_value.Clear(); spaces = 0;}
	void operator=(const Token& t) {type = t.type; str_value = t.str_value; loc = t.loc; end = t.end; spaces = t.spaces;}
	bool operator==(const Token& t) const {return t.type == type && t.str_value == str_value && t.loc == loc && end == t.end && t.spaces == spaces;}
	bool operator!=(const Token& t) const {return !(t == *this);}
	bool IsType(int i) const {return type == i;}
	String GetString() const {return str_value;}
	String GetTypeString() const {return GetTypeStringStatic(type);}
	static String GetTypeStringStatic(int type) {
		switch (type) {
			case TK_UNKNOWN: return "<unknown>";
			case TK_ID: return "id";
			case TK_INTEGER: return "integer";
			case TK_FLOAT: return "float";
			case TK_DOUBLE: return "double";
			case TK_EXCLAMATION: return "exclamation";
			case TK_STRING: return "string";
			case TK_NUMBERSIGN: return "number-sign";
			case TK_PERCENT: return "percent";
			case TK_AMPERSAND: return "ampersand";
			case TK_DIV: return "divide";
			case TK_BRACKET_BEGIN: return "bracket-begin";
			case TK_BRACKET_END: return "bracket-end";
			case TK_PARENTHESIS_BEGIN: return "parenthesis-begin";
			case TK_PARENTHESIS_END: return "parenthesis-end";
			case TK_SQUARE_BEGIN: return "square-begin";
			case TK_SQUARE_END: return "square-end";
			case TK_ASS: return "assign";
			case TK_QUESTION: return "question-mark";
			case TK_PLUS: return "plus";
			case TK_SOLIDUS: return "solidus";
			case TK_ACCENT: return "accent";
			case TK_TILDE: return "tilde";
			case TK_MUL: return "multiply";
			case TK_CHAR: return "char";
			case TK_OR: return "or";
			case TK_MINUS: return "minus";
			case TK_SEMICOLON: return "semicolon";
			case TK_COMMA: return "comma";
			case TK_PUNCT: return "punct";
			case TK_COLON: return "colon";
			case TK_LESS: return "less";
			case TK_GREATER: return "greater";
			case TK_NEWLINE: return "newline";
			case TK_BLOCK_COMMENT: return "block-comment";
			case TK_COMMENT: return "comment";
			case TK_INDENT: return "indent";
			case TK_DEDENT: return "dedent";
			case TK_HEX: return "hex-number";
			case TK_OCT: return "oct-number";
			case TK_INVALID: return "invalid";
			case TK_END_STMT: return "end-statement";
			case TK_EOF: return "end-of-file";
			
			case TK_INC: return "inc";
			case TK_DEC: return "dec";
			case TK_LSHIFT: return "left-shift";
			case TK_RSHIFT: return "right-shift";
			case TK_EQ: return "equal";
			case TK_LSEQ: return "less-or-equal";
			case TK_GREQ: return "greater-or-equal";
			case TK_INEQ: return "inequal";
			case TK_LOGAND: return "logical-and";
			case TK_LOGOR: return "logical-or";
			case TK_MULASS: return "assign-multiplied";
			case TK_DIVASS: return "assign-divided";
			case TK_MODASS: return "assign-modded";
			case TK_ADDASS: return "assign-sum";
			case TK_SUBASS: return "assign-subtracted";
			case TK_ANDASS: return "assign-bitwise-and";
			case TK_XORASS: return "assign-bitwise-xor";
			case TK_ORASS: return "assign-bitwise-or";
			case TK_LSHIFTASS: return "assign-left-shifted";
			case TK_RSHIFTASS: return "assign-right-shifted";
		}
		return "";
	}
	String ToString() const {
		String s = GetTypeString() + ": " + EscapeString(GetTextValue());
		return s;
	}
	String GetTextValue() const {return GetTextValueStatic(type, str_value);}
	static String GetTextValueStatic(int type, String str_value) {
		switch (type) {
			case TK_UNKNOWN: return "";
			case TK_ID: return str_value;
			case TK_INTEGER: return str_value;
			case TK_FLOAT: return str_value;
			case TK_DOUBLE: return str_value;
			case TK_EXCLAMATION: return "!";
			case TK_STRING: return "\"" + EscapeString(str_value) + "\"";
			case TK_NUMBERSIGN: return "#";
			case TK_PERCENT: return "%";
			case TK_AMPERSAND: return "&";
			case TK_BRACKET_BEGIN: return "{";
			case TK_BRACKET_END: return "}";
			case TK_DIV: return "/";
			case TK_PARENTHESIS_BEGIN: return "(";
			case TK_PARENTHESIS_END: return ")";
			case TK_SQUARE_BEGIN: return "[";
			case TK_SQUARE_END: return "]";
			case TK_ASS: return "=";
			case TK_QUESTION: return "?";
			case TK_PLUS: return "+";
			case TK_SOLIDUS: return "\\";
			case TK_ACCENT: return "^";
			case TK_TILDE: return "~";
			case TK_MUL: return "*";
			case TK_CHAR: return "'" + EscapeString(str_value) + "'";
			case TK_OR: return "|";
			case TK_MINUS: return "-";
			case TK_SEMICOLON: return ";";
			case TK_COMMA: return ",";
			case TK_PUNCT: return ".";
			case TK_COLON: return ":";
			case TK_LESS: return "<";
			case TK_GREATER: return ">";
			case TK_NEWLINE: return "\n";
			case TK_BLOCK_COMMENT: return "/* " + str_value + "*/";
			case TK_COMMENT: return "// " + str_value;
			case TK_INDENT: return "<indent>";
			case TK_DEDENT: return "<dedent>";
			case TK_HEX: return str_value;
			case TK_OCT: return str_value;
			case TK_DOLLARSIGN: return "$";
			case TK_END_STMT: return "END-STMT";
			case TK_EOF: return "EOF";
			
			case TK_INC: return "++";
			case TK_DEC: return "--";
			case TK_LSHIFT: return "<<";
			case TK_RSHIFT: return ">>";
			case TK_EQ: return "==";
			case TK_LSEQ: return "<=";
			case TK_GREQ: return ">=";
			case TK_INEQ: return "!=";
			case TK_LOGAND: return "&&";
			case TK_LOGOR: return "||";
			case TK_MULASS: return "*=";
			case TK_DIVASS: return "/=";
			case TK_MODASS: return "%=";
			case TK_ADDASS: return "+=";
			case TK_SUBASS: return "-=";
			case TK_ANDASS: return "&=";
			case TK_XORASS: return "^=";
			case TK_ORASS: return "|=";
			case TK_LSHIFTASS: return "<<=";
			case TK_RSHIFTASS: return ">>=";
			
			default: Panic("Unhandled token type");
		}
		return "";
	}
};

typedef Vector<Token> TokenVec;




class Tokenizer : public ErrorSource {
	FileLocation loc;
	String input;
	bool skip_comments = false;
	bool skip_newlines = false;
	bool skip_separateunary = false;
	bool have_indent_tokens = true;
	int pass_cursor = 0;
	bool parse_indent = false;
	int user_spaces = -1;
	int indent = -1;
	
	int tab_size = 4;
	
	bool ThrowError(String msg) {AddError(loc, msg); return false;}
	
protected:
	
	Vector<Token> tokens;
	
	void Next() {loc.col++; loc.cursor++;}
	Token& Add(int token_id);
	void AppendString(String& s);
	
	
public:
	Tokenizer();
	
	void Load(const Vector<Token>& tokens);
	bool Process(String str, String path);
	void SkipComments(bool b=true) {skip_comments = b;}
	void SkipNewLines(bool b=true) {skip_newlines = b;}
	void SkipSeparateUnary(bool b=true) {skip_separateunary = b;}
	void HaveIdents(bool b=true) {have_indent_tokens = b;}
	void SetTabSize(int i) {tab_size = i;}
	
	void CombineTokens();
	void Dump() const;
	
	const Vector<Token>& GetTokens() const {return tokens;}
	FileLocation GetLocation() const {return loc;}
	
	void Remove(int i) {tokens.Remove(i);}
	//Token& Insert(int i, int type);
	
	int GetPassCursor() const {return pass_cursor;}
	bool PassToken(int tk);
	bool IsToken(int tk);
	bool TryPassToken(int tk);
	bool ReadString(String& s);
	bool ReadId(String& s);
	bool ReadInt(int64& i);
	bool ReadDouble(double& d);
	
	void NewlineToEndStatement();
	
	
};

class TokenizerCParser {
	const Vector<Token>* tokens = NULL;
	int pos = 0;
	
	bool ignore_newline = true;
	
	One<Tokenizer> t;
public:
	typedef TokenizerCParser CLASSNAME;
	TokenizerCParser() {}
	TokenizerCParser(String s) {t.Create(); t->Process(s, "cparser"); Load(t->GetTokens());}
	TokenizerCParser(const Vector<Token>& tokens) {Load(tokens);}
	
	void Load(const Vector<Token>& tokens);
	void IgnoreNewline(bool b);
	
	const Vector<Token>& GetTokens() const {return *tokens;}
	
	void Next() {pos++;}
	const Token& GetCurrent() const;
	bool IsEnd() const;
	int GetTokenCount() const {return tokens ? tokens->GetCount() : 0;}
	int GetTokenPos() const {return pos;}
	FileLocation GetLocation() const;
	
	String ReadId();
	int ReadInt();
	void PassNewline();
	
	bool Id(String id);
	bool Newline();
	bool Type(int i);
	
	bool IsId() const;
	bool IsInt() const;
	bool IsType(int i) const;
	
};


NAMESPACE_TOPSIDE_END

#endif
