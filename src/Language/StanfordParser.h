#ifndef _Language_StanfordParser_h_
#define _Language_StanfordParser_h_


NAMESPACE_LANGUAGE_BEGIN


String GetStanfordEnglish(String txt, int server_port=7688);

class StanfordXmlParser {
	CParser p;
	VectorMap<int, String> lemmas;
	
	void Parse(Node& n);
	void ReadLemma(Node& n, int& counter);
	
public:
	
	bool Parse(String txt, bool is_xml=false);
	void Dump();
	
	One<Node> root;
	
};


NAMESPACE_LANGUAGE_END

#endif
