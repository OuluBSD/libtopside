#include "Clang.h"

NAMESPACE_TRANSLATION
	

Location::Location() {
	
}

Location::Location(CXSourceLocation sl) : sloc(sl) {
	
}

Location::Location(Unit& unit, CXFile file, int line, int column) {
	File f(file);
	*this = f.GetLocation(unit, line, column);
}

Cursor Location::GetCursor(Unit& unit) {
	return clang_getCursor(unit.unit, sloc);
}

bool Location::operator == (const Location& sloc) const {
	return clang_equalLocations(this->sloc, sloc.sloc);
}

Location Location::GetExpansion(Unit& unit) {
	CXFile file;
	unsigned line, column, offset;
	clang_getExpansionLocation(sloc, &file, &line, &column, &offset);
	return Location(unit, file, line, column);
}

File Location::GetFile() {
	CXFile file;
	unsigned line, column, offset;
	clang_getFileLocation(sloc, &file, &line, &column, &offset);
	return file;
}

void Location::GetValues(String& path, int& line_, int& column_) {
	CXFile file;
	unsigned line, column, offset;
	clang_getFileLocation(sloc, &file, &line, &column, &offset);
	File f(file);
	path = f.GetFileName();
	line_ = line;
	column_ = column; 
}


END_NAMESPACE_TRANSLATION
