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
	
	
	SpaceId GetId() const {return id;}
	
	void SetName(String s)			{name = s;}
	void SetPrefab(String s)		{prefab = s;}
	void SetCreated(int64 i)		{created = i;}
	void SetChanged(int64 i)		{changed = i;}
	
	void				Clear();
	void				StopDeep();
	void				Stop();
	void				UnlinkDeep();
	void				UnrefDeep();
	void				UninitializeAtomsDeep();
	void				ClearStatesDeep();
	void				ClearAtomsDeep();
	void				ClearDeep();
	void				Dump();
	String				GetTreeString(int indent=0);
	
	Serial::Loop*		GetLoop() const;
	Space*				GetParent() const;
	Machine&			GetMachine() const;
	String				GetName() const {return name;}
	String				GetDeepName() const;
	bool				HasAtoms() const {return !atoms.IsEmpty();}
	bool				HasSpaces() const {return !spaces.IsEmpty();}
	
	void				Initialize(Space& l, String prefab="Custom");
	
	SpaceRef			CreateEmpty();
	SpaceRef			GetAddEmpty(String name);
	void				CopyTo(Space& l) const;
	
	bool				Link(AtomBaseRef src_comp, AtomBaseRef dst_comp, ValDevCls iface);
	
	AtomBaseRef			GetTypeCls(AtomTypeCls atom_type);
	AtomBaseRef			AddTypeCls(AtomTypeCls cls);
	AtomBaseRef			GetAddTypeCls(AtomTypeCls cls);
	AtomBaseRef			FindTypeCls(AtomTypeCls atom_type);
	SpaceRef			FindSpaceByName(String name);
	AtomBaseRef			FindAtom(TypeCls type);
	AtomBaseRef			FindDeepCls(TypeCls type);
	
	template <class T>
	RefT_Atom<T> FindDeep() {auto r = FindDeepCls(T::TypeIdClass()); return r ? r->template AsRefT<T>() : RefT_Atom<T>();}
	
	
	AtomBaseRef			AddPtr(AtomBase* atom);
	void				InitializeAtoms();
	void				InitializeAtom(AtomBase& atom);
	void				InitializeAtomRef(AtomBaseRef atom) {return InitializeAtom(*atom);}
	void				UninitializeAtoms();
	void				ClearAtoms();
	void				AppendCopy(const Space& l);
	
	int					GetSpaceDepth() const;
	bool				HasSpaceParent(SpaceRef pool) const;
	
	void				UnlinkExchangePoints();
	
	template<typename T>
	RefT_Atom<T> FindCast() {
		for (Ref<AtomBase>& a : atoms.GetValues()) {
			T* o = CastPtr<T>(&*a);
			if (o)
				return o->template AsRef<T>();
		}
		return RefT_Atom<T>();
	}
	
	template<typename T> RefT_Atom<T> FindNearestAtomCast(int nearest_loop_depth);
	EnvStateRef FindNearestState(String name);
	EnvStateRef FindStateDeep(String name);
	
	StateVec& GetStates() {return states;}
	AtomMap& GetAtoms() {return atoms;}
	SpaceVec& GetSpaces() {return spaces;}
	const StateVec& GetStates() const {return states;}
	const AtomMap& GetAtoms() const {return atoms;}
	const SpaceVec& GetSpaces() const {return spaces;}
	
	SpaceRef AddSpace(String name="") {
		Space& p = spaces.Add();
		p.SetParent(HierExBaseParent(0, this));
		p.SetName(name);
		p.SetId(GetNextId());
		return p;
	}
	
	SpaceRef GetAddSpace(String name) {
		for (SpaceRef& pool : spaces)
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
	SpaceVec::Iterator			BeginSpace()		{return spaces.begin();}
	
	void Visit(RuntimeVisitor& vis);
	void VisitSinks(RuntimeVisitor& vis);
	void VisitSources(RuntimeVisitor& vis);
	
private:
	StateVec				states;
	AtomMap					atoms;
	SpaceVec				spaces;
};


class SpaceHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(SpaceHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};



template<typename T>
RefT_Atom<T> Space::FindNearestAtomCast(int nearest_space_depth) {
	if (auto r = FindCast<T>())
		return r;
	
	if (nearest_space_depth > 0)
		for (auto& space : spaces)
			if (auto ret = space->FindNearestAtomCast<T>(nearest_space_depth-1))
				return ret;
	
	if (Space* p = GetParent())
		return p->FindNearestAtomCast<T>(nearest_space_depth);
	
	return RefT_Atom<T>();
}


NAMESPACE_PARALLEL_END

#endif
