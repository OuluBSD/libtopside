#ifndef _EonCore_Parser_h_
#define _EonCore_Parser_h_

NAMESPACE_EON_BEGIN


struct IdPath {
	LinkedList<String> parts;
	
	
	void Set(String s) {parts.Clear(); parts.Add(s);}
	void operator=(const IdPath& v) {parts <<= v.parts;}
	String ToString() const;
	String GetTreeString(int indent=0) const;
	bool operator==(const IdPath& id) const;
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
	LinkedList<IdPath> req;
	
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
	void GetSubChainPointers(LinkedList<ChainDefinition*>& ptrs);
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

struct CompilationUnit {
	GlobalScope						list;
	
	String GetTreeString(int indent=0) const;
	
};




class Parser : public CParser {
	CompilationUnit cunit;
	
	
	bool Parse(CompilationUnit&);
	bool ParseStmt(Statement&);
	bool ParseStmtArguments(Statement&);
	bool ParseLoop(LoopDefinition&);
	bool ParseChain(ChainDefinition&);
	bool ParseId(IdPath&);
	bool ParseValue(Value&);
	bool ParseReturnStmt(Statement&);
	bool ParseRequirementStmt(IdPath&);
	bool EmptyStatement() {return Char(';');}
	bool ChainScope(ChainDefinition&);
	bool ParseLoopScope(LoopDefinition&);
	bool ParseGlobalScope(GlobalScope&);
	bool ParseMachine(MachineDefinition&);
	bool ParseMachineScope(MachineDefinition&);
	bool ParseState(State&);
	bool ParseStateScope(State&);
	
	void AddError(String msg);
	
public:
	Parser() {}
	
	bool Parse(String content, String filepath);
	
	CompilationUnit& GetResult() {return cunit;}
	const CompilationUnit& GetResult() const {return cunit;}
	
	void Dump() {LOG(cunit.GetTreeString());}
};


NAMESPACE_EON_END

#endif
