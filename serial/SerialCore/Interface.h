#ifndef _SerialCore_Interface_h_
#define _SerialCore_Interface_h_

NAMESPACE_SERIAL_BEGIN


template <class T>
class InterfaceContainer : RTTIBase {
	
	
public:
	using Class = T;
	
	
	struct LocalValue : public SimpleValue {
		Class& par;
		
		RTTI_DECL1(LocalValue, SimpleValue)
		LocalValue(Class* par) : par(*par) {}
		void Visit(RuntimeVisitor& vis) {vis.VisitThis<SimpleValue>(this);}
	};
	
	struct LocalBufferedValue : public SimpleBufferedValue {
		Class& par;
		
		RTTI_DECL1(LocalBufferedValue, SimpleBufferedValue)
		LocalBufferedValue(Class* par) : par(*par) {}
		void Visit(RuntimeVisitor& vis) {vis.VisitThis<SimpleBufferedValue>(this);}
	};
	
	struct LocalBufferedStream : public SimpleBufferedStream {
		Class& par;
		
		RTTI_DECL1(LocalBufferedStream, SimpleBufferedStream)
		LocalBufferedStream(Class* par, SimpleBufferedValue& value) :
			par(*par),
			SimpleBufferedStream(value) {}
		
		void Visit(RuntimeVisitor& vis) {vis.VisitThis<SimpleBufferedStream>(this);}
		bool	IsOpen() const override {TODO}
		bool	Open(int fmt_idx) override {TODO}
		void	Close() override {TODO}
		bool	IsEof() override {TODO}
		bool	ReadFrame() override {TODO}
		bool	ProcessFrame() override {TODO}
		bool	ProcessOtherFrame() override {TODO}
		void	ClearPacketData() override {TODO}
	};
	
	struct LocalStream : public SimpleStream {
		Class& par;
		
		RTTI_DECL1(LocalStream, SimpleStream)
		LocalStream(Class* par, SimpleValue& value) :
			par(*par),
			SimpleStream(value) {}
		void Visit(RuntimeVisitor& vis) {vis.VisitThis<SimpleStream>(this);}
		
	};
	
	struct BufferedOutput : RTTIBase {
		LocalBufferedValue value;
		LocalBufferedStream stream;
		
		RTTI_DECL0(BufferedOutput)
		BufferedOutput(Class* par) : value(par), stream(par, value) {}
		~BufferedOutput() {value.ClearBuffer();}
		void Clear() {value.Clear(); stream.Clear();}
		void Visit(RuntimeVisitor& vis) {vis % value % stream;}
	};
	
	struct Output : RTTIBase {
		LocalValue value;
		LocalStream stream;
		
		RTTI_DECL0(Output)
		Output(Class* par) : value(par), stream(par, value) {}
		void Clear() {value.Clear(); stream.Clear();}
		void Visit(RuntimeVisitor& vis) {vis % value % stream;}
	};
	
	One<Output>				val;
	One<BufferedOutput>		val_buf;
	
	
	
public:
	RTTI_DECL0(InterfaceContainer<T>)
	void Visit(RuntimeVisitor& vis) {}
	
	void ClearContainer() {
		GetContainerStream().Clear();
	}
	
	Value& GetContainerValue() {
		return val.IsEmpty() ? (Value&)val_buf->value : (Value&)val->value;
	}
	
	Stream& GetContainerStream() {
		return val.IsEmpty() ? (Stream&)val_buf->stream : (Stream&)val->stream;
	}
	
	void InitializeContainer(Class* c, ValDevTuple vt) {
		ValDevCls vd = vt();
		ASSERT(vd.IsValid());
		Format val_fmt = GetDefaultFormat(vd);
		ASSERT(val_fmt.IsValid());
		
		if (vd.val == ValCls::AUDIO)
			val_buf.Create(c);
		else
			val.Create(c);
		
		GetContainerValue().SetFormat(val_fmt);
	}
	
	void UninitializeContainer() {
		if (val) val->Clear();
		if (val_buf) val_buf->Clear();
		val.Clear();
		val_buf.Clear();
	}
	
};


class InterfaceBase :
	RTTIBase
{
public:
	RTTI_DECL0(InterfaceBase)
	
	virtual AtomBase* AsAtomBase() = 0;
	virtual AtomTypeCls GetType() const = 0;
	ValDevTuple GetSinkCls() const {return GetType().iface.sink;}
	ValDevTuple GetSourceCls() const {return GetType().iface.src;}
	void Visit(RuntimeVisitor& vis) {}
	
};


class InterfaceSink :
	public InterfaceBase,
	public ExchangeSinkProvider
{
protected:
	
public:
	RTTI_DECL2(InterfaceSink, InterfaceBase, ExchangeSinkProvider)
	InterfaceSink() {}
	
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSinkProvider>(this);
	}
	
	virtual Value&				GetValue() = 0;
	virtual void				ClearSink() = 0;
	
};


#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s);
#endif


class InterfaceSource :
	public InterfaceBase,
	public ExchangeSourceProvider
{
	
	
public:
	RTTI_DECL2(InterfaceSource, InterfaceBase, ExchangeSourceProvider)
	InterfaceSource() {}
	
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSourceProvider>(this);
	}
	
	virtual void				ClearSource() = 0;
	virtual Stream&				GetStream() = 0;
	virtual Value&				GetSourceValue() = 0;
	
protected:
	
};

using InterfaceSinkRef			= Ref<InterfaceSink,		RefParent1<Loop>>;
using InterfaceSourceRef		= Ref<InterfaceSource,		RefParent1<Loop>>;




class DefaultInterfaceSink :
	public InterfaceSink,
	public InterfaceContainer<DefaultInterfaceSink>,
	RTTIBase
{
	
protected:
	using Class = DefaultInterfaceSink;
	friend class AtomSystem;
	
	
public:
	using Container = InterfaceContainer<DefaultInterfaceSink>;
	RTTI_DECL2(DefaultInterfaceSink, InterfaceSink, Container)
	
	DefaultInterfaceSink() {}
	
	bool Initialize();
	void Uninitialize() {UninitializeContainer();}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSink>(this);
		vis.VisitThis<Container>(this);
	}
	
	//TypeCls GetTypeCls() override {return TypeId(AsTypeCls<ValDevSpec>());}
	
	Value&						GetSinkValue()       {return GetContainerValue();}
	
	virtual void				ClearSink() override {ClearContainer();}
	virtual Value&				GetValue() override {return GetContainerValue();}
	
};


class DefaultInterfaceSource :
	public InterfaceSource,
	public InterfaceContainer<DefaultInterfaceSource>,
	RTTIBase
{
	/*ValDevCls src_vd;
	ValDevCls sink_vd;*/
	
protected:
	using Class = DefaultInterfaceSource;
	friend class AtomSystem;
	
	
public:
	using Container = InterfaceContainer<DefaultInterfaceSource>;
	RTTI_DECL2(DefaultInterfaceSource, InterfaceSource, Container)
	
	DefaultInterfaceSource() {}
	
	bool Initialize();
	void Uninitialize() {UninitializeContainer();}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSource>(this);
		vis.VisitThis<Container>(this);
	}
	
	//ValDevCls GetTypeCls() override;// {return TypeId(AsTypeCls<ValDevSpec>());}
	
	using ExPt = DefaultExchangePoint;
	using Sink = DefaultInterfaceSink;
	
	
	/*void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
	const RealtimeSourceConfig&	Cfg() const {return cfg;}
	void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}*/
	
	//DevCls						GetDevSpec() const override;// {return AsTypeCls<DevSpec>();}
	virtual void				ClearSource() override {ClearContainer();}
	virtual Stream&				GetStream() override {return GetContainerStream();}
	Value&						GetSourceValue() override {return GetContainerValue();}
	
};

using DefaultInterfaceSourceRef			= Ref<DefaultInterfaceSource,		RefParent1<Loop>>;
using DefaultInterfaceSinkRef			= Ref<DefaultInterfaceSink,			RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
