#include "IMedia.h"
#if HAVE_WIN32_DEVMGR

NAMESPACE_PARALLEL_BEGIN


WIN32_Device::WIN32_Device() {
	
}

int WIN32_Device::GetCaptureCount() const {
	TODO
}

OpenCVCaptureDevice& WIN32_Device::GetCapture(int i) {
	TODO
}




WIN32_DeviceManager::WIN32_DeviceManager() {
	
}

int WIN32_DeviceManager::GetNativeCount() const {
	TODO
}

WIN32_Device& WIN32_DeviceManager::GetNative(int i) {
	TODO
}

void WIN32_DeviceManager::Refresh() {
	TODO
}


NAMESPACE_PARALLEL_END
#endif
