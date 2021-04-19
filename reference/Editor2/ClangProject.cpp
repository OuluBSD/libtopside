#include "Clang.h"


NAMESPACE_TRANSLATION


Project::Project() {
	index = clang_createIndex(true, true);
}

Project::~Project() {
	clang_disposeIndex(index);
}

void Project::Clear() {
	units.Clear();
	clang_disposeIndex(index);
	index = clang_createIndex(true, true);
}

Unit& Project::AddUnit(String path, const Vector<String>& top_folders) {
	ASSERT(path.GetCount());
	Unit& u = units.Add(path).SetPath(path);
	u.Refresh(index, top_folders);
	return u;
}

int Project::FindUnit(String path) {
	for(int i = 0; i < units.GetCount(); i++) {
		Unit& u = units[i];
		if (u.GetPath() == path)
			return i;
	}
	return -1;
}

void Project::RemoveUnit(String path) {
	for(int i = 0; i < units.GetCount(); i++) {
		Unit& u = units[i];
		if (u.GetPath() == path) {
			u.Clear();
			units.Remove(i);
			i--;
		}
	}
}

/*Project& Project::LoadFromBuilder(const ::Project& prj) {
	Clear();
	
	int c1 = prj.GetFolderCount();
	for(int i = 0; i < c1; i++) {
		int c2 = prj.GetFileCount(i);
		for(int j = 0; j < c2; j++) {
			String path = prj.GetFilePath(i, j);
			String ext = GetFileExt(path);
			if (ext != ".cpp" && ext != ".S" && ext != ".c")
				continue;
			Unit& unit = AddFile(path, prj.GetTopFolders());
		}
	}
	return *this;
}*/

Unit& Project::GetUnit(const String& path) {
	String ext = GetFileExt(path);
	if (ext == ".c" || ext == ".cpp" || ext == ".S") {
		for(int i = 0; i < units.GetCount(); i++) {
			if (units[i].GetPath() == path) {
				return units[i];
			}
		}
	}
	else if (ext == ".h") {
		for(int i = 0; i < units.GetCount(); i++) {
			if (units[i].IsDeepIncluded(path)) {
				return units[i];
			}
		}
	}
	ASSERT(units.GetCount());
	units[0].GetFile(path);
	return units[0];
	//Panic("Path translation unit not found: " + path);
}

Cursor Project::GetCursor(const String& path, int line, int column) {
	String ext = GetFileExt(path);
	if (ext == ".c" || ext == ".cpp" || ext == ".S") {
		for(int i = 0; i < units.GetCount(); i++) {
			if (units[i].GetPath() == path) {
				return units[i].GetCursor(line, column);
			}
		}
	}
	else if (ext == ".h") {
		for(int i = 0; i < units.GetCount(); i++) {
			if (units[i].IsDeepIncluded(path)) {
				return units[i].GetCursor(path, line, column);
			}
		}
	}
	//Panic("Path translation unit not found: " + path);
	return clang_getNullCursor();
}

Module Project::GetModule(const String& path) {
	Unit& u = GetUnit(path);
	File f = u.GetFile(path);
	return clang_getModuleForFile(u.unit, f.file);
}

Location Project::GetLocation(const String& path, int line, int column) {
	Unit& u = GetUnit(path);
	File f = u.GetFile(path);
	return clang_getLocation(u.unit, f.file, line, column);
}

Array<Cursor> tmp;
String tmp_path;

enum CXChildVisitResult root_visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {
	Cursor cur(cursor);
	if (cur.GetLocation().GetFile().GetFileName() == tmp_path) {
		tmp.Add(Cursor(cursor));
		if (cur.IsNamespace())
			return CXChildVisit_Recurse;
		else
			return CXChildVisit_Continue;
	} else {
		return CXChildVisit_Recurse;
	}
}

Array<Cursor> Project::GetRootCursors(const String& path) {
	Unit& u = GetUnit(path);
	tmp_path = path;
	tmp.Clear();
	clang_visitChildren(u.rootCursor, &root_visitor, 0);
	
	Array<Cursor> out;
	out <<= tmp;
	return out;
}


END_NAMESPACE_TRANSLATION
