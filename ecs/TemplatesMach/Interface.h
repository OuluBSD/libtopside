#ifndef _TemplatesMach_Interface_h_
#define _TemplatesMach_Interface_h_

NAMESPACE_TOPSIDE_BEGIN


class InterfaceBase :
	RTTIBase
{
public:
	RTTI_DECL0(InterfaceBase)
	
	virtual ComponentBase* AsComponentBase() = 0;
	
};

template <class I>
class InterfaceSink :
	public ExchangeSinkProvider,
	public InterfaceBase
{
	using Sink = InterfaceSink<I>;
	
public:
	RTTI_DECL2(Sink, ExchangeSinkProvider, InterfaceBase)
	
	
};

#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s);
#endif

template <class I, class O>
class InterfaceSource :
	public ExchangeSourceProvider,
	public InterfaceBase
{
	using Source = InterfaceSource<I,O>;
	
public:
	RTTI_DECL2(Source, ExchangeSourceProvider, InterfaceBase)
	
	
protected:
	
};

template <class T>
class InterfaceVisitor : public RuntimeVisitor {
	using InterfaceVisitorT = InterfaceVisitor<T>;
	
	TypeId match_type;
	T* last = 0;
	bool stop_when_found = false;
	
	
	bool OnEntry(TypeId type, void* mem, LockedScopeRefCounter* ref) override {
		if (type == match_type) {
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
	void OnRef(TypeId type, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	RTTI_DECL1(InterfaceVisitorT, RuntimeVisitor)
	InterfaceVisitor() : match_type(AsTypeCls<T>()) {}
	
	
	T* GetLast() const {return last;}
	void StopWhenFound(bool b=true) {stop_when_found = b;}
	
	virtual bool OnInterfaceEntry(T& o) {return true;}
	
};


NAMESPACE_TOPSIDE_END

#endif
