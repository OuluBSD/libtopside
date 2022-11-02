#include "LocalHMD.h"

NAMESPACE_HMD_BEGIN


LocalHMDService::LocalHMDService() {
	
}

bool LocalHMDService::Init(String name) {
	if (!sys.Initialise())
		return false;
	
	sys.Start();
	return true;
}

void LocalHMDService::Update() {
	
}

void LocalHMDService::Stop() {
	sys.Stop();
}

void LocalHMDService::Deinit() {
	sys.Uninitialise();
}

void LocalHMDService::SetSensorCallback(Callback1<CtrlEvent&> cb) {
	sys.WhenSensorEvent << cb;
}




NAMESPACE_HMD_END



