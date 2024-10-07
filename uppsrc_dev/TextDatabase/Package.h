#ifndef _TextDatabase_Package_h_
#define _TextDatabase_Package_h_


BEGIN_TEXTLIB_NAMESPACE


typedef enum : int {
	// NOTE: this order can't be changed or data breaks!
	
	NODE_INVALID = -1,
	NODE_CLASS,
	NODE_FUNCTION,
	NODE_VARIABLE,
	
	NODE_EXPORTER,
	NODE_IMPORTER,
	NODE_LINKED_PROJECT,
	NODE_BUILD_TARGET,
	
	NODE_SYSTEM,
	NODE_FEATURES,
	NODE_FILE_LIST,
	NODE_FILE,
	NODE_DEBUG,
	NODE_WIZARD,
	NODE_DIRECTORY,
	NODE_MODULE,
	NODE_PACKAGE,
	NODE_META,
	NODE_METAWIZARD,
	
	// trash
	NODE_GEN_USER_ENTRY_POINT,
	NODE_GEN_FEATURES,
	NODE_GEN_SOFTWARE_ARCHITECTURE,
	NODE_GEN_MAIN_LOOP,
	NODE_GEN_ASSETS,
	NODE_GEN_CUSTOM_EDITOR,
	
	NODE_COUNT
} NodeType;


String GetNodeName(NodeType n);
String GetNodeName(int i);

struct Node {
	Node*			owner = 0;
	
	// Persistent
	NodeType		type = NODE_INVALID;
	int				ff_i = -1;
	String			name;
	Array<Node>		sub;
	ValueMap		data;
	
	String GetPathFrom(const Node& n) const {
		String s;
		const Node* p = owner;
		while (p && p != &n) {
			s = p->name + "/" + s;
			p = p->owner;
		}
		return s;
	}
	void FindParentDeep(Vector<Node*>& nodes, const String& name, NodeType type) {
		Node* n = this;
		while (n) {
			Node* found = FindNode(name, type);
			if (found)
				nodes << found;
			n = n->owner;
		}
	}
	void FindParentDeep(Vector<Node*>& nodes, NodeType type) {
		Node* n = this;
		while (n) {
			for (Node& n : n->sub)
				if (n.type == type)
					nodes << &n;
			n = n->owner;
		}
	}
	void FindChildDeep(Vector<Node*>& nodes, NodeType type) {
		if (this->type == type) nodes << this;
		for (Node& n : sub)
			n.FindChildDeep(nodes, type);
	}
	Node* FindNode(const String& name, NodeType type){
		for (Node& n : sub)
			if (n.name == name && n.type == type)
				return &n;
		return 0;
	}
	Node& GetAddNode(const String& name, NodeType type, bool ignore_type=false) {
		for (Node& n : sub)
			if (n.name == name && (ignore_type || n.type == type))
				return n;
		Node& n = sub.Add();
		n.owner = this;
		n.name = name;
		n.type = type;
		return n;
	}
	void Remove(Node& n) {
		for(int i = 0; i < sub.GetCount(); i++)
			if (&sub[i] == &n)
				{sub.Remove(i); break;}
	}
	void Jsonize(JsonIO& json) {
		json
			("type", (int&)type)
			("ff_i", ff_i)
			("name", name)
			("sub", sub)
			("data", data)
			;
		if (json.IsLoading())
			for (auto& s : sub)
				s.owner = this;
	}
	
	ValueArray GetArray(const String& key) {
		Value& v = data.GetAdd(key);
		if (!v.Is<ValueArray>())
			v = ValueArray();
		return v;
	}
	ValueMap GetMap(const String& key) {
		Value& v = data.GetAdd(key);
		if (!v.Is<ValueMap>())
			v = ValueMap();
		return v;
	}
};


struct Package {
	// Temp
	String			json_path;
	
	// Persistent
	String			name;
	Node			root;
	
	void StoreToFile();
	void LoadFromFile(String json_path);
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("root", root)
			;
	}
};


END_TEXTLIB_NAMESPACE


#endif
