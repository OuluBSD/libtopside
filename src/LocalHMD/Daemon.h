#ifndef _LocalHMD_Daemon_h_
#define _LocalHMD_Daemon_h_

NAMESPACE_HMD_BEGIN


class LocalHMDService : public DaemonService {
	HMD::System sys;
	
	
public:
	typedef LocalHMDService CLASSNAME;
	LocalHMDService();
	bool Init(String name) override;
	void Update() override;
	void Stop() override;
	void Deinit() override;
	
	void SetSensorCallback(Callback1<CtrlEvent&> cb);
	
};


NAMESPACE_HMD_END

#endif
