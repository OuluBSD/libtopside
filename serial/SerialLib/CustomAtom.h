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
	RealtimeSourceConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!this->AltInitialize(ws)) return false;
		AtomBase::packets_forwarded = 0;
		customer.Create();
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->AddCustomer(r);
		return true;
	}
	
	void Uninitialize() override {
		this->AltUninitialize();
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
			int count = src->GetSourceCount();
			for(int i = 0; i < count; i++) {
				Value& val = src->GetSourceValue(i);
				customer->cfg.Update(dt, val.IsQueueFull());
			}
		}
	}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	//void Forward(FwdScope& fwd) override {}
	
	
	
};


template <class T>
class CenterSource : public Atom<T> {
	
protected:
	using AtomT = Atom<T>;
	
	
public:
	typedef CenterSource CLASSNAME;
	using BaseT = CenterSource<T>;
	RTTI_DECL1(CenterSource, AtomT)
	
	~CenterSource() {}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
	bool Initialize(const Script::WorldState& ws) override {return true;}
	void Uninitialize() override {}

	
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
	//void Forward(FwdScope& fwd) override {}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};

template <class T>
class CenterSink : public Atom<T> {
	
protected:
	using AtomT = Atom<T>;
	
	
public:
	typedef CenterSink CLASSNAME;
	using BaseT = CenterSink<T>;
	RTTI_DECL1(CenterSink, AtomT)
	
	~CenterSink() {}
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
	using BaseT = CenterSinkAsync<T>;
	RTTI_DECL1(CenterSinkAsync, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {return true;}
	void Uninitialize() override {}
	//void Forward(FwdScope& fwd) override {}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};



#if 0
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
class CenterSourcePolling : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	typedef CenterSourcePolling CLASSNAME;
	using BaseT = CenterSourcePolling<T>;
	RTTI_DECL1(CenterSourcePolling, AtomT)
	
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

#endif

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
	
	RealtimeSourceConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	
};



NAMESPACE_SERIAL_END

#endif
