#include "ChainCore.h"




void EonStream::Link(const char* c) {
	tmp_links.Clear();
	
	int src = -1;
	const char* a = c;
	for(int i = 0; *a && i < 1000; i++, a++) {
		if (src < 0)
			src = *a - '0';
		else {
			int dst = *a - '0';
			ASSERT(src >= 0 && src <= 9);
			ASSERT(dst >= 0 && dst <= 9);
			if (tmp_links.GetCount() <= src)
				tmp_links.SetCount(src+1, -1);
			tmp_links[src] = dst;
			src = -1;
		}
	}
	
	//DUMPC(tmp_links);
}
