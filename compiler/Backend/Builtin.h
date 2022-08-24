#ifndef _Backend_Builtin_h_
#define _Backend_Builtin_h_

NAMESPACE_TOPSIDE_BEGIN

typedef enum {
	SEMT_NULL,
	SEMT_NAMESPACE,
	SEMT_BUILTIN,
	SEMT_TYPEDEF,
	SEMT_DECLARED,
	SEMT_DEFINED,
	SEMT_META,
	SEMT_TEMPLATE,
	SEMT_FUNCTION_STATIC,
	SEMT_FUNCTION_METHOD,
	SEMT_VARIABLE,
	SEMT_PARAMETER,
} SemanticType;


inline bool IsTrivialObjectType(SemanticType src) {
	return	src == SEMT_BUILTIN ||
			src == SEMT_TYPEDEF ||
			src == SEMT_DECLARED ||
			src == SEMT_DEFINED;
}

typedef enum {
	STMT_IF,
	STMT_ELSE,
	STMT_DOWHILE,
	STMT_WHILE,
	STMT_FOR,
	STMT_BREAK,
	STMT_CONTINUE,
	STMT_CASE,
	STMT_DEFAULT,
	STMT_RETURN,
	STMT_SWITCH,
	STMT_LOG,
	STMT_BLOCK,
} StmtType;

inline String GetStmtTypeString(StmtType t) {
	switch (t) {
		case STMT_IF: return "if";
		case STMT_ELSE: return "else";
		case STMT_DOWHILE: return "do-while";
		case STMT_WHILE: return "while";
		case STMT_FOR: return "for";
		case STMT_BREAK: return "break";
		case STMT_CONTINUE: return "continue";
		case STMT_CASE: return "case";
		case STMT_DEFAULT: return "default";
		case STMT_RETURN: return "return";
		case STMT_SWITCH: return "switch";
		case STMT_LOG: return "log";
		case STMT_BLOCK: return "block";
	}
	return String();
}

typedef enum {
	STMTP_FOR_DECL,
	STMTP_WHILE_COND,
	STMTP_FOR_POST,
	STMTP_FOR_COLLECTION,
} StmtParamType;

inline String GetStmtParamTypeString(StmtParamType t) {
	switch (t) {
		case STMTP_FOR_DECL: return "for-decl";
		case STMTP_WHILE_COND: return "while-cond";
		case STMTP_FOR_POST: return "for-post";
		case STMTP_FOR_COLLECTION: return "for-collection";
	}
	return String();
}


typedef enum {
	OP_INC,
	OP_DEC,
	OP_POSTINC,
	OP_POSTDEC,
	OP_NEGATIVE,
	OP_POSITIVE,
	OP_NOT,
	OP_NEGATE,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_LSH,
	OP_RSH,
	OP_GREQ,
	OP_LSEQ,
	OP_GREATER,
	OP_LESS,
	OP_EQ,
	OP_INEQ,
	OP_BWAND,
	OP_BWXOR,
	OP_BWOR,
	OP_AND,
	OP_OR,
	OP_COND,
	OP_ASSIGN,
	OP_ADDASS,
	OP_SUBASS,
	OP_MULASS,
	OP_DIVASS,
	OP_MODASS,
	
} OpType;


inline String GetOpString(OpType t) {
	switch (t) {
		case OP_INC: return "increase";
		case OP_DEC: return "decrease";
		case OP_POSTINC: return "post-increase";
		case OP_POSTDEC: return "post-decrease";
		case OP_NEGATIVE: return "negative";
		case OP_POSITIVE: return "positive";
		case OP_NOT: return "not";
		case OP_NEGATE: return "negate";
		case OP_ADD: return "add";
		case OP_SUB: return "subtract";
		case OP_MUL: return "multiply";
		case OP_DIV: return "divide";
		case OP_MOD: return "modulus";
		case OP_LSH: return "left-shift";
		case OP_RSH: return "right-shift";
		case OP_GREQ: return "greqter-or-equal";
		case OP_LSEQ: return "less-or-equal";
		case OP_GREATER: return "greater";
		case OP_LESS: return "less";
		case OP_EQ: return "equal";
		case OP_INEQ: return "inequal";
		case OP_BWAND: return "bitwise-and";
		case OP_BWXOR: return "bitwise-xor";
		case OP_BWOR: return "bitwise-or";
		case OP_AND: return "and";
		case OP_OR: return "op";
		case OP_COND: return "conditional";
		case OP_ASSIGN: return "assign";
		case OP_ADDASS: return "add-and-assign";
		case OP_SUBASS: return "subtract-and-assign";
		case OP_MULASS: return "multiply-and-assign";
		case OP_DIVASS: return "divide-and-assign";
		case OP_MODASS: return "modulus-and-assign";
		default: return "<invalid>";
	}
}

NAMESPACE_TOPSIDE_END

#endif
