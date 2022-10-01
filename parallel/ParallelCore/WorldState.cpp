#include "ParallelCore.h"
#include <SerialScript/SerialScript.h>


NAMESPACE_TOPSIDE_BEGIN
namespace Serial {
using namespace Parallel;


namespace Script {


WorldState::WorldState() {
	
	Clear();
}

void WorldState::Clear() {
	values.Clear();
	//using_act.Clear();
	//cur_atom = Null;
	//type = INVALID;
}

int WorldState::GetValueCount() const {
	// this is a bit ankward counting
	int c = 0;
	for (const String& v : values.GetValues())
		c += (v.IsEmpty() ? 0 : 1);
	return c;
}

#if 0

void WorldState::FindKeys(String key_left, Index<String>& keys) const {
	for(int i = 0; i < values.GetCount(); i++) {
		if (values[i].IsEmpty())
			continue;
		String key = ap->GetAtomKey(i);
		if (key.Left(key_left.GetCount()) == key_left)
			keys.FindAdd(key);
	}
}

#endif
/*
bool WorldState::Set(int index, bool value) {
	if (index < 0) return false;
	if (using_act.GetCount() <= index) {
		using_act.SetCount(index+1, false);
		values.SetCount(index+1);
	}
	using_act[index] = true;
	values[index] = value ? "true" : "false";
	if (use_debugging_order)
		dbg_order.FindAdd(index);
	return true;
}

bool WorldState::Set(int index, String value) {
	if (index < 0) return false;
	if (using_act.GetCount() <= index) {
		using_act.SetCount(index+1, false);
		values.SetCount(index+1);
	}
	using_act[index] = true;
	values[index] = value;
	if (use_debugging_order)
		dbg_order.FindAdd(index);
	return true;
}*/

WorldState& WorldState::operator=(const WorldState& src) {
	values		<<= src.values;
	/*using_act	<<= src.using_act;
	dbg_order	<<= src.dbg_order;
	cur_atom	= src.cur_atom;
	type		= src.type;
	ap			= src.ap;*/
	return *this;
}


hash_t WorldState::GetHashValue() const {
	/*CombineHash c;
	c.Put((int)type);
	c.Put(cur_atom.GetHashValue());
	c.Put(side_vd.GetHashValue());
	bool begun = false;
	for(int i = values.GetCount()-1; i >= 0; i--) {
		bool b = using_act[i];
		if (begun) {
			c.Put(b);
			if (b) {
				c.Put(values[i].GetHashValue());
			}
		}
		else {
			if (b) {
				c.Put(b);
				begun = true;
				c.Put(values[i].GetHashValue());
			}
		}
	}
	return c;*/
	CombineHash c;
	for(int i = values.GetCount()-1; i >= 0; i--) {
		const Object& o = values[i];
		c.Put(o.GetHashValue());
	}
	return c;
}

#if 0

const Script::Statement* WorldState::FindStatement(const String& find_key, LinkedList<Statement>& stmts, bool dbg_print) {
	for (const Statement& stmt : stmts) {
		String key = stmt.id.ToString();
		if (key == find_key) {
			if (dbg_print) RTLOG("WorldState::FindStatement: cmp '" << key << "' == '" << find_key << "': true");
			return &stmt;
		}
		else {
			if (dbg_print) RTLOG("WorldState::FindStatement: cmp '" << key << "' == '" << find_key << "': false");
		}
	}
	return 0;
}

const Script::Statement* WorldState::FindStatement(const WorldState* ws, LinkedList<Statement>& stmts, bool dbg_print) const {
	if (!ws) {
		static thread_local Index<String> cur_ws_keys;
		cur_ws_keys.Clear();
		int i = 0;
		for(const String& s : values) {
			if (s.GetCount()) {
				String key = ap->GetAtom(i).ToString();
				cur_ws_keys.Add(key);
			}
			i++;
		}
		if (dbg_print) DUMPC(cur_ws_keys);
		
		for (const String& cur : cur_ws_keys) {
			if (dbg_print) RTLOG("WorldState::FindStatement: searching key '" << cur << "' in statements");
			const Script::Statement* s = FindStatement(cur, stmts, dbg_print);
			if (s) {
				if (dbg_print) RTLOG("WorldState::FindStatement: found statement: " << s->ToString());
				return s;
			}
		}
	}
	else {
		static thread_local Index<String> prev_ws_keys;
		prev_ws_keys.Clear();
		int i = 0;
		for(const String& s : ws->values) {
			if (s.GetCount()) {
				String key = ap->GetAtom(i).ToString();
				prev_ws_keys.Add(key);
			}
			i++;
		}
		if (dbg_print) DUMPC(prev_ws_keys);
		
		static thread_local Index<String> cur_ws_keys;
		cur_ws_keys.Clear();
		i = 0;
		for(const String& s : values) {
			if (s.GetCount()) {
				String key = ap->GetAtom(i).ToString();
				cur_ws_keys.Add(key);
			}
			i++;
		}
		if (dbg_print) DUMPC(cur_ws_keys);
		
		static thread_local Index<String> new_ws_keys;
		new_ws_keys.Clear();
		for (const String& cur : cur_ws_keys) {
			bool is_new = prev_ws_keys.Find(cur) < 0;
			if (is_new)
				new_ws_keys.Add(cur);
		}
		if (dbg_print) DUMPC(new_ws_keys);
		
		for (const String& new_ : new_ws_keys) {
			if (dbg_print) RTLOG("WorldState::FindStatement: searching key '" << new_ << "' in statements");
			const Script::Statement* s = FindStatement(new_, stmts, dbg_print);
			if (s) {
				if (dbg_print) RTLOG("WorldState::FindStatement: found statement: " << s->ToString());
				return s;
			}
		}
	}
	return 0;
}

bool WorldState::Append(const WorldState& ws, LinkedList<Statement>& ret_list) {
	for (const Script::Statement& ret : ret_list) {
		String atom = ret.id.ToString();
		if (!ret.value.IsEmpty()) {
			const Script::Value& v = *ret.value;
			if (v.type == Script::Value::VAL_STRING)
				Set(atom, v.str);
			else if (v.type == Script::Value::VAL_BOOLEAN)
				Set(atom, v.b ? "true" : "false");
			else if (v.type == Script::Value::VAL_ID)
				Set(atom, v.id.ToString());
			else
				return false;
		}
		else if (ws.IsFalse(atom))
			Set(atom, "false");
		else
			Set(atom, ws.Get(atom));
	}
	return true;
}

bool WorldState::Set(const String& key, bool value) {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return Set(idx, value);
}

bool WorldState::Set(const String& key, String value) {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return Set(idx, value);
}

bool WorldState::IsTrue(const String& key, bool def) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	if (idx < values.GetCount())
		return values[idx] == "true";
	return def;
}

bool WorldState::IsFalse(const String& key, bool def) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	if (idx < values.GetCount()) {
		const auto& s = values[idx];
		return s.IsEmpty() || s == "false";
	}
	return def;
}

bool WorldState::IsFalse(int idx) const {
	ASSERT(ap);
	ASSERT(idx >= 0);
	if (idx >= 0 && idx < values.GetCount()) {
		const auto& s = values[idx];
		return s.IsEmpty() || s == "false";
	}
	return true;
}

bool WorldState::IsUndefined(const String& key) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return IsUndefined(idx);
}

bool WorldState::IsUndefined(int idx) const {
	ASSERT(ap);
	ASSERT(idx >= 0);
	if (idx >= 0 && idx < values.GetCount()) {
		return !using_act[idx];
	}
	return true;
}

String WorldState::Get(const String& key) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return Get(idx);
}

String WorldState::Get(int idx) const {
	ASSERT(idx >= 0);
	if (idx >= 0 && idx < values.GetCount())
		return values[idx];
	return String();
}

Size WorldState::GetSize(const String& cx, const String& cy, Size def) const {
	String cx_str = Get(cx);
	String cy_str = Get(cy);
	if (cx_str.IsEmpty() || cy_str.IsEmpty())
		return def;
	return Size(StrInt(cx_str), StrInt(cy_str));
}

int WorldState::GetInt(const String& key, int def) const {
	String str = Get(key);
	if (str.IsEmpty())
		return def;
	return ScanInt(str);
}

bool WorldState::GetBool(const String& key, bool def) const {
	String str = Get(key);
	if (str.IsEmpty())
		return def;
	str = ToLower(str);
	return str == "true" || str == "1";
}

String WorldState::GetString(const String& key, String def) const {
	String str = Get(key);
	if (str.IsEmpty())
		return def;
	return str;
}

String WorldState::ToString() const {
	ASSERT(ap);
	String s;
	if (use_debugging_order && dbg_order.GetCount()) {
		for(int i = 0; i < dbg_order.GetCount(); i++) {
			int idx = dbg_order[i];
			if (!using_act[idx])
				continue;
			String v = values[idx];
			if (v.IsEmpty()) v = "false";
			String k = ap->GetAtom(idx).ToString();
			if (!s.IsEmpty())
				s << ",";
			s << k << "=" << v;
		}
	}
	else {
		for(int i = 0; i < values.GetCount(); i++) {
			if (!using_act[i])
				continue;
			String v = values[i];
			if (v.IsEmpty()) v = "false";
			String k = ap->GetAtom(i).ToString();
			if (!s.IsEmpty())
				s << ",";
			s << k << "=" << v;
		}
	}
	return s;
}

String WorldState::GetFullString() const {
	String s;
	if (IsAddAtom())
		s << "add-atom " << cur_atom.ToString() << " ";
	if (side_vd.IsValid())
		s << "side-vd=" << side_vd.ToString() << " ";
	s << ToString();
	return s;
}

bool WorldState::Contains(const WorldState& ws) const {
	if (0) {
		LOG("WorldState::Contains: this " << ToString());
		LOG("                      vs   " << ws.ToString());
	}
	int a_count = using_act.GetCount();
	int b_count = ws.using_act.GetCount();
	int c_count = min(a_count, b_count);
	for(int i = c_count; i < b_count; i++)
		if (ws.using_act[i] && !ws.IsFalse(i))
			return false;
	for(int i = 0; i < c_count; i++) {
		if (ws.using_act[i]) {
			if (Compare(i, ws) != 0)
				return false;
		}
	}
	return true;
}

bool WorldState::Conflicts(const WorldState& ws) const {
	int a_count = using_act.GetCount();
	int b_count = ws.using_act.GetCount();
	int c_count = min(a_count, b_count);
	for(int i = 0; i < c_count; i++) {
		if (using_act[i] && ws.using_act[i]) {
			if (Compare(i, ws) != 0)
				return true;
		}
	}
	return false;
}


int WorldState::Compare(int idx, const WorldState& ws) const {
	const String& a = values[idx];
	const String& b = ws.values[idx];
	// Compare false
	if (a.IsEmpty() || a == "false") {
		if (b.IsEmpty() || b == "false")
			return 0;
		return 1;
	}
	else {
		if (b.IsEmpty() || b == "false")
			return -1;
		return a == b ? 0 : -2;
	}
}

#else

/*const Script::Statement* WorldState::FindStatement(const String& find_key, LinkedList<Statement>& stmts, bool dbg_print) {
	TODO
}

const Script::Statement* WorldState::FindStatement(const WorldState* ws, LinkedList<Statement>& stmts, bool dbg_print) const {
	TODO
}

bool WorldState::Append(const WorldState& ws, LinkedList<Statement>& ret_list) {
	TODO
}*/

bool WorldState::Set(const String& key, bool value) {
	values.GetAdd(key) = value;
	return true;
}

bool WorldState::Set(const String& key, String value) {
	values.GetAdd(key) = value;
	return true;
}

bool WorldState::IsTrue(const String& key, bool def) const {
	int i = values.Find(key);
	if (i >= 0)
		return values[i].ToBool();
	return def;
}

bool WorldState::IsFalse(const String& key, bool def) const {
	int i = values.Find(key);
	if (i >= 0)
		return !values[i].ToBool();
	return def;
}

bool WorldState::IsFalse(int idx) const {
	return !values[idx].ToBool();
}

bool WorldState::IsUndefined(const String& key) const {
	TODO
}

bool WorldState::IsUndefined(int idx) const {
	TODO
}

String WorldState::Get(const String& key) const {
	const Object& o = values.Get(key);
	ASSERT(o.IsString());
	return o.ToString();
}

String WorldState::Get(int idx) const {
	const Object& o = values[idx];
	ASSERT(o.IsString());
	return o.ToString();
}

Size WorldState::GetSize(const String& cx, const String& cy, Size def) const {
	TODO
}

int WorldState::GetInt(const String& key, int def) const {
	int i = values.Find(key);
	if (i >= 0) {
		const Object& o = values[i];
		ASSERT(o.IsInt());
		return o.ToInt();
	}
	return def;
}

bool WorldState::GetBool(const String& key, bool def) const {
	int i = values.Find(key);
	if (i >= 0) {
		const Object& o = values[i];
		return o.ToBool();
	}
	return def;
}

String WorldState::GetString(const String& key, String def) const {
	int i = values.Find(key);
	if (i >= 0) {
		const Object& o = values[i];
		ASSERT(o.IsString());
		return o.ToString();
	}
	return def;
}

String WorldState::ToString() const {
	TODO
}

String WorldState::GetFullString() const {
	TODO
}

bool WorldState::Contains(const WorldState& ws) const {
	TODO
}

bool WorldState::Conflicts(const WorldState& ws) const {
	TODO
}


int WorldState::Compare(int idx, const WorldState& ws) const {
	TODO
}

void WorldState::FindKeys(String key_left, Index<String>& keys) const {
	TODO
}

#endif








/*Action::Action() : cost(1.0) {
	
}*/



}
}
NAMESPACE_TOPSIDE_END
