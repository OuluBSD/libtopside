// Vire: Humanistic programming language for the curious.


FileInput: EOF | FileLineSeq EOF;
FileLineSeq: FileLineSeq FileLine | FileLine;
FileLine: EmptyStmt | IncludeStmt | CategorySuiteStmt | PkgSuiteStmt | NamespaceSuiteStmt | ClassSuiteStmt | AtStmt | FeatSuiteStmt;

IncludeStmt: "Include" IncludePath END_STMT;
IncludePath: IncludeRelPath | IncludeIncludePath;
IncludeRelPath: STRING;
IncludeIncludePath: "<" SyspathSeq ">";

AtStmt: "@" AtQualifier RelPathOptVersion END_STMT;
AtQualifier: "Category" | PkgSpecifier | "Scope";

CategorySuiteStmt: "Category" RelPath ":" CategorySuite;
PkgSuiteStmt: PkgSpecifier RelPath ":" PkgSuite;
NamespaceSuiteStmt: "Scope" RelPathOptVersion ":" NamespaceSuite;
ClassSuiteStmt: "Class" RelPathOptVersion ":" ClassSuite;
VersionSuiteStmt: "Ver" VersionId ":" VersionSuite;
DepSuiteStmt: DepSpecifier ":" DepSuite;
FeatSuiteStmt: "Feat" RelPath FeatSuiteOpt;
KeyValueStmt: IDENTIFIER ":" Value END_STMT;
PassStmt: "Pass" END_STMT;
EmptyStmt: END_STMT;

CategorySuite: SmallCategoryStmtSeq | TK_INDENT ScopeCategorySuiteStmt TK_DEDENT END_STMT | TK_INDENT PassStmt TK_DEDENT END_STMT;
ScopeCategorySuiteStmt: SmallCategoryStmtSeq | ScopeCategorySuiteStmt SmallCategoryStmtSeq;
SmallCategoryStmtSeq: SmallCategoryStmt | SmallCategoryStmtSeq ";" SmallCategoryStmt;
SmallCategoryStmt: EmptyStmt | CategorySuiteStmt | PkgSuiteStmt | VersionSuiteStmt | DepSuiteStmt | KeyValueStmt;

PkgSuite: SmallPkgStmtSeq | TK_INDENT ScopePkgSuiteStmt TK_DEDENT END_STMT | TK_INDENT PassStmt TK_DEDENT END_STMT;
ScopePkgSuiteStmt: SmallPkgStmtSeq | ScopePkgSuiteStmt SmallPkgStmtSeq;
SmallPkgStmtSeq: SmallPkgStmt | SmallPkgStmtSeq ";" SmallPkgStmt;
SmallPkgStmt: EmptyStmt | VersionSuiteStmt | DepSuiteStmt | KeyValueStmt | NamespaceSuiteStmt | FeatSuiteStmt;

VersionSuite: SmallVersionStmtSeq | TK_INDENT ScopeVersionSuiteStmt TK_DEDENT END_STMT | TK_INDENT PassStmt TK_DEDENT END_STMT;
ScopeVersionSuiteStmt: SmallVersionStmtSeq | ScopeVersionSuiteStmt SmallVersionStmtSeq;
SmallVersionStmtSeq: SmallVersionStmt | SmallVersionStmtSeq ";" SmallVersionStmt;
SmallVersionStmt: EmptyStmt | DepSuiteStmt | KeyValueStmt | NamespaceSuiteStmt | FeatSuiteStmt;

NamespaceSuite: SmallNamespaceStmtSeq | TK_INDENT ScopeNamespaceSuiteStmt TK_DEDENT END_STMT | TK_INDENT PassStmt TK_DEDENT END_STMT;
ScopeNamespaceSuiteStmt: SmallNamespaceStmtSeq | ScopeNamespaceSuiteStmt SmallNamespaceStmtSeq;
SmallNamespaceStmtSeq: SmallNamespaceStmt | SmallNamespaceStmtSeq ";" SmallNamespaceStmt;
SmallNamespaceStmt: EmptyStmt | DepSuiteStmt | KeyValueStmt | NamespaceSuiteStmt | ClassSuiteStmt | FeatSuiteStmt;

ClassSuite: SmallClassStmtSeq | TK_INDENT ScopeClassSuiteStmt TK_DEDENT END_STMT | TK_INDENT PassStmt TK_DEDENT END_STMT;
ScopeClassSuiteStmt: SmallClassStmtSeq | ScopeClassSuiteStmt SmallClassStmtSeq;
SmallClassStmtSeq: SmallClassStmt | SmallClassStmtSeq ";" SmallClassStmt;
SmallClassStmt: EmptyStmt | DepSuiteStmt | KeyValueStmt | ClassSuiteStmt | FeatSuiteStmt;

DepSuite: SmallDepSeqStmt | TK_INDENT ScopeDepSuiteStmt TK_DEDENT END_STMT | TK_INDENT PassStmt TK_DEDENT END_STMT;
ScopeDepSuiteStmt: SmallDepSeqStmt | ScopeDepSuiteStmt SmallDepSeqStmt;
SmallDepSeqStmt: SmallDepSeq END_STMT;
SmallDepSeq: SmallDep | SmallDepSeq "," SmallDep;
SmallDep: RelPathOptVersion;

FeatSuiteOpt: END_STMT | ":" FeatSuite;
FeatSuite: SmallFeatStmtSeq | TK_INDENT ScopeFeatSuiteStmt TK_DEDENT END_STMT | TK_INDENT PassStmt TK_DEDENT END_STMT;
ScopeFeatSuiteStmt: SmallFeatStmtSeq | ScopeFeatSuiteStmt SmallFeatStmtSeq;
SmallFeatStmtSeq: SmallFeatStmt | SmallFeatStmtSeq ";" SmallFeatStmt;
SmallFeatStmt: DepSuiteStmt;

Value: IDENTIFIER | STRING | CHAR | INTEGER | DOUBLE | FLOAT;

SyspathSeq: RelPath | SyspathSeq "/" RelPath;
RelPath: PathItem | RelPath "." PathItem;

PathItem: IDENTIFIER;

RelPathOptVersion: RelPath VersionId?;
RelPathVersion: RelPath VersionId;
VersionId: VersionCmp VersionInt;
VersionCmp: GREQ | LSEQ | ASS | GREATER | LESS;
VersionInt: DOUBLE | INTEGER | VersionInt "." INTEGER;

PkgSpecifier: "Pkg" | "Lib" | "Bin" | "Share";
DepSpecifier: "Dep" DepSpecifierOpt?;
DepSpecifierOpt: "-" DepSpecifierOptKey;
DepSpecifierOptKey: "Sched" | "Impl" | "Header";

/*
IDENTIFIER: ;
STRING: ;
CHAR: ;
INTEGER: ;
DOUBLE: ;
FLOAT: ;
END_STMT: ;

ASS: ;
GREATER: ;
LESS: ;
GREQ: ;
LSEQ: ;
*/

