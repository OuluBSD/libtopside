#ifndef _SerialLib_DummyAtom_h_
#define _SerialLib_DummyAtom_h_

NAMESPACE_SERIAL_BEGIN


template <class T>
class DummySideAsync : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = DummySideAsync<T>;
	RTTI_DECL1(DummySideAsync, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!this->AltInitialize(ws)) return false;
		
		return true;
	}
	
	void Uninitialize() override {
		this->AltUninitialize();
		
	}
	
	void Forward(FwdScope& fwd) override {
		RTLOG("DummySideAsync<T>::Forward");
	}

	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};


NAMESPACE_SERIAL_END

#endif
