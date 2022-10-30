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
	
	
	ArrayMap<String, Object> values;
	
public:
	
	WorldState();
	void Clear();
	
	bool Set(int index, bool value);
	bool Set(int index, String value);
	bool Set(const String& key, bool value);
	bool Set(const String& key, String value);
	void SetTrue(const String& key) {Set(key, true);}
	void SetFalse(const String& key) {Set(key, false);}
	bool IsTrue(const String& key, bool def=false) const;
	bool IsFalse(const String& key, bool def=true) const;
	bool IsFalse(int idx) const;
	bool IsUndefined(const String& key) const;
	bool IsUndefined(int idx) const;
	bool IsEmpty() const {return values.IsEmpty();}
	int GetValueCount() const;
	void FindKeys(String key_left, Index<String>& keys) const;
	String Get(const String& key, String def="") const;
	String Get(int idx) const;
	Size GetSize(const String& cx, const String& cy, Size def=Size(0,0)) const;
	int GetInt(const String& key, int def=0) const;
	double GetDouble(const String& key, double def=0) const;
	bool GetBool(const String& key, bool def=false) const;
	String GetString(const String& key, String def="") const;
	hash_t GetHashValue() const;
	String ToString() const;
	String GetFullString() const;
	bool Contains(const WorldState& ws) const;
	bool Conflicts(const WorldState& ws) const;
	int Compare(int idx, const WorldState& ws) const;
	
	WorldState& operator=(const WorldState& src);
	
	const ArrayMap<String, Object>& GetValues() const {return values;}
	
	bool operator==(const WorldState& ws) const {return GetHashValue() == ws.GetHashValue();}
	bool operator!=(const WorldState& ws) const {return GetHashValue() != ws.GetHashValue();}
	
};



}
}
NAMESPACE_TOPSIDE_END


#endif
