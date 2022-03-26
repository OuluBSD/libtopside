#ifndef _SerialCore_Loop_h_
#define _SerialCore_Loop_h_

NAMESPACE_SERIAL_BEGIN


class Loop :
	public MetaDirectoryBase
{
	//mutable Machine*	machine = 0;
	//BitField<dword>		freeze_bits;
	String				name;
	String				prefab;
	LoopId				id;
	//int64				created = 0;
	//int64				changed = 0;
	
protected:
	friend class LoopStore;
	friend class ScriptLoader;
	
	Serial::Space*		space = 0;
	
	void SetId(LoopId i) {id = i;}
	
public:
	typedef Loop CLASSNAME;
	
	static LoopId GetNextId();
	
	RTTI_DECL1(Loop, MetaDirectoryBase)
	Loop();
	~Loop();
	
	/*typedef enum {
		BIT_OVERLAP,
		BIT_TRANSFORM,
	} Bit;*/
	
	
	LoopId GetId() const {return id;}
	
	void SetName(String s)			{name = s;}
	void SetPrefab(String s)		{prefab = s;}
	//void SetCreated(int64 i)		{created = i;}
	//void SetChanged(int64 i)		{changed = i;}
	/*void FreezeTransform()			{freeze_bits.Set(BIT_TRANSFORM, true);}
	void FreezeOverlap()			{freeze_bits.Set(BIT_OVERLAP, true);}
	bool IsFrozenTransform() const	{return freeze_bits.Is(BIT_TRANSFORM);}
	bool IsFrozenOverlap() const	{return freeze_bits.Is(BIT_OVERLAP);}*/
	
	void				Clear();
	void				UnlinkDeep();
	void				UnlinkExchangePoints();
	void				ClearInterfacesDeep();
	void				UnrefDeep();
	//void				UninitializeAtomsDeep();
	//void				ClearAtomsDeep();
	void				ClearDeep();
	//void				PruneFromContainer();
	void				Dump();
	String				GetTreeString(int indent=0);
	
	Loop*				GetParent() const;
	Space*				GetSpace() const;
	//Machine&			GetMachine() const;
	String				GetName() const {return name;}
	String				GetDeepName() const;
	bool				HasAtoms() const {return !links.IsEmpty();}
	bool				HasLoops() const {return !loops.IsEmpty();}
	
	void				Initialize(Loop& l, String prefab="Custom");
	
	//void				CopyTo(Loop& l) const;
	LoopRef				CreateEmpty();
	LoopRef				GetAddEmpty(String name);
	
	bool				MakeLink(AtomBaseRef src_comp, AtomBaseRef dst_comp, ValDevCls iface);
	
	void				OnChange();
	/*AtomBaseRef			GetTypeCls(AtomTypeCls atom_type);*/
	AtomBaseRef			GetAddTypeCls(AtomTypeCls cls) {return space->GetAddTypeCls(cls);}
	AtomBaseRef			FindTypeCls(AtomTypeCls atom_type) {return space->FindTypeCls(atom_type);}
	LoopRef				FindLoopByName(String name);
	
	
	
	//AtomBaseRef			AddPtr(AtomBase* atom);
	/*void				InitializeAtoms();
	void				InitializeAtom(AtomBase& atom);
	void				InitializeAtomRef(AtomBaseRef atom) {return InitializeAtom(*atom);}
	void				UninitializeAtoms();
	void				ClearAtoms();*/
	//void				ClearInterfaces();
	void				AppendCopy(const Loop& l);
	
	int					GetLoopDepth() const;
	bool				HasLoopParent(LoopRef pool) const;
	
	/*template<typename T>
	RefT_Loop<T> FindCast() {
		for (Ref<AtomBase>& a : links.GetValues()) {
			T* o = CastPtr<T>(&*a);
			if (o)
				return o->template AsRef<T>();
		}
		return RefT_Loop<T>();
	}*/
	
	//template<typename T> RefT_Loop<T> FindNearestAtomCast(int nearest_loop_depth);
	//EnvStateRef FindNearestState(String name);
	
	//StateVec& GetStates() {return states;}
	//AtomMap& GetAtoms() {return links;}
	LoopVec& GetLoops() {return loops;}
	//const StateVec& GetStates() const {return states;}
	//const AtomMap& GetAtoms() const {return links;}
	//const LoopVec& GetLoops() const {return loops;}
	
	LoopRef AddLoop(String name="") {
		Loop& p = loops.Add();
		p.SetParent(DirExBaseParent(0, this));
		p.SetName(name);
		//p.SetId(GetNextId());
		return p;
	}
	
	LoopRef GetAddLoop(String name) {
		for (LoopRef& pool : loops)
			if (pool->GetName() == name)
				return pool;
		return AddLoop(name);
	}
	
	EnvStateRef GetAddEnv(String name) {return space->GetAddEnv(name);}
	
	/*EnvStateRef AddState(String name="") {
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
	}*/
	
	/*AtomMap::Iterator			begin()			{return links.begin();}
	AtomMap::Iterator			end()			{return links.end();}
	LoopVec::Iterator			BeginLoop()		{return loops.begin();}*/
	
	void Visit(RuntimeVisitor& vis) {vis || links || loops;}
	//void VisitSinks(RuntimeVisitor& vis);
	//void VisitSources(RuntimeVisitor& vis);
	
private:
	//StateVec				states;
	//AtomMap				links;
	LinkVec					links;
	LoopVec					loops;
};


class LoopHashVisitor : public RuntimeVisitor {
	CombineHash ch;
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override;
public:
	RTTI_DECL1(LoopHashVisitor, RuntimeVisitor)
	
	
	operator hash_t() const {return ch;}
	
};





NAMESPACE_SERIAL_END

#endif
