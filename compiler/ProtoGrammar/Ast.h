#ifndef _ProtoGrammar_Ast_h_
#define _ProtoGrammar_Ast_h_


#ifndef flagBOOTSTRAP

NAMESPACE_TOPSIDE_BEGIN
namespace Ast {


struct Type {
	
	
};


struct Node {
	Type* type = 0;
	
	
	Node();
	virtual ~Node() {}
	
	
};


struct Literal : public Node {
	union {
		int64  i64;
		uint64 u64;
		int32  i32[2];
		uint32 u32[2];
		int16  i16[4];
		uint16 u16[4];
		int8  i8[8];
		uint8 u8[8];
		float f[2];
		double d;
	};
	String str;
	
	
	Literal(String s) : str(s) {}
	
};

struct Name {
	String str;
	
};


struct NamedNode : public Node {
	Name name;
	
};


/*struct TypedNode : public Node {
	Type type;
	
};*/


struct Field : public NamedNode {
	
	
};


struct Expression : public Node {
	
	
};


struct Statement : public Node {
	
	
};


struct Function : public Node {
	
	
};


struct FunctionIdScope : public NamedNode {
	ArrayMap<String,Function> variants;
	
	
};


struct Class;

struct Scope : public Node {
	ArrayMap<String, Field>				fields;
	ArrayMap<String, FunctionIdScope>	funcs;
	ArrayMap<String, Class>				classes;
	Array<Statement>					stmts;
	Scope* container = 0;
	
	
	NamedNode* FindInVisible(String id);
	NamedNode* FindInScope(String id);
	
};


struct Namespace : public Scope {
	
	
	
};


struct Class : public NamedNode {
	
	
	
};

/*struct ClassIdScope : public NamedNode {
	ArrayMap<String,Class> variants;
	
	
};*/


}
NAMESPACE_TOPSIDE_END

#endif
#endif
