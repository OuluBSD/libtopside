#include "SerialLib.h"

NAMESPACE_UPP_BEGIN


INITBLOCK_(SerialLib) {
	
	#define ECS_CTX(dev, val, prefix) \
		TS::Parallel::Factory::RegisterInterfaceLink<TS::Parallel::DefaultExchangePoint>(TS::Parallel::DevCls::dev, TS::Parallel::ValCls::val);
	#define IFACE_CTX_CLS(dev, value, prefix) ECS_CTX(dev, value, prefix)
	#define IFACE(x) DEV_IFACE(x)
	IFACE_LIST
	#undef IFACE
	#undef IFACE_CTX_CLS
	#undef ECS_CTX
	
	GfxProgramLibrary::template AddProgramClass<Parallel::RendererBase>("the_renderer_program");
	
}

NAMESPACE_UPP_END
