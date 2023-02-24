#ifndef _SharedCore_RTTIDummy_h_
#define _SharedCore_RTTIDummy_h_

#ifdef UPP_VERSION
#define flagSTDRTTI
#define flagSTDEXC
#endif

NAMESPACE_UPP


#ifdef flagSTDRTTI
struct RTTI;
class Nuller;

struct TypeCls : std::reference_wrapper<const std::type_info> {
	using ti = std::reference_wrapper<const std::type_info>;
	TypeCls() : ti(typeid(void)) {}
	TypeCls(const TypeCls& t) : ti(t) {}
	TypeCls(const ti& t) : ti(t) {}
	TypeCls(const std::type_info& t) : ti(t) {}
	void operator=(const Nuller&) {ti::operator=(typeid(void));}
	void operator=(const TypeCls& t) {ti::operator=(t);}
	void operator=(const RTTI& t);
	hash_t GetHashValue() const {return ti::get().hash_code();}
	bool operator==(const TypeCls& t) const {return GetHashValue() == t.GetHashValue();}
	bool operator!=(const TypeCls& t) const {return GetHashValue() != t.GetHashValue();}
};

struct RTTI {
	RTTI& GetRTTI() {return *this;}
	const RTTI& GetRTTI() const {return *this;}
	
	virtual TypeCls GetTypeId() const {return TypeCls();}
	virtual const char* GetDynamicName() const {return "<unknown>";}
	
};

inline void TypeCls::operator=(const RTTI& t) {ti::operator=(typeid(t));}

template <class T> TypeCls AsTypeCls() {return typeid(T);}
template <class T> TypeCls AsTypeId(const T& o) {return typeid(T);}
template <class T> const char* AsTypeName() {return typeid(T).name();}
#define AsVoidTypeId() typeid(void)
#define AsVoidTypeCls() typeid(void)

template <class T> TypeCls GetTypeIdClass() {return typeid(T);}
template <class T> const char* GetTypeNameT() {return typeid(T).name();}

#endif



#ifdef flagSTDEXC
	template <class T> void Throw(const T& o) {throw o;}
	#define THROW_SPECIFIER		throw()
	#define THROW(x)			{throw(x);}
	#define TYPE_WRAPPER		std::reference_wrapper<const std::type_info>
	#define TYPE_WRAPPER_CTOR	reference_wrapper::reference_wrapper
#else
	#ifdef flagSTDRTTI
		#error STDEXC flag must be set with STDRTTI flag
	#endif
	template <class T> void Throw(const T& o) {const char* name = AsTypeName<T>(); __BREAK__;}
	#define THROW_SPECIFIER
	#define THROW(x)			{UPP::Throw(x); UNREACHABLE;}
	#define TYPE_WRAPPER		RTTIWrapper
	#define TYPE_WRAPPER_CTOR	RTTIWrapper::RTTIWrapper
#endif




// RTTI replacement

#ifdef flagSTDRTTI
#define RTTIBase virtual public RTTI

#define DEF_RTTI \
	TypeCls GetTypeId() const override {return typeid(*this);} \
	const char* GetDynamicName() const override {return typeid(*this).name();}

#define DEF_RTTI_ \
	virtual TypeCls GetTypeId() const {return typeid(*this);} \
	virtual const char* GetDynamicName() const {return typeid(*this).name();}

#define RTTI_DECL0(Type) DEF_RTTI
#define RTTI_DECL1(Type, ParentType) DEF_RTTI
#define RTTI_DECL2(Type, ParentType0, ParentType1) DEF_RTTI
#define RTTI_DECL3(Type, ParentType0, ParentType1, ParentType2) DEF_RTTI
#define RTTI_DECL4(Type, ParentType0, ParentType1, ParentType2, ParentType3) DEF_RTTI
#define RTTI_DECL5(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4) DEF_RTTI

#define RTTI_DECL0_(Type) DEF_RTTI_
#define RTTI_DECL1_(Type, ParentType) DEF_RTTI_
#define RTTI_DECL2_(Type, ParentType0, ParentType1) DEF_RTTI_
#define RTTI_DECL3_(Type, ParentType0, ParentType1, ParentType2) DEF_RTTI_
#define RTTI_DECL4_(Type, ParentType0, ParentType1, ParentType2, ParentType3) DEF_RTTI_
#define RTTI_DECL5_(Type, ParentType0, ParentType1, ParentType2, ParentType3, ParentType4) DEF_RTTI_

#define RTTI_DECL_T0(Type) DEF_RTTI
#define RTTI_DECL_T1(Type, ParentType) DEF_RTTI
#define RTTI_DECL_T2(Type, ParentType0, ParentType1) DEF_RTTI
#define RTTI_DECL_T3(Type, ParentType0, ParentType1, ParentType2) DEF_RTTI
#define RTTI_DECL_T4(Type, ParentType0, ParentType1, ParentType2, ParentType3) DEF_RTTI

#define RTTI_DECL_R0(Type) DEF_RTTI
#define RTTI_DECL_R1(Type, ParentType) DEF_RTTI
#define RTTI_DECL_R2(Type, ParentType0, ParentType1) DEF_RTTI
#define RTTI_DECL_R3(Type, ParentType0, ParentType1, ParentType2) DEF_RTTI
#define RTTI_DECL_R4(Type, ParentType0, ParentType1, ParentType2, ParentType3) DEF_RTTI

#define RTTI_DECL_TR0(Type) DEF_RTTI
#define RTTI_DECL_TR1(Type, ParentType) DEF_RTTI
#define RTTI_DECL_TR2(Type, ParentType0, ParentType1) DEF_RTTI
#define RTTI_DECL_TR3(Type, ParentType0, ParentType1, ParentType2) DEF_RTTI
#define RTTI_DECL_TR4(Type, ParentType0, ParentType1, ParentType2, ParentType3) DEF_RTTI

#endif




#ifdef flagSTDRTTI
#ifdef NTL_MOVEABLE
	NTL_MOVEABLE(TypeCls)
#endif
template <class T, class S> T*			CastPtr(S* o) {
	return dynamic_cast<T*>(o);
}

template <class T, class S> const T*	CastConstPtr(const S* o) {
	return dynamic_cast<const T*>(o);
}

template <class T, class S> T&			CastRef(S& o) {
	return dynamic_cast<T&>(o);
}

template <class T, class S> const T&	CastConstRef(const S& o) {
	return dynamic_cast<const T&>(o);
}

template <class T, class S> T&			CastRef(S* o) {
	return dynamic_cast<T&>(*o);
}

template <class T, class S> const T&	CastConstRef(const S* o) {
	return dynamic_cast<const T&>(*o);
}
#endif

END_UPP_NAMESPACE

#endif
