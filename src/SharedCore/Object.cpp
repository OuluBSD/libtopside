#include <Local/Local.h>


NAMESPACE_UPP



ObjectMap& Object::CreateMap() {
	Create<ObjectMap>();
	return GetMap();
}

ObjectArray& Object::CreateArray() {
	Create<ObjectArray>();
	return GetArray();
}

bool Object::IsArray() const {
	return Is<ObjectArray>();
}

bool Object::IsMap() const {
	return Is<ObjectMap>();
}

bool Object::IsArrayMapComb() const {
	return Is<ObjectArrayMapComb>();
}

const ObjectArray* Object::TryGetArray() const {
	if (IsArray())
		return &Get<ObjectArray>();
	else if (IsArrayMapComb())
		return &Get<ObjectArrayMapComb>().arr;
	else
		return NULL;
}

const ObjectMap* Object::TryGetMap() const {
	if (IsMap())
		return &Get<ObjectMap>();
	else if (IsArrayMapComb())
		return &Get<ObjectArrayMapComb>().map;
	else
		return NULL;
}

ObjectArray* Object::TryGetArray() {
	if (IsArray())
		return &Get<ObjectArray>();
	else if (IsArrayMapComb())
		return &Get<ObjectArrayMapComb>().arr;
	else
		return NULL;
}

ObjectMap* Object::TryGetMap() {
	if (IsMap())
		return &Get<ObjectMap>();
	else if (IsArrayMapComb())
		return &Get<ObjectArrayMapComb>().map;
	else
		return NULL;
}

const ObjectMap& Object::GetMap() const {
	if (!Is<ObjectMap>())
		THROW(Exc("Not a ObjectMap"));
	return Get<ObjectMap>();
}

const ObjectArray& Object::GetArray() const {
	if (!Is<ObjectArray>())
		THROW(Exc("Not a ObjectArray"));
	return Get<ObjectArray>();
}

ObjectMap& Object::GetMap() {
	if (!Is<ObjectMap>())
		THROW(Exc("Not a ObjectMap"));
	return Get<ObjectMap>();
}

ObjectArray& Object::GetArray() {
	if (!Is<ObjectArray>())
		THROW(Exc("Not a ObjectArray"));
	return Get<ObjectArray>();
}

Object* Object::GetMapSub(String key, Object* def) {
	if (IsMap() || IsArrayMapComb()) {
		ObjectMap& map = IsMap() ? Get<ObjectMap>() : Get<ObjectArrayMapComb>().map;
		int i = map.Find(key);
		if (i >= 0)
			return &map.GetObject(i);
		else
			return NULL;
	}
	else return NULL;
}

Object* Object::AddMapSub(String key, Object* def) {
	if (IsMap() || IsArrayMapComb()) {
		ObjectMap& map = IsMap() ? Get<ObjectMap>() : Get<ObjectArrayMapComb>().map;
		int i = map.Find(key);
		if (i >= 0)
			return NULL;
		else if (def)
			return &map.Add(key, *def);
		else
			return &map.Add(key);
	}
	else return NULL;
}

Object* Object::GetAddMapSub(String key, Object* def) {
	if (IsMap() || IsArrayMapComb()) {
		ObjectMap& map = IsMap() ? Get<ObjectMap>() : Get<ObjectArrayMapComb>().map;
		int i = map.Find(key);
		if (i >= 0)
			return &map.GetObject(i);
		else if (def)
			return &map.Add(key, *def);
		else
			return &map.Add(key);
	}
	else return NULL;
}

void Object::DeepCopyArrayMap(Object v) {
	if (v.IsArray())
		CreateArray().DeepCopyArrayMap(v.GetArray());
	else if (v.IsMap())
		CreateMap().DeepCopyArrayMap(v.GetMap());
	else *this = v;
}

bool Object::ToBool() const {
	bool b = false;
	dword type = GetType();
	if (type == BOOL_V)
		b = Get<bool>();
	else if (type == INT_V || type == INT64_V)
		b = ToInt();
	else if (type == DOUBLE_V)
		b = ToDouble();
	return b;
}

Object Object::operator >(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() > o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() > o.ToDouble();
	if (IsString() && o.IsString()) return ToString() > o.ToString();
	if (IsWString() && o.IsWString()) return ToWString() > o.ToWString();
	return Object(false);
}

Object Object::operator <(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() < o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() < o.ToDouble();
	if (IsString() && o.IsString()) return ToString() < o.ToString();
	if (IsWString() && o.IsWString()) return ToWString() < o.ToWString();
	return Object(false);
}

Object Object::operator >=(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() >= o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() >= o.ToDouble();
	if (IsString() && o.IsString()) return ToString() >= o.ToString();
	if (IsWString() && o.IsWString()) return ToWString() >= o.ToWString();
	return Object(false);
}

Object Object::operator <=(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() <= o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() <= o.ToDouble();
	if (IsString() && o.IsString()) return ToString() <= o.ToString();
	if (IsWString() && o.IsWString()) return ToWString() <= o.ToWString();
	return Object(false);
}

Object Object::operator !=(const Object& o) const {
	if (IsVoid() && o.IsVoid()) return false;
	if (IsVoid() || o.IsVoid()) return Object(true);
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() != o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() != o.ToDouble();
	if (IsString() && o.IsString()) return ToString() != o.ToString();
	if (IsWString() && o.IsWString()) return ToWString() != o.ToWString();
	if (!obj || !o.obj) return Object(true);
	return obj != o.obj;
}

Object Object::operator ==(const Object& o) const {
	if (IsVoid() && o.IsVoid()) return true;
	if (IsVoid() || o.IsVoid()) return Object(false);
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() == o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() == o.ToDouble();
	if (IsString() && o.IsString()) return ToString() == o.ToString();
	if (IsWString() && o.IsWString()) return ToWString() == o.ToWString();
	if (!obj || !o.obj) return Object(false);
	return obj == o.obj;
}

Object Object::operator &&(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() && o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() && o.ToDouble();
	if (IsString() && o.IsString()) return !ToString().IsEmpty() && !o.ToString().IsEmpty();
	if (IsWString() && o.IsWString()) return !ToWString().IsEmpty() && !o.ToWString().IsEmpty();
	return Object(false);
}

Object Object::operator ||(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() || o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() || o.ToDouble();
	if (IsString() && o.IsString()) return !ToString().IsEmpty() || !o.ToString().IsEmpty();
	if (IsWString() && o.IsWString()) return !ToWString().IsEmpty() || !o.ToWString().IsEmpty();
	return Object(false);
}

Object Object::operator +(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() + o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() + o.ToDouble();
	if (IsString() && o.IsString()) return ToString() + o.ToString();
	if (IsWString() && o.IsWString()) return ToWString() + o.ToWString();
	return Object(false);
}

Object Object::operator -(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() - o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() - o.ToDouble();
	return Object(false);
}

Object Object::operator *(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() * o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() * o.ToDouble();
	return Object(false);
}

Object Object::operator /(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() / o.ToInt();
	if (IsNumber() && o.IsNumber()) return ToDouble() / o.ToDouble();
	return Object(false);
}

Object Object::operator %(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() % o.ToInt();
	if (IsNumber() && o.IsNumber()) return fmod(ToDouble(), o.ToDouble());
	return Object(false);
}

Object Object::operator <<(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() << o.ToInt();
	if (IsNumber() && o.IsNumber()) return (int64)ToDouble() << (int64)o.ToDouble();
	return Object(false);
}

Object Object::operator >>(const Object& o) const {
	if ((IsInt() || IsInt64()) && (o.IsInt() || o.IsInt64())) return ToInt() >> o.ToInt();
	if (IsNumber() && o.IsNumber()) return (int64)ToDouble() >> (int64)o.ToDouble();
	return Object(false);
}

Object Object::operator !() const {
	if (IsInt() || IsInt64()) return !ToInt();
	if (IsNumber()) return !ToDouble();
	if (IsString()) return ToString().IsEmpty();
	if (IsWString()) return ToWString().IsEmpty();
	return Object(false);
}

Object Object::operator -() const {
	if (IsInt() || IsInt64()) return -ToInt();
	if (IsNumber()) return -ToDouble();
	return Object(false);
}




void ObjectArray::DeepCopyArrayMap(ObjectArray& arr) {
	Clear();
	SetCount(arr.GetCount());
	for(int i = 0; i < GetCount(); i++) {
		Object& from = arr.Get(i);
		Object& dst = Get(i);
		dst.DeepCopyArrayMap(from);
	}
}

hash_t ObjectArray::GetHashValue() const {
	CombineHash h;
	for(const auto& v : values)
		h.Put(v.GetHashValue());
	return h;
}





void ObjectMap::DeepCopyArrayMap(ObjectMap& map) {
	Clear();
	for(int i = 0; i < map.GetCount(); i++) {
		String key = map.GetKey(i);
		Object& from = map.GetObject(i);
		Object& dst = Add(key);
		dst.DeepCopyArrayMap(from);
	}
}

hash_t ObjectMap::GetHashValue() const {
	CombineHash h;
	for(const auto& v : keys)
		h.Put(v.GetHashValue());
	for(const auto& v : values)
		h.Put(v.GetHashValue());
	return h;
}




void ObjectArrayMapComb::DeepCopyArrayMap(ObjectArrayMapComb& am) {
	Clear();
	arr.SetCount(am.arr.GetCount());
	for(int i = 0; i < arr.GetCount(); i++) {
		Object& from = am.arr.Get(i);
		Object& dst = arr.Get(i);
		dst.DeepCopyArrayMap(from);
	}
	for(int i = 0; i < am.map.GetCount(); i++) {
		String key = am.map.GetKey(i);
		Object& from = am.map.GetObject(i);
		Object& dst = map.Add(key);
		dst.DeepCopyArrayMap(from);
	}
}

hash_t ObjectArrayMapComb::GetHashValue() const {
	CombineHash h;
	h.Put(arr.GetHashValue());
	h.Put(map.GetHashValue());
	return h;
}




String GetObjectTreeString(const Object& v, String key, int indent) {
	MAKE_STATIC_LOCAL(Index<void*>, visited);
	if (!indent)
		visited.Clear();
	
	String s;
	for(int i = 0; i < indent; i++)
		s.Cat('\t');
	if (key.IsEmpty())
		key = "<empty>";
	s << key;
	
	void* obj = v.GetObject();
	if (obj) {
		if (visited.Find(obj) >= 0)
			return s + ": <recursive>\n";
		visited.Add(obj);
	}
	
	if (v.IsMap()) {
		s.Cat('\n');
		const ObjectMap& map = v.Get<ObjectMap>();
		for(int i = 0; i < map.GetCount(); i++) {
			String key = map.GetKey(i);
			const Object& v0 = map[i];
			s << GetObjectTreeString(v0, key, indent+1);
		}
	}
	else if (v.IsArray()) {
		s.Cat('\n');
		const ObjectArray& arr = v.Get<ObjectArray>();
		for(int i = 0; i < arr.GetCount(); i++) {
			String key = IntStr(i);
			const Object& v0 = arr[i];
			s << GetObjectTreeString(v0, key, indent+1);
		}
	}
	else if (v.IsArrayMapComb()) {
		s.Cat('\n');
		const ObjectArrayMapComb& comb = v.Get<ObjectArrayMapComb>();
		for(int i = 0; i < comb.map.GetCount(); i++) {
			String key = comb.map.GetKey(i);
			const Object& v0 = comb.map[i];
			s << GetObjectTreeString(v0, key, indent+1);
		}
		for(int i = 0; i < comb.arr.GetCount(); i++) {
			String key = IntStr(i);
			const Object& v0 = comb.arr[i];
			s << GetObjectTreeString(v0, key, indent+1);
		}
	}
	else {
		s << ": " << v.ToString() << "\n";
	}
	
	if (obj)
		RemoveLast(visited);
	
	return s;
}









#if IS_UPP_CORE
Object ObjectFromValue(const Value& v) {
	#define SIMPLE(x) else if (type == GetValueTypeNo<x>()) return v.Get<x>();
	dword type = v.GetType();
	if (type == VALUEMAP_V) {
		Object o;
		ObjectMap& om = o.CreateMap();
		const ValueMap& m = v;
		for(int i = 0; i < m.GetCount(); i++)
			om.Add(m.GetKey(i), ObjectFromValue(m.GetValue(i)));
		return o;
	}
	else if (type == VALUEARRAY_V) {
		Object o;
		ObjectArray& oa = o.CreateArray();
		const ValueArray& a = v;
		for(int i = 0; i < a.GetCount(); i++)
			oa.Add(ObjectFromValue(a[i]));
		return o;
	}
	SIMPLE(Time)
	SIMPLE(Date)
	SIMPLE(WString)
	SIMPLE(String)
	SIMPLE(double)
	SIMPLE(int64)
	SIMPLE(int)
	SIMPLE(bool)
	
	return Object();
}

#endif




#ifdef LIBTOPSIDE
template<> StringT<char>& StringT<char>::operator=(const Object& c) {return *this = c.ToString();}
template<> StringT<wchar_t>& StringT<wchar_t>::operator=(const Object& c) {return *this = c.ToString().ToWString();}
#endif

END_UPP_NAMESPACE

