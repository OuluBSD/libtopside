#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


Value GetMapValue(const Value& v, const String& key) {
	if (!v.Is<ValueMap>())
		return Value();
	ValueMap map = v;
	int i = map.Find(key);
	if (i >= 0)
		return map.GetValue(i);
	return Value();
}

void SetMapValue(Value& v, const String& key, const Value& value) {
	if (!v.Is<ValueMap>())
		v = ValueMap();
	ValueMap map = v.Get<ValueMap>();
	map.Set(key, value);
	v = map;
}

void SetArrayValue(Value& v, int i, const Value& value) {
	if (!v.Is<ValueArray>())
		v = ValueArray();
	ValueArray arr = v;
	arr.Set(i, value);
	v = arr;
}

void SetArrayMapValue(Value& v, int i, const String& key, const Value& value) {
	if (!v.Is<ValueArray>())
		v = ValueArray();
	ValueArray arr = v;
	Value slot = arr.Get(i);
	if (!slot.Is<ValueMap>())
		slot = ValueMap();
	ValueMap map = slot;
	map.Set(key, value);
	arr.Set(i, map);
	v = arr;
}


END_TEXTLIB_NAMESPACE
