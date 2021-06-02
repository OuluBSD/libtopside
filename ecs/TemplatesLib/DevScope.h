#ifndef _TemplatesLib_DevScope_h_
#define _TemplatesLib_DevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevLibT {
	using ComponentBase = typename DevSpec::ComponentBase;
	using ComponentConf = typename ContextDevMachT<DevSpec>::ComponentConf;
	using Stream = typename ContextDevMachT<DevSpec>::Stream;
	
	class ContextComponent;
	class ComponentGroup;
	using ComponentGroupRef		= Ref<ComponentGroup, RefParent1<ContextComponent>>;
	
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
		static int id_counter;
		
	private:
		Object			post_load;
		
		bool			LoadFileAny(String path, Object& dst);
		
	public:
		
		ContextComponent();
		
		void PostLoadFileAny(String s);
		
		
		Callback WhenError;
		
	};
	
	
};


NAMESPACE_TOPSIDE_END

#endif
