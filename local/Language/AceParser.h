#ifndef _Language_AceParser_h_
#define _Language_AceParser_h_

NAMESPACE_LANGUAGE_BEGIN



class AceParser {
	CParser p;
	Vector<String> lemmas;
	
	void Parse(Node& n);
	void ReadLemma(Node& par, Node& n, int& counter);
	
public:
	
	bool Parse(String txt);
	
	void Dump() {if (!root.IsEmpty()) {LOG(NodeTreeString(*root));}}
	
	One<Node> root;
	
};


String GetAceEnglish(String txt, String erg_file="", String dir="");


NAMESPACE_LANGUAGE_END

#endif
