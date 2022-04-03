#ifndef _AtomLocal_Util_h_
#define _AtomLocal_Util_h_

NAMESPACE_SERIAL_BEGIN


class TestEventSrcBase :
	public AtomBase
{
	
public:
	RTTI_DECL0(TestEventSrcBase);
	
	TestEventSrcBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


class EventStateBase :
	public AtomBase
{
	String			target;
	EnvStateRef		state;
	
public:
	RTTI_DECL0(EventStateBase);
	
	EventStateBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {vis & state;}
	
	void			Event(const CtrlEvent& e);
	void			LeftDown(Point p, dword keyflags);
	void			LeftUp(Point p, dword keyflags);
	void			MouseMove(Point p, dword keyflags);
	bool			Key(dword key, int count);
	void			SetBool(dword key, bool b) {state->SetBool(key, b);}
	
	bool			GetBool(dword key) {return state->GetBool(key);}
	EnvState&		GetState() const;
	
};


NAMESPACE_SERIAL_END

#endif
