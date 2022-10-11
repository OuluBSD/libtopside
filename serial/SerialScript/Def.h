#ifndef _SerialScript_Def_h_
#define _SerialScript_Def_h_

NAMESPACE_SERIAL_BEGIN
using namespace Parallel;

namespace Script {



struct Id {
	LinkedList<String> parts;
	
	
	Id() {}
	Id(const Id& o) {*this = o;}
	Id(Id&& o) {Swap(parts, o.parts);}
	
	void Clear() {parts.Clear();}
	void Set(String s) {parts.Clear(); parts.Add(s);}
	void operator=(const Id& v) {parts <<= v.parts;}
	String ToString() const;
	String GetTreeString(int indent=0) const;
	bool operator==(const Id& id) const;
	bool IsEmpty() const {return parts.IsEmpty();}
	void Append(const Id& id) {parts.Append(id.parts);}
	
};

struct AtomDefinition {
	struct LinkCandidate : Moveable<LinkCandidate> {
		AtomDefinition* atom = 0;
		VectorMap<String, Object> req_args;
		
		LinkCandidate() {}
		LinkCandidate(const LinkCandidate& v) {*this = v;}
		void operator=(const LinkCandidate& v) {atom = v.atom; req_args <<= v.req_args;}
	};
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	IfaceConnTuple					iface;
	LinkTypeCls						link;
	VectorMap<int, LinkCandidate>	src_link_cands, sink_link_cands;
	
	AtomDefinition() {}
	AtomDefinition(const AtomDefinition& v) {*this = v;}
	void Set(String key, const Object& val) {args.GetAdd(key) = val;}
	void operator=(const AtomDefinition& v) {id = v.id; loc = v.loc; args <<= v.args; iface = v.iface; src_link_cands <<= v.src_link_cands; sink_link_cands <<= v.sink_link_cands;}
	
};


struct LoopDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	Array<AtomDefinition>			atoms;
	bool							is_driver = false;
	
	LoopDefinition() {}
	LoopDefinition(const LoopDefinition& v) {*this = v;}
	void Set(const String& key, const Object& value) {args.GetAdd(key) = value;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
	void operator=(const LoopDefinition& v) {id = v.id; loc = v.loc; args <<= v.args; atoms <<= v.atoms; is_driver = v.is_driver;}
};

struct StateDeclaration {
	Id id;
	FileLocation loc;
	
	StateDeclaration() {}
	StateDeclaration(const StateDeclaration& v) {*this = v;}
	void operator=(const StateDeclaration& v) {id = v.id; loc = v.loc;}
	
};

struct ChainDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	LinkedList<StateDeclaration>	states;
	LinkedList<LoopDefinition>		loops;
	LinkedList<ChainDefinition>		subchains;
	
	ChainDefinition() {}
	ChainDefinition(const ChainDefinition& v) {*this = v;}
	void Clear() {id.Clear(); args.Clear(); states.Clear(); loops.Clear(); subchains.Clear();}
	void operator=(const ChainDefinition& v) {id = v.id; loc = v.loc; args <<= v.args; states <<= v.states; loops <<= v.loops; subchains <<= v.subchains;}
	String GetTreeString(int indent=0) const;
	void GetSubChainPointers(LinkedList<Script::ChainDefinition*>& ptrs);
};

struct DriverDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	
	DriverDefinition() {}
	DriverDefinition(const DriverDefinition& v) {*this = v;}
	void operator=(const DriverDefinition& v) {id = v.id; loc = v.loc; args <<= v.args;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
	void operator=(const ChainDefinition& v) {id = v.id; loc = v.loc; args <<= v.args;}
	
};

struct ComponentDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	
	ComponentDefinition() {}
	ComponentDefinition(const ComponentDefinition& v) {*this = v;}
	void operator=(const ComponentDefinition& v) {id = v.id; loc = v.loc; args <<= v.args;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct EntityDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	LinkedList<ComponentDefinition>	comps;
	
	EntityDefinition() {}
	EntityDefinition(const EntityDefinition& v) {*this = v;}
	void operator=(const EntityDefinition& v) {id = v.id; loc = v.loc; args <<= v.args; comps <<= v.comps;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct EcsSysDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	
	EcsSysDefinition() {}
	EcsSysDefinition(const EcsSysDefinition& v) {*this = v;}
	void operator=(const EcsSysDefinition& v) {id = v.id; loc = v.loc; args <<= v.args;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct PoolDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	LinkedList<EntityDefinition>	ents;
	LinkedList<PoolDefinition>		pools;
	
	PoolDefinition() {}
	PoolDefinition(const PoolDefinition& v) {*this = v;}
	void operator=(const PoolDefinition& v) {id = v.id; loc = v.loc; args <<= v.args; ents <<= v.ents; pools <<= v.pools;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct WorldDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	LinkedList<EcsSysDefinition>	systems;
	LinkedList<PoolDefinition>		pools;
	
	WorldDefinition() {}
	WorldDefinition(const WorldDefinition& v) {*this = v;}
	void operator=(const WorldDefinition& v) {id = v.id; loc = v.loc; args <<= v.args; systems <<= v.systems; pools <<= v.pools;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct MachineDefinition {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	LinkedList<ChainDefinition>		chains;
	LinkedList<DriverDefinition>	drivers;
	
	MachineDefinition() {}
	MachineDefinition(const MachineDefinition& v) {*this = v;}
	void operator=(const MachineDefinition& v) {id = v.id; loc = v.loc; args <<= v.args; chains <<= v.chains; drivers <<= v.drivers;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct State {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	ArrayMap<String, Object>		ret_list;
	
	State() {}
	State(const State& v) {*this = v;}
	void operator=(const State& v) {id = v.id; loc = v.loc; args <<= v.args; ret_list <<= v.ret_list;}
	String GetTreeString(int indent=0) const;
	String ToString() const;
};

struct GlobalScope {
	Id								id;
	FileLocation					loc;
	ArrayMap<String, Object>		args;
	Array<MachineDefinition>		machs;
	Array<WorldDefinition>			worlds;
	Array<State>					states;
	
	GlobalScope() {}
	GlobalScope(const GlobalScope& v) {*this = v;}
	void operator=(const GlobalScope& v) {id = v.id; loc = v.loc; args <<= v.args; machs <<= v.machs; worlds <<= v.worlds; states <<= v.states;}
	String GetTreeString(int indent=0) const;
	void Clear() {machs.Clear(); states.Clear(); id.Clear();}
	
};

struct CompilationUnit {
	GlobalScope						glob;
	
	CompilationUnit() {}
	CompilationUnit(const CompilationUnit& v) {*this = v;}
	void operator=(const CompilationUnit& v) {glob = v.glob;}
	String GetTreeString(int indent=0) const;
	
};




}
NAMESPACE_SERIAL_END

#endif
