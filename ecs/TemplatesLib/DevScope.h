#ifndef _TemplatesLib_DevScope_h_
#define _TemplatesLib_DevScope_h_

NAMESPACE_ECS_BEGIN

/*
template <class DevSpec>
struct ScopeDevLibT {
	using D							= DevSpec;
	using StageComponentBase		= typename DevSpec::ComponentBase;
	using StageComponentGroupBase	= typename DevSpec::ComponentGroupBase;
	using Mach						= ScopeDevMachT<DevSpec>;
	using Core						= ScopeDevCoreT<DevSpec>;
	using StreamState				= typename Mach::DevStreamState;
	using SystemBase				= typename Mach::DevSystemBase;
	using DevStreamState			= typename Mach::DevStreamState;
	using StageComponentConf		= typename Mach::StageComponentConf;
	using DevSource					= typename Mach::DevSource;
	using DevSourceRef				= typename Mach::DevSourceRef;
	using DevSink					= typename Mach::DevSink;
	using DevSinkRef				= typename Mach::DevSinkRef;
	using DevComponent				= typename Mach::DevComponent;
	using DevComponentRef			= typename Mach::DevComponentRef;
	using DevContextConnectorBase	= typename Mach::DevContextConnectorBase;
	//using SourceRef			= typename Core::SourceRef;
	//using SinkRef				= typename Core::SinkRef;
	//using ExchangePointRef	= typename Core::ExchangePointRef;
	
	//class DevContextConnector;
	//using DevContextConnectorRef		= Ref<DevContextConnector, RefParent1<Pool>>;
	//class StageContextConnector;
	//using StageContextConnectorRef		= Ref<StageContextConnector, RefParent1<Pool>>;
	//class StageComponentGroup;
	//using StageComponentGroupRef		= Ref<StageComponentGroup, RefParent1<StageContextConnector>>;
	class StageComponent;
	using StageComponentRef				= Ref<StageComponent, RefParent1<Entity>>;
	

	static String TypeStringT(const char* t) {
		String s;
		s << DevSpec::GetName() << t;
		return s;
	}
		*/


class StageComponent;
using StageComponentRef = Ref<StageComponent, RefParent1<Entity>>;


struct StageComponentConfVector {
	Array<StageComponentConf> in;
	
	int Find(const StageComponentConf& a) const;
	void Add(const StageComponentConf& a);
};


#define RTTI_CTX_SYS(sys, base) \
		RTTI_DECL2(sys, System<sys>, base)

class DevSystem :
	public System<DevSystem>,
	public DevSystemBase
{
protected:
	friend class DevContextConnector;
	//LinkedList<StageContextConnectorRef> stages;
	//LinkedList<DevContextConnectorRef> devs;
	LinkedList<StageComponentRef> comps;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
	RTTI_CTX_SYS(DevSystem, DevSystemBase)
    SYS_CTOR(DevSystem)
	//SYS_DEF_VISIT_(vis && stages && devs && comps)
	SYS_DEF_VISIT_(vis && comps)
	
	//void AddStage(StageContextConnectorRef stage)		{ASSERT(stage); stages.FindAdd(stage);}
	//void RemoveStage(StageContextConnectorRef stage)	{stages.RemoveKey(stage);}
	//void AddDev(DevContextConnectorRef dev)				{ASSERT(dev); devs.FindAdd(dev);}
	//void RemoveDev(DevContextConnectorRef dev)			{devs.RemoveKey(dev);}
	void AddComp(StageComponentRef comp)				{ASSERT(comp); comps.FindAdd(comp);}
	void RemoveComp(StageComponentRef comp)				{comps.RemoveKey(comp);}
	
	static inline Callback& WhenUninit() {static Callback cb; return cb;}
	
	
	
};

#undef RTTI_CTX_SYS


class StageComponent :
	/*public StageComponentBase,*/
	public WeakRefScopeEnabler<StageComponent, Entity>,
	virtual public PacketForwarder
{
	RTTI_DECL1(StageComponent, PacketForwarder);
	void Visit(RuntimeVisitor& vis) {}
	
protected:
	friend class StageComponentGroup;
	//friend StageComponentBase;
	
	//StageComponentGroupRef			group;
	LinkedList<StageComponentConf>	in;
	int								id = -1;
	int								pos = -1;
	bool							is_open = false;
	
	bool				Open();
	void				Clear();
	void				Close();
	DevStreamState&		GetDevStreamState();
	
	
	virtual bool		LoadAsInput(const StageComponentConf& in) = 0;
	virtual void		UpdateDevBuffers() = 0;
	virtual bool		IsEmptyStream() const = 0;
	virtual void		ClearStream() = 0;
	virtual bool		IsValSpec(TypeCls) const = 0;
	
	virtual void		PreProcess() {}
	void				PostProcess();
	
public:
	virtual TypeCls		GetValSpec() const = 0;
	
	
	void				Initialize();
	void				Uninitialize();
	bool				Load(ObjectMap& st_map, int stage_i, String frag_code);
	//void				SetGroup(StageComponentGroupRef g) {group = g;}
	void				OnError(String fn, String msg);
	
	int					GetId() const {return id;}
	int					GetPos() const {return pos;}
	bool				IsOpen() const {return is_open;}
	String				ToString() const {return GetTypeString() + " (id: " + IntStr(id) + ")";}
	String				GetTypeString() const {return GetStringFromType(RTTI::GetRTTI().GetTypeId());}
	//DevStreamState&		GetStreamState();
	
	//StageComponentGroupRef GetGroup() const {return group;}
	const LinkedList<StageComponentConf>& GetInputs() const {return in;}
	
	static String		GetStringFromType(TypeCls i);
	static bool			IsDevPipeComponent(TypeCls type);
	
	void UpdateDevBuffersValT();
	//template <class ValSpec> bool IsIn() const {return IsValSpec(AsTypeCls<ValSpec>());}
	void ForwardPacket(ValCls dst, FwdScope& fwd, Packet p);
	//template <class FromDevSpec, class ValSpec> void ConvertPacket(Packet& p);
	
	virtual bool		RequiresDeviceProgram() const {return false;}
	
};



#if 0
class DevContextConnector :
	public TS::Connector<DevContextConnector>,
	public DevContextConnectorBase
{
	using Connector = TS::Connector<DevContextConnector>;
	RTTI_DECL_T2(DevContextConnector, Connector, DevContextConnectorBase)
	COPY_PANIC(DevContextConnector)
	void Visit(RuntimeVisitor& vis) override {}
	
	
private:
	LinkedList<DevComponentRef>	devs;
	LinkedList<DevSourceRef>	srcs;
	LinkedList<DevSinkRef>		sinks;
	DevStreamState				stream;
	
	
public:
	
	DevContextConnector();
	
	void				Initialize() override;
	void				Uninitialize() override;
	void				Update(double dt) override;
	void				ForwardPackets(double dt);
	DevStreamState&		GetStreamState() {return stream;}
	
	void				FindAdd(DevComponentRef c);
	void				Remove(DevComponentRef c);
	void				AddCtx(DevSourceRef r);
	void				AddCtx(DevSinkRef r);
	void				RemoveCtx(DevSourceRef r);
	void				RemoveCtx(DevSinkRef r);
	
	
	Callback WhenError;
	
};



class StageComponentGroup :
	public RefScopeEnabler<StageComponentGroup, StageContextConnector>,
	public StageComponentGroupBase
{
	LinkedList<StageComponentRef> comps;
	
protected:
	friend class StageContextConnector;
	TypeCls val_spec;
	
public:
	RTTI_DECL_R1(StageComponentGroup, StageComponentGroupBase)
	
	bool				Open();
	void				Close();
	void				CloseTemporary();
	void				Clear();
	void				FindUniqueInputs(StageComponentConfVector& v);
	void				ConnectInputs(StageComponentConfVector& v);
	bool				LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code);
	void				FindAdd(StageComponentRef r);
	void				Remove(StageComponentRef r);
	void				UpdateCompFlags();
	void				UpdateDevBuffers();
	bool				ForwardPackets();
	void				DumpComponents();
	bool				CheckDevice();
	
	bool				IsValSpec(TypeCls t) const override {return t == val_spec;}
	DevStreamState&		GetStreamState() override {return GetParent()->GetStreamState();}
	TypeCls				GetValSpec() const {return val_spec;}
	StageComponentRef		GetComponentById(int id) const;
	
	const LinkedList<StageComponentRef>& GetComponents() const {return comps;}
	LinkedList<StageComponentRef>& GetComponents() {return comps;}
	
	StageContextConnector* GetParent() {return RefScopeEnabler<StageComponentGroup, StageContextConnector>::GetParent();}
	
};


class StageContextConnector :
	public TS::Connector<StageContextConnector>,
	public ContextConnectorBase
{
	using Connector = TS::Connector<StageContextConnector>;
	RTTI_DECL_T2(StageContextConnector, Connector, ContextConnectorBase)
	COPY_PANIC(StageContextConnector)
	void Visit(RuntimeVisitor& vis) override {}
	
	
private:
	LinkedList<StageComponentGroup>		groups;
	Vector<String>		common_source;
	DevStreamState		stream;
	Object				post_load;
	bool				is_open = false;
	
	void				Clear();
	void				Reset();
	void				Close();
	void				DumpEntityComponents();
	bool				LoadFileAny(String path, Object& dst);
	bool				Load(Object& o);
	bool				RefreshStageQueue();
	void				RefreshStreamValuesAll();
	void				RefreshPipeline();
	StageComponentGroup&	GetAddGroupContext(TypeCls val_spec);
	bool				ConnectComponentInputs();
	bool				ConnectComponentOutputs();
	bool				CreateComponents(StageComponentConfVector& v);
	bool				CheckDevice();
	
	template <class ValSpec>	bool ConnectComponentOutputsT(StageComponentGroup& gr);
	template <class ValSpec>	StageComponentGroup&	GetAddGroupContext() {return GetAddGroupContext(AsTypeCls<ValSpec>());}
	
	
	template <class T> RefT_Entity<T> AddEntityComponent(StageComponentGroup& g) {
		RefT_Entity<T> o = ComponentBase::GetEntity()->template Add<T>();
		o->SetGroup(g.template AsRef<StageComponentGroup>());
		g.FindAdd(o);
		return o;
	}
	
public:
	
	StageContextConnector();
	
	void				Initialize() override;
	void				Uninitialize() override;
	void				Update(double dt) override;
	void				FindComponents();
	void				PostLoadFileAny(String s);
	bool				ForwardPackets();
	bool				ForwardPackets(StageComponentGroup& gr);
	void				OnError(String fn, String msg);
	DevStreamState&		GetStreamState() {return stream;}
	bool				IsOpen() const {return is_open;}
	void				FindAdd(StageComponentRef c);
	void				Remove(StageComponentRef c);
	
	const Vector<String>& GetCommonSources() const {return common_source;}
	
	
	Callback WhenError;
	
};
#endif
	
//};





NAMESPACE_ECS_END

#endif
