#include "Oulu.h"

NAMESPACE_OULU_BEGIN

RefRoot* __cur_ref_root;

RefRoot::RefRoot() {
	ASSERT(!__cur_ref_root);
	__cur_ref_root = this;
	
}

RefRoot::~RefRoot() {
	if (__cur_ref_root == this)
		__cur_ref_root = 0;
}

bool RefRoot::Is() {
	return __cur_ref_root;
}

RefRoot& RefRoot::Get() {
	ASSERT(__cur_ref_root);
	return *__cur_ref_root;
}





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
	if (refs != 0)
		RuntimeDiagnostics::Static().OnRefError(this);
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
