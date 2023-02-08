#ifndef _RTTI_RTTI_h_
#define _RTTI_RTTI_h_

#include <string.h>
#include <type_traits>


namespace UPP {


typedef size_t TypeCls;
class RTTI;


#define RTTIBase virtual public ::UPP::RTTI
template <class T>       ::UPP::RTTI& GetRTTIBase(T& o)       {return o;}
template <class T> const ::UPP::RTTI& GetRTTIBase(const T& o) {return o;}

class RTTI {
	
public:
	RTTI& GetRTTI() {return *this;}
	const RTTI& GetRTTI() const {return *this;}
	
	
	virtual TypeCls GetTypeId() const = 0;
	
	virtual RTTI* GetTypeInfo(TypeCls) {return nullptr;}
	virtual const RTTI* GetTypeInfo(TypeCls) const {return nullptr;}
	virtual void* GetBasePtr(const char* id) const {return nullptr;}
	virtual void* GetBasePtr(TypeCls id) const {return nullptr;}
	virtual void* GetBasePtrUnder(TypeCls id, void* mem) const {return nullptr;}
	virtual bool  GetBasePtrOver0(TypeCls id, void* mem, void*& ret) const {return (RTTI*)this == mem;}
	
    void* GetBasePtrOver(TypeCls id, void* mem) const {
        void* ret = 0;
        GetBasePtrOver0(id, mem, ret);
        return ret;
    }
    
	bool Is(TypeCls id) const {return GetBasePtr(id) != nullptr;}
	bool Is(const char* id) const {return GetBasePtr(id) != nullptr;}
	virtual const char* GetDynamicName() const {return "RTTI";}
	
	
	const char* name() const {return GetDynamicName();}
	size_t hash_code() const {return GetTypeId();}
	
	bool operator==(TypeCls t) const {return Is(t);}
	bool operator!=(TypeCls t) const {return !Is(t);}
	
	bool operator==(const RTTI& w) const;
	bool operator!=(const RTTI& w) const;
	bool before(const RTTI& w) const;
	
};

template <class T> TypeCls GetTypeIdClass() {return T::TypeIdClass();}
template <class T> const char* GetTypeNameT() {return T::GetTypeName();}

#if IS_TS_CORE
template<> inline TypeCls GetTypeIdClass<void>() {static int d = 0; return (size_t) &d;}
#endif

class RTTIWrapper {
	const RTTI* rtti;
	
public:
	RTTIWrapper(const RTTI& rtti) : rtti(&rtti) {}
	
	const RTTI& get() const {return *rtti;}
	
	void operator=(const RTTIWrapper& w) {rtti = w.rtti;}
	
	bool operator==(const RTTIWrapper& w) const {return rtti == w.rtti;}
	bool operator!=(const RTTIWrapper& w) const {return rtti != w.rtti;}
	
	operator const RTTI&() const {return *rtti;}
	
};


#define IF_NAME(Type) if (strcmp(id, GetTypeName()) == 0) return (Type*)this;
#define IF_MEM_UNDER(Type) if ((void*)(Type*)this == mem) {return Type::GetBasePtr(id);}
#define RTTI_IF0(ret) if (id == TypeIdClass()) return ret;
#define RTTI_IF1(r, par, fn)  else if (r* t = par::fn(id)) return t;
#define RTTI_IF1_MEM(r, par, fn)  else if (r* t = par::fn(id, mem)) return t;
#define RTTI_ELSE(x, fn) else return x::fn(id);
#define RTTI_ELSE_MEM(x, fn) else return x::fn(id, mem);
#define IF_MEM_OVER(Type) \
	if ((void*)(Type*)this == mem) {\
		if (id == TypeIdClass()) ret = (void*)(Type*)this;\
		return true;\
	}
#define RTTI_ELIF_OVER(Type, ParentType) \
	else if (ParentType::GetBasePtrOver0(id, mem, ret)) {\
		if (!ret && id == TypeIdClass()) ret = (void*)(Type*)this;\
		return true; \
	}
#define RTTI_ELSE_OVER else return false;
		
#define RTTI_STRING_FN(TypeString) const char* s = TypeString; return s;

#define RTTI_TYPEIDCLS static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}

#define RTTI_DECL_0(Type, TypeString) \
	public: \
        static const char* GetTypeName() {RTTI_STRING_FN(TypeString);} \
        static ::UPP::TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {RTTI_STRING_FN(TypeString);}\
        ::UPP::TypeCls GetTypeId() const override { \
			return Type::TypeIdClass(); \
		} \
        ::UPP::RTTI* GetTypeInfo(::UPP::TypeCls id) override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_ELSE(RTTI, GetTypeInfo) \
        } \
        const ::UPP::RTTI* GetTypeInfo( ::UPP::TypeCls id ) const override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_ELSE(RTTI, GetTypeInfo) \
        } \
        void* GetBasePtr(::UPP::TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_ELSE(RTTI, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_ELSE(RTTI, GetBasePtr) \
        } \
        void* GetBasePtrUnder(::UPP::TypeCls id, void* mem) const override { \
			IF_MEM_UNDER(Type) \
            RTTI_ELSE_MEM(RTTI, GetBasePtrUnder) \
        } \
        bool GetBasePtrOver0(::UPP::TypeCls id, void* mem, void*& ret) const override { \
			IF_MEM_OVER(Type) \
            RTTI_ELIF_OVER(Type, RTTI) \
            RTTI_ELSE_OVER \
        }


#define RTTI_DECL_1(Type, ParentType, TypeString)                      \
    public:                                                            \
		static_assert(std::is_convertible<Type*, ParentType*>(), "Invalid parent type"); \
        static const char* GetTypeName() {RTTI_STRING_FN(TypeString);}          \
        static ::UPP::TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {RTTI_STRING_FN(TypeString);}\
        ::UPP::TypeCls GetTypeId() const override { \
			return Type::TypeIdClass(); \
		} \
        ::UPP::RTTI* GetTypeInfo(::UPP::TypeCls id) override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_ELSE(ParentType, GetTypeInfo) \
        } \
        const ::UPP::RTTI* GetTypeInfo( ::UPP::TypeCls id ) const override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_ELSE(ParentType, GetTypeInfo) \
        } \
        void* GetBasePtr(::UPP::TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_ELSE(ParentType, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_ELSE(ParentType, GetBasePtr) \
        } \
        void* GetBasePtrUnder(::UPP::TypeCls id, void* mem) const override { \
			IF_MEM_UNDER(Type) \
            RTTI_ELSE_MEM(ParentType, GetBasePtrUnder) \
        } \
        bool GetBasePtrOver0(::UPP::TypeCls id, void* mem, void*& ret) const override { \
			IF_MEM_OVER(Type) \
            RTTI_ELIF_OVER(Type, ParentType) \
            RTTI_ELSE_OVER \
        }


#define RTTI_DECL_2(Type, ParentType0, ParentType1, TypeString)        \
    public:                                                            \
		static_assert(std::is_convertible<Type*, ParentType0*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType1*>(), "Invalid parent type"); \
        static const char* GetTypeName() {RTTI_STRING_FN(TypeString);}          \
        static ::UPP::TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {RTTI_STRING_FN(TypeString);}\
        ::UPP::TypeCls GetTypeId() const override { \
			return Type::TypeIdClass(); \
		}\
        ::UPP::RTTI* GetTypeInfo(::UPP::TypeCls id) override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(::UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_ELSE(ParentType1, GetTypeInfo) \
        } \
        const ::UPP::RTTI* GetTypeInfo( ::UPP::TypeCls id ) const override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(const ::UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_ELSE(ParentType1, GetTypeInfo) \
        } \
        void* GetBasePtr(::UPP::TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_ELSE(ParentType1, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_ELSE(ParentType1, GetBasePtr) \
        } \
        void* GetBasePtrUnder(::UPP::TypeCls id, void* mem) const override { \
			IF_MEM_UNDER(Type) \
            RTTI_IF1_MEM(void, ParentType0, GetBasePtrUnder) \
            RTTI_ELSE_MEM(ParentType1, GetBasePtrUnder) \
        } \
        bool GetBasePtrOver0(::UPP::TypeCls id, void* mem, void*& ret) const override { \
			IF_MEM_OVER(Type) \
            RTTI_ELIF_OVER(Type, ParentType0) \
            RTTI_ELIF_OVER(Type, ParentType1) \
            RTTI_ELSE_OVER \
        }



#define RTTI_DECL_3(Type, ParentType0, ParentType1, ParentType2, TypeString)        \
    public:                                                            \
		static_assert(std::is_convertible<Type*, ParentType0*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType1*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType2*>(), "Invalid parent type"); \
        static const char* GetTypeName() {RTTI_STRING_FN(TypeString);}          \
        static ::UPP::TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {RTTI_STRING_FN(TypeString);}          \
        ::UPP::TypeCls GetTypeId() const override { \
			return Type::TypeIdClass();                                \
		} \
        ::UPP::RTTI* GetTypeInfo(::UPP::TypeCls id) override {             \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(::UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(::UPP::RTTI, ParentType1, GetTypeInfo) \
            RTTI_ELSE(ParentType2, GetTypeInfo) \
        } \
        const ::UPP::RTTI* GetTypeInfo( ::UPP::TypeCls id ) const override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(const ::UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(const ::UPP::RTTI, ParentType1, GetTypeInfo) \
            RTTI_ELSE(ParentType2, GetTypeInfo) \
        } \
        void* GetBasePtr(::UPP::TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_IF1(void, ParentType1, GetBasePtr) \
            RTTI_ELSE(ParentType2, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_IF1(void, ParentType1, GetBasePtr) \
            RTTI_ELSE(ParentType2, GetBasePtr) \
        } \
        void* GetBasePtrUnder(::UPP::TypeCls id, void* mem) const override { \
			IF_MEM_UNDER(Type) \
            RTTI_IF1_MEM(void, ParentType0, GetBasePtrUnder) \
            RTTI_IF1_MEM(void, ParentType1, GetBasePtrUnder) \
            RTTI_ELSE_MEM(ParentType2, GetBasePtrUnder) \
        } \
        bool GetBasePtrOver0(::UPP::TypeCls id, void* mem, void*& ret) const override { \
			IF_MEM_OVER(Type) \
            RTTI_ELIF_OVER(Type, ParentType0) \
            RTTI_ELIF_OVER(Type, ParentType1) \
            RTTI_ELIF_OVER(Type, ParentType2) \
            RTTI_ELSE_OVER \
        }

#define RTTI_DECL_4(Type, ParentType0, ParentType1, ParentType2, ParentType3, TypeString)        \
    public:                                                            \
		static_assert(std::is_convertible<Type*, ParentType0*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType1*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType2*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType3*>(), "Invalid parent type"); \
        static const char* GetTypeName() {RTTI_STRING_FN(TypeString);}          \
        static ::UPP::TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {RTTI_STRING_FN(TypeString);}          \
        ::UPP::TypeCls GetTypeId() const override { \
			return Type::TypeIdClass();                                \
		} \
        ::UPP::RTTI* GetTypeInfo(::UPP::TypeCls id) override {             \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(::UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(::UPP::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(::UPP::RTTI, ParentType2, GetTypeInfo) \
            RTTI_ELSE(ParentType3, GetTypeInfo) \
        } \
        const ::UPP::RTTI* GetTypeInfo( ::UPP::TypeCls id ) const override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(const ::UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(const ::UPP::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(const ::UPP::RTTI, ParentType2, GetTypeInfo) \
            RTTI_ELSE(ParentType3, GetTypeInfo) \
        } \
        void* GetBasePtr(::UPP::TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_IF1(void, ParentType1, GetBasePtr) \
            RTTI_IF1(void, ParentType2, GetBasePtr) \
            RTTI_ELSE(ParentType3, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_IF1(void, ParentType1, GetBasePtr) \
            RTTI_IF1(void, ParentType2, GetBasePtr) \
            RTTI_ELSE(ParentType3, GetBasePtr) \
        } \
        void* GetBasePtrUnder(::UPP::TypeCls id, void* mem) const override { \
			IF_MEM_UNDER(Type) \
            RTTI_IF1_MEM(void, ParentType0, GetBasePtrUnder) \
            RTTI_IF1_MEM(void, ParentType1, GetBasePtrUnder) \
            RTTI_IF1_MEM(void, ParentType2, GetBasePtrUnder) \
            RTTI_ELSE_MEM(ParentType3, GetBasePtrUnder) \
        } \
        bool GetBasePtrOver0(::UPP::TypeCls id, void* mem, void*& ret) const override { \
			IF_MEM_OVER(Type) \
            RTTI_ELIF_OVER(Type, ParentType0) \
            RTTI_ELIF_OVER(Type, ParentType1) \
            RTTI_ELIF_OVER(Type, ParentType2) \
            RTTI_ELIF_OVER(Type, ParentType3) \
            RTTI_ELSE_OVER \
        }

#define RTTI_DECL_5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4, TypeString)        \
    public:                                                            \
		static_assert(std::is_convertible<Type*, ParentType0*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType1*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType2*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType3*>(), "Invalid parent type"); \
		static_assert(std::is_convertible<Type*, ParentType4*>(), "Invalid parent type"); \
        static const char* GetTypeName() {RTTI_STRING_FN(TypeString);}          \
        static ::UPP::TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {RTTI_STRING_FN(TypeString);}          \
        ::UPP::TypeCls GetTypeId() const override { \
			return Type::TypeIdClass();                                \
		} \
        ::UPP::RTTI* GetTypeInfo(UPP::TypeCls id) override {             \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(UPP::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(UPP::RTTI, ParentType2, GetTypeInfo) \
            RTTI_IF1(UPP::RTTI, ParentType3, GetTypeInfo) \
            RTTI_ELSE(ParentType4, GetTypeInfo) \
        } \
        const ::UPP::RTTI* GetTypeInfo( ::UPP::TypeCls id ) const override { \
            RTTI_IF0(&this->RTTI::GetRTTI()) \
            RTTI_IF1(const ::UPP::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(const ::UPP::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(const ::UPP::RTTI, ParentType2, GetTypeInfo) \
            RTTI_IF1(const ::UPP::RTTI, ParentType3, GetTypeInfo) \
            RTTI_ELSE(ParentType4, GetTypeInfo) \
        } \
        void* GetBasePtr(UPP::TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_IF1(void, ParentType1, GetBasePtr) \
            RTTI_IF1(void, ParentType2, GetBasePtr) \
            RTTI_IF1(void, ParentType3, GetBasePtr) \
            RTTI_ELSE(ParentType4, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_IF1(void, ParentType1, GetBasePtr) \
            RTTI_IF1(void, ParentType2, GetBasePtr) \
            RTTI_IF1(void, ParentType3, GetBasePtr) \
            RTTI_ELSE(ParentType4, GetBasePtr) \
        } \
        void* GetBasePtrUnder(UPP::TypeCls id, void* mem) const override { \
			IF_MEM_UNDER(Type) \
            RTTI_IF1_MEM(void, ParentType0, GetBasePtrUnder) \
            RTTI_IF1_MEM(void, ParentType1, GetBasePtrUnder) \
            RTTI_IF1_MEM(void, ParentType2, GetBasePtrUnder) \
            RTTI_IF1_MEM(void, ParentType3, GetBasePtrUnder) \
            RTTI_ELSE_MEM(ParentType4, GetBasePtrUnder) \
        } \
        bool GetBasePtrOver0(UPP::TypeCls id, void* mem, void*& ret) const override { \
			IF_MEM_OVER(Type) \
            RTTI_ELIF_OVER(Type, ParentType0) \
            RTTI_ELIF_OVER(Type, ParentType1) \
            RTTI_ELIF_OVER(Type, ParentType2) \
            RTTI_ELIF_OVER(Type, ParentType3) \
            RTTI_ELIF_OVER(Type, ParentType4) \
            RTTI_ELSE_OVER \
        }


#define RTTI_DECL0(Type) RTTI_DECL_0(Type, #Type)
#define RTTI_DECL1(Type, ParentType) RTTI_DECL_1(Type, ParentType, #Type)
#define RTTI_DECL2(Type, ParentType0, ParentType1) RTTI_DECL_2(Type, ParentType0, ParentType1, #Type)
#define RTTI_DECL3(Type, ParentType0, ParentType1, ParentType2) RTTI_DECL_3(Type, ParentType0, ParentType1, ParentType2, #Type)
#define RTTI_DECL4(Type, ParentType0, ParentType1, ParentType2, ParentType3) RTTI_DECL_4(Type, ParentType0, ParentType1, ParentType2, ParentType3, #Type)
#define RTTI_DECL5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4) RTTI_DECL_5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4, #Type)

#define RTTI_DECL0_(Type) RTTI_DECL0(Type)
#define RTTI_DECL1_(Type, ParentType) RTTI_DECL1(Type, ParentType)
#define RTTI_DECL2_(Type, ParentType0, ParentType1) RTTI_DECL2(Type, ParentType0, ParentType1)
#define RTTI_DECL3_(Type, ParentType0, ParentType1, ParentType2) RTTI_DECL3(Type, ParentType0, ParentType1, ParentType2)
#define RTTI_DECL4_(Type, ParentType0, ParentType1, ParentType2, ParentType3) RTTI_DECL4(Type, ParentType0, ParentType1, ParentType2, ParentType3)
#define RTTI_DECL5_(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4) RTTI_DECL5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4)

#define RTTI_DECL_T0(Type) RTTI_DECL_0(Type, TypeStringT(#Type))
#define RTTI_DECL_T1(Type, ParentType) RTTI_DECL_1(Type, ParentType, TypeStringT(#Type))
#define RTTI_DECL_T2(Type, ParentType0, ParentType1) RTTI_DECL_2(Type, ParentType0, ParentType1, TypeStringT(#Type))
#define RTTI_DECL_T3(Type, ParentType0, ParentType1, ParentType2) RTTI_DECL_3(Type, ParentType0, ParentType1, ParentType2, TypeStringT(#Type))
#define RTTI_DECL_T4(Type, ParentType0, ParentType1, ParentType2, ParentType3) RTTI_DECL_4(Type, ParentType0, ParentType1, ParentType2, ParentType3, TypeStringT(#Type))

#define RTTI_DECL_R0(Type) RTTI_DECL1(Type, LockedScopeRefCounter)
#define RTTI_DECL_R1(Type, ParentType) RTTI_DECL2(Type, ParentType, LockedScopeRefCounter)
#define RTTI_DECL_R2(Type, ParentType0, ParentType1) RTTI_DECL3(Type, ParentType0, ParentType1, LockedScopeRefCounter)
#define RTTI_DECL_R3(Type, ParentType0, ParentType1, ParentType2) RTTI_DECL4(Type, ParentType0, ParentType1, ParentType2, LockedScopeRefCounter)
#define RTTI_DECL_R4(Type, ParentType0, ParentType1, ParentType2, ParentType3) RTTI_DECL5(Type, ParentType0, ParentType1, ParentType2, ParentType3, LockedScopeRefCounter)

#define RTTI_DECL_TR0(Type) RTTI_DECL_1(Type, LockedScopeRefCounter, TypeStringT(#Type))
#define RTTI_DECL_TR1(Type, ParentType) RTTI_DECL_2(Type, ParentType, LockedScopeRefCounter, TypeStringT(#Type))
#define RTTI_DECL_TR2(Type, ParentType0, ParentType1) RTTI_DECL_3(Type, ParentType0, ParentType1, LockedScopeRefCounter, TypeStringT(#Type))
#define RTTI_DECL_TR3(Type, ParentType0, ParentType1, ParentType2) RTTI_DECL_4(Type, ParentType0, ParentType1, ParentType2, LockedScopeRefCounter, TypeStringT(#Type))
#define RTTI_DECL_TR4(Type, ParentType0, ParentType1, ParentType2, ParentType3) RTTI_DECL_4(Type, ParentType0, ParentType1, ParentType2, ParentType3, LockedScopeRefCounter, TypeStringT(#Type))


class DummyRTTI :
	RTTIBase
{
public:
	RTTI_DECL_1(DummyRTTI, RTTI, "<unknown>")
};


template <class> const RTTI& GetTypenameRTTI() {static DummyRTTI _; return _;}

}



#endif
