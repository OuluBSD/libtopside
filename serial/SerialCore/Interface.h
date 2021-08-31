#ifndef _SerialCore_Interface_h_
#define _SerialCore_Interface_h_

NAMESPACE_SERIAL_BEGIN

class InterfaceBase :
	RTTIBase
{
public:
	RTTI_DECL0(InterfaceBase)
	
	virtual AtomBase* AsAtomBase() = 0;
	virtual AtomTypeCls GetType() const = 0;
	ValDevCls GetSinkCls() const {return GetType().iface.sink;}
	ValDevCls GetSourceCls() const {return GetType().iface.src;}
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

class InterfaceSideSink :
	public InterfaceBase,
	public ExchangeSideSinkProvider
{
protected:
	
public:
	RTTI_DECL2(InterfaceSideSink, InterfaceBase, ExchangeSideSinkProvider)
	InterfaceSideSink() {}
	
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSideSinkProvider>(this);
	}
	
	virtual Value*				GetSideValue() = 0;
	virtual void				ClearSide() = 0;
	
};

class InterfaceSideSource :
	public InterfaceBase,
	public ExchangeSideSourceProvider
{
	
	
public:
	RTTI_DECL2(InterfaceSideSource, InterfaceBase, ExchangeSideSourceProvider)
	InterfaceSideSource() {}
	
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSideSourceProvider>(this);
	}
	
	virtual void				ClearSide() = 0;
	virtual Stream*				GetSideStream() = 0;
	virtual Value*				GetSideSourceValue() = 0;
	
protected:
	
};


using InterfaceSinkRef			= Ref<InterfaceSink,		RefParent1<Loop>>;
using InterfaceSourceRef		= Ref<InterfaceSource,		RefParent1<Loop>>;
using InterfaceSideSinkRef		= Ref<InterfaceSideSink,	RefParent1<Loop>>;
using InterfaceSideSourceRef	= Ref<InterfaceSideSource,	RefParent1<Loop>>;




class DefaultInterfaceSink :
	public InterfaceSink,
	/*public SinkBase,*/
	/*public DevSink,*/
	RTTIBase
{
	
protected:
	using Class = DefaultInterfaceSink;
	friend class AtomSystem;
	
	struct LocalValue : public SimpleValue {
		Class& par;
		
		LocalValue(Class* par) : par(*par) {}
	};
	
	struct LocalBufferedValue : public SimpleBufferedValue {
		Class& par;
		
		LocalBufferedValue(Class* par) : par(*par) {}
	};
	
	struct LocalBufferedStream : public SimpleBufferedStream {
		Class& par;
		
		RTTI_DECL1(LocalBufferedStream, SimpleBufferedStream)
		LocalBufferedStream(Class* par, SimpleBufferedValue& value) :
			par(*par),
			SimpleBufferedStream(value) {}
		
		bool	IsOpen() const override {TODO}
		bool	Open(int fmt_idx) override {TODO}
		void	Close() override {TODO}
		bool	IsEof() override {TODO}
		bool	ReadFrame() override {TODO}
		bool	ProcessFrame() override {TODO}
		bool	ProcessOtherFrame() override {TODO}
		void	ClearPacketData() override {TODO}
	};
	
	struct BufferedInput {
		LocalBufferedValue value;
		BufferedInput(Class* par) : value(par) {}
		~BufferedInput() {value.ClearBuffer();}
	};
	
	struct Input {
		LocalValue value;
		Input(Class* par) : value(par) {}
	};
	
	One<Input>				sink;
	One<BufferedInput>		sink_buf;
	
public:
	RTTI_DECL1(DefaultInterfaceSink, InterfaceSink)
	
	DefaultInterfaceSink() {}
	
	bool Initialize();
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSink>(this);
		//vis.VisitThis<SinkBase>(this);
		//vis.VisitThis<DevSink>(this);
	}
	
	//TypeCls GetTypeCls() override {return TypeId(AsTypeCls<ValDevSpec>());}
	
	Value&						GetSinkValue()       {return sink.IsEmpty() ? (Value&)sink_buf->value : (Value&)sink->value;}
	
	virtual void				ClearSink() override {GetValue().Clear();}
	virtual Value&				GetValue() override {return sink.IsEmpty() ? (Value&)sink_buf->value : (Value&)sink->value;}
	
};


class DefaultInterfaceSource :
	public InterfaceSource,
	/*public DevSource,*/
	RTTIBase
{
	/*ValDevCls src_vd;
	ValDevCls sink_vd;*/
	
protected:
	using Class = DefaultInterfaceSource;
	friend class AtomSystem;
	
	struct LocalValue : public SimpleValue {
		Class& par;
		
		LocalValue(Class* par) : par(*par) {}
	};
	
	struct LocalBufferedValue : public SimpleBufferedValue {
		Class& par;
		
		LocalBufferedValue(Class* par) : par(*par) {}
	};
	
	struct LocalBufferedStream : public SimpleBufferedStream {
		Class& par;
		
		RTTI_DECL1(LocalBufferedStream, SimpleBufferedStream)
		LocalBufferedStream(Class* par, SimpleBufferedValue& value) :
			par(*par),
			SimpleBufferedStream(value) {}
		
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
		
	};
	
	struct BufferedOutput {
		LocalBufferedValue value;
		LocalBufferedStream stream;
		BufferedOutput(Class* par) : value(par), stream(par, value) {}
		~BufferedOutput() {value.ClearBuffer();}
	};
	
	struct Output {
		LocalValue value;
		LocalStream stream;
		Output(Class* par) : value(par), stream(par, value) {}
	};
	
	One<Output>				src;
	One<BufferedOutput>		src_buf;
	
	
public:
	RTTI_DECL1(DefaultInterfaceSource, InterfaceSource)
	
	DefaultInterfaceSource() {}
	
	bool Initialize();
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSource>(this);
		//vis.VisitThis<DevSource>(this);
	}
	
	//ValDevCls GetTypeCls() override;// {return TypeId(AsTypeCls<ValDevSpec>());}
	
	using ExPt = DefaultExchangePoint;
	using Sink = DefaultInterfaceSink;
	
	
	/*void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
	const RealtimeSourceConfig&	Cfg() const {return cfg;}
	void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}*/
	
	//DevCls						GetDevSpec() const override;// {return AsTypeCls<DevSpec>();}
	virtual void				ClearSource() override {GetStream().Clear();}
	virtual Stream&				GetStream() override {return src.IsEmpty() ? (Stream&)src_buf->stream : (Stream&)src->stream;}
	Value&						GetSourceValue() override {return src.IsEmpty() ? (Value&)src_buf->value : (Value&)src->value;}
	
};


class VoidSideInterfaceSink :
	public InterfaceSideSink,
	RTTIBase
{
	
public:
	RTTI_DECL1(VoidSideInterfaceSink, InterfaceSideSink)
	
	VoidSideInterfaceSink() {}
	
	bool Initialize() {return true;}
	
	
	Value*				GetSideValue() override {return 0;}
	void				ClearSide() override {}
	
};


using DefaultInterfaceSourceRef			= Ref<DefaultInterfaceSource,		RefParent1<Loop>>;
using DefaultInterfaceSinkRef			= Ref<DefaultInterfaceSink,			RefParent1<Loop>>;
using VoidSideInterfaceSinkRef			= Ref<VoidSideInterfaceSink,			RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
