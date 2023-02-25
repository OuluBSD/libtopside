#include "Core.h"

NAMESPACE_UPP_BEGIN


String GetLngString(const char *id)
{
	#if 1
	return id;
	#else
	Mutex::Lock __(slng);
	VectorMap<String, String>& map = sCurrentSLangMap();
	int q = map.Find(id);
	if(q >= 0)
		return map[q];
	String s = GetLngString_(GetCurrentLanguage(), id);
	map.Add(id, s);
	return s;
	#endif
}


NAMESPACE_UPP_END
