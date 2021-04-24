#ifndef _Meta_Common_h_
#define _Meta_Common_h_

#if 0

NAMESPACE_OULU_BEGIN

enum {
	LVL_INFO,
	LVL_WARNING,
	LVL_ERROR,
};

struct Message : Moveable<Message> {
	int source, file, line, col;
	int severity;
	String what;
	
	
	void Set(int src, int f, int l, int c, int s, String w) {source = src; file = f; line = l; col = c; severity = s; what = w;}
};

inline Index<String>& GetFileMap() {static Index<String> v; return v;}



enum {
	TK_UNKNOWN,
	TK_ID,
	TK_INTEGER,
	TK_FLOAT,
	TK_DOUBLE,
	TK_EXCLAMATION,
	TK_STRING,
	TK_NUMBERSIGN,
	TK_PERCENT,
	TK_AMPERSAND,
	TK_DIV, // 10
	TK_BRACKET_BEGIN,
	TK_BRACKET_END,
	TK_PARENTHESIS_BEGIN,
	TK_PARENTHESIS_END,
	TK_SQUARE_BEGIN,
	TK_SQUARE_END,
	TK_EQ,
	TK_QUESTION,
	TK_PLUS, // 20
	TK_SOLIDUS,
	TK_ACCENT,
	TK_TILDE,
	TK_MUL,
	TK_CHAR,
	TK_OR,
	TK_MINUS,
	TK_SEMICOLON,
	TK_COMMA, // 30
	TK_PUNCT,
	TK_COLON,
	TK_LESS,
	TK_GREATER,
	TK_NEWLINE,
	TK_BLOCK_COMMENT,
	TK_COMMENT,
	TK_HEX,
	TK_OCT,
	TK_DOLLARSIGN,
	TK_INVALID,
	TK_EOF,
};

String EscapeString(String s);
String EscapeSpecial(String s);

struct Token : Moveable<Token> {
	int type = 0;
	String str_value;
	int file = 0, line = 0, col = 0;
	int spaces = 0;
	
	Token() {}
	Token(const Token& t) {*this = t;}
	void operator=(const Token& t) {type = t.type; str_value = t.str_value; file = t.file; line = t.line; col = t.col; spaces = t.spaces;}
	bool operator==(const Token& t) const {return t.type == type && t.str_value == str_value && t.file == file && t.line == line && t.col == col && t.spaces == spaces;}
	bool operator!=(const Token& t) const {return !(t == *this);}
	bool IsType(int i) const {return type == i;}
	String GetString() const {return str_value;}
	String GetTypeString() const {
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
			case TK_EQ: return "equal";
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
			case TK_HEX: return "hex-number";
			case TK_OCT: return "oct-number";
			case TK_INVALID: return "invalid";
			case TK_EOF: return "end-of-file";
		}
		return "";
	}
	String ToString() const {
		String s = GetTypeString() + ": " + EscapeSpecial(GetTextValue());
		return s;
	}
	String GetTextValue() const {
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
			case TK_EQ: return "=";
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
			case TK_HEX: return str_value;
			case TK_OCT: return str_value;
			case TK_DOLLARSIGN: return "$";
			case TK_EOF: return "EOF";
			default: Panic("Unhandled token type");
		}
		return "";
	}
};



class ErrdgfhdorSource {
	int src = 0;
	String error_path;
	
protected:
	friend class TracerProc;
	
	
	bool succ = true;
	
	void SetErrorPath(String path) {error_path = path;}
	void Info(String msg, int file, int line, int col);
	void Warning(String msg, int file, int line, int col);
	void Error(String msg, int file, int line, int col);
	
	void SetSrc(int i) {src = i;}
	
public:
	ErrorSource(int src) : src(src) {}
	
	bool IsSrc(int i) const {return src == i;}
	
	Callback1<Message*> WhenMessage;
};






NAMESPACE_OULU_END

#endif
#endif
