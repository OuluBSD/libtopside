#ifndef _SerialCore_AtomStore_h_
#define _SerialCore_AtomStore_h_

NAMESPACE_SERIAL_BEGIN


template<class T> using SerialTypeMap = LinkedMap<SerialTypeCls, T>;


template<typename T, typename ProducerT, typename RefurbisherT>
class SerialFactory
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
    SerialTypeMap<ProducerT> producers;
    SerialTypeMap<RefurbisherT> refurbishers;
    
};


class AtomStore :
	public System<AtomStore>,
	public SerialFactory<AtomBase*, std::function<AtomBase*()>, std::function<void(AtomBase*)>>
{
	
	
public:
	using Main = Loop;
	using Base = AtomBase;
	SYS_RTTI(AtomStore)
    SYS_CTOR(AtomStore)
	SYS_DEF_VISIT
	
	
	using Parent = Machine;
	using Factory = SerialFactory<Base*, std::function<Base*()>, std::function<void(Base*)> >;
	template<typename T> using IsAtom = std::is_base_of<Base, T>;
	template<typename T> using IsConnector = std::is_base_of<Base, T>;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	AtomBase* CreateAtomTypeCls(TypeAtomCls cls);
	
	template<typename T>
	T* CreateAtom(CompCls cls) {
		static_assert(IsAtom<T>::value, "T should be a atom");
		
		TypeAtomCls t;
		t.side  = AsSerialTypeCls<T>(cls.side);
		auto it = SerialFactory::producers.Find(t.side);
		if (!it) {
			std::function<Base*()> p([] { return GetPool<T>().New();});
			std::function<void(Base*)> r([] (Base* b){ GetPool<T>().Return(CastPtr<T>(b));});
			SerialFactory::producers.Add(t.side) = p;
			SerialFactory::refurbishers.Add(t.side) = r;
		}
		
		return CastPtr<T>(CreateAtom(t));
	}
	
	void Clone(Main& dst, const Main& src);
	void ReturnAtom(Base* c);
	
	
private:
	
	Base* CreateAtom(TypeAtomCls cls);
	
};


NAMESPACE_SERIAL_END

#endif
