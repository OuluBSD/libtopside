#ifndef _SerialCore_Exchange_h_
#define _SerialCore_Exchange_h_

NAMESPACE_SERIAL_BEGIN



class DefaultSink :
	public InterfaceSink,
	/*public SinkBase,*/
	/*public DevSink,*/
	RTTIBase
{
	
public:
	RTTI_DECL1(DefaultSink, InterfaceSink)
	
	DefaultSink() {}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSink>(this);
		//vis.VisitThis<SinkBase>(this);
		//vis.VisitThis<DevSink>(this);
	}
	
	//TypeCls GetTypeCls() override {return TypeId(AsTypeCls<ValDevSpec>());}
	
	virtual Value&				GetValue() = 0;
	virtual void				ClearSink() override {GetValue().Clear();}
	
};


class DefaultSource :
	public InterfaceSource,
	/*public DevSource,*/
	RTTIBase
{
	ValDevCls src;
	ValDevCls sink;
	
public:
	RTTI_DECL1(DefaultSource, InterfaceSource)
	
	DefaultSource() {}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSource>(this);
		//vis.VisitThis<DevSource>(this);
	}
	
	//ValDevCls GetTypeCls() override;// {return TypeId(AsTypeCls<ValDevSpec>());}
	
	using ExPt = DefaultExchangePoint;
	using Sink = DefaultSink;
	
	
	/*void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
	const RealtimeSourceConfig&	Cfg() const {return cfg;}
	void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}*/
	
	//DevCls						GetDevSpec() const override;// {return AsTypeCls<DevSpec>();}
	virtual Stream&				GetStream() = 0;
	virtual void				ClearSource() override {GetStream().Clear();}
private:
	
};

using DefaultSourceRef			= Ref<DefaultSource,		RefParent1<Loop>>;
using DefaultSinkRef			= Ref<DefaultSink,			RefParent1<Loop>>;

NAMESPACE_SERIAL_END

#endif
