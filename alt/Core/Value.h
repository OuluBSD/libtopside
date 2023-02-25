#ifndef _CoreAlt_Value_h_
#define _CoreAlt_Value_h_


NAMESPACE_UPP_BEGIN


int RegisterTypeNo__(const char *type);

template <class T>
int StaticTypeNo() {
	static int typeno = RegisterTypeNo__(AsTypeName<T>());
	return typeno;
}


const dword VOID_V    = 0;

const dword INT_V     = 1;
const dword DOUBLE_V  = 2;
const dword STRING_V  = 3;
const dword DATE_V    = 4;
const dword TIME_V    = 5;

const dword ERROR_V   = 6;

const dword VALUE_V   = 7;

const dword WSTRING_V = 8;

const dword VALUEARRAY_V = 9;

const dword INT64_V  = 10;
const dword BOOL_V   = 11;

const dword VALUEMAP_V   = 12;

const dword COLOR_V   = 13;


const dword UNKNOWN_V = (dword)0xffffffff;


inline int RegisterTypeNo__(const char *type) {
	MAKE_STATIC(Index<String>, idx);
	int i = idx.FindAdd(type);
	ASSERT(i <= 255);
	return i;
}


class Value;
class ValueMap;
class ValueArray;


template <class T>
inline dword ValueTypeNo(const T *)                 { return StaticTypeNo<T>() + 0x8000000; }

template<> inline dword ValueTypeNo(const void*)    { return VOID_V; }
template<> inline dword ValueTypeNo(const int*)     { return INT_V; }
template<> inline dword ValueTypeNo(const int64*)   { return INT64_V; }
template<> inline dword ValueTypeNo(const double*)  { return DOUBLE_V; }
template<> inline dword ValueTypeNo(const bool*)    { return BOOL_V; }
template<> inline dword ValueTypeNo<String>(const String*)  { return STRING_V; }
template<> inline dword ValueTypeNo(const WString*) { return WSTRING_V; }
template<> inline dword ValueTypeNo(const Date*)    { return DATE_V; }
template<> inline dword ValueTypeNo(const Time*)    { return TIME_V; }
template<> inline dword ValueTypeNo(const Value*)   { return VALUE_V; }


template <class T, dword type = UNKNOWN_V, class B = EmptyClass>
class ValueType : public B {
public:
	static dword ValueTypeNo()                      { return type == UNKNOWN_V ? StaticTypeNo<T>() + 0x8000000 : type; }
	friend dword ValueTypeNo(const T*)              { return T::ValueTypeNo(); }
	
	bool     IsNullInstance() const                 { return false; }
	void     Serialize(Stream& s)                   { NEVER(); }
	//void     Xmlize(XmlIO& xio)                     { NEVER(); }
	//void     Jsonize(JsonIO& jio)                   { NEVER(); }
	hash_t   GetHashValue() const                   { return 0; }
	bool     operator==(const T&) const             { NEVER(); return false; }
	String   ToString() const                       { return AsTypeName<T>(); }
	int      Compare(const T&) const                { NEVER(); return 0; }
	int      PolyCompare(const Value&) const       { NEVER(); return 0; }
	
	//operator ValueTypeRef();
};


class ValueInstance {
protected:
	dword type = VOID_V;
	
public:
	virtual ~ValueInstance() = default;
	virtual void* Get() {return 0;}
	virtual String ToString() const {return "VOID";}
	virtual int64 ToInt() const {return 0;}
	virtual double ToDouble() const {return 0;}
	virtual hash_t GetHashValue() const {return 0;}
	//virtual void Visit(RuntimeVisitor& vis) {}
	dword GetType() const {return type;}
};

template <class T>
class ValueTemplate : public ValueInstance {
	bool is_owned = false;
	T* ptr = NULL;
	
public:
	ValueTemplate() {ptr = new T(); is_owned = true; type = ValueTypeNo<T>(0);}
	ValueTemplate(T* ptr) : ptr(ptr) {type = ValueTypeNo<T>(0);}
	ValueTemplate(const T& obj) {ptr = new T(obj); is_owned = true; type = ValueTypeNo<T>(0);}
	~ValueTemplate() {if (is_owned && ptr) {delete ptr; ptr = 0; is_owned = false; type = VOID_V;}}
	void* Get() override {return ptr;}
	String ToString() const override {if (ptr) return ::UPP::AsString(*ptr); return "NULL";}
	int64 ToInt() const override {if (ptr) return ::UPP::ToInt(*ptr); return 0;}
	double ToDouble() const override {if (ptr) return ::UPP::ToDouble(*ptr); return 0;}
	hash_t GetHashValue() const override {if (ptr) return ::UPP::GetHashValue(*ptr); return 0;}
	//void Visit(RuntimeVisitor& vis) override {if (ptr) ptr->Visit(vis);}
};



class Value : RTTIBase {
	RTTI_DECL0(Value)
	
public:
	
	class Void {
	protected:
		Atomic  refcount;

	public:
		void               Retain()                    { AtomicInc(refcount); }
		void               Release()                   { if(AtomicDec(refcount) == 0) delete this; }
		int                GetRefCount() const         { return refcount; }

		virtual bool       IsNull() const              { return true; }
		virtual void       Serialize(Stream& s)        {}
		virtual void       Xmlize(XmlIO& xio)          {}
		virtual void       Jsonize(JsonIO& jio)        {}
		virtual hash_t     GetHashValue() const        { return 0; }
		virtual bool       IsEqual(const Void *p)      { return false; }
		virtual bool       IsPolyEqual(const Value& v) { return false; }
		virtual String     AsString() const            { return ""; }
		virtual int        Compare(const Void *p)      { return 0; }
		virtual int        PolyCompare(const Value& p) { return 0; }

		Void()                                         { refcount = 1; }
		virtual ~Void()                                {}

		friend class Value;
	};

	struct Sval {
		bool       (*IsNull)(const void *p);
		void       (*Serialize)(void *p, Stream& s);
		void       (*Xmlize)(void *p, XmlIO& xio);
		void       (*Jsonize)(void *p, JsonIO& jio);
		hash_t     (*GetHashValue)(const void *p);
		bool       (*IsEqual)(const void *p1, const void *p2);
		bool       (*IsPolyEqual)(const void *p, const Value& v);
		String     (*AsString)(const void *p);
		int        (*Compare)(const void *p1, const void *p2);
		int        (*PolyCompare)(const void *p1, const Value& p2);
	};
	
private:
	String   data;
	
	
protected:
	enum { STRING = 0, REF = 255, VOIDV = 3 };
	
	
	void ClearSetDataType(byte type);
	template <class T> void Push(byte special, const T& o) {
		memcpy(data.GetWritableData(special, sizeof(o)), &o, sizeof(o));
	}
	template <class T> T Pop() const {
		T o;
		if (data.GetCount() >= sizeof(o))
			memcpy(&o, data.Begin(), sizeof(o));
		return o;
	}
public:
	Value();
	/*Value(bool b);
	Value(int i);
	Value(int64 i);
	Value(double d);
	Value(String s);
	Value(WString s);
	Value(Date d);
	Value(Time d);
	Value(Nuller);
	Value(const ValueArray& a);
	Value(const ValueMap& m);*/
	//Value(Color m);
	Value(const Value& v) {*this = v;}
	template <class T> Value(const T& o);
	Value& operator=(const Value& v);
	
	enum VSMALL { SMALL };
	
	template <class T>
	Value(const T& value, VSMALL) {TODO}
	
	hash_t GetHashValue() const;
	
	dword    GetType() const;
	bool     IsError() const         { return GetType() == ERROR_V; }
	bool     IsVoid() const          { return Is(VOIDV) || IsError(); }
	bool     IsNull() const;
	bool     IsNullInstance() const;

	template <class T>	bool     Is() const;
	template <class T>	const T& To() const;
	template <class T>	const T& Get() const;

	bool     IsString() const          { return !data.IsSpecial(); }
	bool     Is(byte d) const          { return GetType() == d; }
	bool     IsRef() const             { return Is(REF); }
	
	template <class T>	void     InitSmall(const T& init);
	template <class T>	T&       GetSmallRaw() const {TODO_}
	template <class T>	T&       GetSmall() const;
	
	int      GetOtherInt() const;
	int64    GetOtherInt64() const;
	double   GetOtherDouble() const;
	bool     GetOtherBool() const;
	Date     GetOtherDate() const;
	Time     GetOtherTime() const;
	String   GetOtherString() const;
	hash_t   GetOtherHashValue() const;
	
	/*operator String() const          { return IsString() ? data : GetOtherString(); }
	operator WString() const;
	operator Date() const            { return Is(DATE_V) ? GetSmallRaw<Date>() : GetOtherDate(); }
	operator Time() const            { return Is(TIME_V) ? GetSmallRaw<Time>() : GetOtherTime(); }
	operator double() const          { return Is(DOUBLE_V) ? GetSmallRaw<double>() : GetOtherDouble(); }
	operator int() const             { return Is(INT_V) ? GetSmallRaw<int>() : GetOtherInt(); }
	operator int64() const           { return Is(INT64_V) ? GetSmallRaw<int64>() : GetOtherInt64(); }
	operator bool() const            { return Is(BOOL_V) ? GetSmallRaw<bool>() : GetOtherBool(); }
	*/
	template <class T> operator T() const;
	
	String operator~() const {TODO}
	
};


template <class T> Value::Value(const T& o) {TODO_}
template <class T> Value::operator T() const {TODO_}

template <class T>
Value RawToValue(const T& o) {TODO_}

template <class T>
bool IsTypeRaw(const Value& v) {TODO_}




Value        ErrorValue(const char *s);
Value        ErrorValue(const String& s);
const Value& ErrorValue();



class Id : Moveable<Id> {
	String id;

public:
	const String&  ToString() const              { return id; }
	hash_t         GetHashValue() const          { return ::UPP::GetHashValue(id); }
	bool           IsNull() const                { return ::UPP::IsNull(id); }

	operator const String&() const               { return ToString(); }
	const String&  operator~() const             { return ToString(); }
	bool           operator==(const Id& b) const { return id == b.id; }
	bool           operator!=(const Id& b) const { return id != b.id; }

	operator bool() const                        { return id.GetCount(); }

	Id()                                         {}
	Id(const String& s)                          { id = s; }
	Id(const char *s)                            { id = s; }
};


class ValueArray : public ValueType<ValueArray, VALUEARRAY_V, Moveable<ValueArray> > {
	struct Data : Value::Void {
		virtual bool         IsNull() const;
		virtual void         Serialize(Stream& s);
		virtual void         Xmlize(XmlIO& xio);
		virtual void         Jsonize(JsonIO& jio);
		virtual hash_t       GetHashValue() const;
		virtual bool         IsEqual(const Value::Void *p);
		virtual String       AsString() const;
		virtual int          Compare(const Value::Void *p);

		int GetRefCount() const;//     { return refcount; }
		Vector<Value>& Clone();

		Vector<Value> data;
	};
	struct NullData : Data {};
	Data *data;
	
	static Vector<Value> VoidData;
	
public:
	
	void Clear();
	void SetCount(int n);
	void SetCount(int n, const Value& v);
	int  GetCount() const;//                     { return data->data.GetCount(); }
	bool IsEmpty() const;//                      { return data->data.IsEmpty(); }

	void Add(const Value& v);
	ValueArray& operator<<(const Value& v);//    { Add(v); return *this; }
	void Set(int i, const Value& v);
	const Value& Get(int i) const;
	Value GetAndClear(int i);
	const Vector<Value>& Get() const;//          { return data ? data->data : VoidData; }
	Vector<Value> Pick();

	void Remove(int i, int count = 1);
	void Remove(const Vector<int>& ii);
	void Insert(int i, const ValueArray& va);
	void Append(const ValueArray& va);//         { Insert(GetCount(), va); }

	const Value& operator[](int i) const;//      { return Get(i); }
	
	Value& At(int i);

};

class ValueMap : public ValueType<ValueMap, VALUEMAP_V, Moveable<ValueMap> >{
	struct Data : Value::Void {
		virtual bool       IsNull() const;
		virtual void       Serialize(Stream& s);
		virtual void       Xmlize(XmlIO& xio);
		virtual void       Jsonize(JsonIO& jio);
		virtual hash_t     GetHashValue() const;
		virtual bool       IsEqual(const Value::Void *p);
		virtual String     AsString() const;
		virtual int        Compare(const Value::Void *p);

		const Value& Get(const Value& k);/* const {
			int q = key.Find(k);
			return q >= 0 ? value[q] : ErrorValue();
		}*/
		Value& GetAdd(const Value& k);/* {
			int i = key.Find(k);
			if(i < 0) {
				i = value.GetCount();
				key.Add(k);
			}
			return value.At(i);
		}*/
		Value& At(int i);/* {
			ASSERT(i < value.GetCount());
			return value.At(i);
		}*/

		Index<Value> key;
		ValueArray   value;
	};

	struct NullData : Data {};
	Data *data;

	Data& Create();
	static void Clone(Data *&ptr);
	force_inline
	static ValueMap::Data& UnShare(ValueMap::Data *&ptr);// { if(ptr->GetRefCount() != 1) Clone(ptr); return *ptr; }
	Data& UnShare();// { return UnShare(data); }
	void  Init0();
	void  FromArray(const ValueArray& va);
	
	
public:
	
	
	
	void Clear();
	int  GetCount() const;//                           { return data->value.GetCount(); }
	bool IsEmpty() const;//                            { return data->value.IsEmpty(); }
	const Value& GetKey(int i) const;//                { return data->key[i]; }
	const Value& GetValue(int i) const;//              { return data->value[i]; }
	int  Find(const Value& key) const;//               { return data ? data->key.Find(key) : -1; }
	//int  FindNext(int ii) const                     { return data ? data->key.FindNext(ii) : -1; }

	void Add(const Value& key, const Value& value);
	void Add(const String& key, const Value& value);// { Add(Value(key), value); }
	void Add(const char *key, const Value& value);//   { Add(Value(key), value); }
	void Add(int key, const Value& value);//           { Add(Value(key), value); }
	void Add(Id key, const Value& value);//            { Add(Value(key.ToString()), value); }
	
	ValueMap& operator()(const Value& key, const Value& value);//  { Add(key, value); return *this; }
	ValueMap& operator()(const String& key, const Value& value);// { Add(Value(key), value); return *this; }
	ValueMap& operator()(const char *key, const Value& value);//   { Add(Value(key), value); return *this; }
	ValueMap& operator()(int key, const Value& value);//           { Add(Value(key), value); return *this; }
	ValueMap& operator()(Id key, const Value& value);//            { Add(Value(key.ToString()), value); return *this; }

	void Set(const Value& key, const Value& value);
	void Set(const String& key, const Value& value);// { Set(Value(key), value); }
	void Set(const char *key, const Value& value);//   { Set(Value(key), value); }
	void Set(int key, const Value& value);//           { Set(Value(key), value); }
	void Set(Id key, const Value& value);//            { Set(Value(key.ToString()), value); }

	void SetAt(int i, const Value& v);
	void SetKey(int i, const Value& key);
	void SetKey(int i, const String& key);//           { SetKey(i, Value(key)); }
	void SetKey(int i, const char* key);//             { SetKey(i, Value(key)); }
	void SetKey(int i, int key);//                     { SetKey(i, Value(key)); }
	void SetKey(int i, Id key);//                      { SetKey(i, Value(key.ToString())); }

	int  RemoveKey(const Value& key);
	int  RemoveKey(const String& key);//               { return RemoveKey(Value(key)); }
	int  RemoveKey(const char* key);//                 { return RemoveKey(Value(key)); }
	int  RemoveKey(int key);//                         { return RemoveKey(Value(key)); }
	int  RemoveKey(Id key);//                          { return RemoveKey(Value(key.ToString())); }
	void Remove(int i);

	const Index<Value>& GetKeys() const;//             { return data->key; }
	ValueArray GetValues() const;//                    { return data->value; }

	operator ValueArray() const;//                    { return GetValues(); }
	
	VectorMap<Value, Value> Pick();

	const Value& operator[](const Value& key) const;//  { return data->Get(key); }
	const Value& operator[](const String& key) const;// { return operator[](Value(key)); }
	const Value& operator[](const char *key) const;//   { return operator[](Value(key)); }
	const Value& operator[](const int key) const;//     { return operator[](Value(key)); }
	const Value& operator[](const Id& key) const;//     { return operator[](Value(key.ToString())); }

	Value& GetAdd(const Value& key) {TODO_}//                 { return UnShare().GetAdd(key); }
	Value& operator()(const Value& key);//              { return GetAdd(key); }
	Value& operator()(const String& key);//             { return operator()(Value(key)); }
	Value& operator()(const char *key);//               { return operator()(Value(key)); }
	Value& operator()(const int key);//                 { return operator()(Value(key)); }
	Value& operator()(const Id& key);//                 { return operator()(Value(key.ToString())); }
	Value& At(int i);//                                 { return UnShare().At(i); }
	
	Value GetAndClear(const Value& key);

	
};


String Format(String pattern, Value v0=Value(), Value v1=Value(), Value v2=Value(), Value v3=Value(), Value v4=Value(), Value v5=Value(), Value v6=Value(), Value v7=Value());

template <class T> Value SvoToValue(const T& x) { return Value(x, Value::SMALL); }

NAMESPACE_UPP_END


#endif
