#ifndef _SerialLib_DummyAtom_h_
#define _SerialLib_DummyAtom_h_

NAMESPACE_SERIAL_BEGIN


class DummyAlt :
	public virtual AtomBase
{
	off32_gen	gen;
	
	
public:
	RTTI_DECL0(DummyAlt)
	
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void AltStorePacket(Packet& p) override;
	bool AltIsReady(ValDevCls vd) override;
	
	
};



template <class T>
class AccelSideAsync : public Atom<T> {
	
protected:
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = AccelSideAsync<T>;
	RTTI_DECL1(AccelSideAsync, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!this->AltInitialize(ws)) return false;
		
		return true;
	}
	
	void Uninitialize() override {
		this->AltUninitialize();
		
	}
	
	void Forward(FwdScope& fwd) override {
		RTLOG("AccelSideAsync<T>::Forward");
	}

	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};


NAMESPACE_SERIAL_END

#endif
