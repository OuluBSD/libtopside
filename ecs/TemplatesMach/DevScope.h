#ifndef _TemplatesMach_DevScope_h_
#define _TemplatesMach_DevScope_h_

NAMESPACE_ECS_BEGIN




// Specifier
#define DEV(x, pre, var, lowercase) \
struct x##Spec : RTTIBase {\
	RTTI_DECL0(x##Spec) \
	static String GetName() {return #x;}\
	static String GetPrefix() {return #pre;}\
	static String GetNameLower() {return #lowercase;}\
	using ComponentGroupBase = x##ComponentGroupBase; \
	using ComponentConfBase = x##ComponentConfBase; \
	using ComponentBase = x##ComponentBase; \
};
DEV_FULL_LIST
#undef DEV



// A hack for GCC to enable template specialization inside template
/*template <class ValSpec>
struct StreamStateGetter {};
#define IFACE(cls, var) \
template <> \
struct StreamStateGetter<cls##Spec> {\
	template <class Stream> \
	typename ScopeValMachT<cls##Spec>::ValStreamState& \
		Get(Stream* s) {return s->var;} \
};
IFACE_VAR_LIST
#undef IFACE*/




class DevFormat : RTTIBase {
	RTTI_DECL0(DevFormat)
	
	
};


struct StageComponentConf /*:
	public DevSpec::ComponentConfBase*/
{
	int id = -1;
	
	
	void				SetId(int i) {id = i;}
	
	int					GetId() const {return id;}
	String				ToString() const;// {return DevSpec::ComponentConfBase::ToString() + " (id: " + IntStr(id) + ")";}
	
	// see AccelComponentConfBase
	bool				IsEqualHeader(const StageComponentConf& in) const {TODO}
	
};


struct InternalPacketData : RTTIBase {
	RTTI_DECL0(InternalPacketData)
	
	int pos;
	int count;
	void* dev_comp;
	
	void ClearLinks() {dev_comp = 0;}
};

struct DevSink :
	public WeakRefScopeEnabler<DevSink, Entity>,
	RTTIBase
{
	RTTI_DECL0(DevSink)
	void Visit(RuntimeVisitor& vis) {}
	
};

struct DevSource :
	public WeakRefScopeEnabler<DevSink, Entity>,
	RTTIBase
{
	RTTI_DECL0(DevSource)
	void Visit(RuntimeVisitor& vis) {}
	
};

class DevContextConnectorBase :
	public WeakRefScopeEnabler<DevContextConnectorBase, Pool>,
	RTTIBase
{
	RTTI_DECL0(DevContextConnectorBase)
	
};

using DevContextConnectorBaseRef = Ref<DevContextConnectorBase, RefParent1<Pool>>;


class DevComponentBase :
	public WeakRefScopeEnabler<DevComponentBase, Entity>,
	RTTIBase
{
	DevContextConnectorBaseRef ctx;
public:
	RTTI_DECL0(DevComponentBase)
	
	virtual TypeCls GetValSpec() const = 0;
	virtual void ForwardPackets(double dt) = 0;
	
	void ClearContext() {ctx.Clear();}
	void SetContext(DevContextConnectorBaseRef r) {ctx = r;}
	DevContextConnectorBaseRef GetContext() {return ctx;}
	
	void Initialize();
	void Uninitialize();
};

using DevSinkRef			= Ref<DevSink, RefParent1<Entity>>;
using DevSourceRef			= Ref<DevSource, RefParent1<Entity>>;
using DevComponentBaseRef	= Ref<DevComponentBase, RefParent1<Entity>>;




// This class enables device to process all interface types at once, like
// when OpenGL shader processes all types of data in single pipeline.
/*class DevExchangePoint :
	public ExchangePoint
{
	ConnectorBase* conn = 0;
	off32 offset;
	bool use_consumer = false;
	bool dbg_offset_is_set = false;
	
public:
	RTTI_DECL1(DevExchangePoint, ExchangePoint)
	typedef DevExchangePoint CLASSNAME;
	DevExchangePoint() {}
	~DevExchangePoint() {Deinit();}
	
	void Init(ConnectorBase* conn);
	void Deinit();
	void Update(double dt) override {Update0(dt);} // hack: call non-virtual to prevent linking error
	void Update0(double);
	
	void SetOffset(off32 o) {offset = o; dbg_offset_is_set = true;}
	void UseConsumer(bool b=true) {use_consumer = b;}
	void Destroy() {conn = 0;}
	
	off32 GetOffset() const {return offset;}
	
};*/


/*class Ex;

class DevValue :
	RTTIBase,
	virtual public RealtimeStream
{
	
public:
	RTTI_DECL1(DevValue, RealtimeStream)
	DevValue() = default;
	virtual ~DevValue() = default;
	
	virtual void Exchange(Ex& e) = 0;
	virtual int GetQueueSize() const = 0;
	virtual DevFormat GetFormat() const = 0;
	virtual bool IsQueueFull() const = 0;
	
};*/




class DevSystemBase : RTTIBase
{
public:
	RTTI_DECL0(DevSystemBase)
	
};


class DevStreamState : RTTIBase
{
public:
	RTTI_DECL0(DevStreamState)
	
	using State = ValStreamState;
	
	
	// Generic
	Time time;
	TimeStop total_time;
	int time_us = 0;
	
	
	State& Get(ValCls val) {
		TODO //return StreamStateGetter<ValSpec>().template Get<DevStreamState>(this);
	}
	
	// Context states & formats
	/*#define IFACE(cls, var) \
		State<cls##Spec> var;
	IFACE_VAR_LIST
	#undef IFACE*/
	
	void Reset(TypeCls val_spec) {
		TODO
		/*#define IFACE(cls, var) if (val_spec == AsTypeCls<cls##Spec>()) {var.Reset(); return;}
		IFACE_VAR_LIST
		#undef IFACE*/
	}
	
	void Step(TypeCls val_spec) {
		TODO
		/*#define IFACE(cls, var) if (val_spec == AsTypeCls<cls##Spec>()) {var.Step(); return;}
		IFACE_VAR_LIST
		#undef IFACE*/
	}
	
	virtual int				GetActiveFormatIdx() const {return 0;}
	virtual int				GetFormatCount() const {return 1;}
	virtual bool			FindClosestFormat(const DevFormat& fmt, int& idx) {idx = 0; return true;}
	virtual bool			LoadFileAny(String path) {return false;}
	
	void Clear();
	void Reset();
	void UpdateValuesBase();
	void UpdateValues(TypeCls val_spec);
	
	
	
	/*
	// Controller
	Point mouse, mouse_toycompat_drag, mouse_toycompat_click;
	
	
	
	// Video
	SystemDraw* draw = 0;
	Size video_size;
	Point video_offset;
	TimeStop vframe_time;
	double vtotal_seconds = 0;
	int vframes = 0;
	double fps_limit = 60;
	int depth = 0;
	
	
	AccelStream() {Clear();}
	void Clear();
	void Reset();
	*/
};




NAMESPACE_ECS_END

#endif
