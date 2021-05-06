#ifndef _EcsCore_Connector_h_
#define _EcsCore_Connector_h_

NAMESPACE_OULU_BEGIN



template <class T> inline Ref<T> ComponenBase_Static_As(ConnectorBase*) {return 0;}

struct ConnectorBase : Destroyable, Enableable, LockedScopeEnabler<ConnectorBase> {
	Pool* pool = NULL;
	virtual ~ConnectorBase() = default;

	virtual TypeId GetType() const = 0;
	virtual void CopyTo(ConnectorBase* component) const = 0;
	virtual void Update(double dt) = 0;
	virtual void UnlinkAll(bool forced) {};
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	virtual String ToString() const {return "<not implemented>";}
	
	static bool AllowDuplicates() {return false;}
	
public:
	Pool& GetPool() {ASSERT(pool); return *pool;}
	Pool* GetPoolPtr() const {return pool;}
	
	
};

typedef Ref<ConnectorBase> ConnectorRef;


template<typename T>
struct Connector : ConnectorBase {

	TypeId GetType() const override {
		return typeid(T);
	}
	
	void CopyTo(ConnectorBase* target) const override {
		ASSERT(target->GetType() == GetType());
	    
		*static_cast<T*>(target) = *static_cast<const T*>(this);
	}
};


typedef RefTypeMapIndirect<ConnectorBase> ConnectorMapBase;
typedef ArrayMap<TypeId, Ref<ConnectorBase>> ConnectorRefMap;

class ConnectorMap : public ConnectorMapBase {
	
	void ReturnConnector(ConnectorStore& s, ConnectorBase* c);
	
public:
	
	ConnectorMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename ConnectorT>
	Ref<ConnectorT> Get() {
		CXX2A_STATIC_ASSERT(IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		ConnectorMapBase::Iterator it = ConnectorMapBase::Find(typeid(ConnectorT));
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			throw Exc("Could not find component " + TypeId(typeid(ConnectorT)).CleanDemangledName());
		
		return it->AsRef<ConnectorT>();
	}
	
	template<typename ConnectorT>
	Ref<ConnectorT> Find() {
		CXX2A_STATIC_ASSERT(IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		ConnectorMapBase::Iterator it = ConnectorMapBase::Find(typeid(ConnectorT));
		if (IS_EMPTY_SHAREDPTR(it))
			return NULL;
		else
			return it->AsRef<ConnectorT>();
	}
	
	template<typename ConnectorT>
	Ref<ConnectorT> Add(ConnectorT* component) {
		CXX2A_STATIC_ASSERT(IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		const TypeId type = typeid(ConnectorT);
		ASSERT_(component->GetType() == type, "ConnectorRef type does not match T");
		
		ConnectorMapBase::Iterator it = ConnectorMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || ConnectorT::AllowDuplicates(), "Cannot have duplicate componnets");
		ConnectorRef cmp = ConnectorMapBase::Add(type, component);
		
		return Ref<ConnectorT>(component);
	}
	
	template<typename ConnectorT>
	void Remove(Ref<ConnectorStore> s) {
		CXX2A_STATIC_ASSERT(IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		ConnectorMapBase::Iterator iter = ConnectorMapBase::Find(typeid(ConnectorT));
		ASSERT_(iter, "Tried to remove non-existent component");
		
		iter.value().Uninitialize();
		iter.value().Destroy();
		
		ReturnConnector(*s, iter.value.GetItem()->value.Detach());
		ConnectorMapBase::Remove(iter);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};


NAMESPACE_OULU_END

#endif
