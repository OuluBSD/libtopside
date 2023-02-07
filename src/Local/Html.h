#ifndef _Local_Html_h_
#define _Local_Html_h_

NAMESPACE_TOPSIDE_BEGIN



enum {
	HTMLTK_UNKNOWN,
	HTMLTK_TEXT,
	HTMLTK_NEWLINE,
	HTMLTK_ITALIC,
	HTMLTK_BOLD,
	HTMLTK_BOLDITALIC,
	HTMLTK_CODELINE,
	HTMLTK_DIV,
	HTMLTK_TAG_BEGIN,
	HTMLTK_TAG_END,
	HTMLTK_LIST,
	HTMLTK_NUMBEREDLIST,
	HTMLTK_TEMPLATE_BEGIN,
	HTMLTK_TEMPLATE_END,
	HTMLTK_COMMENT_BEGIN,
	HTMLTK_COMMENT_END,
	HTMLTK_EQ,
	HTMLTK_SECTION,
	HTMLTK_DEFINITION,
	HTMLTK_COLON,
	HTMLTK_INDENT,
	HTMLTK_HORZLINE,
	HTMLTK_LINK_BEGIN,
	HTMLTK_LINK_END,
	HTMLTK_REDIRECT,
	HTMLTK_TABLE_BEGIN,
	HTMLTK_TABLE_END,
	HTMLTK_TABLE_TITLE_BEGIN,
	HTMLTK_TABLE_ROW_BEGIN,
	HTMLTK_TABLE_COL_BEGIN,
	HTMLTK_NLCODE_LINE,
	HTMLTK_SPACE,
	HTMLTK_LESS,
	HTMLTK_GREATER,
	HTMLTK_QUOTATION,
	HTMLTK_SLASH,
};

struct HtmlToken : Moveable<HtmlToken> {
	int type = 0;
	int int_value=0;
	WString str_value;
	
	HtmlToken& SetInt(int i) {int_value = i; return *this;}
	
	int GetInt() const {return int_value;}
	WString GetString() const {return str_value;}
	String GetTypeString() const {
		switch (type) {
			case HTMLTK_TEXT: return "text";
			case HTMLTK_NEWLINE: return "newline";
			case HTMLTK_ITALIC: return "italic";
			case HTMLTK_BOLD: return "bold";
			case HTMLTK_BOLDITALIC: return "bold-italic";
			case HTMLTK_CODELINE: return "codeline";
			case HTMLTK_DIV: return "div";
			case HTMLTK_TAG_BEGIN: return "tag-begin";
			case HTMLTK_TAG_END: return "tag-end";
			case HTMLTK_LIST: return "list";
			case HTMLTK_NUMBEREDLIST: return "numbered-list";
			case HTMLTK_TEMPLATE_BEGIN: return "template-begin";
			case HTMLTK_TEMPLATE_END: return "template-end";
			case HTMLTK_COMMENT_BEGIN: return "comment-begin";
			case HTMLTK_COMMENT_END: return "comment-end";
			case HTMLTK_EQ: return "equal";
			case HTMLTK_SECTION: return "section";
			case HTMLTK_DEFINITION: return "definition";
			case HTMLTK_COLON: return "colon";
			case HTMLTK_INDENT: return "indent";
			case HTMLTK_HORZLINE: return "horz-line";
			case HTMLTK_LINK_BEGIN: return "link-begin";
			case HTMLTK_LINK_END: return "link-end";
			case HTMLTK_REDIRECT: return "redirect";
			case HTMLTK_TABLE_BEGIN: return "table-begin";
			case HTMLTK_TABLE_END: return "table-end";
			case HTMLTK_TABLE_TITLE_BEGIN: return "table-title-begin";
			case HTMLTK_TABLE_ROW_BEGIN: return "row-begin";
			case HTMLTK_TABLE_COL_BEGIN: return "col-begin";
			case HTMLTK_NLCODE_LINE: return "nl-line";
			case HTMLTK_SPACE: return "space";
			case HTMLTK_LESS: return "less";
			case HTMLTK_GREATER: return "greater";
			case HTMLTK_QUOTATION: return "quotation";
			case HTMLTK_SLASH: return "slash";
		}
		return "";
	}
	String ToString() const {
		String s = "type=" + GetTypeString();
		if (int_value) s << " int=" << IntStr(int_value);
		if (!str_value.IsEmpty()) s << " str=" << UPP::AsString(str_value);
		return s;
	}
	WString GetTextValue() const {
		switch (type) {
			case HTMLTK_TEXT: return str_value;
			case HTMLTK_LESS: return WString(L"<");
			case HTMLTK_GREATER: return WString(L">");
			case HTMLTK_SPACE: return str_value;
			case HTMLTK_QUOTATION: return WString(L"\"");
			case HTMLTK_EQ: return WString(L"=");
			case HTMLTK_SLASH: return WString(L"/");
			case HTMLTK_COMMENT_BEGIN: return WString(L"<!--");
			case HTMLTK_COMMENT_END: return WString(L"-->");
			default: Panic("Unhandled token type");
		}
		return ToWString(L"");
	}
};












enum {
	HTMLNODE_NULL = 10000,
	HTMLNODE_ROOT,
	HTMLNODE_TEXT,
	HTMLNODE_TEMPLATE,
	HTMLNODE_TEMPLATE_NAME,
	HTMLNODE_TEMPLATE_ARG,
	HTMLNODE_TAG,
	HTMLNODE_TAG_END,
	HTMLNODE_TAG_ARG,
	HTMLNODE_TAG_SCOPE,
	HTMLNODE_ITALIC,
	HTMLNODE_BOLD,
	HTMLNODE_BOLDITALIC,
	HTMLNODE_CODELINE,
	HTMLNODE_CODELINE_SCOPE,
	HTMLNODE_REDIRECT,
	HTMLNODE_TABLE,
	HTMLNODE_TABLE_ROW,
	HTMLNODE_TABLE_COL,
	HTMLNODE_TABLE_PARAMS,
	HTMLNODE_TABLE_ARG,
	HTMLNODE_LIST,
	HTMLNODE_NUMBEREDLIST,
	HTMLNODE_COMMENT,
	HTMLNODE_SECTION,
	HTMLNODE_SECTION_SCOPE,
	HTMLNODE_DEFINITION,
	HTMLNODE_DEFINITION_KEY,
	HTMLNODE_DEFINITION_ITEM,
	HTMLNODE_INDENT,
	HTMLNODE_HORZLINE,
	HTMLNODE_LINK,
	HTMLNODE_LINK_ARG,
	HTMLNODE_NEWPARAGRAPH,
	HTMLNODE_LIST_SCOPE,
	HTMLNODE_LIST_SCOPE_ITEM,
	HTMLNODE_NUMBEREDLIST_SCOPE,
	HTMLNODE_NUMBEREDLIST_SCOPE_ITEM,
	HTMLNODE_DEFINITION_SCOPE,
	HTMLNODE_PARAGRAPH
};

struct ValidHtmlTags {
	Index<WString> html_pairs_static;
	Index<WString> html_single;
	Index<WString> html_single_only;
	Index<WString> html_nest;
	Index<WString> table_tags;
	Index<WString> html_list;
	Index<WString> list_tags;
	
	ValidHtmlTags();
	void SplitTags(Index<WString>& idx, WString ws);
	void SplitTags(Index<WString>& idx, const char* s) {SplitTags(idx, ToWString(String(s)));}
	
};

inline ValidHtmlTags& GetValidHtmlTags() {return Single<ValidHtmlTags>();}


inline bool IsTypeScopeItem(int scope, int item) {
	return
		(scope == HTMLNODE_LIST_SCOPE && item == HTMLNODE_LIST_SCOPE_ITEM) ||
		(scope == HTMLNODE_NUMBEREDLIST_SCOPE && item == HTMLNODE_NUMBEREDLIST_SCOPE_ITEM) ||
		(scope == HTMLNODE_DEFINITION_SCOPE && item == HTMLNODE_DEFINITION_KEY) ||
		(scope == HTMLNODE_DEFINITION_SCOPE && item == HTMLNODE_DEFINITION_ITEM);
}

class HtmlNode {
	Array<HtmlNode> sub;
	VectorMap<String, String> attr;
	int type = HTMLNODE_NULL;
	
	WString text;
	int int_value = 0;
public:
	
	HtmlNode() {}
	HtmlNode(const HtmlNode& n) {*this = n;}
	HtmlNode(int type, WString txt) {this->type = type; text = txt;}
	
	void operator=(const HtmlNode& n) {
		sub <<= n.sub;
		attr <<= n.attr;
		type = n.type;
		text = n.text;
		int_value = n.int_value;
	}
	void Serialize(Stream& s) {s % sub % attr % type % text % int_value;}
	
	#if IS_UPP_CORE
	void Jsonize(JsonIO& json) {
		json
			("type", type)
			("text", text)
			("int", int_value)
			("sub", sub)
			("attr", attr);
	}
	#endif
	
	HtmlNode& Add(int type) {HtmlNode& n = sub.Add(); n.type = type; return n;}
	HtmlNode& Add(HtmlNode* n) {ASSERT(this != n); HtmlNode& nn = sub.Add(n); return nn;}
	HtmlNode& Add(int type, WString text) {HtmlNode& n = sub.Add(); n.type = type; n.SetText(text); return n;}
	HtmlNode& SetType(int i) {type = i; return *this;}
	HtmlNode& SetText(WString txt) {text = txt; return *this;}
	HtmlNode& SetInt(int i) {int_value = i; return *this;}
	void Clear() {sub.Clear(); type = 0; text.Clear(); attr.Clear();}
	void ClearHtmlNodes() {sub.Clear();}
	void ClearText() {text.Clear();}
	void Remove(int i) {sub.Remove(i);}
	void Remove(int i, int count) {sub.Remove(i, count);}
	HtmlNode* Detach(int i) {return sub.Detach(i);}
	HtmlNode& Insert(int i, HtmlNode* n) {return sub.Insert(i, n);}
	HtmlNode& Insert(int i) {return sub.Insert(i);}
	HtmlNode& Insert(int i, int type, WString txt) {return sub.Insert(i).SetType(type).SetText(txt);}
	void Append(HtmlNode* n) {while(n->sub.GetCount()) {HtmlNode& nn = sub.Add(n->sub.Detach(0)); ASSERT(&nn != this);} delete n;}
	HtmlNode& Top() {return sub.Top();}
	HtmlNode& SetAttr(String key, String value) {attr.GetAdd(key) = value; return *this;}
	HtmlNode& Cat(WString s) {text.Cat(s); return *this;}
	
	HtmlNode& At(int i) {return sub[i];}
	const HtmlNode& At(int i) const {return sub[i];}
	int GetCount() const {return sub.GetCount();}
	int GetType() const {return type;}
	int GetInt() const {return int_value;}
	WString GetText() const {return text;}
	bool IsType(int type) {ASSERT(type >= HTMLNODE_NULL); return this->type == type;}
	bool IsTypeScope() const {return type == HTMLNODE_LIST_SCOPE || type == HTMLNODE_NUMBEREDLIST_SCOPE || type == HTMLNODE_DEFINITION_SCOPE;}
	bool IsText(const WString& ws) {return text == ws;}
	String GetAttr(String key) const {int i = attr.Find(key); if (i == -1) return ""; return attr[i];}
	int GetAttrCount() const {return attr.GetCount();}
	String GetAttrKey(int i) const {return attr.GetKey(i);}
	String GetAttr(int i) const {return attr[i];}
	HtmlNode& TryGetTag(String key);
	
	String GetTypeString() const {
		switch (type) {
			case HTMLNODE_NULL: return "null";
			case HTMLNODE_ROOT: return "root";
			case HTMLNODE_TEXT: return "text";
			case HTMLNODE_TEMPLATE: return "template";
			case HTMLNODE_TEMPLATE_NAME: return "template-name";
			case HTMLNODE_TEMPLATE_ARG: return "template-arg";
			case HTMLNODE_TAG: return "tag";
			case HTMLNODE_TAG_END: return "tag-end";
			case HTMLNODE_TAG_ARG: return "tag-arg";
			case HTMLNODE_TAG_SCOPE: return "tag-scope";
			case HTMLNODE_ITALIC: return "italic";
			case HTMLNODE_BOLD: return "bold";
			case HTMLNODE_BOLDITALIC: return "bold-italic";
			case HTMLNODE_CODELINE: return "codeline";
			case HTMLNODE_CODELINE_SCOPE: return "codeline-scope";
			case HTMLNODE_REDIRECT: return "redirect";
			case HTMLNODE_TABLE: return "table";
			case HTMLNODE_TABLE_ROW: return "table-row";
			case HTMLNODE_TABLE_COL: return "table-col";
			case HTMLNODE_TABLE_PARAMS: return "table-params";
			case HTMLNODE_TABLE_ARG: return "table-arg";
			case HTMLNODE_LIST: return "list";
			case HTMLNODE_NUMBEREDLIST: return "numbered-list";
			case HTMLNODE_COMMENT: return "comment";
			case HTMLNODE_SECTION: return "section";
			case HTMLNODE_SECTION_SCOPE: return "section-scope";
			case HTMLNODE_DEFINITION: return "definition";
			case HTMLNODE_DEFINITION_KEY: return "definition-key";
			case HTMLNODE_DEFINITION_ITEM: return "definition-item";
			case HTMLNODE_INDENT: return "indent";
			case HTMLNODE_HORZLINE: return "horzline";
			case HTMLNODE_LINK: return "link";
			case HTMLNODE_LINK_ARG: return "link-arg";
			case HTMLNODE_NEWPARAGRAPH: return "new-paragraph";
			case HTMLNODE_LIST_SCOPE: return "list-scope";
			case HTMLNODE_LIST_SCOPE_ITEM: return "list-scope-item";
			case HTMLNODE_NUMBEREDLIST_SCOPE: return "numbered-list-scope";
			case HTMLNODE_NUMBEREDLIST_SCOPE_ITEM: return "numbered-list-scope-item";
			case HTMLNODE_DEFINITION_SCOPE: return "definition-scope";
			case HTMLNODE_PARAGRAPH: return "paragraph";
		}
		return "";
	}
};




class HtmlLexer {
	
protected:
	friend class HtmlParser;
	Vector<HtmlToken> tokens;
	
	
public:
	HtmlLexer();
	
	
	void Tokenize(String html);
	HtmlToken& Add(int token_id);
	void AppendText(int chr);
	void AppendSpace(int chr);
	
};

class HtmlParser {
	HtmlLexer l;
	
	int cursor = 0;
	Vector<HtmlNode*> scope;
	
	void ParseStatement();
	
	
public:
	typedef HtmlParser CLASSNAME;
	HtmlParser();
	
	
	bool IsEnd() const {return cursor >= l.tokens.GetCount();}
	const HtmlToken& Get() const {return l.tokens[cursor];}
	void PassType(int tk);
	bool Empty();
	bool Type(int tk);
	bool IsType(int tk) {return l.tokens[cursor].type == tk;}
	HtmlNode& Top() {return *scope.Top();}
	HtmlNode& PushScope(HtmlNode* n) {return *scope.Add(n);}
	HtmlNode& PushScope(int node_type);
	void PopScope();
	
	bool Parse(String html);
	void DoSpaces() {while (!IsEnd() && IsType(HTMLTK_SPACE)) cursor++;}
	WString ReadText();
	void AppendText(WString s);
	void RemoveEmptyTextNodes(HtmlNode& n);
	void MakeTagScopes(HtmlNode& n);
	
	HtmlNode root;
};


NAMESPACE_TOPSIDE_END

#endif
