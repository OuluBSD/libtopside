#ifndef _ParallelCore_Serial_h_
#define _ParallelCore_Serial_h_


NAMESPACE_TOPSIDE_BEGIN
namespace Serial {

class ScriptLoader;
class ScriptLoopLoader;
class ScriptDriverLoader;

namespace Script {
using namespace Parallel;


class ActionPlanner;
class ActionNode;
struct Statement;


class WorldState : public Moveable<WorldState> {

public:
	typedef enum : byte {
		INVALID,
		ADD_COMP,
	} Type;
	
protected:
	friend class ActionPlanner;
	friend class ActionPlannerWrapper;
	friend class ActionNode;
	friend class ::TS::Serial::ScriptLoader;
	friend class ::TS::Serial::ScriptLoopLoader;
	friend class ::TS::Serial::ScriptDriverLoader;
	
	static const bool use_debugging_order = true;
	
	Vector<String>				values;
	Vector<bool>				using_act;
	Index<short>				dbg_order;
	AtomTypeCls					cur_atom;
	ValDevCls					sink_vd;
	ValDevCls					side_vd;
	Type						type = INVALID;
	ActionPlanner*				ap = 0;
	
public:
	
	WorldState();
	void Clear();
	
	const        Script::Statement* FindStatement(const WorldState* ws, LinkedList<Statement>& stmts, bool dbg_print=false) const;
	static const Script::Statement* FindStatement(const String& find_key, LinkedList<Statement>& stmts, bool dbg_print=false);
	
	bool Append(const WorldState& ws, LinkedList<Statement>& ret_list);
	void SetActionPlanner(ActionPlanner& ap) {this->ap = &ap;}
	bool Set(int index, bool value);
	bool Set(int index, String value);
	bool Set(const String& key, bool value);
	bool Set(const String& key, String value);
	void SetTrue(const String& key) {Set(key, true);}
	void SetFalse(const String& key) {Set(key, false);}
	void SetAs_AddAtom(AtomTypeCls atom) {type = ADD_COMP; cur_atom = atom;}
	void SetSideCls(ValDevCls vd) {side_vd = vd;}
	void SetSinkCls(ValDevCls vd) {sink_vd = vd;}
	
	ActionPlanner& GetActionPlanner() const {return *ap;}
	bool IsAddAtom() const {return type == ADD_COMP;}
	bool IsTrue(const String& key) const;
	bool IsFalse(const String& key) const;
	bool IsFalse(int idx) const;
	bool IsUndefined(const String& key) const;
	bool IsUndefined(int idx) const;
	bool IsEmpty() const {return values.IsEmpty();}
	String Get(const String& key) const;
	String Get(int idx) const;
	Size GetSize(const String& cx, const String& cy, Size def=Size(0,0)) const;
	bool GetBool(const String& key, bool def=false) const;
	String GetString(const String& key, String def="") const;
	hash_t GetHashValue() const;
	AtomTypeCls GetAtom() const {return cur_atom;}
	ValDevCls GetCommonSink() const {return sink_vd;}
	ValDevTuple GetInterfaceSink() const {ASSERT(cur_atom.IsValid()); return cur_atom.iface.sink;}
	ValDevTuple GetInterfaceSource() const {ASSERT(cur_atom.IsValid()); return cur_atom.iface.src;}
	const ValDevCls& GetSideCls() const {return side_vd;}
	const ValDevCls& GetSinkCls() const {return sink_vd;}
	String ToString() const;
	String GetFullString() const;
	bool Contains(const WorldState& ws) const;
	bool Conflicts(const WorldState& ws) const;
	int Compare(int idx, const WorldState& ws) const;
	
	WorldState& operator=(const WorldState& src);
	
	bool operator==(const WorldState& ws) const {return GetHashValue() == ws.GetHashValue();}
	bool operator!=(const WorldState& ws) const {return GetHashValue() != ws.GetHashValue();}
	
};


class Action : public Moveable<Action> {
	
protected:
	friend class ActionPlanner;
	friend class ActionNode;
	friend class ActionPlannerWrapper;
	friend class Factory;
	
	WorldState				precond;
	WorldState				postcond;
	double					cost;
	
public:

	Action();
	Action(const WorldState& cond) : precond(cond), postcond(cond), cost(0) {}
	
	const WorldState& Pre() const {return precond;}
	const WorldState& Post() const {return postcond;}
	WorldState& Pre() {return precond;}
	WorldState& Post() {return postcond;}
	
	bool IsAddAtom() const {return postcond.IsAddAtom();}
	
};


}
}
NAMESPACE_TOPSIDE_END


#endif
