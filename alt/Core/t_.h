#ifndef _Core_t__h_
#define _Core_t__h_

NAMESPACE_UPP_BEGIN


inline const char *t_GetLngString(const char *s) { return s; }
inline const char *t_(const char *s)  { return t_GetLngString(s); }
inline const char *tt_(const char *s) { return s; }


NAMESPACE_UPP_END

#endif
