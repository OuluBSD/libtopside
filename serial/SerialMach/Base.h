#ifndef _SerialMach_Base_h_
#define _SerialMach_Base_h_


NAMESPACE_SERIAL_BEGIN



class CustomerLink : public Link {
	off32_gen	off_gen;
	
	
public:
	RTTI_DECL1(CustomerLink, Link)
	typedef CustomerLink CLASSNAME;
	CustomerLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	RTSrcConfig*	GetConfig() override;
	void			Forward(FwdScope& fwd) override;
	bool			IsLoopComplete(FwdScope& fwd) override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	
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
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
};

class IntervalPipeLink : public AsyncMemForwarderBase {
	RunningFlag			flag;
	
	
public:
	RTTI_DECL1(IntervalPipeLink, AsyncMemForwarderBase)
	typedef IntervalPipeLink CLASSNAME;
	IntervalPipeLink();
	~IntervalPipeLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<AsyncMemForwarderBase>(this);}
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
	void IntervalSinkProcess();
	
};


class ExternalPipeLink : public AsyncMemForwarderBase {
	
public:
	RTTI_DECL1(ExternalPipeLink, AsyncMemForwarderBase)
	typedef ExternalPipeLink CLASSNAME;
	ExternalPipeLink();
	~ExternalPipeLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<AsyncMemForwarderBase>(this);}
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
};

class DriverLink : public Link {
	
public:
	RTTI_DECL1(DriverLink, Link)
	typedef DriverLink CLASSNAME;
	DriverLink();
	~DriverLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	bool			ProcessPackets(PacketIO& io) override;
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
};


NAMESPACE_SERIAL_END

#endif
