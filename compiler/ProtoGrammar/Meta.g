"Name":            "Meta-vire-backend Grammar";
"Version":         "1 (December 2020)";
"Author":          "Seppo Pakonen";
"About":           "This language is what is used for meta-paradigm processing after language frontend stage";

"Start Symbol":    "FileInput";
"Comment Start":   "/*";
"Comment End":     "*/";
"Comment Line":    "//";


{IdHead}:          {Letter} + [_];
{IdTail}:          {IdHead} + {Digit};


<Identifier>:      {IdHead}{IdTail}*;


// BEGIN RULES


FileInput: Eof | FileLineSeq Eof;
FileLineSeq: FileLineSeq FileLine | FileLine;
FileLine: ExprStmt;

ExprStmt: CallWithArgs | Call;

Call: FunctionWithoutParams;
CallWithArgs: 'b' FunctionWithParams ArgSeq 'e';

ArgSeq: ArgSeq Arg | Arg;
Arg: 'a' ArgQual? ArgSpec ArgQualOp?;
ArgSpec: ArgExprLeft | ArgExprRight | ArgClsId | CallWithArgs | Call | StrLit | ChrLit | IdLit | ArgId;

FunctionWithoutParams: FnCdParent;
FunctionWithParams: FnExpr | FnAddCd | FnExprStmt | FnAddAttr;

FnCdParent: 'cdp';
FnExpr: 'ex';
FnAddCd: 'acd' DirType;
DirType: 'cls';
FnExprStmt: 'est';
FnAddAttr: 'ata';

ArgExprLeft: 'left';
ArgExprRight: 'right';

ArgClsId: ArgClsIdRule | ArgClsIdSimple;
ArgClsIdSimple: 'clsid';
ArgClsIdRule: 'clsid' 'rule';

ArgQual: ArgQualKey | ArgQualValue | ArgQualOp;
ArgQualKey: 'key';
ArgQualValue: 'value';
ArgQualOp: 'op' Identifier;

ArgId: 'id' Identifier;

StrLit: 'str_lit';
ChrLit: 'char_lit';
IdLit: 'id_lit';


/* BEGIN BOOTSTRAP EXTRA

eof: EOF;
identifier: IDENTIFIER;
char_list: CHARLIST;
char_literal: CHAR;
string_literal: STRING;

CHAR: ;
STRING: ;
IDENTIFIER: ;
CHARLIST: ;

*/
