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
	void SetPrefab(String s)		{prefab = s;}
	void SetCreated(int64 i)		{created = i;}
	void SetChanged(int64 i)		{changed = i;}
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
	
	void				Initialize(Loop& l, String prefab="Custom");
	
	LoopRef				CreateEmpty();
	LoopRef				GetAddEmpty(String name);
	void				CopyTo(Loop& l) const;
	
	bool				Link(AtomBaseRef src_comp, AtomBaseRef dst_comp, ValDevCls iface);
	
	void				OnChange();
	AtomBaseRef			GetTypeCls(AtomTypeCls atom_type);
	AtomBaseRef			GetAddTypeCls(AtomTypeCls cls);
	AtomBaseRef			FindTypeCls(AtomTypeCls atom_type);
	LoopRef				FindLoopByName(String name);
	
	
	
	AtomBaseRef			AddPtr(AtomBase* atom);
	void				InitializeAtoms();
	void				InitializeAtom(AtomBase& atom);
	void				InitializeAtomRef(AtomBaseRef atom) {return InitializeAtom(*atom);}
	void				UninitializeAtoms();
	void				ClearAtoms();
	void				ClearInterfaces();
	void				AppendCopy(const Loop& l);
	
	int					GetLoopDepth() const;
	bool				HasLoopParent(LoopRef pool) const;
	
	template<typename T>
	RefT_Loop<T> FindCast() {
		for (Ref<AtomBase>& a : atoms.GetValues()) {
			T* o = CastPtr<T>(&*a);
			if (o)
				return o->template AsRef<T>();
		}
		return RefT_Loop<T>();
	}
	
	template<typename T> RefT_Loop<T> FindNearestAtomCast(int nearest_loop_depth);
	
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
	
	void Visit(RuntimeVisitor& vis) {vis || atoms || loops;}
	void VisitSinks(RuntimeVisitor& vis);
	void VisitSources(RuntimeVisitor& vis);
	
private:
	AtomMap					atoms;
	LoopVec					loops;
	
};


class LoopHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(LoopHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};




template<typename T>
RefT_Loop<T> Loop::FindNearestAtomCast(int nearest_loop_depth) {
	if (auto r = FindCast<T>())
		return r;
	
	if (nearest_loop_depth > 0)
		for (auto& loop : loops)
			if (auto ret = loop->FindNearestAtomCast<T>(nearest_loop_depth-1))
				return ret;
	
	if (Loop* p = GetParent())
		return p->FindNearestAtomCast<T>(nearest_loop_depth);
	
	return RefT_Loop<T>();
}


NAMESPACE_SERIAL_END

#endif
