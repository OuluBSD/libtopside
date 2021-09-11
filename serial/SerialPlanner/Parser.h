#ifndef _SerialPlanner_Parser_h_
#define _SerialPlanner_Parser_h_


NAMESPACE_SERIAL_BEGIN
namespace Script {


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
	void GetSubChainPointers(LinkedList<Script::ChainDefinition*>& ptrs);
};

struct DriverDefinition {
	LinkedList<Statement> stmts;
	Id id;
	
	void operator=(const DriverDefinition& v) {id = v.id; stmts <<= v.stmts;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
	
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

struct MachineDefinition {
	LinkedList<ChainDefinition>		chains;
	LinkedList<Statement>			stmts;
	LinkedList<DriverDefinition>	drivers;
	Id								id;
	
	void operator=(const MachineDefinition& v) {id = v.id; chains <<= v.chains;}
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
	Array<MachineDefinition>		machs;
	Array<State>					states;
	
	String GetTreeString(int indent=0) const;
	
};

struct AtomilationUnit {
	GlobalScope						list;
	
	String GetTreeString(int indent=0) const;
	
};




class Parser : public CParser {
	Script::AtomilationUnit cunit;
	
	
	bool Parse(Script::AtomilationUnit&);
	bool ParseStmt(Script::Statement&);
	bool ParseStmtArguments(Script::Statement&);
	bool ParseLoop(Script::LoopDefinition&);
	bool ParseChain(Script::ChainDefinition&);
	bool ParseId(Script::Id&);
	bool ParseValue(Script::Value&);
	bool ParseReturnStmt(Script::Statement&);
	bool ParseRequirementStmt(Script::Id&);
	bool EmptyStatement() {return Char(';');}
	bool ChainScope(Script::ChainDefinition&);
	bool ParseLoopScope(Script::LoopDefinition&);
	bool ParseGlobalScope(Script::GlobalScope&);
	bool ParseMachine(Script::MachineDefinition&);
	bool ParseMachineScope(Script::MachineDefinition&);
	bool ParseState(Script::State&);
	bool ParseStateScope(Script::State&);
	bool ParseDriverDefinition(Script::DriverDefinition&);
	bool ParseDriverDefinitionScope(Script::DriverDefinition&);
	
	void AddError(String msg);
	
public:
	Parser() {}
	
	bool Parse(String content, String filepath);
	
	Script::AtomilationUnit& GetResult() {return cunit;}
	const Script::AtomilationUnit& GetResult() const {return cunit;}
	
	void Dump() {LOG(cunit.GetTreeString());}
};


}
NAMESPACE_SERIAL_END


#endif
