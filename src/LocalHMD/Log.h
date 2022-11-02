#ifndef _LocalHMD_LOG_H
#define _LocalHMD_LOG_H


NAMESPACE_HMD_BEGIN


void* AllocateFn(Context* ctx, const char* e_msg, size_t size);
#define lhmd_alloc(_ctx, _size) AllocateFn(_ctx, "could not allocate " #_size " bytes of RAM @ " __FILE__ ":" HMD_STRINGIFY(__LINE__), _size)

#ifndef LOGLEVEL
#define LOGLEVEL 2
#endif

#define HMDLOG(_level, _levelstr, ...) do{ if(_level >= LOGLEVEL){String s; char buf[1024]; buf[0] = 0; snprintf(buf, 1024, "[%s] ", (_levelstr)); s << String((const char*)buf); buf[0] = 0; snprintf(buf, 1024, __VA_ARGS__); s << String((const char*)buf); LOG(s.Left(s.GetCount()-1)); } } while(0)

#if LOGLEVEL == 0
#define LOGD(...) HMDLOG(0, "DD", __VA_ARGS__)
#else
#define LOGD(...)
#endif

#define LOGV(...) HMDLOG(1, "VV", __VA_ARGS__)
#define LOGI(...) HMDLOG(2, "II", __VA_ARGS__)
#define LOGW(...) HMDLOG(3, "WW", __VA_ARGS__)
#define LOGE(...) HMDLOG(4, "EE", __VA_ARGS__)

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#define lhmd_set_error(_ctx, ...) { snprintf((_ctx)->error_msg, HMD_STR_SIZE, __VA_ARGS__); LOGE(__VA_ARGS__); }


NAMESPACE_HMD_END


#endif
