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

void WorldState::FindKeys(String key_left, Index<String>& keys) const {
	for(int i = 0; i < values.GetCount(); i++) {
		if (!values[i])
			continue;
		String key = values.GetKey(i);
		if (key.Left(key_left.GetCount()) == key_left)
			keys.FindAdd(key);
	}
}


WorldState& WorldState::operator=(const WorldState& src) {
	values		<<= src.values;
	return *this;
}


hash_t WorldState::GetHashValue() const {
	CombineHash c;
	for(int i = values.GetCount()-1; i >= 0; i--) {
		const Object& o = values[i];
		c.Put(o.GetHashValue());
	}
	return c;
}

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

String WorldState::Get(const String& key, String def) const {
	int i = values.Find(key);
	if (i < 0)
		return def;
	const Object& o = values[i];
	return o.ToString();
}

String WorldState::Get(int idx) const {
	const Object& o = values[idx];
	ASSERT(o.IsString());
	return o.ToString();
}

Size WorldState::GetSize(const String& cx, const String& cy, Size def) const {
	String cx_str = Get(cx);
	String cy_str = Get(cy);
	if (cx_str.IsEmpty() || cy_str.IsEmpty())
		return def;
	return Size(StrInt(cx_str), StrInt(cy_str));
}

int WorldState::GetInt(const String& key, int def) const {
	int i = values.Find(key);
	if (i >= 0) {
		const Object& o = values[i];
		return o.ToInt32();
	}
	return def;
}

double WorldState::GetDouble(const String& key, double def) const {
	int i = values.Find(key);
	if (i >= 0) {
		const Object& o = values[i];
		return o.ToDouble();
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
	String s;
	for(int i = 0; i < values.GetCount(); i++) {
		const Object& vo = values[i];
		String v = vo.ToString();
		if (v.IsEmpty()) v = "false";
		String k = values.GetKey(i).ToString();
		if (!s.IsEmpty())
			s << ",";
		s << k << "=" << v;
	}
	return s;
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



}
}
NAMESPACE_TOPSIDE_END
