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


NAMESPACE_TOPSIDE_END

#endif
