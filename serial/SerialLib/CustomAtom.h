#ifndef _SerialLib_CustomAtom_h_
#define _SerialLib_CustomAtom_h_

NAMESPACE_SERIAL_BEGIN

template <class T>
class CustomerBaseT : public Atom<T> {
	using AtomT = Atom<T>;
	
protected:
	friend class Loop;
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
	CustomerData* GetCustomerData() override {return customer.IsEmpty() ? 0 : &*customer;}
	
	
public:
	COPY_PANIC(CustomerBaseT)
	
	using BaseT = CustomerBaseT<T>;
	RealtimeSourceConfig& GetConfig() override {ASSERT(customer); return customer->cfg;}
	
	bool Initialize(const Script::WorldState& ws) override {
		AtomBase::packets_forwarded = 0;
		customer.Create();
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->AddCustomer(r);
		return true;
	}
	
	void Uninitialize() override {
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->RemoveCustomer(r);
	}
	
	void AddPlan(Script::Plan& sp) override {
		ASSERT(!customer.IsEmpty());
		customer->plans.Add(sp);
	}
	
	void UpdateConfig(double dt) override {
		ASSERT(customer);
		/*{
			InterfaceSourceRef ss = AtomT::GetSource();
			InterfaceSource* o = ss.Get();
			TypeCls cls = AsTypeCls<DefaultInterfaceSource>();
			void* p = o->GetBasePtr(cls);
			DefaultInterfaceSource* pp = (DefaultInterfaceSource*)p;
		}*/
		DefaultInterfaceSourceRef src = AtomT::GetSource();
		ASSERT(src);
		if (src) {
			Stream& str = src->GetStream();
			Value& val = str.Get();
			customer->cfg.Update(dt, val.IsQueueFull());
		}
	}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	void Forward(FwdScope& fwd) override {}
	
	
	
};


template <class T>
class CenterSourceAsync : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = CenterSourceAsync<T>;
	RTTI_DECL1(CenterSourceAsync, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {return true;}
	void Uninitialize() override {}
	void Forward(FwdScope& fwd) override {}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};

template <class T>
class CenterSinkSync : public Atom<T> {
	
protected:
	using AtomT = Atom<T>;
	
	
public:
	typedef CenterSinkSync CLASSNAME;
	using BaseT = CenterSinkSync<T>;
	RTTI_DECL1(CenterSinkSync, AtomT)
	
	~CenterSinkSync() {}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
	bool Initialize(const Script::WorldState& ws) override {return true;}
	void Uninitialize() override {}

	
};

template <class T>
class CenterSinkAsync : public Atom<T> {
	
protected:
	using AtomT = Atom<T>;
	
	
public:
	typedef CenterSinkAsync CLASSNAME;
	using BaseT = CenterSinkAsync<T>;
	RTTI_DECL1(CenterSinkAsync, AtomT)
	
	~CenterSinkAsync() {}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
	bool Initialize(const Script::WorldState& ws) override {return true;}
	void Uninitialize() override {}

	
};

template <class T>
class CenterSinkPolling : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	typedef CenterSinkPolling CLASSNAME;
	using BaseT = CenterSinkPolling<T>;
	RTTI_DECL1(CenterSinkPolling, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->AddPolling(r);
		return true;
	}
	void Uninitialize() override {
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->RemovePolling(r);
	}
	void Forward(FwdScope& fwd) override {this->AltForward(fwd);}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};


template <class T>
class CenterSideSinkAsync :
	public Atom<
		T,
		DefaultInterfaceSink,
		DefaultInterfaceSource,
		DefaultInterfaceSideSink
	>
{
	
protected:
	
	using AtomT = Atom<T, DefaultInterfaceSink, DefaultInterfaceSource, DefaultInterfaceSideSink>;
	
public:
	using BaseT = CenterSideSinkAsync<T>;
	RTTI_DECL1(CenterSideSinkAsync, AtomT)
	
	void Uninitialize() override {}
	void Forward(FwdScope& fwd) override {
		RTLOG("CenterSideSinkAsync<T>::Forward");
	}

	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};


template <class T>
class CenterSideSourceAsync :
	public Atom<
		T,
		DefaultInterfaceSink,
		DefaultInterfaceSource,
		DefaultInterfaceSideSource
	>
{
	
protected:
	
	using AtomT = Atom<T, DefaultInterfaceSink, DefaultInterfaceSource, DefaultInterfaceSideSource>;
	
public:
	using BaseT = CenterSideSourceAsync<T>;
	RTTI_DECL1(CenterSideSourceAsync, AtomT)
	
	void Uninitialize() override {}
	void Forward(FwdScope& fwd) override {
		RTLOG("CenterSideSourceAsync<T>::Forward");
	}

	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};


template <class T>
class CenterDriver : public Atom<T> {
	
protected:
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
protected:
	
	using AtomT = Atom<T>;
	
	
public:
	using BaseT = CenterDriver<T>;
	RTTI_DECL1(CenterDriver, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {
		customer.Create();
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->AddDriver(r);
		return true;
	}
	
	void Uninitialize() override {
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->RemoveDriver(r);
	}
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
	void UpdateConfig(double dt) override {
		ASSERT(customer);
		customer->cfg.Update(dt, true);
	}
	
	RealtimeSourceConfig& GetConfig() override {ASSERT(customer); return customer->cfg;}
	
};



NAMESPACE_SERIAL_END

#endif
