#ifndef _EcsCore_ConnPoolComps_h_
#define _EcsCore_ConnPoolComps_h_


NAMESPACE_TOPSIDE_BEGIN


template <class T>
class ConnectAllInterfaces :
	public Connector<ConnectAllInterfaces<T>>,
	public MetaExchangePoint
{
	using ConnectorT = Connector<ConnectAllInterfaces<T>>;
	Ref<EntityStore> sys;
	
	int64 refresh_ticks = -1;
	
	
public:
	RTTI_DECL2(ConnectAllInterfaces, ConnectorT, MetaExchangePoint)
	COPY_PANIC(ConnectAllInterfaces);
	
	using Source	= T;
	using Sink		= typename T::SinkClass;
	using ISource	= InterfaceSource<Source, Sink>;
	using ISink		= InterfaceSink<Sink>;
	
	void Refresh() {if (sys) refresh_ticks = sys->PostRefresh(refresh_ticks, this);}
	TypeId GetType() const override {return AsTypeCls<ConnectAllInterfaces<T>>();}
	void CopyTo(ConnectorBase* component) const override {}
	void Initialize() override;
	void Uninitialize() override;
	String ToString() const override {return MetaExchangePoint::ToString();}
	void UnlinkAll() override;
	void Update(double dt) override;
	void Visit(RuntimeVisitor& vis) override {
		vis & sys;
		MetaExchangePoint::Visit(vis);
	}
		
	
	
private:
	
	void Visit(PoolRef pool, LinkedList<LinkedList<Ref<T>>>& src_stack);
	
};



NAMESPACE_TOPSIDE_END


#include "ConnPoolComps.inl"

#endif
