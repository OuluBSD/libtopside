#ifndef _SerialMach_LinkStore_h_
#define _SerialMach_LinkStore_h_

NAMESPACE_SERIAL_BEGIN


template<class T> using LinkTypeMap		= LinkedMap<LinkTypeCls, T>;


template<typename T, typename ProducerT, typename RefurbisherT>
class LinkFactory
{
public:
    using Type = T;
    using Producer = ProducerT;
    using Refurbisher = RefurbisherT;
	
    void RegisterProducer(const ParallelTypeCls& typeId, Producer producer, Refurbisher refurbisher)
    {
        auto p = producers.find(typeId);
        AssertFalse(p != producers.end(), "multiple registrations for the same type is not allowed");
        producers.insert(p, { typeId, pick<Producer>(producer) });
        
        auto r = refurbishers.find(typeId);
        AssertFalse(r != refurbishers.end(), "multiple registrations for the same type is not allowed");
        refurbishers.insert(r, { typeId, pick<Refurbisher>(refurbisher) });
    }
	
protected:
    LinkTypeMap<ProducerT> producers;
    LinkTypeMap<RefurbisherT> refurbishers;
    
};


class LinkStore :
	public System<LinkStore>,
	public LinkFactory<LinkBase*, std::function<LinkBase*()>, std::function<void(LinkBase*)>>
{
	
	
public:
	using Main = Space;
	using Base = LinkBase;
	SYS_RTTI(LinkStore)
    SYS_CTOR(LinkStore)
	SYS_DEF_VISIT
	
	
	using Factory = LinkFactory<Base*, std::function<Base*()>, std::function<void(Base*)> >;
	template<typename T> using IsLink = std::is_base_of<Base, T>;
	template<typename T> using IsConnector = std::is_base_of<Base, T>;
	
	template <class T>
	static inline RecyclerPool<T>& GetPool() {static RecyclerPool<T> p; return p;}
	
	
	LinkBase* CreateLinkTypeCls(LinkTypeCls cls);
	
	template<typename T>
	T* CreateLink(LinkTypeCls t) {
		static_assert(IsLink<T>::value, "T should be a atom");
		
		auto it = LinkFactory::producers.Find(t);
		if (!it) {
			std::function<Base*()> p([] { return GetPool<T>().New();});
			std::function<void(Base*)> r([] (Base* b){ GetPool<T>().Return(CastPtr<T>(b));});
			LinkFactory::producers.Add(t) = p;
			LinkFactory::refurbishers.Add(t) = r;
		}
		
		return CastPtr<T>(CreateLink(t));
	}
	
	void ReturnLink(Base* c);
	
	
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::ATOM_STORE;}
	
	
private:
	
	Base* CreateLink(LinkTypeCls cls);
	
};


NAMESPACE_SERIAL_END

#endif
