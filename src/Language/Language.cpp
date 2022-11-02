#include "Language.h"


NAMESPACE_LANGUAGE_BEGIN



WString TrimBoth(WString s) {
	int begin = 0;
	int end = s.GetCount() - 1;
	while (begin < s.GetCount()) {
		if (!IsSpace(s[begin]))
			break;
		begin++;
	}
	while (end > begin) {
		if (!IsSpace(s[end]))
			break;
		end--;
	}
	if (begin > end)
		return WString();
	return s.Mid(begin, end - begin + 1);
}



String XmlTreeString(const XmlNode& node, int indent, String prev_addr) {
	String out;
	for(int i = 0; i < indent; i++) {
		out.Cat(' ');
	}
	out << String(node.GetTag()) << " : " << String(node.GetText()) << " : " << prev_addr << " : ";
	for(int i = 0; i < node.GetAttrCount(); i++) {
		out += node.AttrId(i) + "=" + node.Attr(i) + ", ";
	}
	out.Replace("\n", "\\n");
	
	out += "\n";
	for(int i = 0; i < node.GetCount(); i++) {
		out += XmlTreeString(node[i], indent+1, prev_addr + " " + IntStr(i));
	}
	return out;
}

Finnish::Finnish() {
	en_native_pronon.Add("ɑː", "aa");
	en_native_pronon.Add("ɑːr", "aar");
	en_native_pronon.Add("ɑ(ː)", "aa");
	en_native_pronon.Add("ɒ", "o");
	en_native_pronon.Add("ɒr", "or");
	en_native_pronon.Add("æ", "ä");
	en_native_pronon.Add("ær", "är");
	en_native_pronon.Add("aɪ", "ai");
	en_native_pronon.Add("aɪər", "aiör");
	en_native_pronon.Add("aɪ.ər", "aier");
	en_native_pronon.Add("aʊ ", "au");
	en_native_pronon.Add("aʊər", "aur");
	en_native_pronon.Add("aʊ.ər", "auver");
	en_native_pronon.Add("ɛ", "e");
	en_native_pronon.Add("ɛr", "err");
	en_native_pronon.Add("eɪ", "ei");
	en_native_pronon.Add("ɛər", "eer");
	en_native_pronon.Add("eɪər", "eiör");
	en_native_pronon.Add("ɪ", "i");
	en_native_pronon.Add("iː", "ii");
	en_native_pronon.Add("ɪər", "iör");
	en_native_pronon.Add("iːər", "iiör");
	en_native_pronon.Add("oʊ", "ou");
	en_native_pronon.Add("oʊər", "over");
	en_native_pronon.Add("ɔː", "oo");
	en_native_pronon.Add("ɔːr", "oor");
	en_native_pronon.Add("ɔːər", "avr");
	en_native_pronon.Add("ɔɪ", "oi");
	en_native_pronon.Add("ɔɪər", "oir");
	en_native_pronon.Add("ɔɪ.ər", "oier");
	en_native_pronon.Add("ʊ", "u");
	en_native_pronon.Add("ʊr", "ur");
	en_native_pronon.Add("uː", "uu");
	en_native_pronon.Add("ʊər", "yöör");
	en_native_pronon.Add("uːər", "uuör");
	en_native_pronon.Add("ʌ", "a");
	en_native_pronon.Add("ɜːr", "öör");
	en_native_pronon.Add("ʌr", "ar");
	en_native_pronon.Add("ə", "a");
	en_native_pronon.Add("i", "i");
	en_native_pronon.Add("u", "u");
	en_native_pronon.Add("ər", "ör");
	en_native_pronon.Add("əl", "öl");
	en_native_pronon.Add("ən", "ön");
	en_native_pronon.Add("əm", "öm");
	en_native_pronon.Add("iə", "iö");
	en_native_pronon.Add("uə", "uö");
	en_native_pronon.Add("ˈ", "ˈ");
	en_native_pronon.Add("ˌ", "ˌ");
	en_native_pronon.Add(".", ".");
	en_native_pronon.Add("b", "b");
	en_native_pronon.Add("d", "d");
	en_native_pronon.Add("dj", "dj");
	en_native_pronon.Add("dʒ", "ts");
	en_native_pronon.Add("ð", "th");
	en_native_pronon.Add("f", "f");
	en_native_pronon.Add("ɡ", "ɡ");
	en_native_pronon.Add("h", "h");
	en_native_pronon.Add("hw", "hv");
	en_native_pronon.Add("j", "j");
	en_native_pronon.Add("k", "k");
	en_native_pronon.Add("q", "k");
	en_native_pronon.Add("l", "l");
	en_native_pronon.Add("lj", "lj");
	en_native_pronon.Add("m", "m");
	en_native_pronon.Add("n", "n");
	en_native_pronon.Add("nj", "nj");
	en_native_pronon.Add("ŋ", "ng");
	en_native_pronon.Add("p", "p");
	en_native_pronon.Add("r", "r");
	en_native_pronon.Add("s", "s");
	en_native_pronon.Add("sj", "sj");
	en_native_pronon.Add("ʃ", "sh");
	en_native_pronon.Add("t", "t");
	en_native_pronon.Add("tj", "tj");
	en_native_pronon.Add("tʃ", "tsh");
	en_native_pronon.Add("θ", "th");
	en_native_pronon.Add("θj", "thj");
	en_native_pronon.Add("v", "v");
	en_native_pronon.Add("w", "vu");
	en_native_pronon.Add("z", "ts");
	en_native_pronon.Add("zj", "zj");
	en_native_pronon.Add("ʒ", "sh");
	en_native_pronon.Add("x", "gh");
	en_native_pronon.Add("ʔ", "ohhou");
	en_native_pronon.Add("ɜː", "öö");
	en_native_pronon.Add("ç", "sch");
	en_native_pronon.Add("ħ", "ch");
	en_native_pronon.Add("x", "ch");
	en_native_pronon.Add("-", "-");
	en_native_pronon.Add(" ", " ");
	en_native_pronon.Add("\n", "\n");
	en_native_pronon.Add("\t", "\t");
	
}

WString Finnish::PronounceNatively(WString en_pron) {
	WString out;
	WString mid[6];
	for(int i = 0; i < en_pron.GetCount(); i++) {
		for(int j = 1; j < 6; j++)
			mid[j] = en_pron.Mid(i, j);
		
		int max_len = 0, max_j = -1;
		for(int j = 0; j < en_native_pronon.GetCount(); j++) {
			const WString& key = en_native_pronon.GetKey(j);
			int len = key.GetCount();
			if (mid[len] == key && len > max_len) {
				max_len = len;
				max_j = j;
			}
		}
		
		if (max_len > 0) {
			out << en_native_pronon[max_j];
			i += max_len -1;
		}
	}
	return out;
}



NAMESPACE_LANGUAGE_END
