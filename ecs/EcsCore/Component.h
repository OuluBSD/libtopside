#ifndef _EcsCore_Component_h_
#define _EcsCore_Component_h_

NAMESPACE_OULU_BEGIN



template <class T> inline Ref<T> ComponenBase_Static_As(ComponentBase*) {return 0;}

struct ComponentBase : Destroyable, Enableable, LockedScopeEnabler<ComponentBase> {
	Entity* ent = NULL;
	virtual ~ComponentBase() = default;

	virtual TypeId GetType() const = 0;
	virtual void CopyTo(ComponentBase* component) const = 0;
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	virtual String ToString() const {return "<not implemented>";}
	
	static bool AllowDuplicates() {return false;}
	
public:
	Entity& GetEntity() {ASSERT(ent); return *ent;}
	Entity* GetEntityPtr() const {return ent;}
	
	template <class T> Ref<T> As() {return ComponenBase_Static_As<T>(this);}
	
	#define IFACE(x) \
	virtual Ref<x##Source> As##x##Source() {return NULL;} \
	virtual Ref<x##Sink>   As##x##Sink()   {return NULL;}
	IFACE_LIST
	#undef IFACE
	
	
};

#define IFACE(x) \
template<> inline Ref<x##Source> ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Source();} \
template<> inline Ref<x##Sink>   ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Sink();}
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
typedef ArrayMap<TypeId, Ref<ComponentBase>> ComponentRefMap;

class ComponentMap : public ComponentMapBase {
	
	void ReturnComponent(ComponentStore& s, ComponentBase* c);
	
public:
	
	ComponentMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename ComponentT>
	Ref<ComponentT> Get() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			throw Exc("Could not find component " + TypeId(typeid(ComponentT)).CleanDemangledName());
		
		return it->AsRef<ComponentT>();
	}
	
	template<typename ComponentT>
	Ref<ComponentT> Find() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		if (IS_EMPTY_SHAREDPTR(it))
			return NULL;
		else
			return it->AsRef<ComponentT>();
	}
	
	template<typename ComponentT>
	Ref<ComponentT> Add(ComponentT* component) {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		const TypeId type = typeid(ComponentT);
		ASSERT_(component->GetType() == type, "ComponentRef type does not match T");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || ComponentT::AllowDuplicates(), "Cannot have duplicate componnets");
		ComponentRef cmp = ComponentMapBase::Add(type, component);
		
		return Ref<ComponentT>(component);
	}
	
	template<typename ComponentT>
	void Remove(Ref<ComponentStore> s) {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator iter = ComponentMapBase::Find(typeid(ComponentT));
		ASSERT_(iter, "Tried to remove non-existent component");
		
		iter.value().Uninitialize();
		iter.value().Destroy();
		
		ReturnComponent(*s, iter.value.GetItem()->value.Detach());
		ComponentMapBase::Remove(iter);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};


NAMESPACE_OULU_END

#endif
