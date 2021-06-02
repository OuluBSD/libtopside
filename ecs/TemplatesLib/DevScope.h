#ifndef _TemplatesLib_DevScope_h_
#define _TemplatesLib_DevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevLibT {
	using D						= DevSpec;
	using DevComponentBase		= typename DevSpec::ComponentBase;
	using DevComponentGroupBase	= typename DevSpec::ComponentGroupBase;
	using Mach				= ScopeDevMachT<DevSpec>;
	using Core				= ScopeDevCoreT<DevSpec>;
	using Stream			= typename Mach::DevStream;
	using ComponentConf		= typename Mach::DevComponentConf;
	using SystemBase		= typename Mach::DevSystemBase;
	using CtxStream			= typename Mach::DevStream;
	using DevComponentConf	= typename Mach::DevComponentConf;
	//using SourceRef			= typename Core::SourceRef;
	//using SinkRef			= typename Core::SinkRef;
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
		DevComponentGroupRef		group;
		LinkedList<ComponentConf>	in;
		
		void				OnError(String fn, String msg);
		Stream*				Stream();
		
		virtual bool		LoadAsInput(const ComponentConf& in) = 0;
		virtual void		UpdateTexBuffers() = 0;
		virtual bool		IsEmptyStream() const = 0;
		virtual void		ClearStream() = 0;
		
		virtual void		PreProcess() {}
		
	public:
		
		void				Initialize();
		void				Uninitialize();
		bool				Load(ObjectMap& st_map, int stage_i, String frag_code);
		void				SetGroup(DevComponentGroupRef g) {group = g;}
		String				ToString() const {return GetTypeString() + " " + DevComponentBase::ToString();}
		String				GetTypeString() const {return GetStringFromType(RTTI::GetRTTI().GetTypeId());}
		
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
		TypeCls group_class;
		
	public:
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
		CtxStream			stream;
		Object				post_load;
		bool				is_open = false;
		
		void				Clear();
		void				Reset();
		void				FindComponents();
		void				DumpEntityComponents();
		bool				LoadFileAny(String path, Object& dst);
		bool				Load(Object& o);
		bool				RefreshStageQueue();
		void				RefreshStreamValuesAll();
		void				RefreshPipeline();
		void				OnError(String fn, String msg);
		DevComponentGroup&	GetAddGroupContext(TypeCls val_spec);
		bool				ConnectComponentInputs();
		bool				ConnectComponentOutputs();
		bool				CreateComponents(DevComponentConfVector& v);
		
		template<class ValSpec> DevComponentGroup&	GetAddGroupContext() {return GetAddGroupContext(AsTypeCls<ValSpec>());}
		
		
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
		
		Callback WhenError;
		
	};
	
	
};


NAMESPACE_TOPSIDE_END

#endif
