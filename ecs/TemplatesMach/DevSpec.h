#ifndef _TemplatesMach_DevSpec_h_
#define _TemplatesMach_DevSpec_h_

NAMESPACE_TOPSIDE_BEGIN



#define DEV(x) \
	using x##MachT = ScopeDevMachT<x##Spec>; \
	using x##Format = x##MachT::DevFormat; \
	using x##StreamState = x##MachT::DevStreamState; \
	using x##CompConf = x##MachT::DevComponentConf;
DEV_LIST
#undef DEV



NAMESPACE_TOPSIDE_END

#endif
