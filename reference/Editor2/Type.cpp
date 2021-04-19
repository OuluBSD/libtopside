#include "Clang.h"

NAMESPACE_TRANSLATION


Type::Type() {
	
}

Type::Type(CXType t) : type(t) {
	
}


bool Type::IsConst() {
	return clang_isConstQualifiedType(type);
}
	

int Type::GetSize() {
	return clang_Type_getSizeOf(type);
}

int Type::GetArraySize() {
	return clang_getArraySize(type);
}



	

String Type::GetName() {
	return clang_getCString(clang_getTypeSpelling(type));
}


Type Type::GetPointeeType() {
	return clang_getPointeeType(type);
}

Type Type::GetSourceType() {
	return clang_getCanonicalType(type);
}

Type Type::GetResultType() {
	//ASSERT(IsFunction()); // or method
	return clang_getResultType(type);
}

Type Type::GetArrayElementType() {
	//ASSERT(IsArray());
	return clang_getArrayElementType(type);
}

Type Type::GetTypeFromPointer() {
	return clang_Type_getClassType(type);
}

Type Type::GetTemplateSpecializationType(int i) {
	return clang_Type_getTemplateArgumentAsType(type, i);
}

Cursor Type::GetTypeDeclaration() {
	return clang_getTypeDeclaration(type);
}


bool Type::operator == (const Type& type) const {
	return clang_equalTypes(type.type, this->type);
}

END_NAMESPACE_TRANSLATION
