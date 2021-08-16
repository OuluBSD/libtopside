#ifndef _Backend_Node_h_
#define _Backend_Node_h_

NAMESPACE_TOPSIDE_BEGIN


#define HINT_PKG	"pkg"
#define HINT_FILE	"file"

class Expression;
class Statement;
class Function;
class Field;
class Class;
class Namespace;
class CompilationUnit;


class NodeBase {
	
public:
	
	VectorMap<String,String>	hints;
	
public:
	
	NodeBase&	Hint(String key, String value) {hints.GetAdd(key) = value; return *this;}
	NodeBase&	WeakHint(String key, String value) {if (hints.Find(key) < 0) hints.Add(key, value); return *this;}
	
	String		GetHint(String key) const {return hints.Get(key, String());}
	
	
};

template <class T, class Parent>
class CompilerNode : public NodeBase {
	Parent*		parent = 0;
	T*			subparent = 0;
public:
	typedef CompilerNode CLASSNAME;
	CompilerNode() {}
	
	CompilerNode& SetParent(Parent* p) {parent = p; return *this;}
	CompilerNode& SetParent(T* p) {subparent = p; return *this;}
	
	void DefaultHintFromParent(String key) {
		NodeBase* pn = parent;
		NodeBase* sn = subparent;
		NodeBase* p = sn ? sn : pn;
		if (p)
			WeakHint(key, p->GetHint(key));
	}
	void DefaultHintsFromParent() {
		DefaultHintFromParent(HINT_PKG);
		DefaultHintFromParent(HINT_FILE);
	}
	
};


NAMESPACE_TOPSIDE_END

#endif
