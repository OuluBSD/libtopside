#ifndef _AudioCore_FILEWVOUT_H
#define _AudioCore_FILEWVOUT_H


NAMESPACE_AUDIO_BEGIN


class FileWaveOut : public WaveOut {
public:

	FileWaveOut( int bufferFrames = 1024 );

	FileWaveOut( String file_name,
				 int channel_count = 1,
				 FileWrite::FILE_TYPE type = FileWrite::FILE_WAV,
				 Audio::AudioFormat format = AUDIO_SINT16,
				 int bufferFrames = 1024 );

	virtual ~FileWaveOut();

	bool OpenFile( String file_name,
				   int channel_count,
				   FileWrite::FILE_TYPE type,
				   Audio::AudioFormat format );
	void CloseFile();
	void Tick( const float sample );
	void Tick( const float l, const float r );
	void Tick( const AudioFrames& frames );

protected:

	void incrementFrame();

	FileWrite file_;
	int bufferFrames_;
	int bufferIndex_;
	int iData_;

};

NAMESPACE_AUDIO_END

#endif
