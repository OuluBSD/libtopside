#include "Clang.h"


NAMESPACE_TRANSLATION

Cursor::Cursor() {
	cursor = clang_getNullCursor();
}

Cursor::Cursor(CXCursor c) : cursor(c) {
	
}


String Cursor::GetScope() {
	CXSourceRange range = clang_getCursorExtent(cursor);
    CXSourceLocation begin = clang_getRangeStart(range);
    CXSourceLocation end = clang_getRangeEnd(range);
    CXFile cxFile;
    unsigned int beginOff;
    unsigned int endOff;
    clang_getExpansionLocation(begin, &cxFile, 0, 0, &beginOff);
    clang_getExpansionLocation(end, 0, 0, 0, &endOff);
    CXString filename = clang_getFileName(cxFile);
    unsigned int textSize = endOff - beginOff;

 	FileIn in(clang_getCString(filename));
 	if (!in.IsOpen()) return "";
 	
 	in.Seek(beginOff);
 	return in.Get(textSize);
}

String Cursor::GetName() {
	return GetType().GetName();
}

String Cursor::GetDisplayName() {
	return clang_getCString(clang_getCursorDisplayName(cursor));
}

String Cursor::GetComment() {
	//ASSERT(IsDeclaration());
	return clang_getCString(clang_Cursor_getRawCommentText(cursor));
}

String Cursor::GetBriefComment() {
	//ASSERT(IsDeclaration());
	return clang_getCString(clang_Cursor_getBriefCommentText(cursor));
}

String Cursor::GetMangledName() {
	return clang_getCString(clang_Cursor_getMangling(cursor));
}

String Cursor::GetTreeString(int indent) {
	String out;
	for(int i = 0; i < indent; i++) {
		out << " ";
	}
	Type t = GetType();
	out << "|-" << GetKind() << ", " << GetName() << ", " << GetType().GetResultType().GetName() << ", " << GetDisplayName() <<  "\n";
	int c1 = GetCount();
	for(int i = 0; i < c1; i++) {
		Cursor c = (*this)[i];
		out << c.GetTreeString(indent+1);
	}
	c1 = GetArgumentCount();
	for(int i = 0; i < c1; i++) {
		Cursor c = GetArgument(i);
		String s = c.GetTreeString(indent+2);
		if (i == 0 && s.GetCount()) {
			for(int i = 0; i < indent+1; i++) {
				out << " ";
			}
			out << "|-Args\n";
		}
		out << s;
	}
	return out;
}

Completion Cursor::GetCompletion() {
	return clang_getCursorCompletionString(cursor);
}


Type Cursor::GetType() {
	return clang_getCursorType(cursor);
}

Type Cursor::GetResultType() {
	return clang_getCursorResultType(cursor);
}
	
Type Cursor::GetArgumentType(int i)  {
	return GetArgument(i).GetType();
}

Type Cursor::GetTemplateArgumentType(int i) {
	return clang_Cursor_getTemplateArgumentType(cursor, i);
}

Type Cursor::GetSourceTemplateType() {
	return GetSourceTemplate().GetType();
}




Cursor Cursor::GetReferenced() {
	return clang_getCursorReferenced(cursor);
}

Cursor Cursor::GetDefinition() {
	return clang_getCursorDefinition(cursor);
}

Cursor Cursor::GetSourceTemplate() {
	return clang_getSpecializedCursorTemplate(cursor);
}

Cursor Cursor::GetSemanticParent() {
	return clang_getCursorSemanticParent(cursor);
}

Cursor Cursor::GetLexicalParent() {
	return clang_getCursorLexicalParent(cursor);
}
	
// Useless
bool Cursor::HasIn(int line, int column) {
	Range range = GetRange();
	String s;
	int l0, c0, l1, c1;
	range.Begin().GetValues(s, l0, c0);
	range.End().GetValues(s, l1, c1);
	
	if (line == l0) 
		return c0 <= column;
	else if (line == l1)
		return c1 > column;
	else
		return line < l1 && line > l0;
}


bool __match_found;

// Useless
Cursor Cursor::GetSubMatch(int line, int column) {
	int c1 = GetCount();
	__match_found = false;
	for(int i = 0; i < c1; i++) {
		Cursor c = (*this)[i];
		if (c.HasIn(line, column)) {
			__match_found = true;
			return c;
		} else {
			Cursor x = c.GetSubMatch(line, column);
			if (__match_found)
				return x;
		}
	}
	return *this;
}

Cursor Cursor::FindName(const String& name) {
	int c1 = GetCount();
	__match_found = false;
	for(int i = 0; i < c1; i++) {
		Cursor c = (*this)[i];
		if (c.GetDisplayName() == name) {
			__match_found = true;
			return c;
		} else {
			Cursor x = c.FindName(name);
			if (__match_found)
				return x;
		}
	}
	c1 = GetArgumentCount();
	for(int i = 0; i < c1; i++) {
		Cursor c = GetArgument(i);
		if (c.GetDisplayName() == name) {
			__match_found = true;
			return c;
		} else {
			Cursor x = c.FindName(name);
			if (__match_found)
				return x;
		}
	}
	return *this;
}

Module Cursor::GetModule() {
	return clang_Cursor_getModule(cursor);
}


File Cursor::GetIncludedFile() {
	return clang_getIncludedFile(cursor);
}


int Cursor::GetArgumentCount() {
	return clang_Cursor_getNumArguments(cursor);
}

int Cursor::GetTemplateArgumentCount() {
	return clang_Cursor_getNumTemplateArguments(cursor);
}

int Cursor::GetStorageClass() {
	return clang_Cursor_getStorageClass(cursor);
}

int Cursor::GetKind() {
	return clang_getCursorKind(cursor);
}


int __cursor_get_count;

enum CXChildVisitResult root_visitor__cursor_get_count(CXCursor cursor, CXCursor parent, CXClientData client_data) {
	__cursor_get_count++;
	return CXChildVisit_Continue;
}

int Cursor::GetCount() {
	__cursor_get_count = 0;
	clang_visitChildren(cursor, &root_visitor__cursor_get_count, 0);
	return __cursor_get_count;
}

int Cursor::GetCppAccessSpecifier() {
	return clang_getCXXAccessSpecifier(cursor);
}

Cursor Cursor::GetArgument(int i) {
	return clang_Cursor_getArgument(cursor, i);
}

CXCursor __cursor_at;
int __cursor_at_num;

enum CXChildVisitResult root_visitor__cursor_at(CXCursor cursor, CXCursor parent, CXClientData client_data) {
	if (__cursor_at_num == __cursor_get_count) {
		__cursor_at = cursor;
		return CXChildVisit_Break;
	} else {
		__cursor_get_count++;
		return CXChildVisit_Continue;
	}
}
Cursor Cursor::operator [] (int i) {
	__cursor_get_count = 0;
	__cursor_at_num = i;
	__cursor_at = cursor;
	clang_visitChildren(cursor, &root_visitor__cursor_at, 0);
	return __cursor_at;
}


int64 Cursor::GetTemplateArgumentValue(int i) {
	return clang_Cursor_getTemplateArgumentValue(cursor, i);
}

Location Cursor::GetLocation() {
	return clang_getCursorLocation(cursor);
}

Range Cursor::GetRange() {
	return clang_getCursorExtent(cursor);
}



bool Cursor::operator == (Cursor& cur) {
	return clang_equalCursors(cursor, cur.cursor);
}



Array<Cursor> Cursor::GetClasses() {
	Array<Cursor> out;
	int c1 = GetCount();
	for(int i = 0; i < c1; i++) {
		Cursor c = (*this)[i];
		if (c.IsClassDecl() || c.IsClassTemplate() || c.IsStructDecl())
			out.Add(c);
	}
	return out;
}

Array<Cursor> Cursor::GetFunctions() {
	Array<Cursor> out;
	int c1 = GetCount();
	for(int i = 0; i < c1; i++) {
		Cursor c = (*this)[i];
		if (c.IsFunctionDecl() || c.IsFunctionTemplate())
			out.Add(c);
	}
	return out;
}

Array<Cursor> Cursor::GetNamespaces() {
	Array<Cursor> out;
	int c1 = GetCount();
	for(int i = 0; i < c1; i++) {
		Cursor c = (*this)[i];
		if (c.IsNamespace())
			out.Add(c);
	}
	return out;
}

Array<Cursor> Cursor::GetCursors(String path) {
	Array<Cursor> out;
	int c1 = GetCount();
	bool adding = false;
	for(int i = 0; i < c1; i++) {
		Cursor c = (*this)[i];
		//if (c.GetLocation().GetFile().GetFileName() == path)
		//	out.Add(c);
		//if (!adding && c.GetLocation().GetFile().GetFileName() == path) adding = true;
		//if (adding) 
		out.Add(c);
	}
	return out;
}
	
END_NAMESPACE_TRANSLATION

