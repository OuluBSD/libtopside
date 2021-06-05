#ifndef _TemplatesMach_Interface_h_
#define _TemplatesMach_Interface_h_

NAMESPACE_TOPSIDE_BEGIN


class InterfaceBase :
	RTTIBase,
	public WeakRefScopeEnabler<InterfaceBase, Entity>
{
public:
	RTTI_DECL0(InterfaceBase)
	
	virtual ComponentBase* AsComponentBase() = 0;
	virtual TypeCls GetSinkCls() const = 0;
	virtual TypeCls GetDevSpec() const {return AsTypeCls<CenterSpec>();}
	
};

class InterfaceSinkBase :
	public InterfaceBase,
	public ExchangeSinkProvider
{
public:
	RTTI_DECL2(InterfaceSinkBase, InterfaceBase, ExchangeSinkProvider)
};

class InterfaceSourceBase :
	public InterfaceBase,
	public ExchangeSourceProvider
{
public:
	RTTI_DECL2(InterfaceSourceBase, InterfaceBase, ExchangeSourceProvider)
};

using InterfaceSinkBaseRef = Ref<InterfaceSinkBase, RefParent1<Entity>>;
using InterfaceSourceBaseRef = Ref<InterfaceSourceBase, RefParent1<Entity>>;


template <class I>
class InterfaceSink :
	public InterfaceSinkBase
{
	using Sink = InterfaceSink<I>;
	
public:
	RTTI_DECL1(Sink, InterfaceSinkBase)
	
	TypeCls GetSinkCls() const override {return AsTypeCls<I>();}
	
};

#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s);
#endif

template <class I, class O>
class InterfaceSource :
	public InterfaceSourceBase
{
	using Source = InterfaceSource<I,O>;
	
public:
	RTTI_DECL1(Source, InterfaceSourceBase)
	
	TypeCls GetSinkCls() const override {return AsTypeCls<I>();}
	
protected:
	
};

template <class T>
class InterfaceVisitor : public RuntimeVisitor {
	using InterfaceVisitorT = InterfaceVisitor<T>;
	
	TypeCls match_type;
	T* last = 0;
	bool stop_when_found = false;
	
	
	bool OnEntry(const RTTI& type, void* mem, LockedScopeRefCounter* ref) override {
		TypeCls cls = type.GetTypeId();
		if (cls == match_type) {
			last = (T*)mem;
			if (stop_when_found) {
				BreakOut();
				return false;
			}
			else return OnInterfaceEntry(*(T*)mem);
		}
		return true;
	}
	void OnExit() override {}
	void OnRef(const RTTI& type, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	RTTI_DECL1(InterfaceVisitorT, RuntimeVisitor)
	InterfaceVisitor() : match_type(AsTypeCls<T>()) {}
	
	
	T* GetLast() const {return last;}
	void StopWhenFound(bool b=true) {stop_when_found = b;}
	
	virtual bool OnInterfaceEntry(T& o) {return true;}
	
};

class CollectInterfacesVisitor : public RuntimeVisitor {
	
	bool OnEntry(const RTTI& type, void* mem, LockedScopeRefCounter* ref) override {
		using Sink = InterfaceSinkBase;
		using Src = InterfaceSourceBase;
		
		Sink* sink = (Sink*)type.GetBasePtr(AsTypeCls<Sink>());
		if (sink)
			sink_ifaces.Add(sink->AsRef<Sink>());
		
		Src* src = (Src*)type.GetBasePtr(AsTypeCls<Src>());
		if (src)
			src_ifaces.Add(src->AsRef<Src>());
		
		return true;
	}
	void OnExit() override {}
	void OnRef(const RTTI& type, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	LinkedList<InterfaceSinkBaseRef> sink_ifaces;
	LinkedList<InterfaceSourceBaseRef> src_ifaces;
	
};


NAMESPACE_TOPSIDE_END

#endif
