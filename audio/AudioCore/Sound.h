#ifndef _portaudio_Sound_h_
#define _portaudio_Sound_h_

NAMESPACE_OULU_BEGIN

#define LOG_SOUND_ERRORS

#ifdef LOG_SOUND_ERRORS
  #define CHECK_ERROR(STREAM) if((STREAM).IsError()) LOG(__FILE__<<" (line "<<__LINE__<<"): "<<(STREAM).GetError());
#else
  #define CHECK_ERROR(STREAM)
#endif
#define CHECK_ERR CHECK_ERROR(*this)

enum SampleFormat {
	SND_FLOAT32 = paFloat32,
	SND_INT32 = paInt32,
	SND_INT24 = paInt24,
	SND_INT16 = paInt16,
	SND_INT8  = paInt8,
	SND_UINT8 = paUInt8,
	SND_UNKNOWN = -1
};

enum StreamFlags {
	SND_NOFLAG    = paNoFlag,
	SND_NOCLIP    = paClipOff,
	SND_NODITHER  = paDitherOff,
	SND_NEVERDROP = paNeverDropInput,
	SND_CALLBACK_PREFILLED = paPrimeOutputBuffersUsingStreamCallback,
	SND_PLATFORM_SPECIFIC  = paPlatformSpecificFlags
};

enum StreamCallbackResult {
	SND_CONTINUE = paContinue,
	SND_COMPLETE = paComplete,
	SND_ABORT = paAbort
};

enum StreamCallbackFlags {
	SND_INPUT_UNDERFLOW = paInputUnderflow,
	SND_INPUT_OVERFLOW = paInputOverflow,
	SND_OUTPUT_UNDERFLOW = paOutputUnderflow,
	SND_OUTPUT_OVERFLOW = paOutputOverflow,
	SND_PRIMING_OUTPUT = paPrimingOutput
};

struct StreamTimeInfo {
	double InputAdc, Current, OutputDac;
	StreamTimeInfo(const PaStreamCallbackTimeInfo* timeinfo):
	  InputAdc(timeinfo->inputBufferAdcTime),
	  OutputDac(timeinfo->outputBufferDacTime),
	  Current(timeinfo->currentTime){}
	operator const PaStreamCallbackTimeInfo*(){
		return reinterpret_cast<const PaStreamCallbackTimeInfo*>(this);
	}
};

struct StreamCallbackArgs {
	const void* input;
	void* output;
	void* data;
	int state;
	unsigned long fpb;
	StreamTimeInfo timeinfo;
	unsigned long flags;
	StreamCallbackArgs(const void *input, void *output, unsigned long fpb,
	                   StreamTimeInfo timeinfo, unsigned long flags,
	                   void* data) : input(input),output(output),fpb(fpb),timeinfo(timeinfo),
	                                 flags(flags),data(data),state(SND_CONTINUE){};
};

struct StreamCallbackData {
	Callback1<StreamCallbackArgs&> func;
	Callback1<void*> finish;
	void* data;
	StreamCallbackData(){}
	StreamCallbackData(Callback1<StreamCallbackArgs&> function,
	                   Callback1<void*> whenfinish ,void* userdata):
	                          func(function),finish(whenfinish),data(userdata){}
};

struct StreamParameters{
	StreamParameters():device(Null){}
	StreamParameters(Nuller):device(Null){}
	StreamParameters(const StreamParameters& p):
	  device(p.device),channels(p.channels),format(p.format),latency(p.latency),APISpecificInfo(p.APISpecificInfo){}
	StreamParameters(int dev,int channels,SampleFormat format,PaTime latency,void* APISpecificInfo=NULL):
	  device(dev),channels(channels),format(format),latency(latency),APISpecificInfo(APISpecificInfo){}
	bool IsNullInstance()const{return IsNull(device);}
	
	int device;
	int channels;
	//SampleFormat format;
	PaSampleFormat format;
	double latency;
	void* APISpecificInfo;
	operator const PaStreamParameters*()const{
		return reinterpret_cast<const PaStreamParameters*>(this);
	}
};

class ASound : public Sound {
protected:
	mutable int err;
	PaStream* stream;
	
	dword total_frames = 0;
	StreamFlags flags;
	SoundFormat fmt;
	
public:
	ASound();
	ASound(const ASound& s) : err(s.err), fmt(s.fmt), flags(s.flags) {stream = s.stream;}
	
	void Get(void* v, int size) override;
	void Put(void* v, int size, bool realtime) override;
	int GetQueueSize() const override {return 1;}
	SoundFormat GetSoundFormat() const override {return fmt;}
	bool IsQueueFull() const override {return false;}
	
#ifdef flagOPENGL
	virtual bool PaintOpenGLTexture(int texture) {TODO; return false;}
#endif
	
	dword GetFrameCount() const {return total_frames;}
	
protected:
	void OpenStream(PaStreamCallback* cb, void* data,
	                const StreamParameters& inparam, const StreamParameters& outparam);
	void OpenDefaultStream(PaStreamCallback* cb, void* data, int inchannels,int outchannels,SampleFormat format);
	void SetFormat(int out_ch, SampleFormat format);
	
public:
	ASound& SetFrequency(int freq)          {fmt.freq = freq; return *this;}
	ASound& SetSampleRate(dword sr)            {fmt.sample_rate = sr; return *this;}
	ASound& SetFlags(StreamFlags f)            {flags = f; return *this;}
	double GetFrequency() const;
	dword GetSampleRate() const           {return fmt.sample_rate;}
	StreamFlags GetFlags() const          {return flags;}

	void Start()               {err = Pa_StartStream(stream); CHECK_ERR;}
	void Stop()                {err = Pa_StopStream(stream); CHECK_ERR;}
	void Abort()               {err = Pa_AbortStream(stream); CHECK_ERR;}
	void Close();

	bool IsStopped() const;
	bool IsActive() const;
	bool IsOpen() const                 {return (stream != NULL);}
	bool IsError() const                {return err!=paNoError;};
	void ClearError() const             {err=paNoError;}
	int  GetErrorCode() const           {return err;}
	String GetError()const              {return Pa_GetErrorText(err);}

	double GetInputLatency() const;
	double GetOutputLatency() const;
	double Time() const                 {return Pa_GetStreamTime(stream);}
	double CpuLoad() const              {return Pa_GetStreamCpuLoad(stream);}
};

class PaSound : public ASound {
	StreamCallbackData scallback;
	SystemSound snd;
	
public:
	Callback1<StreamCallbackArgs&> WhenAction;
	Callback1<void *> WhenFinished;

	PaSound() {snd.Set(this);}
	PaSound(const Sound &) {snd.Set(this);}

	void Open(void* data,const StreamParameters& inparam,const StreamParameters& outparam);
	void Open(const StreamParameters& inparam,const StreamParameters& outparam);
	void OpenDefault(void* data, int inchannels=0,int outchannels=2,SampleFormat format=SND_FLOAT32);
	void OpenDefault(int inchannels=0, int outchannels=2,SampleFormat format=SND_FLOAT32);

	void operator<<=(Callback1<StreamCallbackArgs&> cb)    {WhenAction = cb;}

	SystemSound& GetSystemSound() {return snd;}
	
private:
	void SetFinishCallback();
};

class BufferedPaSound : public PaSound {
	VolatileSoundBuffer buf;
	
	void SinkCallback(StreamCallbackArgs& args);
	
public:
	typedef BufferedPaSound CLASSNAME;
	BufferedPaSound();
	
	void OpenDefault(void* data, int inchannels=0,int outchannels=2,SampleFormat format=SND_FLOAT32);
	void OpenDefault(int inchannels=0, int outchannels=2,SampleFormat format=SND_FLOAT32);
	
	dword GetWriteFrame() const override {return buf.GetWriteFrame();}
	
	void Get(void* v, int size) override {buf.Get(v, size);}
	void Put(void* v, int size, bool realtime) override {buf.Put(v, size, realtime);}
	int GetQueueSize() const override {return buf.GetQueueSize();}
	SoundFormat GetSoundFormat() const override {return buf.GetSoundFormat();}
	bool IsQueueFull() const override {return buf.IsQueueFull();}
	
};

class SoundStream : public ASound {
	SystemSound snd;
	
public:
	SoundStream() {snd.Set(this);};
	SoundStream(const SoundStream& s){stream = s.stream; snd.Set(this);}

	void Open(const StreamParameters& inparam,const StreamParameters& outparam);
	void OpenDefault(int inchannels=0, int outchannels=2, SampleFormat format=SND_FLOAT32);

	SystemSound& GetSystemSound() {return snd;}
	int ReadAvailable();
	int WriteAvailable();
};

class SoundAPI: public Moveable<SoundAPI>{
public:
	int index, type;
	const char* name;
	int deviceCount;
	PaDeviceIndex defaultInputDevice;
	PaDeviceIndex defaultOutputDevice;
	
	SoundAPI():index(Null),name("Null"){};
	SoundAPI(const Nuller&):index(Null),name("Null"){}
	SoundAPI(int n);
	bool IsNullInstance()const           {return IsNull(index);}
	String ToString()const;
	operator int()const                  {return index;}
	operator const PaHostApiInfo*()const {return Pa_GetHostApiInfo(index);}
};

class SoundDevice: public Moveable<SoundDevice>{
public:
	int index;
	const char* name;
	int API;
	int InputChannels,OutputChannels;
	double LowInputLatency,LowOutputLatency,HighInputLatency,HighOutputLatency;
	double SampleRate;
	
	SoundDevice():index(Null),name("Null"){};
	SoundDevice(const Nuller&):index(Null),name("Null"){}
	SoundDevice(int n);
	bool IsNullInstance()const            {return IsNull(index);}
	String ToString()const;
	operator int()const                   {return index;}
	operator const PaDeviceInfo*()const   {return Pa_GetDeviceInfo(index);}
};

class SoundSystem {
	mutable int err;
	static bool exists;
public:
	SoundSystem();
	~SoundSystem();
	
	void Close();
	
	const Vector<SoundDevice> GetDevices()const;
	const Vector<SoundAPI>    GetAPIs()const;

	const SoundDevice GetDefaultInput()const;
	const SoundDevice GetDefaultOutput()const;
	const SoundAPI    GetDefaultAPI()const;
	
	int GetCount()const;
	int GetAPICount()const;
	const SoundDevice Get(int n)const;
	const SoundAPI    GetAPI(int n)const;
	const SoundDevice operator[](int n)const   {return Get(n);}
	const SoundAPI    operator()(int n)const   {return GetAPI(n);}

	bool IsError() const       {return err<paNoError;};
	void ClearError() const    {err=paNoError;}
	int  GetErrorCode() const  {return err;}
	String GetError()const     {return Pa_GetErrorText(err);}

	static bool Exists()       {return exists;}

	String ToString()const;
};

SoundSystem& SoundSys();

class SoundOutStream {
	
protected:
	
	SoundOutStream();
	
	
public:
	
	void Put(const Record& rec);
	
	bool IsOpen() const;
	
	operator bool() const {return !IsOpen();}
	
	static SoundOutStream OpenDefault();
	
};

NAMESPACE_OULU_END;

#endif
