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


NAMESPACE_HMD_END


#endif
