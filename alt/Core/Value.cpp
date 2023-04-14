#include "Core.h"

NAMESPACE_UPP

template <> String ValueTemplate<WString>::ToString() const {return ptr ? ptr->ToString() : String();}


const Nuller Null;


Value::Value(bool b) {
	Push(BOOL_V, b);
}

Value::Value(int i) {
	Push(INT_V, i);
}

Value::Value(int64 i) {
	Push(INT64_V, i);
}

Value::Value(double d) {
	Push(DOUBLE_V, d);
}

Value::Value(String s) {
	Push(STRING_V, s);
}

Value::Value(WString s) {
	Push(WSTRING_V, s);
}

Value::Value(Date d) {
	Push(DATE_V, d);
}

Value::Value(Time d) {
	Push(TIME_V, d);
}

Value::Value() {
	
}

Value::Value(Nuller) {
	
}

Value::Value(const ValueArray& a) {
	TODO
}

Value::Value(const ValueMap& m) {
	TODO
}

Value::Value(const Color& m) {
	Push(COLOR_V, m);
}

Value::Value(const Rect& r) {
	Push(RECT_V, r);
}

/*Value::Value(Color m) {
	Push(COLOR_V, m);
}*/

Value& Value::operator=(const Value& v) {
	data = v.data;
	return *this;
}

dword Value::GetType() const {
	return data ? data->GetType() : VOID_V;
}

bool Value::IsNull() const {
	return !data;
}

#if 0
int Value::GetOtherInt() const {
	byte t = data.GetSpecial();
	switch (t) {
		case INT_V: return Pop<int>();
		case INT64_V: return (int)Pop<int64>();
		case DOUBLE_V: return Pop<double>();
		case BOOL_V: return Pop<bool>();
		default: return 0;
	}
}
int64 Value::GetOtherInt64() const {
	byte t = data.GetSpecial();
	switch (t) {
		case INT_V: return Pop<int>();
		case INT64_V: return Pop<int64>();
		case DOUBLE_V: return Pop<double>();
		case BOOL_V: return Pop<bool>();
		default: return 0;
	}
}
double Value::GetOtherDouble() const {
	byte t = data.GetSpecial();
	switch (t) {
		case INT_V: return Pop<int>();
		case INT64_V: return Pop<int64>();
		case DOUBLE_V: return Pop<double>();
		case BOOL_V: return Pop<bool>();
		default: return 0;
	}
}
bool Value::GetOtherBool() const {
	byte t = data.GetSpecial();
	switch (t) {
		case INT_V: return Pop<int>();
		case INT64_V: return Pop<int64>();
		case DOUBLE_V: return Pop<double>();
		case BOOL_V: return Pop<bool>();
		default: return 0;
	}
}
Date Value::GetOtherDate() const {
	byte t = data.GetSpecial();
	switch (t) {
		case DATE_V: return Pop<Date>();
		case TIME_V: return Pop<Time>();
		default: return Date();
	}
}
Time Value::GetOtherTime() const {
	byte t = data.GetSpecial();
	if (t == DATE_V) {
		Date d = Pop<Date>();
		return Time(d.year, d.month, d.day,0,0,0);
	}
	switch (t) {
		case TIME_V: return Pop<Time>();
		default: return Time();
	}
}
String Value::GetOtherString() const {
	byte t = data.GetSpecial();
	if (t == WSTRING_V) {
		int chars = data.GetCount() / sizeof(wchar);
		WString ws;
		ws.Set((const wchar*)data.Begin(), chars);
		return ws.ToString();
	}
	if (t == COLOR_V) {
		Color c = Pop<Color>();
		return "Color(" + IntStr(c.GetR()) + ", " + IntStr(c.GetG()) + ", " + IntStr(c.GetB()) + ")";
	}
	switch (t) {
		case INT_V: return IntStr(Pop<int>());
		case INT64_V: return IntStr64(Pop<int64>());
		case DOUBLE_V: return DblStr(Pop<double>());
		case BOOL_V: return Pop<bool>() ? "true" : "false";
		default: return 0;
	}
}
hash_t Value::GetOtherHashValue() const {
	byte t = data.GetSpecial();
	switch (t) {
		case VOID_V: return 0;
		case INT_V: return UPP::GetHashValue(Pop<int>());
		case INT64_V: return UPP::GetHashValue(Pop<int64>());
		case DOUBLE_V: return UPP::GetHashValue(Pop<double>());
		case BOOL_V: return UPP::GetHashValue(Pop<bool>());
		case DATE_V: return UPP::GetHashValue(Pop<Date>());
		case TIME_V: return UPP::GetHashValue(Pop<Time>());
		case COLOR_V: return UPP::GetHashValue(Pop<Color>());
		default: return 0;
	}
}

#endif














String Format(String pattern, Value v0, Value v1, Value v2, Value v3, Value v4, Value v5, Value v6, Value v7) {
	static const int MAX_ARGS = 8;
	Value* v[MAX_ARGS] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7};
	
	if (pattern.IsEmpty()) return "";
	
	int arg = 0;
	String out;
	const char* it  = pattern.Begin();
	const char* end = pattern.End();
	while (it != end) {
		int chr = *it++;
		
		if (chr == '\\' && *it == '%') {
			chr = *it++;
			out.Cat(chr);
		}
		else if (chr == '\%') {
			enum {
				MAIN_SWITCH
			};
			enum {
				TYPE_INVALID,
				TYPE_STRING,
				TYPE_INT_HEX_UP,
				TYPE_INT_HEX_LOW,
				TYPE_NORMAL,
				TYPE_DECIMAL,
			};
			int state = MAIN_SWITCH;
			int type = TYPE_INVALID;
			while (it != end) {
				chr = *it++;
				if (state == MAIN_SWITCH) {
					#define CHR_RULE(ch, type_) else if (chr == ch) {type = type_; break;}
					if (0)
						;
					CHR_RULE('s', TYPE_STRING)
					CHR_RULE('X', TYPE_INT_HEX_UP)
					CHR_RULE('x', TYPE_INT_HEX_LOW)
					CHR_RULE('n', TYPE_NORMAL)
					CHR_RULE('d', TYPE_DECIMAL)
					else break;
				}
				else break;
			}
			
			if (type == TYPE_INVALID)
				out << "<invalid>";
			
			else if (type == TYPE_STRING) {
				if (arg < MAX_ARGS)
					out << ~*v[arg++];
				else
					out << "<arg overflow " << arg++ << ">";
			}
			
			else if (type == TYPE_INT_HEX_UP)  {out << HexStr((int64)*v[arg++], false, true);}
			else if (type == TYPE_INT_HEX_LOW) {out << HexStr((int64)*v[arg++], false, false);}
			else if (type == TYPE_NORMAL) {out << DblStr((double)*v[arg++]);}
			else if (type == TYPE_DECIMAL) {out << IntStr64((int64)*v[arg++]);}
		}
		else {
			out.Cat(chr);
		}
	}
	return out;
}

String GetErrorText(const Value& v) {
	ASSERT(v.Is<Exc>());
	return v.To<Exc>();
}

END_UPP_NAMESPACE
