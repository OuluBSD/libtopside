#ifndef _EcsCore_ConnPoolComps_h_
#define _EcsCore_ConnPoolComps_h_


NAMESPACE_OULU_BEGIN


template <class T>
class ConnectAllInterfaces :
	public PoolComponent<ConnectAllInterfaces<T>>,
	public MetaExchangePoint
{
	Ref<EntityStore> sys;
	int64 refresh_ticks = -1;
	
public:
	COPY_PANIC(ConnectAllInterfaces);
	
	void Refresh() {if (sys) refresh_ticks = sys->PostRefresh(refresh_ticks, this);}
	TypeId GetType() const override {return typeid(ConnectAllInterfaces<T>);}
	void CopyTo(PoolComponentBase* component) const override {}
	void Initialize() override {
		Machine& m = PoolComponentBase::GetPool().GetMachine();
		sys = m.Get<EntityStore>();
		ASSERT_(sys, "EntityStore is required for MetaExchangePoints");
		Refresh();
	}
	void Uninitialize() override {
		
	}
	String ToString() const override {return MetaExchangePoint::ToString();}
	
	void Update(double dt) override;
	
	
private:
	
	void Visit(Ref<EntityPool> pool, Vector<Vector<Ref<T>>>& src_stack);
	
};



NAMESPACE_OULU_END


#include "ConnPoolComps.inl"

#endif
