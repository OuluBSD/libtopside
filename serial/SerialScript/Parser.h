#ifndef _SerialScript_Parser_h_
#define _SerialScript_Parser_h_

#if 0

NAMESPACE_SERIAL_BEGIN
namespace Script {


struct Value;

struct Statement {
	Id id;
	One<Value> value;
	Array<Statement> args;
	Array<Statement> sink_side_conds;
	Array<Statement> src_side_conds;
	
	void operator=(const Statement& v);
	String GetTreeString(int indent=0) const;
	String ToString() const;
	bool IsRouting() const;
	
};

struct ChainDefinition {
	LinkedList<StateDeclaration> states;
	LinkedList<Statement> ret_list;
	LinkedList<LoopDefinition> loops;
	LinkedList<ChainDefinition> subchains;
	Id id;
	
	void operator=(const ChainDefinition& v) {states <<= v.states; ret_list <<= v.ret_list; loops <<= v.loops; subchains <<= v.subchains; id = v.id;}
	String GetTreeString(int indent=0) const;
	void GetSubChainPointers(LinkedList<Script::ChainDefinition*>& ptrs);
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
	
	Type			type = VAL_INVALID;
	LoopDefinition	customer;
	String			str;
	bool			b = 0;
	int				i = 0;
	double			f = 0;
	Id				id;
	
	
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
	bool operator==(const Value& v) const {
		switch (type) {
			case VAL_INVALID:	return v.type == VAL_INVALID;
			case VAL_CUSTOMER:	return false;
			case VAL_STRING:	return str == v.str;
			case VAL_INT:		return i == v.i;
			case VAL_DOUBLE:	return f == v.f;
			case VAL_BOOLEAN:	return b == v.b;
			case VAL_ID:		return id == v.id;
			default: return false;
		}
	}
	void SetBool(bool b) {type = VAL_BOOLEAN; this->b = b;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
	String GetValue() const;
	bool IsBoolean() const {return type == VAL_BOOLEAN;}
	bool IsString() const {return type == VAL_STRING;}
	bool IsId() const {return type == VAL_ID;}
	
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
	Script::Id						id;
	
	String GetTreeString(int indent=0) const;
	
};

struct CompilationUnit {
	GlobalScope						list;
	
	String GetTreeString(int indent=0) const;
	
};




class Parser : public CParser {
	Script::CompilationUnit cunit;
	
	
	bool Parse(Script::CompilationUnit&);
	bool ParseStmt(Script::Statement&, bool allow_square_end=false);
	bool ParseStmtArguments(Script::Statement&);
	bool ParseStmtSideConditionals(Script::Statement&, bool src);
	bool ParseLoop(Script::LoopDefinition&);
	bool ParseChain(Script::ChainDefinition&);
	bool ParseId(Script::Id&);
	bool ParseValue(Script::Value&);
	bool ParseReturnStmt(Script::Statement&);
	bool ParseStateStmt(Script::StateDeclaration&);
	bool ParseRequirementStmt(Script::Id&);
	bool EmptyStatement() {return Char(';');}
	bool TrueStatement(Script::Statement&);
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
	
	bool Parse(const String& content, const String& filepath);
	
	Script::CompilationUnit& GetResult() {return cunit;}
	const Script::CompilationUnit& GetResult() const {return cunit;}
	
	void Dump() {LOG(cunit.GetTreeString());}
};


}
NAMESPACE_SERIAL_END


#endif
#endif
