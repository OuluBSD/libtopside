#ifndef _Parser_Service_h_
#define _Parser_Service_h_

#ifdef flagMAIN

NAMESPACE_OULU_BEGIN

class ParserService {
	String dir, grammar_dir, env;
	One<LocalProcess> proc;
	
public:
	typedef ParserService CLASSNAME;
	ParserService();
	
	void Start();
	void Stop();
	void Restart() {Stop(); Start();}
	void Recompile();
	
};


inline ParserService& GetParserService() {return Single<ParserService>();}


struct GrammarNode : Moveable<GrammarNode> {
	Array<GrammarNode> sub;
	String key;
	int type = 0;
	int alt = 0;
	int line = 0, col = 0;
	
	
	GrammarNode() {}
	GrammarNode(int type) : type(type) {}
	GrammarNode(int type, const GrammarNode& n) : type(type), line(n.line), col(n.col) {}
	void Clear() {
		sub.Clear();
		key.Clear();
		line = 0;
		col = 0;
	}
	
	int GetCount() const {return sub.GetCount();}
};

String NodeTreeString(const GrammarNode& n, int indent = 0);

struct RemoteParser {
	
	
	void ReadNode(CParser& p, GrammarNode& n);
	String ParseG4(String code, int port=8765);
	String ParseCpp(String code, int port=8765);
	String ParsePython3(String code, int port=8765);
	String ParsePhp(String code, int port=8765);
	String ParseLua(String code, int port=8765);
	String ParseJava9(String code, int port=8765);
	String ParseECMAScript(String code, int port=8765);
	String ParseCSharp(String code, int port=8765);
	String ParseHigh(String code, int port=8765);
	
};

NAMESPACE_OULU_END

#endif
#endif
