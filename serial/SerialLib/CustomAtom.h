#ifndef _SerialLib_CustomAtom_h_
#define _SerialLib_CustomAtom_h_

NAMESPACE_SERIAL_BEGIN

template <class T>
class AtomReceiptSink : public Atom<T> {
	using AtomT = Atom<T>;
	
protected:
	friend class Loop;
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
	CustomerData* GetCustomerData() override {return customer.IsEmpty() ? 0 : &*customer;}
	
	
public:
	COPY_PANIC(AtomReceiptSink)
	
	using BaseT = AtomReceiptSink<T>;
	RealtimeSourceConfig& GetConfig() override {ASSERT(customer); return customer->cfg;}
	
	bool Initialize(const Script::WorldState& ws) {
		AtomBase::packets_forwarded = 0;
		customer.Create();
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().Get<AtomSystem>()->Add(r);
		return true;
	}
	
	void Uninitialize() {
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().Get<AtomSystem>()->Remove(r);
	}
	
	void AddPlan(Script::Plan& sp) {
		ASSERT(!customer.IsEmpty());
		customer->plans.Add(sp);
	}
	
	void UpdateConfig(double dt) override {
		ASSERT(customer);
		{
			InterfaceSourceRef ss = AtomT::GetSource();
			InterfaceSource* o = ss.Get();
			TypeCls cls = AsTypeCls<DefaultInterfaceSource>();
			void* p = o->GetBasePtr(cls);
			DefaultInterfaceSource* pp = (DefaultInterfaceSource*)p;
		}
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
	Serial::Format		internal_fmt;
	double				time = 0;
	byte				rolling_value = 0;
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = CenterSourceAsync<T>;
	RTTI_DECL1(CenterSourceAsync, AtomT)
	
	bool Initialize(const Script::WorldState& ws)  {
		internal_fmt.SetAudio(SoundSample::U8_LE, 2, 44100, 777);
		time = 0;
		return true;
	}
	
	void Uninitialize()  {
		
	}
	
	void Forward(FwdScope& fwd) {
		RTLOG("CenterSourceAsync<T>::Forward");
		
	}

	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};

template <class T>
class CenterSinkSync : public Atom<T> {
	
protected:
	RunningFlag		flag;
	byte			rolling_value = 0;
	
	
	using AtomT = Atom<T>;
	
	void IntervalSinkProcess0() {IntervalSinkProcess();}
	
public:
	typedef CenterSinkSync CLASSNAME;
	using BaseT = CenterSinkSync<T>;
	RTTI_DECL1(CenterSinkSync, AtomT)
	
	~CenterSinkSync() {ASSERT(!flag.IsRunning());}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	virtual void IntervalSinkProcess() = 0;
	
	bool Initialize(const Script::WorldState& ws) override {
		flag.Start(1);
		Thread::Start(THISBACK(IntervalSinkProcess0));
		return true;
	}
	
	void Uninitialize() override {
		flag.Stop();
	}

	void Forward(FwdScope& fwd) override {
		RTLOG("CenterSinkSync<T>::Forward");
		AtomBase::ForwardVoidSink(fwd);
	}
	
	void StorePacket(Packet& p) override {
		RTLOG("CenterSinkSync<T>::StorePacket");
		//TODO
		//p->SetFormat(GetParent()->GetSourceValue().GetFormat());
	}
	
	
};

NAMESPACE_SERIAL_END

#endif
