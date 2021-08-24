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
	virtual ValDevCls GetSinkCls() const {return ValDevCls();}
	virtual ValDevCls GetSourceCls() const {return ValDevCls();}
	void Visit(RuntimeVisitor& vis) {}
	
};


class InterfaceSink :
	public InterfaceBase,
	public ExchangeSinkProvider
{
protected:
	ValDevCls iface;
	
public:
	RTTI_DECL2(InterfaceSink, InterfaceBase, ExchangeSinkProvider)
	InterfaceSink() {}
	
	void SetSinkType(ValDevCls iface) {this->iface = iface;}
	
	ValDevCls	GetSinkCls() const override {return iface;}
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSinkProvider>(this);
	}
	
	virtual void ClearSink() = 0;
	
};

#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s);
#endif


class InterfaceSource :
	public InterfaceBase,
	public ExchangeSourceProvider
{
	
protected:
	ValDevCls iface;
	
public:
	RTTI_DECL2(InterfaceSource, InterfaceBase, ExchangeSourceProvider)
	InterfaceSource() {}
	
	void SetSourceType(ValDevCls iface) {this->iface = iface;}
	
	ValDevCls	GetSourceCls() const override {return iface;}
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSourceProvider>(this);
	}
	
	virtual void ClearSource() = 0;
	
protected:
	
};


using InterfaceSinkRef		= Ref<InterfaceSink,	RefParent1<Loop>>;
using InterfaceSourceRef	= Ref<InterfaceSource,	RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
