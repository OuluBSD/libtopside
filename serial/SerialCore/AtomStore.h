#ifndef _SerialCore_AtomStore_h_
#define _SerialCore_AtomStore_h_

NAMESPACE_SERIAL_BEGIN


class AtomStore : public System<AtomStore> {
	
	
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
	
	
	AtomBase* CreateAtomTypeCls(TypeCompCls cls);
	
	template<typename T>
	T* CreateAtom(CompCls cls) {
		static_assert(IsAtom<T>::value, "T should be a atom");
		
		TypeCompCls t;
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
	
	static SerialTypeCls::Type		GetSerialType() {return SerialTypeCls::SYS_COMPONENTSTORE;}
	
private:
	
	Base* CreateAtom(TypeCompCls cls);
	
};


NAMESPACE_SERIAL_END

#endif
