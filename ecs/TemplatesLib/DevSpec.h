#ifndef _TemplatesLib_DevSpec_h_
#define _TemplatesLib_DevSpec_h_

NAMESPACE_TOPSIDE_BEGIN


#define DEV(dev) \
	using dev##DevLibT							= ScopeDevLibT<dev##Spec>; \
	using dev##System							= typename dev##DevLibT::System; \
	using dev##Component						= typename dev##DevLibT::Component; \
	using dev##ContextComponent					= typename dev##DevLibT::ContextComponent; \
	using dev##ComponentGroup					= typename dev##DevLibT::ComponentGroup; \
	using dev##ContextComponentRef				= RefT_Entity<dev##ContextComponent>; \
	using dev##ComponentGroupRef				= RefT_Entity<dev##ComponentGroup>; \
	PREFAB_BEGIN(Complete##dev) \
		dev##ContextComponent \
	PREFAB_END
DEV_LIST
#undef DEV


NAMESPACE_TOPSIDE_END

#endif
