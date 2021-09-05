#include "ChainCore.h"

NAMESPACE_PLAN_BEGIN


void GetKeyValDevUpper(String key, String& dev, String& val) {
	String tmp;
	int j = 0;
	for(int i = 0; i < key.GetCount(); i++) {
		int chr = key[i];
		if (!tmp.IsEmpty()) {
			if (IsUpper(chr)) {
				if (j == 0) dev = tmp;
				else if (j == 1) val = tmp;
				tmp.Clear();
				++j;
			}
		}
		tmp.Cat(ToUpper(chr));
	}
	if (val.IsEmpty() && tmp.GetCount())
		val = ToUpper(tmp);
	ASSERT(!dev.IsEmpty());
	ASSERT(!val.IsEmpty());
}


NAMESPACE_PLAN_END
