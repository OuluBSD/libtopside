#ifndef flagBOOTSTRAP
#include "Grammar.h"

namespace TS::Grammar {

bool PostParser::FileInput(const Node& n) {
	ASSERT_TYPE(n, NODE_FILE_INPUT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		Eof(SUB0);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(2);
		FileLineSeq(SUB0);
		Eof(SUB1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in FileInput");}
	return false;
}

bool PostParser::FileLineSeq(const Node& n) {
	ASSERT_TYPE(n, NODE_FILE_LINE_SEQ);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(2);
		FileLineSeq(SUB0);
		FileLine(SUB1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		FileLine(SUB0);
		return true;
	}
	else if (IS_BLOCK(-1)) {
		for(int i = 0; i < n.GetCount(); i++) {
			POST_TEST(FileLineSeqItem(SUB(i)));
		}
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in FileLineSeq");}
	return false;
}

bool PostParser::FileLineSeqItem(const Node& n) {
	ASSERT_TYPE(n, NODE_FILE_LINE_SEQ_ITEM);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT_NONZERO;
		FileLine(SUB0);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT_NONZERO;
		FileLine(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in FileLineSeq");}
	return false;
}

bool PostParser::FileLine(const Node& n) {
	ASSERT_TYPE(n, NODE_FILE_LINE);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		EmptyStmt(SUB0);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		KeyValueStmt(SUB0);
		return true;
	}
	else if (IS_BLOCK(2)) {
		ASSERT_COUNT(1);
		CharRuleStmt(SUB0);
		return true;
	}
	else if (IS_BLOCK(3)) {
		ASSERT_COUNT(1);
		TokenRuleStmt(SUB0);
		return true;
	}
	else if (IS_BLOCK(4)) {
		ASSERT_COUNT(1);
		RuleExprStmt(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in FileLine");}
	return false;
}

bool PostParser::EmptyStmt(const Node& n) {
	ASSERT_TYPE(n, NODE_EMPTY_STMT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		POST_TEST(TestCharLiteral(SUB0, ";"));
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in EmptyStmt");}
	return false;
}

bool PostParser::KeyValueStmt(const Node& n) {
	ASSERT_TYPE(n, NODE_KEY_VALUE_STMT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(4);
		PushCommand("b ata", 5);
		PushCommand("a key", 5);
		StringLiteral(SUB0);
		POST_TEST(TestCharLiteral(SUB1, ":"));
		PushCommand("a value", 7);
		StringLiteral(SUB2);
		POST_TEST(TestCharLiteral(SUB3, ";"));
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in KeyValueStmt");}
	return false;
}

bool PostParser::CharRuleStmt(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_RULE_STMT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(4);
		PushCommand("b acd cls", 9);
		CharRuleId(SUB0);
		PushCommand("e", 1);
		POST_TEST(TestCharLiteral(SUB1, ":"));
		PushCommand("b est", 5);
		CharRuleBlock(SUB2);
		POST_TEST(TestCharLiteral(SUB3, ";"));
		PushCommand("e", 1);
		PushCommand("cdp", 3);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharRuleStmt");}
	return false;
}

bool PostParser::CharRuleBlock(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_RULE_BLOCK);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(3);
		PushCommand("a b ex", 6);
		CharRuleBlock(SUB0);
		CharRuleOp(SUB1);
		CharRuleElement(SUB2);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		CharRuleElement(SUB0);
		return true;
	}
	else if (IS_BLOCK(-1)) {
		for(int i = 0; i < n.GetCount(); i++) {
			POST_TEST(CharRuleBlockItem(SUB(i)));
		}
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharRuleBlock");}
	return false;
}

bool PostParser::CharRuleBlockItem(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_RULE_BLOCK_ITEM);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT_NONZERO;
		PushCommand("a b ex", 6);
		CharRuleOp(SUB0);
		CharRuleElement(SUB1);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT_NONZERO;
		CharRuleElement(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharRuleBlock");}
	return false;
}

bool PostParser::CharRuleOp(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_RULE_OP);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("a op add", 8);
		POST_TEST(TestCharLiteral(SUB0, "+"));
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		PushCommand("a op sub", 8);
		POST_TEST(TestCharLiteral(SUB0, "-"));
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharRuleOp");}
	return false;
}

bool PostParser::CharRuleElement(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_RULE_ELEMENT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("a b ex", 6);
		CharRuleId(SUB0);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		PushCommand("a b ex", 6);
		PushCommand("a char_list", 11);
		CharList(SUB0);
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharRuleElement");}
	return false;
}

bool PostParser::TokenRuleStmt(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_RULE_STMT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(4);
		PushCommand("b acd cls", 9);
		TokenRuleId(SUB0);
		PushCommand("e", 1);
		POST_TEST(TestCharLiteral(SUB1, ":"));
		PushCommand("b est", 5);
		TokenRuleExpr(SUB2);
		POST_TEST(TestCharLiteral(SUB3, ";"));
		PushCommand("e", 1);
		PushCommand("cdp", 3);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenRuleStmt");}
	return false;
}

bool PostParser::TokenRuleExpr(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_RULE_EXPR);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(3);
		PushCommand("a b ex", 6);
		TokenRuleExpr(SUB0);
		POST_TEST(TestCharLiteral(SUB1, "|"));
		TokenRuleBlock(SUB2);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		TokenRuleBlock(SUB0);
		return true;
	}
	else if (IS_BLOCK(-1)) {
		for(int i = 0; i < n.GetCount(); i++) {
			POST_TEST(TokenRuleExprItem(SUB(i)));
		}
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenRuleExpr");}
	return false;
}

bool PostParser::TokenRuleExprItem(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_RULE_EXPR_ITEM);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT_NONZERO;
		PushCommand("a b ex", 6);
		POST_TEST(TestCharLiteral(SUB0, "|"));
		TokenRuleBlock(SUB1);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT_NONZERO;
		TokenRuleBlock(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenRuleExpr");}
	return false;
}

bool PostParser::TokenRuleBlock(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_RULE_BLOCK);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(2);
		PushCommand("a b ex", 6);
		TokenRuleBlock(SUB0);
		TokenRuleElement(SUB1);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		TokenRuleElement(SUB0);
		return true;
	}
	else if (IS_BLOCK(-1)) {
		for(int i = 0; i < n.GetCount(); i++) {
			POST_TEST(TokenRuleBlockItem(SUB(i)));
		}
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenRuleBlock");}
	return false;
}

bool PostParser::TokenRuleBlockItem(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_RULE_BLOCK_ITEM);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT_NONZERO;
		PushCommand("a b ex", 6);
		TokenRuleElement(SUB0);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT_NONZERO;
		TokenRuleElement(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenRuleBlock");}
	return false;
}

bool PostParser::TokenRuleElement(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_RULE_ELEMENT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		ElementCharRule(SUB0);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		ElementTokenRule(SUB0);
		return true;
	}
	else if (IS_BLOCK(2)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		CharListElement(SUB0);
		return true;
	}
	else if (IS_BLOCK(3)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		CharElement(SUB0);
		return true;
	}
	else if (IS_BLOCK(4)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		StringElement(SUB0);
		return true;
	}
	else if (IS_BLOCK(5)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		IdElement(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenRuleElement");}
	return false;
}

bool PostParser::RuleExprStmt(const Node& n) {
	ASSERT_TYPE(n, NODE_RULE_EXPR_STMT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(4);
		PushCommand("b acd cls", 9);
		RuleId(SUB0);
		PushCommand("e", 1);
		POST_TEST(TestCharLiteral(SUB1, ":"));
		PushCommand("b est", 5);
		RuleExpr(SUB2);
		POST_TEST(TestCharLiteral(SUB3, ";"));
		PushCommand("e", 1);
		PushCommand("cdp", 3);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in RuleExprStmt");}
	return false;
}

bool PostParser::RuleExpr(const Node& n) {
	ASSERT_TYPE(n, NODE_RULE_EXPR);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(3);
		PushCommand("a b ex", 6);
		RuleExpr(SUB0);
		POST_TEST(TestStringLiteral(SUB1, "|"));
		BlockExpr(SUB2);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		BlockExpr(SUB0);
		return true;
	}
	else if (IS_BLOCK(-1)) {
		for(int i = 0; i < n.GetCount(); i++) {
			POST_TEST(RuleExprItem(SUB(i)));
		}
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in RuleExpr");}
	return false;
}

bool PostParser::RuleExprItem(const Node& n) {
	ASSERT_TYPE(n, NODE_RULE_EXPR_ITEM);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT_NONZERO;
		PushCommand("a b ex", 6);
		POST_TEST(TestStringLiteral(SUB0, "|"));
		BlockExpr(SUB1);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT_NONZERO;
		BlockExpr(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in RuleExpr");}
	return false;
}

bool PostParser::BlockExpr(const Node& n) {
	ASSERT_TYPE(n, NODE_BLOCK_EXPR);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(2);
		PushCommand("a b ex", 6);
		BlockExpr(SUB0);
		ElementExpr(SUB1);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		ElementExpr(SUB0);
		return true;
	}
	else if (IS_BLOCK(-1)) {
		for(int i = 0; i < n.GetCount(); i++) {
			POST_TEST(BlockExprItem(SUB(i)));
		}
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in BlockExpr");}
	return false;
}

bool PostParser::BlockExprItem(const Node& n) {
	ASSERT_TYPE(n, NODE_BLOCK_EXPR_ITEM);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT_NONZERO;
		PushCommand("a b ex", 6);
		ElementExpr(SUB0);
		PushCommand("e", 1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT_NONZERO;
		ElementExpr(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in BlockExpr");}
	return false;
}

bool PostParser::ElementExpr(const Node& n) {
	ASSERT_TYPE(n, NODE_ELEMENT_EXPR);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		PreExpr(SUB0);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		PushCommand("a", 1);
		PostExpr(SUB0);
		return true;
	}
	else if (IS_BLOCK(2)) {
		DYN_INIT;
		PushCommand("a b ex", 6);
		Element(DYNSUB);
		INC_DYN;
		if (IS_NOT_END && IS_TYPE_SUBDYN(NODE_ELEMENT_POST_QUALIFIER)) {ElementPostQualifier(DYNSUB); INC_DYN;}
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in ElementExpr");}
	return false;
}

bool PostParser::PreExpr(const Node& n) {
	ASSERT_TYPE(n, NODE_PRE_EXPR);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(4);
		PushCommand("b ex", 4);
		POST_TEST(TestCharLiteral(SUB0, "("));
		PushCommand("a op less", 9);
		POST_TEST(TestCharLiteral(SUB1, "<"));
		IdSeq(SUB2);
		POST_TEST(TestCharLiteral(SUB3, ")"));
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in PreExpr");}
	return false;
}

bool PostParser::PostExpr(const Node& n) {
	ASSERT_TYPE(n, NODE_POST_EXPR);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(4);
		PushCommand("b ex", 4);
		POST_TEST(TestCharLiteral(SUB0, "("));
		PushCommand("a op grtr", 9);
		POST_TEST(TestCharLiteral(SUB1, ">"));
		IdSeq(SUB2);
		POST_TEST(TestCharLiteral(SUB3, ")"));
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in PostExpr");}
	return false;
}

bool PostParser::IdSeq(const Node& n) {
	ASSERT_TYPE(n, NODE_ID_SEQ);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(2);
		IdSeq(SUB0);
		PushCommand("a id_lit", 8);
		Identifier(SUB1);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		PushCommand("a id_lit", 8);
		Identifier(SUB0);
		return true;
	}
	else if (IS_BLOCK(-1)) {
		for(int i = 0; i < n.GetCount(); i++) {
			POST_TEST(IdSeqItem(SUB(i)));
		}
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in IdSeq");}
	return false;
}

bool PostParser::IdSeqItem(const Node& n) {
	ASSERT_TYPE(n, NODE_ID_SEQ_ITEM);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT_NONZERO;
		PushCommand("a id_lit", 8);
		Identifier(SUB0);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT_NONZERO;
		PushCommand("a id_lit", 8);
		Identifier(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in IdSeq");}
	return false;
}

bool PostParser::ElementCharRule(const Node& n) {
	ASSERT_TYPE(n, NODE_ELEMENT_CHAR_RULE);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		DYN_INIT;
		PushCommand("b ex", 4);
		CharRuleId(DYNSUB);
		INC_DYN;
		if (IS_NOT_END && IS_TYPE_SUBDYN(NODE_TOKEN_ELEMENT_POST_QUALIFIER)) {TokenElementPostQualifier(DYNSUB); INC_DYN;}
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in ElementCharRule");}
	return false;
}

bool PostParser::ElementTokenRule(const Node& n) {
	ASSERT_TYPE(n, NODE_ELEMENT_TOKEN_RULE);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		DYN_INIT;
		PushCommand("b ex", 4);
		TokenRuleId(DYNSUB);
		INC_DYN;
		if (IS_NOT_END && IS_TYPE_SUBDYN(NODE_TOKEN_ELEMENT_POST_QUALIFIER)) {TokenElementPostQualifier(DYNSUB); INC_DYN;}
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in ElementTokenRule");}
	return false;
}

bool PostParser::CharListElement(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_LIST_ELEMENT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		DYN_INIT;
		PushCommand("b ex", 4);
		PushCommand("a char_list", 11);
		CharList(DYNSUB);
		INC_DYN;
		if (IS_NOT_END && IS_TYPE_SUBDYN(NODE_TOKEN_ELEMENT_POST_QUALIFIER)) {TokenElementPostQualifier(DYNSUB); INC_DYN;}
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharListElement");}
	return false;
}

bool PostParser::CharElement(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_ELEMENT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		DYN_INIT;
		PushCommand("b ex", 4);
		PushCommand("a char_lit", 10);
		CharLiteral(DYNSUB);
		INC_DYN;
		if (IS_NOT_END && IS_TYPE_SUBDYN(NODE_TOKEN_ELEMENT_POST_QUALIFIER)) {TokenElementPostQualifier(DYNSUB); INC_DYN;}
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharElement");}
	return false;
}

bool PostParser::StringElement(const Node& n) {
	ASSERT_TYPE(n, NODE_STRING_ELEMENT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		DYN_INIT;
		PushCommand("b ex", 4);
		PushCommand("a str_lit", 9);
		StringLiteral(DYNSUB);
		INC_DYN;
		if (IS_NOT_END && IS_TYPE_SUBDYN(NODE_TOKEN_ELEMENT_POST_QUALIFIER)) {TokenElementPostQualifier(DYNSUB); INC_DYN;}
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in StringElement");}
	return false;
}

bool PostParser::IdElement(const Node& n) {
	ASSERT_TYPE(n, NODE_ID_ELEMENT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		DYN_INIT;
		PushCommand("b ex", 4);
		PushCommand("a id", 4);
		Identifier(DYNSUB);
		INC_DYN;
		if (IS_NOT_END && IS_TYPE_SUBDYN(NODE_TOKEN_ELEMENT_POST_QUALIFIER)) {TokenElementPostQualifier(DYNSUB); INC_DYN;}
		PushCommand("e", 1);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in IdElement");}
	return false;
}

bool PostParser::CharRuleId(const Node& n) {
	ASSERT_TYPE(n, NODE_CHAR_RULE_ID);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(3);
		PushCommand("a id char_rule", 14);
		POST_TEST(TestCharLiteral(SUB0, "{"));
		PushCommand("a id_lit", 8);
		Identifier(SUB1);
		POST_TEST(TestCharLiteral(SUB2, "}"));
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in CharRuleId");}
	return false;
}

bool PostParser::TokenRuleId(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_RULE_ID);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(3);
		PushCommand("a id token_rule", 15);
		POST_TEST(TestCharLiteral(SUB0, "<"));
		PushCommand("a id_lit", 8);
		Identifier(SUB1);
		POST_TEST(TestCharLiteral(SUB2, ">"));
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenRuleId");}
	return false;
}

bool PostParser::RuleId(const Node& n) {
	ASSERT_TYPE(n, NODE_RULE_ID);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("a id rule", 9);
		PushCommand("a id_lit", 8);
		Identifier(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in RuleId");}
	return false;
}

bool PostParser::TokenElementPostQualifier(const Node& n) {
	ASSERT_TYPE(n, NODE_TOKEN_ELEMENT_POST_QUALIFIER);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("a op any", 8);
		POST_TEST(TestCharLiteral(SUB0, "*"));
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		PushCommand("a op pos", 8);
		POST_TEST(TestCharLiteral(SUB0, "+"));
		return true;
	}
	else if (IS_BLOCK(2)) {
		ASSERT_COUNT(1);
		PushCommand("a v opt", 7);
		POST_TEST(TestCharLiteral(SUB0, "?"));
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in TokenElementPostQualifier");}
	return false;
}

bool PostParser::ElementPostQualifier(const Node& n) {
	ASSERT_TYPE(n, NODE_ELEMENT_POST_QUALIFIER);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("op opt", 6);
		POST_TEST(TestStringLiteral(SUB0, "?"));
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in ElementPostQualifier");}
	return false;
}

bool PostParser::Element(const Node& n) {
	ASSERT_TYPE(n, NODE_ELEMENT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		ASSERT_COUNT(1);
		PushCommand("a char_lit", 10);
		CharLiteral(SUB0);
		return true;
	}
	else if (IS_BLOCK(1)) {
		ASSERT_COUNT(1);
		PushCommand("a str_lit", 9);
		StringLiteral(SUB0);
		return true;
	}
	else if (IS_BLOCK(2)) {
		ASSERT_COUNT(1);
		RuleId(SUB0);
		return true;
	}
	else {ADD_POST_ERROR("Invalid block in Element");}
	return false;
}

}

#endif

