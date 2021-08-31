#ifndef _SerialCore_AtomStore_h_
#define _SerialCore_AtomStore_h_

NAMESPACE_SERIAL_BEGIN


template<class T> using SerialTypeMap	= LinkedMap<SerialTypeCls, T>;
template<class T> using AtomTypeMap		= LinkedMap<AtomTypeCls, T>;


template<typename T, typename ProducerT, typename RefurbisherT>
class AtomFactory
{
public:
    using Type = T;
    using Producer = ProducerT;
    using Refurbisher = RefurbisherT;
	
    void RegisterProducer(const SerialTypeCls& typeId, Producer producer, Refurbisher refurbisher)
    {
        auto p = producers.find(typeId);
        AssertFalse(p != producers.end(), "multiple registrations for the same type is not allowed");
        producers.insert(p, { typeId, pick<Producer>(producer) });
        
        auto r = refurbishers.find(typeId);
        AssertFalse(r != refurbishers.end(), "multiple registrations for the same type is not allowed");
        refurbishers.insert(r, { typeId, pick<Refurbisher>(refurbisher) });
    }
	
protected:
    AtomTypeMap<ProducerT> producers;
    AtomTypeMap<RefurbisherT> refurbishers;
    
};


class AtomStore :
	public System<AtomStore>,
	public AtomFactory<AtomBase*, std::function<AtomBase*()>, std::function<void(AtomBase*)>>
{
	
	
public:
	using Main = Loop;
	using Base = AtomBase;
	SYS_RTTI(AtomStore)
    SYS_CTOR(AtomStore)
	SYS_DEF_VISIT
	
	
	using Parent = Machine;
	using Factory = AtomFactory<Base*, std::function<Base*()>, std::function<void(Base*)> >;
	template<typename T> using IsAtom = std::is_base_of<Base, T>;
	template<typename T> using IsConnector = std::is_base_of<Base, T>;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	AtomBase* CreateAtomTypeCls(AtomTypeCls cls);
	
	template<typename T>
	T* CreateAtom(AtomTypeCls t) {
		static_assert(IsAtom<T>::value, "T should be a atom");
		
		//t.iface.side  = AsSerialTypeCls<T>(cls.side);
		
		auto it = AtomFactory::producers.Find(t);
		if (!it) {
			std::function<Base*()> p([] { return GetPool<T>().New();});
			std::function<void(Base*)> r([] (Base* b){ GetPool<T>().Return(CastPtr<T>(b));});
			AtomFactory::producers.Add(t) = p;
			AtomFactory::refurbishers.Add(t) = r;
		}
		
		return CastPtr<T>(CreateAtom(t));
	}
	
	//void Clone(Main& dst, const Main& src);
	void ReturnAtom(Base* c);
	
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::ATOM_STORE;}
	
	
private:
	
	Base* CreateAtom(AtomTypeCls cls);
	
};


NAMESPACE_SERIAL_END

#endif