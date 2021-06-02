#ifndef _TemplatesMach_DevSpec_h_
#define _TemplatesMach_DevSpec_h_

NAMESPACE_TOPSIDE_BEGIN



#define DEV(x) \
	using x##MachT = ContextDevMachT<x##Spec>; \
	using x##Format = x##MachT::Format; \
	using x##Stream = x##MachT::Stream; \
	using x##CompConf = x##MachT::ComponentConf;
DEV_LIST
#undef DEV



NAMESPACE_TOPSIDE_END

#endif
