#ifndef _EcsCore_Component_h_
#define _EcsCore_Component_h_

NAMESPACE_ECS_BEGIN

class ComponentBase;
namespace Eon {class WorldState;}





template <class T> inline RefT_Entity<T> ComponentBase_Static_As(ComponentBase*) {return RefT_Entity<T>();}

class ComponentBase :
	public ComponentBaseUpdater,
	public Destroyable,
	public Enableable,
	public RefScopeEnabler<ComponentBase,Entity>
{
protected:
	friend class Entity;
	
public:
	virtual void CopyTo(ComponentBase* component) const = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0; // linking errors here means invalid derived visit
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	// moved to inherited: virtual void Update(double dt) {Panic("unimplemented");}
	virtual String ToString() const;
	
	
	Engine& GetEngine();
	
	void AddToUpdateList() {GetEngine().AddToUpdateList(this);}
	void RemoveFromUpdateList() {GetEngine().RemoveFromUpdateList(this);}
	
public:
	RTTI_DECL_R2(ComponentBase, Destroyable, Enableable)
	ComponentBase();
	virtual ~ComponentBase();
	
	EntityRef GetEntity();
	
	virtual void Etherize(Ether& e) = 0;
	
	virtual bool Arg(String key, Object value) {return true;}
	
	template <class T> RefT_Entity<T> As() {return ComponentBase_Static_As<T>(this);}
	
	template <class S, class R>
	void AddToSystem(R ref) {
		Ref<S> sys = GetEngine().Get<S>();
		if (sys)
			sys->Add(ref);
	}
	
	template <class S, class R>
	void RemoveFromSystem(R ref) {
		Ref<S> sys = GetEngine().Get<S>();
		if (sys)
			sys->Remove(ref);
	}
	
	template <class ValDevSpec, class T> bool LinkManually(T& o, String* err_msg=0);
	
	template <class T> void EtherizeRef(Ether& e, Ref<T>& ref);
	template <class T> void EtherizeRefContainer(Ether& e, T& cont);
	
	void GetComponentPath(Vector<String>& path);
	
};




template<typename T>
struct Component :
	public ComponentBase
{
public:
	RTTI_DECL1(Component<T>, ComponentBase)
	using ComponentT = Component<T>;

	void Visit(RuntimeVisitor& v) override {} // don't visit ComponentBase (for error detection reasons)
	
	void CopyTo(ComponentBase* target) const override {
		ASSERT(target->GetTypeId() == GetTypeId());
	    
		*static_cast<T*>(target) = *static_cast<const T*>(this);
	}
	
};


#define COMP_RTTI(x)  RTTI_DECL1(x, Component<x>)

using ComponentMapBase	= RefTypeMapIndirect<ComponentBase>;
using ComponentRefMap	= ArrayMap<TypeCls,Ref<ComponentBase>>;

class ComponentMap : public ComponentMapBase {
	
	void ReturnComponent(ComponentStore& s, ComponentBase* c);
	
public:
	
	ComponentMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename ComponentT>
	RefT_Entity<ComponentT> Get() {
		CXX2A_STATIC_ASSERT(ComponentStore::IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(AsTypeCls<ComponentT>());
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			THROW(Exc("Could not find component " + AsTypeString<ComponentT>()));
		
		return it->AsRef<ComponentT>();
	}
	
	template<typename ComponentT>
	RefT_Entity<ComponentT> Find() {
		CXX2A_STATIC_ASSERT(ComponentStore::IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator it = ComponentMapBase::Find(AsTypeCls<ComponentT>());
		if (IS_EMPTY_SHAREDPTR(it))
			return Null;
		else
			return it->AsRef<ComponentT>();
	}
	
	template<typename ComponentT>
	void Add(ComponentT* component) {
		CXX2A_STATIC_ASSERT(ComponentStore::IsComponent<ComponentT>::value, "T should derive from Component");
		
		TypeCls type = ComponentT::TypeIdClass();
		ASSERT(type != 0);
		ComponentMapBase::Iterator it = ComponentMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it), "Cannot have duplicate componnets");
		ComponentMapBase::Add(type, component);
	}
	
	template<typename ComponentT>
	void Remove(ComponentStoreRef s) {
		CXX2A_STATIC_ASSERT(ComponentStore::IsComponent<ComponentT>::value, "T should derive from Component");
		
		ComponentMapBase::Iterator iter = ComponentMapBase::Find(AsTypeCls<ComponentT>());
		ASSERT_(iter, "Tried to remove non-existent component");
		
		iter.value().Uninitialize();
		iter.value().Destroy();
		
		ReturnComponent(*s, iter.value.GetItem()->value.Detach());
		ComponentMapBase::Remove(iter);
	}
	
	void AddBase(ComponentBase* component) {
		TypeCls type = component->GetTypeId();
		ComponentMapBase::Iterator it = ComponentMapBase::Find(type);
		ComponentMapBase::Add(type, component);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};


NAMESPACE_ECS_END

#endif
