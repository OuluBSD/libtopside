#include <High/High.h>


namespace UPP {

#define LTIMING(x)  // RTIMING(x)

void HIGH_count(HiEscape& e)
{
	e = e[0].GetCount();
}

void HIGH_is_void(HiEscape& e)
{
	e = e[0].IsVoid();
}

void HIGH_is_number(HiEscape& e)
{
	e = e[0].IsNumber();
}

void HIGH_is_array(HiEscape& e)
{
	e = e[0].IsArray();
}

void HIGH_is_map(HiEscape& e)
{
	e = e[0].IsMap();
}

void HIGH_int(HiEscape& e)
{
	if(e[0].IsNumber())
		e = (int)e[0].GetNumber();
}

void HIGH_to_string(HiEscape& e)
{
	e = e[0].ToString();
}

void HIGH_to_number(HiEscape& e)
{
	if(e[0].IsArray()) {
		double d = ScanDouble((String)e[0]);
		if(IsFin(d)) {
			if(FitsInInt64(d))
				e = ScanInt64((String)e[0]);
			else
				e = d;
		}
	}
}

void HIGH_rand(HiEscape& e)
{
	e = rand();
}

void HIGH_keys(HiEscape& e)
{
	e.CheckMap(0);
	HiValue v;
	const VectorMap<HiValue, HiValue>& m = e[0].GetMap();
	for(int i = 0; i < m.GetCount(); i++)
		v.ArrayAdd(m.GetKey(i));
	e = v;
}

void HIGH_values(HiEscape& e)
{
	e.CheckMap(0);
	HiValue v;
	const VectorMap<HiValue, HiValue>& m = e[0].GetMap();
	for(int i = 0; i < m.GetCount(); i++)
		v.ArrayAdd(m[i]);
	e = v;
}

void HIGH_reverse(HiEscape& e)
{
	e.CheckArray(0);
	const Vector<HiValue>& a = e[0].GetArray();
	HiValue r;
	for(int i = a.GetCount() - 1; i >= 0; i--)
		r.ArrayAdd(a[i]);
	e = r;
}

#if !USE_HIGH_BYTECODE

struct HiCmp {
	Hi *esc;
	bool operator()(const HiValue& a, const HiValue& b) const {
		return esc->DoCompare(a, b, "< (sort)") < 0;
	}
};

Vector<int> HiGetSortOrder(HiEscape& e)
{
	e.CheckArray(0);
	const Vector<HiValue>& va = e[0].GetArray();
	HiCmp cmp;
	cmp.esc = &e.esc;
	return GetSortOrder(va, cmp);
}

void HIGH_sort(HiEscape& e)
{
	Vector<int> so = HiGetSortOrder(e);
	HiValue r;
	for(int i = 0; i < so.GetCount(); i++)
		r.ArrayAdd(e[0].ArrayGet(so[i]));
	e = r;
}

void HIGH_order(HiEscape& e)
{
	Vector<int> so = HiGetSortOrder(e);
	HiValue r;
	for(int i = 0; i < so.GetCount(); i++)
		r.ArrayAdd(so[i]);
	e = r;
}

#endif

// ---------------------------

void HIGH_mid(HiEscape& e)
{
	e.CheckArray(0);
	int pos = e.Int(1);
	int count = e.Int(2);
	if(pos < 0 || pos + count > e[0].GetCount())
		e.ThrowError("out of bounds in call to 'mid'");
	e.ret_val = e[0].ArrayGetMid(pos, count);
}

void HIGH_exists(HiEscape& e)
{
	e.CheckMap(0);
	e = !e[0].MapGet(e[1]).IsVoid();
}

struct HIGH_FileOut : public HiHandle {
	FileStream file;
	void Put(HiEscape& e)         { if(file) file.Put(e.Int(0)); }
	void PutLine(HiEscape& e)     { if(file) file.PutLine(String(e[0])); }
	void Close(HiEscape& e)       { if(file) file.Close(); }

	typedef HIGH_FileOut CLASSNAME;

	HIGH_FileOut(HiEscape& e, HiValue& v, int style) {
		file.Open(String(e[0]), style);
		v.HighCall("Put(a)", this, THISBACK(Put));
		v.HighCall("PutLine(a)", this, THISBACK(PutLine));
		v.HighCall("Close()", this, THISBACK(Close));
	}
};

void HIGH_OpenFileOut(HiEscape& e)
{
	HiValue v;
	HIGH_FileOut *f = new HIGH_FileOut(e, v, FileStream::CREATE);
	if(f->file)
		e = v;
}

void HIGH_OpenFileAppend(HiEscape& e)
{
	HiValue v;
	HIGH_FileOut *f = new HIGH_FileOut(e, v, FileStream::APPEND);
	if(f->file)
		e = v;
}

struct HIGH_FileIn : public HiHandle {
	FileIn file;
	void IsEof(HiEscape& e)       { e = file.IsEof(); }
	void Get(HiEscape& e)         { e = file.Get(); }
	void GetLine(HiEscape& e)     { e = file.GetLine(); }
	void Close(HiEscape& e)       { if (file) file.Close(); }

	typedef HIGH_FileIn CLASSNAME;

	HIGH_FileIn(HiEscape& e, HiValue& v) {
		file.Open(String(e[0]));
		v.HighCall("IsEof()", this, THISBACK(IsEof));
		v.HighCall("Get()", this, THISBACK(Get));
		v.HighCall("GetLine()", this, THISBACK(GetLine));
		v.HighCall("Close()", this, THISBACK(Close));
	}
};

void HIGH_OpenFileIn(HiEscape& e)
{
	HiValue v;
	HIGH_FileIn *f = new HIGH_FileIn(e, v);
	if(f->file)
		e = v;
}

// ---------------------------

bool IsDate(const HiValue& v)
{
	return v.HasNumberField("year") && v.HasNumberField("month") && v.HasNumberField("day");
}

bool IsTime(const HiValue& v)
{
	return IsDate(v) && v.HasNumberField("hour") && v.HasNumberField("minute") && v.HasNumberField("second");
}

void SIC_IsDate(HiEscape& e)
{
	e = IsDate(e[0]);
}

void SIC_IsTime(HiEscape& e)
{
	e = IsTime(e[0]);
}

void SIC_GetSysTime(HiEscape& e)
{
	Time tm = GetSysTime();
	HiValue v;
	v.MapSet("year", (int)tm.year);
	v.MapSet("month", (int)tm.month);
	v.MapSet("day", (int)tm.day);
	v.MapSet("hour", (int)tm.hour);
	v.MapSet("minute", (int)tm.minute);
	v.MapSet("second", (int)tm.second);
	e = v;
}

void HIGH_ToLower(HiEscape& e)
{
	String s = e[0];
	e = ToLower(s);
}

void HIGH_ToUpper(HiEscape& e)
{
	String s = e[0];
	e = ToUpper(s);
}

// ---------------------------

void HIGH_replace(HiEscape& e)
{
	String str = e[0];
	str.Replace(e[1], e[2]);
	e = str;
}

// ---------------------------

void StdLib(ArrayMap<String, HiValue>& global)
{
	HighCall(global, "is_number(value)", HIGH_is_number);
	HighCall(global, "is_array(value)", HIGH_is_array);
	HighCall(global, "is_map(value)", HIGH_is_map);
	HighCall(global, "is_void(value)", HIGH_is_void);
	HighCall(global, "int(value)", HIGH_int);
	HighCall(global, "to_string(value)", HIGH_to_string);
	HighCall(global, "to_number(value)", HIGH_to_number);
	HighCall(global, "count(value)", HIGH_count);
	HighCall(global, "keys(map)", HIGH_keys);
	HighCall(global, "values(map)", HIGH_values);
	HighCall(global, "rand()", HIGH_rand);
	HighCall(global, "reverse(array)", HIGH_reverse);
	
	#if !USE_HIGH_BYTECODE
	HighCall(global, "sort(array)", HIGH_sort);
	HighCall(global, "order(array)", HIGH_order);
	#endif
	
	HighCall(global, "replace(str, find, replace)", HIGH_replace);
	
	HighCall(global, "ToUpper(value)", HIGH_ToUpper);
	HighCall(global, "ToLower(value)", HIGH_ToLower);
	
	HighCall(global, "len(x)", HIGH_count);
	HighCall(global, "mid(array, pos, count)", HIGH_mid);
	HighCall(global, "exists(map, key)", HIGH_exists);

	HighCall(global, "OpenFileOut(x)", HIGH_OpenFileOut);
	HighCall(global, "OpenFileAppend(x)", HIGH_OpenFileOut);
	HighCall(global, "OpenFileIn(x)", HIGH_OpenFileIn);

	HighCall(global, "GetSysTime()", SIC_GetSysTime);
	HighCall(global, "IsDate(x)", SIC_IsDate);
	HighCall(global, "IsTime(x)", SIC_IsTime);

	#define FN(fn) Hifn(global, #fn "(value)", [](HiEscape& e) { e = fn(e[0].GetNumber()); });
	
	FN(sin)
	FN(cos)
	FN(tan)
	FN(asin)
	FN(acos)
	FN(atan)

	FN(sinh)
	FN(cosh)
	FN(tanh)
	FN(asinh)
	FN(acosh)
	FN(atanh)
	
	FN(exp)
	FN(log)
	FN(log10)
	FN(exp2)
	FN(log2)
	FN(sqrt)
	FN(cbrt)
	
	#undef FN
	
	Hifn(global, "pow(base, exponent)", [](HiEscape& e) { e = pow(e[0].GetNumber(), e[1].GetNumber()); });
	Hifn(global, "atan2(a, b)", [](HiEscape& e) { e = atan2(e[0].GetNumber(), e[1].GetNumber()); });
}

}
