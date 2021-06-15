#ifndef _Editor_NodeItem_h_
#define _Editor_NodeItem_h_


#include "Clang.h"
#include "Common.h"


enum {CI_NULL, CI_PRJMGR, CI_PKG, CI_FILE, CI_AST};

class ClangItem {
	
protected:
	typedef Node<ClangItem> ClangNode;
	
	friend void ToString(ClangNode& node, int indent, String& s);
	
	String key, data;
	int int_data;
	
	int kind, type;
	
public:
	ClangItem();
	ClangItem(const ClangItem& ci) {*this = ci;}
	ClangItem& operator=(const ClangItem& ci) {
		key = ci.key;
		data = ci.data;
		int_data = ci.int_data;
		kind = ci.kind;
		type = ci.type;
		return *this;
	}
	
	void Serialize(Stream& s) {s % key % data % int_data % kind % type;}
	virtual Node<ClangItem>* GetNode() {return 0;}
	
	int    GetKind()   const {return kind;}
	int    GetType()   const {return type;}
	int    GetInt()    const {return int_data;}
	String GetString() const {return data;}
	String GetKey()    const {return key;}
	
	String GetKindString() const;
	String GetTypeString() const;
	
	ClangItem& SetKind(int i) {kind = i; return *this;}
	ClangItem& SetType(int i) {type = i; return *this;}
	ClangItem& SetInt(int i)  {int_data = i; return *this;}
	ClangItem& SetString(const String& s) {data = s; return *this;}
	ClangItem& SetKey(const String& s) {key = s; return *this;}
	
};



typedef Node<ClangItem> ClangNode;


ClangNode& NodeGetAdd(ClangNode& inner, String name);
inline ClangNode& NodeGetPackage(ClangNode& inner, String name) {return *NodeGetAdd(inner, name).SetType(CI_PKG).GetNode();}
inline ClangNode& NodeGetFile(ClangNode& inner, String name) {return *NodeGetAdd(inner, name).SetType(CI_FILE).GetNode();}

String Dump(ClangNode& node);



#endif
