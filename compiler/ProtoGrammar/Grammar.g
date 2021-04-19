"Name":            "Vire Grammar Grammar";
"Version":         "1 (December 2020)";
"Author":          "Seppo Pakonen";
"About":           "Vire is a new programming and planning language, which combines the best of C++ and python";

"Start Symbol":    "FileInput";
"Comment Start":   "/*";
"Comment End":     "*/";
"Comment Line":    "//";


{HexDigit}:        {Digit} + [abcdefABCDEF];
{OctDigit}:        [01234567];

{IdHead}:          {Letter} + [_];
{IdTail}:          {IdHead} + {Digit};

{StringCh}:        {Printable} - {QuotationMark};
{CharCh}:          {Printable} - {Apostrophe};
{CharListCh}:      {Printable} - {RightSquareBracket};


<DecLiteral>:      [123456789]{digit}*;
<OctLiteral>:      "0" {OctDigit}*;
<HexLiteral>:      "0x" {HexDigit}+;
<FloatLiteral>:    {Digit}*'.'{Digit}+;

<StringLiteral>:   '"' <StringContent>* '"';
<CharLiteral>:     {Apostrophe} <CharContent> {Apostrophe};
<StringContent>:   {StringCh} | '\\'{Printable};
<CharContent>:     {CharCh} | '\\'{Printable};

<Identifier>:      {IdHead}{IdTail}*;
<CharList>:        '[' CharListCh* ']';
<Eof>:				{EndOfFile};



// BEGIN RULES


FileInput: Eof | FileLineSeq Eof;
FileLineSeq: FileLineSeq FileLine | FileLine;
FileLine: EmptyStmt | KeyValueStmt | CharRuleStmt | TokenRuleStmt | RuleExprStmt;

EmptyStmt: ';';
KeyValueStmt: (>b ata) (>a key)StringLiteral ':' (>a value) StringLiteral ';'(>e);

CharRuleStmt: (>b acd cls)CharRuleId(>e) ':' (>b est) CharRuleBlock ';'(>e)(>cdp);
CharRuleBlock: (>a b ex) CharRuleBlock CharRuleOp CharRuleElement (>e) | CharRuleElement;
CharRuleOp: (>a op add)'+' | (>a op sub)'-';
CharRuleElement: (>a b ex) CharRuleId (>e) | (>a b ex) (>a char_list)CharList (>e);

TokenRuleStmt: (>b acd cls)TokenRuleId(>e) ':' (>b est) TokenRuleExpr ';'(>e)(>cdp);
TokenRuleExpr: (>a b ex) TokenRuleExpr '|' TokenRuleBlock (>e) | TokenRuleBlock;
TokenRuleBlock: (>a b ex) TokenRuleBlock TokenRuleElement (>e) | TokenRuleElement;
TokenRuleElement: (>a)ElementCharRule | (>a)ElementTokenRule | (>a)CharListElement | (>a)CharElement | (>a)StringElement | (>a)IdElement;

RuleExprStmt: (>b acd cls) RuleId(>e) ':' (>b est) RuleExpr ';'(>e)(>cdp);
RuleExpr: (>a b ex) RuleExpr "|" BlockExpr (>e) | BlockExpr;
BlockExpr: (>a b ex) BlockExpr ElementExpr (>e) | ElementExpr;
ElementExpr: (>a)PreExpr | (>a)PostExpr | (>a b ex)Element ElementPostQualifier?(>e);

PreExpr:  (>b ex) '(' (>a op less)'<' IdSeq ')' (>e);
PostExpr: (>b ex) '(' (>a op grtr)'>' IdSeq ')' (>e);
IdSeq: IdSeq (>a id_lit)Identifier | (>a id_lit)Identifier;

ElementCharRule:  (>b ex) CharRuleId                TokenElementPostQualifier? (>e);
ElementTokenRule: (>b ex) TokenRuleId               TokenElementPostQualifier? (>e);
CharListElement:  (>b ex) (>a char_list)CharList    TokenElementPostQualifier? (>e);
CharElement:      (>b ex) (>a char_lit)CharLiteral  TokenElementPostQualifier? (>e);
StringElement:    (>b ex) (>a str_lit)StringLiteral TokenElementPostQualifier? (>e);
IdElement:        (>b ex) (>a id)Identifier         TokenElementPostQualifier? (>e);

CharRuleId:  (>a id char_rule)  '{' (>a id_lit)Identifier '}';
TokenRuleId: (>a id token_rule) '<' (>a id_lit)Identifier '>';
RuleId: (>a id rule) (>a id_lit) Identifier;

TokenElementPostQualifier: (>a op any)'*' | (>a op pos)'+' | (>a v opt)'?';
ElementPostQualifier: (>op opt)"?";
Element: (>a char_lit)CharLiteral | (>a str_lit)StringLiteral | RuleId;



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
