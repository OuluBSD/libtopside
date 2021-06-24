#ifndef _TemplatesLib_ValDevScope_h_
#define _TemplatesLib_ValDevScope_h_

NAMESPACE_ECS_BEGIN


/*template <class ValDevSpec>
struct ScopeValDevLibT {
	using ValSpec					= typename ValDevSpec::Val;
	using DevSpec					= typename ValDevSpec::Dev;
	using ValMach					= ScopeValMachT<ValSpec>;
	using Mach						= ScopeValDevMachT<ValDevSpec>;
	using Core						= ScopeValDevCoreT<ValDevSpec>;
	using DevCore					= ScopeDevCoreT<DevSpec>;
	using V							= ValSpec;
	using Packet					= typename ValMach::Packet;
	using Format					= typename Mach::Format;
	using ValueBase					= typename Mach::ValueBase;
	using StreamBase				= typename Mach::StreamBase;
	using Value						= typename Mach::Value;
	using CtxStream					= typename Mach::Stream;
	using ValExchangePoint			= typename Mach::ValExchangePoint;
	using SimpleValue				= typename Mach::SimpleValue;
	using SimpleBufferedValue		= typename Mach::SimpleBufferedValue;
	using SimpleStream				= typename Mach::SimpleStream;
	using SimpleBufferedStream		= typename Mach::SimpleBufferedStream;
	using PacketConsumer			= typename Mach::PacketConsumer;
	using ValSink					= typename Core::ValSink;
	using ValSource					= typename Core::ValSource;
	using DevCompConf				= typename ScopeDevMachT<DevSpec>::StageComponentConf;
	using StageComponent			= typename ScopeDevLibT<DevSpec>::StageComponent;*/
	
	/*
	using ValSpec					= typename ValDevSpec::Val;
	using DevSpec					= typename ValDevSpec::Dev;
	using ValMach					= ScopeValMachT<ValSpec>;
	using Mach						= ScopeValDevMachT<ValDevSpec>;
	using Core						= ScopeValDevCoreT<ValDevSpec>;
	using V							= ValSpec;
	using Packet					= typename ValMach::Packet;
	using ValSink					= typename Core::ValSink;
	using ValSource					= typename Core::ValSource;
	using Format					= typename Mach::Format;
	using SimpleValue				= typename Mach::SimpleValue;
	using SimpleStream				= typename Mach::SimpleStream;
	using CtxStream					= typename Mach::Stream;
	*/
	
	/*using R							= ReceiptSpec;
	using RVD						= VD<DevSpec,ReceiptSpec>;
	using RValMach					= ScopeValMachT<ReceiptSpec>;
	using RMach						= ScopeValDevMachT<RVD>;
	using RCore						= ScopeValDevCoreT<RVD>;
	using RPacket					= typename RValMach::Packet;
	using RFormat					= typename RMach::Format;
	using RStream					= typename RMach::Stream;
	using RSimpleStream				= typename RMach::SimpleStream;
	using RValue					= typename RMach::Value;
	using RSink						= typename RCore::ValSink;
	using RSource					= typename RCore::ValSource;
	using RSimpleValue				= typename RMach::SimpleValue;
	
	using O							= OrderSpec;
	using OVD						= VD<DevSpec,OrderSpec>;
	using OValMach					= ScopeValMachT<OrderSpec>;
	using OMach						= ScopeValDevMachT<OVD>;
	using OCore						= ScopeValDevCoreT<OVD>;
	using OPacket					= typename OValMach::Packet;
	using OFormat					= typename OMach::Format;
	using OSimpleStream				= typename OMach::SimpleStream;
	using OStream					= typename OMach::Stream;
	using OValue					= typename OMach::Value;
	using OSink						= typename OCore::ValSink;
	using OSource					= typename OCore::ValSource;
	using OSimpleValue				= typename OMach::SimpleValue;*/
	
	

class InputComponent;
class OutputComponent;
class PipeComponent;

/*static String TypeStringT(const char* t) {
	String s;
	s << ValDevSpec::GetPrefix() << t;
	return s;
}*/





class InputExt : public ComponentExtBase {
	
public:
	RTTI_DECL1(InputExt, ComponentExtBase);
	using Ext = InputExt;
	using Component = InputComponent;
	
};



class InputComponent :
	public Component<InputComponent, InputExt>
{
	ValDevCls vd;
	
public:
	using ComponentT = Component<InputComponent, InputExt>;
	RTTI_DECL1(InputComponent, ComponentT)
	COPY_PANIC(InputComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE(
			ToLower(vd.dev.GetName()) + "." +
			ToLower(vd.val.GetName()) + "." +
			"src")
	COMP_MAKE_ACTION_END
	
private:
	struct LocalSinkValue : public SimpleValue {
		InputComponent& par;
		
		LocalSinkValue(InputComponent* par) : par(*par) {}
		void StorePacket(Packet& p) override {TODO}
	};
	
	struct LocalSourceValue : public SimpleValue {
		void StorePacket(Packet& p) override {}
	};
	
	struct LocalSourceStream : public SimpleStream {
		InputComponent& par;
		PacketConsumer consumer;
		
		RTTI_DECL1(LocalSourceStream, SimpleStream)
		LocalSourceStream(InputComponent* par) :
			par(*par),
			SimpleStream(par->src_value) {}
		
	};
	
	LocalSinkValue		sink_value;
	LocalSourceValue	src_value;
	LocalSourceStream	src_stream;
	
	
	bool				ReadFrame();
	bool				ProcessDeviceFrame();
	
public:
	InputComponent() : sink_value(this), src_stream(this) {}
	
	void				Forward(FwdScope& fwd) override;
	void				ForwardExchange(FwdScope& fwd) override;
	EcsTypeCls			GetEcsCls() const override {return EcsTypeCls(vd, EcsTypeCls::COMP_IN);}
	
	// OSink
	Value&				GetValue() override {return sink_value;}
	
	// ValSource
	Stream&				GetStream() override {return src_stream;}
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_IN;}
	
};



class OutputExt : public ComponentExtBase {
	
public:
	RTTI_DECL1(OutputExt, ComponentExtBase);
	using Ext = OutputExt;
	using Component = OutputComponent;
	
	OutputComponent& GetParentT() {return CastRef<OutputComponent>(GetParent().o);}
	
};



class OutputComponent :
	public Component<OutputComponent, OutputExt>
{
public:
	using ComponentT = Component<OutputComponent, OutputExt>;
	RTTI_DECL1(OutputComponent, ComponentT)
	COPY_PANIC(OutputComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT_(vis & cust_sys)
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE(
			ToLower(vd.dev.GetName()) + "." +
			ToLower(vd.val.GetName()) + "." +
			"sink")
	COMP_MAKE_ACTION_END
	
private:
	struct LocalSinkValue : public SimpleBufferedValue {
		OutputComponent& par;
		
		LocalSinkValue(OutputComponent* par) : par(*par) {}
	};
	
	struct LocalSourceValue : public SimpleValue {
		void StorePacket(Packet& p) override {}
	};
	
	struct LocalSourceStream : public SimpleStream {
		OutputComponent& par;
		
		RTTI_DECL1(LocalSourceStream, SimpleStream)
		LocalSourceStream(OutputComponent* par) :
			par(*par),
			SimpleStream(par->src_value) {}
		
	};
	
	
	LocalSinkValue			sink_value;
	LocalSourceValue		src_value;
	LocalSourceStream		src_stream;
	RealtimeSourceConfig*	cfg = 0;
	
	Mutex					lock;
	LinkedList<Packet>		consumed_packets;
	PacketConsumer			consumer;
	CustomerSystemRef		cust_sys;
	
	
public:
	OutputComponent() : sink_value(this), src_stream(this) {}
	
	void				Initialize() override;
	void				Uninitialize() override;
	void				Forward(FwdScope& fwd) override;
	void				ForwardExchange(FwdScope& fwd) override;
	bool				ForwardMem(void* mem, size_t mem_size);
	EcsTypeCls			GetEcsCls() const override {return EcsTypeCls(vd, EcsTypeCls::COMP_OUT);}
	
	// ValSink
	Value&				GetValue() override {return sink_value;}
	
	// RSource
	Stream&				GetStream() override {return src_stream;}
	
	bool				ReadFrame() {TODO}
	bool				ProcessFrame() {TODO}
	bool				ProcessDeviceFrame() {TODO}
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_OUT;}
	
};


class PipeExt : public ComponentExtBase {
	
public:
	RTTI_DECL1(PipeExt, ComponentExtBase);
	using Ext = PipeExt;
	using Component = PipeComponent;
	
};

class PipeComponent :
	public Component<PipeComponent, PipeExt>,
	public StageComponent
{
public:
	using ComponentT = Component<PipeComponent, PipeExt>;
	RTTI_DECL2(PipeComponent, ComponentT, StageComponent)
	COPY_PANIC(PipeComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		// TODO Probably should decrease count of allowed pipes, otherwise actionplanner creates
		// these infinitely.
		//COMP_MAKE_ACTION_REQ_TRUE(DevSpec::GetNameLower() + "." + ValSpec::GetNameLower() + ".pipe")
	COMP_MAKE_ACTION_END
	
private:
	class LocalSinkValue : public SimpleBufferedValue {
	public:
		RTTI_DECL1(LocalSinkValue, SimpleBufferedValue)
	};
	
	class LocalSourceValue : public SimpleBufferedValue {
	public:
		RTTI_DECL1(LocalSourceValue, SimpleBufferedValue)
	};
	
	// TODO: select source/sink format based on cheap troughput/storage using template arg
	class LocalStream :
		public SimpleBufferedStream,
		RTTIBase
	{
	public:
		PipeComponent& par;
		RTTI_DECL1(LocalStream, SimpleBufferedStream);
		LocalStream(PipeComponent* p) : par(*p), SimpleBufferedStream(p->src_value) {}
		bool			IsOpen() const override {TODO}
		bool			Open(int fmt_idx) override {TODO}
		void			Close() override {TODO}
		bool			IsEof() override {TODO}
		bool			ReadFrame() override {TODO}
		bool			ProcessFrame() override {TODO}
		bool			ProcessOtherFrame() override {TODO}
		void			ClearPacketData() override {TODO}
	};
	LocalSinkValue		sink_value;
	LocalSourceValue	src_value;
	LocalStream			src_stream;
	
public:
	PipeComponent() : src_stream(this) {}
	
	// ComponentBase
	void				Initialize() override;
	void				Uninitialize() override;
	bool				RequiresDeviceProgram() const override {return true;}
	void				Forward(FwdScope& fwd) override;
	void				ForwardExchange(FwdScope& fwd) override;
	EcsTypeCls			GetEcsCls() const override {return EcsTypeCls(vd, EcsTypeCls::COMP_PIPE);}
	bool				IsValSpec(ValCls c) const override {return vd.val == c;}
	ValCls				GetValSpec() const override {return vd.val;}
	
	// DevSink
	Value&				GetValue() override;
	
	// DevSource
	Stream&				GetStream() override;
	
	// StageComponent
	bool				LoadAsInput(const StageComponentConf& in) override;
	void				UpdateDevBuffers() override {StageComponent::UpdateDevBuffersValT();}
	bool				IsEmptyStream() const override {return src_value.IsEmpty() && sink_value.IsEmpty();}
	void				ClearStream() override {src_value.ClearBuffer(); sink_value.ClearBuffer();}
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_PIPE;}
	
};









class SideOutputComponent;

class SideOutExt : public ComponentExtBase {
	
public:
	RTTI_DECL1(SideOutExt, ComponentExtBase);
	using Ext = SideOutExt;
	using Component = SideOutputComponent;
	
};

class SideOutputComponent :
	public Component<SideOutputComponent, SideOutExt>
{
public:
	using ComponentT = Component<SideOutputComponent, SideOutExt>;
	RTTI_DECL1(SideOutputComponent, ComponentT)
	COPY_PANIC(SideOutputComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		//COMP_MAKE_ACTION_REQ_TRUE(DevSpec::GetNameLower() + "." + ValSpec::GetNameLower() + ".pipe")
	COMP_MAKE_ACTION_END
	
private:
	class LocalSinkValue : public SimpleValue {
	public:
		RTTI_DECL1(LocalSinkValue, SimpleValue)
		void StorePacket(Packet& p) override {}
	};
	
	struct LocalSourceValue : public SimpleValue {
		void StorePacket(Packet& p) override {}
	};
	
	struct LocalSourceStream : public SimpleStream {
		SideOutputComponent& par;
		PacketConsumer consumer;
		
		RTTI_DECL1(LocalSourceStream, SimpleStream)
		LocalSourceStream(SideOutputComponent* par) :
			par(*par),
			SimpleStream(par->src_value) {}
		
	};
	
	LocalSinkValue		sink_value;
	LocalSourceValue	src_value;
	LocalSourceStream	src_stream;
	
public:
	SideOutputComponent() : src_stream(this) {}
	
	// ComponentBase
	void				Initialize() override;
	void				Uninitialize() override;
	void				Forward(FwdScope& fwd) override;
	void				ForwardExchange(FwdScope& fwd) override;
	EcsTypeCls			GetEcsCls() const override {return EcsTypeCls(vd, EcsTypeCls::COMP_SIDE_OUT);}
	
	// ValSink
	Value&				GetValue() override;
	
	// ReceiptSource
	Stream&				GetStream() override;
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_SIDE_OUT;}
	
};



class SideInputComponent;

class SideInExt : public ComponentExtBase {
	
public:
	RTTI_DECL1(SideInExt, ComponentExtBase);
	using Ext = SideInExt;
	using Component = SideInputComponent;
	
};

class SideInputComponent :
	public Component<SideInputComponent, SideInExt>
{
public:
	using ComponentT = Component<SideInputComponent, SideInExt>;
	RTTI_DECL1(SideInputComponent, ComponentT)
	COPY_PANIC(SideInputComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		//COMP_MAKE_ACTION_REQ_TRUE(DevSpec::GetNameLower() + "." + ValSpec::GetNameLower() + ".pipe")
	COMP_MAKE_ACTION_END
	
private:
	class LocalSinkValue : public SimpleValue {
	public:
		RTTI_DECL1(LocalSinkValue, SimpleValue)
		void StorePacket(Packet& p) override {}
	};
	
	struct LocalSourceValue : public SimpleValue {
		void StorePacket(Packet& p) override {}
	};
	
	struct LocalSourceStream : public SimpleStream {
		SideInputComponent& par;
		PacketConsumer consumer;
		
		RTTI_DECL1(LocalSourceStream, SimpleStream)
		LocalSourceStream(SideInputComponent* par) :
			par(*par),
			SimpleStream(par->src_value) {}
		
	};
	LocalSinkValue		sink_value;
	LocalSourceValue	src_value;
	LocalSourceStream	src_stream;
	
public:
	SideInputComponent() : src_stream(this) {}
	
	// ComponentBase
	void				Initialize() override;
	void				Uninitialize() override;
	void				Forward(FwdScope& fwd) override;
	void				ForwardExchange(FwdScope& fwd) override;
	EcsTypeCls			GetEcsCls() const override {return EcsTypeCls(vd, EcsTypeCls::COMP_SIDE_IN);}
	
	// OrderSink
	Value&				GetValue() override;
	
	// ValSource
	Stream&				GetStream() override;
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_SIDE_IN;}
	
};


#if 0
class DevCustomerComponent :
	public Component<DevCustomerComponent, RSink, OSource>,
{
public:
	using ComponentT = Component<DevCustomerComponent, RSink, OSource>;
	RTTI_DECL_1(DevCustomerComponent, ComponentT, ValDevSpec::GetName() + "DevCustomerComponent")
	COPY_PANIC(DevCustomerComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT
	COMP_MAKE_ACTION_BEGIN
		//TODO
	COMP_MAKE_ACTION_END
	
public:
	DevCustomerComponent() {}
	
	// ComponentBase
	void				Initialize() override;
	void				Uninitialize() override;
	ValCls				GetValSpec() const override {return AsTypeCls<O>();}
	bool				IsValSpec(ValCls t) const override {return AsTypeCls<O>() == t;}
	
	// ReceiptSink
	RFormat				GetFormat(R*) override;
	RValue&				GetValue(R*) override;
	
	// OrderSource
	OCtxStream&			GetStream(O*) override;
	void				BeginStream(O*) override;
	void				EndStream(O*) override;
	
};
#endif






struct AudioOutputExt : public OutputExt {};
struct AudioInputExt : public InputExt {};

NAMESPACE_ECS_END

#endif
