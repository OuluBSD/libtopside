#ifndef _Local_Visitor_h_
#define _Local_Visitor_h_


NAMESPACE_TOPSIDE_BEGIN


class LockedScopeRefCounter :
	RTTIBase
{
	
private:
	std::atomic<int> refs;
	
	#ifdef flagDEBUG_STACK
protected:
	bool dbg_referencing = false;
	std::reference_wrapper<const std::type_info> dbg_type;
	void SetDebugReferencing(bool b=true) {dbg_referencing = b;}
	#endif
	
public:
	RTTI_DECL0(LockedScopeRefCounter)
	LockedScopeRefCounter();
	virtual ~LockedScopeRefCounter();
	
	int GetRefCount() const {return refs;}
	void IncRef();
	void DecRef();
	
	void ForcedReset() {refs = 0;}
	
};


template <class T, bool is_base>
struct LockedScopeRefCounterCaster {
	static LockedScopeRefCounter* Cast(T* o) {return CastPtr<LockedScopeRefCounter>(o);}
};

template <class T>
struct LockedScopeRefCounterCaster<T,false> {
	static LockedScopeRefCounter* Cast(T* o) {return 0;}
};
	

class RuntimeVisitor :
	RTTIBase
{
	
protected:
	bool break_out = false;
	bool get_refs = false;
	bool clear_refs = false;
	
	virtual bool OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) {return true;}
	virtual void OnExit() {}
	virtual void OnRef(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) {}
	
	template <class T> LockedScopeRefCounter* GetRefCounter(T* o) {
		return !get_refs ? 0 : LockedScopeRefCounterCaster<T,std::is_base_of<LockedScopeRefCounter,T>::value>().Cast(o);
	}
	
public:
	RTTI_DECL0(RuntimeVisitor)
	RuntimeVisitor() {}
	
	void Clear();
	void BreakOut(bool b=true) {break_out = b;}
	void SetActiveRefCounter(bool b=true) {get_refs = b;}
	void SetClearRefs(bool b=true) {clear_refs = b;}
	
	template <class T>
	void VisitThis(T* o) {
		ASSERT(o);
		if (break_out) return;
		if (OnEntry(o->GetRTTI(), GetTypeIdClass<T>(), GetTypeNameT<T>(), o, GetRefCounter(o))) {
			o->T::Visit(*this);
			OnExit();
		}
	}
	
	template <class T>
	void VisitThisPure(T* o) {
		ASSERT(o);
		if (break_out) return;
		if (OnEntry(o->GetRTTI(), GetTypeIdClass<T>(), GetTypeNameT<T>(), o, GetRefCounter(o))) {
			// Pass actual visit
			OnExit();
		}
	}
	
	template <class T>
	void Visit(T& o) {
		if (break_out) return;
		if (OnEntry(o.GetRTTI(), GetTypeIdClass<T>(), GetTypeNameT<T>(), &o, GetRefCounter(&o))) {
			o.Visit(*this);
			OnExit();
		}
	}
	
	template <class T> void VisitRef(T& o) {
		if (break_out)return;
		if (clear_refs)
			o.Clear();
		else if (o)
			OnRef(o->GetRTTI(), GetTypeIdClass<typename T::Type>(), GetTypeNameT<typename T::Type>(), &o, GetRefCounter(o.Get()));
	}
	
	template <class T>
	void VisitVector(T& o) {
		if (o.IsEmpty())
			return;
		for (auto iter = o.begin(), end = o.end(); iter != end && !break_out; ++iter)
			Visit(*iter);
	}
	
	template <class T>
	void VisitVectorRefs(T& o) {
		if (o.IsEmpty())
			return;
		for (auto iter = o.pbegin(), end = o.pend(); iter != end && !break_out; ++iter)
			Visit(iter());
	}
	
	template <class T>
	void VisitRefVector(T& o) {
		if (o.IsEmpty())
			return;
		for (auto iter = o.begin(), end = o.end(); iter != end && !break_out; ++iter)
			VisitRef(*iter);
	}
	
	template <class T> RuntimeVisitor& operator%(T& o) {Visit(o); return *this;}
	template <class T> RuntimeVisitor& operator&(T& o) {VisitRef(o); return *this;}
	template <class T> RuntimeVisitor& operator|(T& o) {VisitVector(o); return *this;}
	template <class T> RuntimeVisitor& operator||(T& o) {VisitVectorRefs(o); return *this;}
	template <class T> RuntimeVisitor& operator&&(T& o) {VisitRefVector(o); return *this;}
	
	
};

#define VIS_THIS(t) vis.VisitThis<t>(this);
#define EMPTY_VISIT void Visit(RuntimeVisitor& vis) override {}


NAMESPACE_TOPSIDE_END


#endif
