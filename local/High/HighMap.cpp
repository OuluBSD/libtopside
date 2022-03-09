#include "High.h"


namespace UPP {

#define LTIMING(x) // RTIMING(x)

VectorMap<HiValue, HiValue>& HiValue::CloneMap()
{
	LTIMING("CloneMap");
	ASSERT(IsMap());
	if(map->refcount != 1) {
		HiMap *c = new HiMap;
		c->map <<= map->map;
		map->Release();
		map = c;
	}
	hash = 0;
	return map->map;
}

const VectorMap<HiValue, HiValue>& HiValue::GetMap() const
{
	ASSERT(IsMap());
	return map->map;
}

void  HiValue::SetEmptyMap()
{
	Free();
	type = HIGH_MAP;
	hash = 0;
	map = new HiMap;
}

HiValue HiValue::MapGet(HiValue key) const
{
	LTIMING("MapGet");
	return GetMap().Get(key, HiValue());
}

void HiValue::MapSet(HiValue key, HiValue value)
{
	LTIMING("MapSet");
	if(IsVoid())
		SetEmptyMap();
	VectorMap<HiValue, HiValue>& m = map->map; // CloneMap();
	int q = m.Find(key);
	if(q >= 0) {
		m[q] = value;
	}
	else if (!value.IsVoid()) {
		map->count++;
		m.Add(key, value);
	}
}

HiValue& HiValue::operator[](String key) {
	ASSERT(IsVoid() || IsMap());
	if (!IsMap())
		SetEmptyMap();
	VectorMap<HiValue, HiValue>& m = map->map; // CloneMap();
	int q = m.Find(key);
	if(q >= 0)
		return m[q];
	else
		return m.Add(key);
}

HiValue& HiValue::operator[](const char* key) {
	ASSERT(IsVoid() || IsMap());
	if (!IsMap())
		SetEmptyMap();
	VectorMap<HiValue, HiValue>& m = map->map; // CloneMap();
	int q = m.Find(key);
	if(q >= 0)
		return m[q];
	else
		return m.Add(key);
}

bool HiValue::HasNumberField(const char *id) const
{
	return IsMap() && GetMap().Find(id) >= 0;
}

int  HiValue::GetFieldInt(const char *id) const
{
	return HasNumberField(id) ? MapGet(id).GetInt() : 0;
}

}
