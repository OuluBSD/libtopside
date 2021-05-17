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

Font Font::LoadFont(String dir, String name, int ptsize, int weight, bool italic) {
	String path = AppendFileName(dir, name);
	switch (weight) {
		case 0:	path += "-Thin";	break;
		case 1:	path += "-Regular";	break;
		case 2:	path += "-Medium";	break;
		case 3:	path += "-Bold";	break;
	}
	path += ".ttf";
	
	if (!FileExists(path)) {
		return Font();
	}
	
	FontRef* ref = new FontRef();
	
	DLOG("Opening font " << path);
	ref->font.raw = LoadSysFont(path, ptsize);
	ref->dir = dir;
	ref->name = name;
	ref->ptsize = ptsize;
	ref->weight = weight;
	ref->italic = italic;
	
	if (ref->font.IsEmpty()) {
		#if HAVE_SDL2
		DLOG("Opening font failed: " << TTF_GetError());
		#else
		DLOG("Opening font failed");
		#endif
	}
	return ref;
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
		__std_font = Font(Font::LoadFont(Topside::ShareDirFile("fonts"), "Roboto", size));
	}
	return __std_font;
}

void SetStdFont(Font fnt) {
	__std_font = fnt;
}

Size GetTextSize(String s, Font fnt) {
	if (fnt.IsEmpty())
		return Size(0,0);
	return GetSysFontTextSize(fnt.GetSysFont()->GetRaw(), s);
}

Size GetTextSize(WString s, Font fnt) {
	return GetTextSize(s.ToString(), fnt);
}

Font Arial(int size) {
	TODO
}

Font Monospace(int size) {
	TODO
}

Font Serif(int size) {
	TODO
}

Font SansSerif(int size) {
	TODO
}




END_UPP_NAMESPACE
