#ifndef _SerialCore_Loop_h_
#define _SerialCore_Loop_h_

NAMESPACE_SERIAL_BEGIN


class Loop :
	public MetaExchangePoint,
	RTTIBase
{
	mutable Machine*	machine = 0;
	BitField<dword>		freeze_bits;
	String				name;
	String				prefab;
	LoopId				id;
	int64				created = 0;
	int64				changed = 0;
	
protected:
	friend class LoopStore;
	
	void SetId(LoopId i) {id = i;}
	
public:
	typedef Loop CLASSNAME;
	
	static LoopId GetNextId();
	
	RTTI_DECL_R1(Loop, MetaExchangePoint)
	Loop();
	~Loop();
	
	typedef enum {
		BIT_OVERLAP,
		BIT_TRANSFORM,
	} Bit;
	
	
	LoopId GetId() const {return id;}
	
	void SetName(String s)			{name = s;}
	void FreezeTransform()			{freeze_bits.Set(BIT_TRANSFORM, true);}
	void FreezeOverlap()			{freeze_bits.Set(BIT_OVERLAP, true);}
	bool IsFrozenTransform() const	{return freeze_bits.Is(BIT_TRANSFORM);}
	bool IsFrozenOverlap() const	{return freeze_bits.Is(BIT_OVERLAP);}
	
	void				ReverseEntities();
	void				Clear();
	void				UnlinkDeep();
	void				UnlinkExchangePoints();
	void				ClearInterfacesDeep();
	void				UnrefDeep();
	void				UninitializeAtomsDeep();
	void				ClearAtomsDeep();
	void				ClearDeep();
	void				PruneFromContainer();
	void				Dump();
	String				GetTreeString(int indent=0);
	
	Loop*				GetParent() const;
	Machine&			GetMachine() const;
	String				GetName() const {return name;}
	bool				HasEntities() const {return !atoms.IsEmpty();}
	bool				HasLoops() const {return !loops.IsEmpty();}
	
	void				Initialize(Loop& e, String prefab="Custom");
	LoopRef				CreateEmpty() const;
	LoopRef				GetAddEmpty(String name);
	LoopRef				Clone(const Loop& e);
	
	bool Link(AtomBaseRef src_comp, AtomBaseRef dst_comp, ValDevCls iface);
	
	void OnChange();
	AtomBaseRef GetTypeCls(TypeAtomCls atom_type);
	AtomBaseRef GetAddTypeCls(TypeAtomCls cls);
	AtomBaseRef FindTypeCls(TypeAtomCls atom_type);
	
	
	
	AtomBaseRef AddPtr(AtomBase* atom);
	LoopRef Clone() const;
	void InitializeAtoms();
	void InitializeAtom(AtomBase& atom);
	void InitializeAtomRef(AtomBaseRef atom) {return InitializeAtom(*atom);}
	void UninitializeAtoms();
	void ClearAtoms();
	void ClearInterfaces();
	void AppendCopy(const Loop& l);
	
	int GetLoopDepth() const;
	bool HasLoopParent(LoopRef pool) const;
	
	/*template<typename PrefabT>
	LoopRef Create() {
		static_assert(RTupleAllAtoms<typename PrefabT::Atoms>::value, "Prefab should have a list of Atoms");
		
		Loop& e = atoms.Add();
		e.SetParent(this);
		e.SetId(GetNextId());
		PrefabT::Make(e);
		Initialize(e, AsTypeName<PrefabT>());
		
		return e.AsRefT();
	}*/
	
	/*template<typename... AtomTs>
	Vector<RTuple<LoopRef,RefT_Loop<AtomTs>...>> GetAtomsWithLoop() {
		static_assert(sizeof...(AtomTs) > 0, "Need at least one atom");
		static_assert(AllAtoms<AtomTs...>::value, "Ts should all derive from Atom");
		
		Vector<RTuple<LoopRef,RefT_Loop<AtomTs>...>> atoms;
		
		for (LoopRef object : atoms) {
			auto requested_atoms = object->TryGetAtoms<AtomTs...>();
			
			if (AllValidAtoms(requested_atoms)) {
				RTuple<LoopRef, RefT_Loop<AtomTs>...> t(object.Get(), requested_atoms);
				atoms.Add(t);
			}
		}
		
		return atoms;
	}*/
	
	/*template<typename... AtomTs>
	Vector<RTuple<RefT_Loop<AtomTs>...>> GetAtoms() {
		static_assert(sizeof...(AtomTs) > 0, "Need at least one atom");
		static_assert(AllAtoms<AtomTs...>::value, "Ts should all derive from Atom");
		
		Vector<RTuple<RefT_Loop<AtomTs>...>> atoms;
		
		for (LoopRef object : atoms) {
			auto requested_atoms = object->TryGetAtoms<AtomTs...>();
			
			if (AllValidAtoms(requested_atoms)) {
				atoms.Add(requested_atoms);
			}
		}
		
		return atoms;
	}*/
	
	/*template<typename T>
	RefT_Loop<T> GetAdd() {
		RefT_Loop<T> c = comps.Find<T>();
		if (c)
			return c;
		return Add<T>();
	}
	*/
	/*template<typename T>
	RefT_Loop<T> Find() {
		return comps.Find<T>();
	}*/
	
	/*template <class T>
	LoopRef FindLoop(T* atom) {
		if (!atom)
			return LoopRef();
		for (LoopRef object : atoms) {
			RefT_Loop<T> t = object->Find<T>();
			if (t == atom)
				return object;
		}
		return LoopRef();
	}
	
	LoopRef FindLoopByName(String name) {
		for (LoopRef object : atoms)
			if (object->GetName() == name)
				return object;
		return LoopRef();
	}
	
	template<typename Tuple>
	bool AllValidAtoms(const Tuple& atoms) {
		bool all_valid_atoms = true;
		atoms.ForEach([&](auto& atom) {
			all_valid_atoms &= atom && !atom->IsDestroyed() && atom->IsEnabled();
		});
		return all_valid_atoms;
	}*/
	
	AtomMap& GetAtoms() {return atoms;}
	LoopVec& GetLoops() {return loops;}
	const AtomMap& GetAtoms() const {return atoms;}
	const LoopVec& GetLoops() const {return loops;}
	
	LoopRef AddLoop(String name="") {
		Loop& p = loops.Add();
		p.SetParent(LoopParent(0, this));
		p.SetName(name);
		p.SetId(GetNextId());
		return p;
	}
	
	LoopRef GetAddLoop(String name) {
		for (LoopRef& pool : loops)
			if (pool->GetName() == name)
				return pool;
		return AddLoop(name);
	}
	
	AtomMap::Iterator			begin()			{return atoms.begin();}
	AtomMap::Iterator			end()			{return atoms.end();}
	LoopVec::Iterator			BeginLoop()		{return loops.begin();}
	
	
	
	
	/*template<typename T>
	void Remove() {
		comps.Remove<T>(GetMachine().Get<ConnectorStore>());
	}
	
	template<typename T>
	RefT_Loop<T> Add() {
		T* comp = GetMachine().Get<ConnectorStore>()->CreateAtom<T>();
		ASSERT(comp);
		RefScopeParent<RefParent1<Loop>>* rp = comp;
		rp->SetParent(this);
		comps.Add(comp);
		InitializeAtom(*comp);
		return RefT_Loop<T>(this, comp);
	}*/
	
	void Visit(RuntimeVisitor& vis) {vis || atoms || loops;}
	void VisitSinks(RuntimeVisitor& vis);
	void VisitSources(RuntimeVisitor& vis);
	
private:
	AtomMap					atoms;
	LoopVec					loops;
	
	/*ConnectorMap			comps;
	
	void InitializeAtom(ConnectorBase& comp);*/
	
};


class LoopHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(LoopHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};



/*
template<typename T>
RefT_Loop<T> Loop::FindNearestLoopWith() {
	RefT_Loop<T> c = Find<T>();
	if (!c) {
		Loop* p = &GetLoop();
		while (p && !c) {
			for (LoopRef& e : *p) {
				c = e->Find<T>();
				if (c) break;
			}
			p = p->GetParent();
		}
	}
	return c;
}
*/

NAMESPACE_SERIAL_END

#endif
