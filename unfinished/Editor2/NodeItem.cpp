#include "NodeItem.h"


ClangItem::ClangItem() {
	type = CI_NULL;
	int_data = 0;
	kind = 0;
}

String ClangItem::GetKindString() const {
	if (kind == 0) return "";
	if (kind == 1) return "UnexposedDecl";
	if (kind == 2) return "StructDecl";
	if (kind == 3) return "UnionDecl";
	if (kind == 4) return "ClassDecl";
	if (kind == 5) return "EnumDecl";
	if (kind == 6) return "FieldDecl";
	if (kind == 7) return "EnumConstantDecl";
	if (kind == 8) return "FunctionDecl";
	if (kind == 9) return "VarDecl";
	if (kind == 10) return "ParmDecl";
	if (kind == 11) return "ObjCInterfaceDecl";
	if (kind == 12) return "ObjCCategoryDecl";
	if (kind == 13) return "ObjCProtocolDecl";
	if (kind == 14) return "ObjCPropertyDecl";
	if (kind == 15) return "ObjCIvarDecl";
	if (kind == 16) return "ObjCInstanceMethodDecl";
	if (kind == 17) return "ObjCClassMethodDecl";
	if (kind == 18) return "ObjCImplementationDecl";
	if (kind == 19) return "ObjCCategoryImplDecl";
	if (kind == 20) return "TypedefDecl";
	if (kind == 21) return "CXXMethod";
	if (kind == 22) return "Namespace";
	if (kind == 23) return "LinkageSpec";
	if (kind == 24) return "Constructor";
	if (kind == 25) return "Destructor";
	if (kind == 26) return "ConversionFunction";
	if (kind == 27) return "TemplateTypeParameter";
	if (kind == 28) return "NonTypeTemplateParameter";
	if (kind == 29) return "TemplateTemplateParameter";
	if (kind == 30) return "FunctionTemplate";
	if (kind == 31) return "ClassTemplate";
	if (kind == 32) return "ClassTemplatePartialSpecialization";
	if (kind == 33) return "NamespaceAlias";
	if (kind == 34) return "UsingDirective";
	if (kind == 35) return "UsingDeclaration";
	if (kind == 36) return "TypeAliasDecl";
	if (kind == 37) return "ObjCSynthesizeDecl";
	if (kind == 38) return "ObjCDynamicDecl";
	if (kind == 39) return "CXXAccessSpecifier";
	if (kind == 40) return "ObjCSuperClassRef";
	if (kind == 41) return "ObjCProtocolRef";
	if (kind == 42) return "ObjCClassRef";
	if (kind == 43) return "TypeRef";
	if (kind == 44) return "CXXBaseSpecifier";
	if (kind == 45) return "TemplateRef";
	if (kind == 46) return "NamespaceRef";
	if (kind == 47) return "MemberRef";
	if (kind == 48) return "LabelRef";
	if (kind == 49) return "OverloadedDeclRef";
	if (kind == 50) return "VariableRef";
	if (kind == 70) return "FirstInvalid";
	if (kind == 70) return "InvalidFile";
	if (kind == 71) return "NoDeclFound";
	if (kind == 72) return "NotImplemented";
	if (kind == 73) return "InvalidCode";
	if (kind == 100) return "FirstExpr";
	if (kind == 100) return "UnexposedExpr";
	if (kind == 101) return "DeclRefExpr";
	if (kind == 102) return "MemberRefExpr";
	if (kind == 103) return "CallExpr";
	if (kind == 104) return "ObjCMessageExpr";
	if (kind == 105) return "BlockExpr";
	if (kind == 106) return "IntegerLiteral";
	if (kind == 107) return "FloatingLiteral";
	if (kind == 108) return "ImaginaryLiteral";
	if (kind == 109) return "StringLiteral";
	if (kind == 110) return "CharacterLiteral";
	if (kind == 111) return "ParenExpr";
	if (kind == 112) return "UnaryOperator";
	if (kind == 113) return "ArraySubscriptExpr";
	if (kind == 114) return "BinaryOperator";
	if (kind == 115) return "CompoundAssignOperator";
	if (kind == 116) return "ConditionalOperator";
	if (kind == 117) return "CStyleCastExpr";
	if (kind == 118) return "CompoundLiteralExpr";
	if (kind == 119) return "InitListExpr";
	if (kind == 120) return "AddrLabelExpr";
	if (kind == 121) return "StmtExpr";
	if (kind == 122) return "GenericSelectionExpr";
	if (kind == 123) return "GNUNullExpr";
	if (kind == 124) return "CXXStaticCastExpr";
	if (kind == 125) return "CXXDynamicCastExpr";
	if (kind == 126) return "CXXReinterpretCastExpr";
	if (kind == 127) return "CXXConstCastExpr";
	if (kind == 128) return "CXXFunctionalCastExpr";
	if (kind == 129) return "CXXTypeidExpr";
	if (kind == 130) return "CXXBoolLiteralExpr";
	if (kind == 131) return "CXXNullPtrLiteralExpr";
	if (kind == 132) return "CXXThisExpr";
	if (kind == 133) return "CXXThrowExpr";
	if (kind == 134) return "CXXNewExpr";
	if (kind == 135) return "CXXDeleteExpr";
	if (kind == 136) return "UnaryExpr";
	if (kind == 137) return "ObjCStringLiteral";
	if (kind == 138) return "ObjCEncodeExpr";
	if (kind == 139) return "ObjCSelectorExpr";
	if (kind == 140) return "ObjCProtocolExpr";
	if (kind == 141) return "ObjCBridgedCastExpr";
	if (kind == 142) return "PackExpansionExpr";
	if (kind == 143) return "SizeOfPackExpr";
	if (kind == 144) return "LambdaExpr";
	if (kind == 145) return "ObjCBoolLiteralExpr";
	if (kind == 146) return "ObjCSelfExpr";
	if (kind == 147) return "OMPArraySectionExpr";
	if (kind == 200) return "FirstStmt";
	if (kind == 200) return "UnexposedStmt";
	if (kind == 201) return "LabelStmt";
	if (kind == 202) return "CompoundStmt";
	if (kind == 203) return "CaseStmt";
	if (kind == 204) return "DefaultStmt";
	if (kind == 205) return "IfStmt";
	if (kind == 206) return "SwitchStmt";
	if (kind == 207) return "WhileStmt";
	if (kind == 208) return "DoStmt";
	if (kind == 209) return "ForStmt";
	if (kind == 210) return "GotoStmt";
	if (kind == 211) return "IndirectGotoStmt";
	if (kind == 212) return "ContinueStmt";
	if (kind == 213) return "BreakStmt";
	if (kind == 214) return "ReturnStmt";
	if (kind == 215) return "GCCAsmStmt";
	if (kind == 216) return "ObjCAtTryStmt";
	if (kind == 217) return "ObjCAtCatchStmt";
	if (kind == 218) return "ObjCAtFinallyStmt";
	if (kind == 219) return "ObjCAtThrowStmt";
	if (kind == 220) return "ObjCAtSynchronizedStmt";
	if (kind == 221) return "ObjCAutoreleasePoolStmt";
	if (kind == 222) return "ObjCForCollectionStmt";
	if (kind == 223) return "CXXCatchStmt";
	if (kind == 224) return "CXXTryStmt";
	if (kind == 225) return "CXXForRangeStmt";
	if (kind == 226) return "SEHTryStmt";
	if (kind == 227) return "SEHExceptStmt";
	if (kind == 228) return "SEHFinallyStmt";
	if (kind == 229) return "MSAsmStmt";
	if (kind == 230) return "NullStmt";
	if (kind == 231) return "DeclStmt";
	if (kind == 232) return "OMPParallelDirective";
	if (kind == 233) return "OMPSimdDirective";
	if (kind == 234) return "OMPForDirective";
	if (kind == 235) return "OMPSectionsDirective";
	if (kind == 236) return "OMPSectionDirective";
	if (kind == 237) return "OMPSingleDirective";
	if (kind == 238) return "OMPParallelForDirective";
	if (kind == 239) return "OMPParallelSectionsDirective";
	if (kind == 240) return "OMPTaskDirective";
	if (kind == 241) return "OMPMasterDirective";
	if (kind == 242) return "OMPCriticalDirective";
	if (kind == 243) return "OMPTaskyieldDirective";
	if (kind == 244) return "OMPBarrierDirective";
	if (kind == 245) return "OMPTaskwaitDirective";
	if (kind == 246) return "OMPFlushDirective";
	if (kind == 247) return "SEHLeaveStmt";
	if (kind == 248) return "OMPOrderedDirective";
	if (kind == 249) return "OMPAtomicDirective";
	if (kind == 250) return "OMPForSimdDirective";
	if (kind == 251) return "OMPParallelForSimdDirective";
	if (kind == 252) return "OMPTargetDirective";
	if (kind == 253) return "OMPTeamsDirective";
	if (kind == 254) return "OMPTaskgroupDirective";
	if (kind == 255) return "OMPCancellationPointDirective";
	if (kind == 256) return "OMPCancelDirective";
	if (kind == 257) return "OMPTargetDataDirective";
	if (kind == 258) return "OMPTaskLoopDirective";
	if (kind == 259) return "OMPTaskLoopSimdDirective";
	if (kind == 260) return "OMPDistributeDirective";
	if (kind == 300) return "TranslationUnit";
	if (kind == 400) return "FirstAttr";
	if (kind == 400) return "UnexposedAttr";
	if (kind == 401) return "IBActionAttr";
	if (kind == 402) return "IBOutletAttr";
	if (kind == 403) return "IBOutletCollectionAttr";
	if (kind == 404) return "CXXFinalAttr";
	if (kind == 405) return "CXXOverrideAttr";
	if (kind == 406) return "AnnotateAttr";
	if (kind == 407) return "AsmLabelAttr";
	if (kind == 408) return "PackedAttr";
	if (kind == 409) return "PureAttr";
	if (kind == 410) return "ConstAttr";
	if (kind == 411) return "NoDuplicateAttr";
	if (kind == 412) return "CUDAConstantAttr";
	if (kind == 413) return "CUDADeviceAttr";
	if (kind == 414) return "CUDAGlobalAttr";
	if (kind == 415) return "CUDAHostAttr";
	if (kind == 416) return "CUDASharedAttr";
	if (kind == 417) return "VisibilityAttr";
	if (kind == 418) return "DLLExport";
	if (kind == 419) return "DLLImport";
	if (kind == 500) return "PreprocessingDirective";
	if (kind == 501) return "MacroDefinition";
	if (kind == 502) return "MacroExpansion";
	if (kind == 503) return "InclusionDirective";
	if (kind == 600) return "ModuleImportDecl";
	if (kind == 601) return "TypeAliasTemplateDecl";
	if (kind == 700) return "OverloadCandidate";
	return "";
}

String ClangItem::GetTypeString() const {
	if (type == CI_NULL) return "null";
	if (type == CI_FILE) return "file";
	if (type == CI_AST) return "ast";
	if (type == CI_PKG) return "package";
	if (type == CI_PRJMGR) return "project-manager";
	return "unknown";
}


ClangNode& NodeGetAdd(ClangNode& inner, String name) {
	for(int i = 0; i < inner.GetCount(); i++) {
		ClangNode& sub = inner[i];
		if (sub.GetKey() == name)
			return sub;
	}
	ClangNode& sub = inner.Add();
	sub.SetKey(name);
	return sub;
}

void ToString(ClangNode& node, int indent, String& s) {
	for(int i = 0; i < indent; i++) s.Cat(' ');
	s += Format("key=\"%s\" data=\"%s\" int=%d kind=%d (%s) type=%d (%s), sub-node=%d", node.key, node.data, node.int_data, node.kind, node.GetKindString(), node.type, node.GetTypeString(), node.GetCount());
	s.Cat('\n');
	for(int i = 0; i < node.GetCount(); i++) {
		ToString(node[i], indent+1, s);
	}
}
String Dump(ClangNode& node) {
	String s;
	ToString(node, 0, s);
	return s;
}


