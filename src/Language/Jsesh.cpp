#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN


JseshLexer::JseshLexer() {
	
}

bool JseshLexer::Tokenize(WString txt) {
	line = -1;
	col = -1;
	
	txt.Insert(0, '\n');
	
	for(int i = 0; i < txt.GetCount(); i++) {
		int chr = txt[i];
		col++;
		
		if (chr == '\n') {
			Add(JSESH_NEWLINE);
			line++;
			col = -1;
			
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			int chr2 = i+2 < txt.GetCount() ? txt[i+2] : 0;
			
			if (chr1 == '+' && chr2 == '+') {
				Add(JSESH_SETTING);
				i += 2; col += 2;
			}
		}
		else if (chr == '+') {
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			
			if (chr1 == 's') {
				Add(JSESH_ENDTAG);
				i++; col++;
			}
			else if (chr1 == 'l') {
				Add(JSESH_LATIN);
				i++; col++;
			}
			else if (chr1 == 'b') {
				Add(JSESH_LATINBOLD);
				i++; col++;
			}
			else if (chr1 == 'i') {
				Add(JSESH_LATINITALIC);
				i++; col++;
			}
			else if (chr1 == 't') {
				Add(JSESH_TRANSLITERATION);
				i++; col++;
			}
			else {
				WString ws; ws.Cat(chr1);
				Panic("Unexpected tag " + ws.ToString());
			}
		}
		else if (chr == '\\') {
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			if (chr1 == '+') {
				i++;
				col++;
				AppendText('+');
			}
			else
				AppendText(chr);
		}
		else if (chr == '-') {
			Add(JSESH_SEPARATOR);
		}
		else if (chr == ':') {
			Add(JSESH_VERTGROUP);
		}
		else if (chr == '*') {
			Add(JSESH_HORZGROUP);
		}
		else if (chr == '(') {
			Add(JSESH_PARENTHESIS_BEGIN);
		}
		else if (chr == ')') {
			Add(JSESH_PARENTHESIS_END);
		}
		else if (chr == '!') {
			Add(JSESH_LINE_END);
		}
		else if (chr == '<') {
			Add(JSESH_CARTOUCHE_BEGIN);
		}
		else if (chr == '>') {
			Add(JSESH_CARTOUCHE_END);
		}
		else if (chr == '.') {
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			if (chr1 == '.') {
				Add(JSESH_FULL_SPACE);
				i++;
				col++;
			}
			else
				Add(JSESH_HALF_SPACE);
		}
		else
			AppendText(chr);
	}
	
	
	return true;
}

String JseshLexer::GetTypeString(int type) {
	switch (type) {
		case JSESH_NEWLINE: return "newline";
		case JSESH_SETTING: return "setting";
		case JSESH_ENDTAG: return "end-tag";
		case JSESH_LATIN: return "latin";
		case JSESH_LATINBOLD: return "latin-bold";
		case JSESH_LATINITALIC: return "latin-italic";
		case JSESH_TRANSLITERATION: return "transliteration";
		case JSESH_SEPARATOR: return "separator";
		case JSESH_VERTGROUP: return "vert-group";
		case JSESH_HORZGROUP: return "horz-group";
		case JSESH_PARENTHESIS_BEGIN: return "scope-begin";
		case JSESH_PARENTHESIS_END: return "scope-end";
		case JSESH_LINE_END: return "line-end";
		case JSESH_TEXT: return "text";
		case JSESH_CARTOUCHE_BEGIN: return "cartouche-begin";
		case JSESH_CARTOUCHE_END: return "cartouche-end";
		case JSESH_FULL_SPACE: return "full-space";
		case JSESH_HALF_SPACE: return "half-space";
		default: return "";
	}
}







JseshParser::JseshParser() {
	
}

bool JseshParser::Parse(WString txt) {
	
	cursor = 0;
	l.Tokenize(txt);
	//DumpTokens();
	
	errors.Clear();
	
	root.Clear();
	root.SetType(NODE_ROOT);
	scope.Clear();
	scope.Add(&root);
	
	try {
		while (cursor < l.GetCount())
			ParseStatement();
	}
	catch (ParserExc e) {
		int l, c;
		if (!IsEnd()) {
			l = Get().l;
			c = Get().c;
		}
		LOG(":" << l << ":" << c << ": error: " << e);
		errors.Add().Set(l, c, e);
		Panic("error");
	}
	
	
	SolveSigns(root);
	//DumpRoot();
	
	SolveWords(root, 0);
	//DumpRoot();
	
	return true;
}

void JseshParser::DumpTokens() {
	LOG(l.DumpTokens());
}

void JseshParser::DumpRoot() {
	LOG(NodeTreeString(root));
}

void JseshParser::ParseStatement() {
	if (cursor >= l.GetCount()) return;
	const Token& t = l.Get(cursor);
	int tk = t.type;
	
	if (tk == JSESH_UNKNOWN) {
		throw ParserExc("Unexpected unknown token");
	}
	else if (tk == JSESH_NEWLINE) {
		Type(JSESH_NEWLINE);
		
	}
	else if (tk == JSESH_SETTING) {
		Type(JSESH_SETTING);
		if (cursor < l.GetCount() && l.Get(cursor).IsType(JSESH_TEXT)) {
			WString txt = l.Get(cursor).GetString();
			int i = txt.Find(' ');
			WString key, value;
			if (i >= 0) {
				key = txt.Left(i);
				value = txt.Mid(i+1);
				PushScope(NODE_SETTING_KEY);
				Top().SetText(key);
				Top().Add(NODE_TEXT).SetText(value);
				PopScope();
			}
		}
		while (cursor < l.GetCount() && !IsType(JSESH_NEWLINE))
			cursor++;
	}
	else if (tk == JSESH_ENDTAG) {
		Type(JSESH_ENDTAG);
		
	}
	else if (tk == JSESH_LATIN) {
		Type(JSESH_LATIN);
		while (!IsEnd() && !IsType(JSESH_ENDTAG)) {
			AppendText();
		}
		cursor++;
	}
	else if (tk == JSESH_LATINBOLD) {
		Type(JSESH_LATINBOLD);
		PushScope(NODE_BOLD);
		while (!IsEnd() && !IsType(JSESH_ENDTAG)) {
			AppendText();
		}
		cursor++;
		PopScope();
	}
	else if (tk == JSESH_LATINITALIC) {
		Type(JSESH_LATINITALIC);
		PushScope(NODE_ITALIC);
		while (!IsEnd() && !IsType(JSESH_ENDTAG)) {
			AppendText();
		}
		cursor++;
		PopScope();
	}
	else if (tk == JSESH_TRANSLITERATION) {
		Type(JSESH_TRANSLITERATION);
		PushScope(NODE_TRANSLITERATION);
		while (!IsEnd() && !IsType(JSESH_ENDTAG)) {
			AppendText();
		}
		cursor++;
		PopScope();
	}
	else if (tk == JSESH_SEPARATOR) {
		Type(JSESH_SEPARATOR);
		//Top().Add(NODE_SEPARATOR);
	}
	else if (tk == JSESH_PARENTHESIS_BEGIN) {
		Top().Add(LsideStatement());
	}
	else if (tk == JSESH_PARENTHESIS_END) {
		Type(JSESH_PARENTHESIS_END);
	}
	else if (tk == JSESH_LINE_END) {
		Type(JSESH_LINE_END);
	}
	else if (tk == JSESH_TEXT) {
		Top().Add(LsideStatement());
	}
	else if (tk == JSESH_CARTOUCHE_BEGIN) {
		Type(JSESH_CARTOUCHE_BEGIN);
		PushScope(NODE_CARTOUCHE);
		while (!IsEnd() && !IsType(JSESH_CARTOUCHE_END)) {
			ParseStatement();
		}
		PassType(JSESH_CARTOUCHE_END);
		PopScope();
	}
	else if (tk == JSESH_CARTOUCHE_END) {
		Type(JSESH_CARTOUCHE_END);
	}
	else if (tk == JSESH_FULL_SPACE) {
		Top().Add(LsideStatement());
	}
	else if (tk == JSESH_HALF_SPACE) {
		Top().Add(LsideStatement());
	}
	else {
		throw ParserExc("Unexpected token: " + l.GetTypeString(Get().type));
	}
}

void JseshParser::AppendText() {
	if (IsEnd()) return;
	WString str;
	switch (Get().type) {
		case JSESH_NEWLINE: str = "\n"; break;
		case JSESH_SETTING: str = "++"; break;
		case JSESH_ENDTAG: str = "+s"; break;
		case JSESH_LATIN: str = "+l"; break;
		case JSESH_LATINBOLD: str = "+b"; break;
		case JSESH_LATINITALIC: str = "+i"; break;
		case JSESH_TRANSLITERATION: str = "+t"; break;
		case JSESH_SEPARATOR: str = "-"; break;
		case JSESH_VERTGROUP: str = ":"; break;
		case JSESH_HORZGROUP: str = "*"; break;
		case JSESH_PARENTHESIS_BEGIN: str = "("; break;
		case JSESH_PARENTHESIS_END: str = ")"; break;
		case JSESH_LINE_END: str = "!"; break;
		case JSESH_TEXT: str = Get().str_value; break;
		case JSESH_CARTOUCHE_BEGIN: str = "<"; break;
		case JSESH_CARTOUCHE_END: str = ">"; break;
		case JSESH_FULL_SPACE: str = ".."; break;
		case JSESH_HALF_SPACE: str = "."; break;
	}
	if (str.GetCount()) {
		if (Top().GetCount() && Top().Top().GetType() == NODE_TEXT)
			Top().Top().AppendText(str);
		else
			Top().Add(NODE_TEXT).SetText(str);
	}
	cursor++;
}

Node* JseshParser::LsideStatement() {
	return VertGroup();
}

Node* JseshParser::Parenthesis() {
	if (PassType(JSESH_PARENTHESIS_BEGIN)) {
		Node* n = new Node();
		n->SetType(NODE_PARENTHESIS);
		do {
			n->Add(LsideStatement());
		}
		while (PassType(JSESH_SEPARATOR));
		Type(JSESH_PARENTHESIS_END);
		return n;
	}
	else
		return VertGroup();
}

Node* JseshParser::VertGroup() {
	Node* left = HorzGroup();
	
	if (IsType(JSESH_VERTGROUP)) {
		Node* n = new Node();
		n->SetType(NODE_VERTGROUP);
		n->Add(left);
		while (PassType(JSESH_VERTGROUP)) {
			Node* right = HorzGroup();
			n->Add(right);
		}
		return n;
	}
	
	return left;
}

Node* JseshParser::HorzGroup() {
	Node* left = Id();
	
	if (IsType(JSESH_HORZGROUP)) {
		Node* n = new Node();
		n->SetType(NODE_HORZGROUP);
		n->Add(left);
		while (PassType(JSESH_HORZGROUP)) {
			Node* right = Id();
			n->Add(right);
		}
		return n;
	}
	
	return left;
}

Node* JseshParser::Id() {
	if (IsType(JSESH_HALF_SPACE)) {
		Node* n = new Node();
		n->SetType(NODE_TEXT).SetText(" ");
		cursor++;
		return n;
	}
	else 
	if (IsType(JSESH_FULL_SPACE)) {
		Node* n = new Node();
		n->SetType(NODE_TEXT).SetText("  ");
		cursor++;
		return n;
	}
	else if (IsType(JSESH_TEXT)) {
		Node* n = new Node();
		WString str = Get().GetString();
		int len = str.GetCount();
		if (len && str[len-1] == '_') str = str.Left(len-1);
		n->SetType(NODE_TEXT).SetText(str);
		cursor++;
		return n;
	}
	else if (IsType(JSESH_PARENTHESIS_BEGIN))
		return Parenthesis();
	else
		throw ParserExc("Unexpected token: " + l.GetTypeString(Get().type));
}

Node& JseshParser::PushScope(int node_type) {
	ASSERT(node_type >= NODE_NULL);
	Node& top = *scope.Top();
	Node& sub = top.Add(node_type);
	scope.Add(&sub);
	return sub;
}

void JseshParser::PopScope() {
	scope.Pop();
}

void JseshParser::Type(int tk) {
	if (cursor >= l.GetCount())
		throw ParserExc("EOF");
	if (Get().type != tk)
		throw ParserExc("Unexpected token: " + l.GetTypeString(Get().type));
	cursor++;
}

bool JseshParser::PassEmpty() {
	bool found_whitespace = false;
	while (!IsEnd()) {
		const Token& t = l.Get(cursor);
		if ((t.type == JSESH_NEWLINE) ||
			(t.type == JSESH_TEXT && IsEmpty(t.str_value))) {
			cursor++;
			found_whitespace = true;
		}
		else break;
	}
	return found_whitespace;
}

bool JseshParser::PassType(int tk) {
	if (cursor >= l.GetCount())
		return false;
	if (Get().type == tk) {
		cursor++;
		return true;
	}
	return false;
}

void JseshParser::SolveSigns(Node& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		
		if (n0.IsType(NODE_TEXT)) {
			WString sign = n0.GetText();
			
			if (sign == WString("R8A")) {
				n.Remove(i);
				n.Insert(i).SetType(NODE_TEXT).SetText("R8");
				n.Insert(i).SetType(NODE_TEXT).SetText("R8");
				n.Insert(i).SetType(NODE_TEXT).SetText("R8");
				i--;
				continue;
			}
				
			HieroLang& pl = GetHieroLang();
			Dictionary& d = pl.GetSignDictionary();
			int j = d.Find(sign);
			if (j >= 0) {
				n0.SetText(pl.GetSign(j).name.ToWString());
				//n0.ClearText();
				n0.SetType(NODE_SIGN);
				n0.SetInt(j);
			}
			else {
				if (sign.GetCount() == 1 && IsAlpha(sign[0])) {
					Node* s = pl.GetAlpha(sign[0]);
					if (s) {
						n.Remove(i);
						n.Insert(i, s);
						continue;
					}
				}
				
				Dictionary& d = pl.GetTransliterationDictionary();
				
				j = d.Find(sign);
				if (j >= 0) {
					//n0.ClearText();
					n0.SetText(pl.GetSign(j).name.ToWString());
					n0.SetType(NODE_SIGN);
					n0.SetInt(j);
				}
			}
		}
		else if (n0.IsType(NODE_SETTING_KEY))
			continue;
		
		SolveSigns(n0);
	}
}

void JseshParser::SolveWords(Node& n, int depth) {
	
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		
		if (n0.IsType(NODE_SIGN))
			CheckReplaceWord(n, i);
		else if (n0.IsType(NODE_HORZGROUP) ||
			n0.IsType(NODE_VERTGROUP) ||
			n0.IsType(NODE_PARENTHESIS)) {
			if (!CheckReplaceWord(n, i))
				SolveWords(n0, depth+1);
		}
		else if (n0.IsType(NODE_CARTOUCHE))
			SolveWords(n0, 0);
		else
			SolveWords(n0, depth+1);
		
	}
}

bool JseshParser::CheckReplaceWord(Node& n, int begin) {
	Vector<Node*> sign_list;
	Vector<int> results;
	Vector<Node*> result_ends;
	
	GetSignList(n, begin, sign_list, 0);
	//DUMPC(sign_list);
	
	HieroLang& pl = GetHieroLang();
	Dictionary& d = pl.GetHieroDictionary();
	d.BeginSearch();
	
	for(int i = 0; i < sign_list.GetCount(); i++) {
		Node* n = sign_list[i];
		if (!n) continue;
		
		int found = d.SearchNext(n->GetInt());
		if (found) {
			bool is_possible_end = i+1 < sign_list.GetCount() && sign_list[i+1] == NULL;
			if (is_possible_end) {
				d.AppendEndpoints(results);
				while (result_ends.GetCount() < results.GetCount())
					result_ends.Add(n);
			}
		}
		else break;
	}
	
	if (result_ends.GetCount()) {
		for(int i = 0; i < results.GetCount(); i++) {
			LOG(i << ": " << pl.GetDictionary(results[i]).desc);
		}
		int word_ = results.Top();
		String word_desc = pl.GetDictionary(word_).desc;
		if (word_desc.Find("Amun") >= 0) {
			LOG("");
		}
		ASSERT(word_ >= 0);
		Node* end = result_ends.Top();
		for(int i = begin; i < n.GetCount(); i++) {
			if (n.At(i).Contains(end)) {
				int count = i - begin + 1;
				n.Remove(begin, count);
				n.Insert(begin).SetType(NODE_WORD).SetInt(word_).SetText(word_desc.ToWString());
				return true;
			}
		}
	}
	
	return false;
}

bool JseshParser::GetSignList(Node& n, int begin, Vector<Node*>& sign_list, int depth) {
	for(int i = begin; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_SIGN)) {
			sign_list.Add(&n0);
			if (!depth)
				sign_list.Add(NULL); // add possible endpoint
		}
		else if (n0.IsType(NODE_HORZGROUP) ||
			n0.IsType(NODE_VERTGROUP) ||
			n0.IsType(NODE_PARENTHESIS)) {
			if (!GetSignList(n0, 0, sign_list, depth+1))
				return false;
			if (!depth)
				sign_list.Add(NULL); // add possible endpoint
		}
		else if (n0.IsType(NODE_CARTOUCHE)) {
			return false;
		}
		else if (n0.IsType(NODE_SPACE))
			return false;
		else {
			if (!GetSignList(n0, 0, sign_list, depth+1))
				return false;
		}
		
		if (sign_list.GetCount() >= 20)
			return false;
	}
	
	return true;
}


NAMESPACE_LANGUAGE_END
