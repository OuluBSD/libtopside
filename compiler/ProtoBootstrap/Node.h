#ifndef _Common_Node_h_
#define _Common_Node_h_


NAMESPACE_OULU_BEGIN


enum {
	// Default parser nodes
	NODE_NULL = 10000,
	NODE_TOKEN,
	NODE_PREPROCESSOR_ROOT,
	
};


class Node;

struct NodeData {
	VectorMap<String, String> attr;
	union  {
		int64 int_value;
		double dbl_value;
		Node* ptr_value;
	};
	
	
	NodeData() {Clear();}
	NodeData(const NodeData& n) {*this = n;}
	virtual ~NodeData() {}
	
	void operator=(const NodeData& n) {attr <<= n.attr; int_value = n.int_value;}
	
	void Clear() {attr.Clear(); int_value = 0;}
	int GetAttrCount() const {return attr.GetCount();}
	String GetAttrKey(int i) const {return attr.GetKey(i);}
	String GetAttr(int i) const {return attr[i];}
	
	virtual NodeData* Clone() const {return new NodeData(*this);}
	
};


class Node : Moveable<Node>, public ParentArray<Node> {
	
protected:
	friend class Parser;
	friend class MacroInterpreter;
	
	typedef ParentArray<Node> PA;
	
	int node_type = 0;
	char block = -1;
	Token tk;
	One<NodeData> data;
	
	
public:
	Node() {}
	Node(int type) {ASSERT(type >= NODE_NULL); this->node_type = type;}
	Node(const Node& n) {*this = n;}
	//Node(int type, const Node& n) {ASSERT(type >= NODE_NULL); CopyToken(n, type);}
	//~Node() {PA::Clear(); attr.Clear(); str_value.Clear();}
	~Node() {PA::Clear(); node_type = 0; tk.Clear(); data.Clear();}
	
	void SetBlock(int i) {ASSERT(i >= 0 && i <= 255); block = i;}
	
	Token& GetToken() {return tk;}
	const Token& GetToken() const {return tk;}
	String GetTokenFile() const {return GetToken().loc.file;}
	int GetTokenLine() const {return GetToken().loc.line;}
	int GetTokenCol() const {return GetToken().loc.col;}
	int GetTokenType() const {return GetToken().type;}
	String GetTypeString() const {return GetToken().GetTypeString();}
	String GetTokenString() const {return GetToken().str_value;}
	String GetTokenTextValue() const {return GetToken().GetTextValue();}
	FileLocation GetTokenLocation() const {return GetToken().loc;}
	NodeData* GetData() {if (data) return &*data; return 0;}
	const NodeData* GetData() const {if (data) return &*data; return 0;}
	int GetBlock() const {return block;}
	
	void operator=(const Node& n) {
		PA::Copy(n);
		node_type = n.node_type;
		block = n.block;
		tk = n.tk;
		data.Clear();
		if (n.data)
			data = n.data->Clone();
		ASSERT(node_type >= NODE_NULL);
	}
	
	Node& FromToken(const Token& t) {
		ASSERT(t.type != TK_EOF);
		node_type = NODE_TOKEN;
		tk = t;
		data.Clear();
		return *this;
	}
	
	/*Node& CopyToken(const Node& n, int type) {
		this->type = type;
		file = n.file;
		line = n.line;
		col = n.col;
		if (type == NODE_TOKEN) {
			str_value = n.str_value;
			int_value = n.int_value;
			dbl_value = n.dbl_value;
		}
		return *this;
	}
	Node& From(const Node& n) {
		file = n.file;
		line = n.line;
		col  = n.col;
		return *this;
	}
	bool operator==(const Node& n) const {
		if (type != n.type) return false;
		if (int_value != n.int_value) return false;
		if (dbl_value != n.dbl_value) return false;
		if (str_value != n.str_value) return false;
		if (ptr_value != n.ptr_value) return false;
		if (attr.GetCount() != n.attr.GetCount())
			return false;
		for(int i = 0; i < attr.GetCount(); i++)
			if (attr.GetKey(i) != n.attr.GetKey(i) || attr[i] != n.attr[i])
				return false;
		if (GetCount() != n.GetCount())
			return false;
		for(int i = 0; i < GetCount(); i++)
			if (!(At(i) == n.At(i)))
				return false;
		return true;
	}
	void Serialize(Stream& s) {PA::Serialize(s); s % attr % type % str_value % int_value % dbl_value % file % line % col;}
	void Jsonize(JsonIO& json) {
		PA::Jsonize(json);
		json
			("type", type)
			("str", str_value)
			("int", int_value)
			("dbl", dbl_value)
			("attr", attr)
			("file", file)
			("line", line)
			("col", col)
			;
	}
	
	*/
	
	Node& AddType(int node_type) {ASSERT(node_type >= NODE_NULL); Node& n = PA::Add(); n.node_type = node_type; return n;}
	
	Node& SetType(int i) {node_type = i; ASSERT(i >= NODE_NULL); return *this;}
	
	int GetType() const {return node_type;}
	bool IsType(int type) const {ASSERT(type >= NODE_NULL); return node_type == type;}
	bool IsTokenType(int type) const {return tk.IsType(type);}
	
	
	/*
	Node& Add(Node* n) {ASSERT(this != n && n->type >= NODE_NULL); Node& nn = PA::Add(n); return nn;}
	Node& Add(int type, const Node& tk) {ASSERT(type >= NODE_NULL); Node& n = PA::Add(); n.CopyToken(tk, type); return n;}
	Node& Add(int type, String text) {ASSERT(type >= NODE_NULL); Node& n = PA::Add(); n.type = type; n.SetString(text); return n;}
	Node& SetString(String txt) {str_value = txt; return *this;}
	Node& SetInt(int64 i) {int_value = i; return *this;}
	Node& Inc(int64 i) {int_value += i; return *this;}
	Node& SetDouble(double d) {dbl_value = d; return *this;}
	Node& SetPtr(Node* ptr) {ptr_value = ptr; return *this;}
	void Clear() {PA::Clear(); type = NODE_NULL; str_value.Clear(); attr.Clear();}
	void ClearNodes() {PA::Clear();}
	void ClearString() {str_value.Clear();}
	Node& Insert(int i, Node* n) {return PA::Insert(i, n);}
	Node& Insert(int i, int type) {ASSERT(type >= NODE_NULL); return PA::Insert(i).SetType(type);}
	Node& Insert(int i, int type, String txt) {ASSERT(type >= NODE_NULL); return PA::Insert(i).SetType(type).SetString(txt);}
	Node& Insert(int i, int type, const Node& tk) {ASSERT(type >= NODE_NULL); return PA::Insert(i).CopyToken(tk, type);}
	void Append(Node* n) {while(n->GetCount()) {Node& nn = PA::Add(n->PA::Detach(0)); ASSERT(&nn != this);} delete n;}
	Node& SetAttr(String key, String value) {attr.GetAdd(key) = value; return *this;}
	Node& Cat(String s) {str_value.Cat(s); return *this;}
	
	int64 GetInt() const {return int_value;}
	String GetString() const {return str_value;}
	Node* GetPtr() const {return ptr_value;}
	bool IsString(const String& ws) const {return str_value == ws;}
	String GetAttr(String key) const {int i = attr.Find(key); if (i == -1) return ""; return attr[i];}
	int GetAttrCount() const {return attr.GetCount();}
	String GetAttrKey(int i) const {return attr.GetKey(i);}
	String GetAttr(int i) const {return attr[i];}
	int GetFile() const {return file;}
	int GetLine() const {return line;}
	int GetCol() const {return col;}
	String GetTypeString() const {
		if (type == NODE_TOKEN) {
			Token t;
			t.type = int_value;
			return "token_(" + t.GetTypeString() + ")";
		}
		switch (type) {
			case NODE_NULL: return "null";
			//#include "Generated_EnumType_CPP14.inl"
		}
		
		return "<unknown:" + IntStr(type) + ">";
	}*/
};


String NodeTreeStringSimple(const Node& n, int depth=0, String tab="\t");


NAMESPACE_OULU_END


#endif
