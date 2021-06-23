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

/*class InterfaceSinkBase :
	public InterfaceBase,
	public ExchangeSinkProvider
{
public:
	RTTI_DECL2(InterfaceSinkBase, InterfaceBase, ExchangeSinkProvider)
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSinkProvider>(this);
	}
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


*/

class InterfaceSink :
	public InterfaceBase,
	public ExchangeSinkProvider
{
protected:
	ValDevCls sink;
	
public:
	RTTI_DECL2(InterfaceSink, InterfaceBase, ExchangeSinkProvider)
	InterfaceSink() {}
	
	void SetSinkType(ValDevCls sink) {this->sink = sink;}
	
	ValDevCls	GetSinkCls() const override {return sink;}
	DevCls		GetDevSpec() const override {return sink.dev;}
	
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
	ValDevCls sink;
	ValDevCls src;
	
public:
	RTTI_DECL2(InterfaceSource, InterfaceBase, ExchangeSourceProvider)
	InterfaceSource() {}
	
	void SetSourceType(ValDevCls sink, ValDevCls src) {this->sink = sink; this->src = src;}
	
	ValDevCls	GetSourceCls() const {return src;}
	ValDevCls	GetSinkCls() const override {return sink;}
	DevCls		GetDevSpec() const override {return src.dev;}
	
	// Catches the type for CollectInterfacesVisitor
	void Visit(RuntimeVisitor& vis) {
		vis.VisitThis<InterfaceBase>(this);
		vis.VisitThis<ExchangeSourceProvider>(this);
	}
	
	virtual void ClearSource() = 0;
	
protected:
	
};



using InterfaceSinkRef = Ref<InterfaceSink, RefParent1<Entity>>;
using InterfaceSourceRef = Ref<InterfaceSource, RefParent1<Entity>>;


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
		using Sink = InterfaceSink;
		using Src = InterfaceSource;
		
		#if 1
		if (derived == AsTypeCls<InterfaceSink>())
			sink_ifaces.FindAdd(((InterfaceSink*)mem)->AsRef<InterfaceSink>());
		else if (derived == AsTypeCls<InterfaceSource>())
			src_ifaces.FindAdd(((InterfaceSource*)mem)->AsRef<InterfaceSource>());
		#else
		Sink* sink = (Sink*)type.GetBasePtrUnder(AsTypeCls<Sink>(), mem);
		if (sink) {
			InterfaceSinkRef r(sink->GetParentUnsafe(), sink);
			sink_ifaces.FindAdd(r);
		}
		Src* src = (Src*)type.GetBasePtrUnder(AsTypeCls<Src>(), mem);
		if (src) {
			InterfaceSourceRef r(src->GetParentUnsafe(), src);
			src_ifaces.FindAdd(r);
		}
		#endif
		
		return true;
	}
	void OnExit() override {}
	void OnRef(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	LinkedList<InterfaceSinkRef> sink_ifaces;
	LinkedList<InterfaceSourceRef> src_ifaces;
	
	
};


class ClearInterfacesVisitor : public RuntimeVisitor {
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {
		using Sink = InterfaceSink;
		using Src = InterfaceSource;
		
		if (derived == AsTypeCls<InterfaceSink>())
			((InterfaceSink*)mem)->ClearSink();
		else if (derived == AsTypeCls<InterfaceSource>())
			((InterfaceSource*)mem)->ClearSource();
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
	LinkedList<InterfaceSinkRef> sink_ifaces;
	LinkedList<InterfaceSourceRef> src_ifaces;
	
	
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
