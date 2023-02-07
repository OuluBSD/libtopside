#include "Local.h"

#ifdef flagSTDEXC

NAMESPACE_TOPSIDE_BEGIN


ValidHtmlTags::ValidHtmlTags() {
	// Tags that must be closed
	SplitTags(html_pairs_static,
		"b bdi del i ins u font big small sub sup h1 "
        "h2 h3 h4 h5 h6 cite code em s "
        "strike strong tt var div center "
        "blockquote ol ul dl table caption pre "
        "ruby rb rp rt rtc p span abbr dfn "
        "kbd samp data time mark");
	
	SplitTags(html_single,
		"br wbr hr li dt dd meta link");
	
	// Elements that cannot have close tags
	SplitTags(html_single_only,
		"br wbr hr meta link");
	
	// Tags that can be nested
	SplitTags(html_nest,
		"table tr td th div blockquote ol ul "
		"li dl dt dd font big small sub sup span "
		"var kbd samp em strong q ruby bdo");
	
	// Can only appear inside table, we will close them
	SplitTags(table_tags,
		"td th tr");
	
	// Tags used by list
	SplitTags(html_list,
		"ul ol");
	
	// Tags that can appear in a list
	SplitTags(list_tags,
		"li");
}

void ValidHtmlTags::SplitTags(Index<WString>& idx, WString ws) {
	Vector<WString> v = Split(ws, ToWString(" "));
	for(int i = 0; i < v.GetCount(); i++)
		idx.Add(v[i]);
}








HtmlLexer::HtmlLexer() {
	
}

HtmlToken& HtmlLexer::Add(int token_id) {
	HtmlToken& tk = tokens.Add();
	tk.type = token_id;
	return tk;
}

void HtmlLexer::AppendText(int chr) {
	if (!tokens.IsEmpty()) {
		HtmlToken& tk = tokens.Top();
		if (tk.type == HTMLTK_TEXT) {
			tk.str_value.Cat(chr);
			return;
		}
	}
	HtmlToken& tk = tokens.Add();
	tk.type = HTMLTK_TEXT;
	tk.str_value.Cat(chr);
}

void HtmlLexer::AppendSpace(int chr) {
	if (!tokens.IsEmpty()) {
		HtmlToken& tk = tokens.Top();
		if (tk.type == HTMLTK_SPACE) {
			tk.str_value.Cat(chr);
			return;
		}
	}
	HtmlToken& tk = tokens.Add();
	tk.type = HTMLTK_SPACE;
	tk.str_value.Cat(chr);
}

void HtmlLexer::Tokenize(String html) {
	
	for(int i = 0; i < html.GetCount(); i++) {
		int chr = html[i];
		
		if (chr == '<') {
			int chr1 = i+1 < html.GetCount() ? html[i+1] : 0;
			int chr2 = i+2 < html.GetCount() ? html[i+2] : 0;
			int chr3 = i+3 < html.GetCount() ? html[i+3] : 0;
			if (chr1 == '!' && chr2 == '-' && chr3 == '-') {
				Add(HTMLTK_COMMENT_BEGIN);
				i += 3;
			}
			else
				Add(HTMLTK_LESS);
		}
		else if (chr == '-') {
			int chr1 = i+1 < html.GetCount() ? html[i+1] : 0;
			int chr2 = i+2 < html.GetCount() ? html[i+2] : 0;
			if (chr1 == '-' && chr2 == '>') {
				Add(HTMLTK_COMMENT_END);
				i += 2;
			}
			else
				AppendText(chr);
		}
		else if (chr == '>') {
			Add(HTMLTK_GREATER);
		}
		else if (IsSpace(chr)) {
			AppendSpace(chr);
		}
		else if (chr == '=') {
			Add(HTMLTK_EQ);
		}
		else if (chr == '\"') {
			Add(HTMLTK_QUOTATION);
		}
		else if (chr == '/') {
			Add(HTMLTK_SLASH);
		}
		else {
			AppendText(chr);
		}
	}
}


HtmlParser::HtmlParser() {
	
}

void HtmlParser::RemoveEmptyTextNodes(HtmlNode& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		HtmlNode& n0 = n.At(i);
		if (n0.IsType(HTMLNODE_TEXT)) {
			WString text = n0.GetText();
			bool is_empty = true;
			for(int i = 0; i < text.GetCount(); i++)
				if (!IsSpace(text[i]))
					is_empty = false;
			if (is_empty) {
				n.Remove(i);
				i--;
			}
		}
		else RemoveEmptyTextNodes(n0);
	}
}

void HtmlParser::MakeTagScopes(HtmlNode& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		HtmlNode& n0 = n.At(i);
		if (n0.IsType(HTMLNODE_TAG) && !(n0.GetCount() && n0.Top().IsType(HTMLNODE_TAG_END))) {
			WString tag = n0.GetText();
			int end = -1;
			int depth = 1;
			for(int j = i+1; j < n.GetCount(); j++) {
				HtmlNode& n1 = n.At(j);
				if (n1.IsType(HTMLNODE_TAG) && n1.IsText(tag)) {
					if (n1.GetCount() == 1 && n1.At(0).IsType(HTMLNODE_TAG_END)) {
						depth--;
						if (depth <= 0) {
							end = j;
							break;
						}
					}
					else if (n1.GetCount() == 0 || !n1.Top().IsType(HTMLNODE_TAG_END)) {
						depth++;
					}
				}
			}
			if (end >= 0) {
				One<HtmlNode> scope = n.Detach(i);
				scope->SetType(HTMLNODE_TAG_SCOPE);
				scope->SetText(tag);
				for(int j = i+1; j < end; j++)
					scope->Add(n.Detach(i));
				n.Remove(i); // discard end tag
				n.Insert(i, scope.Detach());
			}
		}
		MakeTagScopes(n.At(i));
	}
}

bool HtmlParser::Parse(String html) {
	root.Clear();
	root.SetType(HTMLNODE_ROOT);
	
	// Lazy meta charset parsing and conversion
	int i = html.Find("meta");
		if (i >= 0) {
		int a = html.ReverseFind("<", i);
		int b = html.Find(">", a);
		String meta = html.Mid(a, b-a);
		a = meta.Find("charset");
		if (a >= 0) {
			a = meta.Find("=", a);
			if (a >= 0) {
				a++;
				while (a < meta.GetCount() && IsSpace(meta[a])) a++;
				if (a < meta.GetCount() && meta[a] == '\"') a++;
				int b1 = meta.Find(";", a);
				int b2 = meta.Find("\"", a);
				b = -1;
				if (b1 != -1 && b2 != -1) b = min(b1, b2);
				else if (b1 != -1) b = b1;
				else b = b2;
				if (b != -1) {
					#if IS_UPP_CORE
					String charset = TrimBoth(meta.Mid(a, b-a));
					int charset_id = CharsetByName(charset);
					if (charset_id && charset_id != CHARSET_UTF8) {
						WString out;
						#if 1
						out += ToUnicode(html.Begin(), html.GetCount(), charset_id);
						#else
						out.Cat(' ', html.GetCount());
						ToUnicode((wchar*)out.Begin(), html.Begin(), html.GetCount(), charset_id);
						#endif
						html = out.ToString();
					}
					#endif
				}
			}
		}
	}
	
	
	l.Tokenize(html);
	//DUMPC(l.tokens);
	
	cursor = 0;
	scope.Clear();
	scope.Add(&root);
	try {
		while (!IsEnd())
			ParseStatement();
	}
	catch (Exc e) {
		LOG("error: " + e);
	}
	
	RemoveEmptyTextNodes(root);
	MakeTagScopes(root);
	
	try {
		HtmlNode& meta = root.TryGetTag("html").TryGetTag("head").TryGetTag("meta");
	}
	catch (Exc e) {
		
	}
	
	return true;
}

void HtmlParser::ParseStatement() {
	const HtmlToken& t = Get();
		
	if (Type(HTMLTK_LESS)) {
		if (Type(HTMLTK_SLASH)) {
			DoSpaces();
			
			HtmlNode& n = PushScope(HTMLNODE_TAG);
			n.Add(HTMLNODE_TAG_END);
			WString tag_id = ReadText();
			n.SetText(tag_id);
		}
		else {
			HtmlNode& n = PushScope(HTMLNODE_TAG);
			WString tag_id = ReadText();
			if (IsConstChar(tag_id, "!DOCTYPE", 8)) {
				DoSpaces();
				tag_id += ToWString(" ") + ReadText();
			}
			n.SetText(tag_id);
			DoSpaces();
			
			if (Type(HTMLTK_SLASH)) {
				n.Add(HTMLNODE_TAG_END);
				DoSpaces();
			}
			else {
				while (!IsType(HTMLTK_GREATER)) {
					String key = ToString(ReadText());
					DoSpaces();
					PassType(HTMLTK_EQ);
					DoSpaces();
					
					PassType(HTMLTK_QUOTATION);
					String value;
					while (!IsEnd() && !IsType(HTMLTK_QUOTATION)) {
						value += ToString(Get().GetTextValue());
						cursor++;
					}
					PassType(HTMLTK_QUOTATION);
					DoSpaces();
					
					n.SetAttr(key, value);
					
					if (Type(HTMLTK_SLASH)) {
						n.Add(HTMLNODE_TAG_END);
						DoSpaces();
						break;
					}
				}
			}
		}
		PassType(HTMLTK_GREATER);
		PopScope();
	}
	else if (Type(HTMLTK_COMMENT_BEGIN)) {
		while (!IsEnd() && !IsType(HTMLTK_COMMENT_END))
			cursor++;
		cursor++;
	}
	else {
		AppendText(t.GetTextValue());
		cursor++;
	}
}

void HtmlParser::AppendText(WString s) {
	HtmlNode& scope = Top();
	if (scope.GetCount() == 0 || !scope.Top().IsType(HTMLNODE_TEXT))
		scope.Add(HTMLNODE_TEXT);
	scope.Top().Cat(s);
}

WString HtmlParser::ReadText() {
	if (IsEnd())
		throw Exc("Unexpected end");
	WString s = Get().str_value;
	PassType(HTMLTK_TEXT);
	return s;
}

HtmlNode& HtmlParser::PushScope(int node_type) {
	ASSERT(node_type >= HTMLNODE_NULL);
	HtmlNode& top = *scope.Top();
	HtmlNode& sub = top.Add(node_type);
	scope.Add(&sub);
	return sub;
}

void HtmlParser::PopScope() {
	scope.Pop();
}

void HtmlParser::PassType(int tk) {
	if (cursor >= l.tokens.GetCount())
		throw Exc("EOF");
	if (Get().type != tk)
		throw Exc("Unexpected token: " + Get().GetTypeString());
	cursor++;
}

bool HtmlParser::Type(int tk) {
	if (cursor >= l.tokens.GetCount())
		return false;
	if (Get().type == tk) {
		cursor++;
		return true;
	}
	return false;
}






HtmlNode& HtmlNode::TryGetTag(String key) {
	for(int i = 0; i < sub.GetCount(); i++) {
		HtmlNode& n0 = sub[i];
		if ((n0.IsType(HTMLNODE_TAG) || n0.IsType(HTMLNODE_TAG_SCOPE)) &&
			IsConstChar(n0.GetText(), key, key.GetCount()))
			return n0;
	}
	throw Exc("Tag not found: " + key);
}

NAMESPACE_TOPSIDE_END

#endif
