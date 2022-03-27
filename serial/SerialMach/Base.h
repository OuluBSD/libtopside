#ifndef _SerialMach_Base_h_
#define _SerialMach_Base_h_


NAMESPACE_SERIAL_BEGIN



class CustomerLink : public Link {
	
	
public:
	RTTI_DECL1(CustomerLink, Link)
	typedef CustomerLink CLASSNAME;
	CustomerLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	RTSrcConfig*	GetConfig() override;
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
};

class PipeLink : public Link {
	
	
public:
	RTTI_DECL1(PipeLink, Link)
	typedef PipeLink CLASSNAME;
	PipeLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
};

class IntervalPipeLink : public AsyncMemForwarderBase {
	RunningFlag			flag;
	
	
public:
	RTTI_DECL1(IntervalPipeLink, Link)
	typedef IntervalPipeLink CLASSNAME;
	IntervalPipeLink();
	~IntervalPipeLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
	void IntervalSinkProcess();
	
};


NAMESPACE_SERIAL_END

#endif
