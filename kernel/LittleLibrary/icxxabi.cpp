#include "icxxabi.h"


void *__dso_handle = 0;

atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
uarch_t __atexit_func_count = 0;

int __cxa_atexit(void (*f)(void *), void *objptr, void *dso)
{
	if (__atexit_func_count >= ATEXIT_MAX_FUNCS) {return -1;};
	__atexit_funcs[__atexit_func_count].destructor_func = f;
	__atexit_funcs[__atexit_func_count].obj_ptr = objptr;
	__atexit_funcs[__atexit_func_count].dso_handle = dso;
	__atexit_func_count++;
	return 0; /*I would prefer if functions returned 1 on success, but the ABI says...*/
};

extern "C" {
	void _Unwind_Resume() {
		PanicAssert(__FILE__, __LINE__, "Trying to unwind, but standard exceptions are not supported.");
	}
	
	_Unwind_Reason_Code __gxx_personality_v0
	     (int, _Unwind_Action, _Unwind_Exception_Class,
	      struct _Unwind_Exception *, struct _Unwind_Context *) {
		return _URC_NO_REASON;
	}
}


namespace __cxxabiv1 {




__class_type_info::__class_type_info(const char *__n) : type_info(__n) {}

__class_type_info::~__class_type_info() {}

bool __class_type_info::__do_upcast(const __class_type_info* __dst_type, void**__obj_ptr) const {return false;}

bool __class_type_info::__do_catch(const type_info* __thr_type, void** __thr_obj, unsigned __outer) const {return false;}

bool __class_type_info::__do_upcast(const __class_type_info* __dst, const void* __obj,
			__upcast_result& __restrict __result) const {return false;}
			
__class_type_info::__sub_kind __class_type_info::__find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
				  const __class_type_info* __src_type,
				  const void* __src_ptr) const {return __unknown;}
				  
bool __class_type_info::__do_dyncast(ptrdiff_t __src2dst, __sub_kind __access_path,
			 const __class_type_info* __dst_type, const void* __obj_ptr,
			 const __class_type_info* __src_type, const void* __src_ptr,
			 __dyncast_result& __result) const {return false;}
			 
__class_type_info::__sub_kind __class_type_info::__do_find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
		const __class_type_info* __src_type,
		const void* __src_ptr) const {return __sub_kind();}






__si_class_type_info::__si_class_type_info(const char *__n, const __class_type_info *__base) : __class_type_info(__n), __base_type(__base) {}
		
__si_class_type_info::~__si_class_type_info() {}

__si_class_type_info::__si_class_type_info(const __si_class_type_info& c) : __class_type_info(c.GetName()), __base_type(c.__base_type) {}

__si_class_type_info& __si_class_type_info::operator=(const __si_class_type_info&) {return *this;}

bool __si_class_type_info::__do_dyncast(ptrdiff_t __src2dst, __sub_kind __access_path,
			 const __class_type_info* __dst_type, const void* __obj_ptr,
			 const __class_type_info* __src_type, const void* __src_ptr,
			 __dyncast_result& __result) const {return false;}
             
__si_class_type_info::__sub_kind __si_class_type_info::__do_find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
		const __class_type_info* __src_type,
		const void* __sub_ptr) const {return __unknown;}
        
bool __si_class_type_info::__do_upcast(const __class_type_info*__dst, const void*__obj,
			__upcast_result& __restrict __result) const {return false;}






__vmi_class_type_info::__vmi_class_type_info(const char* __n, int ___flags)
		: __class_type_info(__n), __flags(___flags), __base_count(0) { }
		
__vmi_class_type_info::~__vmi_class_type_info() {}

bool __vmi_class_type_info::__do_dyncast(ptrdiff_t __src2dst, __sub_kind __access_path,
			 const __class_type_info* __dst_type, const void* __obj_ptr,
			 const __class_type_info* __src_type, const void* __src_ptr,
			 __dyncast_result& __result) const {return false;}
             
__vmi_class_type_info::__sub_kind __vmi_class_type_info::__do_find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
		const __class_type_info* __src_type,
		const void* __src_ptr) const {return __sub_kind();}
        
bool __vmi_class_type_info::__do_upcast(const __class_type_info* __dst, const void* __obj,
			__upcast_result& __restrict __result) const {return false;}

}
