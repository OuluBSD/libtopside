#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

String Node::GetTypeString() const {
	switch (type) {
		case NODE_ROOT: return "root";
		case NODE_TEXT: return "text";
		case NODE_SETTING_SCOPE: return "setting-scope";
		case NODE_SETTING_KEY: return "setting-key";
		case NODE_BOLD: return "bold";
		case NODE_ITALIC: return "italic";
		case NODE_TRANSLITERATION: return "transliteration";
		case NODE_SEPARATOR: return "separator";
		case NODE_PARENTHESIS: return "parenthesis";
		case NODE_VERTGROUP: return "vert-group";
		case NODE_HORZGROUP: return "horz-group";
		case NODE_SIGN: return "sign";
		case NODE_WORD: return "word";
		case NODE_SPACE: return "space";
		case NODE_NL: return "nl";
		case NODE_LEMMA: return "lemma";
		case NODE_SENTENCE: return "sentence";
	}
	return "unknown";
}

bool Node::Contains(Node* n) const {
	if (this == n)
		return true;
	for(int i = 0; i < sub.GetCount(); i++) {
		if (sub[i].Contains(n))
			return true;
	}
	return false;
}

String NodeTreeString(const Node& n, int depth, int max_depth) {
	if (depth >= max_depth)
		return "";
	
	String s;
	for(int i = 0; i < depth; i++)
		s.Cat('\t');
	
	s << n.GetTypeString() << ": ";
	if (n.GetInt())
		s << "(" << n.GetInt() << ") ";
	s << n.GetText().ToString();
	for(int i = 0; i < n.GetAttrCount(); i++)
		s << ", " << n.GetAttrKey(i) << "=" << n.GetAttr(i);
	s << "\n";
	
	for(int i = 0; i < n.GetCount(); i++)
		s << NodeTreeString(n.At(i), depth+1);
	
	return s;
}


NAMESPACE_LANGUAGE_END
