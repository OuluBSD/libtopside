#ifndef _Multimedia_Media_h_
#define _Multimedia_Media_h_


NAMESPACE_OULU_BEGIN


class MediaStream : public VolatileStream {
	
	
protected:
	String last_path;
	int last_fmt = 0, last_res = 0;
	
	virtual bool OpenDevice0(int fmt, int res) = 0;
	virtual bool Open0(String path) = 0;
public:
	virtual ~MediaStream() {}
	
	bool Open(String path) {last_path = path; return Open0(path);}
	bool OpenDevice(int fmt, int res) {last_fmt = fmt; last_res = res; return OpenDevice0(fmt, res);}
	bool ReopenDevice() {return Open0(last_path) && OpenDevice0(last_fmt, last_res);}
	
	virtual bool IsDeviceOpen() const = 0;
	virtual bool Step(double seconds) = 0;
	virtual bool Read() = 0;
	virtual void Close() = 0;
	virtual Sound& GetSound() = 0;
	virtual Video& GetVideo() = 0;
	virtual int GetFormatCount() const = 0;
	virtual const VideoInputFormat& GetFormat(int i) const = 0;
	virtual String GetPath() const = 0;
	virtual bool FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) = 0;
	
	virtual String GetLastError() const {return "unknown";}
	
};

class MediaInputStream : public MediaStream {
	
protected:
	friend class MediaDeviceManager;
	
	
public:
	
};

class MediaOutputStream : public MediaStream {
	
protected:
	friend class MediaDeviceManager;
	
	
public:
	
};


NAMESPACE_OULU_END


#endif
