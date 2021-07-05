#include <Local/Local.h>

NAMESPACE_UPP


void IdParser::Parse() {
	const String& n = input;
	int& cursor = pos;
	
	if (cursor < input.GetCount()) {
		int chr = input[cursor];
		
		if (IsAlpha(chr) || chr == '_') {
			id.Cat(chr);
			cursor++;
			while (cursor < input.GetCount()) {
				int chr = input[cursor];
				if (IsAlpha(chr) || chr == '_' || IsDigit(chr)) {
					id.Cat(chr);
					cursor++;
				}
				else
					break;
			}
			is_valid = true;
		}
	}
}


void StringParser::Parse() {
	const String& n = input;
	int& cursor = pos;
	
	if (cursor < input.GetCount()) {
		int chr = input[cursor];
		if (chr == delim) {
			cursor++;
			bool skip_check = false;
			while (cursor < input.GetCount()) {
				int chr = input[cursor++];
				if (skip_check) {
					skip_check = false;
				}
				else if (chr == '\\') {
					skip_check = true;
				}
				else if (chr == delim) {
					is_valid = true;
					break;
				}
				str.Cat(chr);
			}
		}
	}
	if (is_valid || !checkend) {
		str = FromCString(str.Begin(), str.End());
	}
}


void NumberParser::Parse() {
	String& n = str;
	
	bool neg_value = false;
	int chr = input[cursor];
	if (chr == '-') {
		n.Cat(chr);
		if (++cursor >= input.GetCount()) chr = 0;
		else chr = input[cursor];
		neg_value = true;
	}
	else if (chr == '+') {
		n.Cat(chr);
		if (++cursor >= input.GetCount()) chr = 0;
		else chr = input[cursor];
	}
	if (IsDigit(chr)) {
		int upcoming_type = NumberParser::INT;
		bool is_float = false;
		n.Cat(chr);
		cursor++;
		enum {INT, DEC, FRAC, SIGN, EXP, F, END, OCTHEXBIN, OCT, HEX, BIN};
		int exp = chr == '0' ? OCTHEXBIN : INT;
		while (cursor < input.GetCount()) {
			int chr = input[cursor];
			bool cat = false;
			
			if (exp == INT) {
				if (IsDigit(chr)) {
					cat = true;
					upcoming_type = NumberParser::INT;
				}
				else if (chr == '.') {
					exp = FRAC;
					cat = true;
					upcoming_type = is_float ? NumberParser::FLOAT : NumberParser::DOUBLE;
				}
				else if (chr == 'e' || chr == 'E') {
					exp = SIGN;
					cat = true;
					upcoming_type = is_float ? NumberParser::FLOAT : NumberParser::DOUBLE;
				}
			}
			else if (exp == FRAC) {
				if (IsDigit(chr))
					cat = true;
				else if (chr == 'e' || chr == 'E') {
					exp = SIGN;
					cat = true;
					upcoming_type = is_float ? NumberParser::FLOAT : NumberParser::DOUBLE;
				}
			}
			else if (exp == SIGN) {
				if (chr == '+' || chr == '-' || IsDigit(chr)) {
					exp = EXP;
					cat = true;
				}
				else if (chr == 'f' || chr == 'F') {
					exp = END;
					cat = true;
					is_float = true;
					upcoming_type = NumberParser::FLOAT;
				}
			}
			else if (exp == EXP) {
				if (IsDigit(chr))
					cat = true;
				else if (chr == 'f' || chr == 'F') {
					exp = END;
					cat = true;
					is_float = true;
					upcoming_type = NumberParser::FLOAT;
				}
			}
			else if (exp == OCTHEXBIN) {
				if (chr == 'x' || chr == 'X') {
					exp = HEX;
					cat = true;
					upcoming_type = NumberParser::HEX;
				}
				else if (chr == 'b' || chr == 'B') {
					exp = BIN;
					cat = true;
					upcoming_type = NumberParser::BIN;
				}
				else if (chr >= '0' && chr <= '7') {
					exp = OCT;
					cat = true;
					upcoming_type = NumberParser::OCT;
				}
				else if (chr == '.') {
					exp = FRAC;
					cat = true;
					upcoming_type = is_float ? upcoming_type = NumberParser::FLOAT : NumberParser::DOUBLE;
				}
			}
			else if (exp == HEX) {
				if ((chr >= '0' && chr <= '9') ||
					(chr >= 'a' && chr <= 'f') ||
					(chr >= 'A' && chr <= 'F')) {
					cat = true;
				}
			}
			else if (exp == BIN) {
				if (chr == '0' || chr == '1') {
					cat = true;
				}
			}
			else if (exp == OCT) {
				if (chr >= '0' && chr <= '7') {
					cat = true;
				}
			}
			
			if (cat) {
				cursor++;
				n.Cat(chr);
				if (exp == END) break;
			}
			else break;
		}
		
		
		this->type = upcoming_type;
		if (upcoming_type == NumberParser::OCT) {
			i32 = (neg_value ? -1 : +1) * OctInt(n);
			u32 = i32;
			i64 = i32;
			f = i32;
			d = i32;
		}
		else if (upcoming_type == NumberParser::BIN) {
			i64 = (neg_value ? -1 : +1) * BinInt64(n);
			u32 = i64;
			i32 = i64;
			f = i64;
			d = i64;
		}
		else if (upcoming_type == NumberParser::HEX) {
			i64 = (neg_value ? -1 : +1) * HexInt64(n);
			u32 = i64;
			i32 = i64;
			f = i64;
			d = i64;
		}
		else if (upcoming_type == NumberParser::INT) {
			i64 = (neg_value ? -1 : +1) * StrInt64(n);
			u32 = i64;
			i32 = i64;
			f = i64;
			d = i64;
		}
		else if (upcoming_type == NumberParser::FLOAT || upcoming_type == NumberParser::DOUBLE) {
			d = (neg_value ? -1 : +1) * StrDbl(n);
			i32 = d;
			u32 = d;
			i64 = d;
			f = d;
		}
	}
}


END_UPP_NAMESPACE
