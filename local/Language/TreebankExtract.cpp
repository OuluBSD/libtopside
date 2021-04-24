#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

void GetWords(Node& n, Vector<WString>& words) {
	
	if (n.IsType(NODE_TEXT)) {
		WString txt = n.GetText();
		if (!txt.IsEmpty())
			words.Add(txt);
		else if (n.GetCount() && n.At(0).IsType(NODE_LEMMA))
			words.Add("(" + n.At(0).GetText() + ")");
	}
	
	else {
		for(int i = 0; i < n.GetCount(); i++) {
			GetWords(n.At(i), words);
		}
	}
	
}

WString GetSentence(Node& n, int& words) {
	static VectorMap<WString, WString> LEFT, RIGHT;
	static Index<WString> NO_SPACE;
	if (LEFT.IsEmpty()) {
		LEFT.Add("``", "\"");
		LEFT.Add("-LRB-", "(");
		LEFT.Add("$", "$");
		RIGHT.Add("''", "\"");
		RIGHT.Add("-RRB-", ")");
		NO_SPACE.Add("?");
		NO_SPACE.Add(",");
		NO_SPACE.Add(".");
		NO_SPACE.Add(":");
		NO_SPACE.Add("%");
		NO_SPACE.Add("n't");
	}
	Vector<WString> wordv;
	GetWords(n, wordv);
	words = wordv.GetCount();
	
	WString sentence;
	for(int i = 0; i < wordv.GetCount(); i++) {
		WString& w = wordv[i];
		if (w.IsEmpty()) continue;
		int j;
		if ((j = LEFT.Find(w)) >= 0 && i+1 < wordv.GetCount()) {
			if (sentence.GetCount()) sentence.Cat(' ');
			sentence << LEFT[j] << wordv[i+1];
			i++;
		}
		else if ((j = RIGHT.Find(w)) >= 0) {
			sentence << RIGHT[j];
		}
		else if (NO_SPACE.Find(w) >= 0 || w[0] == '\'') {
			sentence << w;
		}
		else {
			if (sentence.GetCount()) sentence.Cat(' ');
			sentence << w;
		}
	}
	
	return sentence;
}


NAMESPACE_LANGUAGE_END
