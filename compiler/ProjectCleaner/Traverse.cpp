// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/ASTMatchers/ASTMatchers.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"


#include "ProjectCleaner.h"


using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;
using namespace Oulu;



/*
	NamedDecl - Matches a declaration of anything that could have a name.
	ValueDecl - Matches any value declaration
*/

/*#define TRAVERSER_LIST \
	 TRAVERSE(cxxCtorInitializer, CXXCtorInitializer) \
	 TRAVERSE(classTemplateDecl, ClassTemplateDecl) \
	 TRAVERSE(classTemplatePartialSpecializationDecl, ClassTemplatePartialSpecializationDecl) \
	 TRAVERSE(classTemplateSpecializationDecl, ClassTemplateSpecializationDecl) \
	 TRAVERSE(cxxConstructorDecl, CXXConstructorDecl) \
	 TRAVERSE(cxxConversionDecl, CXXConversionDecl) \
	 TRAVERSE(cxxDestructorDecl, CXXDestructorDecl) \
	 TRAVERSE(cxxMethodDecl, CXXMethodDecl) \
	 TRAVERSE(cxxRecordDecl, CXXRecordDecl) \
	 TRAVERSE(decl, Decl) \
	 TRAVERSE(declaratorDecl, DeclaratorDecl) \
	 TRAVERSE(enumConstantDecl, EnumConstantDecl) \
	 TRAVERSE(enumDecl, EnumDecl) \
	 TRAVERSE(fieldDecl, FieldDecl) \
	 TRAVERSE(friendDecl, FriendDecl) \
	 TRAVERSE(functionDecl, FunctionDecl) \
	 TRAVERSE(functionTemplateDecl, FunctionTemplateDecl) \
	 TRAVERSE(indirectFieldDecl, IndirectFieldDecl) \
	 TRAVERSE(labelDecl, LabelDecl) \
	 TRAVERSE(namedDecl, NamedDecl) \
	 TRAVERSE(namespaceAliasDecl, NamespaceAliasDecl) \
	 TRAVERSE(namespaceDecl, NamespaceDecl) \
	 TRAVERSE(nonTypeTemplateParmDecl, NonTypeTemplateParmDecl) \
	 TRAVERSE(parmVarDecl, ParmVarDecl) \
	 TRAVERSE(recordDecl, RecordDecl) \
	 TRAVERSE(tagDecl, TagDecl) \
	 TRAVERSE(templateTemplateParmDecl, TemplateTemplateParmDecl) \
	 TRAVERSE(templateTypeParmDecl, TemplateTypeParmDecl) \
	 TRAVERSE(translationUnitDecl, TranslationUnitDecl) \
	 TRAVERSE(typeAliasDecl, TypeAliasDecl) \
	 TRAVERSE(typeAliasTemplateDecl, TypeAliasTemplateDecl) \
	 TRAVERSE(typedefDecl, TypedefDecl) \
	 TRAVERSE(typedefNameDecl, TypedefNameDecl) \
	 TRAVERSE(unresolvedUsingTypenameDecl, UnresolvedUsingTypenameDecl) \
	 TRAVERSE(unresolvedUsingValueDecl, UnresolvedUsingValueDecl) \
	 TRAVERSE(usingDecl, UsingDecl) \
	 TRAVERSE(usingDirectiveDecl, UsingDirectiveDecl) \
	 TRAVERSE(valueDecl, ValueDecl) \
	 TRAVERSE(varDecl, VarDecl) \
	 TRAVERSE(nestedNameSpecifierLoc, NestedNameSpecifierLoc) \
	 TRAVERSE(nestedNameSpecifier, NestedNameSpecifier) \
	 TRAVERSE(addrLabelExpr, AddrLabelExpr) \
	 TRAVERSE(callExpr, CallExpr) \
	 TRAVERSE(cStyleCastExpr, CStyleCastExpr) \
	 TRAVERSE(cxxConstructExpr, CXXConstructExpr) \
	 TRAVERSE(cxxDependentScopeMemberExpr, CXXDependentScopeMemberExpr) \
	 TRAVERSE(cxxFunctionalCastExpr, CXXFunctionalCastExpr) \
	 TRAVERSE(cxxMemberCallExpr, CXXMemberCallExpr) \
	 TRAVERSE(memberExpr, MemberExpr) \
	 TRAVERSE(builtinType, BuiltinType) \
	 TRAVERSE(elaboratedType, ElaboratedType) \
	 TRAVERSE(enumType, EnumType)*/
	 










DeclarationMatcher NamedDecl_matcher = namedDecl().bind("NamedDecl_items");

/*DeclarationMatcher Namespace_matcher = namespaceDecl().bind("namespaces");
DeclarationMatcher NamespaceRef_matcher = namespaceDecl().bind("namespace_refs");*/

/*DeclarationMatcher Namespace_matcher = namespaceDecl().bind("namespaces");
DeclarationMatcher NamespaceRef_matcher = namespaceDecl().bind("namespace_refs");

DeclarationMatcher virtual_method_matcher = cxxMethodDecl(isVirtual()).bind("virtual methods");
DeclarationMatcher method_matcher = cxxMethodDecl().bind("methods");
//DeclarationMatcher externc_matcher = cxxMethodDecl(isExternC()).bind("extern_c");
DeclarationMatcher function_matcher = functionDecl().bind("functions");*/

String output;
bool do_dump_everything;


/*
NAMESPACE,
CLASS,
TYPEDEF,
ENUM,
STATIC_FUNCTION,
CLASS_METHOD,

NAMESPACE_REF,
CLASS_REF,
TYPEDEF_REF,
ENUM_REF,
STATIC_FUNCTION_REF,
CLASS_METHOD_REF
*/

struct NamedDeclPrinter : public MatchFinder::MatchCallback {
	Vector<CodeItem>& out;
	
	NamedDeclPrinter(Vector<CodeItem>& out) : out(out) {}
	void run(const MatchFinder::MatchResult &Result) override {
		if (const NamedDecl *p = Result.Nodes.getNodeAs<clang::NamedDecl>("NamedDecl_items")) {
			String qual_name = p->getQualifiedNameAsString().c_str();
			
			SourceLocation loc = p->getBeginLoc();
			DeclarationName name = p->getDeclName();
			
			
			if (loc.isValid()) {
				CodeItem& ci = out.Add();
				ci.file = Result.SourceManager->getFilename(loc).data();
				ci.offset = Result.SourceManager->getFileOffset(loc);
				ci.name = name.getAsString().c_str();
				ci.qual_name = qual_name;
				
				#define IS(x) (dynamic_cast<const x*>(p) != 0)
				if (IS(NamespaceDecl) || IS(NamespaceAliasDecl))
					ci.type = CodeItem::NAMESPACE;
				else if (IS(ClassTemplateDecl) || IS(ClassTemplatePartialSpecializationDecl) || IS(EnumDecl))
					ci.type = CodeItem::CLASS;
				else if (IS(TypedefDecl) || IS(TypedefNameDecl) || IS(TypeAliasDecl) || IS(TypeAliasTemplateDecl))
					ci.type = CodeItem::TYPEDEF;
				else if (IS(EnumConstantDecl))
					ci.type = CodeItem::ENUM;
				else if (IS(FunctionDecl) || IS(FunctionTemplateDecl))
					ci.type = CodeItem::STATIC_FUNCTION;
				else if (IS(CXXConstructorDecl) || IS(CXXConversionDecl) || IS(CXXDestructorDecl))
					ci.type = CodeItem::CLASS_METHOD;
				
				else if (IS(UsingDirectiveDecl))
					ci.type = CodeItem::NAMESPACE_REF;
				else if (IS(FieldDecl) || IS(ParmVarDecl) || IS(TranslationUnitDecl) || IS(UsingDecl) ||
					IS(VarDecl))
					ci.type = CodeItem::CLASS_REF;
				else if (IS(CXXConstructExpr) || IS(CXXFunctionalCastExpr) || IS(CXXMemberCallExpr))
					ci.type = CodeItem::CLASS_METHOD_REF;
				else if (IS(MemberExpr))
					ci.type = CodeItem::CLASS_FIELD_REF;
				else
					ci.type = CodeItem::UNKNOWN;
			}
			
		}
	}
};




/*struct NamespacePrinter : public MatchFinder::MatchCallback {
	Vector<CodeItem>& out;
	
	NamespacePrinter(Vector<CodeItem>& out) : out(out) {}
	void run(const MatchFinder::MatchResult &Result) override {
		if (const NamespaceDecl *p = Result.Nodes.getNodeAs<clang::NamespaceDecl>("namespaces")) {
			SourceLocation loc = p->getBeginLoc();
			DeclarationName name = p->getDeclName();
			
			
			if (loc.isValid()) {
				CodeItem& ci = out.Add();
				ci.file = Result.SourceManager->getFilename(loc).data();
				ci.offset = Result.SourceManager->getFileOffset(loc);
				ci.name = name.getAsString().c_str();
				ci.type = CodeItem::NAMESPACE;
			}
			
		}
	}
};

class FunctionPrinter : public MatchFinder::MatchCallback {
public :
	virtual void run(const MatchFinder::MatchResult &Result) {
		if (const FunctionDecl *md = Result.Nodes.getNodeAs<clang::FunctionDecl>("functions")) {
			if (md->getDeclName().isIdentifier()) {
				auto clang_name = md->getName();
				String name = ((std::string)clang_name).c_str();
				if (name.GetCount() && name[0] != '_') {
					output << "FUNCTION(" << name << ", ) {\n";
					
					
					//- unique type str (e.g. multiple to_string)
					//-
					
					
					output << "\tC("", )\n";
					output << "}\n\n";
					
				}
			}
			if (do_dump_everything)
				md->dump();
		}
	}
};


class MethodPrinter : public MatchFinder::MatchCallback {
public :
	virtual void run(const MatchFinder::MatchResult &Result) {
		if (const CXXMethodDecl *md = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("methods")) {
			if (do_dump_everything)
				md->dump();
		}
	}
};*/

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...");

int ClangToolMain(int argc, const char **argv, Vector<CodeItem>& out) {
	cl::OptionCategory cat("myname", "mydescription");
	CommonOptionsParser optionsParser(argc, argv, cat, 0);
	
	ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());
	
	MatchFinder finder;
	
	#define AddMatcher(x) \
		x##Printer x##_printer(out); \
		finder.addMatcher(x##_matcher, & x##_printer);
	
	AddMatcher(NamedDecl);
	
	/*#define AddMatcher(x) \
		x##Printer x##_printer(out); \
		finder.AddMatcher(x##_matcher, &x##_printer); \
		x##RefPrinter x##Ref_printer(out); \
		finder.AddMatcher(x##Ref_matcher, &x##Ref_printer);
	
	AddMatcher(Namespace);
	AddMatcher(Class);
	AddMatcher(Typedef);
	AddMatcher(Enum);
	AddMatcher(StaticFunction);
	AddMatcher(ClassMethod);*/
	
	//NamespacePrinter namespace_printer(out);
	//finder.addMatcher(namespace_matcher, &namespace_printer);
	
	return tool.run(&*newFrontendActionFactory(&finder));
}


NAMESPACE_OULU_BEGIN


void AddInclude(Stream& s, String file) {
	s << "#include <" << file << ">\n";
}

void CHeaders(Stream& s) {
	AddInclude(s, "ctype.h");
	AddInclude(s, "errno.h");
	AddInclude(s, "fenv.h");
	AddInclude(s, "float.h");
	AddInclude(s, "inttypes.h");
	AddInclude(s, "iso646.h");
	AddInclude(s, "limits.h");
	AddInclude(s, "locale.h");
	AddInclude(s, "math.h");
	AddInclude(s, "setjmp.h");
	AddInclude(s, "signal.h");
	AddInclude(s, "stdarg.h");
	AddInclude(s, "stdbool.h");
	AddInclude(s, "stddef.h");
	AddInclude(s, "stdint.h");
	AddInclude(s, "stdio.h");
	AddInclude(s, "stdlib.h");
	AddInclude(s, "string.h");
	AddInclude(s, "tgmath.h");
	AddInclude(s, "time.h");
	AddInclude(s, "uchar.h");
	AddInclude(s, "wchar.h");
	AddInclude(s, "wctype.h");
}

void CppHeaders(Stream& s) {
	AddInclude(s, "array");
	AddInclude(s, "deque");
	AddInclude(s, "forward_list");
	AddInclude(s, "list");
	AddInclude(s, "map");
	AddInclude(s, "queue");
	AddInclude(s, "set");
	AddInclude(s, "stack");
	AddInclude(s, "unordered_map");
	AddInclude(s, "unordered_set");
	AddInclude(s, "vector");

	AddInclude(s, "fstream");
	AddInclude(s, "iomanip");
	AddInclude(s, "ios");
	AddInclude(s, "iosfwd");
	AddInclude(s, "iostream");
	AddInclude(s, "istream");
	AddInclude(s, "ostream");
	AddInclude(s, "sstream");
	AddInclude(s, "streambuf");

	AddInclude(s, "atomic");
	AddInclude(s, "condition_variable");
	AddInclude(s, "future");
	AddInclude(s, "mutex");
	AddInclude(s, "thread");

	AddInclude(s, "algorithm");
	AddInclude(s, "bitset");
	AddInclude(s, "chrono");
	AddInclude(s, "codecvt");
	AddInclude(s, "complex");
	AddInclude(s, "exception");
	AddInclude(s, "functional");
	AddInclude(s, "initializer_list");
	AddInclude(s, "iterator");
	AddInclude(s, "limits");
	AddInclude(s, "locale");
	AddInclude(s, "memory");
	AddInclude(s, "new");
	AddInclude(s, "numeric");
	AddInclude(s, "random");
	AddInclude(s, "ratio");
	AddInclude(s, "regex");
	AddInclude(s, "stdexcept");
	AddInclude(s, "string");
	AddInclude(s, "system_error");
	AddInclude(s, "tuple");
	AddInclude(s, "typeindex");
	AddInclude(s, "typeinfo");
}

void CppImportToolCode(String code, Vector<CodeItem>& out) {
	String file = GetExeDirFile("tmp.h");
	
	DeleteFile(file);
	
	FileOut fout(file);
	
	//CHeaders(fout);
	CppHeaders(fout);
	
	fout << code;
	
	fout.Close();
	
	Cout() << "Made temp file " << file << "\n";
	
	
	Vector<String> args;
	args << GetExeFilePath();
	args << file;
	args << "--";
	args << "-x";
	args << "c++";
	
	Vector<const char*> ptrs;
	for(String& s : args)
		ptrs.Add(s.Begin());
	
	ClangToolMain(ptrs.GetCount(), ptrs.Begin(), out);
	
	//LOG(output);
}

void CppImportTool(String path, const Vector<String>& includes, const Vector<String>& defines, Vector<CodeItem>& out) {
	Vector<String> args;
	args << GetExeFilePath();
	args << path;
	args << "--";
	args << "-x";
	args << "c++";
	for (String inc : includes) {
		args << "-I";
		args << inc;
	}
	for (String def : defines)
		args << "-D" + def;
	
	if (0) {
		LOG("cd \"" << GetFileDirectory(path) << "\"");
		String s;
		for(int i = 0; i < args.GetCount(); i++) {
			if (i) s << " ";
			s << args[i];
		}
		LOG(s);
	}
	
	Vector<const char*> ptrs;
	for(String& s : args)
		ptrs.Add(s.Begin());
	
	ClangToolMain(ptrs.GetCount(), ptrs.Begin(), out);
}

void CppImportToolFork(String path, const Vector<String>& includes, const Vector<String>& defines, Vector<CodeItem>& out) {
	String file_name;
	for(int i = 0; i < 8; i++)
		file_name.Cat('a' + Random('z' - 'a' + 1));
	String file_path = ConfigFile(file_name);
	
	String cmd = "\"" + GetExeFilePath() + "\" clang \"" + file_path + "\" \"" + path + "\" -- -x c++";
	
	for (String inc : includes)
		cmd << " -I \"" << inc << "\"";
	
	for (String def : defines)
		cmd << " -D" + def;
	
	//LOG(cmd);
	
	String pipe_out;
	Sys(cmd, pipe_out);
	//LOG(pipe_out);
	
	FileIn fin(file_path);
	fin % out;
	fin.Close();
	DeleteFile(file_path);
}


NAMESPACE_OULU_END
