#ifndef _IMedia_V4L2_DeviceManager_h_
#define _IMedia_V4L2_DeviceManager_h_

#if HAVE_V4L2_DEVMGR

NAMESPACE_PARALLEL_BEGIN

class V4L2_Device {
	
protected:
	friend class V4L2_DeviceManager;
	
	String path, desc;
	Array<OpenCVCaptureDevice> caps;
	
private:
	
public:
	V4L2_Device() {}
	~V4L2_Device() {}
	
	int GetCaptureCount() const {return caps.GetCount();}
	OpenCVCaptureDevice& GetCapture(int i) {return caps[i];}
	
	String GetPath() const {return path;}
	String GetDescription() const {return desc;}
	
};

class V4L2_DeviceManager {
	Array<V4L2_Device> devs;
	
	
public:
	using VideoSourceFormat = VideoSourceFormatT<V4L2Media>;
	using VideoSourceFormatResolution = VideoSourceFormatResolutionT<V4L2Media>;
	
	typedef V4L2_DeviceManager CLASSNAME;
	V4L2_DeviceManager();
	~V4L2_DeviceManager() {}
	
	int GetNativeCount() const {return devs.GetCount();}
	V4L2_Device& GetNative(int i) {return devs[i];}
	
	void Refresh();
	
};

NAMESPACE_PARALLEL_END

#endif
#endif
