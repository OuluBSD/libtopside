#ifndef _TemplatesLib_DevSpec_h_
#define _TemplatesLib_DevSpec_h_

NAMESPACE_TOPSIDE_BEGIN


#define DEV(dev) \
	using dev##DevLibT							= ScopeDevLibT<dev##Spec>; \
	using dev##System							= typename dev##DevLibT::DevSystem; \
	using dev##Component						= typename dev##DevLibT::StageComponent; \
	using dev##StageContextConnector			= typename dev##DevLibT::StageContextConnector; \
	using dev##ContextConnector					= typename dev##DevLibT::DevContextConnector; \
	using dev##ComponentGroup					= typename dev##DevLibT::StageComponentGroup; \
	using dev##StageContextConnectorRef			= RefT_Entity<dev##StageContextConnector>; \
	using dev##ContextConnectorRef				= RefT_Entity<dev##ContextConnector>; \
	using dev##ComponentGroupRef				= RefT_Entity<dev##ComponentGroup>;
DEV_LIST
#undef DEV


NAMESPACE_TOPSIDE_END

#endif
