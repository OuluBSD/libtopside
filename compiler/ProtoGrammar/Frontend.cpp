#include "Grammar.h"


NAMESPACE_OULU_BEGIN
	




#define GRAMMAR_NAME Grammar
#define GRAMMAR_ENUMTYPE_FILE "Generated_EnumType_Grammar.inl"
#include "ParserImpl.inl"
#undef GRAMMAR_ENUMTYPE_FILE
#undef GRAMMAR_NAME



#define GRAMMAR_NAME Meta
#define GRAMMAR_ENUMTYPE_FILE "Generated_EnumType_Meta.inl"
#include "ParserImpl.inl"
#undef GRAMMAR_ENUMTYPE_FILE
#undef GRAMMAR_NAME







NAMESPACE_OULU_END
