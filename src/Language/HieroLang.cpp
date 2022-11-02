#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

HieroLang::HieroLang() {
	LoadThis();
	
	if (signs.IsEmpty()) {
		String dir = ShareDirFile("natlang");
		
		/*
		Parse jsesh signs_description.xml file:
			1. git clone https://github.com/rosmord/jsesh.git
			2. the file is in jsesh/jsesh/src/main/resources/jsesh/hieroglyphs/signs_description.xml
			3. set the full path below
		*/
		String signs_description_path = AppendFileName(dir, "signs_description.xml");
		
		
		/*
		Parse hieroglyphic dictionary:
			1. google "Dictionary of middle egyptian paul dickson" and download it
			2. install pdftotext (easier in linux or freebsd than windows)
			3. run "pdftotext -layout DicksonDictionary.pdf dictionary.txt"
			4. set the full path of new dictionary.txt below
		*/
		String dictionary_path = AppendFileName(dir, "hiero_dict.txt");
		
		if (!FileExists(signs_description_path))
			Panic("Set the signs_description.xml path in the source code");
		ParseSigns(signs_description_path);
		if (!FileExists(dictionary_path))
			Panic("Set the dictionary path in the source code");
		ParseDictionary(dictionary_path);
		
		AddCharToAscii("ꜣ", "A");
		AddCharToAscii("ꜥ", "a");
		AddCharToAscii("ḥ", "H");
		AddCharToAscii("ḫ", "x");
		AddCharToAscii("ẖ", "X");
		AddCharToAscii("š", "S");
		AddCharToAscii("ṯ", "T");
		AddCharToAscii("ḏ", "D");
		
		AddPronounciation('A', "ɑ(ː)");
		AddPronounciation('i', "i(ː), j");
		AddPronounciation('y', "iː");
		AddPronounciation('a', "ɑː");
		AddPronounciation('w', "wː");
		AddPronounciation('b', "b");
		AddPronounciation('p', "p");
		AddPronounciation('f', "f");
		AddPronounciation('m', "m");
		AddPronounciation('n', "n");
		AddPronounciation('r', "r");
		AddPronounciation('h', "h");
		AddPronounciation('H', "ħ");
		AddPronounciation('x', "x");
		AddPronounciation('X', "ç");
		AddPronounciation('s', "s");
		AddPronounciation('z', "z");
		AddPronounciation('S', "ʃ");
		AddPronounciation('q', "q");
		AddPronounciation('k', "k");
		AddPronounciation('g', "g");
		AddPronounciation('t', "t");
		AddPronounciation('T', "tʃ");
		AddPronounciation('d', "d");
		AddPronounciation('D', "dʒ");
		AddPronounciation('-', "-");
		AddPronounciation(' ', " ");
		AddPronounciation('\t', " ");
		AddPronounciation('\n', " ");
		
		StoreThis();
	}
}

Node* HieroLang::GetAlpha(int chr) {
	const char* str;
	
	if (chr == 'A')
		str = "G1";
	else if (chr == 'i')
		str = "M17";
	else if (chr == 'y') {
		int i = GetHieroLang().GetSignDictionary().Find("M17");
		ASSERT(i >= 0);
		Node* n = new Node();
		n->SetType(NODE_HORZGROUP);
		n->Add(NODE_SIGN).SetInt(i);
		n->Add(NODE_SIGN).SetInt(i);
		return n;
	}
	else if (chr == 'a')
		str = "D36";
	else if (chr == 'w')
		str = "G43";
	else if (chr == 'W')
		str = "Z7";
	else if (chr == 'b')
		str = "D58";
	else if (chr == 'p')
		str = "Q3";
	else if (chr == 'f')
		str = "I9";
	else if (chr == 'm')
		str = "G17";
	else if (chr == 'n')
		str = "N35";
	else if (chr == 'r')
		str = "D21";
	else if (chr == 'h')
		str = "O4";
	else if (chr == 'H')
		str = "V28";
	else if (chr == 'x')
		str = "Aa1";
	else if (chr == 'X')
		str = "F32";
	else if (chr == 's')
		str = "S29";
	else if (chr == 'z')
		str = "O34";
	else if (chr == 'S')
		str = "N37";
	else if (chr == 'q')
		str = "N29";
	else if (chr == 'k')
		str = "V31";
	else if (chr == 'g')
		str = "W11";
	else if (chr == 't')
		str = "X1";
	else if (chr == 'T')
		str = "V13";
	else if (chr == 'd')
		str = "D46";
	else if (chr == 'D')
		str = "I10";
	else {
		return NULL;
	}
	
	int i = GetHieroLang().GetSignDictionary().Find(str);
	ASSERT(i >= 0);
	Node* n = new Node();
	n->SetText(str);
	n->SetType(NODE_SIGN);
	n->SetInt(i);
	return n;
}

WString HieroLang::Pronounce(WString str) {
	WString out;
	for(int i = 0; i < str.GetCount(); i++) {
		int j = chr_pronon.Find(str[i]);
		if (j >= 0)
			out << chr_pronon[j];
	}
	return out;
}

void HieroLang::ParseSigns(String xml_path) {
	String xml = LoadFile(xml_path);
	
	XmlNode xn = ParseXML(xml);
	//LOG(XmlTreeString(xn));
	
	XmlNode& signs = xn.At(0);
	for(int i = 0; i < signs.GetCount(); i++) {
		XmlNode& sign = signs.At(i);
		
		if (sign.GetTag() != "sign")
			continue;
		
		String sign_id = sign.Attr("sign");
		
		int sign_pos = sign_dict.Find(sign_id.ToWString());
		if (sign_pos == -1) {
			sign_pos = this->signs.GetCount();
			this->signs.Add();
			sign_dict.Add(sign_id.ToWString(), sign_pos);
		}
		HieroSign& s = this->signs[sign_pos];
		s.name = sign_id;
		
		for(int j = 0; j < sign.GetCount(); j++) {
			XmlNode& sub = sign.At(j);
			String tag = sub.GetTag();
		
			String sub_sign_id = sub.Attr("sign");
			ASSERT(sub_sign_id == sign_id);
			
			if (tag == "signDescription") {
				String desc = sub.At(0).GetText();
				desc.Replace("\\", "\\\\");
				desc.Replace("\n", "\\n");
				desc.Replace("\"", "\\\"");
				s.description = desc;
			}
			else if (tag == "hasTag") {
				String tag = sub.Attr("tag");
				int k = tags.FindAdd(tag);
				s.Tag(k);
			}
			else if (tag == "hasTransliteration") {
				String type = sub.Attr("type");
				String use = sub.Attr("use");
				int type_id = types.FindAdd(type);
				int use_id = uses.FindAdd(use);
				String translit = sub.Attr("transliteration");
				
				s.TransLit(
					translit,
					type_id,
					use_id);
				
				translit_dict.Add(translit, sign_pos);
			}
			else if (tag == "contains") {
				String code = sub.Attr("partCode");
				if (code.IsEmpty()) continue;
				bool all_lower = true;
				for(int k = 0; k < code.GetCount(); k++) {
					if (IsAlpha(code[k]) && IsLower(code[k]))
						;
					else
						all_lower = false;
				}
				
				if (all_lower)
					s.Contains(code);
				else {
					int k = sign_dict.Find(code.ToWString());
					if (k == -1) {
						k = this->signs.GetCount();
						this->signs.Add().name = code;
						sign_dict.Add(code.ToWString(), k);
					}
					s.Contains(k);
				}
			}
			else if (tag == "variantOf") {
				String linguistic = sub.Attr("linguistic");
				int linguistic_id = linguistics.FindAdd(linguistic);
				String base = sub.Attr("baseSign");
				
				int base_id = sign_dict.Find(base.ToWString());
				if (base_id == -1) {
					base_id = this->signs.GetCount();
					this->signs.Add().name = base;
					sign_dict.Add(base.ToWString(), base_id);
				}
				
				s.Variant(
					base_id,
					sub.Attr("isSimilar") == "y",
					linguistic_id
					);
			}
			else {
				LOG("Unknown tag: " + tag);
			}
		}
	}
	
	/*for(int i = 0; i < signs.GetCount(); i++) {
		ASSERT(this->signs[i].name != "");
	}*/
	DUMPC(tags);
	DUMPC(linguistics);
	DUMPC(uses);
	DUMPC(types);
}

void HieroLang::ParseDictionary(String raw_path) {
	String raw = LoadFile(raw_path);
	
	Vector<String> left_rows, right_rows;
	Vector<String> double_rows = Split(raw, "\n");
	Vector<String> rows;
	int skip = 2;
	for(int i = 0; i < double_rows.GetCount(); i++) {
		String& dr = double_rows[i];
		
		if (skip && dr.Find("A - Men") >= 0) {
			skip--;
			continue;
		}
		if (skip) continue;
		
		if (dr.Find("Dictionary of Middle Egyptian") >= 0) {
			rows.Append(left_rows);
			rows.Append(right_rows);
			left_rows.Clear();
			right_rows.Clear();
			continue;
		}
		
		String left = dr.Left(57);
		String right = dr.Mid(57);
		String last_left = left.Mid(56);
		String first_right = right.Left(1);
		//ASSERT(right.GetCount() == 0 || right.Left(1) == " ");
		ASSERT(	last_left.GetCount() == 0 || last_left.Right(1) == " " ||
				first_right.GetCount() == 0 || first_right.Left(1) == " ");
		
		left_rows.Add(TrimBoth(left) + " ");
		right_rows.Add(TrimBoth(right) + " ");
	}
	
	rows.Append(left_rows);
	rows.Append(right_rows);
	
	for(int i = 0; i < rows.GetCount(); i++) {
		WString row = rows[i].ToWString();
		if (row.GetCount() >= 5) {
			bool b = IsAlpha(row[0]) && IsSpace(row[1]) && IsSpace(row[3]) && (row[2] == '-' || row.Find("–") >= 0);
			b = b || IsAlpha(row[0]) && IsAlpha(row[1]) && IsSpace(row[2]) && IsSpace(row[4]) && (row[3] == '-' || row.Find("–") >= 0);
			if (b) {
				LOG("Remove: " << row);
				rows.Remove(i);
				i--;
				continue;
			}
		}
		
		bool digit_only = true;
		for(int j = 0; j < row.GetCount(); j++) {
			if (!IsDigit(row[j])) {
				digit_only = false;
			}
		}
		if (digit_only) {
			rows.Remove(i);
			i--;
		}
	}
	
	//DUMPC(rows);
	
	dict.Clear();
	dict.Reserve(20000);
	
	enum {BEGIN, PRONON, DESC, DESCSUB, CODE};
	int expected = BEGIN;
	String pronon, desc, code;
	int consecutive_fails = 0;
	int max_code_count = 0;
	for (int r = 0; r < rows.GetCount(); r++) {
		String& raw = rows[r];
		
		bool fail = false;
		int expected_prev = expected;
		String prev_pronon = pronon;
		String prev_desc = desc;
		String prev_code = code;
		
		for(int i = 0; i < raw.GetCount(); i++) {
			int chr = raw[i];
			if (expected == BEGIN) {
				if (chr == '[') {
					expected = PRONON;
					pronon = "";
					desc = "";
					code = "";
				}
				else if (IsSpace(chr)) {
					
				}
				else {
					fail = true;
					break;
				}
			}
			else if (expected == PRONON) {
				if (chr == ']') {
					expected = DESC;
				}
				else if (chr == '[' || chr == '{' || chr == '}') {
					fail = true;
					break;
				}
				else {
					pronon.Cat(chr);
				}
			}
			else if (expected == DESC) {
				if (chr == '{') {
					expected = CODE;
				}
				else if (chr == '(') {
					expected = DESCSUB;
					desc.Cat(chr);
				}
				else if (chr == '[' || chr == ']' || chr == '}') {
					fail = true;
					break;
				}
				else {
					desc.Cat(chr);
				}
			}
			else if (expected == DESCSUB) {
				if (chr == ')') {
					expected = DESC;
				}
				desc.Cat(chr);
			}
			else if (expected == CODE) {
				if (chr == '}') {
					int pos = dict.GetCount();
					HieroLangDictItem& i = dict.Add();
					i.pronon = pronon;
					i.desc = desc;
					Vector<String> codes = Split(code, " ");
					ASSERT(codes.GetCount() <= HieroLangDictItem::max_code_len);
					bool fail = false;
					for(int j = 0; j < codes.GetCount(); j++) {
						const String& code = codes[j];
						int code_id = sign_dict.Find(code.ToWString());
						if (code_id == -1) {
							fail = true;
							break;
						}
						i.code.Add(code_id);
					}
					if (fail)
						dict.Pop();
					else {
						pronon_dict.Add(pronon.ToWString(), pos);
						proto_dict.Add(i.code, pos);
						//TODO: add english-hiero dict
					}
					if (i.code.GetCount() > max_code_count)
						max_code_count = i.code.GetCount();
					expected = BEGIN;
				}
				else if (chr == '[' || chr == '{' || chr == ']') {
					fail = true;
					break;
				}
				else {
					code.Cat(chr);
				}
			}
		}
		
		if (fail) {
			consecutive_fails++;
			if (consecutive_fails > 0) {
				Panic("Fail loop");
				// If code fails here, uncomment DUMPC(rows); and start improving the parser.
			}
			Swap(rows[r], rows[r+1]);
			r--;
		}
		else {
			consecutive_fails = 0;
		}
	}
	DUMP(max_code_count);
}


NAMESPACE_LANGUAGE_END
