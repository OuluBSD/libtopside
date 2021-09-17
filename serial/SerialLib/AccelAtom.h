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
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!this->AltInitialize(ws)) return false;
		
		return true;
	}
	
	void Uninitialize() override {
		this->AltUninitialize();
		
	}
	
	void Forward(FwdScope& fwd) override {
		RTLOG("AccelSinkPolling<T>::Forward");
	}
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};

template <class T>
class AccelSourceAsync : public Atom<T> {
	
protected:
	Serial::Format		internal_fmt;
	double				time = 0;
	byte				rolling_value = 0;
	
	using AtomT = Atom<T>;
	
public:
	using BaseT = AccelSourceAsync<T>;
	RTTI_DECL1(AccelSourceAsync, AtomT)
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!this->AltInitialize(ws)) return false;
		
		AtomTypeCls type = ((AtomBase*)this)->GetType();
		if (type.iface.src.val == ValCls::AUDIO)
			internal_fmt.SetAudio(DevCls::ACCEL, SoundSample::U8_LE, 2, 44100, 777);
		else if (type.iface.src.val == ValCls::VIDEO)
			internal_fmt.SetVideo(DevCls::ACCEL, LightSampleFD::U8_LE_ABC, 1280, 720, 60, 1);
		else
			TODO;
		
		time = 0;
		return true;
	}
	
	void Uninitialize() override {
		this->AltUninitialize();
		
	}
	
	void Forward(FwdScope& fwd) override {
		RTLOG("AccelSourceAsync<T>::Forward");
	}

	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	
};


NAMESPACE_SERIAL_END

#endif
