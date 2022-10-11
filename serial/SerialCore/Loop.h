#ifndef _SerialCore_Loop_h_
#define _SerialCore_Loop_h_

NAMESPACE_SERIAL_BEGIN


class Loop :
	public MetaDirectoryBase
{
	String				name;
	String				prefab;
	LoopId				id;
	
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
	
	LoopId GetId() const {return id;}
	
	void SetName(String s)			{name = s;}
	void SetPrefab(String s)		{prefab = s;}
	
	void				Clear();
	void				ClearInterfacesDeep();
	void				UnrefDeep();
	void				UninitializeLinksDeep();
	void				ClearDeep();
	void				Dump();
	String				GetTreeString(int indent=0);
	
	Loop*				GetParent() const;
	Space*				GetSpace() const;
	String				GetName() const {return name;}
	String				GetDeepName() const;
	bool				HasAtoms() const {return !links.IsEmpty();}
	bool				HasLoops() const {return !loops.IsEmpty();}
	
	void				Initialize(Loop& l, String prefab="Custom");
	
	LoopRef				CreateEmpty();
	LoopRef				GetAddEmpty(String name);
	
	bool				MakeLink(AtomBaseRef src_atom, AtomBaseRef dst_atom);
	
	void				OnChange();
	LinkBaseRef			AddTypeCls(LinkTypeCls cls);
	LinkBaseRef			GetAddTypeCls(LinkTypeCls cls);
	LinkBaseRef			FindTypeCls(LinkTypeCls atom_type);
	LoopRef				FindLoopByName(String name);
	
	
	
	LinkBaseRef			AddPtr(LinkBase* link);
	void				InitializeLink(LinkBase& atom);
	void				InitializeLinks();
	void				AppendCopy(const Loop& l);
	
	int					GetLoopDepth() const;
	bool				HasLoopParent(LoopRef pool) const;
	
	LoopVec& GetLoops() {return loops;}
	
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
	
	void Visit(RuntimeVisitor& vis);
	
private:
	LinkMap					links;
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
