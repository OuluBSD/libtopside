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
	
	virtual void ClearSink() = 0;
	
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
	
	virtual void ClearSource() = 0;
	
protected:
	
};


using InterfaceSinkRef		= Ref<InterfaceSink,	RefParent1<Loop>>;
using InterfaceSourceRef	= Ref<InterfaceSource,	RefParent1<Loop>>;




class DefaultInterfaceSink : public InterfaceSink {
	
public:
	RTTI_DECL1(DefaultInterfaceSink, InterfaceSink)
	DefaultInterfaceSink() {}
	
	void Visit(RuntimeVisitor& vis) {vis.VisitThis<InterfaceSink>(this);}
	
};

class DefaultInterfaceSource : public InterfaceSource {
	
public:
	RTTI_DECL1(DefaultInterfaceSource, InterfaceSource)
	DefaultInterfaceSource() {}
	
	void Visit(RuntimeVisitor& vis) {vis.VisitThis<InterfaceSource>(this);}
	
};

NAMESPACE_SERIAL_END

#endif
