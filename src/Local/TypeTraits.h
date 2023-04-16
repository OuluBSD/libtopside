#ifndef _Local_TypeTraits_h_
#define _Local_TypeTraits_h_

NAMESPACE_TOPSIDE_BEGIN


inline String Demangle(const char* name) {
	#ifdef __GNUG__
	int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
    #endif
    return name;
}

#ifdef flagSTDRTTI
class TypeId :
	TYPE_WRAPPER,
	Moveable<TypeId>
{
	const RTTI* rtti = 0;
public:
	typedef TYPE_WRAPPER Wrap;
    using TYPE_WRAPPER_CTOR;
	
	TypeId() : Wrap(AsVoidTypeId()) {}
	TypeId(const TypeId& id) : Wrap(id) {}
	TypeId(const Wrap& w) : Wrap(w) {}
	TypeId(const RTTI& t) : Wrap(typeid(t)), rtti(&t) {}
	
	
    hash_t GetHashValue() const { return (hash_t)get().hash_code(); }
    char const* name() const { return get().name(); }
    String DemangledName() const {return Demangle(name());}
	String CleanDemangledName() const {
		String s(DemangledName());
		if (s.Find("TS::") == 0)
			s = s.Mid(6);
		return s;
	}
	
	void operator=(const TypeId& id) {Wrap::operator=(id);}
    bool operator==(TypeId const& other) const {return get() == other.get();}
    bool operator!=(TypeId const& other) const {return !(*this == other);}
    bool operator<(TypeId const& other) const {return get().before(other);}
    
};
#else
class TypeId : Moveable<TypeId>
{
	TypeCls type;
	const RTTI* rtti;
	
public:
	TypeId() : type(0) {}
	TypeId(const TypeId& id) : type(id.type), rtti(id.rtti) {}
	TypeId(const TypeCls& t) : type(t), rtti(0) {}
	TypeId(const RTTI& t) : type(t.GetTypeId()), rtti(&t) {}
	
	String DemangledName() const {return rtti ? String(rtti->GetDynamicName()) : ("Unknown" + HexStr(type));}
	String CleanDemangledName() const {return DemangledName();}
	
    hash_t GetHashValue() const { return (hash_t)type; }
	void operator=(const RTTI& id) {type = id.GetTypeId(); rtti = &id;}
	void operator=(const TypeId& id) {type = id.type;}
    bool operator==(const TypeId& other) const {return type == other.type;}
    bool operator!=(const TypeId& other) const {return type != other.type;}
    bool operator<(const TypeId& other) const {return type < other.type;}
    
    operator TypeCls() const {return type;}
    
};
#endif

template<class T> using TypeMap				= LinkedMap<TypeCls, T>;







template<typename T1, typename T2>
T1& AsRef(T2& val)
{
    static_assert(sizeof(T1) == sizeof(T2), "Sizes should be the same");
    return *reinterpret_cast<T1*>(&val);
}

template<typename T1, typename T2>
const T1& AsRef(const T2& val)
{
    static_assert(sizeof(T1) == sizeof(T2), "Sizes should be the same");
    return *reinterpret_cast<const T1*>(&val);
}

template<typename Container, typename Predicate>
void EraseIf(Container* container, Predicate&& predicate)
{
	for(int i = 0; i < container->GetCount(); i++) {
		if (predicate((*container)[i]))
			container->Remove(i--);
	}
    //container->Remove(RemoveIf(container->begin(), container->end(), Pick(predicate)), container->end());
}

class Destroyable :
	RTTIBase
{
public:
	RTTI_DECL0(Destroyable)
    virtual ~Destroyable() = default;

    virtual void Destroy() { destroyed = true; }
    virtual bool IsDestroyed() const { return destroyed; }

    template<typename Container>
    static void PruneFromContainer(Container& container)
    {
        auto it = container.begin();
        while(it) {
            if (it().IsDestroyed())
                it = container.Remove(it);
            else
                ++it;
        }
    }

protected:
    bool destroyed = false;
};


class Enableable :
	RTTIBase
{
public:
	RTTI_DECL0(Enableable)
    virtual ~Enableable() = default;

    virtual void SetEnabled(bool enable) { m_enabled = enable; }
    virtual bool IsEnabled() const { return m_enabled; }

protected:
    bool m_enabled{ true };
};


template<typename T, typename ProducerT, typename RefurbisherT>
class FactoryT
{
public:
    using Type = T;
    using Producer = ProducerT;
    using Refurbisher = RefurbisherT;

    void RegisterProducer(const TypeId& typeId, Producer producer, Refurbisher refurbisher)
    {
        auto p = producers.find(typeId);
        AssertFalse(p != producers.end(), "multiple registrations for the same type is not allowed");
        producers.insert(p, { typeId, pick<Producer>(producer) });
        
        auto r = refurbishers.find(typeId);
        AssertFalse(r != refurbishers.end(), "multiple registrations for the same type is not allowed");
        refurbishers.insert(r, { typeId, pick<Refurbisher>(refurbisher) });
    }

protected:
    TypeMap<ProducerT> producers;
    TypeMap<RefurbisherT> refurbishers;
    
};







template<bool...>
struct bool_pack;

template <typename Base, typename T>
using IsBaseOf = std::is_base_of<Base, T>;

template<bool... Bs>
using AllTrue = std::is_same<bool_pack<Bs..., true>, bool_pack<true, Bs...>>;


template <typename Base, typename... Ts>
using AllBaseOf = AllTrue<std::is_base_of<Base, Ts>::value...>;

template <typename To, typename... Ts>
using AllConvertibleTo = AllTrue<std::is_convertible<Ts, To>::value...>;

template <typename T, typename... Ts>
using AllSame = AllTrue<std::is_same<T, Ts>::value...>;

template <typename T, typename Base>
bool IsInstance(const Base& o) {return CastConstPtr<T>(&o) != 0;}


NAMESPACE_TOPSIDE_END

#endif
