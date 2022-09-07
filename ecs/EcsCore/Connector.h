#ifndef _EcsCore_Connector_h_
#define _EcsCore_Connector_h_

NAMESPACE_TOPSIDE_BEGIN



template <class T> inline RefT_Pool<T> ConnectorBase_Static_As(ConnectorBase*) {return 0;}

class ConnectorBase :
	public Destroyable,
	public Enableable,
	public RefScopeEnabler<ConnectorBase,Pool>
{
	
public:
	virtual TypeCls GetType() const = 0;
	virtual void CopyTo(ConnectorBase* component) const = 0;
	virtual void Update(double dt) = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0;
	virtual void UnlinkAll() {};
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	
	static bool AllowDuplicates() {return false;}
	
public:
	RTTI_DECL_R2(ConnectorBase, Destroyable, Enableable)
	ConnectorBase();
	virtual ~ConnectorBase();
	
	PoolRef GetPool();
	
	virtual String ToString() const;
	
};



template<typename T>
struct Connector :
	virtual ConnectorBase
{
	RTTI_DECL_R1(Connector, ConnectorBase)

	TypeCls GetType() const override {
		return AsTypeCls<T>();
	}
	
	void CopyTo(ConnectorBase* target) const override {
		ASSERT(target->GetType() == GetType());
	    
		CastRef<T>(target) = CastRef<const T>(this);
	}
};

#define CONN_RTTI(x)  RTTI_DECL1(x, Connector<x>)


class ConnectorMap : public ConnectorMapBase {
	
	void ReturnConnector(ConnectorStore& s, ConnectorBase* c);
	
public:
	
	ConnectorMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename ConnectorT>
	RefT_Pool<ConnectorT> Get() {
		CXX2A_STATIC_ASSERT(ConnectorStore::IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		ConnectorMapBase::Iterator it = ConnectorMapBase::Find(AsTypeCls<ConnectorT>());
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			THROW(Exc("Could not find component " + AsTypeString<ConnectorT>()));
		
		return it->AsRef<ConnectorT>();
	}
	
	template<typename ConnectorT>
	RefT_Pool<ConnectorT> Find() {
		CXX2A_STATIC_ASSERT(ConnectorStore::IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		ConnectorMapBase::Iterator it = ConnectorMapBase::Find(AsTypeCls<ConnectorT>());
		if (IS_EMPTY_SHAREDPTR(it))
			return RefT_Pool<ConnectorT>();
		else
			return it->AsRef<ConnectorT>();
	}
	
	template<typename ConnectorT>
	void Add(ConnectorT* component) {
		CXX2A_STATIC_ASSERT(ConnectorStore::IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		TypeCls type = AsTypeCls<ConnectorT>();
		ASSERT_(component->GetType() == type, "ConnectorRef type does not match T");
		
		ConnectorMapBase::Iterator it = ConnectorMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || ConnectorT::AllowDuplicates(), "Cannot have duplicate componnets");
		ConnectorMapBase::Add(type, component);
	}
	
	template<typename ConnectorT>
	void Remove(ConnectorStoreRef s) {
		CXX2A_STATIC_ASSERT(ConnectorStore::IsConnector<ConnectorT>::value, "T should derive from Connector");
		
		ConnectorMapBase::Iterator iter = ConnectorMapBase::Find(AsTypeCls<ConnectorT>());
		ASSERT_(iter, "Tried to remove non-existent component");
		
		iter.value().Uninitialize();
		iter.value().Destroy();
		
		ReturnConnector(*s, iter.value.GetItem()->value.Detach());
		ConnectorMapBase::Remove(iter);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};


NAMESPACE_TOPSIDE_END

#endif
