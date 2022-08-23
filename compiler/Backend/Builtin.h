#ifndef _Backend_Builtin_h_
#define _Backend_Builtin_h_

NAMESPACE_TOPSIDE_BEGIN

typedef enum {
	CLSRC_NULL,
	CLSRC_NAMESPACE,
	CLSRC_BUILTIN,
	CLSRC_TYPEDEF,
	CLSRC_DECLARED,
	CLSRC_DEFINED,
	CLSRC_META,
	CLSRC_TEMPLATE,
} ClassSource;


inline bool IsTrivialObjectType(ClassSource src) {
	return	src == CLSRC_BUILTIN ||
			src == CLSRC_TYPEDEF ||
			src == CLSRC_DECLARED ||
			src == CLSRC_DEFINED;
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


NAMESPACE_TOPSIDE_END

#endif
