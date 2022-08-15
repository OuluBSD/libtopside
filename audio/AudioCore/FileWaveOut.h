#ifndef _AudioCore_FILEWVOUT_H
#define _AudioCore_FILEWVOUT_H


NAMESPACE_AUDIO_BEGIN


class FileWaveOut : public WaveOut {
public:

	FileWaveOut( unsigned int bufferFrames = 1024 );

	FileWaveOut( String file_name,
				 unsigned int channel_count = 1,
				 FileWrite::FILE_TYPE type = FileWrite::FILE_WAV,
				 Audio::AudioFormat format = AUDIO_SINT16,
				 unsigned int bufferFrames = 1024 );

	virtual ~FileWaveOut();

	void OpenFile( String file_name,
				   unsigned int channel_count,
				   FileWrite::FILE_TYPE type,
				   Audio::AudioFormat format );
	void CloseFile();
	void Tick( const double sample );
	void Tick( const AudioFrames& frames );

protected:

	void incrementFrame();

	FileWrite file_;
	unsigned int bufferFrames_;
	unsigned int bufferIndex_;
	unsigned int iData_;

};

NAMESPACE_AUDIO_END

#endif
