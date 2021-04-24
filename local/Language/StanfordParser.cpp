#include "Language.h"


NAMESPACE_LANGUAGE_BEGIN


String GetStanfordEnglish(String txt, int server_port) {
	txt = UrlEncode(txt);
	//String args = "properties={\"annotators\": \"tokenize,ssplit,pos,lemma,ner,parse,dcoref\", \"outputFormat\": \"xml\"}";
	//String args = "properties={\"annotators\": \"tokenize,ssplit,pos,lemma,ner,parse,dcoref\"}";
	String args = "properties={\"annotators\": \"tokenize,ssplit,pos,lemma\"}";
	String url = "http://localhost:" + IntStr(server_port) + "/?" + UrlEncode(args);
	//LOG(txt);
	HttpRequest h;
	h.ContentType("text/plain; charset=utf-8");
	h.Post(txt);
	h.ContentType("application/x-www-form-urlencoded");
	h.Url(url);
	h.Timeout(30*1000);
	//h.Trace();
	String out = h.Execute();
	//LOG(out);
	if (0)
		out = Base64Decode(out);
	return out;
}

void StanfordXmlParser::Dump() {
	if (!root.IsEmpty()) {LOG(NodeTreeString(*root));}
}

bool StanfordXmlParser::Parse(String txt, bool is_xml) {
	root.Create();
	root->SetType(NODE_ROOT);
	
	// Earlier server gave xml output by default.
	if (is_xml) {
		XmlNode xml = ParseXML(txt);
		
		XmlNode& sentences = xml.GetAdd("root").GetAdd("document").GetAdd("sentences");
		for(int i = 0; i < sentences.GetCount(); i++) {
			XmlNode& src_sentence = sentences.At(i);
			
			lemmas.Clear();
			XmlNode& tokens = src_sentence.GetAdd("tokens");
			for(int j = 0; j < tokens.GetCount(); j++) {
				XmlNode& token = tokens.At(j);
				XmlNode& lemma = token.GetAdd("lemma");
				String l;
				if (lemma.GetCount())
					l = lemma.At(0).GetText();
				lemmas.Add(lemmas.GetCount(), l);
			}
			
			XmlNode& parse = src_sentence.GetAdd("parse");
			String parse_txt = parse.At(0).GetText();
			
			try {
				//LOG(parse_txt);
				p.Set(parse_txt);
				Parse(*root);
				if (root->GetCount()) {
					Node& n0 = root->Top();
					n0.SetType(NODE_SENTENCE);
					n0.ClearText();
					int counter = 0;
					ReadLemma(n0, counter);
					RemoveRecursiveDuplicates(n0);
					//LOG(NodeTreeString(n0));
				}
			}
			catch (Exc e) {
				LOG(parse_txt);
				LOG("error: " + e);
				return false;
			}
			
		}
	}
	else {
		Value js = ParseJSON(txt);
		try {
			ValueMap root = js;
			ValueArray sentences = root.GetAdd("sentences");
			for(int i = 0; i < sentences.GetCount(); i++) {
				ValueMap src_sentence = sentences.At(i);
				
				lemmas.Clear();
				ValueArray tokens = src_sentence.GetAdd("tokens");
				for(int j = 0; j < tokens.GetCount(); j++) {
					ValueMap token = tokens.At(j);
					int index = token.GetAdd("index");
					String l = token.GetAdd("lemma");
					lemmas.Add(index, l);
				}
				
				VectorMap<int, Node*> known_nodes;
				known_nodes.Add(0, &*this->root);
				
				ValueArray parse = src_sentence.GetAdd("basicDependencies");
				Vector<int> to_process;
				for(int i = 0; i < parse.GetCount(); i++)
					to_process.Add(i);
				while(to_process.GetCount()) {
					bool added_any = false;
					for(int i = 0; i < to_process.GetCount(); i++) {
						int j = to_process[i];
						ValueMap dep = parse.At(j);
						int governor = dep.GetAdd("governor");
						int dependent = dep.GetAdd("dependent");
						Node* gov = known_nodes.Get(governor, 0);
						if (!gov)
							continue;
						Node& n = gov->Add(NODE_NL);
						n.SetAttr(NODEATTR_POS, dependent);
						known_nodes.Add(dependent, &n);
						ValueMap tk = tokens[dependent-1];
						n.Add(NODE_TEXT).SetText(tk.GetAdd("originalText").ToString().ToWString());
						n.Add(NODE_LEMMA).SetText(lemmas.Get(dependent).ToWString());
						to_process.Remove(i--);
						added_any = true;
					}
					if (!added_any) {
						LOG("error: governor node not found");
						return false;
					}
				}
			}
		}
		catch (Exc e) {
			LOG("error: " + e);
			return false;
		}
	}
	
	return true;
}

void StanfordXmlParser::Parse(Node& n) {
	
	if (p.Char('(')) {
		Node& n0 = n.Add(NODE_NL);
		String type;
		while (p.PeekChar() != ' ') {
			int chr = p.GetChar();
			type.Cat(chr);
		}
		p.Char(' ');
		
		n0.SetText(type.ToWString());
		
		if (p.IsChar('(')) {
			while (p.IsChar('('))
				Parse(n0);
		}
		else {
			String txt;
			while (!p.IsChar(')')) {
				txt.Cat(p.PeekChar());
				p.Char(p.PeekChar());
			}
			n0.Add(NODE_TEXT).SetText(txt.ToWString());
		}
		
		if (n0.GetCount() == 0)
			n0.SetType(NODE_TEXT);
		
		p.PassChar(')');
	}
	
}

void StanfordXmlParser::ReadLemma(Node& n, int& counter) {
	
	if (n.IsType(NODE_TEXT)) {
		Node& l = n.Add(NODE_LEMMA);
		if (counter < lemmas.GetCount())
			l.SetText(lemmas[counter].ToWString());
		counter++;
	}
	else {
		for(int i = 0; i < n.GetCount(); i++) {
			ReadLemma(n.At(i), counter);
		}
	}
}


NAMESPACE_LANGUAGE_END
