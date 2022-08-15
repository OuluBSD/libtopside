#ifndef _AudioCore_FILELOOP_H
#define _AudioCore_FILELOOP_H


NAMESPACE_AUDIO_BEGIN


class FileLoop : protected FileWaveIn {
public:

	FileLoop( unsigned long chunkThreshold = 1000000, unsigned long chunkSize = 1024 );

	FileLoop( String file_name, bool raw = false, bool doNormalize = true,
			  unsigned long chunkThreshold = 1000000, unsigned long chunkSize = 1024 );
	~FileLoop();

	void OpenFile( String file_name, bool raw = false, bool doNormalize = true );


	void CloseFile() {
		FileWaveIn::CloseFile();
	};

	void Reset() {
		FileWaveIn::Reset();
	};

	unsigned int GetChannelsOut() const {
		return data_.GetChannelCount();
	};

	void Normalize() {
		FileWaveIn::Normalize( 1.0 );
	};

	void Normalize( double peak ) {
		FileWaveIn::Normalize( peak );
	};

	unsigned long GetSize() const {
		return data_.GetFrameCount();
	};

	double GetFileRate() const {
		return data_.dataRate();
	};

	void SetRate( double rate );

	void SetFrequency( double frequency ) {
		this->SetRate( fileSize_ * frequency / Audio::GetSampleRate() );
	};

	void AddTime( double time );
	void AddPhase( double angle );
	void AddPhaseOffset( double angle );

	double GetLastOut( unsigned int channel = 0 ) {
		return FileWaveIn::GetLastOut( channel );
	};

	double Tick( unsigned int channel = 0 );
	virtual AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	AudioFrames first_frame_;
	double phase_offset_;

};

NAMESPACE_AUDIO_END

#endif
