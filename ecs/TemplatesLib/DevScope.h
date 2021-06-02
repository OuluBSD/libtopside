#ifndef _TemplatesLib_DevScope_h_
#define _TemplatesLib_DevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevLibT {
	using D					= DevSpec;
	using ComponentBase		= typename DevSpec::ComponentBase;
	using Mach				= ScopeDevMachT<DevSpec>;
	using Core				= ScopeDevCoreT<DevSpec>;
	using Stream			= typename Mach::Stream;
	using ComponentConf		= typename Mach::ComponentConf;
	using SystemBase		= typename Mach::SystemBase;
	using CtxStream			= typename Mach::Stream;
	using SourceRef			= typename Core::SourceRef;
	using SinkRef			= typename Core::SinkRef;
	using ExchangePointRef	= typename Core::ExchangePointRef;
	
	class ContextComponent;
	using ContextComponentRef	= Ref<ContextComponent, RefParent1<Entity>>;
	class ComponentGroup;
	using ComponentGroupRef		= Ref<ComponentGroup, RefParent1<ContextComponent>>;
	
	
	#define RTTI_CTX_SYS(sys, base) \
			RTTI_DECL_2(sys, TS::System<sys>, base, DevSpec::GetName() + #sys)
	
	class System :
		public TS::System<System>,
		public SystemBase
	{
		LinkedList<ContextComponentRef> ctxs;
		
		LinkedList<SourceRef> srcs;
		LinkedList<SinkRef> sinks;
		LinkedList<ExchangePointRef> expts;
		
		void Visit(RuntimeVisitor& vis) override {
			vis && srcs
				&& sinks
				&& expts;
		}
	protected:
	    bool Initialize() override;
	    void Start() override;
	    void Update(double dt) override;
	    void Stop() override;
	    void Uninitialize() override;
	    
	public:
		RTTI_CTX_SYS(System, SystemBase)
	    SYS_CTOR(System)
		
		void Add(SourceRef src);
		void Add(SinkRef sink);
		void Add(ExchangePointRef sink);
		void AddCtx(ContextComponentRef ctx);
		void Remove(SourceRef src);
		void Remove(SinkRef sink);
		void Remove(ExchangePointRef sink);
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
	
	class Component :
		public TS::Component<Component>,
		public ComponentBase
	{
		RTTI_COMP0(Component);
		VIS_COMP_0_0
		COPY_PANIC(Component)
		void Visit(RuntimeVisitor& vis) override {}
		
	protected:
		ComponentGroupRef			ctx;
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
	
	
	
	class ComponentGroup :
		public RefScopeEnabler<ComponentGroup, ContextComponent>
	{
		
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
		Object			post_load;
		
		bool			LoadFileAny(String path, Object& dst);
		
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
