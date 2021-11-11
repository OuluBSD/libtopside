#ifndef _AtomLocal_DeviceManager_Win32_h_
#define _AtomLocal_DeviceManager_Win32_h_
#if HAVE_WIN32_DEVMGR

NAMESPACE_SERIAL_BEGIN


class WIN32_Device {
	String path, desc;
	
public:
	WIN32_Device();
	
	int GetCaptureCount() const;
	OpenCVCaptureDevice& GetCapture(int i);
	
	String GetPath() const {return path;}
	String GetDescription() const {return desc;}
	
};

class WIN32_DeviceManager {
	
	
public:
	WIN32_DeviceManager();
	
	int GetNativeCount() const;
	WIN32_Device& GetNative(int i);
	void Refresh();
	
	
};


NAMESPACE_SERIAL_END

#endif
#endif
