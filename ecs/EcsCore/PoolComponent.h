#ifndef _EcsCore_PoolComponent_h_
#define _EcsCore_PoolComponent_h_

NAMESPACE_OULU_BEGIN



template <class T> inline Ref<T> ComponenBase_Static_As(PoolComponentBase*) {return 0;}

struct PoolComponentBase : Destroyable, Enableable, LockedScopeEnabler<PoolComponentBase> {
	Pool* pool = NULL;
	virtual ~PoolComponentBase() = default;

	virtual TypeId GetType() const = 0;
	virtual void CopyTo(PoolComponentBase* component) const = 0;
	virtual void Update(double dt) = 0;
	virtual void UnlinkAll() {};
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	virtual String ToString() const {return "<not implemented>";}
	
	static bool AllowDuplicates() {return false;}
	
public:
	Pool& GetPool() {ASSERT(pool); return *pool;}
	Pool* GetPoolPtr() const {return pool;}
	
	
};

typedef Ref<PoolComponentBase> PoolComponentRef;


template<typename T>
struct PoolComponent : PoolComponentBase {

	TypeId GetType() const override {
		return typeid(T);
	}
	
	void CopyTo(PoolComponentBase* target) const override {
		ASSERT(target->GetType() == GetType());
	    
		*static_cast<T*>(target) = *static_cast<const T*>(this);
	}
};


typedef RefTypeMapIndirect<PoolComponentBase> PoolComponentMapBase;
typedef ArrayMap<TypeId, Ref<PoolComponentBase>> PoolComponentRefMap;

class PoolComponentMap : public PoolComponentMapBase {
	
	void ReturnPoolComponent(PoolComponentStore& s, PoolComponentBase* c);
	
public:
	
	PoolComponentMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename PoolComponentT>
	Ref<PoolComponentT> Get() {
		CXX2A_STATIC_ASSERT(IsPoolComponent<PoolComponentT>::value, "T should derive from PoolComponent");
		
		PoolComponentMapBase::Iterator it = PoolComponentMapBase::Find(typeid(PoolComponentT));
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			throw Exc("Could not find component " + TypeId(typeid(PoolComponentT)).CleanDemangledName());
		
		return it->AsRef<PoolComponentT>();
	}
	
	template<typename PoolComponentT>
	Ref<PoolComponentT> Find() {
		CXX2A_STATIC_ASSERT(IsPoolComponent<PoolComponentT>::value, "T should derive from PoolComponent");
		
		PoolComponentMapBase::Iterator it = PoolComponentMapBase::Find(typeid(PoolComponentT));
		if (IS_EMPTY_SHAREDPTR(it))
			return NULL;
		else
			return it->AsRef<PoolComponentT>();
	}
	
	template<typename PoolComponentT>
	Ref<PoolComponentT> Add(PoolComponentT* component) {
		CXX2A_STATIC_ASSERT(IsPoolComponent<PoolComponentT>::value, "T should derive from PoolComponent");
		
		const TypeId type = typeid(PoolComponentT);
		ASSERT_(component->GetType() == type, "PoolComponentRef type does not match T");
		
		PoolComponentMapBase::Iterator it = PoolComponentMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || PoolComponentT::AllowDuplicates(), "Cannot have duplicate componnets");
		PoolComponentRef cmp = PoolComponentMapBase::Add(type, component);
		
		return Ref<PoolComponentT>(component);
	}
	
	template<typename PoolComponentT>
	void Remove(Ref<PoolComponentStore> s) {
		CXX2A_STATIC_ASSERT(IsPoolComponent<PoolComponentT>::value, "T should derive from PoolComponent");
		
		PoolComponentMapBase::Iterator iter = PoolComponentMapBase::Find(typeid(PoolComponentT));
		ASSERT_(iter, "Tried to remove non-existent component");
		
		iter.value().Uninitialize();
		iter.value().Destroy();
		
		ReturnPoolComponent(*s, iter.value.GetItem()->value.Detach());
		PoolComponentMapBase::Remove(iter);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};


NAMESPACE_OULU_END

#endif
