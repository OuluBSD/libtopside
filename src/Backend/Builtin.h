#ifndef _Backend_Builtin_h_
#define _Backend_Builtin_h_

NAMESPACE_TOPSIDE_BEGIN



typedef enum : uint64 {
	SEMT_NULL					= 1 << 0,
	SEMT_NAMESPACE				= 1 << 1,
	SEMT_BUILTIN				= 1 << 2,
	SEMT_TYPEDEF				= 1 << 3,
	SEMT_CLASS_DECL				= 1 << 4,
	SEMT_CLASS					= 1 << 5,
	SEMT_CLASS_TEMPLATE			= 1 << 6,
	SEMT_META_STATEMENT			= 1 << 7,
	//
	SEMT_FUNCTION_STATIC		= 1 << 9,
	SEMT_FUNCTION_METHOD		= 1 << 10,
	SEMT_VARIABLE				= 1 << 11,
	SEMT_PARAMETER				= 1 << 12,
	SEMT_STATEMENT				= 1 << 13,
	SEMT_STATEMENT_BLOCK		= 1 << 14,
	SEMT_EXPR					= 1 << 15,
	SEMT_CONSTANT				= 1 << 16,
	SEMT_IDPART					= 1 << 17,
	SEMT_ROOT					= 1 << 18,
	SEMT_RESOLVE				= 1 << 19,
	SEMT_ARGUMENT				= 1 << 20,
	SEMT_ARGUMENT_LIST			= 1 << 21,
	SEMT_FUNCTION_BUILTIN		= 1 << 22,
	SEMT_MACHINE_DECL			= 1 << 23,
	SEMT_MACHINE				= 1 << 24,
	SEMT_CHAIN_DECL				= 1 << 25,
	SEMT_CHAIN					= 1 << 26,
	SEMT_LOOP_DECL				= 1 << 27,
	SEMT_LOOP					= 1 << 28,
	SEMT_META_VARIABLE			= 1 << 29,
	SEMT_META_PARAMETER			= 1 << 30,
	SEMT_META_BUILTIN			= 1ULL << 31,
	SEMT_META_FUNCTION_STATIC	= 1ULL << 32,
	SEMT_WORLD					= 1ULL << 33,
	SEMT_ENTITY					= 1ULL << 34,
	SEMT_COMPONENT				= 1ULL << 35,
	SEMT_SYSTEM					= 1ULL << 36,
	SEMT_POOL					= 1ULL << 37,
	SEMT_ATOM					= 1ULL << 38,
	SEMT_CALL_ARG				= 1ULL << 39,
	SEMT_UNRESOLVED				= 1ULL << 40,
	SEMT_META_CLASS				= 1ULL << 41,
	SEMT_RVAL					= 1ULL << 42,
	SEMT_CTOR					= 1ULL << 43,
	SEMT_ARRAYSIZE				= 1ULL << 44,
	SEMT_TYPE_POINTER			= 1ULL << 45,
	SEMT_TYPE_LREF				= 1ULL << 46,
	SEMT_META_RVAL				= 1ULL << 47,
	SEMT_META_CTOR				= 1ULL << 48,
	SEMT_OBJECT					= 1ULL << 49,
	SEMT_META_RESOLVE			= 1ULL << 50,
	SEMT_STATE					= 1ULL << 51,
	SEMT_DRIVER					= 1ULL << 52,
	SEMT_ENGINE					= 1ULL << 53,
	SEMT_SYMBOLIC_LINK			= 1ULL << 54,
	
	// Current limit: 1 << 63
	
	SEMT_FIELD =			SEMT_VARIABLE | SEMT_PARAMETER | SEMT_CONSTANT,
	SEMT_TYPE =				SEMT_BUILTIN | SEMT_TYPEDEF | SEMT_CLASS_DECL | SEMT_CLASS |
							SEMT_CLASS_TEMPLATE | SEMT_TYPE_POINTER | SEMT_TYPE_LREF,
	SEMT_FUNCTION =			SEMT_FUNCTION_STATIC | SEMT_FUNCTION_METHOD | SEMT_FUNCTION_BUILTIN,
	SEMT_UNDEFINED =		SEMT_NULL | SEMT_IDPART,
	SEMT_PARAMETER_PATH =	SEMT_PARAMETER | SEMT_IDPART,
	SEMT_VARIABLE_PATH =	SEMT_VARIABLE | SEMT_IDPART,
	SEMT_PATH =				SEMT_PARAMETER_PATH | SEMT_VARIABLE_PATH | SEMT_NAMESPACE | SEMT_FUNCTION | SEMT_CLASS,
	SEMT_BLOCK =			SEMT_ROOT | SEMT_NAMESPACE | SEMT_STATEMENT_BLOCK,
	SEMT_WITH_RVAL_RET =	SEMT_RVAL | SEMT_EXPR | SEMT_CONSTANT | SEMT_RESOLVE | SEMT_ARGUMENT_LIST | SEMT_CTOR | SEMT_OBJECT,
	
	SEMT_ECS_ANY =			SEMT_ENGINE | SEMT_WORLD | SEMT_ENTITY | SEMT_COMPONENT | SEMT_SYSTEM | SEMT_POOL,
	SEMT_MACH_ANY =			SEMT_MACHINE_DECL | SEMT_MACHINE | SEMT_CHAIN_DECL | SEMT_CHAIN | SEMT_LOOP_DECL | SEMT_DRIVER | SEMT_LOOP | SEMT_STATE | SEMT_ATOM,
	
	SEMT_META_FIELD =		SEMT_META_VARIABLE | SEMT_META_PARAMETER,
	SEMT_META_TYPE =		SEMT_META_BUILTIN,
	SEMT_META_FUNCTION =	SEMT_META_FUNCTION_STATIC /*| SEMT_META_FUNCTION_METHOD | SEMT_META_FUNCTION_BUILTIN*/,
	SEMT_META_PARAMETER_PATH =	SEMT_META_PARAMETER | SEMT_IDPART,
	SEMT_META_VARIABLE_PATH =	SEMT_META_VARIABLE | SEMT_IDPART,
	
	SEMT_META_ANY =			SEMT_IDPART | SEMT_META_FIELD | SEMT_META_TYPE | SEMT_META_FUNCTION | SEMT_META_RVAL | SEMT_META_CTOR | SEMT_META_RESOLVE,
	SEMT_META_PATH =		SEMT_META_PARAMETER_PATH | SEMT_META_VARIABLE_PATH | SEMT_META_FUNCTION | SEMT_META_CLASS,
	
} SemanticType;

typedef uint64 SemanticTypePrimitive;

inline String GetSemanticTypeString(SemanticType t) {
	switch (t) {
		case SEMT_NULL:					return "null";
		case SEMT_NAMESPACE:			return "namespace";
		case SEMT_BUILTIN:				return "builtin";
		case SEMT_TYPEDEF:				return "typedef";
		case SEMT_CLASS_DECL:			return "class-declaration";
		case SEMT_CLASS:				return "class";
		case SEMT_CLASS_TEMPLATE:		return "class-template";
		case SEMT_FUNCTION_STATIC:		return "static function";
		case SEMT_FUNCTION_METHOD:		return "method function";
		case SEMT_VARIABLE:				return "variable";
		case SEMT_PARAMETER:			return "parameter";
		case SEMT_STATEMENT:			return "statement";
		case SEMT_STATEMENT_BLOCK:		return "statement-block";
		case SEMT_EXPR:					return "expression";
		case SEMT_CONSTANT:				return "constant";
		case SEMT_IDPART:				return "id-part";
		case SEMT_ROOT:					return "root";
		case SEMT_RESOLVE:				return "resolve";
		case SEMT_ARGUMENT:				return "argument";
		case SEMT_ARGUMENT_LIST:		return "argument-list";
		case SEMT_FUNCTION_BUILTIN:		return "builtin-function";
		case SEMT_MACHINE_DECL:			return "machine-declaration";
		case SEMT_MACHINE:				return "machine";
		case SEMT_CHAIN_DECL:			return "chain-decl";
		case SEMT_CHAIN:				return "chain";
		case SEMT_LOOP_DECL:			return "loop-decl";
		case SEMT_LOOP:					return "loop";
		case SEMT_FIELD:				return "field";
		case SEMT_TYPE:					return "type";
		case SEMT_FUNCTION:				return "function";
		case SEMT_UNDEFINED:			return "undefined";
		case SEMT_META_VARIABLE:		return "meta-variable";
		case SEMT_META_PARAMETER:		return "meta-parameter";
		case SEMT_META_BUILTIN:			return "meta-builtin";
		case SEMT_META_FUNCTION_STATIC:	return "meta static function";
		case SEMT_META_FIELD:			return "meta-field";
		case SEMT_WORLD:				return "world";
		case SEMT_ENTITY:				return "entity";
		case SEMT_COMPONENT:			return "component";
		case SEMT_SYSTEM:				return "system";
		case SEMT_POOL:					return "pool";
		case SEMT_ATOM:					return "atom";
		case SEMT_CALL_ARG:				return "call-arg";
		case SEMT_UNRESOLVED:			return "unresolved";
		case SEMT_META_CLASS:			return "meta-class";
		case SEMT_RVAL:					return "rval";
		case SEMT_CTOR:					return "ctor";
		case SEMT_ARRAYSIZE:			return "array-size";
		case SEMT_TYPE_POINTER:			return "type-pointer";
		case SEMT_TYPE_LREF:			return "type-lref";
		case SEMT_META_RVAL:			return "meta-rval";
		case SEMT_META_CTOR:			return "meta-ctor";
		case SEMT_OBJECT:				return "object";
		case SEMT_BLOCK:				return "block";
		case SEMT_META_RESOLVE:			return "meta-resolve";
		case SEMT_STATE:				return "state";
		case SEMT_DRIVER:				return "driver";
		case SEMT_ENGINE:				return "engine";
		case SEMT_SYMBOLIC_LINK:		return "symlink";
		default: return "invalid";
	}
}

inline bool IsTypedNode(SemanticType src) {
	return src & SEMT_TYPE;
}

inline bool IsMetaTypedNode(SemanticType src) {
	return src & SEMT_META_TYPE;
}

inline bool IsRvalReturn(SemanticType src) {
	return (int64)src & (int64)SEMT_WITH_RVAL_RET;
}

typedef enum {
	STMT_NULL,
	STMT_IF,
	STMT_ELSE,
	STMT_DOWHILE,
	STMT_WHILE,
	STMT_FOR,
	STMT_FOR_COND,
	STMT_FOR_POST,
	STMT_FOR_RANGE,
	STMT_BREAK,
	STMT_CONTINUE,
	STMT_CASE,
	STMT_DEFAULT,
	STMT_RETURN,
	STMT_SWITCH,
	STMT_BLOCK,
	STMT_EXPR,
	STMT_ATOM_CONNECTOR,
	STMT_CTOR,
	
	STMT_META_IF,
	STMT_META_ELSE,
	STMT_META_DOWHILE,
	STMT_META_WHILE,
	STMT_META_FOR,
	STMT_META_FOR_COND,
	STMT_META_FOR_POST,
	STMT_META_FOR_RANGE,
	STMT_META_BREAK,
	STMT_META_CONTINUE,
	STMT_META_CASE,
	STMT_META_DEFAULT,
	STMT_META_RETURN,
	STMT_META_SWITCH,
	STMT_META_BLOCK,
	STMT_META_EXPR,
	
	STMT_META_ANY = STMT_META_IF |
					STMT_META_ELSE |
					STMT_META_DOWHILE |
					STMT_META_WHILE |
					STMT_META_FOR |
					STMT_META_FOR_COND |
					STMT_META_FOR_POST |
					STMT_META_FOR_RANGE |
					STMT_META_BREAK |
					STMT_META_CONTINUE |
					STMT_META_CASE |
					STMT_META_DEFAULT |
					STMT_META_RETURN |
					STMT_META_SWITCH |
					STMT_META_BLOCK |
					STMT_META_EXPR,
} StmtType;

inline String GetStmtTypeString(StmtType t) {
	switch (t) {
		case STMT_NULL: return "null";
		case STMT_IF: return "if";
		case STMT_ELSE: return "else";
		case STMT_DOWHILE: return "do-while";
		case STMT_WHILE: return "while";
		case STMT_FOR: return "for";
		case STMT_FOR_COND: return "for-conditional";
		case STMT_FOR_POST: return "for-post";
		case STMT_FOR_RANGE: return "for-range";
		case STMT_BREAK: return "break";
		case STMT_CONTINUE: return "continue";
		case STMT_CASE: return "case";
		case STMT_DEFAULT: return "default";
		case STMT_RETURN: return "return";
		case STMT_SWITCH: return "switch";
		case STMT_BLOCK: return "block";
		case STMT_ATOM_CONNECTOR: return "atom-connector";
		case STMT_CTOR: return "ctor";
		case STMT_EXPR: return "expr";
		
		case STMT_META_IF: return "meta-if";
		case STMT_META_ELSE: return "meta-else";
		case STMT_META_DOWHILE: return "meta-do-while";
		case STMT_META_WHILE: return "meta-while";
		case STMT_META_FOR: return "meta-for";
		case STMT_META_FOR_COND: return "meta-for-conditional";
		case STMT_META_FOR_POST: return "meta-for-post";
		case STMT_META_FOR_RANGE: return "meta-for-range";
		case STMT_META_BREAK: return "meta-break";
		case STMT_META_CONTINUE: return "meta-continue";
		case STMT_META_CASE: return "meta-case";
		case STMT_META_DEFAULT: return "meta-default";
		case STMT_META_RETURN: return "meta-return";
		case STMT_META_SWITCH: return "meta-switch";
		case STMT_META_BLOCK: return "meta-block";
		case STMT_META_EXPR: return "meta-expr";
		
		default: return "invalid-type";
	}
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
	OP_NULL,
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
	OP_CALL,
	OP_SUBSCRIPT,
	
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
		case OP_GREQ: return "greater-or-equal";
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
		case OP_CALL: return "call";
		case OP_SUBSCRIPT: return "subscript";
		default: return "<invalid>";
	}
}

inline String GetOpCodeString(OpType t) {
	switch (t) {
		case OP_INC: return "++";
		case OP_DEC: return "--";
		case OP_POSTINC: return "++";
		case OP_POSTDEC: return "--";
		case OP_NEGATIVE: return "-";
		case OP_POSITIVE: return "+";
		case OP_NOT: return "!";
		case OP_NEGATE: return "~";
		case OP_ADD: return "+";
		case OP_SUB: return "-";
		case OP_MUL: return "*";
		case OP_DIV: return "/";
		case OP_MOD: return "%";
		case OP_LSH: return "<<";
		case OP_RSH: return ">>";
		case OP_GREQ: return ">=";
		case OP_LSEQ: return "<=";
		case OP_GREATER: return ">";
		case OP_LESS: return "<";
		case OP_EQ: return "==";
		case OP_INEQ: return "!=";
		case OP_BWAND: return "&";
		case OP_BWXOR: return "^";
		case OP_BWOR: return "|";
		case OP_AND: return "&&";
		case OP_OR: return "||";
		case OP_COND: return "?:";
		case OP_ASSIGN: return "=";
		case OP_ADDASS: return "+=";
		case OP_SUBASS: return "-=";
		case OP_MULASS: return "*=";
		case OP_DIVASS: return "/=";
		case OP_MODASS: return "%=";
		default: return "<invalid>";
	}
}


typedef enum {
	CONST_NULL,
	CONST_BOOL,
	CONST_INT32,
	CONST_INT64,
	CONST_DOUBLE,
	CONST_STRING,
} ConstType;

inline String GetConstString(ConstType t) {
	switch (t) {
		case CONST_NULL:	return "null";
		case CONST_BOOL:	return "bool";
		case CONST_INT32:	return "int32";
		case CONST_INT64:	return "int64";
		case CONST_DOUBLE:	return "double";
		case CONST_STRING:	return "string";
		default: return "invalid";
	}
}


enum {
	COOKIE_NULL,
	COOKIE_IF,
};

NAMESPACE_TOPSIDE_END

#endif
