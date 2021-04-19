namespace GRAMMAR_NAME {


struct Command : Moveable<Command> {
	String raw;
	int indent = 0;
};

class PostParser : public ErrorSource {
	#include GRAMMAR_FILE
	
	const Node* src = NULL;
	int indent = 0;
	Vector<Command> cmds;
	Vector<Token> tokens;
	int cursor;
	
	bool TestCharLiteral(const Node& n, const char* str);
	bool TestStringLiteral(const Node& n, const char* str);
	void PushCommand(const char* str, int str_len);
	
	void Eof(const Node& n);
	void CharLiteral(const Node& n);
	void StringLiteral(const Node& n);
	void CharList(const Node& n);
	void Identifier(const Node& n);
	
	
public:
	PostParser();
	
	bool Process();
	String NodeTreeString(const Node& n, int depth=0, String tab="\t");
	
	void SetSource(const Node& n) {src = &n;}
	const Node& GetOutput() const {ASSERT(root); return *root;}
	const Vector<Token>& GetTokens() const {return tokens;}
	
	void Dump();
	
	
	One<Node> root;
	
};


}
