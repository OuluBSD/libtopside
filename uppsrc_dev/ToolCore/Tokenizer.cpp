#include "ToolCore.h"


BEGIN_TEXTLIB_NAMESPACE


NaturalTokenizer::NaturalTokenizer() {
	
}

bool NaturalTokenizer::Parse(const String& txt) {
	Clear();
	Vector<WString> line;
	
	ws = txt.ToWString();
	
	line.SetCount(0);
	WString tmp;
	
	for(int i = 0; i < ws.GetCount(); i++) {
		int chr = ws[i];
		
		if (chr != L"ä"[0] && chr != L"Ä"[0] &&
			chr != L"ö"[0] && chr != L"Ö"[0]) {
			has_foreign = has_foreign ||
				(chr >= 0x100 && chr < 0x700) || // п, ب
				chr >= 0xc000 ||
				(chr >= 0xc0 && chr < 0x100) || // éá
				0;
			}
		
		if (IsSpace(chr) || chr == 0x2005) {
			if (!tmp.IsEmpty()) {
				line << tmp;
				tmp.Clear();
			}
			if (chr == '\n')
				Swap(line, lines.Add());
		}
		else if (IsToken(chr)) {
			if (!tmp.IsEmpty()) {
				line << tmp;
				tmp.Clear();
			}
			tmp.Cat(chr);
			line << tmp;
			tmp.Clear();
		}
		else {
			tmp.Cat(chr);
		}
	}
	if (!tmp.IsEmpty()) {
		line << tmp;
		tmp.Clear();
	}
	if (line.GetCount()) {
		Swap(lines.Add(), line);
	}
	
	return true;
}

bool NaturalTokenizer::IsToken(int chr) {
	const char* c = "!\"#¤\%&/()=?@£$€{[]}\\+`*^~,.;:-_<>|´"; // skip '
	for (const char* cmp = c; *cmp; cmp++)
		if (*cmp == chr)
			return true;
	/*if (chr == 0x2014) return true;
	if (chr == 0x2026) return true;
	if (chr == 0x2019) return true;
	if (chr == 0x200a) return true;
	if (chr == 0x205f) return true;*/
	if (chr >= 0x2000 && chr < 0x3000) return true;
	if (chr >= 0xe000 && chr < 0xf000) return true;
	return false;
}


END_TEXTLIB_NAMESPACE
