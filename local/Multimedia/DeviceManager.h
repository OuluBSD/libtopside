#ifndef _Multimedia_MediaDeviceManager_h_
#define _Multimedia_MediaDeviceManager_h_

NAMESPACE_OULU_BEGIN

class MediaDevice {
	
protected:
	friend class MediaDeviceManager;
	
	String path, desc;
	Array<MediaCaptureDevice> caps;
	Array<MediaFileInput> inputs;
	
public:
	MediaDevice() {}
	~MediaDevice() {}
	
	int GetCaptureCount() const {return caps.GetCount();}
	MediaCaptureDevice& GetCapture(int i) {return caps[i];}
	MediaStream* FindOpenDevice();
	MediaFileInput& AddFileInput() {return inputs.Add();}
	
	String GetPath() const {return path;}
	String GetDescription() const {return desc;}
	
};

class MediaDeviceManager {
	Array<MediaDevice> devs;
	Array<MediaDevice> virtuals;
	
	
public:
	typedef MediaDeviceManager CLASSNAME;
	MediaDeviceManager();
	~MediaDeviceManager() {}
	
	int GetNativeCount() const {return devs.GetCount();}
	int GetVirtualCount() const {return virtuals.GetCount();}
	int GetCount() const {return devs.GetCount() + virtuals.GetCount();}
	MediaDevice& GetNative(int i) {return devs[i];}
	MediaDevice& GetVirtual(int i) {return virtuals[i];}
	MediaDevice& Get(int i) {return i < devs.GetCount() ? devs[i] : virtuals[i - devs.GetCount()];}
	MediaDevice& operator[](int i) {return Get(i);}
	
	MediaDevice& GetAddVirtual(String path);
	
	void Refresh();
	
};

NAMESPACE_OULU_END

#endif
