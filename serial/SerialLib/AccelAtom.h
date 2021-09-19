#ifndef _SerialLib_AccelAtom_h_
#define _SerialLib_AccelAtom_h_

NAMESPACE_SERIAL_BEGIN


template <class T>
class AccelSinkPolling : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = AccelSinkPolling<T>;
	RTTI_DECL1(AccelSinkPolling, AtomT)
	
	void Uninitialize() override {}
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


NAMESPACE_SERIAL_END

#endif
