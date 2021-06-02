// Generated at 12/21/2020 07:40:50
#include "Grammar.h"
namespace TS::Grammar {
bool Parser::FileInput() {
	RET(FILE_INPUT)
	SAVE;
	BLOCK_BEGIN(0);
	TEST_DISCARDSAVED(Eof, ACT_INVALID)
	BLOCK_BEGIN(1);
	while (true) {
		TEST_PART(FileLineSeq);
		TEST_PART(Eof);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::FileLineSeq() {
	RET(FILE_LINE_SEQ)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(FileLineSeqFirst);}
		else {TEST_PART(FileLineSeqSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::FileLineSeqFirst() {
	RET(FILE_LINE_SEQ_ITEM)
	BLOCK_BEGIN(1);
	TEST(FileLine, ACT_INVALID)
	return false;
}

bool Parser::FileLineSeqSecond() {
	RET(FILE_LINE_SEQ_ITEM)
	BLOCK_BEGIN(0);
	TEST(FileLine, ACT_INVALID)
	return false;
}

bool Parser::FileLine() {
	RET(FILE_LINE)
	BLOCK_BEGIN(0);
	TEST(EmptyStmt, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(KeyValueStmt, ACT_INVALID)
	BLOCK_BEGIN(2);
	TEST(CharRuleStmt, ACT_INVALID)
	BLOCK_BEGIN(3);
	TEST(TokenRuleStmt, ACT_INVALID)
	BLOCK_BEGIN(4);
	TEST(RuleExprStmt, ACT_INVALID)
	return false;
}

bool Parser::EmptyStmt() {
	RET(EMPTY_STMT)
	SAVE;
	BLOCK_BEGIN(0);
	TEST_TOKEN_DISCARDSAVED(';', ACT_INVALID)
	DISCARD;
	return false;
}

bool Parser::KeyValueStmt() {
	RET(KEY_VALUE_STMT)
	SAVE;
	BLOCK_BEGIN(0);
	while (true) {
		TEST_PART(StringLiteral);
		TEST_PART_TOKEN(':');
		TEST_PART(StringLiteral);
		TEST_PART_TOKEN(';');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::CharRuleStmt() {
	RET(CHAR_RULE_STMT)
	SAVE;
	BLOCK_BEGIN(0);
	while (true) {
		TEST_PART(CharRuleId);
		TEST_PART_TOKEN(':');
		TEST_PART(CharRuleBlock);
		TEST_PART_TOKEN(';');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::CharRuleBlock() {
	RET(CHAR_RULE_BLOCK)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(CharRuleBlockFirst);}
		else {TEST_PART(CharRuleBlockSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::CharRuleBlockFirst() {
	RET(CHAR_RULE_BLOCK_ITEM)
	BLOCK_BEGIN(1);
	TEST(CharRuleElement, ACT_INVALID)
	return false;
}

bool Parser::CharRuleBlockSecond() {
	RET(CHAR_RULE_BLOCK_ITEM)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART(CharRuleOp);
		TEST_PART(CharRuleElement);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::CharRuleOp() {
	RET(CHAR_RULE_OP)
	BLOCK_BEGIN(0);
	TEST_TOKEN('+', ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST_TOKEN('-', ACT_INVALID)
	return false;
}

bool Parser::CharRuleElement() {
	RET(CHAR_RULE_ELEMENT)
	BLOCK_BEGIN(0);
	TEST(CharRuleId, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(CharList, ACT_INVALID)
	return false;
}

bool Parser::TokenRuleStmt() {
	RET(TOKEN_RULE_STMT)
	SAVE;
	BLOCK_BEGIN(0);
	while (true) {
		TEST_PART(TokenRuleId);
		TEST_PART_TOKEN(':');
		TEST_PART(TokenRuleExpr);
		TEST_PART_TOKEN(';');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::TokenRuleExpr() {
	RET(TOKEN_RULE_EXPR)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(TokenRuleExprFirst);}
		else {TEST_PART(TokenRuleExprSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::TokenRuleExprFirst() {
	RET(TOKEN_RULE_EXPR_ITEM)
	BLOCK_BEGIN(1);
	TEST(TokenRuleBlock, ACT_INVALID)
	return false;
}

bool Parser::TokenRuleExprSecond() {
	RET(TOKEN_RULE_EXPR_ITEM)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('|');
		TEST_PART(TokenRuleBlock);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::TokenRuleBlock() {
	RET(TOKEN_RULE_BLOCK)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(TokenRuleBlockFirst);}
		else {TEST_PART(TokenRuleBlockSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::TokenRuleBlockFirst() {
	RET(TOKEN_RULE_BLOCK_ITEM)
	BLOCK_BEGIN(1);
	TEST(TokenRuleElement, ACT_INVALID)
	return false;
}

bool Parser::TokenRuleBlockSecond() {
	RET(TOKEN_RULE_BLOCK_ITEM)
	BLOCK_BEGIN(0);
	TEST(TokenRuleElement, ACT_INVALID)
	return false;
}

bool Parser::TokenRuleElement() {
	RET(TOKEN_RULE_ELEMENT)
	BLOCK_BEGIN(0);
	TEST(ElementCharRule, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(ElementTokenRule, ACT_INVALID)
	BLOCK_BEGIN(2);
	TEST(CharListElement, ACT_INVALID)
	BLOCK_BEGIN(3);
	TEST(CharElement, ACT_INVALID)
	BLOCK_BEGIN(4);
	TEST(StringElement, ACT_INVALID)
	BLOCK_BEGIN(5);
	TEST(IdElement, ACT_INVALID)
	return false;
}

bool Parser::RuleExprStmt() {
	RET(RULE_EXPR_STMT)
	SAVE;
	BLOCK_BEGIN(0);
	while (true) {
		TEST_PART(RuleId);
		TEST_PART_TOKEN(':');
		TEST_PART(RuleExpr);
		TEST_PART_TOKEN(';');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::RuleExpr() {
	RET(RULE_EXPR)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(RuleExprFirst);}
		else {TEST_PART(RuleExprSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::RuleExprFirst() {
	RET(RULE_EXPR_ITEM)
	BLOCK_BEGIN(1);
	TEST(BlockExpr, ACT_INVALID)
	return false;
}

bool Parser::RuleExprSecond() {
	RET(RULE_EXPR_ITEM)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('|');
		TEST_PART(BlockExpr);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::BlockExpr() {
	RET(BLOCK_EXPR)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(BlockExprFirst);}
		else {TEST_PART(BlockExprSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::BlockExprFirst() {
	RET(BLOCK_EXPR_ITEM)
	BLOCK_BEGIN(1);
	TEST(ElementExpr, ACT_INVALID)
	return false;
}

bool Parser::BlockExprSecond() {
	RET(BLOCK_EXPR_ITEM)
	BLOCK_BEGIN(0);
	TEST(ElementExpr, ACT_INVALID)
	return false;
}

bool Parser::ElementExpr() {
	RET(ELEMENT_EXPR)
	BLOCK_BEGIN(0);
	TEST(PreExpr, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(PostExpr, ACT_INVALID)
	BLOCK_BEGIN(2);
	SAVE;
	while (true) {
		TEST_PART(Element);
		TEST_PART_OPT(ElementPostQualifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::PreExpr() {
	RET(PRE_EXPR)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('(');
		TEST_PART_TOKEN('<');
		TEST_PART(IdSeq);
		TEST_PART_TOKEN(')');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::PostExpr() {
	RET(POST_EXPR)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('(');
		TEST_PART_TOKEN('>');
		TEST_PART(IdSeq);
		TEST_PART_TOKEN(')');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::IdSeq() {
	RET(ID_SEQ)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(IdSeqFirst);}
		else {TEST_PART(IdSeqSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::IdSeqFirst() {
	RET(ID_SEQ_ITEM)
	BLOCK_BEGIN(1);
	TEST(Identifier, ACT_INVALID)
	return false;
}

bool Parser::IdSeqSecond() {
	RET(ID_SEQ_ITEM)
	BLOCK_BEGIN(0);
	TEST(Identifier, ACT_INVALID)
	return false;
}

bool Parser::ElementCharRule() {
	RET(ELEMENT_CHAR_RULE)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART(CharRuleId);
		TEST_PART_OPT(TokenElementPostQualifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::ElementTokenRule() {
	RET(ELEMENT_TOKEN_RULE)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART(TokenRuleId);
		TEST_PART_OPT(TokenElementPostQualifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::CharListElement() {
	RET(CHAR_LIST_ELEMENT)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART(CharList);
		TEST_PART_OPT(TokenElementPostQualifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::CharElement() {
	RET(CHAR_ELEMENT)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART(CharLiteral);
		TEST_PART_OPT(TokenElementPostQualifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::StringElement() {
	RET(STRING_ELEMENT)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART(StringLiteral);
		TEST_PART_OPT(TokenElementPostQualifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::IdElement() {
	RET(ID_ELEMENT)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART(Identifier);
		TEST_PART_OPT(TokenElementPostQualifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::CharRuleId() {
	RET(CHAR_RULE_ID)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('{');
		TEST_PART(Identifier);
		TEST_PART_TOKEN('}');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::TokenRuleId() {
	RET(TOKEN_RULE_ID)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('<');
		TEST_PART(Identifier);
		TEST_PART_TOKEN('>');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::RuleId() {
	RET(RULE_ID)
	BLOCK_BEGIN(0);
	TEST(Identifier, ACT_INVALID)
	return false;
}

bool Parser::TokenElementPostQualifier() {
	RET(TOKEN_ELEMENT_POST_QUALIFIER)
	BLOCK_BEGIN(0);
	TEST_TOKEN('*', ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST_TOKEN('+', ACT_INVALID)
	BLOCK_BEGIN(2);
	TEST_TOKEN('?', ACT_INVALID)
	return false;
}

bool Parser::ElementPostQualifier() {
	RET(ELEMENT_POST_QUALIFIER)
	BLOCK_BEGIN(0);
	TEST_TOKEN('?', ACT_INVALID)
	return false;
}

bool Parser::Element() {
	RET(ELEMENT)
	BLOCK_BEGIN(0);
	TEST(CharLiteral, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(StringLiteral, ACT_INVALID)
	BLOCK_BEGIN(2);
	TEST(RuleId, ACT_INVALID)
	return false;
}

bool Parser::Eof() {
	RET(EOF)
	BLOCK_BEGIN(0);
	TEST_TOKEN(EOF, ACT_INVALID)
	return false;
}

bool Parser::Identifier() {
	RET(IDENTIFIER)
	BLOCK_BEGIN(0);
	TEST(IDENTIFIER, ACT_INVALID)
	return false;
}

bool Parser::CharList() {
	RET(CHAR_LIST)
	BLOCK_BEGIN(0);
	TEST(CHARLIST, ACT_INVALID)
	return false;
}

bool Parser::CharLiteral() {
	RET(CHAR_LITERAL)
	BLOCK_BEGIN(0);
	TEST(CHAR, ACT_INVALID)
	return false;
}

bool Parser::StringLiteral() {
	RET(STRING_LITERAL)
	BLOCK_BEGIN(0);
	TEST(STRING, ACT_INVALID)
	return false;
}

}

