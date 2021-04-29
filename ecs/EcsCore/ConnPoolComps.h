#ifndef _EcsCore_ConnPoolComps_h_
#define _EcsCore_ConnPoolComps_h_


NAMESPACE_OULU_BEGIN


template <class T>
class ConnectAllInterfaces :
	public Connector<ConnectAllInterfaces<T>>,
	public MetaExchangePoint
{
	Ref<EntityStore> sys;
	int64 refresh_ticks = -1;
	
	
public:
	COPY_PANIC(ConnectAllInterfaces);
	
	using Source	= T;
	using Sink		= typename T::Sink;
	using ISource	= InterfaceSource<Source, Sink>;
	using ISink		= InterfaceSink<Sink>;
	
	void Refresh() {if (sys) refresh_ticks = sys->PostRefresh(refresh_ticks, this);}
	TypeId GetType() const override {return typeid(ConnectAllInterfaces<T>);}
	void CopyTo(ConnectorBase* component) const override {}
	void Initialize() override;
	void Uninitialize() override;
	String ToString() const override {return MetaExchangePoint::ToString();}
	void UnlinkAll() override;
	
	void Update(double dt) override;
	
	
private:
	
	void Visit(Ref<Pool> pool, Vector<Vector<Ref<T>>>& src_stack);
	
};



NAMESPACE_OULU_END


#include "ConnPoolComps.inl"

#endif
