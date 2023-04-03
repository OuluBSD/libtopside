#ifndef _AudioCore_DevWaveOut_h_
#define _AudioCore_DevWaveOut_h_


NAMESPACE_AUDIO_BEGIN

#if 0

class DevWaveOut : public WaveOut {
	Sound snd;
	int device, channels;
public:
	typedef DevWaveOut CLASSNAME;

	DevWaveOut( int bufferFrames = 2048 );

	/*DevWaveOut( String file_name,
				 int channel_count = 1,
				 FileWrite::FILE_TYPE type = FileWrite::FILE_WAV,
				 Audio::AudioFormat format = AUDIO_SINT16,
				 int bufferFrames = 1024 );*/

	virtual ~DevWaveOut();

	void OpenDevice(int i, int channels=2, int sample_rate=-1);
	void Tick( const float sample );
	void Tick( const AudioFrames& frames );
	
	void Generator(StreamCallbackArgs& arg);
protected:
	
	bool CheckError();
	
	int bufferFrames_;
	int iData_;
	int data_src;
	
	Array<AudioFrames> data;
	int data_write, data_read;
	
	bool initializing;
};

#endif

NAMESPACE_AUDIO_END

#endif
