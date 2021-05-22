#ifndef _RTTI_RTTI_h_
#define _RTTI_RTTI_h_

#include <string.h>


namespace Upp {


typedef size_t TypeCls;
class RTTI;


#define RTTIBase virtual public RTTI

class RTTI {
public:
	RTTI& GetRTTI() {return *this;}
	const RTTI& GetRTTI() const {return *this;}
	
	
	virtual TypeCls GetTypeId() const = 0;
	
	virtual RTTI* GetTypeInfo(TypeCls) {return nullptr;}
	virtual const RTTI* GetTypeInfo(TypeCls) const {return nullptr;}
	virtual void* GetBasePtr(const char* id) const {return nullptr;}
	virtual void* GetBasePtr(TypeCls id) const {return nullptr;}
	
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


// Use just CastPtr etc.

/*
#define RTTICastable public RTTICaster

class RTTICaster :
	RTTIBase
{
public:
	
	template <typename T>
	T* Cast() {
		if (Is(T::TypeIdClass()))
			return (T*)this;
		
		return nullptr;
	}
	template <typename T>
	const T* Cast() const {
		if (Is(T::TypeIdClass()))
			return (T*)this;
		
		return nullptr;
	}
	
};*/

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

/*
#define RTTI_Static(Type)                                              \
    public:                                                            \
        static const char* GetTypeName() {return #Type;}               \
        static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
		void* GetBasePtr(const char* name) const override {return strcmp(name, #Type) == 0 ? this : 0;} \
		void* GetBasePtr(TypeCls id) const override {return id == TypeIdClass() ? this : 0;} \
		const Upp::RTTI* GetTypeInfo(TypeCls id) const override {return nullptr;} \
		Upp::RTTI* GetTypeInfo(TypeCls id) override {return nullptr;}
*/


#define IF_NAME(Type) if (strcmp(id, GetTypeName()) == 0) return (Type*)this;
#define RTTI_IF0(ret) if (id == TypeIdClass()) return ret;
#define RTTI_IF1(r, par, fn)  else if (r* t = par::fn(id)) return t;
#define RTTI_ELSE(x, fn) else return x::fn(id);

#define RTTI_DECL_0(Type, TypeString) \
	public: \
        static const char* GetTypeName() {return TypeString;} \
        static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {return TypeString;}\
        TypeCls GetTypeId() const override { \
			return Type::TypeIdClass(); \
		} \
        Upp::RTTI* GetTypeInfo(TypeCls id) override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_ELSE(RTTI, GetTypeInfo) \
        } \
        const Upp::RTTI* GetTypeInfo( TypeCls id ) const override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_ELSE(RTTI, GetTypeInfo) \
        } \
        void* GetBasePtr(TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_ELSE(RTTI, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_ELSE(RTTI, GetBasePtr) \
        } \
        


#define RTTI_DECL_1(Type, ParentType, TypeString)                      \
    public:                                                            \
        static const char* GetTypeName() {return TypeString;}          \
        static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {return TypeString;}\
        TypeCls GetTypeId() const override { \
			return Type::TypeIdClass(); \
		} \
        Upp::RTTI* GetTypeInfo(TypeCls id) override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_ELSE(ParentType, GetTypeInfo) \
        } \
        const Upp::RTTI* GetTypeInfo( TypeCls id ) const override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_ELSE(ParentType, GetTypeInfo) \
        } \
        void* GetBasePtr(TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_ELSE(ParentType, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_ELSE(ParentType, GetBasePtr) \
        }


#define RTTI_DECL_2(Type, ParentType0, ParentType1, TypeString)        \
    public:                                                            \
        static const char* GetTypeName() {return TypeString;}          \
        static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {return TypeString;}\
        TypeCls GetTypeId() const override { \
			return Type::TypeIdClass(); \
		}\
        Upp::RTTI* GetTypeInfo(TypeCls id) override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_ELSE(ParentType1, GetTypeInfo) \
        } \
        const Upp::RTTI* GetTypeInfo( TypeCls id ) const override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(const Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_ELSE(ParentType1, GetTypeInfo) \
        } \
        void* GetBasePtr(TypeCls id) const override { \
            RTTI_IF0((Type*)this) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_ELSE(ParentType1, GetBasePtr) \
        } \
        void* GetBasePtr(const char* id) const override { \
            IF_NAME(Type) \
            RTTI_IF1(void, ParentType0, GetBasePtr) \
            RTTI_ELSE(ParentType1, GetBasePtr) \
        }



#define RTTI_DECL_3(Type, ParentType0, ParentType1, ParentType2, TypeString)        \
    public:                                                            \
        static const char* GetTypeName() {return TypeString;}          \
        static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {return TypeString;}          \
        TypeCls GetTypeId() const override { \
			return Type::TypeIdClass();                                \
		} \
        Upp::RTTI* GetTypeInfo(TypeCls id) override {             \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(Upp::RTTI, ParentType1, GetTypeInfo) \
            RTTI_ELSE(ParentType2, GetTypeInfo) \
        } \
        const Upp::RTTI* GetTypeInfo( TypeCls id ) const override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(const Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(const Upp::RTTI, ParentType1, GetTypeInfo) \
            RTTI_ELSE(ParentType2, GetTypeInfo) \
        } \
        void* GetBasePtr(TypeCls id) const override { \
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
        }

#define RTTI_DECL_4(Type, ParentType0, ParentType1, ParentType2, ParentType3, TypeString)        \
    public:                                                            \
        static const char* GetTypeName() {return TypeString;}          \
        static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {return TypeString;}          \
        TypeCls GetTypeId() const override { \
			return Type::TypeIdClass();                                \
		} \
        Upp::RTTI* GetTypeInfo(TypeCls id) override {             \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(Upp::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(Upp::RTTI, ParentType2, GetTypeInfo) \
            RTTI_ELSE(ParentType3, GetTypeInfo) \
        } \
        const Upp::RTTI* GetTypeInfo( TypeCls id ) const override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(const Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(const Upp::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(const Upp::RTTI, ParentType2, GetTypeInfo) \
            RTTI_ELSE(ParentType3, GetTypeInfo) \
        } \
        void* GetBasePtr(TypeCls id) const override { \
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
        }

#define RTTI_DECL_5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4, TypeString)        \
    public:                                                            \
        static const char* GetTypeName() {return TypeString;}          \
        static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;} \
        const char* GetDynamicName() const override {return TypeString;}          \
        TypeCls GetTypeId() const override { \
			return Type::TypeIdClass();                                \
		} \
        Upp::RTTI* GetTypeInfo(TypeCls id) override {             \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(Upp::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(Upp::RTTI, ParentType2, GetTypeInfo) \
            RTTI_IF1(Upp::RTTI, ParentType3, GetTypeInfo) \
            RTTI_ELSE(ParentType4, GetTypeInfo) \
        } \
        const Upp::RTTI* GetTypeInfo( TypeCls id ) const override { \
            RTTI_IF0(&RTTI::GetRTTI()) \
            RTTI_IF1(const Upp::RTTI, ParentType0, GetTypeInfo) \
            RTTI_IF1(const Upp::RTTI, ParentType1, GetTypeInfo) \
            RTTI_IF1(const Upp::RTTI, ParentType2, GetTypeInfo) \
            RTTI_IF1(const Upp::RTTI, ParentType3, GetTypeInfo) \
            RTTI_ELSE(ParentType4, GetTypeInfo) \
        } \
        void* GetBasePtr(TypeCls id) const override { \
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
        }


#define RTTI_DECL0(Type) RTTI_DECL_0(Type, #Type)
#define RTTI_DECL1(Type, ParentType) RTTI_DECL_1(Type, ParentType, #Type)
#define RTTI_DECL2(Type, ParentType0, ParentType1) RTTI_DECL_2(Type, ParentType0, ParentType1, #Type)
#define RTTI_DECL3(Type, ParentType0, ParentType1, ParentType2) RTTI_DECL_3(Type, ParentType0, ParentType1, ParentType2, #Type)
#define RTTI_DECL4(Type, ParentType0, ParentType1, ParentType2, ParentType3) RTTI_DECL_4(Type, ParentType0, ParentType1, ParentType2, ParentType3, #Type)
#define RTTI_DECL5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4) RTTI_DECL_5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4, #Type)

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
