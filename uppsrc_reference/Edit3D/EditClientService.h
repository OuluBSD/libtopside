#ifndef _Edit3D_EditClientService_h_
#define _Edit3D_EditClientService_h_

NAMESPACE_TOPSIDE_BEGIN


class EditClientService : public DaemonService {
	EnetServiceClient* client = 0;
	bool is_calling = false;
	
public:
	// Remote connection
	RemoteExchange sync;
	
	
public:
	RTTI_DECL1(EditClientService, DaemonService);
	
	bool Init(String name) override;
	void Update() override;
	void Stop() override;
	void Deinit() override;
	
};


NAMESPACE_TOPSIDE_END

#endif
