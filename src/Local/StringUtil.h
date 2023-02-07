#ifndef _Local_StringUtil_h_
#define _Local_StringUtil_h_

NAMESPACE_TOPSIDE_BEGIN


template<class T>
String BinStr(const T& o, const char* chrs=".|") {
	String s;
	int bytes = sizeof(T);
	const byte* b = (const byte*)&o;
	b += bytes-1;
	for(int i = bytes-1; i >= 0; i--) {
		for(int j = 7; j >= 0; j--) {
			bool bit = *b & (1 << j);
			s.Cat(chrs[bit ? 1 : 0]);
		}
		b--;
	}
	return s;
}


NAMESPACE_TOPSIDE_END

#endif
