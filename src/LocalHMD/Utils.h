#ifndef _LocalHMD_UTILS_H
#define _LocalHMD_UTILS_H


NAMESPACE_HMD_BEGIN


static inline int CompareWString(const wchar_t *a, const wchar_t *b) {
	if (!a || !b)
		return 0;
	return wcscmp(a, b) == 0;
}


NAMESPACE_HMD_END


#endif
