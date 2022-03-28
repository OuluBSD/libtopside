#ifndef _ParallelCore_Space_h_
#define _ParallelCore_Space_h_


NAMESPACE_PARALLEL_BEGIN


class Space :
	public MetaSpaceBase
{
	mutable Machine*	machine = 0;
	//BitField<dword>		freeze_bits;
	String				name;
	String				prefab;
	SpaceId				id;
	int64				created = 0;
	int64				changed = 0;
	
protected:
	friend class SpaceStore;
	friend class Serial::ScriptLoader;
	
	Serial::Loop*		loop = 0;
	
	void SetId(SpaceId i) {id = i;}
	
public:
	typedef Space CLASSNAME;
	
	static SpaceId GetNextId();
	
	RTTI_DECL1(Space, MetaSpaceBase)
	Space();
	~Space();
	
	/*typedef enum {
		BIT_OVERLAP,
		BIT_TRANSFORM,
	} Bit;*/
	
	
	SpaceId GetId() const {return id;}
	
	void SetName(String s)			{name = s;}
	void SetPrefab(String s)		{prefab = s;}
	void SetCreated(int64 i)		{created = i;}
	void SetChanged(int64 i)		{changed = i;}
	/*void FreezeTransform()			{freeze_bits.Set(BIT_TRANSFORM, true);}
	void FreezeOverlap()			{freeze_bits.Set(BIT_OVERLAP, true);}
	bool IsFrozenTransform() const	{return freeze_bits.Is(BIT_TRANSFORM);}
	bool IsFrozenOverlap() const	{return freeze_bits.Is(BIT_OVERLAP);}*/
	
	void				Clear();
	void				UnlinkDeep();
	void				UnrefDeep();
	void				UninitializeAtomsDeep();
	void				ClearAtomsDeep();
	void				ClearDeep();
	//void				PruneFromContainer();
	void				Dump();
	String				GetTreeString(int indent=0);
	
	Serial::Loop*		GetLoop() const;
	Space*				GetParent() const;
	Machine&			GetMachine() const;
	String				GetName() const {return name;}
	String				GetDeepName() const;
	bool				HasAtoms() const {return !atoms.IsEmpty();}
	bool				HasSpaces() const {return !sub.IsEmpty();}
	
	void				Initialize(Space& l, String prefab="Custom");
	
	SpaceRef			CreateEmpty();
	SpaceRef			GetAddEmpty(String name);
	void				CopyTo(Space& l) const;
	
	bool				Link(AtomBaseRef src_comp, AtomBaseRef dst_comp, ValDevCls iface);
	
	//void				OnChange();
	AtomBaseRef			GetTypeCls(AtomTypeCls atom_type);
	AtomBaseRef			GetAddTypeCls(AtomTypeCls cls);
	AtomBaseRef			FindTypeCls(AtomTypeCls atom_type);
	SpaceRef			FindSpaceByName(String name);
	
	
	
	AtomBaseRef			AddPtr(AtomBase* atom);
	void				InitializeAtoms();
	void				InitializeAtom(AtomBase& atom);
	void				InitializeAtomRef(AtomBaseRef atom) {return InitializeAtom(*atom);}
	void				UninitializeAtoms();
	void				ClearAtoms();
	//void				ClearInterfaces();
	void				AppendCopy(const Space& l);
	
	int					GetSpaceDepth() const;
	bool				HasSpaceParent(SpaceRef pool) const;
	
	void				UnlinkExchangePoints();
	
	template<typename T>
	RefT_Space<T> FindCast() {
		for (Ref<AtomBase>& a : atoms.GetValues()) {
			T* o = CastPtr<T>(&*a);
			if (o)
				return o->template AsRef<T>();
		}
		return RefT_Space<T>();
	}
	
	template<typename T> RefT_Space<T> FindNearestAtomCast(int nearest_loop_depth);
	EnvStateRef FindNearestState(String name);
	
	StateVec& GetStates() {return states;}
	AtomMap& GetAtoms() {return atoms;}
	SpaceVec& GetSpaces() {return sub;}
	const StateVec& GetStates() const {return states;}
	const AtomMap& GetAtoms() const {return atoms;}
	const SpaceVec& GetSpaces() const {return sub;}
	
	SpaceRef AddSpace(String name="") {
		Space& p = sub.Add();
		p.SetParent(HierExBaseParent(0, this));
		p.SetName(name);
		p.SetId(GetNextId());
		return p;
	}
	
	SpaceRef GetAddSpace(String name) {
		for (SpaceRef& pool : sub)
			if (pool->GetName() == name)
				return pool;
		return AddSpace(name);
	}
	
	EnvStateRef AddState(String name="") {
		EnvState& p = states.Add();
		p.SetParent(this);
		p.SetName(name);
		return p;
	}
	
	EnvStateRef GetAddEnv(String name) {
		if (EnvStateRef e = FindState(name))
			return e;
		return AddState(name);
	}
	
	EnvStateRef FindState(String name) {
		for (EnvStateRef& s : states)
			if (s->GetName() == name)
				return s;
		return EnvStateRef();
	}
	
	AtomMap::Iterator			begin()			{return atoms.begin();}
	AtomMap::Iterator			end()			{return atoms.end();}
	SpaceVec::Iterator			BeginSpace()		{return sub.begin();}
	
	void Visit(RuntimeVisitor& vis) {vis || atoms || sub || states;}
	void VisitSinks(RuntimeVisitor& vis);
	void VisitSources(RuntimeVisitor& vis);
	
private:
	StateVec				states;
	AtomMap					atoms;
	SpaceVec				sub;
};


class SpaceHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(SpaceHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};


NAMESPACE_PARALLEL_END

#endif
