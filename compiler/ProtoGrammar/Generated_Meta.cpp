// Generated at 12/21/2020 07:40:50
#include "Grammar.h"
namespace TS::Meta {
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
	TEST(ExprStmt, ACT_INVALID)
	return false;
}

bool Parser::ExprStmt() {
	RET(EXPR_STMT)
	BLOCK_BEGIN(0);
	TEST(CallWithArgs, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(Call, ACT_INVALID)
	return false;
}

bool Parser::Call() {
	RET(CALL)
	BLOCK_BEGIN(0);
	TEST(FunctionWithoutParams, ACT_INVALID)
	return false;
}

bool Parser::CallWithArgs() {
	RET(CALL_WITH_ARGS)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('b');
		TEST_PART(FunctionWithParams);
		TEST_PART(ArgSeq);
		TEST_PART_TOKEN('e');
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::ArgSeq() {
	RET(ARG_SEQ)
	bool is_fail = false;
	while (!IsEof() && !IsToken(TK_DEDENT)) {
		if (ret->IsEmpty()) {TEST_PART(ArgSeqFirst);}
		else {TEST_PART(ArgSeqSecond);}
	}
	if (!ret->IsEmpty()) {SET_RETURNED; return true;}
	return false;
}

bool Parser::ArgSeqFirst() {
	RET(ARG_SEQ_ITEM)
	BLOCK_BEGIN(1);
	TEST(Arg, ACT_INVALID)
	return false;
}

bool Parser::ArgSeqSecond() {
	RET(ARG_SEQ_ITEM)
	BLOCK_BEGIN(0);
	TEST(Arg, ACT_INVALID)
	return false;
}

bool Parser::Arg() {
	RET(ARG)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN('a');
		TEST_PART_OPT(ArgQual);
		TEST_PART(ArgSpec);
		TEST_PART_OPT(ArgQualOp);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::ArgSpec() {
	RET(ARG_SPEC)
	BLOCK_BEGIN(0);
	TEST(ArgExprLeft, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(ArgExprRight, ACT_INVALID)
	BLOCK_BEGIN(2);
	TEST(ArgClsId, ACT_INVALID)
	BLOCK_BEGIN(3);
	TEST(CallWithArgs, ACT_INVALID)
	BLOCK_BEGIN(4);
	TEST(Call, ACT_INVALID)
	BLOCK_BEGIN(5);
	TEST(StrLit, ACT_INVALID)
	BLOCK_BEGIN(6);
	TEST(ChrLit, ACT_INVALID)
	BLOCK_BEGIN(7);
	TEST(IdLit, ACT_INVALID)
	BLOCK_BEGIN(8);
	TEST(ArgId, ACT_INVALID)
	return false;
}

bool Parser::FunctionWithoutParams() {
	RET(FUNCTION_WITHOUT_PARAMS)
	BLOCK_BEGIN(0);
	TEST(FnCdParent, ACT_INVALID)
	return false;
}

bool Parser::FunctionWithParams() {
	RET(FUNCTION_WITH_PARAMS)
	BLOCK_BEGIN(0);
	TEST(FnExpr, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(FnAddCd, ACT_INVALID)
	BLOCK_BEGIN(2);
	TEST(FnExprStmt, ACT_INVALID)
	BLOCK_BEGIN(3);
	TEST(FnAddAttr, ACT_INVALID)
	return false;
}

bool Parser::FnCdParent() {
	RET(FN_CD_PARENT)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("cdp", ACT_INVALID)
	return false;
}

bool Parser::FnExpr() {
	RET(FN_EXPR)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("ex", ACT_INVALID)
	return false;
}

bool Parser::FnAddCd() {
	RET(FN_ADD_CD)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN_ID("acd");
		TEST_PART(DirType);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::DirType() {
	RET(DIR_TYPE)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("cls", ACT_INVALID)
	return false;
}

bool Parser::FnExprStmt() {
	RET(FN_EXPR_STMT)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("est", ACT_INVALID)
	return false;
}

bool Parser::FnAddAttr() {
	RET(FN_ADD_ATTR)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("ata", ACT_INVALID)
	return false;
}

bool Parser::ArgExprLeft() {
	RET(ARG_EXPR_LEFT)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("left", ACT_INVALID)
	return false;
}

bool Parser::ArgExprRight() {
	RET(ARG_EXPR_RIGHT)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("right", ACT_INVALID)
	return false;
}

bool Parser::ArgClsId() {
	RET(ARG_CLS_ID)
	BLOCK_BEGIN(0);
	TEST(ArgClsIdRule, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(ArgClsIdSimple, ACT_INVALID)
	return false;
}

bool Parser::ArgClsIdSimple() {
	RET(ARG_CLS_ID_SIMPLE)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("clsid", ACT_INVALID)
	return false;
}

bool Parser::ArgClsIdRule() {
	RET(ARG_CLS_ID_RULE)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN_ID("clsid");
		TEST_PART_TOKEN_ID("rule");
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::ArgQual() {
	RET(ARG_QUAL)
	BLOCK_BEGIN(0);
	TEST(ArgQualKey, ACT_INVALID)
	BLOCK_BEGIN(1);
	TEST(ArgQualValue, ACT_INVALID)
	BLOCK_BEGIN(2);
	TEST(ArgQualOp, ACT_INVALID)
	return false;
}

bool Parser::ArgQualKey() {
	RET(ARG_QUAL_KEY)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("key", ACT_INVALID)
	return false;
}

bool Parser::ArgQualValue() {
	RET(ARG_QUAL_VALUE)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("value", ACT_INVALID)
	return false;
}

bool Parser::ArgQualOp() {
	RET(ARG_QUAL_OP)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN_ID("op");
		TEST_PART(Identifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::ArgId() {
	RET(ARG_ID)
	BLOCK_BEGIN(0);
	SAVE;
	while (true) {
		TEST_PART_TOKEN_ID("id");
		TEST_PART(Identifier);
		DISCARD; SET_RETURNED; return true;
	}
	LOAD_NO_DISCARD; CLEAR_RET;
	DISCARD;
	return false;
}

bool Parser::StrLit() {
	RET(STR_LIT)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("str_lit", ACT_INVALID)
	return false;
}

bool Parser::ChrLit() {
	RET(CHR_LIT)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("char_lit", ACT_INVALID)
	return false;
}

bool Parser::IdLit() {
	RET(ID_LIT)
	BLOCK_BEGIN(0);
	TEST_TOKEN_ID("id_lit", ACT_INVALID)
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

