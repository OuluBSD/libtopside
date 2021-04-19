#include "Clang.h"


NAMESPACE_TRANSLATION


unsigned GetDefaultCodeCompl() {return clang_defaultCodeCompleteOptions();}
unsigned GetAllCodeCompl() {return CXCodeComplete_IncludeMacros | CXCodeComplete_IncludeCodePatterns | CXCodeComplete_IncludeBriefComments;}


CodeCompletion::CodeCompletion(CXCodeCompleteResults* res) : res(res) {}

CodeCompletion::~CodeCompletion() {
	clang_disposeCodeCompleteResults(res);
}

void CodeCompletion::SortByName() {
	clang_sortCodeCompletionResults(res->Results, res->NumResults);
}

int CodeCompletion::GetResultCount() {
	return res->NumResults;
}

int CodeCompletion::GetApropriateResultCount() {
	return clang_codeCompleteGetContexts(res);
}


int CodeCompletion::GetDiagnosticsCount() {
	return clang_codeCompleteGetNumDiagnostics(res);
}

int CodeCompletion::GetContainerCursorKind(bool& is_incomplete) {
	unsigned u;
	int r = clang_codeCompleteGetContainerKind(res, &u);
	is_incomplete = u;
	return r;
}

Completion CodeCompletion::operator [] (int i) {
	return res->Results[i].CompletionString;
}

Completion CodeCompletion::GetResult(int i) {
	return res->Results[i].CompletionString;
}

int CodeCompletion::GetResultKind(int i) {
	return res->Results[i].CursorKind;
}

String CodeCompletion::GetUSR() {
	return clang_getCString(clang_codeCompleteGetContainerUSR(res));
}

Diagnostic CodeCompletion::GetDiagnostic(int i) {
	return clang_codeCompleteGetDiagnostic(res, i);
}

END_NAMESPACE_TRANSLATION
