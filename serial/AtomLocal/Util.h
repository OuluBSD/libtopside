#ifndef _AtomLocal_Util_h_
#define _AtomLocal_Util_h_

NAMESPACE_SERIAL_BEGIN


class JoinerBase :
	virtual public AtomBase
{
	
	
public:
	JoinerBase();
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


class SplitterBase :
	virtual public AtomBase
{
	
	
public:
	SplitterBase();
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


NAMESPACE_SERIAL_END

#endif
