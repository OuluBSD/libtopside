#ifndef _EcsCore_Component_h_
#define _EcsCore_Component_h_

NAMESPACE_OULU_BEGIN



template <class T> inline RefT_Entity<T> ComponenBase_Static_As(ComponentBase*) {return 0;}

class ComponentBase :
	public Destroyable,
	public Enableable,
	public RefScopeEnabler<ComponentBase,Entity>
{
protected:
	friend class Entity;
	Entity* ent = NULL;
	
public:
	virtual TypeId GetType() const = 0;
	virtual void CopyTo(ComponentBase* component) const = 0;
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	virtual String ToString() const {return "<not implemented>";}
	
	static bool AllowDuplicates() {return false;}
	
	Machine& GetMachine();
	
public:
	ComponentBase();
	virtual ~ComponentBase();
	
	Entity& GetEntity() {ASSERT(ent); return *ent;}
	Entity* GetEntityPtr() const {return ent;}
	
	template <class T> RefT_Entity<T> As() {return ComponenBase_Static_As<T>(this);}
	
	#define IFACE(x) \
	virtual RefT_Entity<x##Source> As##x##Source() {return Null;} \
	virtual RefT_Entity<x##Sink>   As##x##Sink()   {return Null;}
	IFACE_LIST
	#undef IFACE
	
	
	template <class S, class R>
	void AddToSystem(R ref) {
		Ref<S> sys = GetMachine().Get<S>();
		if (sys)
			sys->Add(ref);
	}
	
	template <class S, class R>
	void RemoveFromSystem(R ref) {
		Ref<S> sys = GetMachine().Get<S>();
		if (sys)
			sys->Remove(ref);
	}
};

#define IFACE(x) \
template<> inline RefT_Entity<x##Source> ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Source();} \
template<> inline RefT_Entity<x##Sink>   ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Sink();}
IFACE_LIST
#undef IFACE


template<typename T>
struct Component :
	ComponentBase
{

	TypeId GetType() const override {
		return typeid(T);
	}
	
	void CopyTo(ComponentBase* target) const override {
		ASSERT(target->GetType() == GetType());
	    
		*static_cast<T*>(target) = *static_cast<const T*>(this);
	}
};

using ComponentMapBase	= RefTypeMapIndirect<ComponentBase>;
using ComponentRefMap	= ArrayMap<TypeId,Ref<ComponentBase>>;

using ComponentMapBase	= RefTypeMapIndirect<ComponentBase>;
using ComponentRefMap	= ArrayMap<TypeId,Ref<ComponentBase>>;

class ComponentMap : public ComponentMapBase {
	
	void ReturnComponent(ComponentStore& s, ComponentBase* c);
	
public:
	
	ComponentMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename ComponentT>
	RefT_Entity<ComponentT> Get() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			throw Exc("Could not find component " + TypeId(typeid(ComponentT)).CleanDemangledName());
		
		return it->AsRef<ComponentT>();
	}
	
	template<typename ComponentT>
	RefT_Entity<ComponentT> Find() {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(typeid(ComponentT));
		if (IS_EMPTY_SHAREDPTR(it))
			return Null;
		else
			return it->AsRef<ComponentT>();
	}
	
	template<typename ComponentT>
	void Add(ComponentT* component) {
		CXX2A_STATIC_ASSERT(IsComponent<ComponentT>::value, "T should derive from Component");
		
		const TypeId type = typeid(ComponentT);
		ASSERT_(component->GetType() == type, "ComponentRef type does not match T");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || ComponentT::AllowDuplicates(), "Cannot have duplicate componnets");
		ComponentRef cmp = ComponentMapBase::Add(type, component);
	}
	
	template<typename ComponentT>
	void Remove(ComponentStoreRef s) {
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
