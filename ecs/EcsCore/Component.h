#ifndef _EcsCore_Component_h_
#define _EcsCore_Component_h_

NAMESPACE_OULU_BEGIN




template <class T> inline T* ComponenBase_Static_As(ComponentBase*) {return 0;}

struct ComponentBase : Destroyable, Enableable, LockedScopeEnabler<ComponentBase> {
	Entity* ent = NULL;
	virtual ~ComponentBase() = default;

	virtual TypeId GetType() const = 0;
	virtual void CopyTo(ComponentBase* component) const = 0;
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	
	static bool AllowDuplicates() {return false;}
	
public:
	Entity& GetEntity() {ASSERT(ent); return *ent;}
	
	template <class T> T* As() {return ComponenBase_Static_As<T>(this);}
	
	#define IFACE(x) \
	virtual x##Source* As##x##Source() {return NULL;} \
	virtual x##Sink* As##x##Sink() {return NULL;}
	IFACE_LIST
	#undef IFACE
	
	
	#define IFACE(x) \
	void Signal##x##Source(); \
	void Signal##x##Sink();
	IFACE_LIST
	#undef IFACE
	
};

#define IFACE(x) \
template<> inline x##Source* ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Source();} \
template<> inline x##Sink* ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Sink();}
IFACE_LIST
#undef IFACE


template<typename T>
struct Component : ComponentBase {

	TypeId GetType() const override {
		return typeid(T);
	}
	
	void CopyTo(ComponentBase* target) const override {
		ASSERT(target->GetType() == GetType());
	    
		*static_cast<T*>(target) = *static_cast<const T*>(this);
	}
};


typedef RefTypeMapIndirect<ComponentBase> ComponentMapBase;

class ComponentMap : public ComponentMapBase {
public:
	
	ComponentMap() {}
	//ComponentMap(ComponentMap&& pick) {Upp::Swap(*(Base*)this, *(Base*)&pick);}
	ComponentMap(Pick<ComponentMap> pick) {Upp::Swap((ComponentMapBase&)*this, (ComponentMapBase&)pick.Get());}
	
	
	//using RefTypeMap<Component>::RefTypeMap;
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	template<typename ComponentT>
	ComponentT* Get() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		return static_cast<ComponentT*>(it->Get());
	}
	
	template<typename ComponentT>
	ComponentT* Find() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		if (IS_EMPTY_SHAREDPTR(it))
			return NULL;
		else
			return static_cast<ComponentT*>(it->Get());
	}
	
	template<typename ComponentT>
	Ref<ComponentT> GetRef() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		return it->As<ComponentT>();
	}
	
	template<typename ComponentT>
	Ref<ComponentT> FindRef() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		if (IS_EMPTY_SHAREDPTR(it))
			return Ref<ComponentT>();
		else
			return it->As<ComponentT>();
	}
	
	template<typename ComponentT>
	ComponentT* TryGet() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		if (!IS_EMPTY_SHAREDPTR(it)) {
			return static_cast<ComponentT*>(it->Get());
		}
		
		return nullptr;
	}
	
	/*template<typename ComponentT>
	ComponentT* Add(ComponentRef component) {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		const TypeId componentType = typeid(ComponentT);
		
		ASSERT_(component->GetType() == componentType, "ComponentRef type does not match T");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(componentType);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || ComponentT::AllowDuplicates(), "Can't have duplicate componnets");
		ComponentRef& cmp = ComponentMapBase::Add(componentType);
		cmp = pick(component);
		
		return static_cast<ComponentT*>(cmp.Get());
	}*/
	
	template<typename ComponentT>
	void Remove() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator iter = ComponentMapBase::Find(typeid(ComponentT));
		ASSERT_(iter, "Tried to remove non-existent component");
		iter.value().Uninitialize();
		iter.value().Destroy();
		ComponentMapBase::Remove(iter);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};


NAMESPACE_OULU_END

#endif
