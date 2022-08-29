#ifndef _SerialScript_Parser_h_
#define _SerialScript_Parser_h_


NAMESPACE_SERIAL_BEGIN
using namespace Parallel;

namespace Script {


struct Id {
	LinkedList<String> parts;
	
	
	Id() {}
	Id(const Id& o) {*this = o;}
	Id(Id&& o) {Swap(parts, o.parts);}
	
	void Set(String s) {parts.Clear(); parts.Add(s);}
	void operator=(const Id& v) {parts <<= v.parts;}
	String ToString() const;
	String GetTreeString(int indent=0) const;
	bool operator==(const Id& id) const;
	bool IsEmpty() const {return parts.IsEmpty();}
	void Append(const Id& id) {parts.Append(id.parts);}
	
};

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

struct LoopDefinition {
	Id id;
	LinkedList<Statement> stmts;
	LinkedList<Statement> ret_list;
	LinkedList<Id> req;
	
	void operator=(const LoopDefinition& v) {id = v.id; stmts <<= v.stmts; ret_list <<= v.ret_list; req <<= v.req;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct StateDeclaration {
	Id id;
	
	void operator=(const StateDeclaration& v) {id = v.id;}
	
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
	Object ToObject() const;
	bool IsBoolean() const {return type == VAL_BOOLEAN;}
	bool IsString() const {return type == VAL_STRING;}
	bool IsId() const {return type == VAL_ID;}
	
};

struct ComponentDefinition {
	LinkedList<Statement>			stmts;
	Id								id;
	
	void operator=(const ComponentDefinition& v) {id = v.id; stmts <<= v.stmts;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct EntityDefinition {
	LinkedList<ComponentDefinition>	comps;
	Id								id;
	
	void operator=(const EntityDefinition& v) {id = v.id; comps <<= v.comps;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct EcsSysDefinition {
	LinkedList<Statement>			stmts;
	Id								id;
	
	void operator=(const EcsSysDefinition& v) {id = v.id; stmts <<= v.stmts;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct PoolDefinition {
	LinkedList<EntityDefinition>	ents;
	LinkedList<PoolDefinition>		pools;
	Id								id;
	
	void operator=(const PoolDefinition& v) {id = v.id; ents <<= v.ents; pools <<= v.pools;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct EngineDefinition {
	LinkedList<EcsSysDefinition>	systems;
	LinkedList<PoolDefinition>		pools;
	Id								id;
	
	void operator=(const EngineDefinition& v) {id = v.id; systems <<= v.systems; pools <<= v.pools;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
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
	Array<EngineDefinition>			engs;
	Array<State>					states;
	Script::Id						id;
	
	String GetTreeString(int indent=0) const;
	
};

struct CompilationUnit {
	GlobalScope						list;
	
	String GetTreeString(int indent=0) const;
	
};




class Parser : public CParser {
	One<Script::CompilationUnit> cunit;
	
	
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
	bool ParseEngine(Script::EngineDefinition&);
	bool ParseEngineScope(Script::EngineDefinition&);
	bool ParseEcsSystem(Script::EcsSysDefinition&);
	bool ParseEcsSystemScope(Script::EcsSysDefinition&);
	bool ParsePool(Script::PoolDefinition&);
	bool ParsePoolScope(Script::PoolDefinition&);
	bool ParseEntity(Script::EntityDefinition&);
	bool ParseEntityScope(Script::EntityDefinition&);
	bool ParseComponentDefinition(Script::ComponentDefinition&);
	bool ParseComponentDefinitionScope(Script::ComponentDefinition&);
	bool ParseMachine(Script::MachineDefinition&);
	bool ParseMachineScope(Script::MachineDefinition&);
	bool ParseState(Script::State&);
	bool ParseStateScope(Script::State&);
	bool ParseDriverDefinition(Script::DriverDefinition&);
	bool ParseDriverDefinitionScope(Script::DriverDefinition&);
	
	void AddError(String msg);
	
public:
	Parser();
	
	bool Parse(const String& content, const String& filepath);
	
	Script::CompilationUnit& GetResult() {return *cunit;}
	Script::CompilationUnit* DetachResult() {return cunit.Detach();}
	const Script::CompilationUnit& GetResult() const {return *cunit;}
	
	void Dump();
	
};


}
NAMESPACE_SERIAL_END


#endif
