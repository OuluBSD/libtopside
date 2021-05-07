#include "Oulu.h"

NAMESPACE_OULU_BEGIN

LockedScopeRefCounter::LockedScopeRefCounter()
#ifdef flagDEBUG_STACK
: dbg_type(typeid(LockedScopeRefCounter))
#endif
{
	refs = 0;
}

LockedScopeRefCounter::~LockedScopeRefCounter() {
	#ifdef flagDEBUG_STACK
	if (dbg_referencing && refs != 0)
		DBG_REF_NONZERO_ERROR;
	#endif
	ASSERT(refs == 0);
}

void LockedScopeRefCounter::IncRef() {
	#ifdef flagDEBUG_STACK
	if (dbg_referencing)
		DBG_REF_INC;
	#endif
	++refs;
}
void LockedScopeRefCounter::DecRef() {
	#ifdef flagDEBUG_STACK
	if (dbg_referencing)
		DBG_REF_DEC;
	#endif
	ASSERT(refs > 0);
	--refs;
}

NAMESPACE_OULU_END
