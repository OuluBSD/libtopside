#ifndef _TemplatesLib_Defs_h_
#define _TemplatesLib_Defs_h_

NAMESPACE_TOPSIDE_BEGIN


#define DEV(dev) \
	using dev##DevLibT							= ContextDevLibT<dev##Context>; \
	using dev##ContextComponent					= typename dev##DevLibT::ContextComponent; \
	using dev##ContextComponentRef				= RefT_Entity<dev##ContextComponent>; \
	PREFAB_BEGIN(Complete##dev) \
		dev##ContextComponent \
	PREFAB_END
DEV_LIST
#undef DEV


NAMESPACE_TOPSIDE_END

#endif
