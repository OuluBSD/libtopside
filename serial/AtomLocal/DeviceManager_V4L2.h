#ifndef _AtomLocal_V4L2_DeviceManager_h_
#define _AtomLocal_V4L2_DeviceManager_h_

#if HAVE_V4L2_DEVMGR

NAMESPACE_SERIAL_BEGIN

class V4L2_Device {
	
protected:
	friend class V4L2_DeviceManager;
	
	String path, desc;
	Array<OpenCVCaptureDevice> caps;
	
	//Array<FfmpegFileInput> inputs;
	
public:
	//FfmpegFileInput& AddFileInput() {return inputs.Add();}
	
private:
	
public:
	V4L2_Device() {}
	~V4L2_Device() {}
	
	int GetCaptureCount() const {return caps.GetCount();}
	OpenCVCaptureDevice& GetCapture(int i) {return caps[i];}
	//MediaStream* FindOpenDevice();
	
	String GetPath() const {return path;}
	String GetDescription() const {return desc;}
	
};

class V4L2_DeviceManager {
	Array<V4L2_Device> devs;
	//Array<V4L2_Device> virtuals;
	
	
public:
	typedef V4L2_DeviceManager CLASSNAME;
	V4L2_DeviceManager();
	~V4L2_DeviceManager() {}
	
	int GetNativeCount() const {return devs.GetCount();}
	//int GetVirtualCount() const {return virtuals.GetCount();}
	//int GetCount() const {return devs.GetCount() + virtuals.GetCount();}
	V4L2_Device& GetNative(int i) {return devs[i];}
	//V4L2_Device& GetVirtual(int i) {return virtuals[i];}
	//V4L2_Device& Get(int i) {return i < devs.GetCount() ? devs[i] : virtuals[i - devs.GetCount()];}
	//V4L2_Device& operator[](int i) {return Get(i);}
	
	//V4L2_Device& GetAddVirtual(String path);
	
	void Refresh();
	
};

NAMESPACE_SERIAL_END

#endif
#endif
