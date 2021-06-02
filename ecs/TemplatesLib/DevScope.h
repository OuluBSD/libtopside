#ifndef _TemplatesLib_DevScope_h_
#define _TemplatesLib_DevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevLibT {
	using D					= DevSpec;
	using ComponentBase		= typename DevSpec::ComponentBase;
	using Mach				= ScopeDevMachT<DevSpec>;
	using Core				= ScopeDevCoreT<DevSpec>;
	using Stream			= typename Mach::DevStream;
	using ComponentConf		= typename Mach::DevComponentConf;
	using SystemBase		= typename Mach::DevSystemBase;
	using CtxStream			= typename Mach::DevStream;
	//using SourceRef			= typename Core::SourceRef;
	//using SinkRef			= typename Core::SinkRef;
	//using ExchangePointRef	= typename Core::ExchangePointRef;
	
	class ContextComponent;
	using ContextComponentRef		= Ref<ContextComponent, RefParent1<Entity>>;
	class DevComponentGroup;
	using DevComponentGroupRef		= Ref<DevComponentGroup, RefParent1<ContextComponent>>;
	
	
	#define RTTI_CTX_SYS(sys, base) \
			RTTI_DECL_2(sys, System<sys>, base, DevSpec::GetName() + #sys)
	
	class DevSystem :
		public System<DevSystem>,
		public SystemBase
	{
		LinkedList<ContextComponentRef> ctxs;
		
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
		public Component<DevComponent>,
		public ComponentBase
	{
		RTTI_COMP0(DevComponent);
		VIS_COMP_0_0
		COPY_PANIC(DevComponent)
		void Visit(RuntimeVisitor& vis) override {}
		
	protected:
		DevComponentGroupRef		ctx;
		LinkedList<ComponentConf>	in;
		
		void				OnError(String fn, String msg);
		Stream*				Stream();
		
		virtual bool		LoadAsInput(const ComponentConf& in) = 0;
		virtual void		UpdateTexBuffers() = 0;
		virtual bool		IsEmptyStream() const = 0;
		virtual void		ClearStream() = 0;
		
	public:
		
		static String		GetStringFromType(TypeCls t);
		
		template <class ValSpec> void UpdateTexBuffersValT();
		template <class ValSpec> bool IsIn() {return IsValSpec(AsTypeCls<ValSpec>());}
		
		
		
	};
	
	
	
	class DevComponentGroup :
		public RefScopeEnabler<DevComponentGroup, ContextComponent>
	{
	public:
		bool Open();
		void CloseTemporary();
		void Clear();
		void FindComponents();
		
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
		Vector<String>	common_source;
		CtxStream		stream;
		Object			post_load;
		bool			is_open = false;
		
		void			Clear();
		void			Reset();
		void			FindComponents();
		void			DumpEntityComponents();
		bool			LoadFileAny(String path, Object& dst);
		bool			Load(Object& o);
		bool			RefreshStageQueue();
		void			RefreshStreamValuesAll();
		void			RefreshPipeline();
		
	public:
		
		ContextComponent();
		
		void			Initialize() override;
		void			Uninitialize() override;
		void			PostLoadFileAny(String s);
		void			Update();
		void			CreatePackets();
		
		Callback WhenError;
		
	};
	
	
};


NAMESPACE_TOPSIDE_END

#endif
