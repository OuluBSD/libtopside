#include "Bootstrap.h"

#ifdef flagMAIN

NAMESPACE_OULU_BEGIN


String NodeTreeString(const GrammarNode& n, int indent) {
	String s;
	for(int i = 0; i < indent; i++)
		s.Cat('\t');
	
	s << n.key << "(" << n.type << ") \n";
	
	for(int i = 0; i < n.sub.GetCount(); i++) {
		s << NodeTreeString(n.sub[i], indent+1);
	}
	
	return s;
}




String RemoteParser::ParseG4(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/antlr");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParseCpp(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/cpp");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParsePython3(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/python3");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParsePhp(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/php");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParseLua(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/lua");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParseJava9(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/java9");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParseECMAScript(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/ecmascript");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParseCSharp(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/csharp");
	//h.Trace();
	return h.Execute();
}

String RemoteParser::ParseHigh(String code, int port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(code);
	h.Url("http://localhost:" + IntStr(port) + "/high");
	//h.Trace();
	return h.Execute();
}

void RemoteParser::ReadNode(CParser& p, GrammarNode& n) {
	
	p.PassChar('(');
	
	p.PassChar(':');
	p.PassChar('(');
	n.key = p.ReadId();
	if (p.Char(':')) {
		n.alt = p.ReadInt();
	}
	p.PassChar(')');
	
	while (true) {
		if (p.Char(':')) {
			p.PassChar('(');
			if (p.Char(':')) {
				GrammarNode& n0 = n.sub.Add();
				n.line = p.ReadInt();
				p.PassChar(':');
				n.col = p.ReadInt();
				p.PassChar(':');
				for(int i = 0;; i++) {
					int chr = p.PeekChar();
					
					if (i && (chr == ')' || chr == '('))
						break;
					
					chr = p.GetChar();
					
					if (chr == '\\') {
						chr = p.GetChar();
						
						if (chr == 'n')
							chr = '\n';
						else if (chr == 't')
							chr = '\t';
						else if (chr == 'r')
							chr = '\r';
						else if (chr == '\"')
							;
						else if (chr == '\\')
							;
						else {
							String s;
							s.Cat(chr);
							LOG("warning: unhandled char " << s);
						}
					}
					
					n0.key.Cat(chr);
				}
				if (p.IsChar('(')) {
					Panic("Error");
				}
				p.PassChar(')');
			}
			else {
				GrammarNode& n0 = n.sub.Add();
				n0.key = p.ReadId();
				if (p.Char(':'))
					n0.alt = p.ReadInt();
				p.PassChar(')');
			}
		}
		else if (p.IsChar('(')) {
			ReadNode(p, n.sub.Add());
		}
		else if (p.IsChar(')')) {
			break;
		}
		else {
			String s;
			s.Cat(p.GetChar());
			Panic("unexpected " + s);
		}
	}
	
	p.PassChar(')');
}


NAMESPACE_OULU_END


#endif
