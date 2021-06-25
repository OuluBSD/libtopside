#ifndef _TemplatesMach_Interface_h_
#define _TemplatesMach_Interface_h_

NAMESPACE_ECS_BEGIN


class InterfaceBase :
	RTTIBase
{
public:
	RTTI_DECL0(InterfaceBase)
	
	virtual ComponentBase* AsComponentBase() = 0;
	virtual TypeCompCls GetType() const = 0;
	virtual ValDevCls GetSinkCls() const {return ValDevCls();}
	virtual ValDevCls GetSourceCls() const {return ValDevCls();}
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



using InterfaceSinkRef = Ref<InterfaceSink, RefParent1<Entity>>;
using InterfaceSourceRef = Ref<InterfaceSource, RefParent1<Entity>>;


class InterfaceVisitor : public RuntimeVisitor {
	TypeCls iface_type;
	ValDevCls match_type;
	bool match_src;
	InterfaceSource* last_src = 0;
	InterfaceSink* last_sink = 0;
	bool stop_when_found = false;
	
	
	bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {
		if (derived == iface_type) {
			if (match_src) {
				last_src = (InterfaceSource*)mem;
				if (last_src->GetSourceCls() == match_type) {
					if (stop_when_found) {
						BreakOut();
						return false;
					}
					else return OnInterfaceEntry(*last_src);
				}
			}
			else {
				last_sink = (InterfaceSink*)mem;
				if (last_sink->GetSinkCls() == match_type) {
					if (stop_when_found) {
						BreakOut();
						return false;
					}
					else return OnInterfaceEntry(*last_sink);
				}
			}
		}
		return true;
	}
	void OnExit() override {}
	void OnRef(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	RTTI_DECL1(InterfaceVisitor, RuntimeVisitor)
	InterfaceVisitor(bool match_type_src, EcsTypeCls match) :
		match_type(match),
		match_src(match_type_src),
		iface_type(match_type_src ? AsTypeCls<InterfaceSource>() : AsTypeCls<InterfaceSink>()) {}
	
	
	InterfaceSource* GetLastSource() const {return last_src;}
	InterfaceSink* GetLastSink() const {return last_sink;}
	void StopWhenFound(bool b=true) {stop_when_found = b;}
	
	virtual bool OnInterfaceEntry(InterfaceSource& o) {return true;}
	virtual bool OnInterfaceEntry(InterfaceSink& o) {return true;}
	
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
