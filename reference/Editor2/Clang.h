#ifndef _Editor_Clang_h_
#define _Editor_Clang_h_

#include <Core/Core.h>
using namespace UPP;

/*
	Easy to use API for clang. Wraps c-api.
	TODO: 
	 - keep the wrapper, but implement functions with the real clang c++ api
	 - add the full context of classes to the cache node (all inherited classes and their methods, from DeclContext )
*/


#include <clang-c/Index.h>

/*
	http://clang.llvm.org/doxygen/group__CINDEX__LOCATIONS.html
	http://clang.llvm.org/doxygen/group__CINDEX__FILES.html
	http://clang.llvm.org/doxygen/group__CINDEX__TYPES.html
*/

#define NAMESPACE_TRANSLATION namespace Translation { using namespace Translation;
#define END_NAMESPACE_TRANSLATION }



NAMESPACE_TRANSLATION

class Location;
class Cursor;
class Unit;
class Module;
class File;
class DiagnosticSet;
class Range;
class Completion;
class Diagnostic;

unsigned GetDefaultCodeCompl();
unsigned GetAllCodeCompl();

class CodeCompletion {
	CXCodeCompleteResults* res;
	
public:
	CodeCompletion(CXCodeCompleteResults* res);
	~CodeCompletion();
	
	void SortByName();
	
	int GetResultCount();
	int GetDiagnosticsCount();
	int GetApropriateResultCount();
	int GetContainerCursorKind(bool& is_incomplete);
	
	Completion operator [] (int i);
	Completion GetResult(int i);
	int GetResultKind(int i);
	
	String GetUSR();
	
	Diagnostic GetDiagnostic(int i);
};

class Diagnostic {
	CXDiagnostic diag;

	String GetString(unsigned options);
	
public:
	Diagnostic(CXDiagnostic diag);
	~Diagnostic();
	
	DiagnosticSet GetChildren();
	
	String GetSourceLocation() {return GetString(CXDiagnostic_DisplaySourceLocation);}
	String GetColumn() {return GetString(CXDiagnostic_DisplayColumn);}
	String GetRanges() {return GetString(CXDiagnostic_DisplaySourceRanges);}
	String GetOptions() {return GetString(CXDiagnostic_DisplayOption);}
	//String GetCategoryNum() {return GetString(CXDiagnostic_DisplayCategoryId);}
	String GetCategory() {return GetString(CXDiagnostic_DisplayCategoryName);}
	
	String GetSpelling();
	String GetTriggerOption();
	String GetCategoryText();
	String GetFixIt(int i);
	String GetFixIt(int i, Translation::Range& replacement);
	
	int GetSeverity();
	int GetCategoryNum();
	int GetRangeCount();
	int GetFixItCount();
	
	Location GetLocation();
	
	Range GetRange(int i);
	
	
};

class DiagnosticSet {
	CXDiagnosticSet set;
	
public:
	DiagnosticSet(CXDiagnosticSet);
	~DiagnosticSet();
	
	Diagnostic operator [] (int i);
	
	int GetCount();
};

class Completion {
	CXCompletionString str;
public:
	Completion();
	Completion(CXCompletionString str);
	
	int GetChunkKind(int i);
	int GetChunkCount();
	int GetPriority();
	int GetAvailabilityKind();
	int GetAnnotationCount();
	
	String GetChunkText(int i);
	String GetAnnotation(int i);
	String GetCompletionParent();
	String GetBriefComment();
	
	Completion GetChunkCompletion(int i);
	
};

class Range {
	friend class Diagnostic;
	
	CXSourceRange range;
	
public:
	Range();
	Range(CXSourceRange range);
	Range(const Range& r) {range = r.range;}
	
	Location Begin();
	Location End();
};

class Location {
	friend class Location;
	CXSourceLocation sloc;
public:
	Location();
	Location(CXSourceLocation sl);
	Location(Unit& unit, CXFile file, int line, int column);
	
	bool IsSystemHeader() {return clang_Location_isInSystemHeader(sloc);}
	bool IsMainFile() {return clang_Location_isFromMainFile(sloc);} // main file of Unit
	
	Cursor GetCursor(Unit& unit);
	
	Location GetExpansion(Unit& unit);
	
	//Unit GetUnit();
	
	File GetFile();
	void GetValues(String& path, int& line, int& column);
	
	bool operator == (const Location& sloc) const;
};

class Type {
	friend class Type;
	CXType type;

public:
	Type();
	Type(CXType);
	
	int GetKind() {return type.kind;}
	
	bool IsInvalid() {return GetKind() == CXType_Invalid;}
	bool IsUnexposed() {return GetKind() == CXType_Unexposed;}
	bool IsVoid() {return GetKind() == CXType_Void;}
	bool IsBool() {return GetKind() == CXType_Bool;}
	bool IsChar_U() {return GetKind() == CXType_Char_U;}
	bool IsUChar() {return GetKind() == CXType_UChar;}
	bool IsChar16() {return GetKind() == CXType_Char16;}
	bool IsChar32() {return GetKind() == CXType_Char32;}
	bool IsUShort() {return GetKind() == CXType_UShort;}
	bool IsUInt() {return GetKind() == CXType_UInt;}
	bool IsULong() {return GetKind() == CXType_ULong;}
	bool IsULongLong() {return GetKind() == CXType_ULongLong;}
	bool IsUInt128() {return GetKind() == CXType_UInt128;}
	bool IsChar_S() {return GetKind() == CXType_Char_S;}
	bool IsSChar() {return GetKind() == CXType_SChar;}
	bool IsWChar() {return GetKind() == CXType_WChar;}
	bool IsShort() {return GetKind() == CXType_Short;}
	bool IsInt() {return GetKind() == CXType_Int;}
	bool IsLong() {return GetKind() == CXType_Long;}
	bool IsLongLong() {return GetKind() == CXType_LongLong;}
	bool IsInt128() {return GetKind() == CXType_Int128;}
	bool IsFloat() {return GetKind() == CXType_Float;}
	bool IsDouble() {return GetKind() == CXType_Double;}
	bool IsLongDouble() {return GetKind() == CXType_LongDouble;}
	bool IsNullPtr() {return GetKind() == CXType_NullPtr;}
	bool IsOverload() {return GetKind() == CXType_Overload;}
	bool IsDependent() {return GetKind() == CXType_Dependent;}
	bool IsObjCId() {return GetKind() == CXType_ObjCId;}
	bool IsObjCClass() {return GetKind() == CXType_ObjCClass;}
	bool IsObjCSel() {return GetKind() == CXType_ObjCSel;}
	bool IsFirstBuiltin() {return GetKind() == CXType_FirstBuiltin;}
	bool IsLastBuiltin() {return GetKind() == CXType_LastBuiltin;}
	bool IsComplex() {return GetKind() == CXType_Complex;}
	bool IsPointer() {return GetKind() == CXType_Pointer;}
	bool IsBlockPointer() {return GetKind() == CXType_BlockPointer;}
	bool IsLValueReference() {return GetKind() == CXType_LValueReference;}
	bool IsRValueReference() {return GetKind() == CXType_RValueReference;}
	bool IsRecord() {return GetKind() == CXType_Record;}
	bool IsEnum() {return GetKind() == CXType_Enum;}
	bool IsTypedef() {return GetKind() == CXType_Typedef;}
	bool IsObjCInterface() {return GetKind() == CXType_ObjCInterface;}
	bool IsObjCObjectPointer() {return GetKind() == CXType_ObjCObjectPointer;}
	bool IsFunctionNoProto() {return GetKind() == CXType_FunctionNoProto;}
	bool IsFunctionProto() {return GetKind() == CXType_FunctionProto;}
	bool IsConstantArray() {return GetKind() == CXType_ConstantArray;}
	bool IsVector() {return GetKind() == CXType_Vector;}
	bool IsIncompleteArray() {return GetKind() == CXType_IncompleteArray;}
	bool IsVariableArray() {return GetKind() == CXType_VariableArray;}
	bool IsDependentSizedArray() {return GetKind() == CXType_DependentSizedArray;}
	bool IsMemberPointer() {return GetKind() == CXType_MemberPointer;}
	
	bool IsIntegerKind() {return type.kind >= CXType_Bool && type.kind <= CXType_Int128;}
	bool IsFloating() {return type.kind >= CXType_Float && type.kind <= CXType_LongDouble;}
	bool IsAssignable() {return type.kind == CXType_LValueReference;}
	bool IsTemporary() {return type.kind == CXType_RValueReference;}
	
	bool IsConst();
	
	
	String GetName();
	
	int GetSize();
	int GetArraySize();
	
	
	Type GetPointeeType();
	Type GetSourceType();
	Type GetResultType();
	Type GetArrayElementType();
	Type GetTypeFromPointer();
	Type GetTemplateSpecializationType(int i);
	
	Cursor GetTypeDeclaration();
	
	bool operator == (const Type& type) const;
};

class Cursor {
	friend class Unit;
	CXCursor cursor;
	
public:
	Cursor();
	Cursor(CXCursor c);
	Cursor(const Cursor& c) {cursor = c.cursor;}
	
	unsigned GetHash() {return clang_hashCursor(cursor);}
	
	bool IsDefinition()				{return clang_isCursorDefinition(cursor);}
	bool IsFunctionImplementation()	{return IsDefinition();}
	bool IsDynamicCall()			{return clang_Cursor_isDynamicCall(cursor);}
	bool IsStaticCall()				{return !IsDynamicCall();}
	bool IsPureVirtual()			{return clang_CXXMethod_isPureVirtual(cursor);}
	bool IsStatic() 				{return clang_CXXMethod_isStatic(cursor);}
	bool IsVirtual()				{return clang_CXXMethod_isVirtual(cursor);}
	bool IsConst()					{return clang_CXXMethod_isConst(cursor);}
	
	bool IsDeclaration()			{return clang_isDeclaration(cursor.kind);}
	bool IsReference()				{return clang_isReference(cursor.kind);}
	bool IsExpression()				{return clang_isExpression(cursor.kind);}
	bool IsStatement()				{return clang_isStatement(cursor.kind);}
	bool IsAttribute()				{return clang_isAttribute(cursor.kind);}
	bool IsPreprocessingElement()	{return clang_isPreprocessing(cursor.kind);}
	
	bool IsInvalid()				{return clang_Cursor_isNull(cursor) || GetKind() == CXCursor_InvalidCode;}
	
	bool IsUnexposedDecl() {return GetKind() == CXCursor_UnexposedDecl;}
	bool IsStructDecl() {return GetKind() == CXCursor_StructDecl;}
	bool IsUnionDecl() {return GetKind() == CXCursor_UnionDecl;}
	bool IsClassDecl() {return GetKind() == CXCursor_ClassDecl;}
	bool IsEnumDecl() {return GetKind() == CXCursor_EnumDecl;}
	bool IsFieldDecl() {return GetKind() == CXCursor_FieldDecl;}
	bool IsEnumConstantDecl() {return GetKind() == CXCursor_EnumConstantDecl;}
	bool IsFunctionDecl() {return GetKind() == CXCursor_FunctionDecl;}
	bool IsVarDecl() {return GetKind() == CXCursor_VarDecl;}
	bool IsParmDecl() {return GetKind() == CXCursor_ParmDecl;}
	bool IsObjCInterfaceDecl() {return GetKind() == CXCursor_ObjCInterfaceDecl;}
	bool IsObjCCategoryDecl() {return GetKind() == CXCursor_ObjCCategoryDecl;}
	bool IsObjCProtocolDecl() {return GetKind() == CXCursor_ObjCProtocolDecl;}
	bool IsObjCPropertyDecl() {return GetKind() == CXCursor_ObjCPropertyDecl;}
	bool IsObjCIvarDecl() {return GetKind() == CXCursor_ObjCIvarDecl;}
	bool IsObjCInstanceMethodDecl() {return GetKind() == CXCursor_ObjCInstanceMethodDecl;}
	bool IsObjCClassMethodDecl() {return GetKind() == CXCursor_ObjCClassMethodDecl;}
	bool IsObjCImplementationDecl() {return GetKind() == CXCursor_ObjCImplementationDecl;}
	bool IsObjCCategoryImplDecl() {return GetKind() == CXCursor_ObjCCategoryImplDecl;}
	bool IsTypedefDecl() {return GetKind() == CXCursor_TypedefDecl;}
	bool IsCXXMethod() {return GetKind() == CXCursor_CXXMethod;}
	bool IsNamespace() {return GetKind() == CXCursor_Namespace;}
	bool IsLinkageSpec() {return GetKind() == CXCursor_LinkageSpec;}
	bool IsConstructor() {return GetKind() == CXCursor_Constructor;}
	bool IsDestructor() {return GetKind() == CXCursor_Destructor;}
	bool IsConversionFunction() {return GetKind() == CXCursor_ConversionFunction;}
	bool IsTemplateTypeParameter() {return GetKind() == CXCursor_TemplateTypeParameter;}
	bool IsNonTypeTemplateParameter() {return GetKind() == CXCursor_NonTypeTemplateParameter;}
	bool IsTemplateTemplateParameter() {return GetKind() == CXCursor_TemplateTemplateParameter;}
	bool IsFunctionTemplate() {return GetKind() == CXCursor_FunctionTemplate;}
	bool IsClassTemplate() {return GetKind() == CXCursor_ClassTemplate;}
	bool IsClassTemplatePartialSpecialization() {return GetKind() == CXCursor_ClassTemplatePartialSpecialization;}
	bool IsNamespaceAlias() {return GetKind() == CXCursor_NamespaceAlias;}
	bool IsUsingDirective() {return GetKind() == CXCursor_UsingDirective;}
	bool IsUsingDeclaration() {return GetKind() == CXCursor_UsingDeclaration;}
	bool IsTypeAliasDecl() {return GetKind() == CXCursor_TypeAliasDecl;}
	bool IsObjCSynthesizeDecl() {return GetKind() == CXCursor_ObjCSynthesizeDecl;}
	bool IsObjCDynamicDecl() {return GetKind() == CXCursor_ObjCDynamicDecl;}
	bool IsCXXAccessSpecifier() {return GetKind() == CXCursor_CXXAccessSpecifier;}
	bool IsFirstDecl() {return GetKind() == CXCursor_FirstDecl;}
	bool IsLastDecl() {return GetKind() == CXCursor_LastDecl;}
	bool IsFirstRef() {return GetKind() == CXCursor_FirstRef;}
	bool IsObjCSuperClassRef() {return GetKind() == CXCursor_ObjCSuperClassRef;}
	bool IsObjCProtocolRef() {return GetKind() == CXCursor_ObjCProtocolRef;}
	bool IsObjCClassRef() {return GetKind() == CXCursor_ObjCClassRef;}
	bool IsTypeRef() {return GetKind() == CXCursor_TypeRef;}
	bool IsCXXBaseSpecifier() {return GetKind() == CXCursor_CXXBaseSpecifier;}
	bool IsTemplateRef() {return GetKind() == CXCursor_TemplateRef;}
	bool IsNamespaceRef() {return GetKind() == CXCursor_NamespaceRef;}
	bool IsMemberRef() {return GetKind() == CXCursor_MemberRef;}
	bool IsLabelRef() {return GetKind() == CXCursor_LabelRef;}
	bool IsOverloadedDeclRef() {return GetKind() == CXCursor_OverloadedDeclRef;}
	bool IsVariableRef() {return GetKind() == CXCursor_VariableRef;}
	bool IsLastRef() {return GetKind() == CXCursor_LastRef;}
	bool IsFirstInvalid() {return GetKind() == CXCursor_FirstInvalid;}
	bool IsInvalidFile() {return GetKind() == CXCursor_InvalidFile;}
	bool IsNoDeclFound() {return GetKind() == CXCursor_NoDeclFound;}
	bool IsNotImplemented() {return GetKind() == CXCursor_NotImplemented;}
	bool IsInvalidCode() {return GetKind() == CXCursor_InvalidCode;}
	bool IsLastInvalid() {return GetKind() == CXCursor_LastInvalid;}
	bool IsFirstExpr() {return GetKind() == CXCursor_FirstExpr;}
	bool IsUnexposedExpr() {return GetKind() == CXCursor_UnexposedExpr;}
	bool IsDeclRefExpr() {return GetKind() == CXCursor_DeclRefExpr;}
	bool IsMemberRefExpr() {return GetKind() == CXCursor_MemberRefExpr;}
	bool IsCallExpr() {return GetKind() == CXCursor_CallExpr;}
	bool IsObjCMessageExpr() {return GetKind() == CXCursor_ObjCMessageExpr;}
	bool IsBlockExpr() {return GetKind() == CXCursor_BlockExpr;}
	bool IsIntegerLiteral() {return GetKind() == CXCursor_IntegerLiteral;}
	bool IsFloatingLiteral() {return GetKind() == CXCursor_FloatingLiteral;}
	bool IsImaginaryLiteral() {return GetKind() == CXCursor_ImaginaryLiteral;}
	bool IsStringLiteral() {return GetKind() == CXCursor_StringLiteral;}
	bool IsCharacterLiteral() {return GetKind() == CXCursor_CharacterLiteral;}
	bool IsParenExpr() {return GetKind() == CXCursor_ParenExpr;}
	bool IsUnaryOperator() {return GetKind() == CXCursor_UnaryOperator;}
	bool IsArraySubscriptExpr() {return GetKind() == CXCursor_ArraySubscriptExpr;}
	bool IsBinaryOperator() {return GetKind() == CXCursor_BinaryOperator;}
	bool IsCompoundAssignOperator() {return GetKind() == CXCursor_CompoundAssignOperator;}
	bool IsConditionalOperator() {return GetKind() == CXCursor_ConditionalOperator;}
	bool IsCStyleCastExpr() {return GetKind() == CXCursor_CStyleCastExpr;}
	bool IsCompoundLiteralExpr() {return GetKind() == CXCursor_CompoundLiteralExpr;}
	bool IsInitListExpr() {return GetKind() == CXCursor_InitListExpr;}
	bool IsAddrLabelExpr() {return GetKind() == CXCursor_AddrLabelExpr;}
	bool IsStmtExpr() {return GetKind() == CXCursor_StmtExpr;}
	bool IsGenericSelectionExpr() {return GetKind() == CXCursor_GenericSelectionExpr;}
	bool IsGNUNullExpr() {return GetKind() == CXCursor_GNUNullExpr;}
	bool IsCXXStaticCastExpr() {return GetKind() == CXCursor_CXXStaticCastExpr;}
	bool IsCXXDynamicCastExpr() {return GetKind() == CXCursor_CXXDynamicCastExpr;}
	bool IsCXXReinterpretCastExpr() {return GetKind() == CXCursor_CXXReinterpretCastExpr;}
	bool IsCXXConstCastExpr() {return GetKind() == CXCursor_CXXConstCastExpr;}
	bool IsCXXFunctionalCastExpr() {return GetKind() == CXCursor_CXXFunctionalCastExpr;}
	bool IsCXXTypeidExpr() {return GetKind() == CXCursor_CXXTypeidExpr;}
	bool IsCXXBoolLiteralExpr() {return GetKind() == CXCursor_CXXBoolLiteralExpr;}
	bool IsCXXNullPtrLiteralExpr() {return GetKind() == CXCursor_CXXNullPtrLiteralExpr;}
	bool IsCXXThisExpr() {return GetKind() == CXCursor_CXXThisExpr;}
	bool IsCXXThrowExpr() {return GetKind() == CXCursor_CXXThrowExpr;}
	bool IsCXXNewExpr() {return GetKind() == CXCursor_CXXNewExpr;}
	bool IsCXXDeleteExpr() {return GetKind() == CXCursor_CXXDeleteExpr;}
	bool IsUnaryExpr() {return GetKind() == CXCursor_UnaryExpr;}
	bool IsObjCStringLiteral() {return GetKind() == CXCursor_ObjCStringLiteral;}
	bool IsObjCEncodeExpr() {return GetKind() == CXCursor_ObjCEncodeExpr;}
	bool IsObjCSelectorExpr() {return GetKind() == CXCursor_ObjCSelectorExpr;}
	bool IsObjCProtocolExpr() {return GetKind() == CXCursor_ObjCProtocolExpr;}
	bool IsObjCBridgedCastExpr() {return GetKind() == CXCursor_ObjCBridgedCastExpr;}
	bool IsPackExpansionExpr() {return GetKind() == CXCursor_PackExpansionExpr;}
	bool IsSizeOfPackExpr() {return GetKind() == CXCursor_SizeOfPackExpr;}
	bool IsLambdaExpr() {return GetKind() == CXCursor_LambdaExpr;}
	bool IsObjCBoolLiteralExpr() {return GetKind() == CXCursor_ObjCBoolLiteralExpr;}
	bool IsObjCSelfExpr() {return GetKind() == CXCursor_ObjCSelfExpr;}
	bool IsLastExpr() {return GetKind() == CXCursor_LastExpr;}
	bool IsFirstStmt() {return GetKind() == CXCursor_FirstStmt;}
	bool IsUnexposedStmt() {return GetKind() == CXCursor_UnexposedStmt;}
	bool IsLabelStmt() {return GetKind() == CXCursor_LabelStmt;}
	bool IsCompoundStmt() {return GetKind() == CXCursor_CompoundStmt;}
	bool IsCaseStmt() {return GetKind() == CXCursor_CaseStmt;}
	bool IsDefaultStmt() {return GetKind() == CXCursor_DefaultStmt;}
	bool IsIfStmt() {return GetKind() == CXCursor_IfStmt;}
	bool IsSwitchStmt() {return GetKind() == CXCursor_SwitchStmt;}
	bool IsWhileStmt() {return GetKind() == CXCursor_WhileStmt;}
	bool IsDoStmt() {return GetKind() == CXCursor_DoStmt;}
	bool IsForStmt() {return GetKind() == CXCursor_ForStmt;}
	bool IsGotoStmt() {return GetKind() == CXCursor_GotoStmt;}
	bool IsIndirectGotoStmt() {return GetKind() == CXCursor_IndirectGotoStmt;}
	bool IsContinueStmt() {return GetKind() == CXCursor_ContinueStmt;}
	bool IsBreakStmt() {return GetKind() == CXCursor_BreakStmt;}
	bool IsReturnStmt() {return GetKind() == CXCursor_ReturnStmt;}
	bool IsGCCAsmStmt() {return GetKind() == CXCursor_GCCAsmStmt;}
	bool IsAsmStmt() {return GetKind() == CXCursor_AsmStmt;}
	bool IsObjCAtTryStmt() {return GetKind() == CXCursor_ObjCAtTryStmt;}
	bool IsObjCAtCatchStmt() {return GetKind() == CXCursor_ObjCAtCatchStmt;}
	bool IsObjCAtFinallyStmt() {return GetKind() == CXCursor_ObjCAtFinallyStmt;}
	bool IsObjCAtThrowStmt() {return GetKind() == CXCursor_ObjCAtThrowStmt;}
	bool IsObjCAtSynchronizedStmt() {return GetKind() == CXCursor_ObjCAtSynchronizedStmt;}
	bool IsObjCAutoreleasePoolStmt() {return GetKind() == CXCursor_ObjCAutoreleasePoolStmt;}
	bool IsObjCForCollectionStmt() {return GetKind() == CXCursor_ObjCForCollectionStmt;}
	bool IsCXXCatchStmt() {return GetKind() == CXCursor_CXXCatchStmt;}
	bool IsCXXTryStmt() {return GetKind() == CXCursor_CXXTryStmt;}
	bool IsCXXForRangeStmt() {return GetKind() == CXCursor_CXXForRangeStmt;}
	bool IsSEHTryStmt() {return GetKind() == CXCursor_SEHTryStmt;}
	bool IsSEHExceptStmt() {return GetKind() == CXCursor_SEHExceptStmt;}
	bool IsSEHFinallyStmt() {return GetKind() == CXCursor_SEHFinallyStmt;}
	bool IsMSAsmStmt() {return GetKind() == CXCursor_MSAsmStmt;}
	bool IsNullStmt() {return GetKind() == CXCursor_NullStmt;}
	bool IsDeclStmt() {return GetKind() == CXCursor_DeclStmt;}
	bool IsOMPParallelDirective() {return GetKind() == CXCursor_OMPParallelDirective;}
	bool IsOMPSimdDirective() {return GetKind() == CXCursor_OMPSimdDirective;}
	bool IsOMPForDirective() {return GetKind() == CXCursor_OMPForDirective;}
	bool IsOMPSectionsDirective() {return GetKind() == CXCursor_OMPSectionsDirective;}
	bool IsOMPSectionDirective() {return GetKind() == CXCursor_OMPSectionDirective;}
	bool IsOMPSingleDirective() {return GetKind() == CXCursor_OMPSingleDirective;}
	bool IsOMPParallelForDirective() {return GetKind() == CXCursor_OMPParallelForDirective;}
	bool IsOMPParallelSectionsDirective() {return GetKind() == CXCursor_OMPParallelSectionsDirective;}
	bool IsOMPTaskDirective() {return GetKind() == CXCursor_OMPTaskDirective;}
	bool IsOMPMasterDirective() {return GetKind() == CXCursor_OMPMasterDirective;}
	bool IsOMPCriticalDirective() {return GetKind() == CXCursor_OMPCriticalDirective;}
	bool IsOMPTaskyieldDirective() {return GetKind() == CXCursor_OMPTaskyieldDirective;}
	bool IsOMPBarrierDirective() {return GetKind() == CXCursor_OMPBarrierDirective;}
	bool IsOMPTaskwaitDirective() {return GetKind() == CXCursor_OMPTaskwaitDirective;}
	bool IsOMPFlushDirective() {return GetKind() == CXCursor_OMPFlushDirective;}
	bool IsSEHLeaveStmt() {return GetKind() == CXCursor_SEHLeaveStmt;}
	bool IsOMPOrderedDirective() {return GetKind() == CXCursor_OMPOrderedDirective;}
	bool IsOMPAtomicDirective() {return GetKind() == CXCursor_OMPAtomicDirective;}
	bool IsOMPForSimdDirective() {return GetKind() == CXCursor_OMPForSimdDirective;}
	bool IsOMPParallelForSimdDirective() {return GetKind() == CXCursor_OMPParallelForSimdDirective;}
	bool IsOMPTargetDirective() {return GetKind() == CXCursor_OMPTargetDirective;}
	bool IsOMPTeamsDirective() {return GetKind() == CXCursor_OMPTeamsDirective;}
	bool IsLastStmt() {return GetKind() == CXCursor_LastStmt;}
	bool IsTranslationUnit() {return GetKind() == CXCursor_TranslationUnit;}
	bool IsFirstAttr() {return GetKind() == CXCursor_FirstAttr;}
	bool IsUnexposedAttr() {return GetKind() == CXCursor_UnexposedAttr;}
	bool IsIBActionAttr() {return GetKind() == CXCursor_IBActionAttr;}
	bool IsIBOutletAttr() {return GetKind() == CXCursor_IBOutletAttr;}
	bool IsIBOutletCollectionAttr() {return GetKind() == CXCursor_IBOutletCollectionAttr;}
	bool IsCXXFinalAttr() {return GetKind() == CXCursor_CXXFinalAttr;}
	bool IsCXXOverrideAttr() {return GetKind() == CXCursor_CXXOverrideAttr;}
	bool IsAnnotateAttr() {return GetKind() == CXCursor_AnnotateAttr;}
	bool IsAsmLabelAttr() {return GetKind() == CXCursor_AsmLabelAttr;}
	bool IsPackedAttr() {return GetKind() == CXCursor_PackedAttr;}
	bool IsPureAttr() {return GetKind() == CXCursor_PureAttr;}
	bool IsConstAttr() {return GetKind() == CXCursor_ConstAttr;}
	bool IsNoDuplicateAttr() {return GetKind() == CXCursor_NoDuplicateAttr;}
	bool IsCUDAConstantAttr() {return GetKind() == CXCursor_CUDAConstantAttr;}
	bool IsCUDADeviceAttr() {return GetKind() == CXCursor_CUDADeviceAttr;}
	bool IsCUDAGlobalAttr() {return GetKind() == CXCursor_CUDAGlobalAttr;}
	bool IsCUDAHostAttr() {return GetKind() == CXCursor_CUDAHostAttr;}
	bool IsCUDASharedAttr() {return GetKind() == CXCursor_CUDASharedAttr;}
	bool IsLastAttr() {return GetKind() == CXCursor_LastAttr;}
	bool IsPreprocessingDirective() {return GetKind() == CXCursor_PreprocessingDirective;}
	bool IsMacroDefinition() {return GetKind() == CXCursor_MacroDefinition;}
	bool IsMacroExpansion() {return GetKind() == CXCursor_MacroExpansion;}
	bool IsMacroInstantiation() {return GetKind() == CXCursor_MacroInstantiation;}
	bool IsInclusionDirective() {return GetKind() == CXCursor_InclusionDirective;}
	bool IsFirstPreprocessing() {return GetKind() == CXCursor_FirstPreprocessing;}
	bool IsLastPreprocessing() {return GetKind() == CXCursor_LastPreprocessing;}
	bool IsModuleImportDecl() {return GetKind() == CXCursor_ModuleImportDecl;}
	bool IsFirstExtraDecl() {return GetKind() == CXCursor_FirstExtraDecl;}
	bool IsLastExtraDecl() {return GetKind() == CXCursor_LastExtraDecl;}


	//TODO: the full list
	
	String GetScope();
	String GetName();
	String GetDisplayName();
	String GetComment();
	String GetBriefComment();
	String GetMangledName();
	String GetTreeString(int indent = 0);
	
	Completion GetCompletion();
	
	Type GetType();
	Type GetResultType();
	Type GetArgumentType(int i);
	Type GetTemplateArgumentType(int i);
	Type GetSourceTemplateType();
	
	Cursor GetReferenced();
	Cursor GetDefinition();
	Cursor GetSourceTemplate();
	Cursor GetSemanticParent();
	Cursor GetLexicalParent();
	Cursor GetSubMatch(int line, int column);
	Cursor FindName(const String& name);
	
	Module GetModule();
	
	File GetIncludedFile();
	
	bool HasIn(int line, int column);
	
	int GetArgumentCount();
	int GetTemplateArgumentCount();
	int GetStorageClass();
	int GetKind();
	int GetCount();
	int GetCppAccessSpecifier();
	
	Cursor operator [] (int i);
	
	bool IsStorageInvalid()			{return GetStorageClass() == CX_SC_Invalid;}
	bool IsStorageNone()			{return GetStorageClass() == CX_SC_None;}
	bool IsStorageExtern()			{return GetStorageClass() == CX_SC_Extern;}
	bool IsStorageStatic()			{return GetStorageClass() == CX_SC_Static;}
	bool IsStoragePrivateExtern()	{return GetStorageClass() == CX_SC_PrivateExtern;}
	bool IsStorageOpenCL_WG()		{return GetStorageClass() == CX_SC_OpenCLWorkGroupLocal;}
	bool IsStorageAuto()			{return GetStorageClass() == CX_SC_Auto;}
	bool IsStorageRegister()		{return GetStorageClass() == CX_SC_Register;}
	
	Cursor GetArgument(int i);
	int64 GetTemplateArgumentValue(int i);
	
	Location GetLocation();
	Range GetRange();
	
	bool operator == (Cursor& cur);
	
	Array<Cursor> GetClasses();
	Array<Cursor> GetFunctions();
	Array<Cursor> GetNamespaces();
	Array<Cursor> GetCursors(String path);
};

class Module {
	friend class Project;
	CXModule module;
public:
	Module();
	Module(CXModule module);
	
	bool IsSystemModule() {return clang_Module_isSystem(module);}
	
	Module GetParent();
	
	File GetFile();
	//Unit GetUnit();
	
	String GetName();
	String GetFullName();
	
	int GetTopLevelHeaderCount(Unit& unit);
	File GetTopLevelHeader(Unit& unit, int i);
	
	bool IsInvalid() {return module == 0;}
	
	bool operator == (Module& mod) {return (long)mod.module == (long)module;} // TODO: not stable, if working at all
	
};

class File {
	friend class File;
	friend class Unit;
	friend class Project;
	
	CXFile file;
public:
	File();
	File(CXFile);
	
	String GetFileName();
	time_t GetModificationTime();
	int GetId();
	bool IsIncludeOnce(Unit& unit);
	
	Location GetLocation(Unit& storage_unit, int line, int column);
	Cursor GetCursor(Unit& storage_unit, int line, int column);
	
	bool operator == (const File& file) const;
	
	bool IsInvalid() {return file == 0;}
};

class Unit {
	friend class File;
	friend class Location;
	friend class Module;
	friend class Project;
	
	CXTranslationUnit unit;
	CXCursor rootCursor;
	bool loaded;
	
	String path;
public:
	Unit();
	~Unit();
	
	void Refresh(CXIndex index, const Vector<String>& folders);
	void Create(CXIndex index, const Vector<String>& folders);
	void Clear();
	
	Unit& SetPath(String s) {path = s; return *this;}
	const String& GetPath() {return path;}
	
	Location GetLocation(const String& path, int line, int column);
	Cursor GetCursor(const String& path, int line, int column);
	Cursor GetCursor(int line, int column);
	Cursor GetRootCursor() {return rootCursor;}
	
	File GetFile(const String& path);
	Module GetModule(File& file);
	
	Array<Range> GetSkippedByPreprocessor(File& file);
	Array<Range> GetReferences(File& search_file, File& cursor_file, int line, int column);
	Array<Range> GetIncludes(File& search_file);
	
	Array<File> GetIncludedFiles(File& search_file);
	Array<File> GetIncludedFilesDeep();
	bool IsDeepIncluded(const String& search_file);
	
	DiagnosticSet GetDiagnostics();
	
	ArrayMap<uint32, Cursor> GetCodeCompletion(const String& path, int line, int column, const String& current_content);
	
	Array<Cursor> GetClasses(String path);
	Array<Cursor> GetFunctions(String path);
	Array<Cursor> GetInclusionDirectives();
	Array<Cursor> GetNamespaces(String path);
};

class Project {
	CXIndex index;
	
	ArrayMap<String, Unit> units;
	
public:
	Project();
	~Project();
	
	void Clear();
	
	
	Cursor GetCursor(const String& path, int line, int column);
	
	Unit& AddUnit(String path, const Vector<String>& top_folders);
	int FindUnit(String path);
	void RemoveUnit(String path);
	
	//Project& LoadFromBuilder(const ::Project& prj);
	
	Unit& GetUnit(const String& path);
	Module GetModule(const String& path);
	Location GetLocation(const String& path, int line, int column);
	
	Array<Cursor> GetRootCursors(const String& path);
	
};

END_NAMESPACE_TRANSLATION


#endif
