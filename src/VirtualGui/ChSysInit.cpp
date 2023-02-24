#include "Local.h"

#if IS_UPP_CORE

#ifdef VIRTUALGUI

NAMESPACE_UPP

void ChSysInit()
{
	ChReset();
}

void ChHostSkin()
{
	ChSysInit();
}

bool IsSystemThemeDark()
{
	return false;
}

END_UPP_NAMESPACE

#endif
#endif
