#ifndef _AudioCore_PortaudioCore_h_
#define _AudioCore_PortaudioCore_h_


NAMESPACE_TOPSIDE_BEGIN
namespace Portaudio {

#define LOG_SOUND_ERRORS

#ifdef LOG_SOUND_ERRORS
  #define CHECK_ERROR(STREAM) if((STREAM).IsError()) LOG(__FILE__<<" (line "<<__LINE__<<"): "<<(STREAM).GetError());
#else
  #define CHECK_ERROR(STREAM)
#endif
#define CHECK_ERR CHECK_ERROR(*this)

enum SampleFormat {
	SND_FLOAT32				= paFloat32,
	SND_INT32				= paInt32,
	SND_INT24				= paInt24,
	SND_INT16				= paInt16,
	SND_INT8				= paInt8,
	SND_UINT8				= paUInt8,
	SND_UNKNOWN				= -1
};

enum StreamFlags {
	SND_NOFLAG				= paNoFlag,
	SND_NOCLIP				= paClipOff,
	SND_NODITHER			= paDitherOff,
	SND_NEVERDROP			= paNeverDropInput,
	SND_CALLBACK_PREFILLED	= paPrimeOutputBuffersUsingStreamCallback,
	SND_PLATFORM_SPECIFIC	= paPlatformSpecificFlags
};

enum StreamCallbackResult {
	SND_CONTINUE			= paContinue,
	SND_COMPLETE			= paComplete,
	SND_ABORT				= paAbort
};

enum StreamCallbackFlags {
	SND_INPUT_UNDERFLOW		= paInputUnderflow,
	SND_INPUT_OVERFLOW		= paInputOverflow,
	SND_OUTPUT_UNDERFLOW	= paOutputUnderflow,
	SND_OUTPUT_OVERFLOW		= paOutputOverflow,
	SND_PRIMING_OUTPUT		= paPrimingOutput
};

struct AudioFormat {
	int				channels = 0;
	int				freq = 0;
	int				sample_rate = 0;
	SampleFormat	fmt = SND_UNKNOWN;
};

struct StreamTimeInfo {
	float			input_adc;
	float			current;
	float			output_adc;
	
	StreamTimeInfo(	const PaStreamCallbackTimeInfo* timeinfo):
					input_adc(timeinfo->inputBufferAdcTime),
					output_adc(timeinfo->outputBufferDacTime),
					current(timeinfo->currentTime){}
	
	operator const PaStreamCallbackTimeInfo*(){
		return reinterpret_cast<const PaStreamCallbackTimeInfo*>(this);
	}
};

struct StreamCallbackArgs {
	const void*		input;
	void*			output;
	void*			data;
	int				state;
	int	fpb;
	StreamTimeInfo	timeinfo;
	int	flags;
	
	StreamCallbackArgs(const void *input, void *output, int fpb,
	                   StreamTimeInfo timeinfo, int flags,
	                   void* data) : input(input),output(output),fpb(fpb),timeinfo(timeinfo),
	                                 flags(flags),data(data),state(SND_CONTINUE){};
};

struct StreamCallbackData {
	Callback1<StreamCallbackArgs&>	func;
	Callback1<void*>				finish;
	void*							data;
	
	StreamCallbackData(){}
	StreamCallbackData(Callback1<StreamCallbackArgs&> function,
	                   Callback1<void*> whenfinish ,void* userdata):
	                          func(function),finish(whenfinish),data(userdata){}
};

struct StreamParameters {
	StreamParameters() : device(Null){}
	StreamParameters(	Nuller) : device(Null) {}
	StreamParameters(	const StreamParameters& p):
						device(p.device), channels(p.channels), format(p.format), latency(p.latency), api_specific_info(p.api_specific_info) {}
	StreamParameters(	int dev, int channels, SampleFormat format, PaTime latency, void* api_specific_info = NULL) :
						device(dev), channels(channels), format(format), latency(latency), api_specific_info(api_specific_info) {}
	
	bool IsNullInstance() const {return IsNull(device);}

	
	int				device;
	int				channels;
	PaSampleFormat	format;
	float			latency;
	void*			api_specific_info;
	
	operator const PaStreamParameters*() const{
		return reinterpret_cast<const PaStreamParameters*>(this);
	}
};






bool IsPortaudioUninitialized();

class AudioBase {
protected:
	mutable int		err;
	PaStream*		stream;
	
	dword			total_frames = 0;
	StreamFlags		flags;
	AudioFormat		pa_fmt;
	
public:
	AudioBase();
	AudioBase(const AudioBase& s) : err(s.err), pa_fmt(s.pa_fmt), flags(s.flags) {stream = s.stream;}
	
	dword			GetFrameCount() const {return total_frames;}
	
protected:
	void			OpenStream(	PaStreamCallback* cb, void* data,
								const StreamParameters& inparam, const StreamParameters& outparam);
	void			OpenDefaultStream(PaStreamCallback* cb, void* data, int inchannels,int outchannels,SampleFormat format);
	void			SetFormat(int out_ch, SampleFormat format);
	
public:
	AudioBase&		SetFrequency(int freq)          {pa_fmt.freq = freq; return *this;}
	AudioBase&		SetSampleRate(dword sr)         {pa_fmt.sample_rate = sr; return *this;}
	AudioBase&		SetFlags(StreamFlags f)         {flags = f; return *this;}
	float			GetFrequency() const;
	dword			GetSampleRate() const           {return pa_fmt.sample_rate;}
	StreamFlags		GetFlags() const                {return flags;}

	void			Start()               {if (!IsPortaudioUninitialized()) {err = Pa_StartStream(stream); CHECK_ERR;}}
	void			Stop()                {if (!IsPortaudioUninitialized()) {err = Pa_StopStream(stream);  CHECK_ERR;}}
	void			Abort()               {if (!IsPortaudioUninitialized()) {err = Pa_AbortStream(stream); CHECK_ERR;}}
	void			Close();

	bool			IsStopped() const;
	bool			IsActive() const;
	bool			IsOpen() const                  {return (stream != NULL);}
	bool			IsError() const                 {return err!=paNoError;};
	void			ClearError() const              {err=paNoError;}
	int				GetErrorCode() const            {return err;}
	String			GetError() const                {return Pa_GetErrorText(err);}
	AudioFormat		GetFormat() const				{return pa_fmt;}

	float			GetInputLatency() const;
	float			GetOutputLatency() const;
	float			Time() const                 {return Pa_GetStreamTime(stream);}
	float			CpuLoad() const              {return Pa_GetStreamCpuLoad(stream);}
};

class AudioDeviceStream : public AudioBase {
	StreamCallbackData	scallback;
	
public:
	Callback1<StreamCallbackArgs&>		WhenAction;
	Callback1<void *>					WhenFinished;

	AudioDeviceStream() {}

	void			Open(void* data, const StreamParameters& inparam, const StreamParameters& outparam);
	void			Open(const StreamParameters& inparam,const StreamParameters& outparam);
	void			OpenDefault(void* data, int inchannels=0,int outchannels=2,SampleFormat format=SND_FLOAT32);
	void			OpenDefault(int inchannels=0, int outchannels=2,SampleFormat format=SND_FLOAT32);

	void			operator<<=(Callback1<StreamCallbackArgs&> cb)    {WhenAction = cb;}
	
private:
	void			SetFinishCallback();
	
};

class AudioStream : public AudioBase {
	
public:
	AudioStream() {}
	AudioStream(const AudioStream& s){stream = s.stream;}

	void			Open(const StreamParameters& inparam,const StreamParameters& outparam);
	void			OpenDefault(int inchannels=0, int outchannels=2, SampleFormat format=SND_FLOAT32);

	int				ReadAvailable();
	int				WriteAvailable();
};







class AudioAPI : public Moveable<AudioAPI> {
	
public:
	int				index;
	int				type;
	const char*		name;
	int				device_count;
	PaDeviceIndex	default_input_dev;
	PaDeviceIndex	default_output_dev;
	
	AudioAPI() : index(Null), name("Null"){};
	AudioAPI(const Nuller&) : index(Null), name("Null") {}
	AudioAPI(int n);

	bool			IsNullInstance() const		{return IsNull(index);}
	String			ToString() const;
	
	operator int() const						{return index;}
	operator const PaHostApiInfo*() const		{return Pa_GetHostApiInfo(index);}
};

class AudioDevice : public Moveable<AudioDevice> {

public:
	int				index;
	const char*		name;
	int				api;
	int				input_channels;
	int				output_channels;
	float			low_input_latency;
	float			low_output_latency;
	float			high_input_latency;
	float			high_output_latency;
	float			sample_rate;
	
	AudioDevice() : index(Null), name("Null") {};
	AudioDevice(const Nuller&) : index(Null), name("Null") {}
	AudioDevice(int n);
	
	bool			IsNullInstance() const {return IsNull(index);}
	String			ToString() const;
	
	operator int() const {return index;}
	operator const PaDeviceInfo*() const {return Pa_GetDeviceInfo(index);}
	
};


class AudioSystem {
	mutable int		err;
	static bool		exists;
	
public:
	AudioSystem();
	~AudioSystem();
	
	void						Close();
	void						Clear() {Close();}
	
	const Vector<AudioDevice>	GetDevices() const;
	const Vector<AudioAPI>		GetAPIs() const;

	const AudioDevice			GetDefaultInput() const;
	const AudioDevice			GetDefaultOutput() const;
	const AudioAPI				GetDefaultAPI() const;
	
	int							GetCount() const;
	int							GetAPICount() const;
	const AudioDevice			Get(int n) const;
	const AudioAPI				GetAPI(int n) const;
	const AudioDevice			operator[](int n) const {return Get(n);}
	const AudioAPI				operator()(int n) const {return GetAPI(n);}

	bool						IsError() const {return err<paNoError;};
	void						ClearError() const {err=paNoError;}
	int							GetErrorCode() const {return err;}
	String						GetError() const {return Pa_GetErrorText(err);}

	static bool					Exists(){return exists;}

	String						ToString() const;
};

AudioSystem& AudioSys();

class AudioOutStream {
	
protected:
	AudioOutStream();
	
	
public:
	
	void						Put(const Record& rec);
	bool						IsOpen() const;
	static AudioOutStream		OpenDefault();
	
	operator bool() const {return !IsOpen();}
	
	
};

}
NAMESPACE_TOPSIDE_END;

#endif
