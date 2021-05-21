#include "Core.h"


NAMESPACE_UPP_BEGIN

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








void CParser::SkipSpaces() {
	while (!IsEnd()) {
		int chr = input[pos.cursor];
		if (!IsSpace(chr))
			break;
		ChkNewline(chr);
		pos.cursor++;
		pos.col++;
	}
}

bool CParser::IsEnd() const {
	return pos.cursor >= input.GetCount();
}

/*FileLocation CParser::GetLocation() const {
	FileLocation loc;
	loc.col = 1;
	loc.line = 1;
	loc.file = "CParser";
	const char* it = input.Begin();
	const char* end = it + std::max(0, pos);
	while (it != end) {
		char chr = *it++;
		if (chr == '\n') {
			loc.col = 1;
			loc.line++;
		}
		else {
			loc.col++;
		}
	}
	return loc;
}*/

bool CParser::GetId(String& str) {
	IdParser ip(input, pos.cursor);
	if (ip.is_valid) {
		pos.cursor = ip.pos;
		str = ip.id;
		DoSpaces();
		return true;
	}
	return false;
}

bool CParser::GetInt(int64& i64) {
	NumberParser np(input, pos.cursor);
	if (np.type == NumberParser::INT ||
		np.type == NumberParser::HEX ||
		np.type == NumberParser::OCT) {
		pos.cursor = np.cursor;
		i64 = np.i64;
		DoSpaces();
		return true;
	}
	return false;
}

bool CParser::GetFloating(double& dbl) {
	NumberParser np(input, pos.cursor);
	if (np.type == NumberParser::FLOAT || np.type == NumberParser::DOUBLE) {
		pos.cursor = np.cursor;
		dbl = np.d;
		DoSpaces();
		return true;
	}
	return false;
}

void CParser::ThrowError(const char *s) {
	Throw(CParser::Error(String(s) + " at " + pos.fn + ":" + IntStr(pos.line) + ":" + IntStr(pos.col)));
}

String CParser::ReadId() {
	IdParser ip(input, pos.cursor);
	if (ip.is_valid) {
		pos.cursor = ip.pos;
		DoSpaces();
		return ip.id;
	}
	ThrowError("Couldn't read id");
	return String();
}

String CParser::ReadString(char delim, bool checkend) {
	StringParser ip(input, pos.cursor, delim, checkend);
	if (ip.is_valid) {
		pos.cursor = ip.pos;
		DoSpaces();
		return ip.str;
	}
	ThrowError("Couldn't read string");
	return String();
}

int CParser::ReadInt() {
	NumberParser np(input, pos.cursor);
	if (np.type == NumberParser::INT ||
		np.type == NumberParser::HEX ||
		np.type == NumberParser::OCT) {
		pos.cursor = np.cursor;
		DoSpaces();
		return np.i32;
	}
	ThrowError("Couldn't read int");
	return 0;
}

double CParser::ReadDouble() {
	NumberParser np(input, pos.cursor);
	if (np.type == NumberParser::INT ||
		np.type == NumberParser::FLOAT ||
		np.type == NumberParser::DOUBLE) {
		pos.cursor = np.cursor;
		DoSpaces();
		return np.d;
	}
	ThrowError("Couldn't read double");
	return 0;
}

double CParser::ReadNumber() {
	NumberParser np(input, pos.cursor);
	if (np.type != NumberParser::INVALID) {
		pos.cursor = np.cursor;
		DoSpaces();
		return np.d;
	}
	ThrowError("Couldn't read number");
	return 0;
}

uint64 CParser::ReadNumber64(int base) {
	const char* err;
	int type;
	if (base == 10) {
		type = NumberParser::INT;
		err = "Couldn't parse base-10 integer";
	}
	else if (base == 16) {
		type = NumberParser::HEX;
		err = "Couldn't parse base-16 integer";
	}
	else if (base == 8) {
		type = NumberParser::OCT;
		err = "Couldn't parse base-8 integer";
	}
	else if (base == 2) {
		type = NumberParser::BIN;
		err = "Couldn't parse base-2 integer";
	}
	else {
		ThrowError("Invalid ReadNumber64 base " + IntStr(base));
		return 0;
	}
	NumberParser np(input, pos.cursor);
	if (np.type == type) {
		pos.cursor = np.cursor;
		DoSpaces();
		return np.i64;
	}
	ThrowError(err);
	return 0;
}

void CParser::PassChar(char chr) {
	if (pos.cursor < input.GetCount() && input[pos.cursor] == chr) {
		ChkNewline(chr);
		pos.cursor++;
		pos.col++;
		DoSpaces();
	}
	else {
		String s; s.Cat(chr);
		ThrowError("char did not match: " + s);
	}
}

void CParser::PassId(String id) {
	if (IsId(id))
		ReadId();
	else
		ThrowError("id did not match: " + id);
}

void CParser::PassNewline() {
	PassChar('\n');
}

bool CParser::Id(String id) {
	IdParser ip(input, pos.cursor);
	if (ip.is_valid && ip.id == id) {
		pos.cursor = ip.pos;
		DoSpaces();
		return true;
	}
	return false;
}

int CParser::PeekChar() const {
	int n = pos.cursor;
	return n < input.GetCount() ? input[n] : 0;
}

bool CParser::Char(char chr) {
	if (IsChar(chr)) {
		ChkNewline(chr);
		pos.cursor++;
		pos.col++;
		DoSpaces();
		return true;
	}
	return false;
}

bool CParser::Char2(char a, char b) {
	if (IsChar2(a, b)) {
		ChkNewline(a);
		ChkNewline(b);
		pos.cursor+=2;
		pos.col+=2;
		DoSpaces();
		return true;
	}
	return false;
}

bool CParser::Char3(char a, char b, char c) {
	if (IsChar3(a, b, c)) {
		ChkNewline(a);
		ChkNewline(b);
		ChkNewline(c);
		pos.cursor+=3;
		pos.col+=3;
		DoSpaces();
		return true;
	}
	return false;
}

bool CParser::Newline() {
	return Char('\n');
}

bool CParser::IsId() const {
	IdParser ip(input, pos.cursor);
	return ip.is_valid;
}

bool CParser::IsId(String id) const {
	IdParser ip(input, pos.cursor);
	if (ip.is_valid && ip.id == id) {
		return true;
	}
	return false;
}

bool CParser::IsInt() const {
	NumberParser np(input, pos.cursor);
	if (np.type == NumberParser::INT ||
		np.type == NumberParser::HEX ||
		np.type == NumberParser::OCT) {
		return true;
	}
	return false;
}

bool CParser::IsChar(char i) const {
	if (pos.cursor < input.GetCount())
		return input[pos.cursor] == i;
	return false;
}

bool CParser::IsChar2(char a, char b) const {
	if (pos.cursor+1 < input.GetCount())
		return input[pos.cursor] == a && input[pos.cursor+1] == b;
	return false;
}

bool CParser::IsChar3(char a, char b, char c) const {
	if (pos.cursor+2 < input.GetCount())
		return input[pos.cursor] == a && input[pos.cursor+1] == b && input[pos.cursor+2] == c;
	return false;
}

bool CParser::IsCharDigit() const {
	if (pos.cursor < input.GetCount())
		return IsDigit(input[pos.cursor]);
	return false;
}

bool CParser::IsNumber() const {
	NumberParser np(input, pos.cursor);
	return np.type!= NumberParser::INVALID;
}

bool CParser::IsString() const {
	StringParser ip(input, pos.cursor);
	return ip.is_valid;
}

void CParser::SkipTerm() {
	if(IsId())
		ReadId();
	else
	if(IsNumber())
		ReadNumber();
	else
	if(IsString())
		ReadString();
	else
	if(IsChar('\''))
		ReadString('\'');
	else
	if (!IsEof())
		PassChar(PeekChar());
	
	DoSpaces();
}





NAMESPACE_UPP_END
