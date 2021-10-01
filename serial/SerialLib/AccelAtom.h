#ifndef _SerialLib_AccelAtom_h_
#define _SerialLib_AccelAtom_h_

NAMESPACE_SERIAL_BEGIN


#if 0

template <class T>
class AccelSinkPolling : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = AccelSinkPolling<T>;
	RTTI_DECL1(AccelSinkPolling, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {
		AtomBase::GetMachine().template Get<AtomSystem>()->AddPolling(AtomBase::AsRefT());
		return true;
	}
	void Uninitialize() override {
		AtomBase::GetMachine().template Get<AtomSystem>()->RemovePolling(AtomBase::AsRefT());
	}
	void Forward(FwdScope& fwd) override {this->AltForward(fwd);}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};

template <class T>
class AccelSourcePolling : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = AccelSourcePolling<T>;
	RTTI_DECL1(AccelSourcePolling, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {
		AtomBase::GetMachine().template Get<AtomSystem>()->AddPolling(AtomBase::AsRefT());
		return true;
	}
	void Uninitialize() override {
		AtomBase::GetMachine().template Get<AtomSystem>()->RemovePolling(AtomBase::AsRefT());
	}
	void Forward(FwdScope& fwd) override {this->AltForward(fwd);}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};


template <class T>
class AccelSourceAsync : public Atom<T> {
	
protected:
	Serial::Format		internal_fmt;
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = AccelSourceAsync<T>;
	RTTI_DECL1(AccelSourceAsync, AtomT)
	
	
	void Uninitialize() override {}
	void Forward(FwdScope& fwd) override {
		RTLOG("AccelSourceAsync<T>::Forward");
	}

	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};

#endif


template <class T> using AccelSink			= CenterSink<T>;
template <class T> using AccelSinkAsync		= CenterSinkAsync<T>;
template <class T> using AccelSource		= CenterSource<T>;
template <class T> using AccelSourceAsync	= CenterSourceAsync<T>;


NAMESPACE_SERIAL_END

#endif
