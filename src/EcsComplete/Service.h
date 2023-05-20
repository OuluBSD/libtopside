#ifndef _EcsComplete_Service_h_
#define _EcsComplete_Service_h_

NAMESPACE_TOPSIDE_BEGIN


class EcsService : public DaemonService {
	EnetServiceServer* server = 0;
	Ecs::EntityRef bound_entity;
	
	Ecs::EntityRef ResolveEntity(Ecs::PoolRef& root, String path);
	
public:
	// Remote connection
	GeomSerializer write, read;
	
	void ReceiveGeoms(Ether& in, Ether& out);
	
public:
	typedef EcsService CLASSNAME;
	RTTI_DECL1(EcsService, DaemonService);
	
	EcsService();
	bool Init(String name) override;
	void Update() override;
	void Stop() override;
	void Deinit() override;
	
};


NAMESPACE_TOPSIDE_END

#endif
