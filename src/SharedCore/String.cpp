#include <Core/Core.h>

NAMESPACE_UPP


String FromCString(const char *s, const char *lim) {
	StringStream t;
	
	if (*s == '\"') {
		s++;
		lim--;
	}
	int i, j;
	int l = (int)(lim - s);
	char esc_char[] = { '\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\'};
	char essc_str[] = {  'a', 'b', 'f', 'n', 'r', 't', 'v', '\\'};
	for (i = 0;i < l;i++) {
		if (s[i] == '\\') {
			i++;
			for (j = 0; j < 8 ;j++) {
				if (s[i] == essc_str[j]) {
					t.Put(esc_char[j]);
					break;
				}
			}
			if (j == 8)
				t.Put(s[i]);
		}
		else {
			t.Put(s[i]);
		}
	}
	
	return t.GetResult();
}


END_UPP_NAMESPACE
