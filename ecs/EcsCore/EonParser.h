#ifndef _EcsLib_EonParser_h_
#define _EcsLib_EonParser_h_

NAMESPACE_TOPSIDE_BEGIN

namespace Eon {

struct Id {
	LinkedList<String> parts;
	
	
	void operator=(const Id& v) {parts <<= v.parts;}
	String ToString() const;
	String GetTreeString(int indent=0) const;
};

struct Value;

struct Statement {
	Id id;
	One<Value> value;
	
	
	void operator=(const Statement& v);
	String GetTreeString(int indent=0) const;
};

struct CustomerDefinition {
	Id id;
	LinkedList<Statement> stmts;
	
	
	void operator=(const CustomerDefinition& v) {id = v.id; stmts <<= v.stmts;}
	String GetTreeString(int indent=0) const;
};

struct Value {
	typedef enum {
		VAL_INVALID,
		VAL_CUSTOMER,
		VAL_STRING,
		VAL_BOOLEAN,
		VAL_ID
	} Type;
	
	Type type = VAL_INVALID;
	CustomerDefinition customer;
	String str;
	bool b;
	Id id;
	
	
	Value() {}
	Value(const Value& v) {*this = v;}
	void operator=(const Value& v) {
		type = v.type;
		customer = v.customer;
		str = v.str;
		b = v.b;
		id = v.id;
	}
	void SetBool(bool b) {type = VAL_BOOLEAN; this->b = b;}
	String GetTreeString(int indent=0) const;
};

struct CompilationUnit {
	LinkedList<CustomerDefinition> customers;
	
	
	String GetTreeString(int indent=0) const;
};




class Parser : public CParser {
	Eon::CompilationUnit cunit;
	
	
	bool Parse(Eon::CompilationUnit&);
	bool Parse(Eon::Statement&);
	bool Parse(Eon::CustomerDefinition&);
	bool Parse(Eon::Id&);
	bool Parse(Eon::Value&);
	bool EmptyStatement() {return Char(';');}
	bool CustomerScope(Eon::CustomerDefinition&);
	
	void AddError(String msg);
	
public:
	Parser() {}
	
	bool Parse(String content, String filepath);
	
	Eon::CompilationUnit& GetResult() {return cunit;}
	const Eon::CompilationUnit& GetResult() const {return cunit;}
	
	void Dump() {LOG(cunit.GetTreeString());}
};

}
NAMESPACE_TOPSIDE_END

#endif
