#include "Core.h"

NAMESPACE_UPP


Value::Value(bool b) {
	TODO
}

Value::Value(int i) {
	TODO
}

Value::Value(int64 i) {
	TODO
}

Value::Value(double d) {
	TODO
}

Value::Value(String s) {
	TODO
}

Value::Value(WString s) {
	TODO
}

Value::Value(Date d) {
	TODO
}

Value::Value(Time d) {
	TODO
}

Value::Value(Nuller) {
	TODO
}

Value::Value(const ValueArray& a) {
	TODO
}

Value::Value(const ValueMap& m) {
	TODO
}

Value::Value(Color m) {
	TODO
}

Value& Value::operator=(const Value& v) {
	TODO
}

dword Value::GetType() const {
	TODO
}

bool Value::IsNull() const {
	TODO
}
















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
					out << (String)*v[arg++];
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



String StdFormat(const Value& q) {
	TODO
}

String StdFormatObj(const Object& q) {
	TODO
}

END_UPP_NAMESPACE
