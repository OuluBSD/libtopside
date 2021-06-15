#ifndef UTIL_H
#define UTIL_H

NAMESPACE_GLSL_BEGIN

// An implementation of std::find
template <typename I, typename T>
static inline I Find(I first, I last, const T &value) {
    for (; first != last; ++first)
        if (*first == value)
            return first;
    return last;
}

// An implementation of vasprintf
int allocvfmt(char **str, const char *fmt, va_list vp);

// An implementation of vsprintf
int allocfmt(char **str, const char *fmt, ...);


NAMESPACE_GLSL_END

#endif
