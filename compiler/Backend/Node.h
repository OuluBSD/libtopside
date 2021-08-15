#ifndef _Backend_Node_h_
#define _Backend_Node_h_

NAMESPACE_TOPSIDE_BEGIN


class Expression;
class Statement;
class Function;
class Field;
class Class;
class Namespace;
class CompilationUnit;


template <class T, class Parent>
class CompilerNode {
	Parent*		parent = 0;
	T*			subparent = 0;
	VectorMap<String,String>	hints;
public:
	typedef CompilerNode CLASSNAME;
	CompilerNode() {}
	
	
	CompilerNode& SetParent(Parent* p) {parent = p; return *this;}
	CompilerNode& SetParent(T* p) {subparent = p; return *this;}
	CompilerNode& Hint(String key, String value) {hints.GetAdd(key) = value; return *this;}
	
	
};


NAMESPACE_TOPSIDE_END

#endif
