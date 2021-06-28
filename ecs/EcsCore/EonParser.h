#ifndef _EcsLib_EonParser_h_
#define _EcsLib_EonParser_h_

NAMESPACE_ECS_BEGIN

namespace Eon {

struct Id {
	LinkedList<String> parts;
	
	
	void Set(String s) {parts.Clear(); parts.Add(s);}
	void operator=(const Id& v) {parts <<= v.parts;}
	String ToString() const;
	String GetTreeString(int indent=0) const;
};

struct Value;

struct Statement {
	Id id;
	One<Value> value;
	Array<Statement> args;
	
	void operator=(const Statement& v);
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct LoopDefinition {
	Id id;
	LinkedList<Statement> stmts;
	LinkedList<Statement> ret_list;
	
	void operator=(const LoopDefinition& v) {id = v.id; stmts <<= v.stmts; ret_list <<= v.ret_list;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct SidechainDefinition {
	typedef enum : byte {
		CENTER,
		NET
	} Type;
	
	LinkedList<SidechainDefinition> chains;
	LinkedList<LoopDefinition> loops;
	LinkedList<Statement> ret_list;
	Type type;
	Id id;
	
	String GetTypeString() const;
	String GetTreeString(int indent=0) const;
	
};

struct Value {
	typedef enum : byte {
		VAL_INVALID,
		VAL_CUSTOMER,
		VAL_STRING,
		VAL_BOOLEAN,
		VAL_ID
	} Type;
	
	Type type = VAL_INVALID;
	LoopDefinition customer;
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
	String ToString() const;
	String GetValue() const;
};

struct CompilationUnit {
	SidechainDefinition					main;
	
	String GetTreeString(int indent=0) const;
	
};




class Parser : public CParser {
	Eon::CompilationUnit cunit;
	
	
	bool Parse(Eon::CompilationUnit&);
	bool ParseStmt(Eon::Statement&);
	bool ParseStmtArguments(Eon::Statement&);
	bool ParseLoop(Eon::LoopDefinition&);
	bool ParseSidechain(Eon::SidechainDefinition&, Eon::SidechainDefinition::Type);
	bool ParseId(Eon::Id&);
	bool ParseValue(Eon::Value&);
	bool ParseReturnStmt(Eon::Statement&);
	bool EmptyStatement() {return Char(';');}
	bool SidechainScope(Eon::SidechainDefinition&);
	bool SidechainStmtList(Eon::SidechainDefinition&);
	bool LoopScope(Eon::LoopDefinition&);
	
	void AddError(String msg);
	
public:
	Parser() {}
	
	bool Parse(String content, String filepath);
	
	Eon::CompilationUnit& GetResult() {return cunit;}
	const Eon::CompilationUnit& GetResult() const {return cunit;}
	
	void Dump() {LOG(cunit.GetTreeString());}
};

}
NAMESPACE_ECS_END

#endif
