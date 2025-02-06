#ifndef _CoreAlt_Object_h_
#define _CoreAlt_Object_h_


NAMESPACE_TOPSIDE_BEGIN


#if IS_UPP_CORE
inline WString ToWString(String s) {return s.ToWString();}
inline WString ToWString(const wchar_t* chr) {return std::wstring(chr);}
template <class T> inline String ToString(const T& o) {return AsString(o);}

template <class T> inline int64 ToInt(const T& o) {return 0;}
template<> inline int64 ToInt(const bool& o) {return (int64)o;}
template<> inline int64 ToInt(const int& o) {return (int64)o;}
//template<> inline int64 ToInt(const int32& o) {return (int64)o;}
template<> inline int64 ToInt(const int64& o) {return (int64)o;}
template<> inline int64 ToInt(const byte& o) {return (int64)o;}
template<> inline int64 ToInt(const char& o) {return (int64)o;}
template<> inline int64 ToInt(const float& o) {return (int64)o;}
template<> inline int64 ToInt(const double& o) {return (int64)o;}
template<> inline int64 ToInt(const String& o) {return StrInt(o);}
template<> inline int64 ToInt(const WString& o) {return StrInt(o.ToString());}
template<> inline int64 ToInt(const Value& o) {return (int64)o;}
template<> inline int64 ToInt(const Date& o) {return (int64)o.Get();}
template<> inline int64 ToInt(const Time& o) {return (int64)o.Get();}

template <class T> inline double ToDouble(const T& o) {return 0;}
template<> inline double ToDouble(const bool& o) {return (double)o;}
template<> inline double ToDouble(const int& o) {return (double)o;}
//template<> inline double ToDouble(const int32& o) {return (double)o;}
template<> inline double ToDouble(const int64& o) {return (double)o;}
template<> inline double ToDouble(const byte& o) {return (double)o;}
template<> inline double ToDouble(const char& o) {return (double)o;}
template<> inline double ToDouble(const float& o) {return (double)o;}
template<> inline double ToDouble(const double& o) {return (double)o;}
template<> inline double ToDouble(const String& o) {return StrDbl(o);}
template<> inline double ToDouble(const WString& o) {return StrDbl(ToString(o));}
template<> inline double ToDouble(const Date& o) {return (double)o.Get();}
template<> inline double ToDouble(const Time& o) {return (double)o.Get();}

#if __MINGW32__
template<> inline int64 ToInt(const long& o) {return (int64)o;}
template<> inline double ToDouble(const long& o) {return (double)o;}
#endif

#endif

const dword VALUE_ARRAY_AND_MAP_O   = 13;


class Object;
class Ether;
template <class T> void Etherize(Ether& e, T& o);

#if IS_UPP_CORE
Object ObjectFromValue(const Value& v);
#endif

// Manual _O value and init registering is required
template <class T>
dword ObjectTypeNo(const T *); // problematic over Ether --> { return StaticTypeNo<T>() + 0x8000000; }

#define OBJ_TYPE_NO_(x, y) template<> inline dword ObjectTypeNo<x>(const x*) { return y; }
#define OBJ_TYPE_NO(x, y) OBJ_TYPE_NO_(x,y)

#include "CoreTypes.inl"

template <class T, dword type = UNKNOWN_O, class B = EmptyClass>
class ObjectType : public B {
public:
	static dword ObjectTypeNo()                      { return type == UNKNOWN_O ? TS::ObjectTypeNo<T>(0) : type; }
	friend dword ObjectTypeNo(const T*)              { return T::ObjectTypeNo(); }
	
	bool     IsNullInstance() const                 { return false; }
	void     Serialize(Stream& s)                   { NEVER(); }
	//void     Xmlize(XmlIO& xio)                     { NEVER(); }
	//void     Jsonize(JsonIO& jio)                   { NEVER(); }
	hash_t   GetHashValue() const                   { return 0; }
	bool     operator==(const T&) const             { NEVER(); return false; }
	String   ToString() const                       { return AsTypeName<T>(); }
	int      Compare(const T&) const                { NEVER(); return 0; }
	int      PolyCompare(const Object&) const       { NEVER(); return 0; }
	
	//operator ObjectTypeRef();
};


class ObjectInstance {
protected:
	dword type = VOID_O;
	
public:
	virtual ~ObjectInstance() = default;
	virtual void* Get() {return 0;}
	virtual String ToString() const {return "VOID";}
	virtual int64 ToInt() const {return 0;}
	virtual double ToDouble() const {return 0;}
	virtual hash_t GetHashValue() const {return 0;}
	virtual void Etherize(Ether& e) {}
	//virtual void Visit(RuntimeVisitor& vis) {}
	dword GetType() const {return type;}
};

template <class T>
class ObjectTemplate : public ObjectInstance {
	bool is_owned = false;
	T* ptr = NULL;
	
public:
	ObjectTemplate() {ptr = new T(); is_owned = true; type = ObjectTypeNo<T>(0);}
	ObjectTemplate(T* ptr) : ptr(ptr) {type = ObjectTypeNo<T>(0);}
	ObjectTemplate(const T& obj) {ptr = new T(obj); is_owned = true; type = ObjectTypeNo<T>(0);}
	~ObjectTemplate() {if (is_owned && ptr) {delete ptr; ptr = 0; is_owned = false; type = VOID_O;}}
	T* GetT() const {return ptr;}
	void* Get() override {return ptr;}
	String ToString() const override {if (ptr) return ::UPP::AsString(*ptr); return "NULL";}
	int64 ToInt() const override {if (ptr) return ::TS::ToInt(*ptr); return 0;}
	double ToDouble() const override {if (ptr) return ::TS::ToDouble(*ptr); return 0;}
	hash_t GetHashValue() const override {if (ptr) return ::UPP::GetHashValue(*ptr); return 0;}
	void Etherize(Ether& e) override {if (ptr) TS::Etherize<T>(e, *ptr);}
	//void Visit(RuntimeVisitor& vis) override {if (ptr) ptr->Visit(vis);}
};

class ObjectMap;
class ObjectArray;
class Ether;

class Object : Moveable<Object>, RTTIBase {
	Shared<ObjectInstance> obj;
	
public:
	RTTI_DECL0(Object)
	
	Object() {}
	Object(const Object& v) {*this = v;}
	Object(const char* str) {String& s = Create<String>(); s = str;}
	Object(const Nuller&) {}
	template <class T> Object(const T& o) {obj.WrapObject(new ObjectTemplate<T>(o));}
	
	#if IS_UPP_CORE
	Object(const Value& v) {*this = ObjectFromValue(v);}
	#endif
	
	//void Visit(RuntimeVisitor& vis) {if (obj) obj->Visit(vis);}
	void Clear() {obj.Clear();}
	template <class T> T& Create() {ObjectTemplate<T>* o = new ObjectTemplate<T>(); T* t = (T*)o->Get(); obj.WrapObject(o); return *t;}
	template <class T> T& Create(const T& arg) {ObjectTemplate<T>* o = new ObjectTemplate<T>(arg); T* t = (T*)o->Get(); obj.WrapObject(o); return *t;}
	void DeepCopyArrayMap(Object v);
	ObjectMap&   CreateMap();
	ObjectArray& CreateArray();
	
	dword GetType() const {if (obj) return obj->GetType(); return VOID_O;}
	Object& operator=(const Nuller&) {Clear(); return *this;}
	template <class T> Object&	operator=(const Object& v) {obj = v.obj; return *this;}
	template <class T> Object&	operator=(T* o) {Set<T>(o); return *this;}
	template <class T> Object&	operator=(const T& o) {Set<T>(o); return *this;}
	
	template <class T> T&       Set(T* o) {ObjectTemplate<T>* p = new ObjectTemplate<T>(o); obj = p; return *p->GetT();}
	template <class T> T&       Set(const T& o) {if (Is<T>()) {T& p = Get<T>(); p = o; return p;} else return Create<T>(o);}
	template <class T> bool		Is() const {if (obj) return obj->GetType() == ObjectTypeNo<T>(0); return false;}
	template <class T> T*		Try() const;
	
	template <class T> operator const T&() const;
	template <class T> operator T&() const;
	template <class T> T& Get() const;
	const ObjectMap* TryGetMap() const;
	const ObjectArray* TryGetArray() const;
	ObjectMap* TryGetMap();
	ObjectArray* TryGetArray();
	const ObjectMap& GetMap() const;
	const ObjectArray& GetArray() const;
	ObjectMap& GetMap();
	ObjectArray& GetArray();
	Object* GetMapSub(String key, Object* def=NULL);
	Object* AddMapSub(String key, Object* def=NULL);
	Object* GetAddMapSub(String key, Object* def=NULL);
	ObjectInstance* GetObject() const {return obj.Get();}
	hash_t GetHashValue() const {if (obj) return obj->GetHashValue(); return 0;}
	
	bool IsVoid() const {if (obj) return obj->GetType() == VOID_O; return true;}
	bool IsNullInstance() const {return IsVoid();}
	bool IsArray() const;
	bool IsMap() const;
	bool IsArrayMapComb() const;
	bool IsString() const {return !obj.IsEmpty() && obj->GetType() == STRING_O;}
	bool IsWString() const {return !obj.IsEmpty() && obj->GetType() == WSTRING_O;}
	bool IsInt() const {return !obj.IsEmpty() && obj->GetType() == INT32_O;}
	bool IsInt64() const {return !obj.IsEmpty() && obj->GetType() == INT64_O;}
	bool IsDouble() const {return !obj.IsEmpty() && obj->GetType() == DOUBLE_O;}
	bool IsNumber() const {return !obj.IsEmpty() && (obj->GetType() == DOUBLE_O || obj->GetType() == INT32_O || obj->GetType() == INT64_O);}
	
	void Etherize(Ether& e);
	operator String() const {return ToString();}
	
	String ToString() const {if (obj) return obj->ToString(); return "NULL";}
	WString ToWString() const {WString* w=Try<WString>(); if (w) return *w; return ::TS::ToWString(ToString());}
	int64 ToInt() const {if (obj) return obj->ToInt(); return 0;}
	int ToInt32() const {if (obj) return (int)obj->ToInt(); return 0;}
	double ToDouble() const {if (obj) return obj->ToDouble(); return 0;}
	float ToFloat() const {if (obj) return (float)obj->ToDouble(); return 0;}
	bool ToBool() const;
	
	Object operator >(const Object& o) const;
	Object operator <(const Object& o) const;
	Object operator >=(const Object& o) const;
	Object operator <=(const Object& o) const;
	Object operator !=(const Object& o) const;
	Object operator ==(const Object& o) const;
	Object operator &&(const Object& o) const;
	Object operator ||(const Object& o) const;
	Object operator +(const Object& o) const;
	Object operator -(const Object& o) const;
	Object operator *(const Object& o) const;
	Object operator /(const Object& o) const;
	Object operator %(const Object& o) const;
	Object operator <<(const Object& o) const;
	Object operator >>(const Object& o) const;
	Object operator !() const;
	Object operator -() const;
	
	
private:
	
	template <class T> static void CreateFn(Object& o) {o.Create<T>();}
	
	struct RegType : Moveable<RegType> {
		typedef void(*CreateObj)(Object&);
		dword type;
		const char* name;
		CreateObj create;
	};
	
	static VectorMap<dword, RegType>& Types() {static VectorMap<dword, RegType> v; return v;}
	
public:
	template <class T>
	static void RegisterType(dword type, const char* name) {
		ASSERT_(Types().Find(type) < 0, "Type was registered twice");
		RegType& t = Types().GetAdd(type);
		t.type = type;
		t.name = name;
		t.create = &CreateFn<T>;
	}
	
	bool CreateType(dword type) {
		Clear();
		if (type == VOID_O)
			return true;
		int i = Types().Find(type);
		if (i < 0)
			return false;
		const RegType& t = Types()[i];
		t.create(*this);
		return true;
	}
};

inline bool IsObjectMap(const Object& v) {return v.IsMap();}

template <class T> T* Object::Try() const {
	if (obj && obj->GetType() == ObjectTypeNo<T>(0))
		return (T*)obj->Get();
	return NULL;
}

template <class T> Object::operator const T&() const {
	if (obj && obj->GetType() == ObjectTypeNo<T>(0))
		return *(const T*)obj->Get();
	THROW(Exc("Unexpected value type"));
}

template <class T> Object::operator T&() const {
	if (obj && obj->GetType() == ObjectTypeNo<T>(0))
		return *(T*)obj->Get();
	THROW(Exc("Unexpected value type"));
}

template <class T> T& Object::Get() const {
	if (obj && obj->GetType() == ObjectTypeNo<T>(0))
		return *(T*)obj->Get();
	THROW(Exc("Unexpected value type"));
}

class ObjectArray {
	typedef Array<Object> A;
	A values;
	
public:
	
	ObjectArray() {}
	ObjectArray(const ObjectArray& m) {*this = m;}
	void operator=(const ObjectArray& m) {values <<= m.values;}
	
	void Clear() {values.Clear();}
	Object& Add() {return values.Add();}
	Object& Add(const Object& v) {return values.Add(v);}
	Object& Insert(int i) {return values.Insert(i);}
	Object& Insert(int i, const Object& v) {return values.Insert(i, v);}
	int GetCount() const {return values.GetCount();}
	Object& operator[](int i) {return values[i];}
	Object& Get(int i) {return values[i];}
	const Object& operator[](int i) const {return values[i];}
	const Object& Get(int i) const {return values[i];}
	bool IsEmpty() const {return values.IsEmpty();}
	void SetCount(int i) {values.SetCount(i);}
	void DeepCopyArrayMap(ObjectArray& arr);
	hash_t GetHashValue() const;
	
	String ToString() const {String s; s << "ObjectArray(" << values.GetCount() << ")"; return s;}
	int64 ToInt() const {return values.GetCount();}
	double ToDouble() const {return values.GetCount();}
	operator double() const {return values.GetCount();}
	
	A::Iterator begin() {return values.begin();}
	A::Iterator end() {return values.end();}
	A::ConstIterator begin() const {return values.begin();}
	A::ConstIterator end() const {return values.end();}
	
	void Etherize(Ether& e);
	
};


class ObjectMap {
	Vector<String>	keys;
	Array<Object>	values;
	
public:
	ObjectMap() {}
	ObjectMap(const ObjectMap& m) {*this = m;}
	
	void			operator=(const ObjectMap& m) {keys <<= m.keys; values <<= m.values;}
	
	Object&			Add(String key, Object v) {keys.Add(key); return values.Add(v);}
	Object&			Add(String key) {keys.Add(key); return values.Add();}
	Object&			GetAdd(String key) {int i = Find(key); if (i >= 0) return values[i]; return Add(key);}
	Object&			GetAdd(String key, const Object& def) {int i = Find(key); if (i >= 0) return values[i]; return Add(key, def);}
	Object			TryGet(String key, Object def=Object()) {int i = Find(key); if (i >= 0) return GetObject(i); else return def;}
	Object*			TryFind(String key) {int i = Find(key); if (i >= 0) return &GetObject(i); return NULL;}
	int				Find(String key) const {for(int i = 0; i < keys.GetCount(); i++) if (keys[i] == key) return i; return -1;}
	Object&			Get(String key) {int i = Find(key); if (i == -1) THROW(Exc("Unexpected key")); return values[i];}
	const Object&	Get(String key) const {int i = Find(key); if (i == -1) THROW(Exc("Unexpected key")); return values[i];}
	int				GetIterPos(Object* v) const {for(int i = 0; i < values.GetCount(); i++) if (&values[i] == v) return i; return -1;}
	void			SetAt(int i, const Object& v) {values[i] = v;}
	void			SetKey(int i, const String& key) {keys[i] = key;}
	void			Remove(int i) {keys.Remove(i); values.Remove(i);}
	
	void			Clear() {keys.Clear(); values.Clear();}
	int				GetCount() const {return values.GetCount();}
	bool			IsEmpty() const {return values.IsEmpty();}
	Object&			operator[](int i) {return values[i];}
	Object&			GetObject(int i) {return values[i];}
	String			GetKey(int i) const {return keys[i];}
	void			DeepCopyArrayMap(ObjectMap& map);
	hash_t			GetHashValue() const;
	
	const Object&	operator[](int i) const {return values[i];}
	const Object&	GetObject(int i) const {return values[i];}
	
	String			ToString() const {String s; s << "ObjectMap(" << keys.GetCount() << ")"; return s;}
	int64			ToInt() const {return keys.GetCount();}
	double			ToDouble() const {return keys.GetCount();}
	operator double() const {return keys.GetCount();}
	
	void Etherize(Ether& e);
	
};

struct ObjectArrayMapComb {
	ObjectArray arr;
	ObjectMap   map;
	
	
	ObjectArrayMapComb() {}
	ObjectArrayMapComb(const ObjectArrayMapComb& v) {*this = v;}
	void operator=(const ObjectArrayMapComb& v) {arr = v.arr; map = v.map;}
	void DeepCopyArrayMap(ObjectArrayMapComb& am);
	
	void Clear() {arr.Clear(); map.Clear();}
	int GetTotal() const {return arr.GetCount() + map.GetCount();}
	String ToString() const {String s; s << "ObjectArrayMapComb(" << arr.GetCount() << ", " << map.GetCount() << ")"; return s;}
	int64 ToInt() const {return GetTotal();}
	double ToDouble() const {return GetTotal();}
	operator double() const {return GetTotal();}
	hash_t GetHashValue() const;
};


template<> inline dword ObjectTypeNo(const ObjectArray*)          { return OBJECTARRAY_O; }
template<> inline dword ObjectTypeNo(const ObjectMap*)            { return OBJECTMAP_O; }
template<> inline dword ObjectTypeNo(const ObjectArrayMapComb*)   { return OBJECT_ARRAY_AND_MAP_O; }

String GetObjectTreeString(const Object& v, String key="", int indent=0);


NAMESPACE_TOPSIDE_END


#endif
