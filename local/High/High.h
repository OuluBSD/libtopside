#ifndef _HIGHALT_HIGH_H_
#define _HIGHALT_HIGH_H_

#include <Local/Local.h>


namespace UPP {

enum HiTypeKind { HIGH_VOID, HIGH_DOUBLE, HIGH_ARRAY, HIGH_MAP, HIGH_LAMBDA, HIGH_INT64 };

String HiTypeName(int sv_type);

struct HiEscape;
class  HiLambda;
struct HiHandle;
struct Hi;

class HiValue : Moveable<HiValue> {
	struct RefCount {
		Atomic   refcount;
		RefCount()              { refcount = 1; }
	};

	int              type;
	mutable hash_t   hash;
	mutable bool	 visited = 0;
	
	struct HiMap;
	struct HiArray;

	union {
		double         number;
		int64          i64;
		HiArray      *array;
		HiMap        *map;
		HiLambda     *lambda;
	};

	void                  Free();
	void                  Assign(const HiValue& s);

	void                  InitString(const WString& w);
	Vector<HiValue>&      CloneArray();

	VectorMap<HiValue, HiValue>& CloneMap();

	static int             total;
	static int             max_total;

public:
	static int             GetTotalCount();
	static void            SetMaxTotalCount(int n);
	static int             GetMaxTotalCount();

	bool IsVoid() const                          { return type == HIGH_VOID; }
	operator bool() const                        { return type != HIGH_VOID; }
	HiValue();

	bool                   IsNumber() const      { return findarg(type, HIGH_DOUBLE, HIGH_INT64) >= 0; }
	double                 GetNumber() const;
	bool                   IsInt64() const       { return type == HIGH_INT64; }
	int64                  GetInt64() const;
	bool                   IsInt() const;
	int                    GetInt() const;
	HiValue(double n);
	HiValue(int64 n);
	HiValue(int n);

	bool                    IsArray() const      { return type == HIGH_ARRAY; }
	const Vector<HiValue>&  GetArray() const;
	HiValue&                ArrayGet(int i);
	const HiValue&          ArrayGet(int i) const;
	HiValue                 ArrayGetMid(int i, int n) const;
	bool                    ArraySet(int i, HiValue val);
	bool                    ArrayRemoveValue(HiValue val);
	bool                    Replace(int i, int n, HiValue a);
	void                    SetEmptyArray();
	HiValue&                ArrayAdd(HiValue val);
	bool                    Append(HiValue a);

	operator WString() const;
	operator String() const                    { return ::UPP::AsString(operator WString()); }
	operator int() const                       { return GetInt(); }
	operator double() const                    { return GetNumber(); }
	
	HiValue(const char *s)                     { InitString(::UPP::ToWString(String(s))); }
	HiValue(const WString& s)                  { InitString(s); }
	HiValue(const String& s)                   { InitString(::UPP::ToWString(s)); }

	bool                                IsMap() const        { return type == HIGH_MAP; }
	const VectorMap<HiValue, HiValue>&  GetMap() const;
	HiValue                             Get(HiValue key) const;
	HiValue                             MapGet(HiValue key) const {return Get(key);}
	void                                Set(HiValue key, HiValue value);
	void                                MapSet(HiValue key, HiValue value) {return Set(key,value);}
	HiValue&							MapGetAdd(HiValue key);
	HiValue&							operator[](String key);
	HiValue&							operator[](const char* key);
	const HiValue&						operator[](int i) const;
	HiValue&							operator[](int i);
	//HiValue&							operator[](HiValue i);
	//HiValue							operator()(HiValue key) const;
	HiValue								operator()(String key) const;
	HiValue								operator()(String key, HiValue def) const;
	HiValue								operator()(int i) const;
	HiValue								operator()(int i, HiValue def) const;
	void                                SetEmptyMap();

	bool                                IsLambda() const     { return type == HIGH_LAMBDA; }
	const HiLambda&                     GetLambda() const;
	HiLambda&                           CreateLambda();


	void    HighCall(const char *method, Callback1<HiEscape&> escape);
	void    HighCall(const char *method, HiHandle *h, Callback1<HiEscape&> escape);
	bool    HasNumberField(const char *id) const;
	int     GetFieldInt(const char *id) const;

	int     GetType() const                                   { return type; }
	String  GetTypeName() const                               { return UPP::HiTypeName(type); }

	int     GetCount() const;

	hash_t  GetHashValue() const;
	bool    operator==(const HiValue& a) const;
	bool    operator!=(const HiValue& a) const              { return !(*this == a); }

	String ToString(int maxlen = INT_MAX, int indent_step = 4, bool hex = false, int indent = 0) const;

	HiValue& operator=(const HiValue& s);
	HiValue(const HiValue& src);

	~HiValue();
};

struct HiValue::HiArray : HiValue::RefCount {
	Vector<HiValue> array;

	void     Retain()        { AtomicInc(refcount); }
	void     Release()       { if(AtomicDec(refcount) == 0) delete this; }
};

struct HiValue::HiMap : HiValue::RefCount {
	VectorMap<HiValue, HiValue> map;
	int                           count;

	void     Retain()        { AtomicInc(refcount); }
	void     Release()       { if(AtomicDec(refcount) == 0) delete this; }

	HiMap()                 { count = 0; }
};

struct HiHandle {
	Atomic   refcount;

	void       Retain()        { AtomicInc(refcount); }
	void       Release()       { if(AtomicDec(refcount) == 0) delete this; }

	HiHandle()                { refcount = 0; }
	virtual ~HiHandle()       {}
};

class HiLambda {
	Atomic   refcount;

	void     Retain()        { AtomicInc(refcount); }
	void     Release()       { if(AtomicDec(refcount) == 0) delete this; }

	HiLambda()                 { refcount = 1; varargs = false; handle = NULL; }
	~HiLambda()                { if(handle) handle->Release(); }

	friend class HiValue;

public:
	Vector<String>        arg;
	Vector<String>        def;
	Vector<bool>          inout;
	String                code;
	HiHandle            *handle;
	Callback1<HiEscape&>     escape;
	bool                  varargs;
	String                filename;
	int                   line;

private:
	HiLambda(const HiLambda&);
	void operator=(const HiLambda&);
};

template <>
inline hash_t GetHashValue(const HiValue& v)
{
	return v.GetHashValue();
}

bool     IsTrue(const HiValue& a);

void     SkipBlock(CParser& p);
HiValue ReadLambda(CParser& p);
HiValue ReadLambda(const char *s);

struct Hi : public CParser {
	struct SRVal : Moveable<SRVal> {
		HiValue *lval;
		HiValue  rval;
		HiValue  sbs;

		SRVal()                    { lval = NULL; }
		SRVal(const HiValue& v)   { lval = NULL; rval = v; }
		SRVal(double n)            { lval = NULL; rval = n; }
		SRVal(int64 n)             { lval = NULL; rval = n; }
		SRVal(uint64 n)            { lval = NULL; rval = (int64)n; }
		SRVal(bool n)              { lval = NULL; rval = (int64)n; }
	};

	ArrayMap<String, HiValue>& global;
	HiValue                    self;
	ArrayMap<String, HiValue>  var;

	int      skipexp;
	int      loop;
	bool     no_break, no_return, no_continue;
	int&     op_limit;
	int      r_stack_level;
	HiValue return_value;

	static int stack_level;

	void       OutOfMemory();

	void       TestLimit();
	double     DoCompare(const HiValue& a, const HiValue& b, const char *op);
	double     DoCompare(const SRVal& a, const char *op);
	String     ReadName();
	HiValue   ExecuteLambda(const String& id, HiValue lambda, SRVal self, Vector<SRVal>& arg);

	void       Assign(HiValue& val, const Vector<HiValue>& sbs, int si, const HiValue& src);

	HiValue   Get(const SRVal& val);
	void       Assign(const SRVal& val, const HiValue& src);

	HiValue   GetExp();

	double Number(const HiValue& a, const char *oper);
	int64  Int(const HiValue& a, const char *oper);
	double Number(const SRVal& a, const char *oper);
	int64  Int(const SRVal& a, const char *oper);

	HiValue   MulArray(HiValue array, HiValue times);

	void  Subscript(SRVal& r, SRVal _self, String id);
	void  Subscript(SRVal& r);
	void  Term(SRVal& r);
	void  Unary(SRVal& r);
	void  Mul(SRVal& r);
	void  Add(SRVal& r);
	void  Shift(SRVal& r);
	void  Compare(SRVal& r);
	void  Equal(SRVal& r);
	void  BinAnd(SRVal& r);
	void  BinXor(SRVal& r);
	void  BinOr(SRVal& r);
	void  And(SRVal& r);
	void  Or(SRVal& r);
	void  Cond(SRVal& r);
	void  Assign(SRVal& r);
	void  Exp(SRVal& r);

	void  SkipTerm();
	void  SkipStatement();
	void  SkipExp();
	bool  PCond();
	void  FinishSwitch();
	void  DoStatement();

	void  Run();

	Hi(ArrayMap<String, HiValue>& global, const char *s, int& oplimit,
	    const String& fn, int line = 1)
	: CParser(s, fn, line), global(global), op_limit(oplimit)
	{ r_stack_level = stack_level;  skipexp = false; }
	~Hi() { stack_level = r_stack_level; }
};

struct HiEscape {
	Hi&             esc;
	HiValue         self;
	Array<HiValue>& arg;
	HiValue         ret_val;
	String           id;

	HiValue&    operator[](int i)             { return arg[i]; }
	int          GetCount() const              { return arg.GetCount(); }
	void         operator=(const HiValue& v)  { ret_val = v; }
	operator     HiValue&()                   { return ret_val; }
	void         ThrowError(const char *s)     { esc.ThrowError(s); }

	String       DumpType(int i);
	String       InCall();

	void         CheckNumber(int i);
	void         CheckArray(int i);
	void         CheckMap(int i);

	double       Number(int i);
	int          Int(int i);

	HiEscape(Hi& esc, HiValue self, Array<HiValue>& arg)
	  : esc(esc), self(self), arg(arg) {}
};

void HighCall(ArrayMap<String, HiValue>& globals, const char *function, void (*escape)(HiEscape& e));

inline // resolve overloading with Function...
void Hifn(ArrayMap<String, HiValue>& globals, const char *function, void (*escape)(HiEscape& e))
{
	return HighCall(globals, function, escape);
}

void HighCall(ArrayMap<String, HiValue>& globals, const char *function, Callback1<HiEscape&> escape);

void Scan(ArrayMap<String, HiValue>& global, const char *code, const char *filename = "");

void StdLib(ArrayMap<String, HiValue>& global);

void     LambdaArgs(CParser& p, HiLambda& l);

HiValue  Execute(ArrayMap<String, HiValue>& global, HiValue *self,
                 const HiValue& lambda, Vector<HiValue>& arg, int oplimit = 50000);
HiValue  Execute(ArrayMap<String, HiValue>& global, HiValue *self,
                 const char *name, Vector<HiValue>& arg, int oplimit = 50000);
HiValue  Execute(ArrayMap<String, HiValue>& global, const char *name, int oplimit = 50000);

HiValue  Evaluatex(const char *expression, ArrayMap<String, HiValue>& global, int oplimit = 50000);
HiValue  Evaluate(const char *expression, ArrayMap<String, HiValue>& global, int oplimit = 50000);

HiValue  HiFromStdValue(const Object& v);
Object   StdValueFromHi(const HiValue& v);
void     StdValueLib(ArrayMap<String, HiValue>& global);

bool     IsDate(const HiValue& v);
bool     IsTime(const HiValue& v);

String   StdFormat(const Value& q);
String   StdFormatObj(const Object& q);

String   Expand(const String& doc, ArrayMap<String, HiValue>& global,
                int oplimit = 50000, String (*format)(const Object& v) = StdFormatObj);


}

#endif
