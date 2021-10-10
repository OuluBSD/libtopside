#ifndef _SerialCore_Interface_h_
#define _SerialCore_Interface_h_

NAMESPACE_SERIAL_BEGIN


template <class T>
class InterfaceContainer : RTTIBase {
	
	
public:
	using Class = T;
	
	struct Item {
		
		void ClearContainer() {
			if (val) val->Clear();
			val.Clear();
		}
		
		Value& GetContainerValue() {
			ASSERT(val);
			return *val;
		}
		
		void InitializeContainer(ValDevTuple vt) {
			ClearContainer();
			
			ValDevCls vd = vt();
			ASSERT(vd.IsValid());
			Format val_fmt = GetDefaultFormat(vd);
			ASSERT(val_fmt.IsValid());
			
			val.Create();
			val->SetFormat(val_fmt);
		}
		
		void UninitializeContainer() {
			ClearContainer();
		}
		
		One<SimpleValue>	val;
	};
	
	
	Array<Item>	items;
	
	
public:
	RTTI_DECL0(InterfaceContainer<T>)
	void Visit(RuntimeVisitor& vis) {}
	
	
	int GetContainerCount() const {return items.GetCount();}
	
	void ClearContainer(int i) {
		GetContainerStream(i).Clear();
	}
	
	Value& GetContainerValue(int i) {
		return items[i].GetContainerValue();
	}
	
	Stream& GetContainerStream(int i) {
		return items[i].GetContainerStream();
	}
	
	void SetContainerCount(int c) {items.SetCount(c);}
	
	void InitializeContainer(int i, ValDevTuple vt) {
		items[i].InitializeContainer(vt);
	}
	
	void UninitializeContainer(int i) {
		items[i].UninitializeContainer();
	}
	
	void ClearContainers() {
		for (Item& it : items)
			it.ClearContainer();
	}
	
	void UninitializeContainers() {
		for (Item& it : items)
			it.UninitializeContainer();
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
	
	virtual Value&				GetValue(int i) = 0;
	virtual void				ClearSink() = 0;
	virtual int					GetSinkCount() const = 0;
	
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
	virtual Value&				GetSourceValue(int i) = 0;
	virtual int					GetSourceCount() const = 0;
	
protected:
	
};

using InterfaceSinkRef			= Ref<InterfaceSink,		AtomParent>;
using InterfaceSourceRef		= Ref<InterfaceSource,		AtomParent>;
using ISinkRef					= Ref<InterfaceSink,		AtomParent>;
using ISourceRef				= Ref<InterfaceSource,		AtomParent>;




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
	void Uninitialize() {UninitializeContainers();}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSink>(this);
		vis.VisitThis<Container>(this);
	}
	
	//TypeCls GetTypeCls() override {return TypeId(AsTypeCls<ValDevSpec>());}
	
	Value&						GetSinkValue(int i)       {return GetContainerValue(i);}
	
	virtual void				ClearSink() override {ClearContainers();}
	virtual Value&				GetValue(int i) override {return GetContainerValue(i);}
	virtual int					GetSinkCount() const override {return GetContainerCount();}
	
};


class DefaultInterfaceSource :
	public InterfaceSource,
	public InterfaceContainer<DefaultInterfaceSource>,
	RTTIBase
{
	
protected:
	using Class = DefaultInterfaceSource;
	friend class AtomSystem;
	
	
public:
	using Container = InterfaceContainer<DefaultInterfaceSource>;
	RTTI_DECL2(DefaultInterfaceSource, InterfaceSource, Container)
	
	DefaultInterfaceSource() {}
	
	bool Initialize();
	void Uninitialize() {UninitializeContainers();}
	
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceSource>(this);
		vis.VisitThis<Container>(this);
	}
	
	using ExPt = DefaultExchangePoint;
	using Sink = DefaultInterfaceSink;
	
	virtual void				ClearSource() override {ClearContainers();}
	virtual int					GetSourceCount() const override {return GetContainerCount();}
	Value&						GetSourceValue(int i) override {return GetContainerValue(i);}
	
};

using DefaultInterfaceSourceRef			= Ref<DefaultInterfaceSource,		AtomParent>;
using DefaultInterfaceSinkRef			= Ref<DefaultInterfaceSink,			AtomParent>;


NAMESPACE_SERIAL_END

#endif
