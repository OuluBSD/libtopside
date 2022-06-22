#ifndef _LittleLibrary_icxxabi_h_
#define _LittleLibrary_icxxabi_h_


// source http://wiki.osdev.org/C%2B%2B


#define ATEXIT_MAX_FUNCS	128

typedef unsigned uarch_t;

struct atexit_func_entry_t
{
	/*
	* Each member is at least 4 bytes large. Such that each entry is 12bytes.
	* 128 * 12 = 1.5KB exact.
	**/
	void (*destructor_func)(void *);
	void *obj_ptr;
	void *dso_handle;
};


void PanicAssert(const char *file, unsigned int line, const char *desc);


extern "C" {
	
	extern void *__dso_handle;
	
	int __cxa_atexit(void (*f)(void *), void *objptr, void *dso);
	
	
	typedef int _Unwind_Action;
	typedef unsigned _Unwind_Exception_Class;
	
	typedef enum
	{
	  _URC_NO_REASON = 0,
	  _URC_FOREIGN_EXCEPTION_CAUGHT = 1,
	  _URC_FATAL_PHASE2_ERROR = 2,
	  _URC_FATAL_PHASE1_ERROR = 3,
	  _URC_NORMAL_STOP = 4,
	  _URC_END_OF_STACK = 5,
	  _URC_HANDLER_FOUND = 6,
	  _URC_INSTALL_CONTEXT = 7,
	  _URC_CONTINUE_UNWIND = 8
	} _Unwind_Reason_Code;
	
	_Unwind_Reason_Code __gxx_personality_v0
	     (int, _Unwind_Action, _Unwind_Exception_Class,
	      struct _Unwind_Exception *, struct _Unwind_Context *);
	      
}

namespace std {

class type_info {
	const char* name;
	
public:
	type_info(const char* name) : name(name) {}
	
	const char* GetName() const {return name;}
	
};

}

namespace __cxxabiv1 {

typedef unsigned long ptrdiff_t;

class __class_type_info : public std::type_info {
public:
	explicit
	__class_type_info(const char *__n);
	
	virtual
	~__class_type_info();
	
	enum __sub_kind {
		__unknown = 0,
		__not_contained,
		__contained_ambig,
		__contained_virtual_mask ,
		__contained_public_mask,
		__contained_mask,
		__contained_private,
		__contained_public,
	};
	
	struct __upcast_result;
	struct __dyncast_result;
	
protected:
	virtual bool
	__do_upcast(const __class_type_info* __dst_type, void**__obj_ptr) const;
	
	virtual bool
	__do_catch(const type_info* __thr_type, void** __thr_obj,
			   unsigned __outer) const;
	           
public:
	virtual bool
	__do_upcast(const __class_type_info* __dst, const void* __obj,
				__upcast_result& __restrict __result) const;
	inline __sub_kind
	__find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
					  const __class_type_info* __src_type,
					  const void* __src_ptr) const;
	virtual bool
	__do_dyncast(ptrdiff_t __src2dst, __sub_kind __access_path,
				 const __class_type_info* __dst_type, const void* __obj_ptr,
				 const __class_type_info* __src_type, const void* __src_ptr,
				 __dyncast_result& __result) const;
	virtual __sub_kind
	__do_find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
			const __class_type_info* __src_type,
			const void* __src_ptr) const;
};


  
  
class __si_class_type_info : public __class_type_info {
	const __class_type_info *__base_type;
public:
	
	explicit
	__si_class_type_info(const char *__n, const __class_type_info *__base);
			
	virtual
	~__si_class_type_info();
	
protected:
	__si_class_type_info(const __si_class_type_info&);
	
	__si_class_type_info&
	operator=(const __si_class_type_info&);
	
	virtual bool
	__do_dyncast(ptrdiff_t __src2dst, __sub_kind __access_path,
				 const __class_type_info* __dst_type, const void* __obj_ptr,
				 const __class_type_info* __src_type, const void* __src_ptr,
				 __dyncast_result& __result) const;
	             
	virtual __sub_kind
	__do_find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
			const __class_type_info* __src_type,
			const void* __sub_ptr) const;
	        
	virtual bool
	__do_upcast(const __class_type_info*__dst, const void*__obj,
				__upcast_result& __restrict __result) const;
};



class __vmi_class_type_info : public __class_type_info {
public:
	unsigned int __flags;
	unsigned int __base_count;
	
	explicit
	__vmi_class_type_info(const char* __n, int ___flags);
			
	virtual
	~__vmi_class_type_info();
	
	enum __flags_masks {
		__non_diamond_repeat_mask = 0x1,
		__diamond_shaped_mask = 0x2,
		__flags_unknown_mask = 0x10
	};
	
protected:
	virtual bool
	__do_dyncast(ptrdiff_t __src2dst, __sub_kind __access_path,
				 const __class_type_info* __dst_type, const void* __obj_ptr,
				 const __class_type_info* __src_type, const void* __src_ptr,
				 __dyncast_result& __result) const;
	             
	virtual __sub_kind
	__do_find_public_src(ptrdiff_t __src2dst, const void* __obj_ptr,
			const __class_type_info* __src_type,
			const void* __src_ptr) const;
	        
	virtual bool
	__do_upcast(const __class_type_info* __dst, const void* __obj,
				__upcast_result& __restrict __result) const;
};


}


#endif
