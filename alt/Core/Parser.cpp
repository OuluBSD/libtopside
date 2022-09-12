#include "Core.h"


NAMESPACE_UPP_BEGIN


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

void CParser::SkipChar() {
	int chr = input[pos.cursor];
	ChkNewline(chr);
	pos.cursor++;
	pos.col++;
}

void CParser::DoSpaces() {
	while (1) {
		if (pass_whitespace)
			SkipSpaces();
		if (pass_comments) {
			if (DoComments())
				continue;
		}
		break;
	}
}

void CParser::Spaces() {
	DoSpaces();
}

bool CParser::DoComments() {
	if (Char2('/', '/')) {
		while (pos.cursor < input.GetCount()) {
			if (IsChar('\n') || IsChar2('\r','\n'))
				break;
			pos.cursor++;
			pos.col++;
		}
		if (pass_whitespace)
			SkipSpaces();
		return true;
	}
	return false;
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

bool CParser::IsOctal() const {
	if (IsChar('0')) {
		if (pos.cursor+1 < input.GetCount())
			return IsDigit(input[pos.cursor+1]);
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
