#ifndef _TemplatesLib_DevScope_h_
#define _TemplatesLib_DevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevLibT {
	using D						= DevSpec;
	using DevComponentBase		= typename DevSpec::ComponentBase;
	using DevComponentGroupBase	= typename DevSpec::ComponentGroupBase;
	using Mach					= ScopeDevMachT<DevSpec>;
	using Core					= ScopeDevCoreT<DevSpec>;
	using StreamState			= typename Mach::DevStreamState;
	using SystemBase			= typename Mach::DevSystemBase;
	using DevStreamState		= typename Mach::DevStreamState;
	using DevComponentConf		= typename Mach::DevComponentConf;
	//using SourceRef			= typename Core::SourceRef;
	//using SinkRef				= typename Core::SinkRef;
	//using ExchangePointRef	= typename Core::ExchangePointRef;
	
	class ContextComponent;
	using ContextComponentRef		= Ref<ContextComponent, RefParent1<Entity>>;
	class DevComponentGroup;
	using DevComponentGroupRef		= Ref<DevComponentGroup, RefParent1<ContextComponent>>;
	class DevComponent;
	using DevComponentRef			= Ref<DevComponent, RefParent1<Entity>>;
	
	
	struct DevComponentConfVector {
		Array<DevComponentConf> in;
		
		int Find(const DevComponentConf& a) const;
		void Add(const DevComponentConf& a);
	};
	
	
	#define RTTI_CTX_SYS(sys, base) \
			RTTI_DECL_2(sys, System<sys>, base, DevSpec::GetName() + #sys)
	
	class DevSystem :
		public System<DevSystem>,
		public SystemBase
	{
		LinkedList<ContextComponentRef> ctxs;
		LinkedList<DevComponentRef> comps;
		
		void Visit(RuntimeVisitor& vis) override {
			vis && ctxs;
		}
	protected:
	    bool Initialize() override;
	    void Start() override;
	    void Update(double dt) override;
	    void Stop() override;
	    void Uninitialize() override;
	    
	public:
		RTTI_CTX_SYS(DevSystem, SystemBase)
	    SYS_CTOR(DevSystem)
		
		void Add(DevComponentRef comp) {comps.FindAdd(comp);}
		void Remove(DevComponentRef comp) {comps.RemoveKey(comp);}
		void AddCtx(ContextComponentRef ctx);
		void RemoveCtx(ContextComponentRef ctx);
		
		static inline Callback& WhenUninit() {static Callback cb; return cb;}
		
	};
	
	#undef RTTI_CTX_SYS
	
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << DevSpec::GetName() << t;
		return s;
	}
	
	class DevComponent :
		public DevComponentBase
	{
		RTTI_DECL1(DevComponent, DevComponentBase);
		void Visit(RuntimeVisitor& vis) {}
		
	protected:
		friend class DevComponentGroup;
		
		DevComponentGroupRef			group;
		LinkedList<DevComponentConf>	in;
		int								id = -1;
		
		void				Clear();
		void				OnError(String fn, String msg);
		DevStreamState&		GetDevStreamState();
		
		virtual bool		LoadAsInput(const DevComponentConf& in) = 0;
		virtual void		UpdateDevBuffers() = 0;
		virtual bool		IsEmptyStream() const = 0;
		virtual void		ClearStream() = 0;
		
		virtual void		PreProcess() {}
		
	public:
		
		void				Initialize();
		void				Uninitialize();
		bool				Load(ObjectMap& st_map, int stage_i, String frag_code);
		void				SetGroup(DevComponentGroupRef g) {group = g;}
		
		int					GetId() const {return id;}
		String				ToString() const {return GetTypeString() + " (id: " + IntStr(id) + ")";}
		String				GetTypeString() const {return GetStringFromType(RTTI::GetRTTI().GetTypeId());}
		DevStreamState&		GetStreamState();
		
		DevComponentGroupRef GetGroup() const {return group;}
		const LinkedList<DevComponentConf>& GetInputs() const {return in;}
		
		static String		GetStringFromType(TypeCls i);
		static bool			IsDevPipeComponent(TypeCls type);
		
		template <class ValSpec> void UpdateDevBuffersValT();
		template <class ValSpec> bool IsIn() {return IsValSpec(AsTypeCls<ValSpec>());}
		
	};
	
	
	
	
	class DevComponentGroup :
		public RefScopeEnabler<DevComponentGroup, ContextComponent>,
		public DevComponentGroupBase
	{
		LinkedList<DevComponentRef> comps;
		
	protected:
		friend class ContextComponent;
		TypeCls val_spec;
		
	public:
		RTTI_DECL_R1(DevComponentGroup, DevComponentGroupBase)
		
		bool		Open();
		void		CloseTemporary();
		void		Clear();
		void		FindComponents();
		void		FindUniqueInputs(DevComponentConfVector& v);
		void		ConnectInputs(DevComponentConfVector& v);
		bool		LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code);
		void		Add(DevComponentRef r) {comps.FindAdd(r); UpdateCompFlags();}
		void		Remove(DevComponentRef r) {comps.RemoveKey(r); UpdateCompFlags();}
		void		UpdateCompFlags();
		void		UpdateDevBuffers();
		
		bool				IsValSpec(TypeCls t) const override {return t == val_spec;}
		DevStreamState&		GetStreamState() override {return GetParent()->GetStreamState();}
		TypeCls				GetValSpec() const {return val_spec;}
		
		const LinkedList<DevComponentRef>& GetComponents() const {return comps;}
		
		ContextComponent* GetParent() {return RefScopeEnabler<DevComponentGroup, ContextComponent>::GetParent();}
		
	};
	
	class ContextComponent :
		public TS::Component<ContextComponent>,
		public ContextComponentBase
	{
		RTTI_COMP0(ContextComponent)
		VIS_COMP_0_0
		COPY_PANIC(ContextComponent)
		void Visit(RuntimeVisitor& vis) override {}
		
		
	private:
		LinkedList<DevComponentGroup>	groups;
		Vector<String>		common_source;
		DevStreamState		stream;
		Object				post_load;
		bool				is_open = false;
		
		void				Clear();
		void				Reset();
		void				Close();
		void				FindComponents();
		void				DumpEntityComponents();
		bool				LoadFileAny(String path, Object& dst);
		bool				Load(Object& o);
		bool				RefreshStageQueue();
		void				RefreshStreamValuesAll();
		void				RefreshPipeline();
		DevComponentGroup&	GetAddGroupContext(TypeCls val_spec);
		bool				ConnectComponentInputs();
		bool				ConnectComponentOutputs();
		bool				CreateComponents(DevComponentConfVector& v);
		void				RefreshStreamValuesBase();
		bool				CheckInputTextures();
		
		template <class ValSpec>	void RefreshStreamValues() {}
		template <class ValSpec>	bool ConnectComponentOutputsT(DevComponentGroup& gr);
		template <class ValSpec>	DevComponentGroup&	GetAddGroupContext() {return GetAddGroupContext(AsTypeCls<ValSpec>());}
		
		
		template <class T> RefT_Entity<T> AddEntityComponent(DevComponentGroup& g) {
			RefT_Entity<T> o = ComponentBase::GetEntity()->template Add<T>();
			o->SetGroup(g.AsRefT());
			g.Add(o);
			return o;
		}
		
	public:
		
		ContextComponent();
		
		void				Initialize() override;
		void				Uninitialize() override;
		void				PostLoadFileAny(String s);
		void				Update();
		void				CreatePackets();
		void				OnError(String fn, String msg);
		DevStreamState&		GetStreamState() {return stream;}
		
		
		Callback WhenError;
		
	};
	
	
};


NAMESPACE_TOPSIDE_END

#endif
