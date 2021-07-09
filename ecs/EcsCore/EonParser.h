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
	bool operator==(const Id& id) const;
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
	LinkedList<Id> req;
	
	void operator=(const LoopDefinition& v) {id = v.id; stmts <<= v.stmts; ret_list <<= v.ret_list; req <<= v.req;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct ChainDefinition {
	LinkedList<Statement> ret_list;
	LinkedList<LoopDefinition> loops;
	LinkedList<ChainDefinition> subchains;
	Id id;
	
	void operator=(const ChainDefinition& v) {ret_list <<= v.ret_list; loops <<= v.loops; subchains <<= v.subchains; id = v.id;}
	String GetTreeString(int indent=0) const;
};

struct Value {
	typedef enum : byte {
		VAL_INVALID,
		VAL_CUSTOMER,
		VAL_STRING,
		VAL_INT,
		VAL_DOUBLE,
		VAL_BOOLEAN,
		VAL_ID
	} Type;
	
	Type type = VAL_INVALID;
	LoopDefinition customer;
	String str;
	bool b;
	int i;
	double f;
	Id id;
	
	
	Value() {}
	Value(const Value& v) {*this = v;}
	void operator=(const Value& v) {
		type = v.type;
		customer = v.customer;
		str = v.str;
		b = v.b;
		i = v.i;
		f = v.f;
		id = v.id;
	}
	void SetBool(bool b) {type = VAL_BOOLEAN; this->b = b;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
	String GetValue() const;
};

struct Machine {
	LinkedList<ChainDefinition>		chains;
	LinkedList<Statement>			stmts;
	Id								id;
	
	void operator=(const Machine& v) {id = v.id; chains <<= v.chains;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct State {
	LinkedList<Statement>			stmts;
	LinkedList<Statement>			ret_list;
	Id								id;
	
	void operator=(const State& v) {stmts <<= v.stmts; ret_list <<= v.ret_list; id = v.id;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct GlobalScope {
	Array<Machine>					machs;
	Array<State>					states;
	
	String GetTreeString(int indent=0) const;
	
};

struct CompilationUnit {
	GlobalScope						list;
	
	String GetTreeString(int indent=0) const;
	
};




class Parser : public CParser {
	Eon::CompilationUnit cunit;
	
	
	bool Parse(Eon::CompilationUnit&);
	bool ParseStmt(Eon::Statement&);
	bool ParseStmtArguments(Eon::Statement&);
	bool ParseLoop(Eon::LoopDefinition&);
	bool ParseChain(Eon::ChainDefinition&);
	bool ParseId(Eon::Id&);
	bool ParseValue(Eon::Value&);
	bool ParseReturnStmt(Eon::Statement&);
	bool ParseRequirementStmt(Eon::Id&);
	bool EmptyStatement() {return Char(';');}
	bool ChainScope(Eon::ChainDefinition&);
	bool ParseLoopScope(Eon::LoopDefinition&);
	bool ParseGlobalScope(Eon::GlobalScope&);
	bool ParseMachine(Eon::Machine&);
	bool ParseMachineScope(Eon::Machine&);
	bool ParseState(Eon::State&);
	bool ParseStateScope(Eon::State&);
	
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
