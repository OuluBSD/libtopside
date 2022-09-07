#include "Clang.h"

NAMESPACE_TRANSLATION
	
File::File() {
	
}

File::File(CXFile f) : file(f) {
	
}

String File::GetFileName() {
	return clang_getCString(clang_getFileName(file));
}

time_t File::GetModificationTime() {
	return clang_getFileTime(file);
}

int File::GetId() {
	// CINDEX_LINKAGE int 	clang_getFileUniqueID (CXFile file, CXFileUniqueID *outID)
	//return clang_getFileUniqueID 
	TODO
	return 0;
}

bool File::IsIncludeOnce(Unit& unit) {
	return clang_isFileMultipleIncludeGuarded(unit.unit, file);
}

Location File::GetLocation(Unit& storage_unit, int line, int column) {
	return clang_getLocation(storage_unit.unit, file, line, column);
}

Cursor File::GetCursor(Unit& storage_unit, int line, int column) {
	return GetLocation(storage_unit, line, column).GetCursor(storage_unit);
}

bool File::operator == (const File& file) const {
	return clang_File_isEqual(this->file, file.file);
}


END_NAMESPACE_TRANSLATION
