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
	void Visit(RuntimeVisitor& vis) {}
	
};

class InterfaceSinkBase :
	public InterfaceBase,
	public ExchangeSinkProvider
{
public:
	RTTI_DECL2(InterfaceSinkBase, InterfaceBase, ExchangeSinkProvider)
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSinkProvider>(this);
	}
	virtual void ClearSink() = 0;
};

class InterfaceSourceBase :
	public InterfaceBase,
	public ExchangeSourceProvider
{
public:
	RTTI_DECL2(InterfaceSourceBase, InterfaceBase, ExchangeSourceProvider)
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSourceProvider>(this);
	}
	virtual TypeCls GetSourceCls() const = 0;
	virtual void ClearSource() = 0;
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
	
	TypeCls GetSinkCls() const override {
		//LOG("InterfaceSink: " << GetDynamicName() << " " << IntStr64(AsTypeCls<I>()));
		return AsTypeCls<I>();
	}
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {vis.VisitThis<InterfaceSinkBase>(this);}
	
};

#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s);
#endif

template <class O, class I>
class InterfaceSource :
	public InterfaceSourceBase
{
	using Source = InterfaceSource<O,I>;
	
public:
	RTTI_DECL1(Source, InterfaceSourceBase)
	
	TypeCls GetSourceCls() const override {return AsTypeCls<O>();}
	TypeCls GetSinkCls() const override {
		//LOG("InterfaceSource: " << GetDynamicName() << " " << IntStr64(AsTypeCls<I>()));
		return AsTypeCls<I>();
	}
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {vis.VisitThis<InterfaceSourceBase>(this);}
	
protected:
	
};

template <class T>
class InterfaceVisitor : public RuntimeVisitor {
	using InterfaceVisitorT = InterfaceVisitor<T>;
	
	TypeCls match_type;
	T* last = 0;
	bool stop_when_found = false;
	
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {
		if (derived == match_type) {
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
	void OnRef(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	RTTI_DECL1(InterfaceVisitorT, RuntimeVisitor)
	InterfaceVisitor() : match_type(AsTypeCls<T>()) {}
	
	
	T* GetLast() const {return last;}
	void StopWhenFound(bool b=true) {stop_when_found = b;}
	
	virtual bool OnInterfaceEntry(T& o) {return true;}
	
};

class CollectInterfacesVisitor : public RuntimeVisitor {
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {
		using Sink = InterfaceSinkBase;
		using Src = InterfaceSourceBase;
		
		#if 1
		if (derived == AsTypeCls<InterfaceSinkBase>())
			sink_ifaces.FindAdd(((InterfaceSinkBase*)mem)->AsRef<InterfaceSinkBase>());
		else if (derived == AsTypeCls<InterfaceSourceBase>())
			src_ifaces.FindAdd(((InterfaceSourceBase*)mem)->AsRef<InterfaceSourceBase>());
		#else
		Sink* sink = (Sink*)type.GetBasePtrUnder(AsTypeCls<Sink>(), mem);
		if (sink) {
			InterfaceSinkBaseRef r(sink->GetParentUnsafe(), sink);
			sink_ifaces.FindAdd(r);
		}
		Src* src = (Src*)type.GetBasePtrUnder(AsTypeCls<Src>(), mem);
		if (src) {
			InterfaceSourceBaseRef r(src->GetParentUnsafe(), src);
			src_ifaces.FindAdd(r);
		}
		#endif
		
		return true;
	}
	void OnExit() override {}
	void OnRef(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	LinkedList<InterfaceSinkBaseRef> sink_ifaces;
	LinkedList<InterfaceSourceBaseRef> src_ifaces;
	
	
};


class ClearInterfacesVisitor : public RuntimeVisitor {
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {
		using Sink = InterfaceSinkBase;
		using Src = InterfaceSourceBase;
		
		if (derived == AsTypeCls<InterfaceSinkBase>())
			((InterfaceSinkBase*)mem)->ClearSink();
		else if (derived == AsTypeCls<InterfaceSourceBase>())
			((InterfaceSourceBase*)mem)->ClearSource();
		return true;
	}
};


/*class ComponentInterfacesVisitor : public RuntimeVisitor {
	
	bool OnEntry(const RTTI& type, void* mem, LockedScopeRefCounter* ref) override {
		using Sink = InterfaceSinkBase;
		using Src = InterfaceSourceBase;
		
		Sink* sink = (Sink*)type.GetBasePtrUnder(AsTypeCls<Sink>(), mem);
		if (sink) {
			sink_ifaces.FindAdd(sink->AsRefUnsafe<Sink>());
		}
		Src* src = (Src*)type.GetBasePtrUnder(AsTypeCls<Src>(), mem);
		if (src) {
			src_ifaces.FindAdd(src->AsRefUnsafe<Src>());
		}
		
		return true;
	}
	void OnExit() override {}
	void OnRef(const RTTI& type, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	LinkedList<InterfaceSinkBaseRef> sink_ifaces;
	LinkedList<InterfaceSourceBaseRef> src_ifaces;
	
	
	template <class T>
	void Visit(T& o) {
		if (break_out) return;
		if (OnEntry(o.GetRTTI(), &o, GetRefCounter(&o))) {
			o.VisitSources(*this);
			o.VisitSinks(*this);
			OnExit();
		}
	}
	
};*/

NAMESPACE_TOPSIDE_END

#endif
