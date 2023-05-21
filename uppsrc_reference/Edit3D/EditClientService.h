#ifndef _Edit3D_EditClientService_h_
#define _Edit3D_EditClientService_h_

NAMESPACE_TOPSIDE_BEGIN


class EditClientService : public DaemonService {
	EnetServiceClient* client = 0;
	bool is_calling = false;
	
public:
	Edit3D* edit = 0;
	
	// Remote connection
	RemoteExchange sync;
	bool debug = false;
	bool ready = false;
	
	
public:
	RTTI_DECL1(EditClientService, DaemonService);
	
	bool Init(String name) override;
	void Update() override;
	void Stop() override;
	void Deinit() override;
	
	void SetReady(bool b=true) {ready = b;}
	void SetDebuggingMode() {debug = true;}
	
};


NAMESPACE_TOPSIDE_END

#endif
