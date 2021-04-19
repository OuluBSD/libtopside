#include "Clang.h"


NAMESPACE_TRANSLATION
	

Unit::Unit() {
	loaded = false;
}

Unit::~Unit() {
	Clear();
}

void Unit::Clear() {
	if (loaded) {
		clang_disposeTranslationUnit(unit);
		loaded = false;
	}
}

void Unit::Refresh(CXIndex index, const Vector<String>& folders) {
	if (!loaded) Create(index, folders);
	else {
		clang_reparseTranslationUnit(unit, 0,0,0);
		rootCursor = clang_getTranslationUnitCursor(unit);
	}
}

CXChildVisitResult printVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {

    CXSourceRange range = clang_getCursorExtent(cursor);
    CXSourceLocation startLocation = clang_getRangeStart(range);
    CXSourceLocation endLocation = clang_getRangeEnd(range);

    CXFile file;
    unsigned int line, column, offset;
    clang_getInstantiationLocation(startLocation, &file, &line, &column, &offset);
    LOG(Format("Start: Line: %d Column: %d Offset: %d", (int)line, (int)column, (int)offset));
    clang_getInstantiationLocation(endLocation, &file, &line, &column, &offset);
    LOG(Format("End: Line: %d Column: %d Offset: %d", (int)line, (int)column, (int)offset));

    return CXChildVisit_Recurse;
}

void Unit::Create(CXIndex index, const Vector<String>& folders) {
	Clear();
	
	const char* argv[128];
	int argc = 0;
	
	Array<String> args;
	for(int i = 0; i < folders.GetCount(); i++) {
		String& arg = args.Add("-I" + folders[i]);
		argv[argc] = arg.Begin();
		argc++;
	}
	
	
	unit = clang_createTranslationUnitFromSourceFile (
		index,					// CIdx
		path.Begin(),			// source_filename
		argc,					// num_command_line_args
		argv,					// command_line_args
		0,						// unsave_files
		0						// num_unsaved_files
	);
	
	loaded = true;
	
	rootCursor = clang_getTranslationUnitCursor(unit);

	//clang_visitChildren(rootCursor, printVisitor, NULL);

}

Location Unit::GetLocation(const String& path, int line, int column) {
	return GetFile(path).GetLocation(*this, line, column);
}

Cursor Unit::GetCursor(int line, int column) {
	return GetFile(path).GetCursor(*this, line, column);
}

Cursor Unit::GetCursor(const String& path, int line, int column) {
	return GetFile(path).GetCursor(*this, line, column);
}

File Unit::GetFile(const String& path) {
	return clang_getFile(unit, path.Begin());
}

Module Unit::GetModule(File& file) {
	return clang_getModuleForFile(unit, file.file);
}


Array<Range> Unit::GetSkippedByPreprocessor(File& file) {
	CXSourceRangeList *list, *cur;
	list = clang_getSkippedRanges(unit, file.file);
	Array<Range> out;
	for(int i = 0; i < list->count; i++) {
		out.Add(Range(list->ranges[i]));
	}
	clang_disposeSourceRangeList(list);
	return out;
}

Array<Range> tmp_out;
enum CXVisitorResult visit_cb(void *context, CXCursor, CXSourceRange rng) {
	tmp_out.Add(Range(rng));
	return CXVisit_Continue;
}

Array<Range> Unit::GetReferences(File& search_file, File& cursor_file, int line, int column) {
	tmp_out.Clear();
	
	Cursor cur = cursor_file.GetCursor(*this, line, column);
	
	CXCursorAndRangeVisitor visitor;
	visitor.visit = &visit_cb; 
	clang_findReferencesInFile(cur.cursor, search_file.file, visitor);
	
	Array<Range> out;
	out <<= tmp_out;
	return out;
}

Array<Range> Unit::GetIncludes(File& search_file) {
	tmp_out.Clear();
	
	CXCursorAndRangeVisitor visitor;
	visitor.visit = &visit_cb; 
	clang_findIncludesInFile(unit, search_file.file, visitor);
	
	Array<Range> out;
	out <<= tmp_out;
	return out;
}

DiagnosticSet Unit::GetDiagnostics() {
	return clang_getDiagnosticSetFromTU(unit);
}

/*CodeCompletion Unit::GetCodeCompletion(int line, int column, const String& current_content) {
	CXUnsavedFile current;
	current.Filename = path.Begin();
	current.Contents = current_content.Begin();
	current.Length = current_content.GetLength();
	return clang_codeCompleteAt(unit, path.Begin(), line, column, &current, 1, 0xFFFFFFFF);//GetAllCodeCompl());
}*/



ArrayMap<uint32, Cursor> tmp_codecompl;
Cursor break_cur;
enum CXChildVisitResult root_visitor2(CXCursor cursor, CXCursor parent, CXClientData client_data) {
	Cursor cur(cursor);
	unsigned hash = cur.GetHash();
	if (tmp_codecompl.Find(hash) == -1)
		tmp_codecompl.Add(hash, cur);
	if (cur == break_cur)
		return CXChildVisit_Break;
	if (cur.IsCompoundStmt() || cur.IsClassDecl() || cur.IsNamespace() || cur.IsStructDecl() || 
		cur.IsUnionDecl() || cur.IsEnumConstantDecl() || cur.IsTypedefDecl() || cur.IsDeclStmt() || cur.IsVarDecl()) {
		return CXChildVisit_Recurse;
	} else {
		return CXChildVisit_Continue;
	}
}


	
ArrayMap<uint32, Cursor> Unit::GetCodeCompletion(const String& path, int line, int column, const String& current_content) {
	tmp_codecompl.Clear();
	
	Cursor current = GetCursor(path, line, column);
	
	int kind = current.GetKind();
	
	Cursor parent = current.GetSemanticParent();
	//LOG(parent.GetTreeString());
	
	bool skip_first_parent = false;
	if (current.IsCompoundStmt()) {
		skip_first_parent = true;
		/*current = parent;
		if (current.IsConstructor() || current.IsDestructor() || current.IsCXXMethod() || current.IsFunctionDecl()) {
			int c1 = current.GetCount();
			if (c1) {
				current = current[c1-1];
				c1 = current.GetCount();
				if (c1) {
					current = current[0];
				}
			}
		}*/
	}
	
	LOG(current.GetTreeString());
	Cursor cur0 = current;
	if (skip_first_parent)
		parent = cur0; // TODO: now actually visits all children
	else
		parent = current.GetLexicalParent();
	while (1) {
		if (parent.IsInvalid())
			break;
		
		break_cur = cur0;
		clang_visitChildren(parent.cursor, &root_visitor2, 0);
		
		cur0 = parent;
		parent = cur0.GetLexicalParent();
	}
	
	cur0 = current;
	//parent = cur0;
	parent = cur0.GetSemanticParent();
	while (1) {
		if (parent.IsInvalid()) 
			break;
		
		break_cur = cur0;
		clang_visitChildren(parent.cursor, &root_visitor2, 0);
		
		cur0 = parent;
		parent = cur0.GetSemanticParent();
	}
	
	ArrayMap<uint32, Cursor> out;
	out <<= tmp_codecompl;
	return out;
}

Array<File> Unit::GetIncludedFiles(File& search_file) {
	Array<Range> ranges = GetIncludes(search_file);
	Array<File> out;
	for(int i = 0; i < ranges.GetCount(); i++) {
		Cursor cur = ranges[i].Begin().GetCursor(*this);
		out.Add(cur.GetIncludedFile());
	}
	return out;
}

Array<File> Unit::GetIncludedFilesDeep() {
	Array<File>	out, queue;
	queue.Add(GetFile(path));
	while (queue.GetCount()) {
		Array<File>	files = GetIncludedFiles(queue[0]);
		queue.Remove(0);
		for(int i = 0; i < files.GetCount(); i++) {
			bool found = false;
			for(int j = 0; j < out.GetCount(); j++) {
				if (out[j] == files[i]) {
					found = true;
					break;
				}
			}
			if (found) continue;
			out.Add(files[i]);
			queue.Add(files[i]);
		}
	}
	return out;
}

bool Unit::IsDeepIncluded(const String& search_file) {
	Array<File>	files = GetIncludedFilesDeep();
	for(int i = 0; i < files.GetCount(); i++) {
		if (files[i].GetFileName() == search_file)
			return true;
	}
	return false;
	/*Module m = GetModule(search_file);
	return m.IsInvalid();*/
}


Array<Cursor> Unit::GetClasses(String path) {
	bool check_path = path != "";
	Array<Cursor> out;
	Cursor root(rootCursor);
	int c1 = root.GetCount();
	
	for(int i = 0; i < c1; i++) {
		Cursor c = root[i];
		if (check_path && c.GetLocation().GetFile().GetFileName() != path)
			continue;
		if (c.IsClassDecl() || c.IsClassTemplate() || c.IsStructDecl())
			out.Add(c);
	}
	
	return out;
}

Array<Cursor> Unit::GetFunctions(String path) {
	bool check_path = path != "";
	Array<Cursor> out;
	Cursor root(rootCursor);
	int c1 = root.GetCount();
	
	for(int i = 0; i < c1; i++) {
		Cursor c = root[i];
		if (check_path && c.GetLocation().GetFile().GetFileName() != path)
			continue;
		if (c.IsFunctionDecl() || c.IsFunctionTemplate())
			out.Add(c);
	}
	
	return out;
}

Array<Cursor> Unit::GetInclusionDirectives() {
	Array<Cursor> out;
	Cursor root(rootCursor);
	int c1 = root.GetCount();
	
	for(int i = 0; i < c1; i++) {
		Cursor c = root[i];
		if (c.IsInclusionDirective())
			out.Add(c);
	}
	
	return out;
}

Array<Cursor> Unit::GetNamespaces(String path) {
	bool check_path = path != "";
	Array<Cursor> out;
	Cursor root(rootCursor);
	int c1 = root.GetCount();
	
	for(int i = 0; i < c1; i++) {
		Cursor c = root[i];
		if (check_path && c.GetLocation().GetFile().GetFileName() != path)
			continue;
		if (c.IsNamespace())
			out.Add(c);
	}
	
	return out;
}

END_NAMESPACE_TRANSLATION

