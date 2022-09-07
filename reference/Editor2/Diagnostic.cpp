#include "Clang.h"

NAMESPACE_TRANSLATION
	
	
Diagnostic::Diagnostic(CXDiagnostic diag) : diag(diag) {
	
}

Diagnostic::~Diagnostic() {
	clang_disposeDiagnostic(diag);
}

DiagnosticSet Diagnostic::GetChildren() {
	return clang_getChildDiagnostics(diag);
}

String Diagnostic::GetString(unsigned options) {
	return clang_getCString(clang_formatDiagnostic(diag, options));
}

String Diagnostic::GetSpelling() {
	return clang_getCString(clang_getDiagnosticSpelling(diag));
}

String Diagnostic::GetTriggerOption() {
	return clang_getCString(clang_getDiagnosticOption(diag, 0));
}

String Diagnostic::GetCategoryText() {
	return clang_getCString(clang_getDiagnosticCategoryText(diag));
}

String Diagnostic::GetFixIt(int i) {
	return clang_getCString(clang_getDiagnosticFixIt(diag, i, 0));
}

String Diagnostic::GetFixIt(int i, Range& replacement) {
	return clang_getCString(clang_getDiagnosticFixIt(diag, i, &replacement.range));
}

int Diagnostic::GetSeverity() {
	return clang_getDiagnosticSeverity(diag);
}

int Diagnostic::GetCategoryNum() {
	return clang_getDiagnosticCategory(diag);
}

int Diagnostic::GetRangeCount() {
	return clang_getDiagnosticNumRanges(diag);
}

int Diagnostic::GetFixItCount() {
	return clang_getDiagnosticNumFixIts(diag);
}

Location Diagnostic::GetLocation() {
	return clang_getDiagnosticLocation(diag);
}

Range Diagnostic::GetRange(int i) {
	return clang_getDiagnosticRange(diag, i);
}


DiagnosticSet::DiagnosticSet(CXDiagnosticSet set) : set(set) {
	
}

DiagnosticSet::~DiagnosticSet() {
	clang_disposeDiagnosticSet(set);
}

Diagnostic DiagnosticSet::operator [] (int i) {
	return clang_getDiagnosticInSet(set, i);
}

int DiagnosticSet::GetCount() {
	return clang_getNumDiagnosticsInSet(set);
}


END_NAMESPACE_TRANSLATION
