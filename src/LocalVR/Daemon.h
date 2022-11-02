#ifndef __LocalVR_OUVRTD_H__
#define __LocalVR_OUVRTD_H__


struct udev;

NAMESPACE_HMD_BEGIN


extern GList *device_list;


struct LocalVRService : DaemonService {
	::udev* udev;
	guint owner_id;
	int longind;
	int ret;
	
	
	bool Init(String name) override;
	void Update() override;
	void Stop() override;
	void Deinit() override;
	
};


struct WmrFusionService : DaemonService {
	WmrFusionSystem sys;
	RunningFlag flag;
	SerialServiceServer* server = 0;
	LocalVRDebugService* lvrd_svc = 0;
	LocalHMDService* lhmd_svc = 0;
	
	typedef WmrFusionService CLASSNAME;
	WmrFusionService();
	bool Init(String name) override;
	void Update() override;
	void Stop() override;
	void Deinit() override;
	
	void FusionProcess();
	void OnBrightFrame(DebugService::Stream& s);
	void OnDarkFrame(DebugService::Stream& s);
	void OnSensorData(CtrlEvent& e);
};



NAMESPACE_HMD_END


#endif
