#ifndef _Language_Parser_h_
#define _Language_Parser_h_

NAMESPACE_LANGUAGE_BEGIN

enum {
	NODE_NULL=1000,
	NODE_ROOT,
	NODE_TEXT,
	NODE_SETTING_SCOPE,
	NODE_SETTING_KEY,
	NODE_BOLD,
	NODE_ITALIC,
	NODE_TRANSLITERATION,
	NODE_SEPARATOR,
	NODE_PARENTHESIS,
	NODE_VERTGROUP,
	NODE_HORZGROUP,
	NODE_SIGN,
	NODE_CARTOUCHE,
	NODE_WORD,
	NODE_SPACE,
	NODE_NL,
	NODE_LEMMA,
	NODE_SENTENCE,
};

#define NODEATTR_POS	"pos"

class Node {
	Array<Node> sub;
	VectorMap<String, Value> attr;
	
	int type = NODE_NULL;
	
	WString text;
	int int_value = 0;
public:
	
	Node() {}
	Node(const Node& n) {*this = n;}
	Node(int type, WString txt) {this->type = type; text = txt;}
	
	void operator=(const Node& n) {
		sub <<= n.sub;
		attr <<= n.attr;
		type = n.type;
		text = n.text;
		int_value = n.int_value;
	}
	void Serialize(Stream& s) {s % sub % attr % type % text % int_value;}
	void Jsonize(JsonIO& json) {
		json
			("type", type)
			("text", text)
			("int", int_value)
			("sub", sub)
			("attr", attr);
	}
	
	Node& Add(int type) {Node& n = sub.Add(); n.type = type; return n;}
	Node& Add(Node* n) {Node& nn = sub.Add(n); return nn;}
	Node& Add(int type, WString text) {Node& n = sub.Add(); n.type = type; n.SetText(text); return n;}
	Node& SetType(int i) {type = i; return *this;}
	Node& SetText(WString txt) {text = txt; return *this;}
	Node& AppendText(WString txt) {text += txt; return *this;}
	Node& SetInt(int i) {int_value = i; return *this;}
	void Clear() {sub.Clear(); type = 0; text.Clear();}
	void ClearNodes() {sub.Clear();}
	void ClearText() {text.Clear();}
	void Remove(int i) {sub.Remove(i);}
	void Remove(int i, int count) {sub.Remove(i, count);}
	Node* Detach(int i) {return sub.Detach(i);}
	Node& Insert(int i, Node* n) {return sub.Insert(i, n);}
	Node& Insert(int i) {return sub.Insert(i);}
	Node& Insert(int i, int type, WString txt) {return sub.Insert(i).SetType(type).SetText(txt);}
	void Append(Node* n) {while(n->sub.GetCount()) {sub.Add(n->sub.Detach(0));} delete n;}
	Node& Top() {return sub.Top();}
	Node& SetAttr(String key, Value value) {attr.GetAdd(key) = value; return *this;}
	
	Node& At(int i) {return sub[i];}
	const Node& At(int i) const {return sub[i];}
	int GetCount() const {return sub.GetCount();}
	int GetType() const {return type;}
	int GetInt() const {return int_value;}
	WString GetText() const {return text;}
	bool IsType(int type) const {ASSERT(type >= NODE_NULL); return this->type == type;}
	bool IsText(const WString& ws) {return text == ws;}
	bool Contains(Node* n) const;
	Value GetAttr(String key) const {int i = attr.Find(key); if (i == -1) return Value(); return attr[i];}
	Value GetAttr(int i) const {return attr[i];}
	String GetAttrKey(int i) const {return attr.GetKey(i);}
	int GetAttrCount() const {return attr.GetCount();}
	
	String GetTypeString() const;
};

struct ParserExc : public String {
	ParserExc() {}
	ParserExc(String s) : String(s) {}
};

struct ParserError : Moveable<ParserError> {
	int line = 0, col = 0;
	String what;
	
	ParserError& Set(int l, int c, String s) {line = l; col = c; what = s; return *this;}
};

class Parser {
	
protected:
	Vector<ParserError> errors;
	
public:
	
	
	virtual bool Parse(WString txt) = 0;
	
};

String NodeTreeString(const Node& n, int depth=0, int max_depth=100);


NAMESPACE_LANGUAGE_END

#endif
