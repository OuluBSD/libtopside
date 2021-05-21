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


const dword UNKNOWN_V = (dword)0xffffffff;


inline int RegisterTypeNo__(const char *type) {
	static Index<String> idx;
	return idx.FindAdd(type);
}



class ValueArray;
class ValueMap;

class Value {
	
	
public:
	Value() {}
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
	Value(Color m);
	Value(const Value& v) {*this = v;}
	
	Value& operator=(const Value& v);
	
	
	template <class T>
	T&	To() {TODO}
	
	
	operator int() const;
	operator String() const;
	
};


template <class T>
Value RawToValue(const T& o) {TODO}

template <class T>
bool IsTypeRaw(const Value& v) {TODO}

NAMESPACE_UPP_END


#endif
