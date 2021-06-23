#ifndef _TemplatesMach_Interface_h_
#define _TemplatesMach_Interface_h_

NAMESPACE_ECS_BEGIN


class InterfaceBase :
	RTTIBase
{
public:
	RTTI_DECL0(InterfaceBase)
	
	virtual ComponentBase* AsComponentBase() = 0;
	virtual EcsTypeCls GetEcsCls() const = 0;
	virtual ValDevCls GetSinkCls() const = 0;
	virtual DevCls GetDevSpec() const {return GetCenterDevCls();}
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
	virtual ValDevCls GetSourceCls() const = 0;
	virtual void ClearSource() = 0;
};

using InterfaceSinkBaseRef = Ref<InterfaceSinkBase, RefParent1<Entity>>;
using InterfaceSourceBaseRef = Ref<InterfaceSourceBase, RefParent1<Entity>>;



class InterfaceSink :
	public InterfaceSinkBase
{
protected:
	ValDevCls sink;
	
public:
	RTTI_DECL1(InterfaceSink, InterfaceSinkBase)
	InterfaceSink(ValDevCls sink_cls) : sink(sink_cls) {}
	
	ValDevCls GetSinkCls() const override {return sink;}
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {vis.VisitThis<InterfaceSinkBase>(this);}
	
};

#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s);
#endif


class InterfaceSource :
	public InterfaceSourceBase
{
	ValDevCls sink;
	ValDevCls src;
	
public:
	RTTI_DECL1(InterfaceSource, InterfaceSourceBase)
	InterfaceSource(ValDevCls sink_cls, ValDevCls src_cls) : sink(sink_cls), src(src_cls) {}
	
	ValDevCls GetSourceCls() const override {return src;}
	ValDevCls GetSinkCls() const override {return sink;}
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {vis.VisitThis<InterfaceSourceBase>(this);}
	
protected:
	
};

class InterfaceVisitor : public RuntimeVisitor {
	TypeCls iface_base;
	EcsTypeCls match_type;
	InterfaceBase* last = 0;
	bool stop_when_found = false;
	
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {
		if (derived == iface_base) {
			last = (InterfaceBase*)mem;
			if (last->GetEcsCls() == match_type) {
				if (stop_when_found) {
					BreakOut();
					return false;
				}
				else return OnInterfaceEntry(*(InterfaceBase*)mem);
			}
		}
		return true;
	}
	void OnExit() override {}
	void OnRef(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	RTTI_DECL1(InterfaceVisitor, RuntimeVisitor)
	InterfaceVisitor(EcsTypeCls match) : match_type(match), iface_base(AsTypeCls<InterfaceBase>()) {}
	
	
	InterfaceBase* GetLast() const {return last;}
	void StopWhenFound(bool b=true) {stop_when_found = b;}
	
	virtual bool OnInterfaceEntry(InterfaceBase& o) {return true;}
	
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

NAMESPACE_ECS_END

#endif
