#ifndef _ProtoGrammar_PostParser_h_
#define _ProtoGrammar_PostParser_h_

#ifndef flagBOOTSTRAP

NAMESPACE_OULU_BEGIN


#define GRAMMAR_NAME Grammar
#define GRAMMAR_FILE "Generated_GrammarPost.inl"
#define GRAMMAR_ENUM_BEGIN 20000
#include "PostParserHeader.inl"
#undef GRAMMAR_NAME
#undef GRAMMAR_FILE
#undef GRAMMAR_ENUM_BEGIN


}

#define IS_TYPE(n, type)		(n.GetType() == type)
#define REF_BLOCK				int block = n.GetBlock();
#define IS_BLOCK(i)				(block == i)
#define SUB(x)					(n[x])
#define DYN_INIT				int p = 0;
#define DYNSUB					(n[p])
#define INC_DYN					++p
#define IS_NOT_END				(p < n.GetCount())
#define IS_TYPE_SUBDYN(x)		(DYNSUB.GetType() == (x))
#define ASSERT_TYPE(n, x)		ASSERT(n.GetType() == (x))
#define ASSERT_COUNT(x)			ASSERT(n.GetCount() == (x))
#define ASSERT_COUNT_NONZERO	ASSERT(n.GetCount() > 0)
#define ADD_POST_ERROR(msg)		AddError(n.GetTokenLocation(), msg)
#define POST_TEST(x)			if (!(x)) return false;


#define SUB0						SUB(0)
#define SUB1						SUB(1)
#define SUB2						SUB(2)
#define SUB3						SUB(3)
#define SUB4						SUB(4)
#define SUB5						SUB(5)
#define SUB6						SUB(6)
#define SUB7						SUB(7)
#define SUB8						SUB(8)
#define SUB9						SUB(9)
#define SUB10						SUB(10)
#define SUB11						SUB(11)
#define SUB12						SUB(12)
#define SUB13						SUB(13)
#define SUB14						SUB(14)
#define SUB15						SUB(15)
#define SUB16						SUB(16)
#define SUB17						SUB(17)

#endif

#endif
