#ifndef _TemplatesCore_ValDevScope_h_
#define _TemplatesCore_ValDevScope_h_

NAMESPACE_ECS_BEGIN


/*template <class ValDevSpec>
struct ScopeValDevCoreT {
	using ValSpec			= typename ValDevSpec::Val;
	using DevSpec			= typename ValDevSpec::Dev;
	using Data				= ScopeValMachT<ValSpec>;
	using Mach				= ScopeValDevMachT<ValDevSpec>;
	using DevMach			= ScopeDevMachT<DevSpec>;
	using V					= ValSpec;
	using Format			= typename Data::Format;
	using ValueBase			= typename ValSpec::ValueBase;
	using StreamBase		= typename ValSpec::StreamBase;
	using SystemBase		= typename ValSpec::SystemBase;
	using SinkBase			= typename ValSpec::SinkBase;
	using Value				= typename Mach::Value;
	using CtxStream			= typename Mach::Stream;
	using ValExchangePoint	= typename Mach::ValExchangePoint;
	using DevSource			= typename DevMach::DevSource;
	using DevSink			= typename DevMach::DevSink;*/


class ValSink :
	public InterfaceSink,
	/*public SinkBase,*/
	public DevSink,
	RTTIBase
{
	
public:
	RTTI_DECL2(ValSink, InterfaceSink, DevSink)
	
	ValSink() {}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSink>(this);
		//vis.VisitThis<SinkBase>(this);
		vis.VisitThis<DevSink>(this);
	}
	
	//TypeCls GetTypeCls() override {return TypeId(AsTypeCls<ValDevSpec>());}
	
	virtual Value&				GetValue() = 0;
	virtual void				ClearSink() override {GetValue().Clear();}
	
};

class ValSource :
	public InterfaceSource,
	public DevSource,
	RTTIBase
{
	ValDevCls src;
	ValDevCls sink;
	
public:
	RTTI_DECL2(ValSource, InterfaceSource, DevSource)
	
	ValSource() {}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSource>(this);
		vis.VisitThis<DevSource>(this);
	}
	
	//ValDevCls GetTypeCls() override;// {return TypeId(AsTypeCls<ValDevSpec>());}
	
	using ExPt = ValExchangePoint;
	using Sink = ValSink;
	
	
	/*void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
	const RealtimeSourceConfig&	Cfg() const {return cfg;}
	void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}*/
	
	//DevCls						GetDevSpec() const override;// {return AsTypeCls<DevSpec>();}
	virtual Stream&				GetStream() = 0;
	virtual void				ClearSource() override {GetStream().Clear();}
private:
	
};

using ValSourceRef			= Ref<ValSource,		RefParent1<Entity>>;
using ValSinkRef			= Ref<ValSink,			RefParent1<Entity>>;
using ValExchangePointRef	= Ref<ValExchangePoint,	RefParent1<MetaExchangePoint>>;


#define RTTI_CTX_SYS(sys, base) \
		RTTI_DECL_2(sys, System<sys>, base, ValDevSpec::GetName() + #sys)

#if HAVE_VALSYSTEM
class ValSystem :
	public System<ValSystem>,
	public SystemBase
{
	LinkedList<ValSourceRef> srcs;
	LinkedList<ValSinkRef> sinks;
	LinkedList<ValExchangePointRef> expts;
	
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
	RTTI_CTX_SYS(ValSystem, SystemBase)
    SYS_CTOR(ValSystem)
	SYS_DEF_VISIT_(vis && srcs && sinks && expts)
	
	void Add(ValSourceRef src);
	void Add(ValSinkRef sink);
	void Add(ValExchangePointRef sink);
	void Remove(ValSourceRef src);
	void Remove(ValSinkRef sink);
	void Remove(ValExchangePointRef sink);
	
	static inline Callback& WhenUninit() {static Callback cb; return cb;}
	
};
#endif

#undef RTTI_CTX_SYS
	
//};


NAMESPACE_ECS_END

#endif
