#include "Draw.h"
#include <Local/Local.h>

NAMESPACE_UPP

bool Font::operator==(const Font& fnt) const {
	TODO
}

void Font::Face(int i) {
	TODO
}

void Font::Height(int i) {
	TODO
}

void Font::Italic(bool b) {
	TODO
}

void Font::Bold(bool b) {
	TODO
}

void Font::Strikeout(bool b) {
	TODO
}

void Font::Underline(bool b) {
	TODO
}

int Font::GetAscent() const {
	TODO
}

int Font::GetDescent() const {
	TODO
}

int Font::GetHeight() const {
	TODO
}

int Font::GetFaceCount() {
	TODO
}

String Font::GetFaceName(int i) {
	TODO
}






int __std_font_sz = 15;
Font __std_font;

Size GetStdFontSize() {
	Size sz(__std_font_sz, __std_font_sz);
	return sz;
}

Font GetStdFont(int size) {
	size = size < 0 ? GetStdFontSize().cy : size;
	if (__std_font.IsEmpty()) {
		__std_font = Font(Font::LoadFont(TS::ShareDirFile("fonts"), "Roboto-Regular.ttf", size));
	}
	return __std_font;
}

void SetStdFont(Font fnt) {
	__std_font = fnt;
}

Size GetSysFontTextSize(const SysFont& fnt, const String& s);

Size GetTextSize(String s, Font fnt) {
	if (fnt.IsEmpty())
		return Size(0,0);
	return GetSysFontTextSize(*fnt.GetSysFont(), s);
}

Size GetTextSize(WString s, Font fnt) {
	return GetTextSize(s.ToString(), fnt);
}

Font Arial(int size) {
	return Font::LoadFont(TS::ShareDirFile("fonts"), "Roboto-Regular.ttf", size);
}

Font Monospace(int size) {
	return Font::LoadFont(TS::ShareDirFile("fonts"), "Inconsolata-Regular.ttf", size);
}

Font Serif(int size) {
	return Font::LoadFont(TS::ShareDirFile("fonts"), "PlayfairDisplay-Regular.ttf", size);
}

Font SansSerif(int size) {
	return Font::LoadFont(TS::ShareDirFile("fonts"), "LiberationSans-Regular.ttf", size);
}

Font StdFont(int size) {
	return SansSerif(size);
}



END_UPP_NAMESPACE
