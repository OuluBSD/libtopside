#include "Clang.h"

NAMESPACE_TRANSLATION
	
unsigned DefaultCompletionSettings() {return clang_defaultCodeCompleteOptions();}

Completion::Completion() {
	
}

Completion::Completion(CXCompletionString str) : str(str) {
	
}

int Completion::GetChunkKind(int i) {
	return clang_getCompletionChunkKind(str, i);
}

int Completion::GetChunkCount() {
	return clang_getNumCompletionChunks(str);
}

int Completion::GetPriority() {
	return clang_getCompletionPriority(str);
}

int Completion::GetAvailabilityKind() {
	return clang_getCompletionAvailability(str);
}

int Completion::GetAnnotationCount() {
	return clang_getCompletionNumAnnotations(str);
}

String Completion::GetChunkText(int i) {
	return clang_getCString(clang_getCompletionChunkText(str, i));
}

String Completion::GetAnnotation(int i) {
	return clang_getCString(clang_getCompletionAnnotation(str, i));
}

String Completion::GetCompletionParent() {
	return clang_getCString(clang_getCompletionParent(str, 0));
}

String Completion::GetBriefComment() {
	return clang_getCString(clang_getCompletionBriefComment(str));
}

Completion Completion::GetChunkCompletion(int i) {
	return clang_getCompletionChunkCompletionString(str, i);
}

END_NAMESPACE_TRANSLATION
