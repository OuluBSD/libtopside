#ifndef _Language_Lexer_h_
#define _Language_Lexer_h_

NAMESPACE_LANGUAGE_BEGIN


inline bool IsSpaceString(const WString& ws) {
	for(int i = 0; i < ws.GetCount(); i++) {
		int chr = ws[i];
		if (chr != ' ' && chr != '\t' && chr != '\r' && chr != '\n')
			return false;
	}
	return true;
}


struct Token : Moveable<Token> {
	int type = 0;
	int int_value=0;
	WString str_value;
	int l = 0, c = 0;
	
	Token& SetInt(int i) {int_value = i; return *this;}
	
	int GetInt() const {return int_value;}
	WString GetString() const {return str_value;}
	bool IsType(int type) const {return type == this->type;}
	Token& Cat(int chr) {str_value.Cat(chr); return *this;}
	Token& SetType(int type) {this->type = type; return *this;}
	
};


class Lexer {
	
protected:
	Vector<Token> tokens;
	
public:
	
	virtual bool Tokenize(WString txt) = 0;
	virtual String GetTypeString(int type) = 0;
	
	String DumpTokens();
	
	const Token& Get(int i) const {return tokens[i];}
	Token& ForceGet(int i) {return tokens[i];}
	int GetCount() const {return tokens.GetCount();}
	
};


NAMESPACE_LANGUAGE_END

#endif
