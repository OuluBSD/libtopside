#ifndef _CoreAlt_Value_h_
#define _CoreAlt_Value_h_


NAMESPACE_UPP_BEGIN

class Color;
class Image;

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

const dword WSTRING_V = 8;

const dword VALUEARRAY_V = 9;

const dword INT64_V  = 10;
const dword BOOL_V   = 11;

const dword VALUEMAP_V   = 12;
const dword COLOR_V   = 13;
const dword IMAGE_V   = 14;
const dword RECT_V   = 15;


const dword UNKNOWN_V = (dword)0xffffffff;


inline int RegisterTypeNo__(const char *type) {
	MAKE_STATIC(Index<String>, idx);
	return idx.FindAdd(type);
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
template<> inline dword ValueTypeNo(const Color*)   { return COLOR_V; }


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


class ValueInstance : RTTIBase {
protected:
	friend class Value;
	
	dword type = VOID_V;
	Atomic refs;
	
public:
	RTTI_DECL0(ValueInstance)
	ValueInstance() {refs = 0;}
	virtual ~ValueInstance() = default;
	virtual void* Get() {return 0;}
	virtual String ToString() const {return "VOID";}
	virtual int64 ToInt() const {return 0;}
	virtual double ToDouble() const {return 0;}
	virtual hash_t GetHashValue() const {return 0;}
	//virtual void Visit(RuntimeVisitor& vis) {}
	dword GetType() const {return type;}
	
	void IncRef() {++refs;}
	void DecRef() {--refs; if (refs < 0) delete this;}
};

template <class T>
class ValueTemplate : public ValueInstance {
	bool is_owned = false;
	T* ptr = NULL;
	
public:
	RTTI_DECL1(ValueTemplate, ValueInstance)
	ValueTemplate() {ptr = new T(); is_owned = true; type = ValueTypeNo<T>(0);}
	ValueTemplate(T* ptr) : ptr(ptr) {type = ValueTypeNo<T>(0);}
	ValueTemplate(const T& obj) {ptr = new T(obj); is_owned = true; type = ValueTypeNo<T>(0);}
	~ValueTemplate() {if (is_owned && ptr) {delete ptr; ptr = 0; is_owned = false; type = VOID_V;}}
	void* Get() override {return ptr;}
	String ToString() const override;
	int64 ToInt() const override;
	double ToDouble() const override;
	hash_t GetHashValue() const override {if (ptr) return ::UPP::GetHashValue(*ptr); return 0;}
	//void Visit(RuntimeVisitor& vis) override {if (ptr) ptr->Visit(vis);}
};



template <> inline String ValueTemplate<int>::ToString() const    {return ptr ? IntStr(*ptr) : String();}
template <> inline int64  ValueTemplate<int>::ToInt() const       {return ptr ? *ptr : 0;}
template <> inline double ValueTemplate<int>::ToDouble() const    {return ptr ? *ptr : 0;}
template <> inline String ValueTemplate<double>::ToString() const {return ptr ? DblStr(*ptr) : String();}
template <> inline int64  ValueTemplate<double>::ToInt() const    {return ptr ? (int64)*ptr : 0;}
template <> inline double ValueTemplate<double>::ToDouble() const {return ptr ? *ptr : 0;}
template <> inline String ValueTemplate<String>::ToString() const {return ptr ? *ptr : String();}
template <> inline String ValueTemplate<WString>::ToString() const;
template <> inline String ValueTemplate<Date>::ToString() const   {return ptr ? ptr->ToString() : String();}
template <> inline int64  ValueTemplate<Date>::ToInt() const      {return ptr ? ptr->Get() : 0;}
template <> inline double ValueTemplate<Date>::ToDouble() const   {return ptr ? (double)ptr->Get() : 0;}
template <> inline String ValueTemplate<Time>::ToString() const   {return ptr ? ptr->ToString() : String();}
template <> inline int64  ValueTemplate<Time>::ToInt() const      {return ptr ? ptr->Get() : 0;}
template <> inline double ValueTemplate<Time>::ToDouble() const   {return ptr ? (double)ptr->Get() : 0;}
template <> inline String ValueTemplate<Exc>::ToString() const    {return ptr ? *ptr : Exc();}
template <> inline String ValueTemplate<int64>::ToString() const  {return ptr ? IntStr64(*ptr) : String();}
template <> inline int64  ValueTemplate<int64>::ToInt() const     {return ptr ? *ptr : 0;}
template <> inline double ValueTemplate<int64>::ToDouble() const  {return ptr ? (double)*ptr : 0;}
template <> inline String ValueTemplate<bool>::ToString() const   {return ptr ? (*ptr ? "true" : "false") : "";}
template <> inline int64  ValueTemplate<bool>::ToInt() const      {return ptr ? *ptr : 0;}
template <> inline double ValueTemplate<bool>::ToDouble() const   {return ptr ? *ptr : 0;}

template <class T> inline String ValueTemplate<T>::ToString() const {return "";}
template <class T> inline int64  ValueTemplate<T>::ToInt() const    {return 0;}
template <class T> inline double ValueTemplate<T>::ToDouble() const {return 0;}


class Value : RTTIBase {
	RTTI_DECL0(Value)
	
	
protected:
	ValueInstance* data = 0;
	bool ref = false;
	
public:
	Value();
	Value(bool b);
	Value(int i);
	Value(int64 i);
	Value(double d);
	Value(String s);
	Value(WString s);
	Value(Date d);
	Value(Time d);
	Value(Nuller);
	Value(const ValueArray& a);
	Value(const ValueMap& m);
	Value(const Color& m);
	Value(const Image& m);
	Value(const Rect& r);
	Value(const Value& v) {*this = v;}
	~Value() {Clear();}
	
	Value& operator=(const Value& v);
	
	template <class T>
	Value& Push(byte kind, const T& val) {
		Clear();
		data = new ValueTemplate<T>(val);
		data->IncRef();
		return *this;
	}
	
	void Clear() {
		if (data) {
			data->DecRef();
			data = 0;
		}
	}
	
	hash_t GetHashValue() const;
	
	dword    GetType() const;
	bool     IsError() const         { return GetType() == ERROR_V; }
	bool     IsVoid() const          { return data == 0; }
	bool     IsNull() const;
	bool     IsNullInstance() const  {return IsNull();}

	template <class T>	bool     Is() const {return GetType() == ValueTypeNo((T*)0);}
	template <class T>	const T& To() const {
		if (Is<T>()) {
			ValueTemplate<T>* o = CastPtr<ValueTemplate<T>>(data);
			if (o) return *(T*)o->Get();
		}
		Panic("invalid value");
		NEVER();
	}
	template <class T>	const T& Get() const {return To<T>();}

	bool     IsString() const          { return data && data->type == STRING_V; }
	bool     Is(byte v) const          { return data && data->type == v; }
	bool     IsRef() const             { return data && ref; }
	
	template <class T>	void     InitSmall(const T& init);
	template <class T>	T&       GetSmallRaw() const {TODO_}
	template <class T>	T&       GetSmall() const;
	
	int      GetOtherInt() const {TODO_}
	int64    GetOtherInt64() const {TODO_}
	double   GetOtherDouble() const {TODO_}
	bool     GetOtherBool() const {TODO_}
	Date     GetOtherDate() const {TODO_}
	Time     GetOtherTime() const {TODO_}
	String   GetOtherString() const {TODO_}
	hash_t   GetOtherHashValue() const {TODO_}
	
	operator String() const          { return IsString() ? data->ToString() : GetOtherString(); }
	operator WString() const;
	operator Date() const            { return Is(DATE_V) ? GetSmallRaw<Date>() : GetOtherDate(); }
	operator Time() const            { return Is(TIME_V) ? GetSmallRaw<Time>() : GetOtherTime(); }
	operator double() const          { return Is(DOUBLE_V) ? GetSmallRaw<double>() : GetOtherDouble(); }
	operator int() const             { return Is(INT_V) ? GetSmallRaw<int>() : GetOtherInt(); }
	operator int64() const           { return Is(INT64_V) ? GetSmallRaw<int64>() : GetOtherInt64(); }
	operator bool() const            { return Is(BOOL_V) ? GetSmallRaw<bool>() : GetOtherBool(); }
	
	String operator ~() const {return operator String();}
	
	template <class T>
	operator T() {if (data && ValueTypeNo<T>(0) == data->GetType()) return *(T*)data->Get(); return T();}
	
};


template<> inline dword ValueTypeNo(const Value* v)   { return v->GetType(); }

template <class T>
Value RawToValue(const T& o) {TODO_}

template <class T>
bool IsTypeRaw(const Value& v) {TODO_}




Value        ErrorValue(const char *s);
Value        ErrorValue(const String& s);
const Value& ErrorValue();

String GetErrorText(const Value& v);


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


NAMESPACE_UPP_END


#endif
