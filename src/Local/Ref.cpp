#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

bool __dbg_ref_visits;
bool IsDebugRefVisits() {return __dbg_ref_visits;}
void SetDebugRefVisits(bool b) {__dbg_ref_visits = b;}



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
: dbg_type(AsTypeId(LockedScopeRefCounter))
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


NAMESPACE_TOPSIDE_END
