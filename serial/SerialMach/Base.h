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

class PipeOptSideLink : public Link {
	bool finalize_on_side = false;
	
	
public:
	RTTI_DECL1(PipeOptSideLink, Link)
	typedef PipeOptSideLink CLASSNAME;
	PipeOptSideLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	void			SetFinalizeOnSide(bool b=true) {finalize_on_side = b;}
	
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

class PollerLink : public FramePollerBase {
	bool finalize_on_side = false;
	
public:
	RTTI_DECL1(PollerLink, FramePollerBase)
	typedef PollerLink CLASSNAME;
	PollerLink();
	~PollerLink();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<FramePollerBase>(this);}
	bool			ProcessPackets(PacketIO& io) final;
	void			SetFinalizeOnSide(bool b=true) {finalize_on_side = b;}
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
	
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

class JoinerLink : public Link
{
	byte scheduler_iter = 1;
	
public:
	RTTI_DECL1(JoinerLink, Link)
	JoinerLink();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
};

class SplitterLink : public Link
{
	
public:
	RTTI_DECL1(SplitterLink, Link)
	SplitterLink();
	bool Initialize(const Script::WorldState& ws) final;
	void Uninitialize() final;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	bool IsReady(PacketIO& io) final;
	bool ProcessPackets(PacketIO& io) override;
	
	static LinkTypeCls GetType();
	LinkTypeCls GetLinkType() const override {return GetType();}
	
};


NAMESPACE_SERIAL_END

#endif
